/* plat.h: the platform interface (PORTING.md stage 3). Every call the game makes to the operating system, its
   graphics, sound, input and network libraries goes through one of these operations, by area.

   On master (the bit-exact builds) each operation is the very call the original makes - the same COM method or
   import slot, the same arguments - so the generated code does not change. In the portable build (AXIS_PORTABLE) it
   is a call to plat_<operation>, which src/plat/win32/ implements with the same Windows calls today and another
   host (Godot, PORTING.md) can implement its own way. Handles (a sound buffer, a music stream) are opaque there.

   The operations keep the original's shape (a buffer locked and written, a stream opened then run): the game's
   logic around them is unchanged; only what is behind them is the platform's.

   Two kinds:
   - the COM objects (sound, music, input, network: below) as named operations, SND_ / MUS_ / IN_ / NET_;
   - every plain system call (OpenGL, the window and messages, timers, files, registry, sockets, ping: the 228
     imports of src/import_list.h) as a function of its own name, plat_<name> (glColor4f -> plat_glColor4f), stdcall
     with the system function's arguments: src/axis.h's IMPORT_FN, which game.h's wrappers use, calls it. The Windows
     platform's are build/plat_imports.s (tools/mkimportlist.py --thunks): a jump through the game's import slot, so
     the network layer's hooks there still apply. Another platform defines the same symbols (_plat_<name>). */
#ifndef PLAT_H
#define PLAT_H

/* ---- sound: a device, sound buffers of PCM samples (the description and format as DirectSound's DSBUFFERDESC /
   WAVEFORMATEX), each played, its volume and pan set; 0 = success, as the original tests them */
#ifdef AXIS_PORTABLE
long plat_soundCreate(void **device);
long plat_soundSetWindow(void *device, void *window);
long plat_soundCreateBuffer(void *device, void *desc, void **buffer);
long plat_soundDuplicate(void *device, void *buffer, void **copy);
u32 plat_soundRelease(void *object);
long plat_soundSetFormat(void *buffer, void *format);
long plat_soundPlay(void *buffer, u32 flags);
long plat_soundSetVolume(void *buffer, int volume);
long plat_soundSetPan(void *buffer, int pan);
long plat_soundLock(void *buffer, u32 size, void **data, u32 *bytes);
long plat_soundUnlock(void *buffer, void *data, u32 bytes);
#define SND_CREATE(device) plat_soundCreate(device)
#define SND_SET_WINDOW(ds, window) plat_soundSetWindow(ds, window)
#define SND_CREATE_BUFFER(ds, desc, buffer) plat_soundCreateBuffer(ds, desc, buffer)
#define SND_DUPLICATE(ds, buffer, copy) plat_soundDuplicate(ds, buffer, copy)
#define SND_RELEASE(object) plat_soundRelease(object)
#define SND_SET_FORMAT(b, format) plat_soundSetFormat(b, format)
#define SND_PLAY(b, flags) plat_soundPlay(b, flags)
#define SND_SET_VOLUME(b, volume) plat_soundSetVolume(b, volume)
#define SND_SET_PAN(b, pan) plat_soundSetPan(b, pan)
#define SND_LOCK(b, size, data, bytes) plat_soundLock(b, size, data, bytes)
#define SND_UNLOCK(b, data, bytes) plat_soundUnlock(b, data, bytes)
#else
#define SND_CREATE(device) DirectSoundCreate(NULL, device, NULL)
#define SND_SET_WINDOW(ds, window) COM(ds, 0x18, int, void *, u32)(ds, window, 2)   /* SetCooperativeLevel(DSSCL_PRIORITY) */
#define SND_CREATE_BUFFER(ds, desc, buffer) COM(ds, 0x0c, long, void *, void **, void *)(ds, desc, buffer, NULL)
#define SND_DUPLICATE(ds, buffer, copy) COM(ds, 0x14, long, void *, void **)(ds, buffer, copy)
#define SND_RELEASE(object) COM(object, COM_RELEASE, u32)(object)
#define SND_SET_FORMAT(b, format) COM(b, 0x38, int, void *)(b, format)
#define SND_PLAY(b, flags) COM(b, 0x30, long, u32, u32, u32)(b, 0, 0, flags)   /* (flags 1: looping) */
#define SND_SET_VOLUME(b, volume) COM(b, 0x3c, long, int)(b, volume)
#define SND_SET_PAN(b, pan) COM(b, 0x40, u32, u32)(b, (u32)(pan))
#define SND_LOCK(b, size, data, bytes) COM(b, 0x2c, long, u32, u32, void **, u32 *, void **, u32 *, u32)(b, 0, size, data, bytes, NULL, NULL, 0)
#define SND_UNLOCK(b, data, bytes) COM(b, 0x4c, long, void *, u32, void *, u32)(b, data, bytes, NULL, 0)
#endif

/* ---- music: a stream playing a file (the original: DirectShow's multimedia stream); its time and duration in 100 ns
   units, 64 bits as two words */
#ifdef AXIS_PORTABLE
long plat_musicCreate(void **stream);
long plat_musicInit(void *stream);
long plat_musicAddAudio(void *stream);
long plat_musicOpen(void *stream, const void *wideName);
u32 plat_musicSetState(void *stream, u32 state);
long plat_musicDuration(void *stream, void *time);
u32 plat_musicTime(void *stream, u32 *time);
u32 plat_musicSeek(void *stream, u32 low, u32 high);
long plat_musicRelease(void *stream);
#define MUS_CREATE(stream) plat_musicCreate(stream)
#define MUS_INIT(s) plat_musicInit(s)
#define MUS_ADD_AUDIO(s) plat_musicAddAudio(s)
#define MUS_OPEN(s, wideName) plat_musicOpen(s, wideName)
#define MUS_SET_STATE(s, state) plat_musicSetState(s, state)
#define MUS_DURATION(s, time) plat_musicDuration(s, time)
#define MUS_TIME(s, time) plat_musicTime(s, time)
#define MUS_SEEK(s, low, high) plat_musicSeek(s, low, high)
#define MUS_RELEASE(s) plat_musicRelease(s)
#else
#define MUS_CREATE(stream) CoCreateInstance((const void *)OBJ(k_CLSID_AMMultiMediaStream), NULL, 1, \
	(const void *)OBJ(k_IID_IAMMultiMediaStream), stream)
#define MUS_INIT(s) COM(s, 0x30, long, u32, u32, void *)(s, 0, 1, NULL)   /* Initialize(read, no graph thread) */
#define MUS_ADD_AUDIO(s) COM(s, 0x3c, long, void *, const void *, u32, void *)(s, NULL, (const void *)OBJ(k_MSPID_PrimaryAudio), 1, NULL)
#define MUS_OPEN(s, wideName) COM(s, 0x40, long, const void *, u32)(s, wideName, 0)
#define MUS_SET_STATE(s, state) COM(s, 0x1c, u32, u32)(s, state)   /* (1: run) */
#define MUS_DURATION(s, time) COM(s, 0x24, long, void *)(s, time)
#define MUS_TIME(s, time) COM(s, 0x20, u32, u32 *)(s, time)
#define MUS_SEEK(s, low, high) COM(s, 0x28, u32, u32, u32)(s, low, high)
#define MUS_RELEASE(s) COM(s, COM_RELEASE, long)(s)
#endif


/* ---- input: the keyboard and mouse as devices read whole each frame (the original: DirectInput 7) - a key state of
   256 bytes (DIK codes, bit 7 held), a mouse state of 16 bytes (movement x, y, wheel, 4 buttons); results below 0
   are failures, 0x8007001e "input lost" (taken again then) */
#ifdef AXIS_PORTABLE
long plat_inputCreate(void *instance, void **input);
long plat_inputCreateKeyboard(void *input, void **keyboard);
long plat_inputCreateMouse(void *input, void **mouse);
long plat_inputSetKeyboardFormat(void *keyboard);
long plat_inputSetMouseFormat(void *mouse);
long plat_inputSetWindow(void *device, void *window, u32 mode);
long plat_inputAcquire(void *device);
long plat_inputUnacquire(void *device);
long plat_inputRead(void *device, u32 size, void *state);
long plat_inputRelease(void *object);
#define IN_CREATE(instance, input) plat_inputCreate(instance, input)
#define IN_CREATE_KEYBOARD(di, keyboard) plat_inputCreateKeyboard(di, keyboard)
#define IN_CREATE_MOUSE(di, mouse) plat_inputCreateMouse(di, mouse)
#define IN_SET_KEYBOARD_FORMAT(k) plat_inputSetKeyboardFormat(k)
#define IN_SET_MOUSE_FORMAT(m) plat_inputSetMouseFormat(m)
#define IN_SET_WINDOW(d, window, mode) plat_inputSetWindow(d, window, mode)
#define IN_ACQUIRE(d) plat_inputAcquire(d)
#define IN_UNACQUIRE(d) plat_inputUnacquire(d)
#define IN_READ(d, size, state) plat_inputRead(d, size, state)
#define IN_RELEASE(object) plat_inputRelease(object)
#else
#define IN_CREATE(instance, input) DirectInputCreateA(instance, 0x700, input, NULL)
#define IN_CREATE_KEYBOARD(di, keyboard) COM(di, 0x0c, int, const void *, void **, void *)(di, (const void *)OBJ(k_GUID_SysKeyboard), keyboard, NULL)
#define IN_CREATE_MOUSE(di, mouse) COM(di, 0x0c, int, const void *, void **, void *)(di, (const void *)OBJ(k_GUID_SysMouse), mouse, NULL)
#define IN_SET_KEYBOARD_FORMAT(k) COM(k, 0x2c, int, const void *)(k, (const void *)OBJ(k_c_dfDIKeyboard))
#define IN_SET_MOUSE_FORMAT(m) COM(m, 0x2c, int, const void *)(m, (const void *)OBJ(k_c_dfDIMouse))
#define IN_SET_WINDOW(d, window, mode) COM(d, 0x34, int, void *, u32)(d, window, mode)   /* (5 exclusive, 6 non-exclusive; foreground) */
#define IN_ACQUIRE(d) COM(d, 0x1c, long)(d)
#define IN_UNACQUIRE(d) COM(d, 0x20, long)(d)
#define IN_READ(d, size, state) COM(d, 0x24, long, u32, void *)(d, size, state)
#define IN_RELEASE(object) COM(object, COM_RELEASE, long)(object)
#endif


/* ---- time: the high-resolution counter and its frequency (the game clock, timer.c), milliseconds (timeGetTime: the
   clock check; GetTickCount: the network's waits), sleeping, and the date and time (SYSTEMTIME's eight 16-bit
   fields: year, month, weekday, day, hour, minute, second, milliseconds - local, or UTC) */
#ifdef AXIS_PORTABLE
int plat_timeCounter(void *count);       /* 64-bit count; nonzero = success */
int plat_timeFrequency(void *frequency); /* 64-bit counts per second; nonzero = success */
u32 plat_timeMs(void);
u32 plat_timeTicks(void);
void plat_sleep(u32 ms);
void plat_timeLocal(void *systemTime);
void plat_timeUTC(void *systemTime);
#define TIME_COUNTER(count) plat_timeCounter(count)
#define TIME_FREQUENCY(frequency) plat_timeFrequency(frequency)
#define TIME_MS() plat_timeMs()
#define TIME_TICKS() plat_timeTicks()
#define TIME_SLEEP(ms) plat_sleep(ms)
#define TIME_LOCAL(st) plat_timeLocal(st)
#define TIME_UTC(st) plat_timeUTC(st)
#else
#define TIME_COUNTER(count) IMPORT_FN(QueryPerformanceCounter, int, void *)(count)
#define TIME_FREQUENCY(frequency) IMPORT_FN(QueryPerformanceFrequency, int, void *)(frequency)
#define TIME_MS() IMPORT_FN(timeGetTime, u32, void)()
#define TIME_TICKS() IMPORT_FN(GetTickCount, u32, void)()
#define TIME_SLEEP(ms) IMPORT_FN(Sleep, void, u32)(ms)
#define TIME_LOCAL(st) IMPORT_FN(GetLocalTime, void, void *)(st)
#define TIME_UTC(st) IMPORT_FN(GetSystemTime, void, void *)(st)
#endif


/* ---- the game's window's messages delivered each frame when a host runs it without a window (standalone/host_window.c) */
#ifdef AXIS_PORTABLE
extern void (*g_platPump)(void);
#define PLAT_PUMP() do { if (g_platPump) g_platPump(); } while (0)
#else
#define PLAT_PUMP() ((void)0)
#endif


/* ---- a check (AXIS_LOADLOG, standalone/portable.c): each loading-screen frame's timer, logged */
#ifdef AXIS_PORTABLE
extern void (*g_platLoadLog)(const void *timeSync, int mode);
#define PLAT_LOADLOG(timeSync, mode) do { if (g_platLoadLog) g_platLoadLog(timeSync, mode); } while (0)
#else
#define PLAT_LOADLOG(timeSync, mode) ((void)0)
#endif


/* ---- network: DirectPlay-shaped sessions (the original: DirectPlay 4 and its lobby, which the network layer,
   axisnet, serves); a later port may replace the whole with its own netcode (no crossplay, PORTING.md) */
#ifdef AXIS_PORTABLE
long plat_netCreate(void **out);
#define NET_CREATE(out) plat_netCreate(out)
long plat_netLobbyCreate(void **out);
#define NET_LOBBY_CREATE(out) plat_netLobbyCreate(out)
long plat_netRelease(void *o);
#define NET_RELEASE(o) plat_netRelease(o)
long plat_netClose(void *p);
#define NET_CLOSE(p) plat_netClose(p)
u32 plat_netDestroyPlayer(void *p, u32 id);
#define NET_DESTROY_PLAYER(p, id) plat_netDestroyPlayer(p, id)
int plat_netEnumSessions(void *p, void *desc, void *callback);
#define NET_ENUM_SESSIONS(p, desc, callback) plat_netEnumSessions(p, desc, callback)
int plat_netGetPlayerName(void *p, u32 id, void *name, u32 *size);
#define NET_GET_PLAYER_NAME(p, id, name, size) plat_netGetPlayerName(p, id, name, size)
int plat_netCreatePlayer(void *p, u32 *id, void *name);
#define NET_CREATE_PLAYER(p, id, name) plat_netCreatePlayer(p, id, name)
int plat_netOpen(void *p, void *desc, u32 flags);
#define NET_OPEN(p, desc, flags) plat_netOpen(p, desc, flags)
int plat_netLobbyGetConnection(void *l, void *buffer, u32 *size);
#define NET_LOBBY_GET_CONNECTION(l, buffer, size) plat_netLobbyGetConnection(l, buffer, size)
int plat_netLobbySetConnection(void *l, void *connection);
#define NET_LOBBY_SET_CONNECTION(l, connection) plat_netLobbySetConnection(l, connection)
int plat_netLobbyConnect(void *l, void **out);
#define NET_LOBBY_CONNECT(l, out) plat_netLobbyConnect(l, out)
int plat_netEnumConnections(void *p, void *callback);
#define NET_ENUM_CONNECTIONS(p, callback) plat_netEnumConnections(p, callback)
int plat_netLobbyAddress(void *l, void *elements, u32 n, void *block, u32 *size);
#define NET_LOBBY_ADDRESS(l, elements, n, block, size) plat_netLobbyAddress(l, elements, n, block, size)
int plat_netInitConnection(void *p, void *connection);
#define NET_INIT_CONNECTION(p, connection) plat_netInitConnection(p, connection)
int plat_netGetCaps(void *p, u32 *caps);
#define NET_GET_CAPS(p, caps) plat_netGetCaps(p, caps)
long plat_netReceive(void *p, u32 *from, u32 *to, u32 flags, void *data, u32 *size);
#define NET_RECEIVE(p, from, to, flags, data, size) plat_netReceive(p, from, to, flags, data, size)
long plat_netSend(void *p, u32 from, u32 to, u32 flags, const void *data, u32 size);
#define NET_SEND(p, from, to, flags, data, size) plat_netSend(p, from, to, flags, data, size)
#else
#define NET_CREATE(out) CoCreateInstance((const void *)OBJ(k_CLSID_DirectPlay), NULL, 1, (const void *)OBJ(k_IID_IDirectPlay4A), out)
#define NET_LOBBY_CREATE(out) CoCreateInstance((const void *)OBJ(k_CLSID_DirectPlayLobby), NULL, 1, (const void *)OBJ(k_IID_IDirectPlayLobby3A), out)
#define NET_RELEASE(o) COM(o, COM_RELEASE, long)(o)
#define NET_CLOSE(p) COM(p, 0x10, long)(p)
#define NET_DESTROY_PLAYER(p, id) COM(p, 0x24, u32, u32)(p, id)
#define NET_ENUM_SESSIONS(p, desc, callback) COM(p, 0x34, int, void *, u32, void *, void *, u32)(p, desc, 0, callback, NULL, 0x12)
#define NET_GET_PLAYER_NAME(p, id, name, size) COM(p, 0x54, int, u32, void *, u32 *)(p, id, name, size)
#define NET_CREATE_PLAYER(p, id, name) COM(p, 0x18, int, u32 *, void *, void *, void *, u32, u32)(p, id, name, NULL, NULL, 0, 0)
#define NET_OPEN(p, desc, flags) COM(p, 0x60, int, void *, u32)(p, desc, flags)
#define NET_LOBBY_GET_CONNECTION(l, buffer, size) COM(l, 0x20, int, u32, void *, u32 *)(l, 0, buffer, size)
#define NET_LOBBY_SET_CONNECTION(l, connection) COM(l, 0x30, int, u32, u32, void *)(l, 0, 0, connection)
#define NET_LOBBY_CONNECT(l, out) COM(l, 0x3c, int, u32, const void *, void **, void *)(l, 0, (const void *)OBJ(k_IID_IDirectPlay4A), out, NULL)
#define NET_ENUM_CONNECTIONS(p, callback) COM(p, 0x8c, int, const void *, void *, void *, u32)(p, (const void *)OBJ(k_axisAppGuid), callback, NULL, 0)
#define NET_LOBBY_ADDRESS(l, elements, n, block, size) COM(l, 0x38, int, void *, u32, void *, u32 *)(l, elements, n, block, size)
#define NET_INIT_CONNECTION(p, connection) COM(p, 0x98, int, void *, u32)(p, connection, 0)
#define NET_GET_CAPS(p, caps) COM(p, 0x38, int, u32 *, u32)(p, caps, 0)
#define NET_RECEIVE(p, from, to, flags, data, size) COM(p, 0x64, long, u32 *, u32 *, u32, void *, u32 *)(p, from, to, flags, data, size)
#define NET_SEND(p, from, to, flags, data, size) COM(p, 0x68, long, u32, u32, u32, const void *, u32)(p, from, to, flags, data, size)
#endif

#endif
