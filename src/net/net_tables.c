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
