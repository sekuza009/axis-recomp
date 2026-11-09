/* host_window.c: the game's window without a window (PORTING.md stage 3), when a host runs the game. The game keeps
   its window procedure and talks to it as before; this answers the window calls it makes for its own window and its
   text field, in place of Windows:
   - its window ("AXIS"): created as Windows creates one (WM_NCCREATE, WM_NCCALCSIZE, WM_CREATE, WM_SIZE, WM_MOVE -
     the messages the hidden window got, AXIS_MSGLOG), destroyed the same way (WM_DESTROY, WM_NCDESTROY);
   - posted messages (quitting: WM_CLOSE) queued and delivered at the next frame, before it, as the original's loop
     delivered them; timers (the keep-alives and the join poll) delivered as WM_TIMER when due;
   - the network's socket events (WSAAsyncSelect: the lobby's and the game server's connections) polled each frame;
   - the text field (an EDIT control, subclassed by the game): a line of text with a caret, the messages the game
     sends it, at most `width / 8` characters (as the real control held: no horizontal scrolling, 8-pixel Fixedsys).
   Calls about any other window go on to Windows. hostwin_pump runs from axis_frame (g_platPump). */
#include <windows.h>
#include <winsock2.h>
#include <stddef.h>
#include <string.h>

#define MAIN_MAGIC 0x41584d57   /* "AXMW" */
#define EDIT_MAGIC 0x41584557   /* "AXEW" */

typedef struct Win {
	unsigned magic;
	WNDPROC proc;           /* the procedure messages go to (the game's; for the text field, its subclass) */
	int x, y, w, h;
	int alive;
	/* the text field */
	char text[256];
	int len, caret, selStart, limit;
} Win;

static Win g_main = { MAIN_MAGIC }, g_edit = { EDIT_MAGIC };
static WNDPROC g_mainClassProc;   /* the "AXIS" class's procedure (RegisterClassA / ExA) */
static WNDPROC (*g_editDefault);  /* (unused: the text field's own procedure is edit_proc) */

static Win *win_of(HWND h)
{
	if ((Win *)h == &g_main && g_main.alive) return &g_main;
	if ((Win *)h == &g_edit && g_edit.alive) return &g_edit;
	return NULL;
}
#define IS_OURS(h) ((Win *)(h) == &g_main || (Win *)(h) == &g_edit)

/* the slots' previous contents (what calls about other windows go on to) */
static ATOM (WINAPI *r_RegisterClassA)(const WNDCLASSA *);
static ATOM (WINAPI *r_RegisterClassExA)(const WNDCLASSEXA *);
static HWND (WINAPI *r_CreateWindowExA)(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
static BOOL (WINAPI *r_DestroyWindow)(HWND);
static BOOL (WINAPI *r_ShowWindow)(HWND, int);
static BOOL (WINAPI *r_UpdateWindow)(HWND);
static LRESULT (WINAPI *r_DefWindowProcA)(HWND, UINT, WPARAM, LPARAM);
static BOOL (WINAPI *r_GetClientRect)(HWND, RECT *);
static HDC (WINAPI *r_GetDC)(HWND);
static int (WINAPI *r_ReleaseDC)(HWND, HDC);
static UINT_PTR (WINAPI *r_SetTimer)(HWND, UINT_PTR, UINT, TIMERPROC);
static BOOL (WINAPI *r_KillTimer)(HWND, UINT_PTR);
static BOOL (WINAPI *r_PostMessageA)(HWND, UINT, WPARAM, LPARAM);
static LRESULT (WINAPI *r_SendMessageA)(HWND, UINT, WPARAM, LPARAM);
static LONG (WINAPI *r_SetWindowLongA)(HWND, int, LONG);
static LRESULT (WINAPI *r_CallWindowProcA)(WNDPROC, HWND, UINT, WPARAM, LPARAM);
static int (WINAPI *r_GetWindowTextA)(HWND, LPSTR, int);
static int (WINAPI *r_GetWindowTextLengthA)(HWND);
static int (WINAPI *r_WSAAsyncSelect)(SOCKET, HWND, unsigned, long);
static void (WINAPI *r_PostQuitMessage)(int);
static int (WINAPI *r_MessageBoxA)(HWND, LPCSTR, LPCSTR, UINT);

/* ---- the queue, the timers, the sockets ---- */
typedef struct { HWND w; UINT m; WPARAM wp; LPARAM lp; } Msg;
static Msg g_queue[128];
static int g_qHead, g_qCount;
typedef struct { HWND w; UINT_PTR id; DWORD every, last; int on; } Timer;
static Timer g_timers[16];
typedef struct { SOCKET s; HWND w; unsigned m; long events; int on; } Watch;
static Watch g_watch[8];

static LRESULT deliver(HWND h, UINT m, WPARAM wp, LPARAM lp)
{
	Win *w = win_of(h);
	if (!w || !w->proc)
		return 0;
	return w->proc(h, m, wp, lp);   /* (straight to the procedure: Windows does not know this handle) */
}

static BOOL WINAPI h_PostMessageA(HWND h, UINT m, WPARAM wp, LPARAM lp)
{
	if (!IS_OURS(h))
		return r_PostMessageA(h, m, wp, lp);
	if (!win_of(h) || g_qCount == (int)(sizeof g_queue / sizeof g_queue[0]))
		return FALSE;
	Msg *q = &g_queue[(g_qHead + g_qCount++) % (sizeof g_queue / sizeof g_queue[0])];
	q->w = h; q->m = m; q->wp = wp; q->lp = lp;
	return TRUE;
}

static UINT_PTR WINAPI h_SetTimer(HWND h, UINT_PTR id, UINT ms, TIMERPROC f)
{
	if (!IS_OURS(h))
		return r_SetTimer(h, id, ms, f);
	Timer *free_ = NULL;
	for (int i = 0; i < 16; i++) {
		if (g_timers[i].on && g_timers[i].w == h && g_timers[i].id == id) { free_ = &g_timers[i]; break; }
		if (!g_timers[i].on && !free_) free_ = &g_timers[i];
	}
	if (!free_)
		return 0;
	free_->w = h; free_->id = id; free_->every = ms ? ms : 1; free_->last = GetTickCount(); free_->on = 1;
	return id;
}
static BOOL WINAPI h_KillTimer(HWND h, UINT_PTR id)
{
	if (!IS_OURS(h))
		return r_KillTimer(h, id);
	for (int i = 0; i < 16; i++)
		if (g_timers[i].on && g_timers[i].w == h && g_timers[i].id == id) {
			g_timers[i].on = 0;
			return TRUE;
		}
	return FALSE;
}

/* WSAAsyncSelect for our window: the socket non-blocking (as WSAAsyncSelect makes it), its reads and close polled */
static int WINAPI h_WSAAsyncSelect(SOCKET s, HWND h, unsigned m, long events)
{
	if (!IS_OURS(h))
		return r_WSAAsyncSelect(s, h, m, events);
	for (int i = 0; i < 8; i++)
		if (g_watch[i].on && g_watch[i].s == s)
			g_watch[i].on = 0;
	if (!events)
		return 0;
	u_long nb = 1;
	ioctlsocket(s, FIONBIO, &nb);
	for (int i = 0; i < 8; i++)
		if (!g_watch[i].on) {
			g_watch[i].s = s; g_watch[i].w = h; g_watch[i].m = m; g_watch[i].events = events; g_watch[i].on = 1;
			return 0;
		}
	WSASetLastError(WSAENOBUFS);
	return SOCKET_ERROR;
}

static void poll_sockets(void)
{
	for (int i = 0; i < 8; i++) {
		Watch *w = &g_watch[i];
		if (!w->on)
			continue;
		fd_set r;
		FD_ZERO(&r);
		FD_SET(w->s, &r);
		struct timeval tv = { 0, 0 };
		if (select(0, &r, NULL, NULL, &tv) != 1)
			continue;
		char b;
		int n = recv(w->s, &b, 1, MSG_PEEK);
		if (n > 0) {
			if (w->events & FD_READ)
				deliver(w->w, w->m, (WPARAM)w->s, MAKELONG(FD_READ, 0));
		} else {
			int err = n == 0 ? 0 : WSAGetLastError();
			if (err == WSAEWOULDBLOCK)
				continue;
			w->on = 0;   /* (closed: told once) */
			if (w->events & FD_CLOSE)
				deliver(w->w, w->m, (WPARAM)w->s, MAKELONG(FD_CLOSE, err));
		}
	}
}

/* each frame, before it (the original's loop: the messages, then the frame) */
void hostwin_pump(void)
{
	int n = g_qCount;   /* (the ones posted before this round; those posted while delivering wait for the next) */
	while (n-- > 0 && g_qCount) {
		Msg q = g_queue[g_qHead];
		g_qHead = (g_qHead + 1) % (sizeof g_queue / sizeof g_queue[0]);
		g_qCount--;
		deliver(q.w, q.m, q.wp, q.lp);
	}
	DWORD now = GetTickCount();
	for (int i = 0; i < 16; i++)
		if (g_timers[i].on && now - g_timers[i].last >= g_timers[i].every) {
			g_timers[i].last = now;   /* (one WM_TIMER however late, as Windows coalesces them) */
			deliver(g_timers[i].w, WM_TIMER, g_timers[i].id, 0);
		}
	poll_sockets();
}

/* ---- the text field: the EDIT control's behaviour the game relies on ---- */
static void edit_delete_selection(Win *e)
{
	int a = e->selStart < e->caret ? e->selStart : e->caret, b = e->selStart < e->caret ? e->caret : e->selStart;
	if (a == b)
		return;
	memmove(e->text + a, e->text + b, e->len - b + 1);
	e->len -= b - a;
	e->caret = e->selStart = a;
}
static void edit_insert(Win *e, char c)
{
	edit_delete_selection(e);
	if (e->len >= e->limit || e->len >= (int)sizeof e->text - 1)
		return;   /* (full: the real control refuses it) */
	memmove(e->text + e->caret + 1, e->text + e->caret, e->len - e->caret + 1);
	e->text[e->caret] = c;
	e->len++;
	e->caret = ++e->selStart;
}
static LRESULT CALLBACK edit_proc(HWND h, UINT m, WPARAM wp, LPARAM lp)
{
	Win *e = win_of(h);
	if (!e)
		return 0;
	switch (m) {
	case WM_SETTEXT: {
		const char *s = lp ? (const char *)lp : "";
		e->len = (int)strlen(s);
		if (e->len > (int)sizeof e->text - 1) e->len = sizeof e->text - 1;
		memcpy(e->text, s, e->len);
		e->text[e->len] = 0;
		e->caret = e->selStart = 0;
		return TRUE;
	}
	case WM_GETTEXT: {
		if (!wp) return 0;
		int n = e->len < (int)wp - 1 ? e->len : (int)wp - 1;
		memcpy((char *)lp, e->text, n);
		((char *)lp)[n] = 0;
		return n;
	}
	case WM_GETTEXTLENGTH:
		return e->len;
	case EM_SETSEL: {
		int a = (int)wp, b = (int)lp;
		if (a < 0) { e->selStart = e->caret = e->len; return 0; }
		if (b < 0 || b > e->len) b = e->len;
		if (a > e->len) a = e->len;
		e->selStart = a;
		e->caret = b;
		return 0;
	}
	case WM_CHAR:
		if (wp == 8) {   /* backspace */
			if (e->selStart != e->caret)
				edit_delete_selection(e);
			else if (e->caret > 0) {
				memmove(e->text + e->caret - 1, e->text + e->caret, e->len - e->caret + 1);
				e->len--;
				e->caret = --e->selStart;
			}
		} else if (wp >= 32 && wp != 127 && wp < 256)
			edit_insert(e, (char)wp);
		return 0;
	case WM_KEYDOWN:
		switch (wp) {
		case VK_LEFT: if (e->caret > 0) e->caret--; e->selStart = e->caret; break;   /* (the game swallows Left and Home) */
		case VK_HOME: e->caret = e->selStart = 0; break;
		case VK_RIGHT: if (e->caret < e->len) e->caret++; e->selStart = e->caret; break;
		case VK_END: e->caret = e->selStart = e->len; break;
		case VK_DELETE:
			if (e->selStart != e->caret)
				edit_delete_selection(e);
			else if (e->caret < e->len) {
				memmove(e->text + e->caret, e->text + e->caret + 1, e->len - e->caret);
				e->len--;
			}
			break;
		}
		return 0;
	}
	return 0;   /* (WM_SETFONT, WM_KEYUP, WM_TIMER and the rest: nothing) */
}

/* ---- the window calls ---- */
static ATOM WINAPI h_RegisterClassA(const WNDCLASSA *c)
{
	if (c->lpszClassName && (ULONG_PTR)c->lpszClassName > 0xffff && !strcmp(c->lpszClassName, "AXIS")) {
		g_mainClassProc = c->lpfnWndProc;
		return 0xc0de;
	}
	return r_RegisterClassA(c);
}
static ATOM WINAPI h_RegisterClassExA(const WNDCLASSEXA *c)
{
	if (c->lpszClassName && (ULONG_PTR)c->lpszClassName > 0xffff && !strcmp(c->lpszClassName, "AXIS")) {
		g_mainClassProc = c->lpfnWndProc;
		return 0xc0de;
	}
	return r_RegisterClassExA(c);
}

static HWND WINAPI h_CreateWindowExA(DWORD ex, LPCSTR cls, LPCSTR title, DWORD style, int x, int y, int w, int h,
                                     HWND parent, HMENU menu, HINSTANCE inst, LPVOID param)
{
	int isMain = (ULONG_PTR)cls > 0xffff && !strcmp(cls, "AXIS") && g_mainClassProc;
	int isEdit = (ULONG_PTR)cls > 0xffff && !_stricmp(cls, "EDIT") && IS_OURS(parent);
	if (!isMain && !isEdit)
		return r_CreateWindowExA(ex, cls, title, style, x, y, w, h, parent, menu, inst, param);
	if (isEdit) {
		Win *e = &g_edit;
		memset(&e->text, 0, sizeof *e - offsetof(Win, text));
		e->x = x; e->y = y; e->w = w; e->h = h;
		e->limit = w / 8;   /* (measured: the real control held width / 8 characters - 8-pixel Fixedsys, no scrolling) */
		e->proc = edit_proc;
		e->alive = 1;
		return (HWND)e;
	}
	Win *m = &g_main;
	m->x = x; m->y = y; m->w = w; m->h = h;
	m->proc = g_mainClassProc;
	m->alive = 1;
	HWND hw = (HWND)m;
	CREATESTRUCTA cs = { param, inst, menu, parent, h, w, y, x, (LONG)style, title, cls, ex };
	if (!deliver(hw, WM_NCCREATE, 0, (LPARAM)&cs)) {
		m->alive = 0;
		return NULL;
	}
	RECT r = { x, y, x + w, y + h };
	deliver(hw, WM_NCCALCSIZE, 0, (LPARAM)&r);
	if (deliver(hw, WM_CREATE, 0, (LPARAM)&cs) == -1) {
		m->alive = 0;
		return NULL;
	}
	deliver(hw, WM_SIZE, 0, MAKELONG(w, h));
	deliver(hw, WM_MOVE, 0, MAKELONG(x, y));
	return hw;
}

static BOOL WINAPI h_DestroyWindow(HWND h)
{
	if (!IS_OURS(h))
		return r_DestroyWindow(h);
	Win *w = win_of(h);
	if (!w)
		return FALSE;
	if (w == &g_main) {
		deliver(h, WM_DESTROY, 0, 0);
		deliver(h, WM_NCDESTROY, 0, 0);
		for (int i = 0; i < 16; i++)
			if (g_timers[i].w == h) g_timers[i].on = 0;
		for (int i = 0; i < 8; i++)
			if (g_watch[i].w == h) g_watch[i].on = 0;
	}
	w->alive = 0;
	return TRUE;
}

static BOOL WINAPI h_ShowWindow(HWND h, int cmd) { return IS_OURS(h) ? FALSE : r_ShowWindow(h, cmd); }
static BOOL WINAPI h_UpdateWindow(HWND h) { return IS_OURS(h) ? TRUE : r_UpdateWindow(h); }
static LRESULT WINAPI h_DefWindowProcA(HWND h, UINT m, WPARAM wp, LPARAM lp)
{
	if (!IS_OURS(h))
		return r_DefWindowProcA(h, m, wp, lp);
	return m == WM_NCCREATE ? TRUE : 0;
}
static BOOL WINAPI h_GetClientRect(HWND h, RECT *r)
{
	Win *w = win_of(h);
	if (!IS_OURS(h))
		return r_GetClientRect(h, r);
	if (!w)
		return FALSE;
	r->left = r->top = 0;
	r->right = w->w;
	r->bottom = w->h;
	return TRUE;
}
static HDC WINAPI h_GetDC(HWND h) { return IS_OURS(h) ? (HDC)(ULONG_PTR)0x41584443 : r_GetDC(h); }   /* (the no-GL layer ignores it) */
static int WINAPI h_ReleaseDC(HWND h, HDC dc) { return IS_OURS(h) ? 1 : r_ReleaseDC(h, dc); }
static LRESULT WINAPI h_SendMessageA(HWND h, UINT m, WPARAM wp, LPARAM lp)
{
	if (!IS_OURS(h))
		return r_SendMessageA(h, m, wp, lp);
	return deliver(h, m, wp, lp);
}
static LONG WINAPI h_SetWindowLongA(HWND h, int index, LONG v)
{
	if (!IS_OURS(h))
		return r_SetWindowLongA(h, index, v);
	Win *w = win_of(h);
	if (!w || index != GWL_WNDPROC)
		return 0;
	LONG old = (LONG)(ULONG_PTR)w->proc;
	w->proc = (WNDPROC)(ULONG_PTR)v;
	return old;
}
static LRESULT WINAPI h_CallWindowProcA(WNDPROC p, HWND h, UINT m, WPARAM wp, LPARAM lp)
{
	if (!IS_OURS(h))
		return r_CallWindowProcA(p, h, m, wp, lp);
	return p ? p(h, m, wp, lp) : 0;
}
static int WINAPI h_GetWindowTextA(HWND h, LPSTR out, int n)
{
	if (!IS_OURS(h))
		return r_GetWindowTextA(h, out, n);
	return (int)edit_proc(h, WM_GETTEXT, (WPARAM)n, (LPARAM)out);
}
static int WINAPI h_GetWindowTextLengthA(HWND h)
{
	if (!IS_OURS(h))
		return r_GetWindowTextLengthA(h);
	return (int)edit_proc(h, WM_GETTEXTLENGTH, 0, 0);
}
static void WINAPI h_PostQuitMessage(int code) { (void)code; }   /* (the host's loop is not the game's to end) */
static int WINAPI h_MessageBoxA(HWND h, LPCSTR text, LPCSTR title, UINT type)
{
	return r_MessageBoxA(IS_OURS(h) ? NULL : h, text, title, type);
}

HWND hostwin_main(void) { return g_main.alive ? (HWND)&g_main : NULL; }
/* where the window is (the screen point of its client's origin) */
void hostwin_origin(int *x, int *y) { *x = g_main.x; *y = g_main.y; }
/* its client's size (the frame's: glrec.c g_glrecFrameSize) */
void hostwin_size(int *w, int *h) { *w = g_main.w; *h = g_main.h; }

int hostwin_install(void **(*slot)(const char *name))
{
	int n = 0;
#define HOOK(name) do { void **s = slot(#name); if (s) { *(void **)&r_##name = *s; *s = (void *)h_##name; n++; } } while (0)
	HOOK(RegisterClassA); HOOK(RegisterClassExA); HOOK(CreateWindowExA); HOOK(DestroyWindow); HOOK(ShowWindow);
	HOOK(UpdateWindow); HOOK(DefWindowProcA); HOOK(GetClientRect); HOOK(GetDC); HOOK(ReleaseDC); HOOK(SetTimer);
	HOOK(KillTimer); HOOK(PostMessageA); HOOK(SendMessageA); HOOK(SetWindowLongA); HOOK(CallWindowProcA);
	HOOK(GetWindowTextA); HOOK(GetWindowTextLengthA); HOOK(WSAAsyncSelect); HOOK(PostQuitMessage); HOOK(MessageBoxA);
#undef HOOK
	(void)g_editDefault;
	return n;
}
