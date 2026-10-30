/* net_tables.c: the network code's fixed tables: the 200 session values (8-byte records at 0xa0b470: in use,
   value; the last index in 0xa0b41c) and the sixteen player slot records (0x410 bytes from 0x9f9840). */
#include "../game.h"
#include <string.h>

/* 0x454110: the first free session record, -1 when all 200 are used */
int (FUN_00454110)(void)
{
	int i = 0;
	for (u32 p = 0xa0b470; p < 0xa0bab0; p += 8, i++)
		if (GAME_VAR(u32, p) == 0)
			return i;
	return -1;
}

/* 0x4532b0: session i's value, 0 when out of range or unused */
int (arena_4532b0)(int i)
{
	if (i > -1 && i <= GAME_VAR(int, 0xa0b41c) && GAME_VAR(int, 0xa0b470 + i * 8))
		return GAME_VAR(int, 0xa0b474 + i * 8);
	return 0;
}

/* 0x4514a0: player slot (its low byte) taken by player id: the shorts at +0x10 .. +0x22 reset (two of them -1),
   +0x32 the current value of 0xa0b428 */
void (arena_4514a0)(u32 slot, int id)
{
	static const short init[10] = { 0, 0, 0, 0, 0, -1, 0, 0, -1, 0 };
	u32 r = 0x9f9840 + (slot & 0xff) * 0x410;
	GAME_VAR(int, r) = 1;
	GAME_VAR(int, r + 4) = id;
	memcpy((void *)(r + 0x10), init, sizeof init);
	GAME_VAR(short, r + 0x32) = GAME_VAR(short, 0xa0b428);
}

/* 0x4515a0: all slots freed (and the 0x40 bytes at 0x9f93d8 cleared) */
void (arena_4515a0)(void)
{
	memset((void *)0x9f93d8, 0, 0x40);
	for (u32 r = 0x9f9840; r < 0x9fd940; r += 0x410)
		memset((void *)r, 0, 16);
}

/* 0x451450: a free player slot claimed (its flag in the sixteen at 0x9f93d8 set); 0xff when none is free */
u8 (FUN_00451450)(void)
{
	for (u8 i = 0; i < 0x10; i++)
		if (GAME_VAR(int, 0x9f93d8 + i * 4) == 0) {
			GAME_VAR(int, 0x9f93d8 + i * 4) = 1;
			return i;
		}
	return 0xff;
}

/* 0x451410: a slot claimed for the local player (id 0xa0b424) when the session is up; 1 when done */
int (arena_451410)(void)
{
	if (!GAME_VAR(int, 0xa0baf8))
		return 0;
	u8 slot = FUN_00451450();
	arena_4514a0(slot, GAME_VAR(int, 0xa0b424));
	GAME_VAR(u8, 0x9fd954) = slot;
	GAME_VAR(int, 0x9f9838) = 1;
	return 1;
}

/* 0x454130: with a session list (0xa0b384), every used session record (8 bytes from 0xa0b470: used, a malloc'd copy)
   freed and the list emptied (count 0xa0b41c). Returns the count, or 0 without a list */
u32 (arena_454130)(void)
{
	if (!GAME_VAR(int, 0xa0b384))
		return 0;
	for (int i = 0; i < GAME_VAR(int, 0xa0b41c); i++) {
		u32 *rec = (u32 *)(0xa0b470 + i * 8);
		if (rec[0] != 1)
			continue;
		rec[0] = 0;
		if (rec[1])
			crt_free((void *)rec[1]);
		rec[0] = 0;
		rec[1] = 0;
	}
	u32 r = GAME_VAR(u32, 0xa0b41c);
	GAME_VAR(int, 0xa0b41c) = 0;
	return r;
}

/* 0x4542a0: the address typed as "a.b.c.d" (0xa0b43c, cut up in place by strtok) as (a << 24) | b << 16 | c << 8 | d
   (a not masked). Each part goes into a 4-byte slot of a zeroed 20-byte buffer (a longer part runs into the next
   slot); more than four parts would overrun the original's stack, and a string with none makes it copy from NULL */
int (arena_4542a0)(void)
{
	char buf[20];
	memset(buf, 0, sizeof buf);
	char *part = crt_strtok((char *)0xa0b43c, (const char *)0x4b1304);   /* "." */
	strcpy(buf, part);
	if (part)
		for (char *slot = buf + 4; (part = crt_strtok(NULL, (const char *)0x4b3e68)) != NULL; slot += 4)
			strcpy(slot, part);
	int a = crt_atoi(buf), b = crt_atoi(buf + 4), c = crt_atoi(buf + 8), d = crt_atoi(buf + 12);
	return ((((a << 8) | (b & 0xff)) << 8 | (c & 0xff)) << 8) | (d & 0xff);
}

/* 0x454390: the address as "a.b.c.d" (bytes high to low) into 0xa0b460; returns its length + 1 */
int (dplay_formatSessionEntry)(u32 address)
{
	char text[16], part[4];
	itoa((int)(address >> 24), part, 10);
	strcpy(text, part);
	for (int shift = 16; shift >= 0; shift -= 8) {
		strcat(text, (const char *)0x4b1304);
		itoa((int)((address >> shift) & 0xff), part, 10);
		strcat(text, part);
	}
	strcpy((char *)0xa0b460, text);
	return (int)strlen(text) + 1;
}

/* a DirectPlay session description as the enumeration callback gets it, by value */
typedef struct { u8 b[0x85]; } SessionDesc;

/* 0x4540b0: a session found: unless it is the game's own (its GUID, bytes 4 .. 19, the one at 0x4aae70), a copy
   (malloc'd) kept in the first free slot of the table at 0xa0b470, the count up. Returns the copy, 0 for the game's
   own, or -1 when the table is full */
u32 (FUN_004540b0)(SessionDesc d)
{
	if (!memcmp(d.b + 4, (const void *)0x4aae70, 16))
		return 0;
	int i = FUN_00454110();
	if (i < 0)
		return (u32)i;
	void *copy = crt_malloc(0x85);
	GAME_VAR(void *, 0xa0b474 + i * 8) = copy;
	GAME_VAR(int, 0xa0b470 + i * 8) = 1;
	memcpy(GAME_VAR(void *, 0xa0b474 + i * 8), d.b, 0x85);
	GAME_VAR(int, 0xa0b41c) += 1;
	return (u32)copy;
}

/* 0x4547c0: inet_addr of the text (Winsock, through the game's jump to its import) */
u32 (inet_addr_wrap_4547c0)(const char *text) { return ((u32 (STDCALL *)(const char *))0x4a82b0)(text); }

/* 0x451270: a message sent from the local player (0xa0b424) to to: types 2 and 6 guaranteed (flag 1) with 8 bytes,
   type 7 with size bytes, any other with none. Returns the send's result */
int (FUN_00451270)(const int *message, u32 to, u32 size)
{
	u32 flags = 0, length = 0;
	switch (message[0]) {
	case 2:
	case 6:
		flags = 1;
		length = 8;
		break;
	case 7:
		length = size;
		break;
	}
	return FUN_00450bf0(GAME_VAR(u32, 0xa0b424), to, flags, message, length);
}

/* 0x452170: socket 100 (message 0x40a) or 101 (0x40c) set to tell the window wnd about reads and closes
   (WSAAsyncSelect, 0x21); 0 when that fails, else 1 (also without the socket) */
int (net_asyncSelect)(void *wnd, int which)
{
	u32 sock, message;
	if (which == 100) {
		sock = GAME_VAR(u32, 0xa055f8);
		message = 0x40a;
	} else if (which == 101) {
		sock = GAME_VAR(u32, 0xa05630);
		message = 0x40c;
	} else
		return 1;
	if (!sock)
		return 1;
	if (((int (STDCALL *)(u32, void *, u32, u32))0x4a82c8)(sock, wnd, message, 0x21) == -1)
		return 0;
	return 1;
}

/* 0x453720: DirectPlay's start: its state and the session table cleared, COM started, the DirectPlay objects made
   (arena_453770); on a failure everything released again and the error returned, else 0 */
int (dplay_coInit)(void)
{
	GAME_VAR(int, 0xa0b42c) = 0;
	GAME_VAR(int, 0xa0b430) = 0;
	GAME_VAR(int, 0xa0b434) = 0;
	memset((void *)0xa0b470, 0, 0x190 * 4);
	GAME_VAR(int, 0xa0b438) = 0;
	int hr = IMPORT(0x4a93bc, int, void *)(NULL);   /* CoInitialize */
	if (hr >= 0) {
		hr = GAME_CDECL(0x453770, int, void)();      /* arena_453770 */
		if (hr >= 0)
			return 0;
	}
	dplay_release();
	return hr;
}

/* 0x454760: the network thread's three handles closed (0xa0d788, 0xa0bf1c, 0xa0bb10) and the running flag cleared.
   Returns what the original leaves in eax (the last close's answer, or 0) */
u32 (net_454760)(void)
{
	static const u32 handles[3] = { 0xa0d788, 0xa0bf1c, 0xa0bb10 };
	u32 r = 0;
	for (int k = 0; k < 3; k++) {
		r = GAME_VAR(u32, handles[k]);
		if (r) {
			r = IMPORT(0x4a91b0, u32, u32)(r);   /* CloseHandle */
			GAME_VAR(u32, handles[k]) = 0;
		}
	}
	if (GAME_VAR(int, 0xa0d784))
		GAME_VAR(int, 0xa0d784) = 0;
	return r;
}

/* 0x452d70: the server's 62-byte reply received into 0xa052e8 (recv on 0xa05630 until 62 bytes have come or 3 s
   have passed; each call reads to the start of the buffer), then by its kind (+0x1e): 0 accepted (net_452de0), 1
   refused (0xa0b350 set, 0xa0b300 cleared) */
void (net_452d70)(void)
{
	u8 *reply = (u8 *)0xa052e8;
	u32 start = GetTickCount();
	u32 got = 0;
	do {
		int n = ((int (STDCALL *)(u32, void *, int, int))0x4a82d4)(GAME_VAR(u32, 0xa05630), reply, 0x3e, 0);   /* recv */
		if (n > 0)
			got += n;
	} while (GetTickCount() - start <= 3000 && got < 0x3e);
	switch (GAME_VAR(int, 0xa05306)) {
	case 0:
		net_452de0(reply);
		break;
	case 1:
		GAME_VAR(int, 0xa0b350) = 1;
		GAME_VAR(int, 0xa0b300) = 0;
		break;
	}
}

/* 0x4520e0: both sockets (0xa055f8, 0xa05630) closed: a blocking call cancelled, sending shut down, the socket closed,
   the connection's state reset (arena_4519b0); then the connection flags cleared. Returns what the original leaves
   in eax */
u32 (FUN_004520e0)(void)
{
	static const u32 sockets[2] = { 0xa055f8, 0xa05630 };
	u32 r = GAME_VAR(u32, 0xa055f8);
	for (int k = 0; k < 2; k++) {
		if (!GAME_VAR(u32, sockets[k]))
			continue;
		GAME_VAR(int, 0x9fd94c) = 1;
		((int (STDCALL *)(void))0x4a8292)();                                     /* WSACancelBlockingCall */
		((int (STDCALL *)(u32, int))0x4a828c)(GAME_VAR(u32, sockets[k]), 1);   /* shutdown(SD_SEND) */
		((int (STDCALL *)(u32))0x4a8286)(GAME_VAR(u32, sockets[k]));           /* closesocket */
		GAME_VAR(u32, sockets[k]) = 0;
		r = GAME_CDECL(0x4519b0, u32, void)();                                   /* arena_4519b0 */
	}
	GAME_VAR(int, 0xa0b300) = 0;
	GAME_VAR(int, 0xa0b380) = 0;
	return r;
}

/* a block of n bytes from malloc, cleared */
static void *alloc_clear(u32 n)
{
	void *p = crt_malloc(n);
	memset(p, 0, n);
	return p;
}

/* 0x451600: the connection to `kind` (100 the lobby, 101 the game server) started afresh: the server table cleared,
   both sockets closed (a blocking call cancelled, sending shut down; arena_4519b0 after each), the server's address
   taken (its host name, or what net_resolveHost made of it, into 0xa055e4) with its port (0xa05326); then every
   network table cleared and the packet buffers allocated anew, cleared. The caller ignores the eax it leaves */
void (net_closeAll)(int kind)
{
	net_454690();
	static const u32 sockets[2] = { 0xa055f8, 0xa05630 };
	for (int k = 0; k < 2; k++) {
		if (!GAME_VAR(u32, sockets[k]))
			continue;
		((int (STDCALL *)(void))0x4a8292)();                                     /* WSACancelBlockingCall */
		((int (STDCALL *)(u32, int))0x4a828c)(GAME_VAR(u32, sockets[k]), 1);   /* shutdown(SD_SEND) */
		((int (STDCALL *)(u32))0x4a8286)(GAME_VAR(u32, sockets[k]));           /* closesocket */
		GAME_VAR(u32, sockets[k]) = 0;
		arena_4519b0();
	}
	if (kind == 100 || kind == 101) {
		const char *host = (const char *)(kind == 100 ? 0xa0b24c : 0xa055fc);
		strcpy((char *)0xa055e4, net_resolveHost(host) ? (const char *)0xa0d320 : host);
		GAME_VAR(u16, 0xa05326) = GAME_VAR(u16, kind == 100 ? 0xa055f4 : 0xa05634);
	}
	memset((void *)0x9fd960, 0, 0x1e40 * 4);
	memset((void *)0xa05748, 0, 0x16c0 * 4);
	memset((void *)0xa05330, 0, 0x2aa);
	static const struct { u32 at, size; } buffers[] = {
		{ 0xa0b310, 0x5b }, { 0xa0b314, 0x5b }, { 0xa0b318, 0x5b }, { 0xa0b31c, 4 }, { 0xa0b304, 0x10 }, { 0xa0b320, 0x10b },
		{ 0xa0b324, 8 }, { 0xa0b328, 0x79 }, { 0xa0b32c, 0x79 }, { 0xa0b330, 0x79 }, { 0xa0b334, 4 }, { 0xa0b30c, 4 },
		{ 0xa0b308, 0x10 }, { 0xa0b340, 0xb9 }, { 0xa0b344, 0x5c }, { 0xa0b338, 0x36 }, { 0xa052e4, 1 }, { 0xa055e0, 0x1e } };
	for (unsigned k = 0; k < sizeof buffers / sizeof *buffers; k++)
		GAME_VAR(void *, buffers[k].at) = alloc_clear(buffers[k].size);
	memset((void *)0xa052c0, 0, 0x22);
	GAME_VAR(void *, 0xa0b33c) = alloc_clear(0x1e);
	memset((void *)0xa05260, 0, 0x5b);
	memset((void *)0xa0b280, 0, 0x79);
	GAME_VAR(int, 0xa05328) = 0;
	memset((void *)0xa052e8, 0, 0x3e);
	memset((void *)0xa05638, 0, 0x10b);
}

/* a GlobalAlloc'd block unlocked and freed (through its handle) */
static void global_free(void *p)
{
	IMPORT(0x4a918c, u32, void *)(IMPORT(0x4a9078, void *, void *)(p));   /* GlobalUnlock(GlobalHandle(p)) */
	IMPORT(0x4a9190, u32, void *)(IMPORT(0x4a9078, void *, void *)(p));   /* GlobalFree(GlobalHandle(p)) */
}

/* 0x453920: DirectPlay shut down: the lobby object released, the local player destroyed and the session closed and
   released, the session buffers freed (0xa0bab0 is freed but not cleared), COM ended. Returns 0 */
int (dplay_release)(void)
{
	void *lobby = GAME_VAR(void *, 0xa0b398);
	if (lobby) {
		COM(lobby, COM_RELEASE, u32)(lobby);
		GAME_VAR(void *, 0xa0b398) = 0;
	}
	void *play = GAME_VAR(void *, 0xa0b404);
	if (play) {
		if (GAME_VAR(u32, 0xa0b424)) {
			COM(play, 0x24, u32, u32)(play, GAME_VAR(u32, 0xa0b424));   /* DestroyPlayer */
			play = GAME_VAR(void *, 0xa0b404);
			GAME_VAR(u32, 0xa0b424) = 0;
		}
		COM(play, 0x10, u32)(play);   /* Close */
		play = GAME_VAR(void *, 0xa0b404);
		COM(play, COM_RELEASE, u32)(play);
		GAME_VAR(void *, 0xa0b404) = 0;
	}
	if (GAME_VAR(void *, 0xa0baf0)) {
		crt_free(GAME_VAR(void *, 0xa0baf0));
		GAME_VAR(void *, 0xa0baf0) = 0;
	}
	if (GAME_VAR(void *, 0xa0bab0))
		global_free(GAME_VAR(void *, 0xa0bab0));
	if (GAME_VAR(void *, 0xa0baf4)) {
		global_free(GAME_VAR(void *, 0xa0baf4));
		GAME_VAR(void *, 0xa0baf4) = 0;
	}
	IMPORT(0x4a93b8, void, void)();   /* CoUninitialize */
	return 0;
}

/* 0x4547d0: host (a name or dotted address) resolved: Winsock started, a raw ICMP socket opened (for the pings),
   the host looked up and its first address as text in 0xa0d320; the socket closed again. 1 when there is an
   address; 0 if Winsock, the socket or the lookup failed (the socket is left open then, as in the original) */
int (net_resolveHost)(const char *host)
{
	u8 wsa[0x190];
	memset((void *)0xa0d320, 0, 0x64);
	if (((int (STDCALL *)(u32, void *))0x4a82c2)(0x202, wsa))             /* WSAStartup */
		return 0;
	int sock = ((int (STDCALL *)(int, int, int))0x4a82bc)(2, 3, 1);        /* socket(AF_INET, SOCK_RAW, IPPROTO_ICMP) */
	if (sock == -1)
		return 0;
	u8 *entry = ((u8 *(STDCALL *)(const char *))0x4a82a4)(host);           /* gethostbyname */
	if (!entry)
		return 0;
	u32 address = ***(u32 ***)(entry + 0xc);                                 /* h_addr_list[0] */
	strcpy((char *)0xa0d320, ((const char *(STDCALL *)(u32))0x4a82da)(address));   /* inet_ntoa */
	if (!strlen((const char *)0xa0d320))
		return 0;
	if (sock) {
		((int (STDCALL *)(void))0x4a8292)();      /* WSACancelBlockingCall */
		((int (STDCALL *)(int))0x4a8286)(sock);   /* closesocket */
	}
	return 1;
}

/* 0x453fd0: the sessions asked for (DirectPlay EnumSessions, async with the callback 0x453560, flags 0x12): of the
   game's application (GUID at 0x4a96e8), on the instance at *0xa0bad8; once more while 0xa0b418 is 1. 1 on success,
   0 without DirectPlay or on a failure */
int (dplay_enumSessions)(void)
{
	void *play = GAME_VAR(void *, 0xa0b404);
	if (!play)
		return 0;
	u32 desc[0x14];
	memset(desc, 0, sizeof desc);
	desc[0] = 0x50;                                                  /* dwSize */
	memcpy(&desc[2], GAME_VAR(const void *, 0xa0bad8), 16);         /* guidInstance */
	memcpy(&desc[6], (const void *)0x4a96e8, 16);                    /* guidApplication */
	if (!GAME_VAR(int, 0xa0b418)) {
		if (COM(play, 0x34, int, void *, u32, void *, void *, u32)(play, desc, 0, (void *)0x453560, NULL, 0x12) < 0)
			return 0;
		play = GAME_VAR(void *, 0xa0b404);
	}
	if (GAME_VAR(int, 0xa0b418) == 1 &&
	    COM(play, 0x34, int, void *, u32, void *, void *, u32)(play, desc, 0, (void *)0x453560, NULL, 0x12) < 0)
		return 0;
	return 1;
}

#define lstrcpyA(dst, src) IMPORT(0x4a911c, char *, char *, const char *)(dst, src)

/* ---- a received record appended to a list: its strings (each also as the list's name, 20 bytes a slot at
   0xa0bf20) and single bytes copied into the next slot, the count advanced. Returns the slot's offset in the list
   (the original's eax) ---- */
static int list_append(u32 count, u32 base, int size, const u8 *rec, const u8 *strings, int nstrings, int name,
                       const u8 *bytes, int nbytes)
{
	for (int k = 0; k < nstrings; k++)
		lstrcpyA((char *)(base + GAME_VAR(int, count) * size + strings[k]), (const char *)rec + strings[k]);
	lstrcpyA((char *)(0xa0bf20 + GAME_VAR(int, count) * 20), (const char *)rec + name);
	int i = GAME_VAR(int, count);
	u8 *slot = (u8 *)(base + i * size);
	for (int k = 0; k < nbytes; k++)
		slot[bytes[k]] = rec[bytes[k]];
	GAME_VAR(int, count) = i + 1;
	return i * size;
}
/* 0x452af0: a server record (0x5b bytes) into the list at 0xa05748 (count 0xa0b368) */
int (net_452af0)(const u8 *rec)
{
	static const u8 strings[3] = { 0x33, 0x01, 0x53 };
	static const u8 bytes[9] = { 0x00, 0x49, 0x47, 0x48, 0x46, 0x45, 0x43, 0x44, 0x52 };
	return list_append(0xa0b368, 0xa05748, 0x5b, rec, strings, 3, 0x33, bytes, 9);
}
/* 0x452c80: a room record (0x79 bytes) into the list at 0x9fd960 (count 0xa0b358) */
int (net_452c80)(const u8 *rec)
{
	static const u8 strings[4] = { 0x43, 0x33, 0x01, 0x71 };
	static const u8 bytes[9] = { 0x00, 0x67, 0x65, 0x64, 0x63, 0x61, 0x62, 0x66, 0x70 };
	return list_append(0xa0b358, 0x9fd960, 0x79, rec, strings, 4, 0x33, bytes, 9);
}

#define lstrlenA(s) IMPORT(0x4a9188, int, const char *)(s)
/* 0x451350: a chat line for the log: "<name>: <text>" (format 0x4b3e30; the sender's short name from DirectPlay
   through 0x454190, "?" when it has none) in a new global block, stored in *out. Returns the name lookup's result,
   or 0x8007000e (E_OUTOFMEMORY) when the block cannot be had */
int (net_logMessage)(u32 from, const char *text, char **out)
{
	u8 *name = NULL;
	int r = GAME_CDECL(0x454190, int, u32, u8 **)(from, &name);
	if (r >= 0) {
		const char *shortName = *(const char **)(name + 8);
		if (!shortName)
			shortName = (const char *)0x4b3e38;
		int length = lstrlenA(shortName) + lstrlenA(text) + lstrlenA((const char *)0x4b3e30) + 1;
		char *line = IMPORT(0x4a9198, char *, void *)(IMPORT(0x4a9070, void *, u32, u32)(0x42, length));   /* GlobalLock(GlobalAlloc(GHND)) */
		if (!line)
			r = 0x8007000e;
		else {
			((int (CDECL *)(char *, const char *, ...))GAME_VAR(void *, 0x4a92f0))(line, (const char *)0x4b3e30, shortName, text);   /* wsprintfA */
			*out = line;
		}
	}
	if (name)
		global_free(name);
	return r;
}

/* 0x454d90: the first place in text where word appears (strncmp at each position where the first letters match, or
   _strnicmp, ignoring case, when exact is 0); NULL when it does not */
const char *(dplay_454d90)(const char *text, const char *word, int exact)
{
	int length = strlen(word);
	int positions = strlen(text) - length + 1;
	char first = word[0];
	for (int i = 0; i < positions; i++) {
		if (exact) {
			if (text[i] == first && !GAME_CDECL(0x49fbe0, int, const char *, const char *, u32)(text + i, word, length))   /* strncmp */
				return text + i;
		} else if (!GAME_CDECL(0x4a8740, int, const char *, const char *, u32)(text + i, word, length))   /* _strnicmp */
			return text + i;
	}
	return NULL;
}

/* 0x4546d0: the network worker started: two events (0xa0bb10, 0xa0bf1c) and the thread running 0x454560 (handle
   0xa0d788, id 0xa0d784), then the first event set. 1, or 0 when any of them cannot be made */
int (net_startThread)(void)
{
	if (!(GAME_VAR(void *, 0xa0bb10) = IMPORT(0x4a9170, void *, void *, int, int, void *)(NULL, 0, 0, NULL)))   /* CreateEventA */
		return 0;
	if (!(GAME_VAR(void *, 0xa0bf1c) = IMPORT(0x4a9170, void *, void *, int, int, void *)(NULL, 0, 0, NULL)))
		return 0;
	GAME_VAR(void *, 0xa0d788) = IMPORT(0x4a9174, void *, void *, u32, void *, void *, u32, u32 *)(NULL, 0, (void *)0x454560, NULL, 0, (u32 *)0xa0d784);   /* CreateThread */
	if (!GAME_VAR(void *, 0xa0d788))
		return 0;
	SetEvent(GAME_VAR(void *, 0xa0bb10));
	return 1;
}

/* 0x452de0: a player record appended to the list at 0xa05330 (62 bytes a slot, count 0xa0b35c): its name and seven
   dwords (+0x22 .. +0x3a). Returns the slot's offset (the original's eax) */
int (net_452de0)(const u8 *rec)
{
	static const u8 fields[7] = { 0x2a, 0x26, 0x22, 0x2e, 0x36, 0x3a, 0x32 };
	lstrcpyA((char *)(0xa05330 + GAME_VAR(int, 0xa0b35c) * 62), (const char *)rec);
	int i = GAME_VAR(int, 0xa0b35c);
	u8 *slot = (u8 *)(0xa05330 + i * 62);
	for (int k = 0; k < 7; k++)
		*(u32 *)(slot + fields[k]) = *(const u32 *)(rec + fields[k]);
	GAME_VAR(int, 0xa0b35c) = i + 1;
	return i * 62;
}

/* 0x454220: this machine's address as text in 0xa0b43c (16 bytes, cleared first): its host name looked up and the
   first address taken. -1 when the name cannot be had, otherwise 0 */
int (net_getLocalAddress)(void)
{
	char name[0xc8];
	memset((void *)0xa0b43c, 0, 16);
	if (((int (STDCALL *)(char *, int))0x4a82e0)(name, 0xc8) == -1)   /* gethostname */
		return -1;
	u8 *entry = ((u8 *(STDCALL *)(const char *))0x4a82a4)(name);     /* gethostbyname */
	if (entry)
		strcpy((char *)0xa0b43c, ((const char *(STDCALL *)(u32))0x4a82da)(***(u32 ***)(entry + 0xc)));   /* inet_ntoa */
	return 0;
}

/* 0x4512c0: a chat line sent: logged for this player (net_logMessage into 0x9fd944), then a message (type 1, from
   the player 0xa0b424, the text at +0xc) in a new global block sent to everyone (0x450bf0). 1 when sent */
int (match_4512c0)(const char *text)
{
	if (GAME_CDECL(0x451350, int, u32, const char *, char **)(GAME_VAR(u32, 0xa0b424), text, (char **)0x9fd944) < 0)   /* net_logMessage */
		return 0;
	int size = lstrlenA(text) + 0x10;
	u8 *message = IMPORT(0x4a9198, u8 *, void *)(IMPORT(0x4a9070, void *, u32, u32)(0x42, size));   /* GlobalLock(GlobalAlloc(GHND)) */
	if (!message)
		return 0;
	*(u32 *)message = 1;
	*(u32 *)(message + 8) = GAME_VAR(u32, 0xa0b424);
	lstrcpyA((char *)message + 0xc, text);
	return GAME_CDECL(0x450bf0, int, u32, u32, u32, void *, int)(GAME_VAR(u32, 0xa0b424), 0, 0, message, size) >= 0;
}

/* 0x4548b0: host ip pinged (ICMP echo, waiting up to timeout ms). Returns the round trip time, kept in 0xa0d798:
   0 when the echo failed with no time, 1 when it came back in no time */
u32 (net_ping)(u32 ip, u32 timeout)
{
	u32 reply[9];   /* ICMP_ECHO_REPLY; [2] the round trip time */
	GAME_VAR(u32, 0xa0d798) = 0;
	void *icmp = ((void *(STDCALL *)(void))0x454e4c)();   /* IcmpCreateFile */
	memset(reply, 0, sizeof reply);
	reply[2] = 0xffffffff;
	u32 sent = ((u32 (STDCALL *)(void *, u32, void *, u16, void *, void *, u32, u32))0x454e46)(icmp, ip, NULL, 0, NULL, reply, 0x24, timeout);   /* IcmpSendEcho */
	u32 rtt = reply[2];
	if (!sent) {
		GAME_VAR(u32, 0xa0d798) = rtt;
		((int (STDCALL *)(void *))0x454e40)(icmp);   /* IcmpCloseHandle */
		return rtt ? GAME_VAR(u32, 0xa0d798) : 0;
	}
	GAME_VAR(u32, 0xa0d798) = rtt ? rtt : 1;
	((int (STDCALL *)(void *))0x454e40)(icmp);
	return GAME_VAR(u32, 0xa0d798);
}

/* 0x454190: player id's name (a DPNAME) fetched into a new global block (*out): its size asked first (GetPlayerName
   with no buffer). 0, or the error (0x8007000e when the block cannot be had; the block is freed again on a failure) */
int (dplay_getPlayerName)(u32 id, void **out)
{
	void *play = GAME_VAR(void *, 0xa0b404);
	u32 size;
	int r = COM(play, 0x54, int, u32, void *, u32 *)(play, id, NULL, &size);
	if (r != (int)0x8877001e)   /* DPERR_BUFFERTOOSMALL */
		return r;
	void *name = IMPORT(0x4a9198, void *, void *)(IMPORT(0x4a9070, void *, u32, u32)(0x42, size));   /* GlobalLock(GlobalAlloc(GHND)) */
	if (!name)
		return 0x8007000e;
	play = GAME_VAR(void *, 0xa0b404);
	r = COM(play, 0x54, int, u32, void *, u32 *)(play, id, name, &size);
	if (r >= 0) {
		*out = name;
		return 0;
	}
	global_free(name);
	return r;
}

/* 0x4545b0: every server in the list pinged (net_454650 by name, 20 bytes a slot at 0xa0bf20) until done
   (0xa0d7a0): its time in 0xa0d384 (above 1000 ms less 400; 0 when it did not answer) and marked pinged (0xa0bb14);
   then done, and the events reset (0x454740, whose eax it returns) */
u32 (net_4545b0)(void)
{
	GAME_VAR(int, 0xa0d798) = 0;
	if (GAME_VAR(int, 0xa0d79c) > 0) {
		for (int i = 0; i < GAME_VAR(int, 0xa0d79c) && GAME_VAR(int, 0xa0d7a0) != 1; i++) {
			const char *name = (const char *)(0xa0bf20 + i * 20);
			if ((int)strlen(name) <= 0)
				continue;
			if (GAME_CDECL(0x454650, int, const char *, int)(name, i)) {   /* net_454650 */
				int time = GAME_VAR(int, 0xa0d798);
				if (time > 1000)
					GAME_VAR(int, 0xa0d798) = time -= 400;
				GAME_VAR(int, 0xa0d384 + i * 4) = time;
			} else
				GAME_VAR(int, 0xa0d384 + i * 4) = 0;
			GAME_VAR(int, 0xa0bb14 + i * 4) = 1;
		}
	}
	GAME_VAR(int, 0xa0d7a0) = 1;
	return GAME_CDECL(0x454740, u32, void)();   /* net_454740 */
}

/* ---- a reply of size bytes read from socket into buf, waiting up to 3 s. Each recv lands at buf's start (as in the
   original); the bytes are only counted ---- */
static void reply_read(u32 socket, void *buf, u32 size)
{
	u32 start = IMPORT(0x4a9184, u32, void)();   /* GetTickCount */
	u32 got = 0;
	do {
		int n = ((int (STDCALL *)(u32, void *, int, int))0x4a82d4)(GAME_VAR(u32, socket), buf, size, 0);   /* recv */
		if (n > 0)
			got += n;
	} while (IMPORT(0x4a9184, u32, void)() - start <= 3000 && got < size);
}

/* 0x452a30: a lobby reply (0x5b bytes into 0xa05260, socket 0xa055f8), by its type (0xa052aa): 0 a server for the
   list (net_452af0), 1 the list is complete (its count to 0xa0d79c, the ping thread started), 2 / 3 the connection
   state 0xa0b36c set (0xcb / 0x29); 1..3 also end the wait (0xa0b300) */
void (net_452a30)(void)
{
	reply_read(0xa055f8, (void *)0xa05260, 0x5b);
	switch (GAME_VAR(u32, 0xa052aa)) {
	case 0:
		GAME_CDECL(0x452af0, int, void *)((void *)0xa05260);   /* net_452af0 */
		break;
	case 1:
		GAME_VAR(int, 0xa0d79c) = GAME_VAR(int, 0xa0b368);
		GAME_CDECL(0x4546d0, int, void)();   /* net_startThread */
		GAME_VAR(int, 0xa0b36c) = 0xca;
		GAME_VAR(int, 0xa0b300) = 0;
		break;
	case 2:
		GAME_VAR(int, 0xa0b36c) = 0xcb;
		GAME_VAR(int, 0xa0b300) = 0;
		break;
	case 3:
		GAME_VAR(int, 0xa0b36c) = 0x29;
		GAME_VAR(int, 0xa0b300) = 0;
		break;
	}
}

/* 0x452bd0: a game server's reply (0x79 bytes into 0xa0b280, socket 0xa05630), by its type (0xa0b2e8): 0 a room for
   the list (net_452c80), 1 the list is complete (as above, state 0xa0b34c 0xca), 2 / 3 state 0x28 */
void (net_452bd0)(void)
{
	reply_read(0xa05630, (void *)0xa0b280, 0x79);
	switch (GAME_VAR(u32, 0xa0b2e8)) {
	case 0:
		GAME_CDECL(0x452c80, int, void *)((void *)0xa0b280);   /* net_452c80 */
		break;
	case 1:
		GAME_VAR(int, 0xa0d79c) = GAME_VAR(int, 0xa0b358);
		GAME_CDECL(0x4546d0, int, void)();
		GAME_VAR(int, 0xa0b34c) = 0xca;
		GAME_VAR(int, 0xa0b300) = 0;
		break;
	case 2:
	case 3:
		GAME_VAR(int, 0xa0b34c) = 0x28;
		GAME_VAR(int, 0xa0b300) = 0;
		break;
	}
}

/* a global block freed; returns GlobalFree's eax */
static u32 global_free_r(void *p)
{
	IMPORT(0x4a918c, u32, void *)(IMPORT(0x4a9078, void *, void *)(p));          /* GlobalUnlock(GlobalHandle(p)) */
	return IMPORT(0x4a9190, u32, void *)(IMPORT(0x4a9078, void *, void *)(p));   /* GlobalFree(GlobalHandle(p)) */
}

/* 0x450a60: every waiting DirectPlay message received (0x450bc0) into a global block of 0x9fd940 bytes, grown when
   too small: system messages (from 0) go to 0x450c20 and the next is read; the first player message goes to
   arena_451090 (a type 7 one longer than 0x49 bytes is dropped). The block is freed at the end (its size reset).
   Returns what the original leaves in eax */
u32 (arena_450a60)(void)
{
	u8 *buf = NULL;
	u32 size = GAME_VAR(u32, 0x9fd940), r;
	for (;;) {
		u32 from = 0, to = 0;
		r = GAME_CDECL(0x450bc0, u32, u32 *, u32 *, int, void *, u32 *)(&from, &to, 1, buf, &size);
		if (r == 0x887700be || r == 0x887703e8)   /* no more messages */
			break;
		if (r == 0x8877001e) {                     /* the buffer too small: a bigger one */
			if (buf)
				global_free_r(buf);
			buf = IMPORT(0x4a9198, u8 *, void *)(IMPORT(0x4a9070, void *, u32, u32)(0x42, size));   /* GlobalLock(GlobalAlloc(GHND)) */
			if (!buf)
				return 0;
			GAME_VAR(u32, 0x9fd940) = size;
			continue;
		}
		if (r != 0 || GAME_VAR(u32, 0x9fd940) < 4)
			break;
		if (!from) {
			GAME_CDECL(0x450c20, void, void *)(buf);   /* a system message */
			continue;
		}
		if (*(u32 *)buf == 7 && GAME_VAR(u32, 0x9fd940) > 0x49)
			return global_free_r(buf);
		r = GAME_CDECL(0x451090, u32, void *, u32, u32)(buf, GAME_VAR(u32, 0x9fd940), from);   /* arena_451090 */
		break;
	}
	if (!buf)
		return r;
	r = global_free_r(buf);
	GAME_VAR(u32, 0x9fd940) = 0;
	return r;
}

/* the session description shared by hosting and joining (DPSESSIONDESC2 at 0xa0b3b0): cleared, its size, the
   session's GUID and the game's application GUID (0x4a96e8) */
static u32 *session_desc(const void *guid)
{
	u32 *desc = (u32 *)0xa0b3b0;
	memset(desc, 0, 0x50);
	desc[0] = 0x50;                              /* dwSize */
	memcpy(&desc[2], guid, 16);                  /* guidInstance */
	memcpy(&desc[6], (const void *)0x4a96e8, 16);   /* guidApplication */
	return desc;
}

/* the local player created (CreatePlayer with the short name `name`, no data); its id into *id */
static int create_player(void *play, u32 *id, const char *name)
{
	u32 dpname[4] = { 0x10, 0, (u32)name, 0 };   /* DPNAME: dwSize, dwFlags, lpszShortNameA, lpszLongNameA */
	return COM(play, 0x18, int, u32 *, void *, void *, void *, u32, u32)(play, id, dpname, NULL, NULL, 0, 0);
}

/* 0x453cf0: a session hosted (Open with DPOPEN_CREATE): flags 0x44, the instance GUID from *0xa0bad8, the session
   name, at most maxPlayers, the user words (user3 = hi << 8 | lo, sign-extended bytes; user4 the local address,
   unless 0xa0b418), then the local player `player`: its id into 0xa0b424, data into 0xa0b428, the host flag
   0xa0baf8 set and a player slot claimed (arena_451410). 0 without DirectPlay or on a failure, else 1 */
int (dplay_hostSession)(const char *session, const char *player, u32 user1, u32 maxPlayers, u32 user2,
                        signed char hi, signed char lo, u32 data)
{
	void *play = GAME_VAR(void *, 0xa0b404);
	if (!play)
		return 0;
	u32 *desc = session_desc(GAME_VAR(const void *, 0xa0bad8));
	desc[1] = 0x44;                  /* dwFlags */
	desc[12] = (u32)session;         /* lpszSessionNameA */
	desc[10] = maxPlayers;
	desc[16] = user1;
	desc[17] = user2;
	desc[18] = (u32)((int)hi << 8 | (int)lo);
	if (!GAME_VAR(int, 0xa0b418)) {
		GAME_CDECL(0x454220, void, void)();                 /* net_getLocalAddress */
		desc[19] = GAME_CDECL(0x4542a0, u32, void)();       /* arena_4542a0 */
		play = GAME_VAR(void *, 0xa0b404);
	}
	if (COM(play, 0x60, int, void *, u32)(play, desc, 2) < 0)   /* Open(DPOPEN_CREATE) */
		return 0;
	u32 id;
	if (create_player(GAME_VAR(void *, 0xa0b404), &id, player) < 0)
		return 0;
	GAME_VAR(u32, 0xa0b428) = data;
	GAME_VAR(u32, 0xa0b424) = id;
	GAME_VAR(int, 0xa0baf8) = 1;
	GAME_CDECL(0x451410, void, void)();   /* arena_451410 */
	return 1;
}

/* 0x453e60: the session `guid` joined (Open with DPOPEN_JOIN), then the local player `player`: its id into
   0xa0b424, data into 0xa0b428, the host flag 0xa0baf8 cleared. 0x1f4 joined (also for a CreatePlayer error not
   listed), 0x1f9 / 0x1f8 / 0x1f6 Open failing (0x887700dc, 0x887700f0, any other), 0x1fa the session full or
   refusing the player, 0x1fb without DirectPlay */
int (dplay_joinSession)(const void *guid, const char *player, u32 data)
{
	void *play = GAME_VAR(void *, 0xa0b404);
	if (!play)
		return 0x1fb;
	int r = COM(play, 0x60, int, void *, u32)(play, session_desc(guid), 1);   /* Open(DPOPEN_JOIN) */
	if (r == (int)0x887700dc)
		return 0x1f9;
	if (r == (int)0x887700f0)
		return 0x1f8;
	if (r)
		return 0x1f6;
	u32 id;
	r = create_player(GAME_VAR(void *, 0xa0b404), &id, player);
	switch ((u32)r) {
	case 0x88770078: case 0x80070057: case 0x88770028: case 0x8877003c: case 0x887700aa: case 0x88770168:
		return 0x1fa;
	case 0:
		GAME_VAR(u32, 0xa0b428) = data;
		GAME_VAR(u32, 0xa0b424) = id;
		GAME_VAR(int, 0xa0baf8) = 0;
	}
	return 0x1f4;
}

/* the lobby's part of dplay_create: its connection settings (DPLCONNECTION, into a global block 0xa0baf4) with the
   session flags 0x44 and at most 16 players, connected (ConnectEx into 0xa0b404) and the local player created
   with the lobby's player name record; the host flag 0xa0baf8 by the connection's flags (2 create, 1 join). Stops at the
   first failure */
static void dplay_lobbyConnect(void)
{
	if (IMPORT(0x4a93b4, long, const void *, void *, u32, const void *, void **)((const void *)0x4a9648, NULL, 1,
			(const void *)0x4a9658, (void **)0xa0b398) < 0)   /* CoCreateInstance(CLSID_DirectPlayLobby, IID_IDirectPlayLobby3A) */
		return;
	void *lobby = GAME_VAR(void *, 0xa0b398);
	u32 size;
	if ((u32)COM(lobby, 0x20, int, u32, void *, u32 *)(lobby, 0, NULL, &size) != 0x8877001e)   /* DPERR_BUFFERTOOSMALL */
		return;
	u8 *conn = IMPORT(0x4a9198, void *, void *)(IMPORT(0x4a9070, void *, u32, u32)(0x42, size));   /* GlobalLock(GlobalAlloc) */
	GAME_VAR(void *, 0xa0baf4) = conn;
	if (!conn)
		return;
	lobby = GAME_VAR(void *, 0xa0b398);
	if (COM(lobby, 0x20, int, u32, void *, u32 *)(lobby, 0, conn, &size) < 0)   /* GetConnectionSettings */
		return;
	u32 *session = *(u32 **)(GAME_VAR(u8 *, 0xa0baf4) + 8);
	session[1] = 0x44;    /* dwFlags */
	session[10] = 16;     /* dwMaxPlayers */
	lobby = GAME_VAR(void *, 0xa0b398);
	if (COM(lobby, 0x30, int, u32, u32, void *)(lobby, 0, 0, GAME_VAR(void *, 0xa0baf4)) < 0)   /* SetConnectionSettings */
		return;
	lobby = GAME_VAR(void *, 0xa0b398);
	if (COM(lobby, 0x3c, int, u32, const void *, void **, void *)(lobby, 0, (const void *)0x4a9678, (void **)0xa0b404, NULL) < 0)
		return;   /* ConnectEx */
	u32 id;
	void *play = GAME_VAR(void *, 0xa0b404);   /* CreatePlayer with the lobby's DPNAME (lpPlayerName) */
	if (COM(play, 0x18, int, u32 *, void *, void *, void *, u32, u32)(play, &id, *(void **)(GAME_VAR(u8 *, 0xa0baf4) + 0xc),
			NULL, NULL, 0, 0) < 0)
		return;
	u32 flags = *(u32 *)(GAME_VAR(u8 *, 0xa0baf4) + 4);
	if (flags & 2)
		GAME_VAR(int, 0xa0baf8) = 1;
	else if (flags & 1)
		GAME_VAR(int, 0xa0baf8) = 0;
}

/* 0x453790: DirectPlay made: first through a lobby that started the game (dplay_lobbyConnect), then (either way) a plain
   DirectPlay object (arena_4539f0; its failure returned) and the connections listed (EnumConnections of the game's
   application with dplay_enumConnections). The lobby's settings block is freed (but 0xa0baf4 kept). Returns the
   listing's failure, else 0 */
int (dplay_create)(void)
{
	dplay_lobbyConnect();
	int r = GAME_CDECL(0x4539f0, int, void **)((void **)0xa0b404);   /* arena_4539f0 */
	if (r < 0)
		return r;
	void *play = GAME_VAR(void *, 0xa0b404);
	r = COM(play, 0x8c, int, const void *, void *, void *, u32)(play, (const void *)0x4a96e8, (void *)0x4532f0, NULL, 0);
	if (r >= 0)
		r = 0;
	if (GAME_VAR(void *, 0xa0baf4))
		global_free(GAME_VAR(void *, 0xa0baf4));
	return r;
}

/* 0x451090: a game message from player `from`, by its type (the first word): 1 a chat line (+0xc) logged into
   0x9fd948 (the old one dropped first; 0x9fd95c raised); 2 the host's id (+4, into 0x9fd94c) with the player slots
   reset (0x454130, then 0x4515a0); 6 our own player slot (byte +4, 0x410 bytes a slot from 0x9f9840) taken, the slot
   noted in 0x9fd954 and 0x9f9838 raised; 7 another player's slot data: the slot taken by `from` if it was free,
   then a 0x40-byte block (size +5, data +9) stored when the size is right. Returns what the original leaves in
   eax */
u32 (arena_451090)(const u8 *message, u32 size, u32 from)
{
	(void)size;
	u32 type = *(const u32 *)message;
	u32 slot = message[4], length = *(const u32 *)(message + 5);
	u8 *player = (u8 *)0x9f9840 + slot * 0x410;   /* +0 taken, +4 the id, +8 data there, +0xc its size, +0x10 data */
	int r;
	switch (type) {
	case 1:
		if (GAME_VAR(int, 0x9fd948))
			GAME_VAR(int, 0x9fd948) = 0;
		r = GAME_CDECL(0x451350, int, u32, const u8 *, char **)(from, message + 0xc, (char **)0x9fd948);   /* net_logMessage */
		if (r >= 0)
			GAME_VAR(int, 0x9fd95c) = 1;
		return r;
	case 2:
		GAME_VAR(u32, 0x9fd94c) = *(const u32 *)(message + 4);
		GAME_CDECL(0x454130, void, void)();
		return GAME_CDECL(0x4515a0, u32, void)();
	case 6:
		arena_4514a0(slot, GAME_VAR(int, 0xa0b424));
		*(int *)player = 1;
		GAME_VAR(int, 0x9f9838) = 1;
		GAME_VAR(u8, 0x9fd954) = (u8)slot;
		return slot;
	case 7:
		if (*(int *)player != 1) {
			arena_4514a0(slot, from);
			*(int *)player = 1;
			*(u32 *)(player + 4) = from;
		} else if (length != 0x40)
			return slot * 0x410;
		if (length != 0x40)
			return length;
		*(int *)(player + 8) = 1;
		*(u32 *)(player + 0xc) = length;
		memcpy(player + 0x10, message + 9, length);
		return length;
	}
	return type - 1;
}

/* 0x453a90: a fresh DirectPlay connection of kind 0 .. 3: the old object closed (dplay_closeSession). The kind picks
   the service provider (0xa0bad8: 0xa0b3a0, 0xa0b450, 0xa0b408, 0xa0bab8) and its stored connection (0xa0badc from
   0xa0bae0 + 4 * kind); for TCP/IP (0) a compound address is made instead by the lobby from the provider and the
   host `address` (or 0xa0bb0c), size query then fill, into a new block 0xa0baf0. Then (when there is a connection) a
   new DirectPlay object (arena_4539f0) initialised with it and its caps kept (timeout, buffer and queue sizes into
   0xa0bb00 .. 0xa0bb08). 0 when that fails, else 1 */
int (dplay_initConnection)(int kind, const char *address)
{
	if (GAME_VAR(void *, 0xa0b404)) {
		GAME_CDECL(0x453a10, void, void *)(GAME_VAR(void *, 0xa0b404));   /* dplay_closeSession */
		GAME_VAR(void *, 0xa0b404) = NULL;
	}
	static const u32 provider[4] = { 0xa0b3a0, 0xa0b450, 0xa0b408, 0xa0bab8 };
	if ((u32)kind <= 3) {
		GAME_VAR(u32, 0xa0bad8) = provider[kind];
		GAME_VAR(u32, 0xa0badc) = GAME_VAR(u32, 0xa0bae0 + kind * 4);
	}
	if (kind == 0) {
		struct { u32 guid[4], size; const void *data; } element[2];   /* DPCOMPOUNDADDRESSELEMENT */
		char host[0xc0];
		u32 size = 0;
		strcpy(host, address ? address : (const char *)0xa0bb0c);
		memcpy(element[0].guid, (const void *)0x4a9638, 16);   /* DPAID_ServiceProvider */
		element[0].size = 0x10;
		element[0].data = GAME_VAR(const void *, 0xa0bad8);
		memcpy(element[1].guid, (const void *)0x4a9628, 16);   /* DPAID_INet */
		element[1].size = strlen(host) + 1;
		element[1].data = host;
		void *lobby = GAME_VAR(void *, 0xa0b398);
		COM(lobby, 0x38, int, void *, u32, void *, u32 *)(lobby, element, 2, NULL, &size);   /* CreateCompoundAddress */
		void *block = crt_malloc(size);
		GAME_VAR(void *, 0xa0baf0) = block;
		lobby = GAME_VAR(void *, 0xa0b398);
		COM(lobby, 0x38, int, void *, u32, void *, u32 *)(lobby, element, 2, block, &size);
		GAME_VAR(void *, 0xa0badc) = GAME_VAR(void *, 0xa0baf0);
	}
	if (!GAME_VAR(void *, 0xa0badc))
		return 1;
	if (GAME_CDECL(0x4539f0, int, void **)((void **)0xa0b404) < 0 || !GAME_VAR(void *, 0xa0b404))   /* arena_4539f0 */
		return 0;
	void *play = GAME_VAR(void *, 0xa0b404);
	if (COM(play, 0x98, int, void *, u32)(play, GAME_VAR(void *, 0xa0badc), 0) < 0)   /* InitializeConnection */
		return 0;
	u32 caps[10] = { 0x28 };   /* DPCAPS */
	play = GAME_VAR(void *, 0xa0b404);
	if (COM(play, 0x38, int, u32 *, u32)(play, caps, 0))   /* GetCaps */
		return 0;
	GAME_VAR(u32, 0xa0bb00) = caps[9];   /* dwTimeout */
	GAME_VAR(u32, 0xa0bb04) = caps[2];   /* dwMaxBufferSize */
	GAME_VAR(u32, 0xa0bb08) = caps[3];   /* dwMaxQueueSize */
	return 1;
}

/* a server socket closed: pending Winsock calls cancelled, sends shut down, the socket closed and forgotten, then
   0x4519b0. Returns its eax */
static u32 socket_close(u32 socket)
{
	((int (STDCALL *)(void))0x4a8292)();                                  /* WSACancelBlockingCall */
	((int (STDCALL *)(int, int))0x4a828c)(GAME_VAR(int, socket), 1);      /* shutdown(SD_SEND) */
	((int (STDCALL *)(int))0x4a8286)(GAME_VAR(int, socket));              /* closesocket */
	GAME_VAR(int, socket) = 0;
	return GAME_CDECL(0x4519b0, u32, void)();
}

/* the leaving player's record (from *from into *to): the leave flag (+0) and the flagged byte, the bytes listed
   copied in order, then three names; sent as message `type` (net_send), then a second's wait */
static int send_leave(u32 from, u32 to, const u8 *bytes, int nbytes, int flagged, const u8 *names, int type, int code)
{
	u8 *dst = GAME_VAR(u8 *, to);
	if (!dst)
		return 0;
	dst[0] = 1;
	for (int i = 0; i < nbytes; i++) {
		if (bytes[i] == flagged)
			GAME_VAR(u8 *, to)[flagged] = 1;
		else
			GAME_VAR(u8 *, to)[bytes[i]] = GAME_VAR(u8 *, from)[bytes[i]];
	}
	for (int i = 0; i < 3; i++)
		lstrcpyA(GAME_VAR(char *, to) + names[i], GAME_VAR(char *, from) + names[i]);
	GAME_CDECL(0x4521c0, int, int, int)(type, code);   /* net_send */
	IMPORT(0x4a9110, void, u32)(1000);                 /* Sleep */
	return 1;
}

#define WSACancelBlockingCall() ((int (STDCALL *)(void))0x4a8292)()

/* ---- the info sent to the server when a player comes or goes while hosting over TCP/IP: the room's (0xa0b310 into
   the packet 0xa0b314) or the arena's (0xa0b328 into 0xa0b32c), the player count (0x9fd950) included ---- */
#define g_playerCount GAME_VAR(int, 0x9fd950)

static void room_info(u8 *dst, u8 first, u8 count)
{
	const u8 *src = GAME_VAR(const u8 *, 0xa0b310);
	dst[0] = first;
	static const u8 bytes[] = { 0x49, 0x47, 0x48, 0x46 };
	for (int k = 0; k < 4; k++)
		dst[bytes[k]] = src[bytes[k]];
	dst[0x45] = count;
	dst[0x43] = src[0x43];
	dst[0x44] = src[0x44];
	dst[0x52] = src[0x52];
	lstrcpyA((char *)dst + 0x53, (const char *)src + 0x53);
	lstrcpyA((char *)dst + 0x33, (const char *)src + 0x33);
	lstrcpyA((char *)dst + 1, (const char *)src + 1);
	net_send(0xc, 0x64);
}

static void arena_info(u8 *dst, u8 first, u8 count)
{
	const u8 *src = GAME_VAR(const u8 *, 0xa0b328);
	dst[0] = first;
	dst[0x67] = src[0x67];
	dst[0x65] = src[0x65];
	dst[0x64] = src[0x64];
	dst[0x63] = count;
	static const u8 bytes[] = { 0x61, 0x62, 0x66, 0x70 };
	for (int k = 0; k < 4; k++)
		dst[bytes[k]] = src[bytes[k]];
	lstrcpyA((char *)dst + 0x71, (const char *)src + 0x71);
	lstrcpyA((char *)dst + 0x43, (const char *)src + 0x43);
	lstrcpyA((char *)dst + 0x33, (const char *)src + 0x33);
	net_send(0x14, 0x65);
}

/* 0x450c20 (DirectPlay system message): 5, a player created: its slot taken by the host (net_451530, unless
   0x9fd94c), then the info sent with the count less one; 3, a player gone: a slot freed (FUN_00451450 into
   0x9f9424, FUN_00451270), the message's count kept and the info sent (an arena's then starts with 1). Only while
   hosting (0xa0baf8) over TCP/IP (0xa0b418 = 0) with the right socket open (200: the room on the lobby's, 201: the
   arena on the game server's) and nothing pending (0xa0b360 / 0xa0b364). The original leaves eax to callers that
   ignore it */
void (net_sendLocalInfo)(const u32 *msg)
{
	int gone;
	if (msg[0] == 5) {
		if (!GAME_VAR(int, 0x9fd94c))
			GAME_CDECL(0x451530, void, u32)(msg[2]);   /* net_451530 */
		gone = 0;
	} else if (msg[0] == 3) {
		if (!GAME_VAR(int, 0xa0baf8))
			return;
		GAME_VAR(u8, 0x9f9424) = FUN_00451450();
		GAME_CDECL(0x451270, void, void *, u32, int)((void *)0x9f9420, msg[2], 0);   /* FUN_00451270 */
		gone = 1;
	} else
		return;
	if (!GAME_VAR(int, 0xa0baf8) || GAME_VAR(int, 0xa0b418))
		return;
	switch (GAME_VAR(int, 0xa0b380)) {
	case 201:
		if (GAME_VAR(int, 0xa0b364) || !GAME_VAR(int, 0xa05630))
			return;
		if (gone)
			g_playerCount = msg[3];
		if (!GAME_VAR(u8 *, 0xa0b32c))
			return;
		if (gone)
			arena_info(GAME_VAR(u8 *, 0xa0b32c), 1, (u8)g_playerCount);
		else
			arena_info(GAME_VAR(u8 *, 0xa0b32c), GAME_VAR(const u8 *, 0xa0b328)[0], (u8)(g_playerCount - 1));
		break;
	case 200:
		if (GAME_VAR(int, 0xa0b360) || !GAME_VAR(int, 0xa055f8))
			return;
		if (gone)
			g_playerCount = msg[3];
		if (!GAME_VAR(u8 *, 0xa0b314))
			return;
		room_info(GAME_VAR(u8 *, 0xa0b314), GAME_VAR(const u8 *, 0xa0b310)[0], (u8)(g_playerCount - !gone));
		break;
	}
}

/* a TCP socket into *sock connected to the host 0xa055e4 (a dotted address, else looked up by name) at port
   0xa05326, after Winsock 2.2 starts and the socket is bound to any address; connected: 0xa0b380 = status, 1. A
   refusal (connect's result compared with 10061, as the original does) 2, any failure 0 (Winsock cleaned up and
   the network left where the original does so) */
static int connect_socket(int *sock, int status)
{
	const char *host = (const char *)0xa055e4;
	u8 wsa[0x190];
	if (((int (STDCALL *)(u32, void *))0x4a82c2)(0x202, wsa))                /* WSAStartup */
		return 0;
	if (wsa[0] != 2 || wsa[1] != wsa[0]) {
		WSACancelBlockingCall();
		return 0;
	}
	*sock = ((int (STDCALL *)(int, int, int))0x4a82bc)(2, 1, 0);           /* socket(AF_INET, SOCK_STREAM, 0) */
	if (*sock == -1) {
		WSACancelBlockingCall();
		net_disconnect();
		return 0;
	}
	struct { u16 family, port; u32 address; u8 zero[8]; } where;          /* sockaddr_in */
	memset(&where, 0, sizeof where);
	where.family = 2;
	if (((int (STDCALL *)(int, void *, int))0x4a82b6)(*sock, &where, 16) == -1)   /* bind */
		return 0;
	where.family = 2;
	where.address = ((u32 (STDCALL *)(const char *))0x4a82b0)(host);      /* inet_addr */
	where.port = ((u16 (STDCALL *)(u32))0x4a82aa)(GAME_VAR(u16, 0xa05326)); /* htons */
	if (where.address == 0xffffffff) {
		u8 *entry = ((u8 *(STDCALL *)(const char *))0x4a82a4)(host);       /* gethostbyname */
		if (!entry) {
			((void (STDCALL *)(int))0x4a8298)(0x2726);                     /* WSASetLastError(WSAEINVAL) */
			return 0;
		}
		where.address = ***(u32 ***)(entry + 0xc);                          /* h_addr_list[0] */
	}
	int r = ((int (STDCALL *)(int, void *, int))0x4a829e)(*sock, &where, 16);   /* connect */
	if (r == 10061 || r == -1) {
		WSACancelBlockingCall();
		net_disconnect();
		*sock = 0;
		return r == 10061 ? 2 : 0;
	}
	GAME_VAR(int, 0xa0b380) = status;
	return 1;
}

/* 0x451b80: connecting (everything closed first): 100 the lobby's socket (0xa055f8, status 200), 0x65 the game
   server's (0xa05630, status 201); any other mode just 1 */
int (net_connect)(int mode)
{
	net_closeAll(mode);
	GAME_VAR(int, 0xa0b2fc) = 1;
	if (mode == 100)
		return connect_socket((int *)0xa055f8, 200);
	if (mode == 0x65)
		return connect_socket((int *)0xa05630, 201);
	return 1;
}

/* 0x451e60: leaving the network (while connected, 0xa0b2fc = 1): on the lobby's socket (0xa055f8) the player's
   leave record (0xa0b310 into 0xa0b318, message 0xb) unless 0xa0b360, on the room's (0xa05630) the room record
   (0xa0b328 into 0xa0b330, message 0x16) unless 0xa0b364; each socket closed. Without a send buffer it stops there
   (0). Then the connection flags cleared. Returns what the original leaves in eax */
u32 (net_disconnect)(void)
{
	static const u8 lobbyBytes[9] = { 0x49, 0x47, 0x48, 0x46, 0x45, 0x43, 0x44, 0x52 }, lobbyNames[3] = { 0x53, 0x33, 1 };
	static const u8 roomBytes[9] = { 0x67, 0x65, 0x64, 0x63, 0x61, 0x62, 0x66, 0x70 }, roomNames[3] = { 0x71, 0x43, 0x33 };
	if (GAME_VAR(int, 0xa0b2fc) != 1)
		return GAME_VAR(u32, 0xa0b2fc);
	u32 r = GAME_VAR(u32, 0xa055f8);
	if (GAME_VAR(int, 0xa055f8)) {
		if (!GAME_VAR(int, 0xa0b360) && !send_leave(0xa0b310, 0xa0b318, lobbyBytes, 8, 0x45, lobbyNames, 0xb, 0x64))
			return 0;
		r = socket_close(0xa055f8);
	}
	if (GAME_VAR(int, 0xa05630)) {
		if (!GAME_VAR(int, 0xa0b364) && !send_leave(0xa0b328, 0xa0b330, roomBytes, 8, 0x63, roomNames, 0x16, 0x65))
			return 0;
		r = socket_close(0xa05630);
	}
	GAME_VAR(int, 0xa0b300) = 0;
	GAME_VAR(int, 0xa0b380) = 0;
	GAME_VAR(int, 0xa0b2fc) = 0;
	return r;
}

/* 0x450bb0, 0x4532e0: jumps to arena_450a60 and net_getLocalAddress (their eax passed on) */
u32 (FUN_00450bb0)(void) { return arena_450a60(); }
int (jmp_net_getLocalAddress_4532e0)(void) { return net_getLocalAddress(); }

/* ---- packets to the lobby (socket 0xa055f8) and the game server (0xa05630): a kind word, then the kind's buffer ---- */

/* the buffer at the pointer kept at `buffer` sent whole (size bytes) over the socket kept at `socket`, if both are
   there */
static void send_buffer(u32 socket, u32 buffer, int size)
{
	void *data = GAME_VAR(void *, buffer);
	if (data && GAME_VAR(u32, socket))
		((int (STDCALL *)(u32, const void *, int, int))0x4a82ce)(GAME_VAR(u32, socket), data, size, 0);   /* send */
}

/* 0x4521c0: packet `kind` sent to `to` (100 the lobby, 101 the game server; another value sends only the packet
   itself): its kind word (in 0xa0b30c; none: nothing at all), then the kind's buffer: 10 .. 12 to the lobby (0x5b
   bytes), 13 the hello (the game list cleared), 23 the name (0x10), 14 / 15 the address request (this machine's
   address at +0x60), 17 .. 22 and 24 .. 29 to the game server (19 and 21 / 26 after clearing the server or player
   tables, 22 with its first byte set). Most kinds are kept as the last request (0xa0b300). The callers ignore the
   eax it leaves */
void (net_send)(int kind, int to)
{
	u32 *word = GAME_VAR(u32 *, 0xa0b30c);
	if (to == 100 || to == 101) {
		if (!word)
			return;
		*word = (u32)kind;
		u32 socket = to == 100 ? 0xa055f8 : 0xa05630;
		if (GAME_VAR(u32, socket))
			((int (STDCALL *)(u32, const void *, int, int))0x4a82ce)(GAME_VAR(u32, socket), GAME_VAR(void *, 0xa0b30c), 4, 0);
	}
	static const struct { u32 buffer; int size, lobby; } plain[30] = {
		[10] = { 0xa0b310, 0x5b, 1 }, [11] = { 0xa0b318, 0x5b, 1 }, [12] = { 0xa0b314, 0x5b, 1 },
		[17] = { 0xa0b338, 0x36, 0 }, [18] = { 0xa0b328, 0x79, 0 }, [20] = { 0xa0b32c, 0x79, 0 },
		[25] = { 0xa0b33c, 0x1e, 0 }, [27] = { 0xa0b340, 0xb9, 0 }, [28] = { 0xa0b344, 0x5c, 0 }, [29] = { 0xa055e0, 0x1e, 0 } };
	switch (kind) {
	case 10: case 11: case 12: case 17: case 18: case 20: case 27: case 28: case 29:
		GAME_VAR(int, 0xa0b300) = kind;
		/* fall through */
	case 25:
		send_buffer(plain[kind].lobby ? 0xa055f8 : 0xa05630, plain[kind].buffer, plain[kind].size);
		return;
	case 13:
		net_452e60();
		GAME_VAR(int, 0xa0b300) = 13;
		send_buffer(0xa055f8, 0xa0b31c, 4);
		return;
	case 23: {
		char *name = GAME_VAR(char *, 0xa0b304);
		const char *from = GAME_VAR(const char *, 0xa0b310);
		if (!name || !from)
			return;
		strcpy(name, from + 0x33);
		send_buffer(0xa055f8, 0xa0b304, 0x10);
		return;
	}
	case 14: case 15:
		GAME_VAR(int, 0xa0b300) = kind;
		if (!GAME_VAR(void *, 0xa0b320))
			return;
		jmp_net_getLocalAddress_4532e0();
		lstrcpyA(GAME_VAR(char *, 0xa0b320) + 0x60, (const char *)0xa0b43c);
		send_buffer(0xa05630, 0xa0b320, 0x10b);
		return;
	case 19:
		net_454690();
		net_452e80();
		GAME_VAR(int, 0xa0b300) = 0x13;
		send_buffer(0xa05630, 0xa0b334, 4);
		return;
	case 21:
	case 26:
		net_452ea0();
		if (kind == 21)
			GAME_VAR(int, 0xa0b300) = 0x15;
		send_buffer(0xa05630, kind == 21 ? 0xa0b324 : 0xa052e4, kind == 21 ? 8 : 1);
		return;
	case 22:
		GAME_VAR(int, 0xa0b300) = 0x16;
		if (!GAME_VAR(u8 *, 0xa0b330))
			return;
		*GAME_VAR(u8 *, 0xa0b330) = 1;
		send_buffer(0xa05630, 0xa0b330, 0x79);
		return;
	case 24:
		jmp_net_getLocalAddress_4532e0();
		if (!GAME_VAR(char *, 0xa0b308))
			return;
		lstrcpyA(GAME_VAR(char *, 0xa0b308), (const char *)0xa0b43c);
		send_buffer(0xa05630, 0xa0b308, 0x10);
		return;
	}
}

/* ---- replies to the last request (0xa0b300) ---- */

/* size bytes read from the socket kept at `socket` into buf, again and again until that many have come (1) or 3
   seconds since start have passed (0) */
static int recv_all(u32 socket, void *buf, int size, u32 start)
{
	u32 got = 0;
	for (;;) {
		int n = ((int (STDCALL *)(u32, void *, int, int))0x4a82d4)(GAME_VAR(u32, socket), buf, size, 0);   /* recv */
		if (n > 0)
			got += n;
		if (GetTickCount() - start > 3000)
			return 0;
		if (got >= (u32)size)
			return 1;
	}
}

/* a status reply (four bytes into reply): 1 the connection closed, 0 refused, 3 the timeout's code; each ends the
   request and leaves its code in status */
static void status_reply(u32 socket, u32 reply, u32 status, u32 timeout, u32 start)
{
	if (!recv_all(socket, (void *)reply, 4, start)) {
		GAME_VAR(int, status) = timeout;
		GAME_VAR(int, 0xa0b300) = 0;
	}
	switch (GAME_VAR(int, reply)) {
	case 1:
		GAME_VAR(int, status) = 0x67;
		net_disconnect();
		GAME_VAR(int, 0xa0b300) = 0;
		break;
	case 0:
		GAME_VAR(int, 0xa0b300) = 0;
		GAME_VAR(int, status) = 0x66;
		break;
	case 3:
		GAME_VAR(int, 0xa0b300) = 0;
		GAME_VAR(int, status) = timeout;
		break;
	}
}

/* an answer (0x10b bytes into 0xa05638) from the game server: its code kept in `answer` when it is one of `codes`
   (that ends the request); a timeout leaves 0x28 */
static void answer_reply(u32 answer, const u8 *codes, int count, u32 start)
{
	if (!recv_all(0xa05630, (void *)0xa05638, 0x10b, start)) {
		GAME_VAR(int, answer) = 0x28;
		GAME_VAR(int, 0xa0b300) = 0;
	}
	int code = GAME_VAR(int, 0xa05638);
	for (int k = 0; k < count; k++)
		if (code == codes[k]) {
			GAME_VAR(int, 0xa0b300) = 0;
			GAME_VAR(int, answer) = code;
			return;
		}
}

/* 0x452620: the reply to the last request (0xa0b300) read: 10 the lobby's status (0xa055dc into 0xa0b370), 13 the
   list of games, 14 / 15 the game server's answers (kept in 0xa0b378 / 0xa0b37c), 18 its status (0xa0b248 into
   0xa0b374), 19 the server list, 21 the player list, 26 the player list cleared (0xa0b350), 29 a 0x22-byte notice
   (0xa052c0; 0xa0b354 when it is not empty). The callers ignore the eax it leaves */
void (net_recv)(void)
{
	u32 start = GetTickCount();
	static const u8 answers14[6] = { 0x1f, 0x20, 0x21, 0x22, 0x28, 0x2a }, answers15[4] = { 0x1e, 0x21, 0x28, 0x2a };
	switch (GAME_VAR(int, 0xa0b300)) {
	case 10:
		status_reply(0xa055f8, 0xa055dc, 0xa0b370, 0x29, start);
		break;
	case 13:
		net_452a30();
		break;
	case 14:
		answer_reply(0xa0b378, answers14, 6, start);
		break;
	case 15:
		answer_reply(0xa0b37c, answers15, 4, start);
		break;
	case 18:
		status_reply(0xa05630, 0xa0b248, 0xa0b374, 0x28, start);
		break;
	case 19:
		net_452bd0();
		break;
	case 21:
		net_452d70();
		break;
	case 26:
		net_452ea0();
		GAME_VAR(int, 0xa0b350) = 1;
		GAME_VAR(int, 0xa0b300) = 0;
		break;
	case 29:
		recv_all(0xa05630, (void *)0xa052c0, 0x22, start);
		if (*(const u8 *)0xa052c0) {
			GAME_VAR(int, 0xa0b354) = 1;
			GAME_VAR(int, 0xa0b300) = 0;
		}
		break;
	}
}

/* a match packet (0x40 bytes) sent and counted (+0x2340c78); while recording (+0x2340d1d 1) the frame (+0x2340d29),
   the camera's actor (+0x234240d), the packet's size and the packet written to the recording (+0x2340d08) */
static void send_packet(u8 *s, u8 *packet)
{
	net_sendPacketData(0x40, packet);
	GAME_VAR(int, s + 0x2340c78)++;
	if (GAME_VAR(int, s + 0x2340d1d) == 1) {
		int size = 0x40;
		FUN_0046cc30(s + 0x2340d29, 4, 1, GAME_VAR(void *, s + 0x2340d08));
		FUN_0046cc30(s + 0x234240d, 4, 1, GAME_VAR(void *, s + 0x2340d08));
		FUN_0046cc30(&size, 4, 1, GAME_VAR(void *, s + 0x2340d08));
		FUN_0046cc30(packet, 1, size, GAME_VAR(void *, s + 0x2340d08));
	}
}

/* 0x48ead0 (thiscall on the scene): the players' levels sent (a 0x40-byte packet, kind 0xe in its second byte): one
   nibble each for up to 124 players (+0x22ee4c0, 0x28 bytes each, +0x22f0400 of them; two to a byte from the third,
   the even one low), a player in the game (+0 not negative, +0x20 1) its level (+0x24) / 10 + 1, at most 15 (each
   byte cleared at its even player). The frame count (+0x2340c78) goes up; while recording (+0x2340d1d 1) the frame
   (+0x2340d29), the camera's actor (+0x234240d), the packet's size and the packet written to the recording
   (+0x2340d08). Its caller ignores the eax it leaves */
#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))
void THISCALL (net_sendState_48ead0)(u8 *s)
{
	u8 packet[0x40];
	packet[1] = 0xe;
	for (int i = 0; i < FIELD(int, s, 0x22f0400) && i < 0x7c; i++) {
		u8 *player = s + 0x22ee4c0 + i * 0x28;
		if (i % 2 == 0)
			packet[2 + i / 2] = 0;
		if (FIELD(int, player, 0) < 0 || FIELD(int, player, 0x20) != 1)
			continue;
		int level = ftol(FIELD(float, player, 0x24)) / 10 + 1;
		if (level > 15)
			level = 15;
		packet[2 + i / 2] |= (u8)(i % 2 ? level << 4 : level);
	}
	send_packet(s, packet);
}
#undef FIELD

/* 0x48e0f0 (thiscall on the scene): player p's info sent once when flagged (+0x234300a + p x 0x10, cleared): packet
   2 (64 bytes, its first byte left as it was): the name (from the part type record +0x1755230 + p x 0x47fd2, +4),
   then +0x13 its +0x44, +0x14 its +0x48, the actor's team byte (+0x1eccb4c), p, the five parts and six items (each
   + 1), the 30 colour bytes (+0x479a4). Sent by send_packet. Its caller ignores the eax it
   leaves */
void THISCALL (match_48e0f0)(u8 *s, int p)
{
	int *flag = (int *)(s + 0x234300a + p * 0x10);
	if (!*flag)
		return;
	u8 *r = s + 0x1755230 + p * 0x47fd2;
	u8 packet[0x40];
	packet[1] = 2;
	strcpy((char *)packet + 2, (const char *)r + 4);
	packet[0x14] = r[0x48];
	packet[0x13] = r[0x44];
	packet[0x16] = (u8)p;
	packet[0x15] = s[0x1eccb4c + p * 0x8888];
	for (int k = 0; k < 5; k++)
		packet[0x17 + k] = r[0x30c + k * 4] + 1;
	for (int k = 0; k < 6; k++)
		packet[0x1c + k] = r[0x320 + k * 4] + 1;
	memcpy(packet + 0x22, r + 0x479a4, 30);
	*flag = 0;
	send_packet(s, packet);
}

/* 0x4532f0: DirectPlay's EnumConnections callback: the service provider's short name kept upper-cased (the 0x80-byte
   slot of the count 0xa0bac8, which counts up to 9), and by its kind (the name containing "TCP", "IPX", "MODEM" or
   its Korean name, "SERIAL" or its Korean name) its GUID (0xa0b3a0, 0xa0b450, 0xa0b408, 0xa0bab8) and a copy of its
   connection data (GlobalAlloc'ed, 0xa0bab0; 0xa0bae0 .. 0xa0baec). Returns 1 (go on) */
u32 STDCALL (dplay_enumConnections)(const u32 *guid, const void *connection, u32 size, const u32 *name, u32 flags, void *context)
{
	static const struct { u32 words[2], guid, data; } kinds[4] = {
		{ { 0x4b3e64 }, 0xa0b3a0, 0xa0bae0 }, { { 0x4b3e60 }, 0xa0b450, 0xa0bae4 },
		{ { 0x4b3e58, 0x4b3e50 }, 0xa0b408, 0xa0bae8 }, { { 0x4b3e48, 0x4b3e40 }, 0xa0bab8, 0xa0baec } };
	char names[10][0x80];
	char *own = names[GAME_VAR(int, 0xa0bac8)];
	strcpy(own, (const char *)name[2]);   /* lpszShortNameA */
	crt_strupr(own);
	u32 *id = operator_new(0x10);
	if (!id)
		return 1;
	memcpy(id, guid, 0x10);
	void *data = GAME_VAR(void *, 0xa0bab0) = IMPORT(0x4a9198, void *, void *)(IMPORT(0x4a9070, void *, u32, u32)(0x42, size));   /* GlobalLock(GlobalAlloc(GHND)) */
	if (!data)
		return 1;
	memcpy(data, connection, size);
	for (int k = 0; k < 4; k++)
		if (dplay_454d90(own, (const char *)kinds[k].words[0], 1) ||
		    (kinds[k].words[1] && dplay_454d90(own, (const char *)kinds[k].words[1], 1))) {
			memcpy((void *)kinds[k].guid, id, 0x10);
			GAME_VAR(void *, kinds[k].data) = GAME_VAR(void *, 0xa0bab0);
			break;
		}
	operator_delete(id);
	if (GAME_VAR(int, 0xa0bac8) < 9)
		GAME_VAR(int, 0xa0bac8)++;
	return 1;
}

/* 0x48e680 (thiscall on the scene): the first pending match event (flags at 1, each cleared when taken) sent as its
   packet (kind in the second byte; 0x6b where it carries nothing): 3, 4, 5 (+0x2343237, +0x234323b, +0x234323f); 6 two
   bytes (+0x234324f: +0x2343247, +0x234324b); 7 a byte and a line (+0x234319b: +0x234315a, +0x234315e; and byte
   0x3e from +0x2343197); 8 the same (+0x234314e: +0x234310a, +0x234310e); 9 a byte (+0x2343156: +0x2343152); 10 two
   bytes and a line (+0x23431e7: +0x234319f, +0x23431a3, +0x23431a7); 11 the camera's actor, a byte and a line
   (+0x2343233: +0x23431ef, +0x23431f3); 13 (+0x2343243). With none pending any more the events are done
   (+0x2343106 0). Sent by send_packet (even with nothing pending). Its callers ignore the eax it leaves */
void THISCALL (match_48e680)(u8 *s)
{
#define FLAG(offset) GAME_VAR(int, s + (offset))
#define TAKE(offset) (FLAG(offset) == 1 && (FLAG(offset) = 0, 1))
	static const u32 flags[10] = { 0x234319b, 0x234314e, 0x2343156, 0x23431e7, 0x2343233, 0x2343237, 0x234323b, 0x234323f, 0x234324f, 0x2343243 };
	u8 packet[0x40];
	if (TAKE(0x2343237))
		packet[1] = 3, packet[2] = 0x6b;
	else if (TAKE(0x234323b))
		packet[1] = 4, packet[2] = 0x6b;
	else if (TAKE(0x234323f))
		packet[1] = 5, packet[2] = 0x6b;
	else if (TAKE(0x234324f))
		packet[1] = 6, packet[2] = s[0x2343247], packet[3] = s[0x234324b];
	else if (FLAG(0x234319b) == 1) {
		packet[1] = 7;
		packet[2] = s[0x234315a];
		strcpy((char *)packet + 3, (const char *)s + 0x234315e);
		FLAG(0x234319b) = 0;
		packet[0x3c] = s[0x2343197];
	} else if (FLAG(0x234314e) == 1) {
		packet[1] = 8;
		packet[2] = s[0x234310a];
		strcpy((char *)packet + 3, (const char *)s + 0x234310e);
		FLAG(0x234314e) = 0;
	} else if (TAKE(0x2343156))
		packet[1] = 9, packet[2] = s[0x2343152];
	else if (FLAG(0x23431e7) == 1) {
		packet[1] = 10;
		packet[2] = s[0x234319f];
		packet[3] = s[0x23431a3];
		strcpy((char *)packet + 4, (const char *)s + 0x23431a7);
		FLAG(0x23431e7) = 0;
	} else if (FLAG(0x2343233) == 1) {
		packet[1] = 11;
		packet[2] = s[0x234240d];
		packet[3] = s[0x23431ef];
		strcpy((char *)packet + 4, (const char *)s + 0x23431f3);
		FLAG(0x2343233) = 0;
	} else if (TAKE(0x2343243))
		packet[1] = 13, packet[2] = 0x6b;
	int pending = 0;
	for (int k = 0; k < 10; k++)
		pending |= FLAG(flags[k]) != 0;
	if (!pending)
		FLAG(0x2343106) = 0;
	send_packet(s, packet);
#undef FLAG
#undef TAKE
}

/* 0x48e990 (thiscall on the scene): player p's colour ring sent (packet 0xc, p): when either of its flags is set
   (its part type record +0x1755230 + p x 0x47fd2: +0x47fc6, +0x47fca) the ring's position (+0x47fce, a short) and
   16 three-byte colours from there (4 bytes apart, from +0x479c2), the position then 16 on; else 0xffff and the
   position back to 0x180. Sent by send_packet. Its caller ignores the eax it leaves */
void THISCALL (match_48e990)(u8 *s, int p)
{
	u8 *r = s + p * 0x47fd2;
	u8 packet[0x40];
	packet[1] = 0xc;
	packet[2] = (u8)p;
	if (GAME_VAR(int, r + 0x179d1f6) == 1 || GAME_VAR(int, r + 0x179d1fa) == 1) {
		int at = GAME_VAR(int, r + 0x179d1fe);
		memcpy(packet + 3, &at, 2);
		for (int k = 0; k < 16; k++)
			memcpy(packet + 5 + k * 3, r + 0x179cbf2 + (at + k) * 4, 3);
		GAME_VAR(int, r + 0x179d1fe) = at + 16;
	} else {
		packet[3] = packet[4] = 0xff;
		GAME_VAR(int, r + 0x179d1fe) = 0x180;
	}
	send_packet(s, packet);
}

/* a float in memory times a constant, truncated (the original's __ftol) */
static int scaled(const void *v, u32 k)
{
	return ftol(fmul_m(fld_m((const float *)v), (const float *)k));
}

/* an angle wrapped into a turn (FUN_0046c100, given the float's bits) times 0x4aa49c, truncated */
static int angle_byte(const void *v)
{
	return ftol(fmul_m(FUN_0046c100_bits(*(const u32 *)v), (const float *)0x4aa49c));
}

/* 0x48e2c0 (thiscall on the game): player p's state sent (packet 0; the actor at +0x1ecca70 + p x 0x8888): its
   flags word (+0x3f0), a byte of p and its mode (+0x3ec: 0 with +0x140, 1, 2; bit 0 in play +0x14c), the position
   (+0x180, x 0x4a93ec, words), two angles (+0x18c, +0x190) and two tilts (+0x194, +0x198), two nibbles (+0x19c,
   +0x1a4), a third angle (+0x1a0); a pending hit (+0x8850: cleared) as 0x80 alive / 0xc0 dead with the attacker
   (+0x4c0) and value (+0x4c4); then its five shot slots (+0x360, nine bytes each): a slot whose shot (0x4e8 bytes
   from +0x22225fc) is gone is cleared (-1); else flags (1, 3 for a new one: +0x1fc + slot x 0x20 cleared; 4 aimed
   at an actor, 8 still flying), the target (+0xb8, or the object's index + 1, or 0) and the position (+0x60 while
   it flies at an object, else +0x84). Sent by send_packet. Its caller ignores the eax it leaves */
void THISCALL (match_48e2c0)(u8 *g, int p)
{
	u8 *a = g + 0x1ecca70 + p * 0x8888;
	u8 packet[0x40];
	u16 w;
	packet[1] = 0;
	memcpy(packet + 2, a + 0x3f0, 2);
	switch (GAME_VAR(int, a + 0x3ec)) {
	case 0: packet[4] = (u8)((((u8)p << 3) | a[0x140]) << 1); break;
	case 1: packet[4] = (u8)(p << 4 | 0xc); break;
	case 2: packet[4] = (u8)(p << 4 | 0xe); break;
	}
	if (GAME_VAR(int, a + 0x14c) == 1)
		packet[4] |= 1;
	for (int c = 0; c < 3; c++) {
		w = (u16)scaled(a + 0x180 + c * 4, 0x4a93ec);
		memcpy(packet + 5 + c * 2, &w, 2);
	}
	packet[0xb] = (u8)angle_byte(a + 0x18c);
	packet[0xc] = (u8)angle_byte(a + 0x190);
	packet[0xd] = (u8)scaled(a + 0x194, 0x4a9418);
	packet[0xe] = (u8)scaled(a + 0x198, 0x4a9418);
	packet[0xf] = (u8)(scaled(a + 0x19c, 0x4aa498) << 4) | (u8)scaled(a + 0x1a4, 0x4aa498);
	packet[0x10] = (u8)angle_byte(a + 0x1a0);
	packet[0x11] = 0;
	if (GAME_VAR(int, a + 0x8850) == 1) {
		u8 state = GAME_VAR(int, a + 0x128) > 0 ? 0x80 : 0xc0;
		GAME_VAR(int, a + 0x8850) = 0;
		packet[0x11] = state | a[0x4c0];
		packet[0x12] = a[0x4c4];
	}
	for (int k = 0; k < 5; k++)
		packet[0x13 + k * 9] = 0;
	for (int k = 0; k < 5; k++) {
		int *slot = (int *)(a + 0x360 + k * 4), *fresh = (int *)(a + 0x1fc + k * 0x20);
		u8 *o = packet + 0x13 + k * 9;
		if (*slot < 0)
			continue;
		u8 *shot = g + 0x22225fc + *slot * 0x4e8;
		if (GAME_VAR(int, shot + 4) != 1) {
			*slot = -1;
			continue;
		}
		if (*fresh == 1) {
			o[0] |= 3;
			*fresh = 0;
		} else
			o[0] |= 1;
		if (GAME_VAR(int, shot + 0xb8) >= 0) {
			o[0] |= 4;
			w = (u16)GAME_VAR(int, shot + 0xb8);
		} else if (GAME_VAR(void *, shot + 0x6c))
			w = (u16)(FUN_0046cba0(GAME_VAR(void *, shot + 0x6c), GAME_VAR(int, g + 0x1f40ec), 0xac) + 1);
		else
			w = 0;
		memcpy(o + 1, &w, 2);
		int flying = GAME_VAR(float, shot + 0x70) > GAME_VAR(float, shot + 0x74);
		if (flying)
			o[0] |= 8;
		u8 *at = flying && GAME_VAR(void *, shot + 0x6c) ? shot + 0x60 : shot + 0x84;
		for (int c = 0; c < 3; c++) {
			w = (u16)scaled(at + c * 4, 0x4a93ec);
			memcpy(o + 3 + c * 2, &w, 2);
		}
	}
	send_packet(g, packet);
}

/* the next value of the game's table of rand() values (0xa106f8, 4096 of them; the position 0xa1efb8 moves on) */
static u32 table_rand(void)
{
	u32 at = GAME_VAR(u32, 0xa1efb8);
	GAME_VAR(u32, 0xa1efb8) = at + 1;
	return GAME_VAR(u32, 0xa106f8 + (at & 0xfff) * 4);
}

/* a random entry of one of the level's geometry tables (rows of row_len dwords from base, rows of them at +rows,
   n per row at +per_row): its random position (a 16-bit word, below 100000 before it was cut) into *at, the entry
   returned */
static u32 sample(u8 *s, u32 per_row, u32 rows, int row_len, u32 base, u8 *at)
{
	u16 r = (u16)(table_rand() % 100000);
	memcpy(at, &r, 2);
	int n = GAME_VAR(int, s + per_row);
	int row = r / n % GAME_VAR(int, s + rows);
	return GAME_VAR(u32, s + base + (row * row_len + r % n) * 4);
}

/* 0x48dbf0 (thiscall on the scene): player p's game packet (1), sent when flagged (+0x2343006 + p x 0x10, cleared):
   the room's game (its map and modes from +0x1f1668 / +0x1f1cb4 ..; 0xff and 0xffff without one, or once the start
   countdown +0x234239d is running), the clock (+0x22f0408, +0x22f040c), the player's two scores (+0x1eccb6c,
   +0x1eccb70 of its actor), which of the players in use (net_playerInUse) were flagged twice (+0x234300e,
   +0x2343012: cleared, one bit each), the actor's two counts (+0x1eccb54 / 58) and the team scores (+0x2221fb8 /
   bc), the kill notice (+0x22f0404, set back to -1), then two random checks of the level: one of the five geometry
   tables in turn (+0x23423c9 counting; its number in byte 0x2b) and the sixth, each a position and the entry there.
   Sent by send_packet. Its caller ignores the eax it leaves */
void THISCALL (net_sendGamePacket)(u8 *s, int p)
{
	static const struct { u32 per_row, rows; int row_len; u32 base; } tables[5] = {
		{ 0x23423e5, 0x15de6c8, 682, 0x15bd1f8 }, { 0x23423e9, 0x15fff84, 687, 0x15de6cc },
		{ 0x23423ed, 0x163b588, 0x4c0, 0x15fff88 }, { 0x23423f1, 0x1679b34, 1277, 0x163b58c },
		{ 0x23423f5, 0x16c5178, 1544, 0x1679b38 } };
	int *flag = (int *)(s + 0x2343006 + p * 0x10);
	if (!*flag)
		return;
	u8 *a = s + p * 0x8888;
	u8 packet[0x40];
	packet[1] = 1;
	packet[2] = (u8)p;
	if (GAME_VAR(int, s + 0x1f1ca8) > 0 && !(GAME_VAR(float, s + 0x234239d) > *(const float *)0x4a93e8)) {
		int k = GAME_VAR(int, s + 0x1f1cac) * 16;
		packet[3] = s[0x1f1668 + k];
		packet[4] = s[0x1f1cb4];
		packet[5] = s[0x1f166c + k];
		packet[6] = s[0x1f1cb8];
		memcpy(packet + 7, s + 0xbe3000, 2);
	} else
		memset(packet + 3, 0xff, 6);
	memcpy(packet + 9, s + 0x22f0408, 4);
	float clock = f32(fld_m((const float *)(s + 0x22f040c)));
	memcpy(packet + 0xd, &clock, 4);
	u32 turn = GAME_VAR(u32, s + 0x23423c9);
	packet[0x2b] = (u8)(turn % 5);
	GAME_VAR(u32, s + 0x23423c9) = turn + 1;
	u32 v = sample(s, tables[packet[0x2b]].per_row, tables[packet[0x2b]].rows, tables[packet[0x2b]].row_len, tables[packet[0x2b]].base,
	               packet + 0x2c);
	memcpy(packet + 0x2e, &v, 4);
	v = sample(s, 0x23423f9, 0x175522c, 2950, 0x16c517c, packet + 0x32);
	memcpy(packet + 0x34, &v, 4);
	memcpy(packet + 0x11, a + 0x1eccb6c, 4);
	memcpy(packet + 0x15, a + 0x1eccb70, 4);
	u32 twice[2] = { 0, 0 };
	for (int i = 0; i < 16; i++) {
		if (net_playerInUse(i) != 1)
			continue;
		for (int k = 0; k < 2; k++) {
			int *f = (int *)(s + 0x234300e + i * 0x10 + k * 4);
			if (*f == 1) {
				*f = 0;
				twice[k] |= 1u << i;
			}
		}
	}
	memcpy(packet + 0x19, twice, 8);
	memcpy(packet + 0x21, a + 0x1eccb54, 2);
	memcpy(packet + 0x23, a + 0x1eccb58, 2);
	memcpy(packet + 0x25, s + 0x2221fb8, 2);
	memcpy(packet + 0x27, s + 0x2221fbc, 2);
	memcpy(packet + 0x29, s + 0x22f0404, 2);
	GAME_VAR(int, s + 0x22f0404) = -1;
	*flag = 0;
	send_packet(s, packet);
}
