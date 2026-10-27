/* batch 98 (lifted/grp44.c) */
#include "lifted/grp44.c"
/* 0x4546d0 net_startThread(): the network worker: two events (0xa0bb10 / 0xa0bf1c) and a thread running net_454560
   (handle 0xa0d788, id 0xa0d784), the first event set; 0 if any of them cannot be made */
LIFT_PLAIN(net_startThread, 4546d0)
/* 0x452a30 net_452a30 / 0x452bd0 net_452bd0(): read one 0x5b-byte (lobby, socket 0xa055f8, into 0xa05260) / 0x79-byte
   (game server, socket 0xa05630, into 0xa0b280) reply, waiting up to 3 s; by its type (0xa052aa / 0xa0b2e8): 0 handle
   it (net_452af0 / net_452c80), 1 start the network thread, others set the connection state (0xa0b36c / 0xa0b34c) */
LIFT_PLAIN(net_452a30, 452a30)
LIFT_PLAIN(net_452bd0, 452bd0)
/* 0x451b80 net_connect(mode): close everything (net_closeAll), then 100: the lobby socket (0xa055f8), 0x65: the
   game-server socket (0xa05630): Winsock 2.2, a TCP socket bound to any address, connected to the host 0xa055e4 (a
   dotted address, else resolved by name) at port 0xa05326. 1 connected (+ 0xa0b380 = 200 for the lobby), 2 refused
   (10061), 0 any failure (Winsock cleaned up, net_disconnect); other modes just 1 */
LIFT_PLAIN(net_connect, 451b80)
/* 0x4060f0 lobby_openConnection(): unless already connected (0x4db718): disconnect, net_connect(100) and
   net_asyncSelect on the main window (messages 0x3d / 0x46 / 0x3e via FUN_0041ee40 and 0 on failure); then the lobby
   screen's state variables are reset; 1 */
LIFT_PLAIN(lobby_openConnection, 4060f0)
