/* hostwin64.c: the game's window without a window in the 64-bit build (PORTING.md, stage 6) - standalone/host_window.c
   for the game's 32-bit view of the calls: a window handle is the address of its record in the arena, a window
   procedure a function the game holds (an FN number: fn_ptr calls it), the window class record (WNDCLASSA /
   WNDCLASSEXA) and the creation record (CREATESTRUCTA) words, the messages' wParam / lParam 32-bit. As there:
   - its window ("AXIS"): created with WM_NCCREATE, WM_NCCALCSIZE, WM_CREATE, WM_SIZE, WM_MOVE, destroyed with WM_DESTROY,
     WM_NCDESTROY; posted messages queued and delivered at the next frame; timers delivered as WM_TIMER when due;
   - the network's socket events (WSAAsyncSelect) polled each frame;
   - the text field (an EDIT control the game subclasses): a line of text with a caret, at most width / 8 characters.
   hostwin_pump runs from axis_frame (g_platPump). */
#if defined(__x86_64__) || defined(__aarch64__)
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <winsock2.h>
#else
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/socket.h>
#endif

typedef uint32_t u32;
typedef uint8_t u8;
extern unsigned char *g_arena;
void *arena_malloc(size_t n);
void *fn_ptr(u32 address);
u32 fn_ref(void *fn);
void *host64_handle(void);
#define AP_(v) ((void *)((v) ? g_arena + (u32)(v) : NULL))
#define AV_(p) ((p) ? (u32)((const u8 *)(p) - g_arena) : 0u)

#define WM_CREATE 0x0001
#define WM_DESTROY 0x0002
#define WM_MOVE 0x0003
#define WM_SIZE 0x0005
#define WM_SETTEXT 0x000c
#define WM_GETTEXT 0x000d
#define WM_GETTEXTLENGTH 0x000e
#define WM_NCCREATE 0x0081
#define WM_NCDESTROY 0x0082
#define WM_NCCALCSIZE 0x0083
#define WM_KEYDOWN 0x0100
#define WM_CHAR 0x0102
#define WM_TIMER 0x0113
#define EM_SETSEL 0x00b1
#define FD_READ_ 1
#define FD_CLOSE_ 32
#define MAKELONG_(a, b) ((u32)(uint16_t)(a) | (u32)(uint16_t)(b) << 16)

typedef long (*GameProc)(void *wnd, u32 msg, u32 w, u32 l);   /* (the game's window procedures: src/app/win32.c) */
typedef struct Win {
	u32 magic;
	u32 proc;               /* the procedure messages go to (an FN number; the text field's: edit_proc's) */
	int x, y, w, h;
	int alive;
	char text[256];         /* the text field */
	int len, caret, selStart, limit;
} Win;
#define MAIN_MAGIC 0x41584d57u
#define EDIT_MAGIC 0x41584557u
static Win *g_main, *g_edit;   /* (in the arena: their addresses are the handles) */
static u32 g_mainClassProc;
static void *g_dc;

static Win *win_of(const void *h)
{
	if (h && h == g_main && g_main->alive) return g_main;
	if (h && h == g_edit && g_edit->alive) return g_edit;
	return NULL;
}
#define IS_OURS(h) ((h) && ((h) == (void *)g_main || (h) == (void *)g_edit))

static unsigned ticks(void)
{
	struct timespec t;
	timespec_get(&t, TIME_UTC);
	return (unsigned)(t.tv_sec * 1000u + t.tv_nsec / 1000000);
}

static long deliver(void *h, u32 m, u32 wp, u32 lp)
{
	Win *w = win_of(h);
	if (!w || !w->proc)
		return 0;
	return ((GameProc)fn_ptr(w->proc))(h, m, wp, lp);
}

/* ---- the queue, the timers, the sockets */
typedef struct { void *w; u32 m, wp, lp; } Msg;
static Msg g_queue[128];
static int g_qHead, g_qCount;
typedef struct { void *w; u32 id; unsigned every, last; int on; } Timer;
static Timer g_timers[16];
typedef struct { u32 s; void *w; u32 m; u32 events; int on; } Watch;
static Watch g_watch[8];

static int h_PostMessageA(void *h, u32 m, u32 wp, u32 lp)
{
	if (!win_of(h) || g_qCount == (int)(sizeof g_queue / sizeof g_queue[0]))
		return 0;
	Msg *q = &g_queue[(g_qHead + g_qCount++) % (sizeof g_queue / sizeof g_queue[0])];
	q->w = h; q->m = m; q->wp = wp; q->lp = lp;
	return 1;
}
static u32 h_SetTimer(void *h, u32 id, u32 ms, void *f)
{
	(void)f;
	if (!IS_OURS(h))
		return 0;
	Timer *free_ = NULL;
	for (int i = 0; i < 16; i++) {
		if (g_timers[i].on && g_timers[i].w == h && g_timers[i].id == id) { free_ = &g_timers[i]; break; }
		if (!g_timers[i].on && !free_) free_ = &g_timers[i];
	}
	if (!free_)
		return 0;
	free_->w = h; free_->id = id; free_->every = ms ? ms : 1; free_->last = ticks(); free_->on = 1;
	return id;
}
static int h_KillTimer(void *h, u32 id)
{
	for (int i = 0; i < 16; i++)
		if (g_timers[i].on && g_timers[i].w == h && g_timers[i].id == id) {
			g_timers[i].on = 0;
			return 1;
		}
	return 0;
}
static int h_WSAAsyncSelect(u32 s, void *h, u32 m, u32 events)
{
	for (int i = 0; i < 8; i++)
		if (g_watch[i].on && g_watch[i].s == s)
			g_watch[i].on = 0;
	if (!events)
		return 0;
#ifdef _WIN32
	u_long nb = 1;
	ioctlsocket((SOCKET)s, FIONBIO, &nb);
#else
	fcntl((int)s, F_SETFL, fcntl((int)s, F_GETFL) | O_NONBLOCK);
#endif
	for (int i = 0; i < 8; i++)
		if (!g_watch[i].on) {
			g_watch[i].s = s; g_watch[i].w = h; g_watch[i].m = m; g_watch[i].events = events; g_watch[i].on = 1;
			return 0;
		}
	return -1;
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
		if (select((int)w->s + 1, &r, NULL, NULL, &tv) != 1)
			continue;
		char b;
		int n = (int)recv(w->s, &b, 1, MSG_PEEK);
		if (n > 0) {
			if (w->events & FD_READ_)
				deliver(w->w, w->m, w->s, MAKELONG_(FD_READ_, 0));
		} else {
#ifdef _WIN32
			int err = n == 0 ? 0 : WSAGetLastError();
			if (err == WSAEWOULDBLOCK)
				continue;
#else
			int err = n == 0 ? 0 : errno;
			if (err == EAGAIN || err == EWOULDBLOCK)
				continue;
			if (err)
				err = 10054;   /* (WSAECONNRESET: the game only tells a close from an error) */
#endif
			w->on = 0;
			if (w->events & FD_CLOSE_)
				deliver(w->w, w->m, w->s, MAKELONG_(FD_CLOSE_, err));
		}
	}
}

/* each frame, before it (the original's loop: the messages, then the frame) */
void hostwin_pump(void)
{
	int n = g_qCount;
	while (n-- > 0 && g_qCount) {
		Msg q = g_queue[g_qHead];
		g_qHead = (g_qHead + 1) % (sizeof g_queue / sizeof g_queue[0]);
		g_qCount--;
		deliver(q.w, q.m, q.wp, q.lp);
	}
	unsigned now = ticks();
	for (int i = 0; i < 16; i++)
		if (g_timers[i].on && now - g_timers[i].last >= g_timers[i].every) {
			g_timers[i].last = now;
			deliver(g_timers[i].w, WM_TIMER, g_timers[i].id, 0);
		}
	poll_sockets();
}

/* ---- the text field */
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
		return;
	memmove(e->text + e->caret + 1, e->text + e->caret, e->len - e->caret + 1);
	e->text[e->caret] = c;
	e->len++;
	e->caret = ++e->selStart;
}
static long edit_proc(void *h, u32 m, u32 wp, u32 lp)
{
	Win *e = win_of(h);
	if (!e)
		return 0;
	switch (m) {
	case WM_SETTEXT: {
		const char *s = lp ? AP_(lp) : "";
		e->len = (int)strlen(s);
		if (e->len > (int)sizeof e->text - 1) e->len = sizeof e->text - 1;
		memcpy(e->text, s, e->len);
		e->text[e->len] = 0;
		e->caret = e->selStart = 0;
		return 1;
	}
	case WM_GETTEXT: {
		if (!wp) return 0;
		int n = e->len < (int)wp - 1 ? e->len : (int)wp - 1;
		memcpy(AP_(lp), e->text, n);
		((char *)AP_(lp))[n] = 0;
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
		if (wp == 8) {
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
		case 0x25: if (e->caret > 0) e->caret--; e->selStart = e->caret; break;   /* VK_LEFT */
		case 0x24: e->caret = e->selStart = 0; break;                             /* VK_HOME */
		case 0x27: if (e->caret < e->len) e->caret++; e->selStart = e->caret; break;   /* VK_RIGHT */
		case 0x23: e->caret = e->selStart = e->len; break;                        /* VK_END */
		case 0x2e:                                                                /* VK_DELETE */
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
	return 0;
}

/* ---- the window calls (the game's prototypes: src/game.h) */
static int is_class(u32 nameAddress, const char *name)
{
	return nameAddress > 0xffff && !strcmp((const char *)AP_(nameAddress), name);
}
static int ieq(const char *a, const char *b)
{
	for (; *a && *b; a++, b++)
		if ((*a | 32) != (*b | 32))
			return 0;
	return *a == *b;
}
static u32 h_RegisterClassA(const u32 *c)   /* WNDCLASSA: style, lpfnWndProc, ..., lpszClassName (+9) */
{
	if (is_class(c[9], "AXIS")) {
		g_mainClassProc = c[1];
		return 0xc0de;
	}
	return 0xc0df;   /* (another class: the GL window's own, never created here) */
}
static u32 h_RegisterClassExA(const u32 *c)   /* WNDCLASSEXA: cbSize, style, lpfnWndProc, ..., lpszClassName (+10) */
{
	if (is_class(c[10], "AXIS")) {
		g_mainClassProc = c[2];
		return 0xc0de;
	}
	return 0xc0df;
}
static void *h_CreateWindowExA(u32 ex, const char *cls, const char *title, u32 style, int x, int y, int w, int h,
                               void *parent, void *menu, void *inst, void *param)
{
	u32 c = AV_(cls);
	int isMain = c > 0xffff && !strcmp(cls, "AXIS") && g_mainClassProc;
	int isEdit = c > 0xffff && ieq(cls, "EDIT") && IS_OURS(parent);
	if (isEdit) {
		Win *e = g_edit;
		memset(e->text, 0, sizeof *e - offsetof(Win, text));
		e->x = x; e->y = y; e->w = w; e->h = h;
		e->limit = w / 8;
		e->proc = fn_ref((void *)edit_proc);
		e->alive = 1;
		return e;
	}
	if (!isMain)
		return NULL;
	Win *m = g_main;
	m->x = x; m->y = y; m->w = w; m->h = h;
	m->proc = g_mainClassProc;
	m->alive = 1;
	/* CREATESTRUCTA as the game reads it: lpCreateParams, hInstance, hMenu, hwndParent, cy, cx, y, x, style,
	   lpszName, lpszClass, dwExStyle (on the arena's stack: its address is a game address) */
	u32 cs[12] = { AV_(param), AV_(inst), AV_(menu), AV_(parent), (u32)h, (u32)w, (u32)y, (u32)x, style, AV_(title), c, ex };
	if (!deliver(m, WM_NCCREATE, 0, AV_(cs))) {
		m->alive = 0;
		return NULL;
	}
	int r[4] = { x, y, x + w, y + h };
	deliver(m, WM_NCCALCSIZE, 0, AV_(r));
	if (deliver(m, WM_CREATE, 0, AV_(cs)) == -1) {
		m->alive = 0;
		return NULL;
	}
	deliver(m, WM_SIZE, 0, MAKELONG_(w, h));
	deliver(m, WM_MOVE, 0, MAKELONG_(x, y));
	return m;
}
static int h_DestroyWindow(void *h)
{
	Win *w = win_of(h);
	if (!w)
		return 0;
	if (w == g_main) {
		deliver(h, WM_DESTROY, 0, 0);
		deliver(h, WM_NCDESTROY, 0, 0);
		for (int i = 0; i < 16; i++)
			if (g_timers[i].w == h) g_timers[i].on = 0;
		for (int i = 0; i < 8; i++)
			if (g_watch[i].w == h) g_watch[i].on = 0;
	}
	w->alive = 0;
	return 1;
}
static int h_ShowWindow(void *h, int cmd) { (void)h; (void)cmd; return 0; }
static int h_UpdateWindow(void *h) { (void)h; return 1; }
static long h_DefWindowProcA(void *h, u32 m, u32 wp, u32 lp) { (void)h; (void)wp; (void)lp; return m == WM_NCCREATE; }
static int h_GetClientRect(void *h, int *r)
{
	Win *w = win_of(h);
	if (!w)
		return 0;
	r[0] = r[1] = 0;
	r[2] = w->w;
	r[3] = w->h;
	return 1;
}
static void *h_GetDC(void *h) { (void)h; if (!g_dc) g_dc = host64_handle(); return g_dc; }
static int h_ReleaseDC(void *h, void *dc) { (void)h; (void)dc; return 1; }
static int h_SendMessageA(void *h, u32 m, u32 wp, u32 lp) { return (int)deliver(h, m, wp, lp); }
static u32 h_SetWindowLongA(void *h, int index, u32 v)
{
	Win *w = win_of(h);
	if (!w || index != -4)   /* GWL_WNDPROC */
		return 0;
	u32 old = w->proc;
	w->proc = v;
	return old;
}
static long h_CallWindowProcA(u32 proc, u32 wnd, u32 m, u32 wp, u32 lp)
{
	return proc ? ((GameProc)fn_ptr(proc))(AP_(wnd), m, wp, lp) : 0;
}
static int h_GetWindowTextA(void *h, char *out, int n) { return (int)edit_proc(h, WM_GETTEXT, (u32)n, AV_(out)); }
static int h_GetWindowTextLengthA(void *h) { return (int)edit_proc(h, WM_GETTEXTLENGTH, 0, 0); }
static void h_PostQuitMessage(int code) { (void)code; }

void *hostwin_main(void) { return g_main && g_main->alive ? g_main : NULL; }
void hostwin_origin(int *x, int *y) { *x = g_main ? g_main->x : 0; *y = g_main ? g_main->y : 0; }
void hostwin_size(int *w, int *h) { *w = g_main ? g_main->w : 0; *h = g_main ? g_main->h : 0; }

extern void (*g_platPump)(void);   /* src/plat/host/devices.c */
int hostwin_install(void **(*slot)(const char *name))
{
	g_main = arena_malloc(sizeof *g_main);
	g_edit = arena_malloc(sizeof *g_edit);
	memset(g_main, 0, sizeof *g_main);
	memset(g_edit, 0, sizeof *g_edit);
	g_main->magic = MAIN_MAGIC;
	g_edit->magic = EDIT_MAGIC;
	g_platPump = hostwin_pump;
	int n = 0;
#define HOOK(name) do { void **s = slot(#name); if (s) { *s = (void *)h_##name; n++; } } while (0)
	HOOK(RegisterClassA); HOOK(RegisterClassExA); HOOK(CreateWindowExA); HOOK(DestroyWindow); HOOK(ShowWindow);
	HOOK(UpdateWindow); HOOK(DefWindowProcA); HOOK(GetClientRect); HOOK(GetDC); HOOK(ReleaseDC); HOOK(SetTimer);
	HOOK(KillTimer); HOOK(PostMessageA); HOOK(SendMessageA); HOOK(SetWindowLongA); HOOK(CallWindowProcA);
	HOOK(GetWindowTextA); HOOK(GetWindowTextLengthA); HOOK(WSAAsyncSelect); HOOK(PostQuitMessage);
#undef HOOK
	return n;
}
#endif
