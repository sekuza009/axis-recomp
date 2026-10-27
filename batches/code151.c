/* batch 150 (lifted/grp96.c): the network receive thread */
#include "lifted/grp96.c"
/* 0x454560 net_454560(): the receive thread's procedure: wait on the two events (0xa0bb10 data, 0xa0bf1c stop):
   data handles the incoming packets (net_4545b0) and waits again, stop ends the thread (ExitThread 0), anything
   else waits again */
LIFT_PLAIN(net_454560, 454560)
