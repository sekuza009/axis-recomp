/* batch 159 */
/* DirectInput: a fake DirectInput (CreateDevice giving a fake device), DirectInputCreateA giving it or failing,
   each device step succeeding or not, the keyboard and mouse devices there or not, ready or not, the mouse capture
   flag, the key states filled; DirectSound there or not */
static void dinput_setup(void)
{
	FakeCom *di = (FakeCom *)fakecom_new(0, 0x30, g_nargsDinput, 0), *dev = (FakeCom *)fakecom_new(1, 0x31, g_nargsDidev, 0);
	FakeCom *kb = (FakeCom *)fakecom_new(2, 0x32, g_nargsDidev, ds_res()), *ms = (FakeCom *)fakecom_new(3, 0x33, g_nargsDidev, ds_res());
	di->ret[3] = ds_res(); di->outarg[3] = 2; di->val[3] = (DWORD)dev;
	dev->ret[11] = ds_res(); dev->ret[13] = ds_res(); dev->ret[7] = ds_res();
	g_mockDiObj = irnd(0, 4) ? (DWORD)di : 0;
	G32(0x4d1e98) = (int)di;
	G32(0x4d1fa0) = irnd(0, 3) ? (int)kb : 0; G32(0x4d1fa4) = irnd(0, 3) ? (int)ms : 0;
	G32(0x4d1fa8) = irnd(0, 2) ? 0 : 1; G32(0x4d1fac) = irnd(0, 2) ? 0 : 1; G32(0x4ad17c) = irnd(0, 1);
	fill((void *)0x4d1a98, 0x400);
	G32(0xa0e804) = irnd(0, 3) ? (int)fakecom_new(4, 3, g_nargsDsound, 0) : 0;
	g_a[0] = irnd(0, 0xffff); g_a[1] = irnd(0, 0xffff);
}
T_PLAIN(input_initKeyboard, 0x401310, dinput_setup();, 0, g_a[0], 0, 0, 0)
T_PLAIN(input_4013a0, 0x4013a0, dinput_setup();, 0, g_a[0], 0, 0, 0)
T_PLAIN(input_createDirectInput, 0x401410, dinput_setup();, 0, g_a[0], g_a[1], 0, 0)
T_PLAIN(input_reacquireKeyboard, 0x4012c0, dinput_setup();, 0, 0, 0, 0, 0)
T_PLAIN(input_reacquireMouse, 0x4012e0, dinput_setup();, 0, 0, 0, 0, 0)
T_PLAIN(input_releaseKeyboard, 0x401460, dinput_setup();, 0, 0, 0, 0, 0)
T_PLAIN(wnd_401490, 0x401490, dinput_setup();, 0, 0, 0, 0, 0)
T_PLAIN(wnd_467b70, 0x467b70, dinput_setup();, 0, 0, 0, 0, 0)
