/* winsock.h: the game's Winsock imports (wsock32, by ordinal) - their import-table slots, called as
   IMPORT(WS_x, ret, args...)(...) with each call site's own types */
#pragma once
#define WS_INET_ADDR 0x4a9370        /* ordinal 11 inet_addr */
#define WS_HTONS 0x4a9374            /* ordinal 9 htons */
#define WS_STARTUP 0x4a9378          /* ordinal 115 WSAStartup */
#define WS_SOCKET 0x4a937c           /* ordinal 23 socket */
#define WS_SET_LAST_ERROR 0x4a9380   /* ordinal 112 WSASetLastError */
#define WS_BIND 0x4a9384             /* ordinal 2 bind */
#define WS_ASYNC_SELECT 0x4a9388     /* ordinal 101 WSAAsyncSelect */
#define WS_SHUTDOWN 0x4a938c         /* ordinal 22 shutdown */
#define WS_CLOSESOCKET 0x4a9390      /* ordinal 3 closesocket */
#define WS_SEND 0x4a9394             /* ordinal 19 send */
#define WS_RECV 0x4a9398             /* ordinal 16 recv */
#define WS_INET_NTOA 0x4a939c        /* ordinal 12 inet_ntoa */
#define WS_GETHOSTNAME 0x4a93a0      /* ordinal 57 gethostname */
#define WS_CONNECT 0x4a93a4          /* ordinal 4 connect */
#define WS_GETHOSTBYNAME 0x4a93a8    /* ordinal 52 gethostbyname */
#define WS_CLEANUP 0x4a93ac          /* ordinal 116 WSACleanup */
