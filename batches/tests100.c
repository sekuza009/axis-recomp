/* batch 99 */
/* every state of the machine (and some others) with the network mocks; the answers already in the buffers (recv may
   overwrite them, or return nothing so they stay): small status values, both reply buffers as netreply_setup's */
static void netrecv_setup(void)
{
	static const int states[] = { 10, 0xd, 0xe, 0xf, 0x12, 0x13, 0x15, 0x1a, 0x1d, 0, 7 };
	netreply_setup(0xa05260, 0x5b, 0xa052aa);
	fill((void *)0xa0b280, 0x79); G32(0xa0b2e8) = irnd(0, 4);
	for (int k = 15; k < 0x79; k += 16) ((BYTE *)0xa0b280)[k] = 0;
	G32(0xa055f8) = irnd(1, 99); G32(0xa05630) = irnd(1, 99);
	G32(0xa055dc) = irnd(0, 4); G32(0xa0b248) = irnd(0, 4);
	fill((void *)0xa05638, 0x10b); *(BYTE *)0xa05638 = (BYTE)(irnd(0, 2) ? 0x1e + irnd(0, 12) : irnd(0, 255));
	fill((void *)0xa052c0, 0x22); if (irnd(0, 1)) *(BYTE *)0xa052c0 = 0;
	fill((void *)0xa052e8, 0x40); fill((void *)0xa05330, 0x9b * 4 + 8);
	fill((void *)0xa0b350, 8); fill((void *)0xa0b370, 0x10);
	G32(0xa0b300) = states[irnd(0, 10)];
}
ST(net_recv, netrecv_setup();, (CD(void, 0x452620, void)(), 0), (net_recv(0, 0, 0, 0, 0, 0, 0), 0))
