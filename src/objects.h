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
#define g_playerName ((char *)IMG(0x4ded20))   /* char[48]; the arena settings record (GameSettings, axis.cfg's server section): the name, then the map .. limits (+0x20: g_arenaMap ..), the clan / password (+0x26), the flag +0x2e */
#define g_cfgPlayerName ((char *)IMG(0x4dedb0))   /* char[32]; axis.cfg's player name (default "PLAYER") */
#define g_roomRecName ((char *)IMG(0x5b1b30))   /* char[48]; the room settings record (GameSettings, the registry's copy): the name, then the six choices (+0x20: g_roomRec*), the password (+0x26) */
#define g_roomSettingsName ((char *)IMG(0x4df9c8))   /* char[48]; the room's settings record (GameSettings, the room's form): the name, then +0x20: g_roomMap .., the password (+0x26) */
#define g_newArenaName ((char *)IMG(0x4db528))   /* char[48]; the new arena's settings record (GameSettings, the create-arena form): the name, then +0x20: g_newArenaMap .., the password (+0x26) */
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
#define g_graphicSettings ((int *)IMG(0x83a9c0))   /* int[7]; the graphics settings in use: video mode, colour depth, polygon detail (HIGH), then axis.cfg's four switches (setup_keys.c copies all 7) */
#define g_cfgSwitches (g_graphicSettings + 3)   /* int[4]; axis.cfg's graphics switches: linear filtering */
#define g_armcParts ((int *)IMG(0x4dc760))   /* int[5]; the mech's chosen parts: head */
#define g_savedMechPartIds ((int *)IMG(0x4dc878))   /* int[5]; the saved mech's parts (match_start's loop of 5) */
#define g_mechSettings ((int *)IMG(0x4dcb18))   /* int[6]; the mech's weapon and item settings (copied into g_savedMechSettings: armc_misc.c) */
#define g_savedMechSettings ((int *)IMG(0x4dcf18))   /* int[6]; the saved mech's weapon and items (menu_records' loop writes items 2 .. 5) */
#define g_slotTextures ((int *)IMG(0x4dcc70))   /* int[6]; ARM CENTER's six slot textures (armc_screens' loop of 6) */
#define g_timerClocks ((u32 *)IMG(0x9db980))   /* u32[4]; the timer's two doubles (now */
#define g_mouseClicked ((int *)IMG(0x4ded88))   /* int[3]; the three mouse buttons' click pulses (0xfa .. 0xfc) */
#define g_mouseButtonsHeld ((int *)IMG(0x4ded94))   /* int[3]; the three mouse buttons held (devices.c's loop of 3) */
#define g_mechPartStats ((int *)IMG(0x4dcab4))   /* int[7]; the mech stats copied from a part (armc_parts' loop of 7) */
#define g_armcTabColour ((u32 *)IMG(0x4dbc58))   /* u32[4]; ARM CENTER's chosen tab colour (armc_misc's loop of 4) */
#define g_legsStats ((float *)IMG(0x4dc228))   /* float[7]; the legs' stats: two values (armc_stats' loop of 2), four speed corrections (g_legsSpeedCorrection + k * 4; three of them bonuses from +0xc), the weight (g_legsWeight) */
#define g_armsStats ((int *)IMG(0x4dc290))   /* int[5]; the arms' stats copied from the part (armc_parts' loop of 5) */
#define g_dpConnections ((int *)IMG(0xa0bae0))   /* int[4]; the DirectPlay connections by kind (net_connectionAvailable: below 4) */
#define g_camPoints ((float *)IMG(0x4df870))   /* float[20]; the menu camera's five target points (x y z */
#define g_camAims ((float *)IMG(0x76d388))   /* float[20]; the menu camera's five look-at points (x y z */
#define g_controls ((int *)IMG(0x4def00))   /* int[68]; axis.cfg's control settings: the key bindings (two slots per action) */
#define g_controlsEdit ((int *)IMG(0x4de0c0))   /* int[68]; setup's edited copy of g_controls (copied in on open */
#define g_mouseSettings (g_controls + 0x40)   /* int[4]; axis.cfg's mouse lines 0x40 .. 0x43: invert, smooth, sensitivity, crosshair */
#define g_setupToggles (g_controlsEdit + 0x40)   /* int[2]; two setup on / off values (setup_pages' loop of 2) */
#define g_menuEye ((float *)IMG(0x4df024))   /* float[3]; the menu camera's position (x: g_menuCameraPos */
#define g_menuLook ((float *)IMG(0x680378))   /* float[3]; the point the menu camera looks at (g_menuCameraLook */
#define g_menuEyeHome ((float *)IMG(0x9db090))   /* float[3]; the menu camera's home position (g_menuCameraX .. Z) */
#define g_menuLookHome ((float *)IMG(0x76d3f8))   /* float[3]; the menu camera's home look-at point (g_menuLookAtX .. Z) */
#define g_armcTabColourDim ((u32 *)IMG(0x4dc1d0))   /* u32[4]; ARM CENTER's tab colour when not chosen (RGBA; g_armcTabColour the chosen one: armc_misc's loop of 4) */
#define g_mechSpeeds ((float *)IMG(0x4dcaf8))   /* float[6]; the mech's speeds from its legs: normal (g_mechNormalSpeed) .. max backward (g_mechMaxSpeedBwd) .. the legs' max weight (g_legsMaxWeight) */
#define g_boosterStats ((float *)IMG(0x4dce80))   /* float[10]; the booster's stats: thrust type (g_boosterThrustType) */
#define g_armcCameraBox ((u32 *)IMG(0x4dcf40))   /* u32[38]; ARM CENTER's camera box corners (+-700 or 0 as floats; armc_initCameraBox writes them from 0x4dcf00 + 0x40 ..) */
#define g_setupSoundRect ((int *)IMG(0x4ddad0))   /* int[4]; the setup sound panel's window: left (g_setupSoundLeft) */
#define g_graphicEdited ((u32 *)IMG(0x4ddba0))   /* u32[7]; the graphics tab's seven values being edited: the screen size (g_setupResolution) then six choices (copied from / to g_graphicInUse) */
#define g_setupControlRect ((int *)IMG(0x4dde80))   /* int[4]; the setup control panel's window: left (g_setupControlLeft) */
#define g_soundEdited ((int *)IMG(0x4dde98))   /* int[4]; the sound tab's four values being edited: the volume (g_volumeSetting) */
#define g_newArenaForm ((int *)IMG(0x4dbb00))   /* int[4]; the create-arena form's window: left (g_newArenaFormLeft) */
#define g_pilotStats ((int *)IMG(0x9dd5d8))   /* int[8]; the pilot's record from the server: level (g_pilotLevel) */
#define g_pilotStatsKept ((int *)IMG(0x9dd240))   /* int[8]; the pilot's record as kept: level (g_pilotLevelKept) .. losses */
#define g_roomForm ((int *)IMG(0x9dd1b8))   /* int[4]; the game room settings form's window: left (g_roomFormLeft) */
#define g_roomLookKept ((float *)IMG(0x9dd918))   /* float[3]; the room camera's look-at point kept for the slide (g_roomSlideNearX .. Z; menu_tunnel's LOOK_KEPT) */
#define g_roomEyeKept ((float *)IMG(0x9dd930))   /* float[3]; the room camera's position kept for the slide (g_roomSlideFarX .. Z; menu_tunnel's EYE_KEPT) */
#define g_mapSelectDim ((u32 *)IMG(0x9dda70))   /* u32[4]; the map list's colour */
#define g_mapSelectLit ((u32 *)IMG(0x9eea98))   /* u32[4]; the map list's colour */
#define g_missionSelectRect ((int *)IMG(0x9f6308))   /* int[4]; the mission select dialog's window: left (g_missionSelectLeft) */
#define g_missionColourLit ((u32 *)IMG(0x9f6318))   /* u32[4]; the mission list's colour */
#define g_missionColourDim ((u32 *)IMG(0x9f62e8))   /* u32[4]; the mission list's colour */
#define g_keptChat ((char *)IMG(0x9f63e4))   /* char[1024]; the chat line kept (copied whole from g_chatLine */
#define g_netSendPacket ((u32 *)IMG(0x9f9428))   /* u32[259]; the message being sent (cleared as 0x103 words): kind (g_netPacketMessageKind) */
#define g_campaign ((u8 *)IMG(0x9f1718))   /* u8[940]; the pilot's save record (0x3ac bytes */
#define g_armcViewPoints ((u32 *)IMG(0x4dca30))   /* u32[24]; ARM CENTER's six view points (16 bytes each */
#define g_menuFrameTextures ((int *)IMG(0x4deb4c))   /* int[2]; the menu frames' textures: the panel corner ornaments */
#define g_soundSettings ((int *)IMG(0x4e0c90))   /* int[4]; the sound settings in use: the volume (g_soundVolume) */
#define g_missionHeader ((u32 *)IMG(0x9ef2c0))   /* u32[4]; the mission file's header: the count (g_missionCount) and three words (g_misHeader1 .. 3; read as four words) */
#define g_cursorPoint ((int *)IMG(0xae2f18))   /* int[2]; the cursor position (x: g_cursorPos */
#define g_resultMsg ((u32 *)IMG(0x9f9418))   /* u32[2]; an 8-byte message sent (net_sendMessage */
#define g_netSlotMsg ((u32 *)IMG(0x9f9420))   /* u32[2]; an 8-byte message sent (net_sendMessage): kind (g_netSlotMessageKind) */
#define g_lobbyReplyRecord ((u8 *)IMG(0xa05260))   /* u8[91]; a lobby reply (0x5b bytes read from the lobby socket; its kind at +0x4a: g_lobbyReplyKind) */
#define g_netNoticeRecord ((u8 *)IMG(0xa052c0))   /* u8[34]; the notice received (cleared as 0x22 bytes: g_netNotice */
#define g_serverReply ((u8 *)IMG(0xa052e8))   /* u8[62]; the game server's 62-byte reply (its kind at +0x1e: g_serverReplyKind) */
#define g_gameServerReply ((u8 *)IMG(0xa0b280))   /* u8[121]; a game server's reply (0x79 bytes; its kind at +0x68: g_gameServerReplyKind) */
#define g_netRecvRecord ((u8 *)IMG(0xa05638))   /* u8[267]; the receive buffer (cleared as 0x10b bytes; g_netRecvBuffer its start */
#define g_texture64x64 ((u8 *)IMG(0x4e1878))   /* u8[840004]; the 64 x 64 texture set (a Texture: g_staticTex64x64 its vtable word) */
#define g_texture128x64 ((u8 *)IMG(0x5b1db8))   /* u8[840004]; the 128 x 64 texture set (g_staticTex128x64 its vtable word) */
#define g_texture256x64 ((u8 *)IMG(0x680cd8))   /* u8[840004]; the 256 x 64 texture set (g_staticTex256x64 its vtable word) */
#define g_texture128x128 ((u8 *)IMG(0x76d498))   /* u8[840004]; the 128 x 128 texture set (g_staticTex128x128 its vtable word) */
#define g_texture256x256 ((u8 *)IMG(0x83a9e0))   /* u8[840004]; the 256 x 256 texture set (g_staticTex256x256 its vtable word) */
#define g_texture256x128 ((u8 *)IMG(0x90d1e0))   /* u8[840004]; the 256 x 128 texture set (g_staticTex256x128 its vtable word) */
#define g_textureSets ((u32 *)IMG(0x83a5e0))   /* u32[8]; the texture manager: its vtable word (g_textureManager), the count, the six sets (TextureManager_clear: 8 words; g_textures points here) */
#define g_vecOriginXyz ((float *)IMG(0xa0e7a8))   /* float[3]; the origin (0 */
#define g_vecUnitZXyz ((float *)IMG(0xa0e7c8))   /* float[3]; the unit z axis (0 */
#define g_vecZeroXyz ((float *)IMG(0xa0e7e8))   /* float[3]; the rest vector (0 */
#define g_musicDuration ((u32 *)IMG(0xa0e018))   /* u32[2]; the music's duration (GetDuration's 64-bit time: g_musicLength the low word */
