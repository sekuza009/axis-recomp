/* objects.h: the game's arrays, buffers and records by name (tools/name_objects.py): each the original address in
   the harness, its place in AxisRC.exe (IMG; in AxisRC.exe a member of g_rdata / g_data, src/data/layout.h).
   OBJ(name) is its address as a number (src/axis.h). Element type, count: the extent known (see the note) */
#pragma once
#define g_chatLine ((char *)IMG(0x9dc92c))   /* char[1024]; the chat line being typed (memset 0x400) */
#define g_joinedTitleName ((char *)IMG(0x9dd570))   /* char[30]; the joined game's title record: the name (laid out as 0x4de700) */
#define g_titleName ((char *)IMG(0x4de700))   /* char[30]; the title record's name (+0x1e the level: g_titleLevel) */
#define g_accountName ((char *)IMG(0x9dd1d8))   /* char[30]; the login form's name (30 bytes) */
#define g_accountPassword ((char *)IMG(0x9dd1f6))   /* char[12]; (12 bytes) */
#define g_accountPasswordRepeat ((char *)IMG(0x9dd202))   /* char[12]; (12 bytes) */
#define g_accountEmail ((char *)IMG(0x9dd20e))   /* char[40]; (40 bytes) */
#define g_playerName ((char *)IMG(0x4ded20))   /* char[32]; the arena player's record: the name (32 bytes) */
#define g_cfgPlayerName ((char *)IMG(0x4dedb0))   /* char[32]; axis.cfg's player name (default "PLAYER") */
#define g_roomRecName ((char *)IMG(0x5b1b30))   /* char[32]; the room record's name (fields from +0x20: g_roomRec*) */
#define g_roomSettingsName ((char *)IMG(0x4df9c8))   /* char[32]; the room's settings record (GameSettings): its name */
#define g_newArenaName ((char *)IMG(0x4db528))   /* char[32]; the new arena's settings record: its name */
#define g_mapTitle ((char *)IMG(0x67fb44))   /* char[32]; the map's title (TITLE: %s) */
#define g_profileName ((char *)IMG(0x9f8fe8))   /* char[32]; the profile's name (written 0x20 bytes) */
#define g_arenaName ((char *)IMG(0x4db560))   /* char[32]; (0x20 bytes) */
#define g_localAddress ((char *)IMG(0xa0b43c))   /* char[16]; the local IP address text (memset 16) */
#define g_dataDir ((char *)IMG(0x9dae7c))   /* char[1]; the data folder's path (extent unknown) */
#define g_savedColourChoices ((u8 *)IMG(0x4dcfe0))   /* u8[144]; the ARM CENTER's colour choices kept (memcpy 0x90) */
#define g_textColour ((Colour *)IMG(0x76d438))   /* Colour[1]; the menus' text colour */
#define g_rectColour ((Colour *)IMG(0x9da480))   /* Colour[1]; the rectangles' colour */
#define g_roomBright ((u32 *)IMG(0x9dcec0))   /* u32[4]; the room's bright colour (r g b a) */
#define g_roomDim ((u32 *)IMG(0x9dd338))   /* u32[4]; the room's dim colour */
#define g_profileColour ((u32 *)IMG(0x9f8eb0))   /* u32[4] */
#define g_vecZero2 ((float *)IMG(0xa0e7b8))   /* float[3]; a zero vector (vec_initZero) */
#define g_vecUnitY ((float *)IMG(0xa0e7d8))   /* float[3]; (0 1 0: vec_initUp) */
#define g_vecUnitX ((float *)IMG(0xa0e7f8))   /* float[3]; (1 0 0: vec_initAxisX) */
#define g_logTexture ((u32 *)IMG(0xa0dff8))   /* u32[2]; vtable + class name */
#define g_logTextureManager ((u32 *)IMG(0xa0e000))   /* u32[2]; vtable + class name */
#define g_logSound ((u32 *)IMG(0xa0e020))   /* u32[2]; vtable + class name */
#define g_logConsole ((u32 *)IMG(0xa0e778))   /* u32[2]; vtable + class name */
#define g_logShapeManager ((u32 *)IMG(0xa0e788))   /* u32[2]; vtable + class name */
#define g_logShape ((u32 *)IMG(0xa0e790))   /* u32[2]; vtable + class name */
#define g_logSkeletonManager ((u32 *)IMG(0xa0eaa0))   /* u32[2]; vtable + class name */
#define g_logSkeleton ((u32 *)IMG(0xa0eaa8))   /* u32[2]; vtable + class name */
#define g_logBMPRGBFile ((u32 *)IMG(0xa1f0f0))   /* u32[2]; vtable + class name */
#define g_logPackedColor ((u32 *)IMG(0xa1f250))   /* u32[2]; vtable + class name */
#define g_logRealColor ((u32 *)IMG(0xa1f290))   /* u32[2]; vtable + class name */
#define g_logUnit ((u32 *)IMG(0xae2e98))   /* u32[2]; vtable + class name */
#define g_logUnitPartInfo ((u32 *)IMG(0xae2ea0))   /* u32[2]; vtable + class name */
#define g_logUnitPoseInfo ((u32 *)IMG(0xae2ea8))   /* u32[2]; vtable + class name */
#define g_logStage ((u32 *)IMG(0xae2eb8))   /* u32[2]; vtable + class name */
#define g_logCollisionVolume ((u32 *)IMG(0xae2ed0))   /* u32[2]; vtable + class name */
#define g_logLight ((u32 *)IMG(0xae2ee8))   /* u32[2]; vtable + class name */
#define g_logViewVolume ((u32 *)IMG(0xae2ef0))   /* u32[2]; vtable + class name */
#define g_logTimeSync ((u32 *)IMG(0xae2f00))   /* u32[2]; vtable + class name */
#define g_logScene ((u32 *)IMG(0xae3328))   /* u32[2]; vtable + class name */
#define k_m40f ((float *)IMG(0x4a9400))   /* float[1]; -40 */
#define k_0_005f ((float *)IMG(0x4a9404))   /* float[1]; 0.005 */
#define k_0_4f ((float *)IMG(0x4a9408))   /* float[1]; 0.4 */
#define k_30f ((float *)IMG(0x4a940c))   /* float[1]; 30 */
#define k_12f ((float *)IMG(0x4a9410))   /* float[1]; 12 */
#define k_40f ((float *)IMG(0x4a9414))   /* float[1]; 40 */
#define k_0_003f ((float *)IMG(0x4a9430))   /* float[1]; 0.003 */
#define k_0_0667f ((float *)IMG(0x4a9434))   /* float[1]; 0.0667 */
#define k_0_333333f ((float *)IMG(0x4a9438))   /* float[1]; 0.333333 */
#define k_0_015f ((float *)IMG(0x4a943c))   /* float[1]; 0.015 */
#define k_0_05f ((float *)IMG(0x4a9468))   /* float[1]; 0.05 */
#define k_0_15625f ((float *)IMG(0x4a9478))   /* float[1]; 0.15625 */
#define k_600f ((float *)IMG(0x4a94ac))   /* float[1]; 600 */
#define k_0_036f ((float *)IMG(0x4a94b8))   /* float[1]; 0.036 */
#define k_1000f ((float *)IMG(0x4a94bc))   /* float[1]; 1000 */
#define k_8f ((float *)IMG(0x4a94cc))   /* float[1]; 8 */
#define k_m0_390625f ((float *)IMG(0x4a94f0))   /* float[1]; -0.390625 */
#define k_0_3f ((float *)IMG(0x4a94fc))   /* float[1]; 0.3 */
#define k_m2_56f ((float *)IMG(0x4a9500))   /* float[1]; -2.56 */
#define k_0_01f_4a9504 ((float *)IMG(0x4a9504))   /* float[1]; 0.01 */
#define k_0_035f ((float *)IMG(0x4a950c))   /* float[1]; 0.035 */
#define k_48f ((float *)IMG(0x4a9514))   /* float[1]; 48 */
#define k_64f ((float *)IMG(0x4a9518))   /* float[1]; 64 */
#define k_0_00208333f ((float *)IMG(0x4a9574))   /* float[1]; 0.00208333 */
#define k_0_0015625f ((float *)IMG(0x4a9578))   /* float[1]; 0.0015625 */
#define k_0_875f ((float *)IMG(0x4a9588))   /* float[1]; 0.875 */
#define k_0_0625f ((float *)IMG(0x4a958c))   /* float[1]; 0.0625 */
#define k_0_09375f ((float *)IMG(0x4a9590))   /* float[1]; 0.09375 */
#define k_1100f ((float *)IMG(0x4a95c4))   /* float[1]; 1100 */
#define k_85f ((float *)IMG(0x4a95e8))   /* float[1]; 85 */
#define k_86f ((float *)IMG(0x4a95ec))   /* float[1]; 86 */
#define k_m0_9f ((float *)IMG(0x4a95f0))   /* float[1]; -0.9 */
#define k_255f ((float *)IMG(0x4a9744))   /* float[1]; 255 */
#define k_1_5f ((float *)IMG(0x4a974c))   /* float[1]; 1.5 */
#define k_0_0555556f ((float *)IMG(0x4aa26c))   /* float[1]; 0.0555556 */
#define k_57_2958f ((float *)IMG(0x4aa270))   /* float[1]; 57.2958 */
#define k_28f ((float *)IMG(0x4aa280))   /* float[1]; 28 */
#define k_0_000277778f ((float *)IMG(0x4aa284))   /* float[1]; 0.000277778 */
#define k_0_00392157f ((float *)IMG(0x4aa2a4))   /* float[1]; 0.00392157 */
#define k_2500f ((float *)IMG(0x4aa410))   /* float[1]; 2500 */
#define k_0_02f ((float *)IMG(0x4aa480))   /* float[1]; 0.02 */
#define k_750f ((float *)IMG(0x4aa484))   /* float[1]; 750 */
#define k_0_6f ((float *)IMG(0x4aa488))   /* float[1]; 0.6 */
#define k_0_0711111f ((float *)IMG(0x4aa49c))   /* float[1]; 0.0711111 */
#define k_m1_5f ((float *)IMG(0x4aa500))   /* float[1]; -1.5 */
#define g_tan10Table ((float *)IMG(0xa106b0))   /* float[18]; to the random table (0x48 bytes) */
#define g_randTable ((int *)IMG(0xa106f8))   /* int[4096]; to the tan table (0x4000 bytes) */
#define g_tanTable ((float *)IMG(0xa146f8))   /* float[3600]; by tenths of a degree (to the cos table) */
#define g_cosTable ((float *)IMG(0xa17f38))   /* float[3600]; (to the sin table) */
#define g_sinTable ((float *)IMG(0xa1b778))   /* float[3600] */
#define g_netSlots ((u8 *)IMG(0x9f9840))   /* u8[16640]; 16 network slots of 0x410 bytes (net_clearSlots runs to 0x9fd940); overlapped by g_profileRecords' 103 records at start-up */
#define g_netPlayerList ((u8 *)IMG(0xa05330))   /* u8[682]; (net_clearPlayerList) */
#define g_keySeen ((int *)IMG(0x4d1a98))   /* int[256]; a key's press seen until released (0x400 bytes) */
#define g_briefingText ((char *)IMG(0x9f1064))   /* char[1600]; the briefing's text (memset 0x640) */
#define g_roomMech ((u8 *)IMG(0x9dd5f8))   /* u8[11]; the room's copy of the mech bytes (11) */
#define g_roomColours ((float *)IMG(0x9dd603))   /* float[36]; the room's copy of the colour choices (0x90 bytes) */
#define g_armcColours ((float *)IMG(0x4dc4b8))   /* float[36]; the ARM CENTER's colour choices (0x90 bytes: six values per slot) */
#define g_accountOldPassword ((char *)IMG(0x9dd6d8))   /* char[12]; (12 bytes) */
#define g_packedWhite ((u8 *)IMG(0xa1f23c))   /* u8[4]; a packed colour (ff ff ff ff: colour_initPackedWhite) */
#define g_serverAddress ((char *)IMG(0xa0d320))   /* char[100]; the server's address text (100 bytes) */
#define g_clockLastTime ((u16 *)IMG(0x9dd878))   /* u16[8]; a SYSTEMTIME (sys_checkClockTampering) */
#define g_clockNowTime ((u16 *)IMG(0x9dd8d0))   /* u16[8]; a SYSTEMTIME */
#define g_arenaBright ((u32 *)IMG(0x4dba98))   /* u32[4]; the arena lobby's bright colour */
#define g_arenaDim ((u32 *)IMG(0x4db8a0))   /* u32[4]; the arena lobby's dim colour */
#define g_profileDim ((u32 *)IMG(0x9f8d58))   /* u32[4]; the profile screen's dim colour */
#define g_mapNames ((char *)IMG(0x907b30))   /* char[32]; 0x20 bytes a map (extent unknown: the first) */
#define g_profileList ((char *)IMG(0x9f684c))   /* char[72]; 0x48 bytes a profile (extent unknown: the first) */
#define g_gameList ((u8 *)IMG(0x9087c4))   /* u8[74]; 0x4a bytes a game (extent unknown: the first) */
#define g_profileRecords ((u8 *)IMG(0x9f9040))   /* u8[76]: 0x4c bytes a record; the stats check reads 103 records (to 0x9fafb4), so the table overlaps g_netSlots (the original's aliasing) */
#define g_messages ((char *)IMG(0x74de24))   /* char[128256]; the message table: 0x80 bytes a line from msgeng.dat (data_loadMessages) */
#define g_ptxPixels ((u8 *)IMG(0xa21708))   /* u8[262144]; the image decoder's output (RGB(A) */
#define g_ptxData ((u8 *)IMG(0xaa2e98))   /* u8[262144]; the image decoder's input */
#define g_roomList ((u8 *)IMG(0x9fd960))   /* u8[7744]; the server's room list (net_clearRoomList: 0x1e40 bytes) */
#define g_missions ((u8 *)IMG(0x9ef2d0))   /* u8[7560]; the 30 missions of axis.mis: 0xfc bytes each (mission_clear runs to 0x9f109c) */
#define g_serverNames ((u32 *)IMG(0xa0bf20))   /* u32[1280]; 256 server names of 0x14 bytes */
#define g_ptxCbGreen ((int *)IMG(0xa6170c))   /* int[256]; YCbCr -> RGB: Cb's part of green (ptx_initColourTables: 256 entries) */
#define g_ptxCrRed ((int *)IMG(0xaa228c))   /* int[256]; Cr's part of red */
#define g_ptxCbBlue ((int *)IMG(0xa1f304))   /* int[256]; Cb's part of blue */
#define g_ptxCrGreen ((int *)IMG(0xaa2690))   /* int[256]; Cr's part of green */
#define g_ptxYCbCrTables ((int *)IMG(0xa1f704))   /* int[2048]; RGB -> YCbCr: eight tables of 256 (ptx_initYCbCrTables) */
#define g_ptxClampTable ((u8 *)IMG(0xa61b0c))   /* u8[1408]; the clamp table: 0x100 zeros */
#define g_ptxPlanes ((u8 *)IMG(0xa6228c))   /* u8[262144]; the decoded planes: 64 KB each */
#define g_ptxDequant ((float *)IMG(0xaa2a90))   /* float[128]; the two 64-entry dequantisation tables */
#define g_ptxQuant ((int *)IMG(0xaa2c94))   /* int[128]; the two 64-entry quantisation tables */
#define g_fileList ((u8 *)IMG(0x9dda88))   /* u8[69632]; 1024 entries of 0x44 bytes: the file dialog's names (the reset runs 0x9ddac8 .. 0x9eeac8) */
#define g_introTextures ((int *)IMG(0x9dad6c))   /* int[8]; the intro frames (m_intro1 .. 4 */
#define g_mainMenuTextures ((int *)IMG(0x76d478))   /* int[2]; mainmenu01 / 02 (the main */
#define g_arenaMenuTextures ((int *)IMG(0x4df040))   /* int[2]; arenamenu01 / 02 (the arena lobby's tunnel) */
#define g_ctrlMenuTextures ((int *)IMG(0x5b1978))   /* int[2]; ctrlmenu01 / 02 (the setup tunnel) */
#define g_ladderMenuTextures ((int *)IMG(0x4df904))   /* int[2]; laddermenu01 / 02 (the room's and the ARM CENTER preview's tunnel) */
#define g_spiralTextures ((int *)IMG(0x9da45c))   /* int[6]; the six spirals */
