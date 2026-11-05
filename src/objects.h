/* objects.h: the game's arrays, buffers and records by name (tools/name_objects.py): each the original address in
   the harness, its place in AxisRC.exe (IMG; in AxisRC.exe a member of g_rdata / g_data, src/data/layout.h).
   OBJ(name) is its address as a number (src/axis.h). Element type, count: the extent known (see the note) */
#pragma once
#define g_chatLine ((char *)IMG(0x9dc92c))   /* char[1024]; the chat line being typed (memset 0x400) */
#define g_ladderId ((char *)IMG(0x9dd570))   /* char[54]; the Ladder login: the ID (30 bytes; the registry's "Name", default "AxisPlayer"), then its password at +0x1e (g_ladderPassword; 12 at most), up to the registry's e-mail copy at 0x9dd5a6 */
#define g_ladderName ((char *)IMG(0x4de700))   /* char[30]; the logged-in pilot's Ladder record: the ID, then from +0x1e its level, points, rating, score, wins and losses (g_ladderLevel ..) */
#define g_accountForm ((u8 *)IMG(0x9dd1d8))   /* u8[94]; the account / Ladder login / new-ID forms' fields: the name (+0; 30); the password (+0x1e; 12); its repeat (+0x2a; 12); the e-mail (+0x36; 40). One clear of 0x54 bytes spans the fields and copies run on from the name: one record */
#define g_accountName ((char *)(g_accountForm + 0))
#define g_accountPassword ((char *)(g_accountForm + 0x1e))
#define g_accountPasswordRepeat ((char *)(g_accountForm + 0x2a))
#define g_accountEmail ((char *)(g_accountForm + 0x36))
#define g_playerName ((char *)IMG(0x4ded20))   /* char[48]; the arena settings record (GameSettings, axis.cfg's server section): the name, then the map .. limits (+0x20: g_arenaMap ..), the clan / password (+0x26), the flag +0x2e */
#define g_cfgPlayerName ((char *)IMG(0x4dedb0))   /* char[32]; axis.cfg's player name (default "PLAYER") */
#define g_roomRecName ((char *)IMG(0x5b1b30))   /* char[48]; the room settings record (GameSettings, the registry's copy): the name, then the six choices (+0x20: g_roomRec*), the password (+0x26) */
#define g_roomSettingsName ((char *)IMG(0x4df9c8))   /* char[48]; the room's settings record (GameSettings, the room's form): the name, then +0x20: g_roomMap .., the password (+0x26) */
#define g_newArenaName ((char *)IMG(0x4db528))   /* char[48]; the new arena's settings record (GameSettings, the create-arena form): the name, then +0x20: g_newArenaMap .., the password (+0x26) */
#define g_mapTitle ((char *)IMG(0x67fb44))   /* char[32]; the map's title (TITLE: %s) */
#define g_profileName ((char *)IMG(0x9f8fe8))   /* char[32]; the profile's name (written 0x20 bytes) */
#define g_arenaPlayerName ((char *)IMG(0x4db560))   /* char[32]; the lobby player's name (edited; axis.cfg's g_cfgPlayerName kept) */
#define g_localAddress ((char *)IMG(0xa0b43c))   /* char[16]; the local IP address text (memset 16) */
#define g_dataDir ((char *)IMG(0x9dae7c))   /* char[0x105]; the data folder's path (app_setDataPaths clears 0x105 bytes; 0x9daf88 next) */
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
#define g_netSlots ((NetSlot *)IMG(0x9f9840))   /* NetSlot[16] (net_clearSlots runs to 0x9fd940); overlapped by g_profileRecords' 103 records at start-up */
#define g_netPlayerList ((RankedPlayer *)IMG(0xa05330))   /* RankedPlayer[11]; (net_clearPlayerList) */
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
#define g_mapNames ((char *)IMG(0x907b30))   /* char[100][0x20]; a map's name (100 maps: up to 0x9087b0, like the descriptions g_mapAbouts) */
#define g_profileRecords ((PilotProfile *)IMG(0x9f9040))   /* PilotProfile[1]: 0x4c bytes a record; the stats check reads 103 records (to 0x9fafb4), so the table overlaps g_netSlots (the original's aliasing) */
#define g_messages ((char *)IMG(0x74de24))   /* char[128256]; the message table: 0x80 bytes a line from msgeng.dat (data_loadMessages) */
#define g_ptxPixels ((u8 *)IMG(0xa21708))   /* u8[262144]; the image decoder's output (RGB(A) */
#define g_ptxData ((u8 *)IMG(0xaa2e98))   /* u8[262144]; the image decoder's input */
#define g_roomList ((u8 *)IMG(0x9fd960))   /* u8[30976]; the server's room list: 256 rooms of 0x79 bytes (net_clearRoomList: 0x1e40 dwords) */
#define g_missions ((Mission *)IMG(0x9ef2d0))   /* Mission[30]; the missions of axis.mis (mission_clear runs to 0x9f109c) */
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
#define g_replayList ((FileEntry *)IMG(0x9dda88))   /* FileEntry[1024]; the file dialog's names (the reset runs 0x9ddac8 .. 0x9eeac8) */
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
#define g_slotTextures ((int *)IMG(0x4dcc70))   /* int[7]; ARM CENTER's snapshot textures by part record (armc_snapshot(i): the six slots, then the part looked at - g_armcBuildTexture, the seventh) */
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
#define g_replaySelectDim ((u32 *)IMG(0x9dda70))   /* u32[4]; the map list's colour */
#define g_replaySelectLit ((u32 *)IMG(0x9eea98))   /* u32[4]; the map list's colour */
#define g_missionSelectRect ((int *)IMG(0x9f6308))   /* int[4]; the mission select dialog's window: left (g_missionSelectLeft) */
#define g_missionColourLit ((u32 *)IMG(0x9f6318))   /* u32[4]; the mission list's colour */
#define g_missionColourDim ((u32 *)IMG(0x9f62e8))   /* u32[4]; the mission list's colour */
#define g_keptChat ((char *)IMG(0x9f63e4))   /* char[1024]; the chat line kept (copied whole from g_chatLine */
#define g_netSendPacket ((NetPacketMessage *)IMG(0x9f9428))   /* NetPacketMessage[1]; the packet message being sent (cleared as 0x103 words): kind (g_netPacketMessageKind) */
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
#define g_texture64x64 ((u8 *)IMG(0x4e1878))   /* u8[840004]; the 64 x 64 texture set (a Texture: g_texture64x64Vtable its vtable word) */
#define g_texture128x64 ((u8 *)IMG(0x5b1db8))   /* u8[840004]; the 128 x 64 texture set (g_texture128x64Vtable its vtable word) */
#define g_texture256x64 ((u8 *)IMG(0x680cd8))   /* u8[840004]; the 256 x 64 texture set (g_texture256x64Vtable its vtable word) */
#define g_texture128x128 ((u8 *)IMG(0x76d498))   /* u8[840004]; the 128 x 128 texture set (g_texture128x128Vtable its vtable word) */
#define g_texture256x256 ((u8 *)IMG(0x83a9e0))   /* u8[840004]; the 256 x 256 texture set (g_texture256x256Vtable its vtable word) */
#define g_texture256x128 ((u8 *)IMG(0x90d1e0))   /* u8[840004]; the 256 x 128 texture set (g_texture256x128Vtable its vtable word) */
#define g_textureSets ((u32 *)IMG(0x83a5e0))   /* u32[8]; the texture manager: its vtable word (g_textureManager), the count, the six sets (TextureManager_clear: 8 words; g_textures points here) */
#define g_vecOriginXyz ((float *)IMG(0xa0e7a8))   /* float[3]; the origin (0 */
#define g_vecUnitZXyz ((float *)IMG(0xa0e7c8))   /* float[3]; the unit z axis (0 */
#define g_vecZeroXyz ((float *)IMG(0xa0e7e8))   /* float[3]; the rest vector (0 */
#define g_musicDuration ((u32 *)IMG(0xa0e018))   /* u32[2]; the music's duration (GetDuration's 64-bit time: g_musicLength the low word */
#define g_resolutionNames ((u32 *)IMG(0x4b04cc))   /* u32[8]; the setup screen's screen size names (by g_setupResolution) */
#define g_typedArenaNameText ((char *)IMG(0x4dbbd4))   /* char[24]; the arena address typed (cleared as 24 bytes; its edit takes 20 characters; g_typedArenaName its first word) */
#define g_partRecords ((u8 *)IMG(0x4dbe50))   /* u8[896]; ARM CENTER's part records: six slots then the part looked at */
#define g_viewedPart (g_partRecords + 6 * 0x80)   /* u8[0x80]; the part being looked at: the seventh of g_partRecords (g_viewedPartKind +0x44, index +0x48) */
#define g_mapListRects ((int *)IMG(0x4d9358))   /* int[104]; mapList_hitTest's 26 hit rectangles (hit_tests.c) */
#define g_arenaNameDialogRects ((int *)IMG(0x4db588))   /* int[24]; arenaNameDialog_hitTest's 6 hit rectangles (hit_tests.c) */
#define g_createArenaRects ((int *)IMG(0x4db5e8))   /* int[64]; createArena_hitTest's 16 hit rectangles (hit_tests.c) */
#define g_createArena2Rects ((int *)IMG(0x4db6e8))   /* int[8]; createArena_hitTest's 2 hit rectangles (hit_tests.c) */
#define g_arenaGameListRects ((int *)IMG(0x4db720))   /* int[72]; arenaGameList_hitTest's 18 hit rectangles (hit_tests.c) */
#define g_arenaDialogBoxRects ((int *)IMG(0x4dbad0))   /* int[4]; arenaDialogBox_hitTest's 1 hit rectangles (hit_tests.c) */
#define g_arenaCreateRects ((int *)IMG(0x4dbb80))   /* int[8]; arenaCreate_hitTest's 2 hit rectangles (hit_tests.c) */
#define g_armcWeaponsPageRects ((int *)IMG(0x4dbc88))   /* int[60]; armcWeaponsPage_hitTest's 15 hit rectangles (hit_tests.c) */
#define g_armcPartsPageRects ((int *)IMG(0x4dc2a8))   /* int[68]; armcPartsPage_hitTest's 17 hit rectangles (hit_tests.c) */
#define g_armcColourRects ((int *)IMG(0x4dcb38))   /* int[72]; armcColour_hitTest's 18 hit rectangles (hit_tests.c) */
#define g_setupSoundRects ((int *)IMG(0x4ddcf0))   /* int[40]; setupSound_hitTest's 10 hit rectangles (hit_tests.c) */
#define g_setupSliderRects ((int *)IMG(0x4ddd98))   /* int[12]; setupSlider_hitTest's 3 hit rectangles (hit_tests.c) */
#define g_setupOptionsRects ((int *)IMG(0x4ddde0))   /* int[36]; setupOptions_hitTest's 9 hit rectangles (hit_tests.c) */
#define g_setupControlRects ((int *)IMG(0x4ddea8))   /* int[72]; setupControl_hitTest's 18 hit rectangles (hit_tests.c) */
#define g_gameListRects ((int *)IMG(0x9dcd48))   /* int[60]; gameList_hitTest's 15 hit rectangles (hit_tests.c) */
#define g_newIdFormRects ((int *)IMG(0x9dce50))   /* int[28]; newIdForm_hitTest's 7 hit rectangles (hit_tests.c) */
#define g_gameListStopRects ((int *)IMG(0x9dd308))   /* int[4]; gameListStop_hitTest's 1 hit rectangles (hit_tests.c) */
#define g_leaveDialogRects ((int *)IMG(0x9dd390))   /* int[8]; leaveDialog_hitTest's 2 hit rectangles (hit_tests.c) */
#define g_popupRects ((int *)IMG(0x9dd3b8))   /* int[8]; popup_hitTest's 2 hit rectangles (hit_tests.c) */
#define g_accountRects ((int *)IMG(0x9dd400))   /* int[24]; account_hitTest's 6 hit rectangles (hit_tests.c) */
#define g_rankingRects ((int *)IMG(0x9dd4c0))   /* int[36]; ranking_hitTest's 9 hit rectangles (hit_tests.c) */
#define g_roomSettingsRects ((int *)IMG(0x9dd6f8))   /* int[56]; roomSettings_hitTest's 14 hit rectangles (hit_tests.c) */
#define g_roomLoginRects ((int *)IMG(0x9dd7e0))   /* int[20]; roomLogin_hitTest's 5 hit rectangles (hit_tests.c) */
#define g_replaySelectRects ((int *)IMG(0x9dd950))   /* int[72]; replaySelect_hitTest's 18 hit rectangles (hit_tests.c) */
#define g_skirmishSettingsRects ((int *)IMG(0x9ef220))   /* int[40]; skirmishSettings_hitTest's 10 hit rectangles (hit_tests.c) */
#define g_briefingRects ((int *)IMG(0x9f16c0))   /* int[16]; briefing_hitTest's 4 hit rectangles (hit_tests.c) */
#define g_missionselRects ((int *)IMG(0x9f6330))   /* int[16]; missionsel_hitTest's 4 hit rectangles (hit_tests.c) */
#define g_deleteDialogRects ((int *)IMG(0x9f6808))   /* int[8]; deleteDialog_hitTest's 2 hit rectangles (hit_tests.c) */
#define g_profilePageRects ((int *)IMG(0x9f8c60))   /* int[36]; profilePage_hitTest's 9 hit rectangles (hit_tests.c) */
#define g_profileListRects ((int *)IMG(0x9f8d78))   /* int[52]; profileList_hitTest's 13 hit rectangles (hit_tests.c) */
#define g_logOutDialogRects ((int *)IMG(0x9f8ee8))   /* int[8]; logOutDialog_hitTest's 2 hit rectangles (hit_tests.c) */
#define g_pilotSelectRects ((int *)IMG(0x9f8f38))   /* int[44]; pilotSelect_hitTest's 11 hit rectangles (hit_tests.c) */
#define g_newNameDialogRects ((int *)IMG(0x9f9020))   /* int[8]; newNameDialog_hitTest's 2 hit rectangles (hit_tests.c) */
#define g_mousePos ((int *)IMG(0x4ded68))   /* int[2]; the mouse pointer in 640 x 480 units (g_mouseX */
#define g_bindRows ((int *)IMG(0x4b04ec))   /* int[4]; the rows of each controls page (move */
#define g_setupOptionsRect ((int *)IMG(0x4dddd0))   /* int[4]; the setup options panel's window: left */
#define g_lobbyTopRect ((int *)IMG(0x4dba70))   /* int[4]; the lobby top menu's window: left */
#define g_roomMessageRect ((int *)IMG(0x9dced8))   /* int[4]; the game room's message box window: left */
#define g_setupColourLit ((u32 *)IMG(0x4de048))   /* u32[4]; setup's text colour */
#define g_setupColourDim ((u32 *)IMG(0x4ddae0))   /* u32[4]; setup's text colour */
#define g_skirmishColourLit ((u32 *)IMG(0x9ef208))   /* u32[4]; the skirmish settings' panel colour */
#define g_skirmishColourDim ((u32 *)IMG(0x9eeac8))   /* u32[4]; the skirmish settings' colour */
#define g_textColours ((Colour *)IMG(0xa1f100))   /* Colour[16]; the 16 message colours (RGBA floats; colour_initTextColours fills them) */
#define g_keyState ((u8 *)IMG(0x4d1e9c))   /* u8[256]; the keyboard's 256 key bytes (0x80: held; DirectInput's GetDeviceState) */
#define g_dplaySlots ((int *)IMG(0xa0d7a4))   /* int[4]; four DirectPlay connection slots: 1 while open */
#define g_panelBoxes ((u8 *)IMG(0x4dc550))   /* u8[528]; ARM CENTER's six part panels' boxes (0x58 bytes each: +-600 corners */
#define g_mapChoiceTable ((u8 *)IMG(0x4d7358))   /* u8[8192]; the arena's map choices (1024 of 8 bytes: MapChoice) */
#define g_mapChoiceKeptTable ((MapChoice *)IMG(0x4d9508))   /* MapChoice[1024]; the map choices kept (1024 of 8: on */
#define g_packetQueue ((u8 *)IMG(0xaef660))   /* u8[139328]; the packet queue: g_unused16, g_history, g_ahead (one object: netq_receive
   reads g_ahead[-1], the history's last word, while player 0's next number is -1, and when that word is 1 copies the 64
   bytes before g_history, g_unused16) */
#define g_unused16 ((int *)g_packetQueue)   /* int[16]; per player */
#define g_history (g_packetQueue + 0x40)   /* u8[131072]; each player's packets by number: 16 x 128 of 64 bytes (net_packets) */
#define g_ahead ((int *)(g_packetQueue + 0x20040))   /* int[2048]; [player * 128 + number]: arrived ahead of its turn (net_packets) */
#define g_nextNumber ((int *)IMG(0xb116a0))   /* int[16]; each player's next packet number (-1: none yet) */
#define g_serverUsed ((u32 *)IMG(0xa0bb14))   /* u32[256]; per server slot: in use */
#define g_serverPing ((int *)IMG(0xa0d384))   /* int[256]; per server slot: the ping time (0 none) */
#define g_loadTimer ((u8 *)IMG(0xa0e948))   /* u8[56]; the loading screen's own game-time timer (a TimeSync: 0xe words) */
#define g_lobbyTopOutlines ((int *)IMG(0x5b1cf8))   /* int[44]; the lobby top menu's 4 button outlines (lobby_states / setup_pages' hovered_panel) */
#define g_mainMenuOutlines ((int *)IMG(0x4deb80))   /* int[66]; the main menu's 6 button outlines (menu_records' menu_choice) */
#define g_roomOutlines ((int *)IMG(0x9daf88))   /* int[66]; the game room's 6 button outlines (room_clicks) */
#define g_setupTopOutlines ((int *)IMG(0x4df918))   /* int[44]; the setup top page's 4 button outlines (copied from the lobby's: setupTop_initOutlines) */
#define g_outlinesCopy ((int *)IMG(0x9da328))   /* int[44]; a second copy of the lobby's 4 outlines (setupTop_initOutlines; not read elsewhere) */
#define g_vkTable ((int *)IMG(0x4df054))   /* int[57]; the scan-code row -> virtual key table (input_initVkTable; written only */
#define g_defaultColours ((u32 *)IMG(0xa1f298))   /* u32[16]; the 16 default packed colours (colour_initDefaultColours: RGBA bytes) */
#define g_headList ((int *)IMG(0x4dc3e8))   /* int[50]; the unlocked heads (armc_buildPartLists) */
#define g_chestList ((int *)IMG(0x4dcd6c))   /* int[50]; the unlocked chests */
#define g_armList ((int *)IMG(0x4dc964))   /* int[50]; the unlocked arms */
#define g_legList ((int *)IMG(0x4dc89c))   /* int[50]; the unlocked legs */
#define g_boosterList ((int *)IMG(0x4dbd7c))   /* int[50]; the unlocked boosters */
#define g_weaponListTable ((int *)IMG(0x4dc79c))   /* int[50]; the weapons on offer (starts with -1; armc_items' g_weaponList) */
#define g_extraListTable ((int *)IMG(0x4dcca4))   /* int[50]; the other items on offer (starts with -1; armc_items' g_extraList) */
#define g_headPanelName ((char *)IMG(0x4dceb8))   /* char[64]; the head panel's part name (panel_name) */
#define g_chestPanelName ((char *)IMG(0x4dbc08))   /* char[64]; the chest panel's part name */
#define g_armPanelName ((char *)IMG(0x4dc250))   /* char[64]; the arm panel's part name */
#define g_legPanelName ((char *)IMG(0x4dc1e8))   /* char[64]; the leg panel's part name */
#define g_boosterPanelName ((char *)IMG(0x4dce40))   /* char[64]; the booster panel's part name */
#define g_launcherCheck ((u8 *)IMG(0x4dd988))   /* u8[12]; the launcher's eight check bytes (app_readLauncherCheck: 12 cleared) */
#define g_missionClearBuffer ((u8 *)IMG(0x9eebac))   /* u8[1600]; cleared on a mission's load (0x640) and otherwise unused */
#define g_serverAddressArg ((char *)IMG(0x4de748))   /* char[1024]; "-ip x <server>": the server's address (0x400 cleared) */
#define g_arenaGameName ((char *)IMG(0x5b191c))   /* char[32]; the arena file's gamename value (32 cleared) */
#define g_profileHeader ((u8 *)IMG(0x9f61d8))   /* u8[260]; a profile file's header (0x104 bytes) checked on the profile scan */
#define g_pilotNoise ((u8 *)IMG(0x9f3ac4))   /* u8[10000]; the noise blocks around a saved pilot (pilot_write: 10000 random bytes) */
#define g_playerSlotFlags ((int *)IMG(0x9f93d8))   /* int[16]; the sixteen player slots' in-use flags (net_claimPlayerSlot) */
#define g_sessionTable ((SessionSlot *)IMG(0xa0b470))   /* SessionSlot[200] */
#define g_dottedAddress ((char *)IMG(0xa0b460))   /* char[16]; an address as dotted text (at most 15 characters) */
#define g_sessionDesc ((DPSessionDesc2 *)IMG(0xa0b3b0))   /* DPSessionDesc2[1]; the one shared by hosting and joining (session_desc) */
#define g_tcpProviderGuid ((u8 *)IMG(0xa0b3a0))   /* u8[16]; the TCP service provider's GUID */
#define g_ipxProviderGuid ((u8 *)IMG(0xa0b450))   /* u8[16]; the IPX service provider's GUID */
#define g_modemProviderGuid ((u8 *)IMG(0xa0b408))   /* u8[16]; the modem service provider's GUID */
#define g_serialProviderGuid ((u8 *)IMG(0xa0bab8))   /* u8[16]; the serial service provider's GUID */
#define g_font16Bottom ((float *)IMG(0x9db0b0))   /* float[280]; the 16 / 32-pixel menu font: the cells' bottom edges */
#define g_font16Top ((float *)IMG(0x9da4a8))   /* float[280]; the 16 / 32-pixel menu font: the cells' top edges */
#define g_font16Left ((float *)IMG(0x9da90c))   /* float[280]; the 16 / 32-pixel menu font: the cells' left edges */
#define g_font16Right ((float *)IMG(0x9db510))   /* float[280]; the 16 / 32-pixel menu font: the cells' right edges */
#define g_font8Bottom ((float *)IMG(0x67ff64))   /* float[256]; the 8-pixel menu font: the cells' bottom edges */
#define g_font8Top ((float *)IMG(0x6803ac))   /* float[256]; the 8-pixel menu font: the cells' top edges */
#define g_font8Left ((float *)IMG(0x6807ac))   /* float[256]; the 8-pixel menu font: the cells' left edges */
#define g_font8Right ((float *)IMG(0x67fb64))   /* float[256]; the 8-pixel menu font: the cells' right edges */
#define g_font5Bottom ((float *)IMG(0x4e0ce4))   /* float[256]; the 5-pixel menu font: the cells' bottom edges */
#define g_font5Top ((float *)IMG(0x5b1114))   /* float[256]; the 5-pixel menu font: the cells' top edges */
#define g_font5Left ((float *)IMG(0x5b1514))   /* float[256]; the 5-pixel menu font: the cells' left edges */
#define g_font5Right ((float *)IMG(0x4e10e8))   /* float[256]; the 5-pixel menu font: the cells' right edges */
#define g_hudFontBottom ((float *)IMG(0x4e0474))   /* float[256]; the HUD glyphs: the cells' bottom edges */
#define g_hudFontTop ((float *)IMG(0x5b0910))   /* float[256]; the HUD glyphs: the cells' top edges */
#define g_hudFontLeft ((float *)IMG(0x5b0d10))   /* float[256]; the HUD glyphs: the cells' left edges */
#define g_hudFontRight ((float *)IMG(0x4e0878))   /* float[256]; the HUD glyphs: the cells' right edges */
#define g_hudLayerABottom ((float *)IMG(0x5b1b64))   /* float[100]; the HUD two-layer glyphs */
#define g_hudLayerATop ((float *)IMG(0x4e16d8))   /* float[100]; the HUD two-layer glyphs */
#define g_hudLayerALeft ((float *)IMG(0x4e1548))   /* float[100]; the HUD two-layer glyphs */
#define g_hudLayerARight ((float *)IMG(0x5b199c))   /* float[100]; the HUD two-layer glyphs */
#define g_hudLayerBBottom ((float *)IMG(0x83a7e0))   /* float[120]; the HUD two-layer glyphs */
#define g_hudLayerBTop ((float *)IMG(0x4df638))   /* float[120]; the HUD two-layer glyphs */
#define g_hudLayerBLeft ((float *)IMG(0x4df458))   /* float[120]; the HUD two-layer glyphs */
#define g_hudLayerBRight ((float *)IMG(0x83a600))   /* float[120]; the HUD two-layer glyphs */
#define g_penFixedTopLeft ((float *)IMG(0xa0f498))   /* float[210]; the fixed set's top left corners */
#define g_penFixedTopRight ((float *)IMG(0xa10018))   /* float[210]; the fixed set's top right corners */
#define g_penFixedBottomRight ((float *)IMG(0xa0f150))   /* float[210]; the fixed set's bottom right corners */
#define g_penFixedBottomLeft ((float *)IMG(0xa0fcd0))   /* float[210]; the fixed set's bottom left corners */
#define g_penPropTopLeft ((float *)IMG(0xa0eac0))   /* float[210]; the proportional set's top left corners */
#define g_penPropTopRight ((float *)IMG(0xa10360))   /* float[210]; the proportional set's top right corners */
#define g_penPropBottomRight ((float *)IMG(0xa0ee08))   /* float[210]; the proportional set's bottom right corners */
#define g_penPropBottomLeft ((float *)IMG(0xa0f7e0))   /* float[210]; the proportional set's bottom left corners */
#define g_penFixedWidths ((int *)IMG(0xa0fb28))   /* int[105]; the fixed set's glyph widths (all 8) */
#define g_sortBounds ((int *)IMG(0x4c83c4))   /* int[8192]; the two sorts' lo / hi arrays: A lo */
#define g_sortState ((u8 *)IMG(0xae3338))   /* u8[49176]; the two sorts' i / j / pivot arrays */
#define g_packedBlue ((u8 *)IMG(0xa1f200))   /* u8[4]; packed blue (colour_initPackedBlue) */
#define g_packedGrey ((u8 *)IMG(0xa1f204))   /* u8[4]; packed grey */
#define g_packedYellow ((u8 *)IMG(0xa1f208))   /* u8[4]; packed yellow (main_loop's view-volume segments) */
#define g_packedGreen ((u8 *)IMG(0xa1f2ec))   /* u8[4]; packed green */
#define g_realClear ((float *)IMG(0xa1f210))   /* float[4]; real clear (colour_initRealClear) */
#define g_realBlue ((float *)IMG(0xa1f228))   /* float[4]; real blue */
#define g_realWhite ((float *)IMG(0xa1f240))   /* float[4]; real white */
#define g_realGreen ((float *)IMG(0xa1f258))   /* float[4]; real green */
#define g_realRed ((float *)IMG(0xa1f268))   /* float[4]; real red */
#define g_realBlack ((float *)IMG(0xa1f280))   /* float[4]; real black */
#define g_realYellow ((float *)IMG(0xa1f2d8))   /* float[4]; real yellow */
#define g_realGrey ((float *)IMG(0xa1f2f0))   /* float[4]; real grey */
#define k_c_dfDIKeyboard ((u32 *)IMG(0x4a95f8))   /* u32[6]; DIDATAFORMAT (0x18 / 0x10 / DIDF_RELAXIS / 0x100 bytes / 0x100 objects at 0x44f950) */
#define k_c_dfDIMouse ((u32 *)IMG(0x4a9610))   /* u32[6]; DIDATAFORMAT (0x18 / 0x10 / DIDF_RELAXIS / 0x10 bytes / 7 objects at 0x450950) */
#define k_DPAID_INet ((u8 *)IMG(0x4a9628))   /* u8[16]; c4a54da0-e0af-11cf-9c4e-00a0c905425e */
#define k_DPAID_ServiceProvider ((u8 *)IMG(0x4a9638))   /* u8[16]; 07d916c0-e0af-11cf-9c4e-00a0c905425e */
#define k_CLSID_DirectPlayLobby ((u8 *)IMG(0x4a9648))   /* u8[16]; 2fe8f810-b2a5-11d0-a787-0000f803abfc */
#define k_IID_IDirectPlayLobby3A ((u8 *)IMG(0x4a9658))   /* u8[16]; 2db72491-652c-11d1-a7a8-0000f803abfc */
#define k_CLSID_DirectPlay ((u8 *)IMG(0x4a9668))   /* u8[16]; d1eb6d20-8923-11d0-9d97-00a0c90a43cb */
#define k_IID_IDirectPlay4A ((u8 *)IMG(0x4a9678))   /* u8[16]; 0ab1c531-4745-11d1-a7a1-0000f803abfc */
#define k_GUID_SysKeyboard ((u8 *)IMG(0x4a9688))   /* u8[16]; 6f1d2b61-d5a0-11cf-bfc7-444553540000 */
#define k_GUID_SysMouse ((u8 *)IMG(0x4a9698))   /* u8[16]; 6f1d2b60-d5a0-11cf-bfc7-444553540000 */
#define k_axisAppGuid ((u8 *)IMG(0x4a96e8))   /* u8[16]; the game's DirectPlay application GUID (guidApplication) 456a6a41-e585-11d4-9662-0050da8e5b67 */
#define k_GUID_NULL ((u8 *)IMG(0x4aae70))   /* u8[16]; 16 zero bytes (a session with no GUID is skipped) */
#define k_IID_IAMMultiMediaStream ((u8 *)IMG(0x4aae90))   /* u8[16]; bebe595c-9a6f-11d0-8fde-00c04fd9189d */
#define k_CLSID_AMMultiMediaStream ((u8 *)IMG(0x4aaf10))   /* u8[16]; 49c47ce5-9ba4-11d0-8212-00c04fc32c45 */
#define k_MSPID_PrimaryAudio ((u8 *)IMG(0x4aafc0))   /* u8[16]; the audio stream's purpose ID (IAMMultiMediaStream::AddMediaStream) */
#define g_hangulLeadIndex ((signed char *)IMG(0x4ad3c4))   /* signed char[32]; lead consonant code -> index */
#define g_hangulVowelIndex ((signed char *)IMG(0x4ad3e4))   /* signed char[32]; vowel code -> index */
#define g_hangulTailIndex ((signed char *)IMG(0x4ad404))   /* signed char[32]; tail consonant code -> index (0 none) */
#define g_hangulVowelSetPlain ((signed char *)IMG(0x4ad424))   /* signed char[22]; the lead's glyph set by the vowel; no tail */
#define g_hangulVowelSetTail ((signed char *)IMG(0x4ad43a))   /* signed char[22]; the lead's glyph set by the vowel; with a tail */
#define g_hangulLeadSetPlain ((signed char *)IMG(0x4ad450))   /* signed char[20]; the vowel's glyph set by the lead; no tail */
#define g_hangulLeadSetTail ((signed char *)IMG(0x4ad464))   /* signed char[20]; the vowel's glyph set by the lead; with a tail */
#define g_hangulTailSet ((signed char *)IMG(0x4ad478))   /* signed char[22]; the tail's glyph set by the vowel (2 padding bytes before 0x4ad490) */
#define g_matchPlayerName ((char *)IMG(0x4dedd8))   /* char[32]; the player's name for the match (match_name clears 32 bytes) */
#define g_mapInfoDir ((char *)IMG(0x4dedf8))   /* char[261]; the second data path ("initdata/"; app_setDataPaths clears 0x105 bytes; mapinfo.dat's folder) */
#define g_stageDir ((char *)IMG(0x680bc4))   /* char[261]; the maps' folder ("stage/"; app_setDataPaths clears 0x105 bytes) */
#define g_mapAbouts ((char *)IMG(0x5ae9d0))   /* char[8000]; a map's 0x50-byte description (100 maps: up to 0x5b0910) */
#define g_joinedSessionRec ((SessionEntry *)IMG(0x9dae20))   /* SessionEntry[1]; the session record the arena join answer builds */
#define g_codeColours ((Colour *)IMG(0x9dada0))   /* Colour[7]; the seven "$[n]" text colours (menu_initColours) */
#define g_serverList ((u8 *)IMG(0xa05748))   /* u8[23296]; 256 servers of 0x5b bytes (net_clearServerList: 0x16c0 dwords; up to 0xa0b248) */
#define g_lobbyReplyCode ((int *)IMG(0xa055dc))   /* int[1]; the lobby's 4-byte status reply (request 12) */
#define g_gameServerReplyCode ((int *)IMG(0xa0b248))   /* int[1]; the game server's 4-byte status reply (request 18) */
#define g_lobbyHost ((char *)IMG(0xa055e4))   /* char[16]; the lobby server's address as text (a name that does not resolve is copied whole: runs on in the original) */
#define g_ladderDns ((char *)IMG(0xa055fc))   /* char[50]; HKCU SelectServer LadderDNS (50 bytes cleared by net_clearServerSettings) */
#define g_tcpDns ((char *)IMG(0xa0b24c))   /* char[50]; HKCU SelectServer TcpDNS (50 bytes) */
#define g_noAddress ((char *)IMG(0xa0bb0c))   /* char[4]; the empty address DirectPlay's TCP connection gets without one (never written) */
#define g_statBars ((float *)IMG(0x9f8d34))   /* float[9]; the profile screen's nine stat bars as drawn (eased a tenth a frame) */
#define g_statBarTargets ((float *)IMG(0x9f8ec0))   /* float[9]; the bars' targets (only cleared) */
#define g_profileDialogBox ((int *)IMG(0x9f9010))   /* int[4]; the profile dialog box (left; top; right; bottom) */
#define g_chatHistory ((char *)IMG(0x67ef38))   /* char[3072]; the chat line's three-line history of 0x400 bytes; newest first (frontEnd_startUp clears 0x300 dwords) */
#define g_undoStack ((int *)IMG(0x9eeadc))   /* int[50]; the skirmish settings' undo values (0xc8 bytes cleared; g_briefingStart follows) */
#define g_ladderEmail ((char *)IMG(0x9dd5a6))   /* char[30]; the Ladder account's e-mail (the registry's copy) (30 bytes cleared; up to 39 copied in) */
#define g_keyTable1 ((int *)IMG(0x4d1688))   /* int[256]; a key table only cleared at start-up */
#define g_mouseState ((int *)IMG(0x4d1a88))   /* int[4]; DIMOUSESTATE: x; y; wheel movement; four button bytes */
#define g_keyTable2 ((int *)IMG(0x4d1fc4))   /* int[256]; the second key table (only cleared) */
#define g_asyncKeySeen ((int *)IMG(0xae2f24))   /* int[256]; input_asyncKeyPressed's seen flags by virtual key */
#define g_mouseWasDown ((int *)IMG(0x9f1704))   /* int[3]; the three mouse buttons down last frame */
#define g_teamNames ((char *)IMG(0x4db860))   /* char[60]; RED / BLUE / YELLOW; 0x14 bytes each (messages 441 .. 443) */
#define g_gameTypeNames ((char *)IMG(0x4db8d8))   /* char[300]; 15 game type names of 0x14 bytes (messages 456 .. 470) */
#define g_arenaOnOff ((char *)IMG(0x4dbb14))   /* char[40]; OFF / ON; 0x14 bytes each (messages 444; 445) */
#define g_arenaOnOff2 ((char *)IMG(0x4dbba4))   /* char[40]; OFF / ON again; 0x14 bytes each (the new-arena form's kind names; arena_createDraw) */
#define g_lobbyTopRects ((int *)IMG(0x4dbb40))   /* int[8]; lobbyTop_layout's two rectangles */
#define g_lobbyTopEase ((float *)IMG(0x4dbb60))   /* float[1]; the lobby top panel's ease (menu_slide) */
#define g_colourDepthTexts ((char *)IMG(0x4ddbbc))   /* char[100]; COLOR DEPTH: 16BIT COLOR / 32BIT COLOR (messages 431; 432) */
#define g_fxStatusTexts ((char *)IMG(0x4dda64))   /* char[100]; F/X STATUS: OFF / ON (messages 433; 434) */
#define g_linearFilterTexts ((char *)IMG(0x4ddc84))   /* char[100]; LINEAR FILTERING: OFF / ON (messages 435; 436) */
#define g_mipMapTexts ((char *)IMG(0x4de058))   /* char[100]; MIP MAPPING: OFF / ON */
#define g_viewFpsTexts ((char *)IMG(0x4ddc20))   /* char[100]; VIEW FPS: OFF / ON */
#define g_simpleMenuTexts ((char *)IMG(0x4ddaf0))   /* char[100]; SIMPLE MENU: OFF / ON */
#define g_crosshairName ((char *)IMG(0x4ddb58))   /* char[32]; the crosshair texture's name (texture/crosshair/crosshair<n>: 0x20-byte strings) */
#define g_messageBoxLine ((char *)IMG(0x4df81c))   /* char[80]; the front end's message box line (0x50 bytes cleared) */
#define g_clearColour ((Colour *)IMG(0x76d350))   /* Colour[1]; the start-up screen's clear colour (black) */
#define g_ladderIdCopy ((char *)IMG(0x76d450))   /* char[32]; the registry's copy of the Ladder ID (up to 0x76d470) */
#define g_windowClass ((u8 *)IMG(0x4e0ca8))   /* u8[40]; the WNDCLASS the window was registered with (a copy) */
#define g_glTitle ((char *)IMG(0xa0e81c))   /* char[256]; the window's title (also the window class's; icon's and menu's name; up to 0xa0e91c) */
#define g_musicFile ((char *)IMG(0xa0e674))   /* char[260]; the music file's name (MAX_PATH; up to 0xa0e778) */
#define g_messageBoxText ((char *)IMG(0x4dd0d0))   /* char[1024]; sys_messageBox's text (vsprintf; 4 more bytes before 0x4dd4d4) */
#define g_sessionList ((SessionEntry *)IMG(0x9087c0))   /* SessionEntry[256] (to 0x90d1c0) */
#define g_profiles ((u8 *)IMG(0x9f6848))   /* u8[9216]; 128 records of 0x48 (to 0x9f8c48): +0 the number; +4 the name (g_profileList); +0x44 the pilot */
#define g_profileList ((char *)(g_profiles + 4))   /* a profile's name: +4 in g_profiles' records (0x48 apart) */
#define g_saveFileNames ((char *)IMG(0x9f1ac4))   /* char[8192]; profile_scanSaves' *.axs names (0x40 apart; strcpy of any count: held) */
#define g_roomTextAndRows ((u8 *)IMG(0x9dcee8))   /* u8[684]; the room's typed password text (+0; 8 bytes cleared; a strcpy of the chat line) and the room list's ten 0x44-byte rows from +4 (to 0x9dd194): the two overlap in the original */
#define g_roomJoinPassword (*(int *)g_roomTextAndRows)   /* the typed password (text from here) */
#define g_roomJoinPassword4 (*(int *)(g_roomTextAndRows + 4))   /* the rows' start (cleared with the text) */
#define g_rankingRows ((RankRow *)(g_roomTextAndRows + 4))   /* RankRow[10] */
#define g_roomDialogBox ((int *)IMG(0x9dd1a0))   /* int[4]; the room's server dialog box (room_openDialog58; popup_layout) */
#define g_roomMechKept ((u8 *)IMG(0x9dd260))   /* u8[11]; the room record's mech parts kept (lobby_states) */
#define g_roomColoursKept ((u8 *)IMG(0x9dd26b))   /* u8[144]; the room record's colours kept */
#define g_launchArgs ((u32 *)IMG(0x9dd890))   /* u32[14]; the launch line's words (strtok of up to 0x400 bytes: held) */
#define g_shapeDat ((u32 *)IMG(0xa0e79c))   /* u32[3]; Data\Shape.dat: the entry count; the table; the FILE */
#define g_skelDat ((u32 *)IMG(0xa0eab4))   /* u32[3]; Data\Skeleton.dat: the entry count; the table; the FILE */
#define g_skirmishInfo ((u8 *)IMG(0x9db998))   /* u8[1380]; skirmish.dat's 15 records of 0x5c (to 0x9dbefc) */
#define g_soundTable ((u32 *)IMG(0xa0e02c))   /* u32[400]; the sound table's buffers by index (sound_initSoundTable; to 0xa0e66c) */
#define g_menuSoundBuffers ((u32 *)IMG(0x4dd4d4))   /* u32[10]; the ten menu sounds (sound_loadMenuSounds) */
#define g_slotCams ((float *)IMG(0x4dfa1c))   /* float[655]; the ARM CENTER's camera per slot (88 bytes a slot: +0 .. +8 the point; +0x28 the turn); to 0x4e0458 */
#define g_unlockTablesSolo ((u8 *)IMG(0x4ad5f0))   /* u8[5600]; armc_buildPartLists' seven 0x320-byte Unlock tables for solo play (to 0x4aebd0) */
#define g_unlockTablesNet ((u8 *)IMG(0x4aebd0))   /* u8[5600]; the same for network play (to 0x4b01b0) */
#define g_setupWallTurns ((float *)IMG(0x4b04c4))   /* float[2]; the setup tunnel's wall turn by parity (-35; 35) */
#define g_titleSpread ((int *)IMG(0x4b065c))   /* int[20]; by g_titleFrames (0 .. 19): how far the title's quarters have moved apart (0 .. 512) */
#define g_penPropWidths ((int *)IMG(0x4c5558))   /* int[105]; the pen font's proportional glyph widths (105 glyphs; to 0x4c56fc) */
#define g_ptxZigzag ((int *)IMG(0x4c59ec))   /* int[64]; the PTX decoder's zigzag order */
#define g_ptxDcCodes ((int *)IMG(0x4c5af0))   /* int[48]; the DC Huffman codes: two tables of 96 bytes (length; code pairs) */
#define g_ptxAcCodes ((int *)IMG(0x4c5bb0))   /* int[1024]; the AC Huffman codes: two tables of 256 (length; code) pairs */
#define g_ptxDequantBase ((float *)IMG(0x4c6bb0))   /* float[128]; the dequantisation tables' base values (luma; chroma) */
#define g_ptxQuantBase ((int *)IMG(0x4c6db0))   /* int[128]; the quantisation tables' base values (luma; chroma) */
#define g_crtStderr ((u8 *)IMG(0x4d0878))   /* u8[32]; the C runtime's stderr FILE (_iob[2]; name only: the runtime's own code reaches it) */
#define g_crtTenPowersUp ((u8 *)IMG(0x4d12f8))   /* u8[352]; crt_atof's powers of ten (12-byte entries; name only) */
#define g_crtTenPowersDown ((u8 *)IMG(0x4d1458))   /* u8[352]; crt_atof's negative powers of ten (name only) */
#define k_teamNamesKorean ((char *)IMG(0x4a975c))   /* char[64]; the four team names in Korean (16 bytes each) */
#define k_aanScales ((double *)IMG(0x4aa2b0))   /* double[8]; the AAN inverse DCT's scale factors */
#define k_ptxQuantScales ((int *)IMG(0x4aa2f0))   /* int[64]; the quantisation scale per coefficient */
#define g_keyNames ((u32 *)IMG(0x4b0750))   /* u32[256]; a key code's name (pointers to the texts; to 0x4b0b50) */
