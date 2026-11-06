/* globals.h: the game's global variables named (tools/name_globals.py adds them): each is the game's own
   memory at its address, with the type it is used as. A use with another type is written (*(type *)&name)
   (tools/names/retype_uses.py). */
#pragma once

#define g_lobbyConnectionOpen GAME_VAR(int, 0x4db718)
#define g_lobbySearching GAME_VAR(int, 0x4db858)
#define g_lobbyRefreshing GAME_VAR(int, 0x4db8b8)
#define g_lobbyBlinkClock GAME_VAR(float, 0x4dba80)   /* the lists' searching clock: counts down by g_lobbyBlinkRate x g_frameTime (blink step = clock/3 % 15; back to 1000 below 10); also the LAN search's time-out (150 at its start; arena_gamesPageFrame ends the search at 0); shared by the arena list, the game room's list and the ranking page */
#define g_lanSearch GAME_VAR(int, 0x4dba90)
#define g_arenaCameraMode GAME_VAR(int, 0x4dbb3c)
#define g_joinTimedOut GAME_VAR(int, 0x4dbb78)   /* a join's DirectPlay session search timed out (WM_TIMER 0x378 after 30 ticks); the next join answer (arena_joinAnswer / room_joinAnswer) leaves the session with message 0x44 CONNETION TIME OUT */
#define g_enteringMenus GAME_VAR(int, 0x4deb48)
#define g_dialogFrameTexture GAME_VAR(int, 0x4deb50)
#define g_hostAnswer GAME_VAR(int, 0x4ded60)   /* the server's answer to a hosting announcement: 2 none / handled (set by lobby_announceArena, room_announceGame, lobby_openConnection, gameList_open), 1 allowed (arena_connectionOutcome / room_hostingStep host now), 0 other reply, 3 version outdated (g_arenaUpdateNotice), 4 refused (MSG 0x46 / 0x2a SERVER IS BUSY); WndProc sets it from g_lobbyStatus / g_gameServerStatus (0x66 -> 1, 0x67 -> 3, 0x29 / 0x28 -> 4, else 0) */
#define g_rightClick GAME_VAR(int, 0x4ded8c)   /* g_mouseClicked[1]: the right button clicked this frame */
#define g_playerCorporation GAME_VAR(int, 0x4dedd0)
#define g_serverAnswerIn GAME_VAR(int, 0x4df018)
#define g_matchMode GAME_VAR(int, 0x5ae9c4)
#define g_listRefreshPeriod GAME_VAR(int, 0x5b1914)
#define g_panelGlow GAME_VAR(float, 0x680ccc)
#define g_chosenGameMode GAME_VAR(int, 0x76d368)
#define g_launchedForNetGame GAME_VAR(int, 0x76d410)   /* started by the launcher for a network game: command line "-net" (axiswl.dat present: host) or "<x> -ip <server>" (join); skips the file checks, drives the automatic start (g_launchStartStep) and quits after the match (game_postMatch) */
#define g_mapRotation GAME_VAR(int, 0x9da3e0)
#define g_launchStartStep GAME_VAR(int, 0x9da49c)   /* the launcher-started game's automatic start (g_launchedForNetGame): 0 none (also cleared by menu_showMessage), 0x65 profile logged in, 0x66 menus entered (ARM CENTER), 0x67 ARM CENTER left (menu_cameras then calls arena_startFromLauncher), 0x68 hosting / 0x69 joining (menu_frame then takes no mouse or keys) */
#define g_buttonTexture GAME_VAR(int, 0x9db0a4)
#define g_roomCameraMode GAME_VAR(int, 0x9dce48)
#define g_roomLoginDue GAME_VAR(int, 0x9dd1c8)
#define g_lineToLoginId GAME_VAR(int, 0x9dd1cc)
#define g_rankingPage GAME_VAR(int, 0x9dd6ac)
#define g_roomRequestOut GAME_VAR(int, 0x9dd838)
#define g_replayFileCount GAME_VAR(int, 0x9dd928)
#define g_currentProfile GAME_VAR(int, 0x9f8c58)
#define g_netLastRequest GAME_VAR(int, 0xa0b300)
#define g_lobbyListAnswer GAME_VAR(int, 0xa0b36c)   /* the lobby server's answer to the game-list request (net_receiveLobbyReply): 0xca the list complete (ping thread started), 0xcb reply kind 2 (WndProc -> g_searchResult 3: update notice), 0x29 reply kind 3 (-> result 4: MSG 0x46 SERVER IS BUSY); 0 none (cleared when leaving) */
#define g_dplaySessionCount GAME_VAR(int, 0xa0b41c)
#define g_localPlayerId GAME_VAR(u32, 0xa0b424)
#define g_lobbyConnectionBlock GAME_VAR(void *, 0xa0baf4)
#define g_isHost GAME_VAR(int, 0xa0baf8)
#define g_pingTime GAME_VAR(u32, 0xa0d798)
#define g_netListDone GAME_VAR(int, 0xa0d7a0)
#define g_soundBaseVolume GAME_VAR(int, 0xa0e66c)
#define g_randPos GAME_VAR(u32, 0xa1efb8)
#define g_joinThroughServer GAME_VAR(int, 0x4dbaac)   /* the game list is the lobby server's (1, lobby_openConnection / arenaGames connect) rather than the LAN search's (0, set when the DirectPlay search starts); picks the join path: password check + arena_askJoinPassword (1) or arena_joinSession via g_lanJoinRequest (0) */
#define g_lanJoinRequest GAME_VAR(int, 0x4dbbf0)   /* join the selected LAN (DirectPlay-listed) game: set by lobby_join when the list is not the server's (g_joinThroughServer 0); arena_gamesPageFrame then calls arena_joinSession(g_pickedGame) */
#define g_setupTunnelDepth GAME_VAR(float, 0x4ddd90)
#define g_arenaMap GAME_VAR(signed char, 0x4ded40)
#define g_arenaMaxPlayers GAME_VAR(u8, 0x4ded41)
#define g_arenaGameType GAME_VAR(u8, 0x4ded43)
#define g_arenaFragLimit GAME_VAR(u8, 0x4ded44)
#define g_arenaTimeLimit GAME_VAR(u8, 0x4ded45)
#define g_playerCustomize GAME_VAR(int, 0x4dedd4)   /* axis.cfg's "set_player customize" ON (1) / OFF (cfg_readPlayer / cfg_writePlayer; copied to and from g_arenaCustomize by arena_loadPlayerSettings / arena_savePlayerSettings); nothing else reads it */
#define g_panelGlowStep GAME_VAR(float, 0x4df454)   /* the hovered panel's glow step per frame time: +1 or -1 (g_panelGlow bounces between 2 and 38) */
#define g_fragLimit GAME_VAR(int, 0x4df8e8)
#define g_soundVolume GAME_VAR(int, 0x4e0c90)
#define g_desktopWidth GAME_VAR(int, 0x67eefc)
#define g_menuCameraLook GAME_VAR(float, 0x680378)   /* the menu camera's look-at x (g_menuLook[0]; y and z follow) */
#define g_launchedAsHost GAME_VAR(int, 0x76d364)   /* started by the launcher with "-net" and axiswl.dat present: arena_startFromLauncher hosts the arena from axiswl.dat's settings (0: it joins g_serverAddressArg instead) */
#define g_timeLimit GAME_VAR(int, 0x76d408)
#define g_rankingListIn GAME_VAR(int, 0x76d40c)
#define g_desktopHeight GAME_VAR(int, 0x76d430)
#define g_windowDC GAME_VAR(void *, 0x76d480)   /* the game window's DC (WM_CREATE; SwapBuffers on it); at start-up briefly the desktop's, for its depth */
#define g_videoMode GAME_VAR(u32, 0x83a9c0)
#define g_videoDepth GAME_VAR(int, 0x83a9c4)   /* the colour depth choice: 0 16 bits, 1 32 bits (axis.cfg "32"); used as (v + 1) * 16 colour bits */
#define g_lastPanel GAME_VAR(int, 0x907b24)
#define g_roomSearchAnswerIn GAME_VAR(int, 0x9da498)
#define g_replayShowOn GAME_VAR(int, 0x9db994)   /* picked replays are being shown (replaySelect_ok sets it): on the main menu (screen 300) menu_frame zooms in and starts the next replay (g_replayRunning); it stays set between replays until the game-menu key during one (hud_cycleF11Mode clears it); the main menu takes no clicks / keys while it is 1 */
#define g_lineMaxLength GAME_VAR(int, 0x9dcd30)   /* the open text field's length (menu_clearInputBuffer's argument: 0x10 pilot name, 0x14, 0x32 chat, a field's bufferLength ...): the bytes of g_chatLine wiped when the line is cancelled (menu_closeInputLine, newNameDialog_clicks) */
#define g_rankingRequestPending GAME_VAR(int, 0x9dd350)
#define g_rankingHaveList GAME_VAR(int, 0x9dd3b0)
#define g_lineToLoginPassword GAME_VAR(int, 0x9dd6b0)
#define g_roomConnected GAME_VAR(int, 0x9dd84c)
#define g_argCount GAME_VAR(int, 0x9dd88c)
#define g_replayRandomOrder GAME_VAR(int, 0x9eeac0)
#define g_chosenPilot GAME_VAR(int, 0x9f8d6c)
#define g_hostGoneMessageFlag GAME_VAR(int, 0x9f941c)   /* word +4 of the type-2 message at g_netHostLeftMessageKind (0x9f9418) that the host sends when it closes the session (dplay_leaveSession, game_postMatch's send_host_leaving, freeCam_keys): 1 while sent; receivers copy it into g_netHostGone and free the session (net_handleMessage case 2) */
#define g_netBlockSize GAME_VAR(u32, 0x9fd940)
#define g_roomListAnswer GAME_VAR(int, 0xa0b34c)   /* the game server's answer to the room-list request (net_receiveGameServerReply): 0xca the list complete (ping thread started), 0x28 reply kinds 2 / 3 (WndProc -> g_searchResult 4: MSG 0x2a SERVER IS BUSY); 0 none */
#define g_serverListCount GAME_VAR(int, 0xa0b368)
#define g_sessionListOpen GAME_VAR(int, 0xa0b384)   /* 1 while the DirectPlay session list is in use (dplay_openConnection sets it); dplay_leaveSession / net_freeSessionList need it */
#define g_serverPingCount GAME_VAR(int, 0xa0d79c)
#define g_glWidth GAME_VAR(int, 0xa0e810)
#define g_glHeight GAME_VAR(int, 0xa0e928)
#define g_replayWrap GAME_VAR(int, 0x4b2a7c)
#define g_arenaJoinRow GAME_VAR(int, 0x4db710)
#define g_arenaServerList GAME_VAR(int, 0x4dbaa8)   /* the arena list shows the lobby server's games (lobby_openConnection sets 1; the LAN rebuild arenaList_rebuild clears it): rows with the lock icon and the ping; while g_arenaLanListBuilt is 0 the page count is g_serverListCount */
#define g_arenaLanListBuilt GAME_VAR(int, 0x4dbac8)   /* the LAN search's list built (arenaList_rebuild: g_sessionList from DirectPlay's sessions, count g_gameCount); cleared when the server is connected or the screen entered */
#define g_typingArenaPassword GAME_VAR(int, 0x4dbacc)
#define g_arenaListClickTimer GAME_VAR(float, 0x4dbaf8)   /* the arena list's double-click window: grows by g_frameTime while g_arenaListClickArmed (a row clicked once); past 20 the click is disarmed; reset to 0 on each row click */
#define g_playerSetupLeft GAME_VAR(int, 0x4dbb68)
#define g_playerSetupRight GAME_VAR(int, 0x4dbb70)
#define g_playerSetupBottom GAME_VAR(int, 0x4dbb74)
#define g_typingArenaPlayerName GAME_VAR(int, 0x4dbbd0)   /* the player's name (g_arenaPlayerName, 16 characters) being typed on the arena lobby's player page */
#define g_unusedEmptySlot0Flag GAME_VAR(int, 0x4dbc80)   /* never set to 1 (0 in the image, .bss): armc_updatePartsPreview / armc_updateWeaponsPreview only test and clear it, so armc_itemSlotRecord(0, 0) there never runs */
#define g_savedMechHead GAME_VAR(int, 0x4dc878)   /* the saved mech's head part (g_savedMechPartIds[0]; chest, arm, leg, booster follow) */
#define g_mechChanged GAME_VAR(int, 0x4dcc58)
#define g_savedMechItemSlot4 GAME_VAR(int, 0x4dcf18)   /* the saved mech's item in slot 4 (g_savedMechSlotItems[0]: an extra item; [1] slot 5, [2] .. [5] weapon slots 0 .. 3): from record byte 5 / the profile's record (armc_state.c: into g_itemSlot4) */
#define g_setupPanelMoving GAME_VAR(int, 0x4dda60)
#define g_arenaRotation GAME_VAR(u8, 0x4ded42)
#define g_menuEyeX GAME_VAR(float, 0x4df024)   /* the menu camera's eye x (g_menuEye[0]; y and z follow) */
#define g_characterTexture GAME_VAR(int, 0x4dfa00)
#define g_panelHovered GAME_VAR(int, 0x680398)
#define g_mapPreviewChanged GAME_VAR(int, 0x680cd0)
#define g_searchResult GAME_VAR(int, 0x76d484)
#define g_mapPreviewTexture GAME_VAR(int, 0x9da324)
#define g_dikF1 GAME_VAR(int, 0x9da440)
#define g_replayRunning GAME_VAR(int, 0x9db990)
#define g_retypePassword GAME_VAR(int, 0x9dced0)
#define g_loginToSend GAME_VAR(int, 0x9dd198)
#define g_rankingPrevPage GAME_VAR(int, 0x9dd1b4)
#define g_rankingPrevSort GAME_VAR(int, 0x9dd300)
#define g_typingLoginPassword GAME_VAR(int, 0x9dd38c)
#define g_rankingLast GAME_VAR(int, 0x9dd7dc)
#define g_typingLoginId GAME_VAR(int, 0x9dd830)
#define g_startTicks GAME_VAR(u32, 0x9dd8e8)
#define g_tunnelFlyingIn GAME_VAR(int, 0x9eeaa8)
#define g_profileRowClicked GAME_VAR(int, 0x9f900c)
#define g_localSlot GAME_VAR(u8, 0x9fd954)   /* the local player's slot (0 .. 15): taken by net_claimLocalSlot or given by the host (net_handleMessage kind 6); sent in every packet (net_sendPacketData); also picks the slot's camera record in g_slotCams (freeCam_mouseLook, freeCam_keys) */
#define g_lobbySocket GAME_VAR(u32, 0xa055f8)
#define g_gameServerSocket GAME_VAR(int, 0xa05630)
#define g_playerListDone GAME_VAR(int, 0xa0b350)
#define g_roomListCount GAME_VAR(int, 0xa0b358)
#define g_playerListCount GAME_VAR(int, 0xa0b35c)
#define g_gameServerPending GAME_VAR(int, 0xa0b364)   /* never set: only ever written 0 (gameList_mouse 0x436020 / 0x43616f, gameList_keys 0x4374e2; .bss); net_handleSystemMessage and net_disconnect test it, so the room's leave packet (0x16) and the room-info sends are never held back by it (the lobby's twin g_lobbyReportsOff is set) */
#define g_connectedServer GAME_VAR(int, 0xa0b380)   /* which server's socket is connected: 200 the lobby (g_lobbySocket), 201 the game server (g_gameServerSocket), 0 none (net_disconnect / net_closeSockets); net_handleSystemMessage sends the hosted record to that one */
#define g_localPlayerData GAME_VAR(u32, 0xa0b428)
#define g_connectionCopy GAME_VAR(void *, 0xa0bab0)
#define g_providerGuid GAME_VAR(const void *, 0xa0bad8)   /* points at the chosen DirectPlay service provider's GUID (g_tcpProviderGuid / ipx / modem / serial by connection kind, dplay_initConnection); the TCP compound address's DPAID_ServiceProvider data; also copied into the session descriptions' guidInstance (dplay_hostSession, dplay_enumSessions) */
#define g_storedConnection GAME_VAR(void *, 0xa0badc)
#define g_hostAddressBlock GAME_VAR(void *, 0xa0baf0)
#define g_pingDataEvent GAME_VAR(void *, 0xa0bb10)
#define g_ptxTablesReady GAME_VAR(int, 0xa0e00c)
#define g_fullScreen GAME_VAR(int, 0xa0e920)
#define g_textWrapX GAME_VAR(int, 0x4ad490)
#define g_textBottom GAME_VAR(int, 0x4ad494)
#define g_lastCrosshair GAME_VAR(int, 0x4b04f8)
#define g_timerFirstCall GAME_VAR(int, 0x4b1048)
#define g_keepCameraAsked GAME_VAR(int, 0x4b2a70)
#define g_hudProjMode GAME_VAR(int, 0x4c4de8)   /* the projection gfx_setMatchProjection set last (1 the 3D one, 0 the HUD's 2D one; -1 none: glWindow_init / glWindow_resize) */
#define g_convertHangul GAME_VAR(int, 0x4d23d0)
#define g_newArenaFragLimit GAME_VAR(u8, 0x4db54c)   /* the new arena form's frag limit (g_newArenaName record +0x24, GameSettings.limit[0]; 0 .. 250) */
#define g_newArenaTimeLimit GAME_VAR(u8, 0x4db54d)   /* the new arena form's time limit (g_newArenaName record +0x25, GameSettings.limit[1]; 0 .. 250) */
#define g_arenaListRefreshTimer GAME_VAR(float, 0x4dbaf0)
#define g_totalWeight GAME_VAR(float, 0x4dc78c)
#define g_itemSlot4 GAME_VAR(int, 0x4dcb18)
#define g_itemSlot5 GAME_VAR(int, 0x4dcb1c)
#define g_colourChanged GAME_VAR(int, 0x4dd074)
#define g_setupPanelPos GAME_VAR(float, 0x4de03c)
#define g_crosshairEdit GAME_VAR(int, 0x4de1cc)   /* the setup page's crosshair (0 .. 7): g_controlsEdit[0x43], the edit copy of g_crosshairSetting (copied in / out with g_controlsEdit) */
#define g_mouseInvert GAME_VAR(int, 0x4df000)
#define g_mouseSensitivity GAME_VAR(int, 0x4df008)
#define g_crosshairSetting GAME_VAR(int, 0x4df00c)
#define g_roomMap GAME_VAR(signed char, 0x4df9e8)
#define g_roomFragLimit GAME_VAR(u8, 0x4df9ec)
#define g_roomTimeLimit GAME_VAR(u8, 0x4df9ed)
#define g_sound3D GAME_VAR(int, 0x4e0c98)   /* axis.cfg's "3dsound": only the setup page and axis.cfg use it (3D SOUND does nothing) */
#define g_menuTunnelTexture GAME_VAR(int, 0x4e0cd0)
#define g_desktopDepth GAME_VAR(int, 0x76d3ec)
#define g_frameCounter40 GAME_VAR(int, 0x9da908)
#define g_lastTime GAME_VAR(double, 0x9db988)
#define g_pixelFormatFilled GAME_VAR(u8, 0x9dbefc)
#define g_directInputMade GAME_VAR(int, 0x9dbf0c)
#define g_rankingPrevRank GAME_VAR(int, 0x9dd328)
#define g_editingRoomName GAME_VAR(int, 0x9dd380)
#define g_openLoginName GAME_VAR(int, 0x9dd4a0)
#define g_rankingLastPage GAME_VAR(int, 0x9dd4b8)   /* the ranking's last page: 999 until a page shows an empty row (ranking_drawTable stores g_rankingPage there); ranking_nextPage stops at it */
#define g_newIdAnswerAwaited GAME_VAR(int, 0x9dd6a4)   /* 1 once the new ID was sent (newId_register): newIdConfirm_update then reads the server's answer (g_newIdAnswer) */
#define g_roomListRefreshTimer GAME_VAR(float, 0x9dd6c0)
#define g_roomPanelsSliding GAME_VAR(int, 0x9dd7d8)   /* 1 while the game room's panels slide in (menuState800_enterGameRoom sets it; room_slideMenu (menu_slide) clears it when g_roomTunnelDepth is past k_setupPanelEnd): the room's keys, clicks and panel hover are off meanwhile */
#define g_rankingFirst GAME_VAR(int, 0x9dd83c)   /* the ranking page's first rank shown ("first ~ last"; page * 10 + 1): written by ranking_enter / ranking_drawTable / ranking_page, never read */
#define g_inputFont GAME_VAR(void *, 0x9dd8e4)
#define g_clockCheckQuits GAME_VAR(int, 0x9dd904)   /* 1: a clock found set back closes the game (sys_checkClockTampering posts WM_CLOSE); 0: only the message and the check restarted. app_init sets 1 before the first check; nothing clears it */
#define g_replayListCount GAME_VAR(int, 0x9eeab8)
#define g_writeMatchLog GAME_VAR(int, 0x9f67ec)
#define g_lastChatLine GAME_VAR(char *, 0x9fd948)   /* the last chat line: a received one as "<name> > <text>" in a GlobalAlloc block (net_formatChatLine), or g_chatLine for one the free camera sent (freeCam_keys); only net_handleMessage reads it (to zero it, the old block not freed) */
#define g_lastChatLineSet GAME_VAR(int, 0x9fd95c)   /* 1 when g_lastChatLine was set (net_handleMessage, freeCam_keys; 0 for an empty line): never read */
#define g_netConnected GAME_VAR(int, 0xa0b2fc)
#define g_lobbyReportsOff GAME_VAR(int, 0xa0b360)   /* 1: nothing about the hosted arena goes to the lobby server (net_handleSystemMessage's player join/leave updates, net_disconnect's leave record): set entering the arena list (lobby_enterArenaList) and on WM_CLOSE; cleared entering a create page (lobby_enterCreate, room_enterCreatePage) */
#define g_gameServerAnswer GAME_VAR(int, 0xa0b378)
#define g_arenaSessionOpen GAME_VAR(int, 0xa0b390)
#define g_serviceProviderCount GAME_VAR(int, 0xa0bac8)
#define g_pingStopEvent GAME_VAR(void *, 0xa0bf1c)
#define g_glColourBits GAME_VAR(int, 0xa0e818)   /* glWindow_init's colourBits, kept for the display mode and the pixel format; the game passes g_videoDepth (match_enter), so it holds that 0 / 1 choice, not a bit count */
#define g_glDepthBits GAME_VAR(int, 0xa0e924)
#define g_defaultColour GAME_VAR(int, 0xa1f220)
#define g_logHook GAME_VAR(void *, 0xae2ec8)
#define g_displayModeChanged GAME_VAR(u8, 0xb12a80)
#define k_cameraSnapDistance GAME_VAR(double, 0x4a93d8)
#define k_clockRate GAME_VAR(float, 0x4a9428)
#define k_setupPanelEnd GAME_VAR(double, 0x4a9440)
#define k_setupPanelTarget GAME_VAR(float, 0x4a9448)
#define k_tenth GAME_VAR(float, 0x4a955c)
#define k_degToRad GAME_VAR(double, 0x4aa290)
#define k_tenthDegreeRad GAME_VAR(double, 0x4aa298)
#define k_clockRate3 GAME_VAR(float, 0x4aa498)
#define g_errorHook GAME_VAR(ErrorHook, 0x4c57cc)
#define g_unlockedLevel GAME_VAR(int, 0x4dc784)
#define g_loadLimit GAME_VAR(float, 0x4dcb0c)   /* the stats panel's load limit: the actor's Player.loadMax (the chest's weightLimit x the pilot's MAX.LOAD factor x the items' loadFactor; armc_readMechStats) */
#define g_cursorBlinkTimer GAME_VAR(float, 0x4de1f0)
#define g_menuCamX GAME_VAR(float, 0x4de344)
#define g_menuCamZ GAME_VAR(float, 0x4de34c)
#define g_crosshairTexture GAME_VAR(int, 0x4e0c8c)
#define g_perfCounterLow GAME_VAR(u32, 0x5ae9c8)   /* the last QueryPerformanceCounter reading's low word (timer_now; the high word in g_timerHigh): never read */
#define g_arenaFileTimeLimit GAME_VAR(int, 0x5b1954)   /* axiswl.dat's timelimit (arena_loadSettings; arena_startFromLauncher takes its low byte into g_arenaTimeLimit) */
#define g_arenaFileSecret GAME_VAR(int, 0x5b1958)
#define g_textureManager GAME_VAR(u32, 0x83a5e0)
#define g_pilotLevelKept GAME_VAR(int, 0x9dd240)
#define g_gameListLoaded GAME_VAR(int, 0x9dd330)
#define g_typingAccountName GAME_VAR(int, 0x9dd348)
#define g_typingAccountPassword GAME_VAR(int, 0x9dd3f8)
#define g_typingAccountRepeat GAME_VAR(int, 0x9dd564)
#define g_roomTunnelDepth GAME_VAR(float, 0x9dd698)
#define g_editingRoomPassword GAME_VAR(int, 0x9dd6a8)
#define g_typingRoomJoinPassword GAME_VAR(int, 0x9dd6c8)
#define g_typingAccountEmail GAME_VAR(int, 0x9dd6cc)
#define g_editOldProc GAME_VAR(u32, 0x9dd868)
#define g_profileMechHead GAME_VAR(int, 0x9f19f8)   /* the profile's mech: its head part (the record's first word; chest .. booster follow to 0x9f1a08) */
#define g_netHostLeftMessageKind GAME_VAR(int, 0x9f9418)   /* the host-leaving game message: its kind word (2; net_resetState) then the flag word g_hostGoneMessageFlag (+4); the host sends it (net_sendMessage) from game_postMatch, freeCam_keys (cancel) and dplay_leaveSession; receivers (net_handleMessage kind 2) put +4 into g_netHostGone and reset the slots */
#define g_slotTakenFlag GAME_VAR(int, 0x9f9838)
#define g_outOfRank GAME_VAR(u8, 0xa052c1)
#define g_serverPort GAME_VAR(u16, 0xa05326)
#define g_pingThreadId GAME_VAR(int, 0xa0d784)
#define g_pingThread GAME_VAR(void *, 0xa0d788)
#define g_musicLength GAME_VAR(u32, 0xa0e018)
#define g_primarySoundBuffer GAME_VAR(void *, 0xa0e808)
#define g_errorLogging GAME_VAR(int, 0xa1efdc)   /* ERROR.TXT logging on (== 1): never written by the game (bss, 0), so the error functions never append to ERROR.TXT */
#define g_cursorX GAME_VAR(int, 0xae2f18)   /* the cursor's x (screen pixels; g_cursorPoint[0], input_getCursorPos) */
#define g_crtErrno GAME_VAR(int, 0xaef35c)   /* the C runtime's errno (set by its own code: EINVAL, ENOENT ..) */
#define g_otherModeWidth GAME_VAR(int, 0xb12a84)
#define g_arenaCorporation GAME_VAR(int, 0x4db580)
#define g_arenaCustomize GAME_VAR(int, 0x4db584)
#define g_sessionFound GAME_VAR(int, 0x4db708)   /* 1 once the session search (WM_TIMER 0x378) found the picked game's session (g_receivedSession): arena_joinAnswer / room_joinAnswer then join it; cleared when a search starts (arena_joinListed, room_joinSession) and after the answer */
#define g_arenaTunnelDepth GAME_VAR(float, 0x4dba68)
#define g_playerSetupTop GAME_VAR(int, 0x4dbb6c)
#define g_unusedArenaFloat GAME_VAR(float, 0x4dbba0)   /* 0.7 stored on entering the player / list / create pages (lobby_enterPlayerScreen, lobby_enterArenaList, lobby_enterCreate); never read */
#define g_bestProgressSolo GAME_VAR(int, 0x4dc1e0)
#define g_bestLevelNet GAME_VAR(int, 0x4dc4b4)
#define g_savedMechChest GAME_VAR(int, 0x4dc87c)
#define g_savedMechArm GAME_VAR(int, 0x4dc880)
#define g_savedMechLeg GAME_VAR(int, 0x4dc884)
#define g_savedMechBooster GAME_VAR(int, 0x4dc888)
#define g_savedMechItemSlot5 GAME_VAR(int, 0x4dcf1c)   /* the saved mech's item in slot 5 (g_savedMechSlotItems[1]; into g_itemSlot5) */
#define g_savedMechWeaponSlot0 GAME_VAR(int, 0x4dcf20)   /* the saved mech's item in weapon slot 0 (g_savedMechSlotItems[2]; into g_mechWeaponSlot0) */
#define g_savedMechWeaponSlot1 GAME_VAR(int, 0x4dcf24)   /* the saved mech's item in weapon slot 1 (g_savedMechSlotItems[3]; into g_mechWeaponSlot1) */
#define g_savedMechWeaponSlot2 GAME_VAR(int, 0x4dcf28)   /* the saved mech's item in weapon slot 2 (g_savedMechSlotItems[4]; into g_mechWeaponSlot2) */
#define g_savedMechWeaponSlot3 GAME_VAR(int, 0x4dcf2c)   /* the saved mech's item in weapon slot 3 (g_savedMechSlotItems[5]; into g_mechWeaponSlot3) */
#define g_fpsFrameCount GAME_VAR(int, 0x4dd0b0)   /* frames counted this second for the fps readout (menu_frame, only while g_showFps; cleared when a second has passed, g_fps = frames / seconds); app_startupLoad zeroes it */
#define g_debugValue GAME_VAR(int, 0x4de6e0)
#define g_mouseWheel GAME_VAR(int, 0x4ded7c)
#define g_musicVolume GAME_VAR(int, 0x4e0c94)
#define g_stereoReverse GAME_VAR(int, 0x4e0c9c)   /* axis.cfg's "stereoreverse": sound_play3D pans the other way */
#define g_roomRecMap GAME_VAR(signed char, 0x5b1b50)
#define g_roomRecMaxPlayers GAME_VAR(signed char, 0x5b1b51)
#define g_roomRecFragLimit GAME_VAR(u8, 0x5b1b54)
#define g_roomRecTimeLimit GAME_VAR(u8, 0x5b1b55)
#define g_netRole GAME_VAR(int, 0x67ef04)
#define g_listAnswered GAME_VAR(int, 0x680bb8)   /* the games heard from so far, the left number of the lists' "n / total" counter (game_page): +1 for each newly answered server (merge, pinged or not), the DirectPlay session count (arenaList_rebuild), 0 when a list is opened or refreshed (lobby_openConnection, arenaGames_mouse / keys, gameList_mouse / keys) */
#define g_cfgLinearFilter GAME_VAR(u32, 0x83a9cc)
#define g_cfgMipmaps GAME_VAR(u32, 0x83a9d0)
#define g_timerRepeatCount GAME_VAR(int, 0x9dbf00)
#define g_accountRank GAME_VAR(int, 0x9dd248)
#define g_rankingPrevValue GAME_VAR(float, 0x9dd384)   /* the ranking: the previous page's last sort value (ranking_fillPage stores it, the next page's first row ties with it); 10,000,000 from ranking_enter / ranking_cycleSort */
#define g_rankingWaiting GAME_VAR(int, 0x9dd6b8)
#define g_unusedRoomFloat GAME_VAR(float, 0x9dd6bc)   /* 0.7 stored on entering each game room page (menuState800_enterGameRoom, room_enterAccountPage, room_enterGameList, room_enterCreatePage, ranking_enter); never read */
#define g_launchMessage GAME_VAR(const char *, 0x9dd8c8)
#define g_replaySelectOpen GAME_VAR(int, 0x9eeab4)   /* the main menu's replay selection dialog is open (F1: mainmenu_processKeys -> replayList_open; closed by replaySelect_ok / its cancel and back keys / its button 7; menuState300_enter clears it): the main menu's keys and clicks go to the dialog, menuState300_frame draws it, mainmenu_drawMenu lights no panel */
#define g_profileMechItem0 GAME_VAR(int, 0x9f1a14)
#define g_profileMechItem1 GAME_VAR(int, 0x9f1a18)
#define g_profileMechItem2 GAME_VAR(int, 0x9f1a1c)
#define g_profileMechItem3 GAME_VAR(int, 0x9f1a20)
#define g_profileMechItem4 GAME_VAR(int, 0x9f1a24)
#define g_profileMechItem5 GAME_VAR(int, 0x9f1a28)
#define g_arenaPacket GAME_VAR(u8 *, 0xa0b310)
#define g_accountPacket GAME_VAR(char *, 0xa0b320)
#define g_roomPacket GAME_VAR(u8 *, 0xa0b328)
#define g_dplayLobby GAME_VAR(void *, 0xa0b398)
#define g_roomMaxPlayers GAME_VAR(u8, 0x4df9e9)
#define g_roomRotation GAME_VAR(u8, 0x4df9ea)
#define g_roomRecRotation GAME_VAR(u8, 0x5b1b52)
#define g_profileMechChest GAME_VAR(int, 0x9f19fc)
#define g_profileMechArm GAME_VAR(int, 0x9f1a00)
#define g_profileMechLeg GAME_VAR(int, 0x9f1a04)
#define g_profileMechBooster GAME_VAR(int, 0x9f1a08)
#define g_mainWindow GAME_VAR(void *, 0x4ded18)
#define g_hInstance GAME_VAR(void *, 0x67ef18)
#define g_textEndX GAME_VAR(int, 0x4d23c8)
#define g_textEndY GAME_VAR(int, 0x4d23cc)
#define g_mapListOpen GAME_VAR(int, 0x4db508)
#define g_typingArenaAddress GAME_VAR(int, 0x4db714)
#define g_joinConnecting GAME_VAR(int, 0x4db8b4)   /* a join's connection is being waited for (arena_joinListed / room_joinSession set it with the 2 s timer 0x378): the CONNECTING TO THE GAME SERVER / PLEASE WAIT box with CANCEL (arena_drawGameList, gameList_draw); its CANCEL/keys stop the join (arena_joinAnswer, room_joinAnswer, gameList_stopJoin, arenaJoinBox_clicks clear it) */
#define g_arenaJoinNeedsPassword GAME_VAR(int, 0x4db8bc)
#define g_armcPreview GAME_VAR(int, 0x4dbc68)
#define g_armcSessionMade GAME_VAR(int, 0x4dc54c)
#define g_armcState GAME_VAR(int, 0x4dc790)
#define g_coloursChanged GAME_VAR(int, 0x4dca98)
#define g_armcChanged GAME_VAR(int, 0x4dcc64)
#define g_loadStep GAME_VAR(int, 0x4dda34)
#define g_replayZoomTime GAME_VAR(float, 0x4dda48)   /* the main menu's zoom into a chosen replay (while g_replayShowOn on screen 300): g_frameTime added each frame (menu_frame); at 100 the replay starts (screen 9999, g_replayRunning); cleared by menuState100_intro, menuState210_enter, game_returnTo*; menuState210_frame draws nothing while it is above 0 */
#define g_bindPage GAME_VAR(int, 0x4ddce8)
#define g_setupCameraMode GAME_VAR(int, 0x4ddcec)   /* the setup screen's camera (setup_camera): 1 going to the open tab's menu point (tab_opened), 0 going home (the page closed: OK / back / cancel), 2 arrived (page shown, or home); the tunnel's alpha eases to 0.3 in 1 and 0.5 in 0 (setup_drawTunnel) */
#define g_bindWaiting GAME_VAR(int, 0x4dddc8)
#define g_setupEffectVolume GAME_VAR(int, 0x4dde98)   /* the sound tab's EFFECT SOUND volume being edited (0 .. 100; g_soundEdited[0]); OK makes it g_soundVolume (axis.cfg set_sound effectvolume) */
#define g_whiteFade GAME_VAR(float, 0x4deb74)   /* the white fade over the screen while the menus are left for a match (+0.015 x g_frameTime a frame, drawn alpha capped at 1): room_drawWhiteFade (game room) and menu_drawWhiteFade (arena lobby, main menu: menuState300_frame); cleared by arena_camera, room_camera, skirmish_camera */
#define g_tunnelPulseStep GAME_VAR(float, 0x4df010)
#define g_menuScaleY GAME_VAR(float, 0x4df014)
#define g_freeCamZoom GAME_VAR(int, 0x4e0464)   /* the free camera's zoom (Z in freeCam_keys toggles 1 / 2): 1 narrows g_viewAngle by 5 each menu frame down to 5, 2 widens it by 5 up to 45 (menu_frame, after SwapBuffers); other values leave it */
#define g_projMode GAME_VAR(int, 0x5ae9bc)
#define g_mapCount GAME_VAR(int, 0x67ef00)   /* mapinfo.dat's map count (data_loadMapInfo); g_mapNames / g_mapAbouts hold that many */
#define g_leavingForMatch GAME_VAR(int, 0x67ef14)   /* 1 while the menus are being left for a match: set when an arena / room game is hosted or joined (lobby_hostArenaTcpIp, lobby_hostArenaIpx, arena_connectionOutcome, arena_joinAnswer, room_hostingStep, room_clicks) or a skirmish / mission starts (menu_records.c:481); the menu tunnel then runs 2200-step rings, the white fade (g_whiteFade) runs, the top pages ignore keys / clicks and menu_slide moves to screen 9999. Cleared at start-up (app_startupLoad), on a host failure (lobby_hostArenaIpx), and by leave_game on the way back */
#define g_menuCameraLookZ GAME_VAR(float, 0x680380)   /* the menu camera's look-at point: z (gluLookAt centre z; g_menuCameraLook / g_menuCameraLookY the x / y) */
#define g_menuScaleX GAME_VAR(float, 0x680bac)
#define g_arenaUpdateNotice GAME_VAR(int, 0x907b2c)
#define g_tunnelRings GAME_VAR(int, 0x9dae10)
#define g_rankingSort GAME_VAR(int, 0x9dd1d0)
#define g_roomRefreshing GAME_VAR(int, 0x9dd3fc)
#define g_roomJoinStarted GAME_VAR(int, 0x9dd56c)   /* a join of the picked game was asked in the game room's list (gameList_mouse / keys set it after room_askJoinPassword); gameList_pageFrame then joins (room_joinSession) or checks the typed password; cleared by room_joinSession, a wrong password and room_enterGameList */
#define g_roomJoinNeedsPassword GAME_VAR(int, 0x9dd6b4)
#define g_newIdConfirmChoice GAME_VAR(int, 0x9dd6c4)
#define g_roomState GAME_VAR(int, 0x9dd834)
#define g_roomUpdateNotice GAME_VAR(int, 0x9dd850)
#define g_replaySelectFirst GAME_VAR(int, 0x9dd92c)
#define g_missionsState GAME_VAR(int, 0x9ef1f0)
#define g_missionsPage GAME_VAR(int, 0x9ef1f8)   /* the mission screen's (900) page: 10 the list (missions_frameList), 20 the mission settings (mission_loadBriefing); -1 once its camera is home again (menu_camera2's third flag, as g_skirmishLeft for the skirmish screen) */
#define g_briefingEnd GAME_VAR(int, 0x9ef200)
#define g_briefingDone GAME_VAR(int, 0x9f105c)
#define g_briefingPage GAME_VAR(int, 0x9f1060)
#define g_selectedCharacter GAME_VAR(int, 0x9f1818)
#define g_profileFrameStep GAME_VAR(float, 0x9f8c48)
#define g_profileCount GAME_VAR(int, 0x9f9008)
#define g_dplay GAME_VAR(void *, 0xa0b404)
#define g_connectionKind GAME_VAR(int, 0xa0b418)
#define g_directSound GAME_VAR(void *, 0xa0e804)
#define g_soundOn GAME_VAR(int, 0xa0e80c)
#define g_ptxBitPos GAME_VAR(int, 0xa21704)
#define g_ptxLastDc GAME_VAR(int, 0xaa268c)
#define g_roomSearching GAME_VAR(int, 0x9dd6a0)
#define k_tenthsToDegrees GAME_VAR(float, 0x4a93ec)
#define k_oneOver180 GAME_VAR(double, 0x4a9540)
#define k_pi GAME_VAR(double, 0x4a9548)
#define g_receivedSession GAME_VAR(const u8 *, 0x4dbbf8)
#define g_setupMusicVolume GAME_VAR(int, 0x4dde9c)   /* the sound tab's BGM switch being edited (g_soundEdited[1]): 0 off / 100 on (setup_soundTabClicks button 5 flips it at 50); OK makes it g_musicVolume (axis.cfg set_sound musicvolume) */
#define g_roomInfoPacket GAME_VAR(u8 *, 0xa0b32c)
#define g_roomLeavePacket GAME_VAR(u8 *, 0xa0b330)
#define g_arenaListClickArmed GAME_VAR(int, 0x4db71c)
#define g_serverSearching GAME_VAR(int, 0x4db854)
#define g_lanSearchStarted GAME_VAR(int, 0x4dba84)   /* a local-network search has opened a DirectPlay session (arenaGames_mouse / keys button 0: dplay_openConnection(1, NULL), g_lanSearch); left (dplay_leaveSession) before another search or a join (arena_joinListed) */
#define g_connectionAwaited GAME_VAR(int, 0x4dba88)
#define g_lobbyJoinStarted GAME_VAR(int, 0x4dbbec)
#define g_arenaLobbyState GAME_VAR(int, 0x4dbbf4)
#define g_arenaGameSetUp GAME_VAR(int, 0x4ded54)
#define g_menuCameraLookY GAME_VAR(float, 0x68037c)   /* the menu camera's look-at point: y (gluLookAt centre y) */
#define g_gameListClickTimer GAME_VAR(float, 0x9dcd40)
#define g_gameListClickArmed GAME_VAR(int, 0x9dd34c)
#define g_dikMouse1 GAME_VAR(int, 0x4de73c)
#define g_dikF11 GAME_VAR(int, 0x4df8d0)
#define g_dikNone GAME_VAR(int, 0x4df8e4)
#define g_dikPageUp GAME_VAR(int, 0x4df90c)
#define g_dikRAlt GAME_VAR(int, 0x4df9fc)
#define g_dik1 GAME_VAR(int, 0x4e0468)
#define g_dik2 GAME_VAR(int, 0x4e046c)
#define g_dik3 GAME_VAR(int, 0x4e0470)
#define g_dik4 GAME_VAR(int, 0x4e0874)
#define g_dikA GAME_VAR(int, 0x4e0cd4)
#define g_dikC GAME_VAR(int, 0x4e0cdc)
#define g_dikD GAME_VAR(int, 0x4e0ce0)
#define g_dikG GAME_VAR(int, 0x4e14ec)
#define g_dikI GAME_VAR(int, 0x4e14f4)
#define g_dikJ GAME_VAR(int, 0x4e14f8)
#define g_dikL GAME_VAR(int, 0x4e1504)
#define g_dikM GAME_VAR(int, 0x4e1508)
#define g_dikN GAME_VAR(int, 0x4e150c)
#define g_dikO GAME_VAR(int, 0x4e1510)
#define g_dikP GAME_VAR(int, 0x4e1514)
#define g_dikR GAME_VAR(int, 0x4e151c)
#define g_dikS GAME_VAR(int, 0x4e1524)
#define g_dikT GAME_VAR(int, 0x4e1528)
#define g_dikW GAME_VAR(int, 0x4e1538)
#define g_dikX GAME_VAR(int, 0x4e153c)
#define g_dikSpace GAME_VAR(int, 0x5b1da8)
#define g_dikLShift GAME_VAR(int, 0x67ef24)
#define g_dikZ_2 GAME_VAR(int, 0x680388)
#define g_dikTab GAME_VAR(int, 0x680390)
#define g_dikEscape GAME_VAR(int, 0x6803a0)
#define g_dikLCtrl GAME_VAR(int, 0x6803a8)
#define g_dikDown GAME_VAR(int, 0x76d330)
#define g_dikDelete GAME_VAR(int, 0x76d414)
#define g_dikMouse2 GAME_VAR(int, 0x76d424)
#define g_dikEscape_2 GAME_VAR(int, 0x76d48c)
#define g_dikWheelDown GAME_VAR(int, 0x76d490)   /* 0xfe: the wheel turned down / towards the user (key name "WHEEL-DOWN"; input_isDown: g_mouseWheel > 0) */
#define g_dikWheelUp GAME_VAR(int, 0x9da490)   /* 0xfd: the wheel turned up / away from the user (key name "WHEEL-UP"; input_isDown: g_mouseWheel < 0) */
#define g_dikLAlt GAME_VAR(int, 0x9da4a0)
#define g_dikRCtrl GAME_VAR(int, 0x9dad8c)
#define g_dikLeft GAME_VAR(int, 0x9dae14)
#define g_dikEnter GAME_VAR(int, 0x9dae70)
#define g_dikUp GAME_VAR(int, 0x9db0a0)
#define g_dikRShift GAME_VAR(int, 0x9db0ac)
#define g_dikRight GAME_VAR(int, 0x9db974)
#define g_gameRunning GAME_VAR(int, 0x4b2790)
#define g_viewFov GAME_VAR(float, 0x4c4dec)
#define g_viewNear GAME_VAR(float, 0x4c4df0)
#define g_viewFar GAME_VAR(float, 0x4c4df4)
#define g_catalogueFile GAME_VAR(const char *, 0x4d05a4)
#define g_hostErrorBox GAME_VAR(int, 0x4db55c)
#define g_editingNewArenaName GAME_VAR(int, 0x4dbab0)
#define g_joinPollTicks GAME_VAR(int, 0x4dbb10)   /* ticks of the join timer 0x378 (2 s; WndProc: dplay_listSessions each tick until a session arrives); past 30 the join gives up (g_joinTimedOut set). Zeroed when a join starts or ends: arena_joinListed, room_joinSession, arena_joinAnswer, room_joinAnswer, gameList_stopJoin, gameList_keys, arenaGames_keys, arenaJoinBox_clicks */
#define g_armcUnusedFlag GAME_VAR(int, 0x4dc788)
#define g_armcLeaving GAME_VAR(int, 0x4dcf10)
#define g_progressWentUp GAME_VAR(int, 0x4dcf34)
#define g_watchChatOpen GAME_VAR(int, 0x4de6fc)
#define g_roomGameMode GAME_VAR(signed char, 0x4df9eb)   /* the room form's game mode (GameSettings.mode at g_roomSettingsName + 0x23; 0 .. 9, the mode names MSG(791) + mode * 0x80) */
#define g_roomRecGameMode GAME_VAR(signed char, 0x5b1b53)   /* the registry record's game mode (GameSettings.mode at g_roomRecName + 0x23); roomSettings_page resets it to 0 outside 0 .. 11 */
#define g_matchRunning GAME_VAR(int, 0x5b1dac)
#define g_cfgSimpleMenu GAME_VAR(int, 0x83a9d8)
#define g_pilotExpKept GAME_VAR(int, 0x9dd244)
#define g_pilotKillsKept GAME_VAR(int, 0x9dd254)
#define g_accountNotice GAME_VAR(int, 0x9dd354)
#define g_pilotLevel GAME_VAR(int, 0x9dd5d8)
#define g_pilotExp GAME_VAR(int, 0x9dd5dc)
#define g_pilotKills GAME_VAR(int, 0x9dd5ec)
#define g_roomAwaitingServer GAME_VAR(int, 0x9dd6d4)
#define g_skirmishPreviewDue GAME_VAR(int, 0x9f63b0)
#define g_chatTyping GAME_VAR(int, 0x9f67e8)   /* set when the match's chat line opens (chat_textField); cleared by chat_endTyping only when the line is not empty (an empty line leaves it 1); never read */
#define g_matchLogWritten GAME_VAR(int, 0x9f67f0)
#define g_matchEndedByUser GAME_VAR(int, 0x9f67f4)
#define g_matchEndedByServer GAME_VAR(int, 0x9f67f8)
#define g_profileLogInAsked GAME_VAR(int, 0x9f6840)   /* LOG IN chosen on the profile screen (button 2, key I, or the chosen row clicked twice: page 4, profile_logIn; the pilot grid is page 6); profile_logIn does nothing without it; cleared only on entering the screen (menuState210_enter) */
#define g_profileRowClickTime GAME_VAR(float, 0x9f8f18)   /* the time (1/60 s, g_frameTime) since a profile row was clicked (g_profileRowClicked); past 20 the click is forgotten; a second click on the same row within it opens the pilot grid (a double click) */
#define g_netHostGone GAME_VAR(int, 0x9fd94c)   /* the network game is over: set when slot 0 (the host) is freed (net_freeSlotsOf), when the TCP sockets are closed (net_closeSockets), or to the word at +4 of a type 2 game message (net_handleMessage); cleared by net_resetState / match_startRound. Read by net_hostGone (0x4a86e0: the match quits) and net_handleSystemMessage (no per-player slot freeing once set) */
#define g_rankReplyIn GAME_VAR(int, 0xa0b354)
#define g_newIdAnswer GAME_VAR(int, 0xa0b37c)   /* the game server's answer to request 15, the new ID's registration (newId_register): 0x21 accepted, 0x1e refused (message 0x22), 0x2a the update notice, 0x28 no answer; newIdConfirm_update reads and clears it */
#define g_mapMissing GAME_VAR(int, 0xa0ea94)
#define g_errorCleanupHook GAME_VAR(int, 0xa1efe8)
#define g_displayModeLeft GAME_VAR(u8, 0xb12a81)
#define g_otherModeHeight GAME_VAR(int, 0xb12a88)
#define k_69_9 GAME_VAR(double, 0x4a93e0)
#define k_100f GAME_VAR(float, 0x4a93f4)
#define k_10f GAME_VAR(float, 0x4a9418)
#define k_3600f GAME_VAR(float, 0x4a94c8)
#define k_10000f GAME_VAR(float, 0x4a9708)
#define g_mapListMade GAME_VAR(int, 0x4db510)
#define g_editingNewArenaTimeLimit GAME_VAR(int, 0x4db518)
#define g_typingArenaJoinPassword GAME_VAR(int, 0x4db70c)
#define g_editingNewArenaFragLimit GAME_VAR(int, 0x4db850)
#define g_lobbyPanelsSliding GAME_VAR(int, 0x4db85c)   /* the arena lobby's top menu is sliding in: set by menuState400_enter; while set lobby_slidePanels (menu_slide) eases g_lobbySlideEase and moves g_arenaTunnelDepth, clearing it at the end (depth -1650), and lobbyTop_drawMenu hovers no panel. lobby_enterPlayerScreen / lobby_enterArenaList / lobby_enterCreate clear it */
#define g_armcCameraTravelling GAME_VAR(int, 0x4dc868)   /* the ARM CENTER's camera is between the menus and the ARM CENTER: set by armc_open and while it flies home (armc_cameraStep, state 0), cleared when it arrives (state 2); while set (and not from the lobby, g_armcFrom 2) menuState700_armCenter draws the menus' background */
#define g_ladderLevel GAME_VAR(int, 0x4de71e)
#define g_mouseWheelTurned GAME_VAR(int, 0x4ded70)
#define g_mouse2Down GAME_VAR(int, 0x4ded98)
#define g_camPoint0X GAME_VAR(float, 0x4df870)
#define g_camPoint0Y GAME_VAR(float, 0x4df874)
#define g_camPoint0Z GAME_VAR(float, 0x4df878)
#define g_camAim0X GAME_VAR(float, 0x76d388)
#define g_camAim0Y GAME_VAR(float, 0x76d38c)
#define g_camAim0Z GAME_VAR(float, 0x76d390)
#define g_editingEmail GAME_VAR(int, 0x9dd304)
#define g_editingPasswordRepeat GAME_VAR(int, 0x9dd378)
#define g_editingAccountPassword GAME_VAR(int, 0x9dd37c)
#define g_pilotPower GAME_VAR(float, 0x9dd5e4)
#define g_editingOldPassword GAME_VAR(int, 0x9dd69c)
#define g_editLineDone GAME_VAR(int, 0x9dd900)
#define g_penFontTexture GAME_VAR(int, 0xa106ac)
#define k_0f GAME_VAR(float, 0x4a93e8)
#define k_2f GAME_VAR(float, 0x4a93fc)
#define k_0_25f GAME_VAR(float, 0x4a941c)
#define k_1f GAME_VAR(float, 0x4a9424)
#define k_0_5f GAME_VAR(float, 0x4a942c)
#define k_20f GAME_VAR(float, 0x4a944c)
#define k_360f GAME_VAR(float, 0x4a9460)
#define k_m1f GAME_VAR(float, 0x4a9474)
#define k_4f GAME_VAR(float, 0x4a947c)
#define k_550f GAME_VAR(float, 0x4a9498)
#define k_m2f GAME_VAR(float, 0x4a94a8)
#define k_0_01 GAME_VAR(double, 0x4a94c0)
#define k_60 GAME_VAR(double, 0x4a94d0)
#define k_60f GAME_VAR(float, 0x4a94dc)
#define k_1 GAME_VAR(double, 0x4a94e0)
#define k_m0_5f GAME_VAR(float, 0x4a94f4)
#define k_0_9f GAME_VAR(float, 0x4a9508)
#define k_50f GAME_VAR(float, 0x4a9560)
#define k_0_00390625f GAME_VAR(float, 0x4a957c)
#define k_2000000 GAME_VAR(double, 0x4a9580)
#define k_0_3 GAME_VAR(double, 0x4a9598)
#define k_49f GAME_VAR(float, 0x4a95a0)
#define k_m1100f GAME_VAR(float, 0x4a95a4)
#define k_23 GAME_VAR(double, 0x4a95a8)
#define k_25 GAME_VAR(double, 0x4a95b0)
#define k_3_6f GAME_VAR(float, 0x4a95b8)
#define k_m100f GAME_VAR(float, 0x4a95bc)
#define k_m1000f GAME_VAR(float, 0x4a95c0)
#define k_1_4 GAME_VAR(double, 0x4a95e0)
#define k_27_7778f GAME_VAR(float, 0x4a9750)
#define k_1em8f GAME_VAR(float, 0x4aa268)
#define k_1800f GAME_VAR(float, 0x4aa288)
#define k_1_40625f GAME_VAR(float, 0x4aa41c)
#define k_0_0078125f GAME_VAR(float, 0x4aa420)
#define k_1em8 GAME_VAR(double, 0x4aa458)
#define g_tunnelStep GAME_VAR(int, 0x4b2a74)
#define g_tunnelStepF GAME_VAR(float, 0x4b2a78)
#define g_musicVolumeSetting GAME_VAR(int, 0x4b42dc)   /* written by music_setVolumeSetting only; never read */
#define g_hangulVowelGlyph GAME_VAR(int, 0x4d23d4)
#define g_hangulTailGlyph GAME_VAR(int, 0x4d23dc)
#define g_hangulLeadGlyph GAME_VAR(int, 0x4d60e0)
#define g_newArenaFormLeft GAME_VAR(int, 0x4dbb00)
#define g_newArenaFormTop GAME_VAR(int, 0x4dbb04)
#define g_newArenaFormRight GAME_VAR(int, 0x4dbb08)
#define g_newArenaFormBottom GAME_VAR(int, 0x4dbb0c)
#define g_armcLevel GAME_VAR(int, 0x4dc870)
#define g_boosterCount GAME_VAR(int, 0x4dc890)   /* the booster list's length (g_boosterList; armc_buildPartLists) */
#define g_messageBoxArgs GAME_VAR(va_list, 0x4dd0b4)
#define g_setupSound3D GAME_VAR(int, 0x4ddea0)
#define g_setupStereoReverse GAME_VAR(int, 0x4ddea4)
#define g_showCmd GAME_VAR(int, 0x4deb54)
#define g_mouse3Down GAME_VAR(int, 0x4ded9c)
#define g_keyChat GAME_VAR(int, 0x4defa8)
#define g_keyGameMenu GAME_VAR(int, 0x4defc8)
#define g_keyGameMenu2 GAME_VAR(int, 0x4defcc)
#define g_screenCentreX GAME_VAR(int, 0x4e1520)
#define g_texture64x64Vtable GAME_VAR(u32, 0x4e1878)
#define g_timerHigh GAME_VAR(u32, 0x5ae9cc)
#define g_texture128x64Vtable GAME_VAR(u32, 0x5b1db8)
#define g_screenCentreY GAME_VAR(int, 0x680394)
#define g_texture256x64Vtable GAME_VAR(u32, 0x680cd8)
#define g_menuLookHomeX GAME_VAR(float, 0x76d3f8)   /* the menu camera's home look-at point (g_menuLookHome[0]) */
#define g_menuLookHomeY GAME_VAR(float, 0x76d3fc)
#define g_menuLookHomeZ GAME_VAR(float, 0x76d400)
#define g_editFieldLength GAME_VAR(int, 0x76d418)
#define g_texture128x128Vtable GAME_VAR(u32, 0x76d498)
#define g_texture256x256Vtable GAME_VAR(u32, 0x83a9e0)
#define g_skirmishInfoCount GAME_VAR(int, 0x90d1d8)
#define g_texture256x128Vtable GAME_VAR(u32, 0x90d1e0)
#define g_menuEyeHomeX GAME_VAR(float, 0x9db090)   /* the menu camera's home position (g_menuEyeHome[0]) */
#define g_menuEyeHomeY GAME_VAR(float, 0x9db094)
#define g_menuEyeHomeZ GAME_VAR(float, 0x9db098)
#define g_roomFormLeft GAME_VAR(int, 0x9dd1b8)
#define g_roomFormTop GAME_VAR(int, 0x9dd1bc)
#define g_roomFormRight GAME_VAR(int, 0x9dd1c0)
#define g_roomFormBottom GAME_VAR(int, 0x9dd1c4)
#define g_pilotPowerKept GAME_VAR(float, 0x9dd24c)
#define g_pilotDeathsKept GAME_VAR(int, 0x9dd258)
#define g_gameListRefreshClicked GAME_VAR(int, 0x9dd4bc)   /* set when the game room's list request goes out (REFRESH, button 1 = MSG(388) '$[0] REFRESH', or the R key; gameList_open succeeded); cleared by room_enterGameList; never read */
#define g_pilotDeaths GAME_VAR(int, 0x9dd5f0)
#define g_pilotKillRate GAME_VAR(float, 0x9dd5f4)
#define g_languageId GAME_VAR(u16, 0x9dd858)
#define g_clockCheckSeconds GAME_VAR(int, 0x9dd860)
#define g_clockCheckTick GAME_VAR(u32, 0x9dd8e0)
#define g_clockCheckTickSeconds GAME_VAR(u32, 0x9dd8ec)
#define g_progressSeen GAME_VAR(int, 0x9f62fc)   /* the campaign progress the skirmish screen has already announced: set from g_progress when a profile is made current (profile_makeCurrent); menuState500_enter raises the briefing (g_skirmishNewPartsNotice) when g_progress has passed it, then catches it up */
#define g_skirmishChosen GAME_VAR(int, 0x9f6328)
#define g_netClaimedSlot GAME_VAR(int, 0x9f9424)
#define g_lobbyReplyKind GAME_VAR(u32, 0xa052aa)
#define g_serverReplyKind GAME_VAR(int, 0xa05306)
#define g_netAccountRequest GAME_VAR(char *, 0xa055e0)
#define g_gameServerReplyKind GAME_VAR(u32, 0xa0b2e8)
#define g_lobbyKeepAlive GAME_VAR(char *, 0xa0b304)   /* the 16-byte buffer of packet 23 (0x17), the lobby keep-alive sent on timer 0x29a while hosting an arena (g_arenaLobbyState 2: WndProc / editField_editProc): the hosted arena's address (g_arenaPacket's ServerRecord.address) */
#define g_gameServerKeepAlive GAME_VAR(char *, 0xa0b308)   /* the 16-byte buffer of packet 24 (0x18), the game server keep-alive sent on timer 0x115c while g_roomConnected: this machine's address (g_localAddress) */
#define g_netKindBuffer GAME_VAR(u32 *, 0xa0b30c)
#define g_arenaInfoPacket GAME_VAR(u8 *, 0xa0b314)
#define g_arenaListRequest GAME_VAR(u32 *, 0xa0b31c)   /* the 4-byte packet 13 to the lobby (lobby_openConnection writes 0x180001): asks for the arena list (net_send 13 clears g_serverList first; net_recv 13 -> net_receiveLobbyReply adds the servers) */
#define g_netRankingBuffer GAME_VAR(int *, 0xa0b324)
#define g_netPlayerRecordPacket GAME_VAR(u8 *, 0xa0b338)
#define g_netLeaveBuffer GAME_VAR(char *, 0xa0b33c)
#define g_netSelectionPacket GAME_VAR(u8 *, 0xa0b340)
#define g_netAccountBuffer GAME_VAR(char *, 0xa0b344)
#define g_lobbyStatus GAME_VAR(int, 0xa0b370)
#define g_gameServerStatus GAME_VAR(int, 0xa0b374)
#define g_arenaJoinTimer GAME_VAR(u32, 0xa0bad0)   /* the id SetTimer(0x378, 2000 ms) returns when a join's session search starts: the arena's (arena_joinListed) and the game room's (room_joinSession); never read (WndProc's WM_TIMER 0x378 kills the timer by its id) */
#define g_dpTimeout GAME_VAR(u32, 0xa0bb00)
#define g_dpMaxBufferSize GAME_VAR(u32, 0xa0bb04)
#define g_dpMaxQueueSize GAME_VAR(u32, 0xa0bb08)
#define g_musicEndHigh GAME_VAR(int, 0xa0e01c)
#define g_mciCallback GAME_VAR(u32, 0xa1efc8)
#define g_mciFrom GAME_VAR(u32, 0xa1efcc)
#define g_mciTo GAME_VAR(u32, 0xa1efd0)
#define g_mciDevice GAME_VAR(u32, 0xa1efd8)
#define g_cursorPosY GAME_VAR(int, 0xae2f1c)
#define k_armcDistance GAME_VAR(u32, 0x4a9454)
#define k_armcDistanceRoom GAME_VAR(u32, 0x4a9458)
#define g_newArenaMap GAME_VAR(signed char, 0x4db548)
#define g_newArenaMaxPlayers GAME_VAR(signed char, 0x4db549)
#define g_newArenaRotation GAME_VAR(signed char, 0x4db54a)
#define g_newArenaMode GAME_VAR(signed char, 0x4db54b)
#define g_newArenaPassword GAME_VAR(int, 0x4db54e)
#define g_armcBuildTexture GAME_VAR(int, 0x4dcc88)
#define g_keyForward GAME_VAR(int, 0x4def00)
#define g_keyBackward GAME_VAR(int, 0x4def08)
#define g_keyStepLeft GAME_VAR(int, 0x4def10)
#define g_keyStepRight GAME_VAR(int, 0x4def18)
#define g_camPoint1X GAME_VAR(float, 0x4df880)
#define g_camPoint1Z GAME_VAR(float, 0x4df888)
#define g_camPoint2X GAME_VAR(float, 0x4df890)
#define g_camPoint2Y GAME_VAR(float, 0x4df894)
#define g_camPoint2Z GAME_VAR(float, 0x4df898)
#define g_arenaFileMap GAME_VAR(int, 0x5b1944)   /* the arena file's map (atoi; arena_startFromLauncher takes the low byte into g_arenaMap) */
#define g_arenaFilePlayers GAME_VAR(int, 0x5b1948)
#define g_arenaFileGameType GAME_VAR(int, 0x5b194c)
#define g_arenaFileFragLimit GAME_VAR(int, 0x5b1950)
#define g_camAim1X GAME_VAR(float, 0x76d398)
#define g_camAim1Y GAME_VAR(float, 0x76d39c)
#define g_camAim1Z GAME_VAR(float, 0x76d3a0)
#define g_camAim2X GAME_VAR(float, 0x76d3a8)
#define g_camAim2Y GAME_VAR(float, 0x76d3ac)
#define g_camAim2Z GAME_VAR(float, 0x76d3b0)
#define g_pilotGamesKept GAME_VAR(int, 0x9dd250)
#define g_pilotGames GAME_VAR(int, 0x9dd5e8)
#define g_menuLookKeptX GAME_VAR(float, 0x9dd918)   /* the menu camera's look-at point (g_menuLook) kept by menuTunnel_advance (camera_keep) and put back a ring further when a tunnel move ends; X (with g_menuLookKeptY / Z; objects.h g_menuLookKept) */
#define g_menuLookKeptY GAME_VAR(float, 0x9dd91c)
#define g_menuLookKeptZ GAME_VAR(float, 0x9dd920)
#define g_menuEyeKeptX GAME_VAR(float, 0x9dd930)   /* the menu camera's position (g_menuEye) kept by menuTunnel_advance (camera_keep; EYE_KEPT), X (with Y / Z; objects.h g_menuEyeKept) */
#define g_menuEyeKeptY GAME_VAR(float, 0x9dd934)
#define g_menuEyeKeptZ GAME_VAR(float, 0x9dd938)
#define g_mainMenuFrames GAME_VAR(int, 0x9eeab0)
#define g_matchChatCaretY GAME_VAR(int, 0x9f63c4)
#define g_matchChatCaretX GAME_VAR(int, 0x9f63c8)
#define g_textHitBottom GAME_VAR(int, 0x4d7348)   /* 1 once an ASCII text pass (text_ascii8Pass / 16 / 32) stopped at g_textBottom; the briefing takes it as its page being full: briefing_typeOut stops typing and its cursor, briefing_nextPage only then turns the page, the NEXT button is lit (mission_list.c). Cleared by app_startupLoad, mission_loadBriefing, briefing_nextPage / prevPage */
#define g_armcSlot GAME_VAR(int, 0x4dbe48)
#define g_armcFrom GAME_VAR(int, 0x4dc24c)
#define g_armcCursor GAME_VAR(int, 0x4dc77c)
#define g_armcPageRight GAME_VAR(int, 0x4dcc98)   /* the ARM CENTER window's right edge (630, armc_open); with g_armcPageLeft / Top / Bottom the window every page draws in. The colour sliders start 184 units left of it (armc_colours.c) */
#define g_armcSpin GAME_VAR(int, 0x4dceac)
#define g_unusedArmcViewCountdown GAME_VAR(float, 0x4dcfd8)   /* float; set to 1 on each change of the part in view (armc_open, armc_partsPageClicks, armc_partsPageKeys, armc_readPartPanels), then lowered by 0.1 a frame time down to -2 (menuState700_armCenter); nothing else reads it */
#define g_setupPressedClock GAME_VAR(float, 0x4ddb98)
#define g_setupPressed GAME_VAR(int, 0x4dde90)
#define g_setupTunnelAlpha GAME_VAR(float, 0x4de038)
#define g_bindRow GAME_VAR(int, 0x4de040)
#define g_menuEyeY GAME_VAR(float, 0x4df028)   /* g_menuEye[1]: the menu camera's position, y (float) */
#define g_menuEyeZ GAME_VAR(float, 0x4df02c)   /* g_menuEye[2]: the menu camera's position, z (along the tunnel; float) */
#define g_gameCount GAME_VAR(int, 0x67ef30)
#define g_menuTunnel GAME_VAR(TunnelRing *, 0x67fb3c)
#define g_briefingStart GAME_VAR(int, 0x9eeba4)
#define g_briefingSource GAME_VAR(u8 *, 0x9ef1ec)
#define g_briefingShown GAME_VAR(int, 0x9ef1f4)
#define g_missionCount GAME_VAR(int, 0x9ef2c0)
#define g_missionPicked GAME_VAR(int, 0x9f16a4)
#define g_missionsWindowLeft GAME_VAR(int, 0x9f16a8)   /* the mission screen's window, left (10; with g_missionsWindowTop, g_missionsWindowRight 0x276, g_missionsWindowBottom 0x1cc): the mission list, its briefing and the skirmish settings all draw in it */
#define g_missionsWindowTop GAME_VAR(int, 0x9f16ac)
#define g_briefingClock GAME_VAR(float, 0x9f16b8)
#define g_skirmishShown GAME_VAR(int, 0x9f63b4)
#define g_profileFrameAlpha GAME_VAR(float, 0x9f8f08)
#define g_netQueueOnline GAME_VAR(int, 0xa0b388)
#define g_bitStream GAME_VAR(const u8 *, 0xa61708)
#define g_imp_wsprintfA GAME_VAR(void *, 0x4a92f0)
#define g_componentDatPath GAME_VAR(const char *, 0x4b4414)   /* -> "Data/Component.dat" (0x4b4418): the component catalogue's path; actor_processFrame passes it to the catalogue load (0x473780) when the local player's actor passes from dying to dead */
#define g_insertCdMessage GAME_VAR(const char *, 0x4b4568)
#define g_unusedKeyTable2Word0 GAME_VAR(int, 0x4d1fb0)
#define g_unusedKeyTable2Flags GAME_VAR(u16, 0x4d1fba)
#define g_unusedKeyTable2Word1 GAME_VAR(int, 0x4d1fbc)
#define g_unusedKeyTable2Word2 GAME_VAR(int, 0x4d1fc0)
#define g_mapEntry22On GAME_VAR(int, 0x4d95b8)
#define g_mapEntry23On GAME_VAR(int, 0x4d95c0)
#define g_mapEntry24On GAME_VAR(int, 0x4d95c8)
#define g_arenaJoinPassword GAME_VAR(int, 0x4db520)
#define g_arenaJoinPassword4 GAME_VAR(int, 0x4db524)
#define g_newArenaPassword4 GAME_VAR(int, 0x4db552)
#define g_arenaListPlayers GAME_VAR(int, 0x4dba8c)   /* the players of all arenas merged into the list so far (each SessionEntry.players added by arena_mergeReceivedSessions; 0 from lobby_openConnection); nothing else reads it */
#define g_typedArenaAddress GAME_VAR(int, 0x4dbbd4)   /* the first word of g_typedArenaAddressText (char[24]) (arena_editAddress clears it as a dword with g_typedArenaAddress4) */
#define g_typedArenaAddress4 GAME_VAR(int, 0x4dbbd8)
#define g_unusedArmcWord4 GAME_VAR(int, 0x4dbc00)
#define g_chestMaxArmor GAME_VAR(int, 0x4dbc4c)
#define g_chestMaxShield GAME_VAR(int, 0x4dbc50)
#define g_viewedPartAmmoType GAME_VAR(int, 0x4dc194)   /* g_viewedPart's PartInfo.ammoType (+0x44): BULLET TYPE 0 .. 3, -1 a special weapon */
#define g_viewedPartAmmoPerShot GAME_VAR(int, 0x4dc198)   /* g_viewedPart's PartInfo.ammoPerShot (+0x48); for a special weapon (ammoType -1) armc_viewedPartRecord overwrites it with the item's actorItems index (shown as message 745 + it) */
#define g_panel0Speed GAME_VAR(float, 0x4dc5a4)   /* g_panels[0].speed: ARM CENTER background panel 0's turning speed (0.15, armc_initPanels; armc_drawPanels turns panels 1 .. 5 only, so this one is never read) */
#define g_panel1Speed GAME_VAR(float, 0x4dc5fc)
#define g_panel2Speed GAME_VAR(float, 0x4dc654)
#define g_panel3Speed GAME_VAR(float, 0x4dc6ac)
#define g_panel4Speed GAME_VAR(float, 0x4dc704)
#define g_panel5Speed GAME_VAR(float, 0x4dc75c)
#define g_unusedArmcWord1 GAME_VAR(int, 0x4dc864)
#define g_unusedArmcPoint0Y GAME_VAR(float, 0x4dca34)   /* 300.0: g_armcViewPoints[1] (point 0's y), set by armc_initCameraPoints; the whole table 0x4dca30 .. 0x4dca8c is never read */
#define g_unusedArmcPoint3Y GAME_VAR(float, 0x4dca64)
#define g_unusedArmcPoint5Y GAME_VAR(float, 0x4dca84)
#define g_mechDetectionRange GAME_VAR(float, 0x4dcaa0)
#define g_mechHackingLevel GAME_VAR(int, 0x4dcaa8)
#define g_unusedMechStat GAME_VAR(int, 0x4dcae8)
#define g_mechMaxSpeedBwd GAME_VAR(float, 0x4dcb00)
#define g_mechWeaponSlot0 GAME_VAR(u32, 0x4dcb20)   /* g_armcSlotItems[2]: the item in weapon slot 0 (armc_items.c slot_item(0)); g_armcSlotItems[0 .. 1] are the item slots 4 / 5 (g_itemSlot4 / 5) */
#define g_mechWeaponSlot1 GAME_VAR(u32, 0x4dcb24)
#define g_mechWeaponSlot2 GAME_VAR(u32, 0x4dcb28)
#define g_mechWeaponSlot3 GAME_VAR(u32, 0x4dcb2c)
#define g_unusedArmcWord3 GAME_VAR(int, 0x4dce38)
#define g_boosterThrustType GAME_VAR(int, 0x4dce80)
#define g_headHackingLevel GAME_VAR(int, 0x4dcf00)
#define g_unusedArmcWord2 GAME_VAR(int, 0x4dcf14)
#define g_armcPanelDepth GAME_VAR(float, 0x4dcfc8)   /* z of the panels' origin point (g_armcCameraBox + 0x88, 0 from armc_initCameraBox; its y + 0x84 gives the panels' heights); armc_drawPanels glTranslate's z */
#define g_unusedStartupWord3 GAME_VAR(int, 0x4dd0b8)
#define g_unusedStartupWord2 GAME_VAR(u32, 0x4dd96c)
#define g_setupResolution GAME_VAR(int, 0x4ddba0)
#define g_freeCamHeight GAME_VAR(float, 0x4de348)
#define g_unusedFreeCamMoveWord GAME_VAR(u32, 0x4de6f0)
#define g_unusedPostMatchFlag GAME_VAR(int, 0x4de6f8)
#define g_arenaPassword GAME_VAR(u32, 0x4ded46)   /* char[8] (GameSettings.password of g_arenaName): the arena's password, sent with it */
#define g_arenaPassword4 GAME_VAR(u32, 0x4ded4a)
#define g_arenaLocked GAME_VAR(u8, 0x4ded4e)   /* GameSettings.locked: 1 a password game (the arena file's "secret") */
#define g_menuTunnelSpeed GAME_VAR(float, 0x4deda8)
#define g_mouseSmooth GAME_VAR(int, 0x4df004)
#define g_unusedMenuReturnWord GAME_VAR(int, 0x4df8e0)
#define g_arenaFilePassword GAME_VAR(u32, 0x5b193c)
#define g_arenaFilePassword4 GAME_VAR(u32, 0x5b1940)
#define g_unusedStartupWord1 GAME_VAR(int, 0x76d474)
#define g_unusedRoomListWord GAME_VAR(int, 0x9087b0)
#define g_freeCamYaw GAME_VAR(float, 0x90d1cc)   /* the match's free (watching) camera's heading in degrees, 0 .. 360: freeCam_mouseLook (screen 9999) turns it by the pointer, freeCam_stepLeft / back move along it (+90), turn_update keeps its sine / cosine and puts it in the watched slot's g_slotCams record */
#define g_unusedRoomWord GAME_VAR(int, 0x9dd1b0)
#define g_unusedLoginWord GAME_VAR(int, 0x9dd32c)
#define g_pilotRank GAME_VAR(int, 0x9dd5e0)
#define g_roomListPlayers GAME_VAR(int, 0x9dd840)   /* the players of all rooms merged into the game list so far (each SessionEntry.players added by room_mergeReceivedSessions; 0 from room_enterGameList / gameList_open); nothing else reads it */
#define g_unusedActive GAME_VAR(u32, 0x9dd864)
#define g_unusedInitWord GAME_VAR(int, 0x9dd8f8)
#define g_unusedReplayListWord1 GAME_VAR(int, 0x9dd944)
#define g_unusedReplayListWord2 GAME_VAR(int, 0x9eea88)
#define g_unusedMainMenuWord GAME_VAR(int, 0x9eeabc)
#define g_missionsDrawBackground GAME_VAR(int, 0x9eeba8)
#define g_unusedBriefingWord GAME_VAR(int, 0x9ef218)
#define g_misHeader1 GAME_VAR(int, 0x9ef2c4)
#define g_misHeader2 GAME_VAR(int, 0x9ef2c8)
#define g_misHeader3 GAME_VAR(int, 0x9ef2cc)
#define g_unusedProfileCameraWord GAME_VAR(int, 0x9f6800)
#define g_profileNoneAtEntry GAME_VAR(int, 0x9f8d70)   /* 1: the profile screen was entered with no profiles (menuState210_enter sets it when g_profileCount is 0, else clears it): profile_listPage then runs the new-name dialog (profile_typeNewName) while a dialog is up; otherwise it returns 0 */
#define g_netChatMessageKind GAME_VAR(int, 0x9f93c8)
#define g_netChatMessageWord1 GAME_VAR(int, 0x9f93cc)
#define g_netChatMessageFrom GAME_VAR(int, 0x9f93d0)   /* +8 of the unsent chat-message template (net_resetState clears it; never read): in net_sendChat's layout the sender's player id */
#define g_netChatMessageText GAME_VAR(int, 0x9f93d4)
#define g_netSlotMessageKind GAME_VAR(int, 0x9f9420)
#define g_netPacketMessageKind GAME_VAR(int, 0x9f9428)
#define g_receivedRank GAME_VAR(int, 0xa052d6)
#define g_unusedNetResetWord GAME_VAR(int, 0xa05328)
#define g_lobbyTcpPort GAME_VAR(int, 0xa055f4)
#define g_ladderPort GAME_VAR(int, 0xa05634)
#define g_profileReplyResult GAME_VAR(int, 0xa05638)   /* the Ladder server's profile reply's result code: the first dword of g_profileReply (requests 14 login / 15 create ID; 0x21 ok, 0x1f no such ID, 0x20 wrong password, 0x22 ID in use, 0x1e ID taken) */
#define g_roomListRequest GAME_VAR(u32, 0xa0b334)   /* the 4-byte body of request 19 (list rooms; 01 00 18 00 = 0x180001, written by gameList_open), sent to the game server by net_send(19); allocated by net_resetConnection, freed by net_freeBuffers */
#define g_unusedSessionWord GAME_VAR(int, 0xa0b420)
#define g_unusedDplayWord1 GAME_VAR(int, 0xa0b42c)
#define g_unusedDplayWord2 GAME_VAR(int, 0xa0b430)
#define g_unusedDplayWord3 GAME_VAR(int, 0xa0b434)
#define g_unusedDplayWord4 GAME_VAR(int, 0xa0b438)
#define g_unusedPingWord1 GAME_VAR(int, 0xa0bf14)
#define g_unusedPingWord2 GAME_VAR(int, 0xa0bf18)
#define g_vecOrigin GAME_VAR(float, 0xa0e7a8)
#define g_vecUnitZ GAME_VAR(float, 0xa0e7c8)
#define g_vecZero GAME_VAR(float, 0xa0e7e8)
#define g_penInitialized GAME_VAR(int, 0xa106a8)   /* pen_init's duplicate guard: 1 would make a second pen_init only report 'pen duplicate initialization - penInit()' and return 0; never written (0 always), so the guard never fires */
#define g_packedRed GAME_VAR(u32, 0xa1f238)
#define k_5f GAME_VAR(float, 0x4a93d0)
#define k_200f GAME_VAR(float, 0x4a93f0)
#define k_38f GAME_VAR(float, 0x4a93f8)
#define k_0_01f GAME_VAR(float, 0x4a9420)
#define k_500f GAME_VAR(float, 0x4a9450)
#define k_0_07f GAME_VAR(float, 0x4a946c)
#define k_45f GAME_VAR(float, 0x4a94e8)
#define k_1000000f GAME_VAR(float, 0x4a94ec)
#define k_0_2f GAME_VAR(float, 0x4a94f8)
#define k_640f GAME_VAR(float, 0x4a9510)
#define k_3f GAME_VAR(float, 0x4a9534)
#define k_0_95f GAME_VAR(float, 0x4a953c)
#define k_90f GAME_VAR(float, 0x4a9550)
#define k_2000f GAME_VAR(float, 0x4a9554)
#define k_m50f GAME_VAR(float, 0x4a9558)
#define k_0_28125f GAME_VAR(float, 0x4a9564)
#define k_120f GAME_VAR(float, 0x4a95cc)
#define k_m549_9f GAME_VAR(float, 0x4a95d0)
#define k_m549_99f GAME_VAR(float, 0x4a95d4)
#define k_m549f GAME_VAR(float, 0x4a95d8)
#define k_m890f GAME_VAR(float, 0x4a9728)
#define k_890f GAME_VAR(float, 0x4a972c)
#define k_8 GAME_VAR(double, 0x4aa3f0)
#define k_100 GAME_VAR(double, 0x4aa3f8)
#define k_27 GAME_VAR(double, 0x4aa408)
#define g_arenaKeptCamX GAME_VAR(float, 0x4db840)
#define g_arenaKeptCamY GAME_VAR(float, 0x4db844)
#define g_arenaKeptCamZ GAME_VAR(float, 0x4db848)
#define g_arenaKeptLookX GAME_VAR(float, 0x4dbab8)
#define g_arenaKeptLookY GAME_VAR(float, 0x4dbabc)
#define g_arenaKeptLookZ GAME_VAR(float, 0x4dbac0)
#define g_chestWeightLimit GAME_VAR(float, 0x4dbc48)
#define g_itemBonusCapacityPerLevel GAME_VAR(float, 0x4dbc70)
#define g_itemBonusDetectionRange GAME_VAR(float, 0x4dbc78)
#define g_legsSpeedCorrection GAME_VAR(float, 0x4dc230)
#define g_legsWeight GAME_VAR(float, 0x4dc240)
#define g_armsFcsLevel GAME_VAR(int, 0x4dc290)
#define g_armsWeight GAME_VAR(float, 0x4dc2a4)
#define g_itemBonusTargetKeep GAME_VAR(float, 0x4dc88c)
#define g_itemBonusRechargeTime GAME_VAR(float, 0x4dc894)
#define g_itemBonusLockOn GAME_VAR(float, 0x4dc898)
#define g_mechMobility GAME_VAR(float, 0x4dcad0)
#define g_mechBoostTime GAME_VAR(float, 0x4dcaec)   /* the mech's boost time in ms (Player.boostTime x 1000): the first figure of BOOSTER ENERGY (message 680), shown / 1000 in seconds */
#define g_mechBoosterRecharge GAME_VAR(float, 0x4dcaf0)
#define g_mechNormalSpeed GAME_VAR(float, 0x4dcaf8)
#define g_itemBonusShield GAME_VAR(float, 0x4dcc68)
#define g_hasItemCapacity GAME_VAR(int, 0x4dcb10)   /* extra item 27 (BE-VOX EXPANSION MAGAZINE) is fitted (armc_extraItemBonuses; written only) */
#define g_hasItemEpak GAME_VAR(int, 0x4dcea8)   /* extra item 28 (BE-EOX E-PAK EXTRA MAGAZINE) is fitted (armc_extraItemBonuses; written only) */
#define g_hasItem30mm GAME_VAR(int, 0x4dcc5c)   /* extra item 29 (BE-30X 30MM EXTRA MAGAZINE) is fitted (armc_extraItemBonuses; written only) */
#define g_hasItem60mm GAME_VAR(int, 0x4dbc54)   /* extra item 30 (BE-60X 60MM EXTRA MAGAZINE) is fitted (armc_extraItemBonuses; written only) */
#define g_hasItemMissile GAME_VAR(int, 0x4dbe44)   /* extra item 31 (BE-ROX EXTRA ROCKET CHAMBER) is fitted (armc_extraItemBonuses; written only) */
#define g_hasItemSensor GAME_VAR(int, 0x4dc794)   /* extra item 32 (SE-S10 SENSOR ARRAY) is fitted (armc_extraItemBonuses; written only) */
#define g_hasItemBooster GAME_VAR(int, 0x4dbd78)   /* extra item 33 (TEP-34L BOOST GENERATOR) is fitted (armc_extraItemBonuses; read there) */
#define g_hasItemWeight GAME_VAR(int, 0x4dc774)   /* extra item 34 (BP-2001 GRAVITY CONTROLLER) is fitted (armc_extraItemBonuses; read there) */
#define g_hasItemShield GAME_VAR(int, 0x4dcf30)   /* extra item 35 (SH-4 FORCEFIELD BOOSTER) is fitted (armc_extraItemBonuses; read there) */
#define g_itemBonusActiveTime GAME_VAR(float, 0x4dcca0)
#define g_boosterActiveTime GAME_VAR(float, 0x4dce84)
#define g_boosterRechargeTime GAME_VAR(float, 0x4dce88)
#define g_boosterRechargeDelay GAME_VAR(float, 0x4dce8c)
#define g_boosterNormalSpeed GAME_VAR(float, 0x4dce90)
#define g_boosterWeight GAME_VAR(float, 0x4dcea0)
#define g_itemBonusWeightLimit GAME_VAR(float, 0x4dceb0)
#define g_itemBonusHacking GAME_VAR(float, 0x4dceb4)
#define g_headDetectionRange GAME_VAR(float, 0x4dcef8)
#define g_headDetectionAngle GAME_VAR(float, 0x4dcefc)
#define g_headLockOnTime GAME_VAR(float, 0x4dcf04)
#define g_headTargetKeepTime GAME_VAR(float, 0x4dcf08)
#define g_headWeight GAME_VAR(float, 0x4dcf0c)
#define g_fpsSecondStart GAME_VAR(double, 0x4dd0a0)
#define g_lastFrameClock GAME_VAR(double, 0x4dd0c8)
#define g_fpsFrameClock GAME_VAR(double, 0x4dd550)
#define g_frameRate GAME_VAR(double, 0x4dd558)
#define g_fpsSecondSoFar GAME_VAR(double, 0x4dd978)
#define g_fps GAME_VAR(float, 0x4dd980)
#define g_freeCamMoveStarted GAME_VAR(int, 0x4de340)   /* set to 1 by the first click in the free camera (freeCam_mouseLook) and never cleared: later clicks start nothing; read only there */
#define g_freeCamMoveEyeX GAME_VAR(float, 0x4de350)
#define g_freeCamMoveEyeY GAME_VAR(float, 0x4de354)
#define g_freeCamMoveEyeZ GAME_VAR(float, 0x4de358)
#define g_freeCamTurnSin GAME_VAR(float, 0x4de6c0)   /* sin of the free camera's turn (g_freeCamYaw, degrees), set by freeCam_mouseLook's turn_update; freeCam_keys moves the camera forward / back by it (with g_freeCamTurnCos) */
#define g_freeCamTilt GAME_VAR(float, 0x4de6c4)
#define g_freeCamTurnCos GAME_VAR(float, 0x4de6c8)
#define g_freeCamMoveTargetX GAME_VAR(float, 0x4de6d0)
#define g_freeCamMoveTargetY GAME_VAR(float, 0x4de6d4)
#define g_freeCamMoveTargetZ GAME_VAR(float, 0x4de6d8)
#define g_ladderPassword GAME_VAR(int, 0x9dd58e)   /* the Ladder password (12 bytes; g_ladderId + 0x1e): its first dword */
#define g_ladderPassword4 GAME_VAR(int, 0x9dd592)
#define g_ladderPassword8 GAME_VAR(int, 0x9dd596)
#define g_replaySelectDimR GAME_VAR(float, 0x9dda70)
#define g_replaySelectDimG GAME_VAR(float, 0x9dda74)
#define g_replaySelectDimB GAME_VAR(float, 0x9dda78)
#define g_replaySelectDimA GAME_VAR(float, 0x9dda7c)
#define g_replaySelectLitR GAME_VAR(float, 0x9eea98)
#define g_replaySelectLitG GAME_VAR(float, 0x9eea9c)
#define g_replaySelectLitB GAME_VAR(float, 0x9eeaa0)
#define g_replaySelectLitA GAME_VAR(float, 0x9eeaa4)
#define g_keptChatLine GAME_VAR(char, 0x9f63e4)
#define g_rankReplyCode GAME_VAR(u8, 0xa052c0)   /* the first byte of the 0x22-byte reply to request 29 (my rank; g_rankReply): 1 when a reply came (net_recv sets g_rankReplyIn when it is non-zero); +1 g_outOfRank, +0x16 g_receivedRank */
#define g_arenaGameListLeft GAME_VAR(int, 0x4db8c8)
#define g_arenaGameListTop GAME_VAR(int, 0x4db8cc)
#define g_arenaGameListRight GAME_VAR(int, 0x4db8d0)
#define g_arenaGameListBottom GAME_VAR(int, 0x4db8d4)
#define g_armcPageLeft GAME_VAR(int, 0x4dcc90)   /* the ARM CENTER page's frame (10, 10, 0x276, 0x1d6 = the 640x480 screen less a margin; armc_open): left */
#define g_armcPageTop GAME_VAR(int, 0x4dcc94)
#define g_armcPageBottom GAME_VAR(int, 0x4dcc9c)
#define g_setupSoundLeft GAME_VAR(int, 0x4ddad0)
#define g_setupSoundRight GAME_VAR(int, 0x4ddad8)
#define g_setupGraphicTop GAME_VAR(int, 0x4dddd4)
#define g_setupControlLeft GAME_VAR(int, 0x4dde80)
#define g_setupControlTop GAME_VAR(int, 0x4dde84)
#define g_setupControlRight GAME_VAR(int, 0x4dde88)
#define g_sensitivitySlider GAME_VAR(int, 0x4de1c8)
#define g_ladderExp GAME_VAR(int, 0x4de722)
#define g_ladderPower GAME_VAR(float, 0x4de726)
#define g_ladderGames GAME_VAR(int, 0x4de72a)
#define g_ladderKills GAME_VAR(int, 0x4de72e)
#define g_ladderDeaths GAME_VAR(int, 0x4de732)
#define g_menuFramePhase GAME_VAR(int, 0x4de740)
#define g_gameListRow GAME_VAR(int, 0x4df818)   /* the selected game's row among the nine shown (0 .. 8; g_gameListTop + it = g_pickedGame), shared by the arena lobby's list and the game room's (Ladder) list */
#define g_gameListTop GAME_VAR(int, 0x680bb0)
#define g_menuFrameCounter GAME_VAR(int, 0x76d428)
#define g_clockNow GAME_VAR(double, 0x9db980)
#define g_fieldStep GAME_VAR(int, 0x9dc428)   /* the focus step a key asks of the login / new-ID / account forms: 20 on to the next field, 10 back, 0 none. Set by the chat edit (editField_editProc: Enter 20; Tab in the game room 20, with Shift 10) when it closes a field, and also by roomLogin_keys / newIdForm_keys from the DirectInput Tab (+Shift) and toggle keys while no field is open; consumed and cleared by roomLogin_update, newIdForm_update, account_page */
#define g_roomLoginLeft GAME_VAR(int, 0x9dd358)
#define g_roomLoginTop GAME_VAR(int, 0x9dd35c)
#define g_roomLoginBottom GAME_VAR(int, 0x9dd364)
#define g_accountPanelLeft GAME_VAR(int, 0x9dd368)
#define g_accountPanelTop GAME_VAR(int, 0x9dd36c)
#define g_accountPanelRight GAME_VAR(int, 0x9dd370)
#define g_accountPanelBottom GAME_VAR(int, 0x9dd374)
#define g_roomGameListLeft GAME_VAR(int, 0x9dd4a8)
#define g_roomGameListTop GAME_VAR(int, 0x9dd4ac)
#define g_roomGameListRight GAME_VAR(int, 0x9dd4b0)
#define g_roomGameListBottom GAME_VAR(int, 0x9dd4b4)
#define g_newIdFormLeft GAME_VAR(int, 0x9dd6e8)
#define g_newIdFormRight GAME_VAR(int, 0x9dd6f0)
#define g_newIdFormBottom GAME_VAR(int, 0x9dd6f4)
#define g_replaySelectLeft GAME_VAR(int, 0x9dd908)
#define g_replaySelectTop GAME_VAR(int, 0x9dd90c)
#define g_replaySelectRight GAME_VAR(int, 0x9dd910)
#define g_replaySelectBottom GAME_VAR(int, 0x9dd914)
#define g_menuHintStep GAME_VAR(float, 0x9dd948)   /* the AUTOPLAY-F1 hint's fade step per time unit: +0.05 rising, -0.05 falling (mainmenu_drawMenu; 0.05 again on any panel hover and at menuState300_enter) */
#define g_menuIdleTime GAME_VAR(float, 0x9dda80)   /* time in 1/60 s with no main-menu panel under the pointer (mainmenu_drawMenu adds g_frameTime; 0 on a hover / when the hint finishes); the AUTOPLAY-F1 hint shows past 120 */
#define g_menuHintFade GAME_VAR(float, 0x9eea8c)   /* the AUTOPLAY-F1 hint's fade (mainmenu_drawMenu): + g_menuHintStep x g_frameTime; past 3 set to 1 and falling, below 0 set to 0 and rising (idle restarts); drawn with alpha min(1, this) */
#define g_mainMenuDepth GAME_VAR(float, 0x9eea90)   /* the main menu tunnel's camera depth: -300 at menuState300_enter, flown down to -550 while g_tunnelFlyingIn (mainmenu_drawMenu), passed to menu_tunnel */
#define g_missionsWindowRight GAME_VAR(int, 0x9f16b0)   /* the mission screen's (900) window: right (0x276); left / top g_missionsWindowLeft / g_missionsWindowTop */
#define g_missionsWindowBottom GAME_VAR(int, 0x9f16b4)   /* the mission screen's (900) window: bottom (0x1cc) */
#define g_skirmishRectLeft GAME_VAR(int, 0x9f6308)
#define g_skirmishRectTop GAME_VAR(int, 0x9f630c)
#define g_pilotSelectBottom GAME_VAR(int, 0x9f682c)
#define g_pilotSelectRight GAME_VAR(int, 0x9f6830)
#define g_profileListTop GAME_VAR(int, 0x9f8c4c)
#define g_pilotSelectTop GAME_VAR(int, 0x9f8c50)
#define g_pilotSelectLeft GAME_VAR(int, 0x9f8c54)
#define g_profileListRow GAME_VAR(int, 0x9f8c5c)
#define g_profileChosen GAME_VAR(int, 0x9f8d74)   /* the profile chosen in the list (index into g_profiles; = g_profileListTop + g_profileListRow) */
#define g_profilePageLeft GAME_VAR(int, 0x9f8e48)
#define g_profilePageTop GAME_VAR(int, 0x9f8e4c)
#define g_profilePageRight GAME_VAR(int, 0x9f8ea0)
#define g_profilePageBottom GAME_VAR(int, 0x9f8ea4)
#define g_newNameDialogTop GAME_VAR(int, 0x9f8ea8)
#define g_newNameDialogLeft GAME_VAR(int, 0x9f8eac)
#define g_newNameDialogRight GAME_VAR(int, 0x9f8f20)
#define g_newNameDialogBottom GAME_VAR(int, 0x9f8f24)
#define g_ptxHuffSet GAME_VAR(int, 0xaa2e94)
#define g_dikNumpad4 GAME_VAR(int, 0x4deb58)
#define g_dikNumpad3 GAME_VAR(int, 0x4deb5c)
#define g_dikNumpad6 GAME_VAR(int, 0x4deb60)
#define g_dikNumpad5 GAME_VAR(int, 0x4deb64)
#define g_dikNumpad8 GAME_VAR(int, 0x4deb68)
#define g_dikNumpad7 GAME_VAR(int, 0x4deb6c)
#define g_dikNumpad9 GAME_VAR(int, 0x4deb70)
#define g_dikNumpad0 GAME_VAR(int, 0x4deb78)
#define g_dikNumpadDot GAME_VAR(int, 0x4dec88)
#define g_dikNumpad2 GAME_VAR(int, 0x4dec8c)
#define g_dikNumpad1 GAME_VAR(int, 0x4dec90)
#define g_dikNumLock GAME_VAR(int, 0x4dec94)
#define g_dikInsert GAME_VAR(int, 0x4deda0)
#define g_dikPeriod GAME_VAR(int, 0x4deda4)
#define g_dikLWin GAME_VAR(int, 0x4df038)
#define g_dikInsert_2 GAME_VAR(int, 0x4df04c)
#define g_dikF12 GAME_VAR(int, 0x4df8d4)
#define g_dikF10 GAME_VAR(int, 0x4df8dc)
#define g_dikLBracket GAME_VAR(int, 0x4df8fc)
#define g_dik0 GAME_VAR(int, 0x4e0460)
#define g_dik5 GAME_VAR(int, 0x4e0c78)
#define g_dik6 GAME_VAR(int, 0x4e0c7c)
#define g_dik7 GAME_VAR(int, 0x4e0c80)
#define g_dik8 GAME_VAR(int, 0x4e0c84)
#define g_dik9 GAME_VAR(int, 0x4e0c88)
#define g_dikNumpadSlash GAME_VAR(int, 0x4e0ca0)
#define g_dikB GAME_VAR(int, 0x4e0cd8)
#define g_dikE GAME_VAR(int, 0x4e10e4)
#define g_dikF GAME_VAR(int, 0x4e14e8)
#define g_dikH GAME_VAR(int, 0x4e14f0)
#define g_dikK GAME_VAR(int, 0x4e1500)
#define g_dikQ GAME_VAR(int, 0x4e1518)
#define g_dikU GAME_VAR(int, 0x4e1530)
#define g_dikV GAME_VAR(int, 0x4e1534)
#define g_dikY GAME_VAR(int, 0x4e1540)
#define g_dikZ GAME_VAR(int, 0x4e1544)
#define g_dikEnd GAME_VAR(int, 0x5ae9c0)
#define g_dikSlash GAME_VAR(int, 0x5b1974)
#define g_dikPageDown GAME_VAR(int, 0x5b1980)
#define g_dikPageUp_2 GAME_VAR(int, 0x5b1db0)
#define g_dikNumpadPlus GAME_VAR(int, 0x67ef08)
#define g_dikScrollLock GAME_VAR(int, 0x67ef10)
#define g_dikApps GAME_VAR(int, 0x67ef28)
#define g_dikEnter_2 GAME_VAR(int, 0x67ef2c)
#define g_dikPrintScreen GAME_VAR(int, 0x67fb40)
#define g_dikComma GAME_VAR(int, 0x680368)
#define g_dikNumpadEnter GAME_VAR(int, 0x6803a4)
#define g_dikMouse3 GAME_VAR(int, 0x680bbc)
#define g_dikApostrophe GAME_VAR(int, 0x74de20)
#define g_dikEnd_2 GAME_VAR(int, 0x76d32c)
#define g_dikGrave GAME_VAR(int, 0x76d334)
#define g_dikRWin GAME_VAR(int, 0x76d338)
#define g_dikPageDown_2 GAME_VAR(int, 0x76d370)
#define g_dikMinus GAME_VAR(int, 0x76d374)
#define g_dikBack GAME_VAR(int, 0x76d378)
#define g_dikRBracket GAME_VAR(int, 0x76d380)
#define g_dikNumpadMinus GAME_VAR(int, 0x76d3f4)
#define g_dikCapsLock GAME_VAR(int, 0x76d420)
#define g_dikSemicolon GAME_VAR(int, 0x76d470)
#define g_dikDelete_2 GAME_VAR(int, 0x907b28)
#define g_dikHome GAME_VAR(int, 0x90d1c0)
#define g_dikF3 GAME_VAR(int, 0x9da448)
#define g_dikF2 GAME_VAR(int, 0x9da44c)
#define g_dikF5 GAME_VAR(int, 0x9da450)
#define g_dikF4 GAME_VAR(int, 0x9da454)
#define g_dikF7 GAME_VAR(int, 0x9da458)
#define g_dikF6 GAME_VAR(int, 0x9da474)
#define g_dikF9 GAME_VAR(int, 0x9da478)
#define g_dikF8 GAME_VAR(int, 0x9da47c)
#define g_dikEquals GAME_VAR(int, 0x9dae18)
#define g_dikHome_2 GAME_VAR(int, 0x9dae6c)
#define g_dikBackslash GAME_VAR(int, 0x9dae78)
#define g_dikNumpadStar GAME_VAR(int, 0x9db0a8)
/* moved from game.h and the files' own defines (tools/promote_locals.py) */
#define g_mouseTaken GAME_VAR(int, 0x4ad17c)   /* 1 in the exe's data and never written: input_reacquireMouse always takes the mouse again (0 would let it go) */
#define g_pulse GAME_VAR(float, 0x4b06fc)   /* the bands' colour pulse, 0.05 .. 0.95 */
#define g_pulseStep GAME_VAR(float, 0x4b0700)
#define g_flareSizeB GAME_VAR(float, 0x4b0704)   /* a breathing half-size shared by two screens: in the menu tunnel flare 3's (10 .. 48; menuState300_enter / armc_exit set 10); in the ARM CENTER part panel 3's half width (200 .. 600; armc_initPanels sets 200; armc_drawPanels) */
#define g_flareSizeA GAME_VAR(float, 0x4b0708)   /* flare 2's */
#define g_flareStepB GAME_VAR(float, 0x4b070c)
#define g_flareStepA GAME_VAR(float, 0x4b0710)
#define g_frameTime GAME_VAR(float, 0x4b071c)   /* the last frame's time in 1/60 s (menu_frame: 60 / the frame rate, 1 when above 20); screen cameras clamp it again before use (1 above their limit: arena_camera, armc_cameraStep, setup_camera, room_camera, skirmish_camera, missions camera, menu_titleEmblemTransition (above 3); menuTunnel_advance sets 2 above 10) */
#define g_directInput GAME_VAR(void *, 0x4d1e98)
#define g_keyboard GAME_VAR(void *, 0x4d1fa0)
#define g_mouse GAME_VAR(void *, 0x4d1fa4)
#define g_keyboardReady GAME_VAR(int, 0x4d1fa8)   /* 1 once the DirectInput keyboard is made and acquired (input_initKeyboard); 0 when released (input_releaseKeyboard: while a text field takes typing through Windows, and at shutdown); while 0 the key reads give 0 */
#define g_mouseReady GAME_VAR(int, 0x4d1fac)   /* 1 once the DirectInput mouse device is made and set up (input_createMouse, which returns at once while it is set); 0 when released (input_releaseMouse) */
#define g_textCharWidth GAME_VAR(int, 0x4d23d8)   /* the Korean passes' advance for a single-byte character other than a space (text_pass); set per call by text_begin: 8 (draw8 / centred8), 13 (draw16 / box16), 26 (draw32), 18 (box32), 6 (draw5 / centred5) */
#define g_mapTop GAME_VAR(int, 0x4d7350)   /* the first map shown */
#define g_mapListKept GAME_VAR(int, 0x4d94fc)   /* 1 once a list has been kept (mapList_ok); never read */
#define g_lobbySubState GAME_VAR(int, 0x4db51c)   /* the lobby's page: 5 the top menu, 0 player setup, 1 join, 2 create */
#define g_armcAngle GAME_VAR(float, 0x4dbc04)   /* the preview's turn */
#define g_armcPartSlot GAME_VAR(int, 0x4dbc6c)   /* the parts page's slot in view: 0 head, 1 chest, 2 arm, 3 leg, 4 booster, 5 the whole mech (VIEW ALL, key A; set at entry) */
#define g_weaponCount GAME_VAR(int, 0x4dc244)
#define g_armcColourSlot GAME_VAR(int, 0x4dc4b0)   /* the colour slot being edited */
#define g_extraCount GAME_VAR(int, 0x4dc778)
#define g_armcMode GAME_VAR(int, 0x4dc798)   /* the ARM CENTER's page: 1 the parts, 2 the weapons, 3 the colours; 0 once its camera is home on leaving (armc_cameraStep); 4 is dispatched (armc_processInput, armc_mouse) but never set */
#define g_armcSessionDue GAME_VAR(int, 0x4dc86c)   /* the "please wait" box was shown: the session is made next */
#define g_armcHideInterface GAME_VAR(int, 0x4dd078)   /* Ctrl+Alt+M: the screen without its interface */
#define g_menuVolume GAME_VAR(int, 0x4dd984)   /* DirectSound volume of the menu sounds: (v * 5 - 500) * 4 of the setting */
#define g_menuRepeatClock GAME_VAR(float, 0x4dda44)   /* the menus' hold-to-repeat clock in 1/60 s: menu_frame adds g_frameTime (back to 100 past 1e6); a held scroll arrow / key acts again once it reaches the caller's threshold (5 in the map, arena, game and replay lists, 1 for the setup sliders and bindings) and sets it to 0; screen entries and most menu clicks / keys clear it */
#define g_setupTab GAME_VAR(int, 0x4ddac8)   /* 0 sound, 1 graphics, 2 controls, 0x29a the top page */
#define g_emblemPulse GAME_VAR(float, 0x4de1d8)   /* its change per time unit: 0.02 from app_startupLoad, then +-0.018 (menu_titleEmblemTransition) */
#define g_emblemAlpha GAME_VAR(float, 0x4de1e0)   /* the pulsing layer's alpha (0.2 .. 0.9) */
#define g_logoFade GAME_VAR(float, 0x4de1e8)   /* the title logo (iftex/axis_title) fading OUT: 0 .. 1 by 0.1 a time unit; drawn with alpha 1 - this until it reaches 1 */
#define g_unusedLogoFade GAME_VAR(float, 0x4de1ec)   /* only written (menu_titleEmblemTransition: a second fade running twice as fast from 0.2) */
#define g_timerTick GAME_VAR(double, 0x4ded58)   /* seconds per (shifted) tick */
#define g_mouseX GAME_VAR(int, 0x4ded68)   /* the pointer: in the menus 640 x 480 units (input_updateMouse adds the mouse's movement and keeps it to 0..630 / 0..474, or the patch's wide clamp); in a match (screen 9999) not clamped and put back each frame to the window's centre in pixels (gfx_getWidth() / 2: match_combatInput, hud_cycleF11Mode, match_startRound) */
#define g_mouseY GAME_VAR(int, 0x4ded6c)
#define g_titleClosing GAME_VAR(int, 0x4df01c)   /* 1: a key (title_keyDismiss) or click (title_clickDismiss) dismissed the title: its layers fade and spread over g_titleCloseFrames, the profile screen (210) after 19 frames; 0 from menuState100_intro */
#define g_timerFrequency GAME_VAR(u64, 0x4df030)   /* QueryPerformanceFrequency's result */
#define g_cursorFrame GAME_VAR(int, 0x4df03c)   /* the mouse pointer's animation frame, 0..14 */
#define g_exitCode GAME_VAR(int, 0x4df048)   /* how the game closes (app_closeWindow's code; WM_DESTROY acts on it): 0 quit, 1 start AxisGL.exe again (graphics changed), 2 start axispatch.exe "nstower", 3 start DServer.exe "1", 99 the ending movie */
#define g_dialogPending GAME_VAR(int, 0x4df900)   /* a message box is up: it takes the keys */
#define g_cursorFrameTime GAME_VAR(float, 0x4df910)   /* frame time collected towards the next frame (5 units) */
#define g_titleCloseFrames GAME_VAR(int, 0x4e0458)   /* frames since the title was dismissed (g_titleClosing; from 0): indexes g_titleSpread and fades both layers by 0.02 a frame; the profile screen at 19 */
#define g_screenH GAME_VAR(int, 0x4e045c)
#define g_tunnelStripeScroll GAME_VAR(float, 0x4e14fc)   /* the menu tunnel's stripes' scroll (every screen's tunnel: menu_tunnel / setup_drawTunnel; tunnel_advance adds g_menuTunnelSpeed per time unit): runs 0 .. 200, then 0 */
#define g_cursorTexture GAME_VAR(int, 0x4e152c)   /* the pointer's sprite sheet (texture id) */
#define g_inputLineHidden GAME_VAR(int, 0x4e1868)   /* 1: the input line shows as stars (password fields); 0 for names */
#define g_ringBandTexture GAME_VAR(int, 0x4e186c)   /* \"iftex/cylinder\" (menu_loadTextures): the background tunnel rings' outer bands (menu_drawBackground3D, menu_tunnel.c outer_bands; not bound with SIMPLE MENU) */
#define g_viewAspect GAME_VAR(float, 0x4e1870)   /* gluPerspective's aspect: the screen's width / height, but narrowed (to 0.1, or eased towards 0) and eased back while the menu cameras fly (menu_camera*, armc_cameraStep, the room and skirmish cameras) and while the replay zooms in (menu_frame) */
#define g_screenW GAME_VAR(int, 0x5b1998)
#define g_lastScreen GAME_VAR(int, 0x67ef0c)   /* the screen whose set-up ran last (menu_enterState: menuStateN_enter / match_enter, then g_lastScreen = g_screen); menu_frame / app_frameByScreen run that set-up when g_screen differs. Screens that set themselves up store it too (200, 300, 500, 700, 800, 900) */
#define g_timerShift GAME_VAR(int, 0x67ef1c)   /* how far the counter is shifted right */
#define g_nextScreen GAME_VAR(int, 0x67ef20)   /* the front-end screen to go to: taken into g_screen when the tunnel's move ends (menuTunnel_advance); 300 the main menu */
#define g_highlightX GAME_VAR(int, 0x67ef34)   /* where the mouse pointer glides to (menu units) while g_pointerGliding: the focused button or field of a two-button question, or of the login / new-ID dialog */
#define g_highlightY GAME_VAR(int, 0x67fb38)
#define g_menuCameraMove GAME_VAR(int, 0x680370)   /* the menu camera's move along the tunnel (menu_tunnel.c): 0 still, 1 / 3 moving in / out a ring, 2 / 4 the view swinging up first; the menus ignore keys while not 0 */
#define g_viewAngle GAME_VAR(float, 0x68038c)   /* the 3D view's vertical angle (degrees) */
#define g_textFieldOpen GAME_VAR(int, 0x68039c)   /* 1: a text field has the keys (typing a name, password or chat line; edit_fields.c); the other input is off */
#define g_repeatDown GAME_VAR(float, 0x680bb4)
#define g_pointerGlideTime GAME_VAR(float, 0x680bc0)   /* the pointer glide's time left (20 time units, less g_frameTime each frame); below 0 the glide stops (g_pointerGliding 0) */
#define g_dialogFocus GAME_VAR(int, 0x74de1c)   /* the item with the keyboard focus in a dialog: in the profile questions (pages 3 and 5) 0 the left button, 1 the right; in the Ladder login 0 .. 3 (name, password, buttons; roomLogin_keys); in the new-ID form the field 0 .. 2 (newIdForm_keys) */
#define g_fontHanJungJong GAME_VAR(int, 0x76d360)   /* Hangul vowels and finals */
#define g_cageTexture GAME_VAR(int, 0x76d36c)
#define g_repeatUp GAME_VAR(float, 0x76d37c)   /* frames until a held up / down key steps again */
#define g_screen GAME_VAR(int, 0x76d3e8)   /* the front end's screen: 100 intro, 200 title, 210 profile, 300 main menu, 400 lobby,
                                                         500 skirmish, 600 setup, 700 armour, 800 game room, 900 the mission list (axis.mis; never
                                                         entered), 9999 in a match */
#define g_logoTexture GAME_VAR(int, 0x76d3f0)
#define g_pickedGame GAME_VAR(int, 0x76d41c)   /* the game picked in the arena lobby's / game room's game list: an index into g_sessionList (g_listTop + the row); joined with arena_joinSession / room_joinSession, its password and lock checked */
#define g_pointerGliding GAME_VAR(int, 0x76d42c)   /* 1: the mouse pointer glides to (g_pointerGlideX, g_pointerGlideY) until g_pointerGlideTime runs out (menuState800_gameRoom, the profile question pages) */
#define g_fontAscii GAME_VAR(int, 0x76d448)   /* ASCII, 5- and 8-unit fonts */
#define g_scene GAME_VAR(Scene *, 0x9087b4)   /* the scene object (0 outside a match) */
#define g_glContext GAME_VAR(void *, 0x9087b8)
#define g_frameOpening GAME_VAR(int, 0x90d1c4)   /* 1: a panel's frame is opening (menu_drawFrame's three-phase animation, which clears this when it ends): meanwhile the screen draws only that frame and takes no keys or clicks. Set when a menu camera arrives (menu_camera / menu_camera2) and when a profile dialog opens */
#define g_editCaretX GAME_VAR(int, 0x9da3d8)   /* where the line being typed is drawn (menu units) */
#define g_editCaretY GAME_VAR(int, 0x9da3dc)
#define g_menuKeyGuard GAME_VAR(float, 0x9da434)   /* a key delay (time units): 5 when a screen or text field opens (10 or 20 for some); app_frame takes g_frameTime off; the menu keys (menu_processKeys) and the chat edit's Enter (editField_editProc) wait until it is not above 0 */
#define g_simpleMenu GAME_VAR(int, 0x9da494)   /* SIMPLE MENU (the graphics setting, from g_cfgSimpleMenu; the setup page's button 6 flips it): the menus' 3D background (the tunnel's bands, flares and cages) is not drawn, only moved on */
#define g_unusedHighlightAlpha GAME_VAR(float, 0x9da4a4)   /* only written (0.4 when a dialog's focus moves, 0.2 by profile_askDelete / profile_askLogOut) */
#define g_fontAsciiLarge GAME_VAR(int, 0x9dad90)   /* ASCII, 16- and 32-unit fonts */
#define g_mapIndex GAME_VAR(int, 0x9dad94)   /* the map being played or loaded: an index into g_mapNames (the skirmish round, the arena / room game's map, the rotation's current map; -1 none). Saved in replays */
#define g_fontHanCho GAME_VAR(int, 0x9dae1c)   /* font textures (ids): Hangul initial consonants */
#define g_language GAME_VAR(int, 0x9dae74)   /* the language: 1 Korean (system language 0x412 / 0x812, WinMain), 2 English. It picks msgkor/msgeng.dat, profkor/profeng.dat, the message boxes, the ARM CENTER text widths and the message lines (msg_players.c KOREAN / ENGLISH) */
#define g_tunnelPulse GAME_VAR(float, 0x9db978)   /* bounces 0 .. 100 */
#define g_timerLastCount GAME_VAR(u32, 0x9dbf08)   /* timer_now's last counter reading (shifted by g_timerShift) */
#define g_chatLength GAME_VAR(int, 0x9dbf10)   /* characters in g_chatLine */
#define g_hEditField GAME_VAR(void *, 0x9dd888)   /* the hidden EDIT control typing goes to */
#define g_missionTop GAME_VAR(int, 0x9f16bc)   /* the first row shown */
#define g_skirmishNewPartsNotice GAME_VAR(int, 0x9f62e0)   /* 1: the skirmish screen shows the "YOU'VE GOT NEW PARTS AND WEAPONS" notice (skirmish_frameNewPartsNotice), raised when a new round is reached (menuState500_enter); a click (newPartsNotice_clickClose) or Esc / Enter (newPartsNotice_keys) closes it */
#define g_skirmishState GAME_VAR(int, 0x9f62f8)   /* the skirmish screen's camera state (menu_camera2): 1 flying in (menuState500_enter), 2 there: the screen is up (keys, no tunnel), 0 flying home (skirmish_leave); 2 again once home */
#define g_skirmishLeft GAME_VAR(int, 0x9f6300)   /* -1 once the skirmish camera is home again (menu_camera2's third flag: the screen was left for the main menu); 0 from menuState500_enter. While it is set the screen draws nothing of its own and takes no keys or clicks */
#define g_skirmishShowBackground GAME_VAR(int, 0x9f63b8)
#define g_profileReveal GAME_VAR(int, 0x9f6828)   /* CHARACTER SELECT: the chosen pilot's portrait cell grown by this many pixels a side (0 .. 8, one more each time g_profileRevealClock passes 1); 0 when the pilot cursor moves (profile_emblemKeys, pilotSelect_clicks) or the selection resets */
#define g_logOutDialogX GAME_VAR(int, 0x9f6834)   /* page 5's dialog frame */
#define g_profileQuitting GAME_VAR(int, 0x9f6838)   /* 1: the log-out question was answered yes (profile_quitGame, from profile_logOutKeys / profile_logOutClicks): the profile screen's next frame quits the game (menuState210_frame -> app_quitGame) and the pointer is no longer drawn (menu_frame); 0 from menuState210_enter */
#define g_logOutDialogY GAME_VAR(int, 0x9f683c)
#define g_pilotSelectCursor GAME_VAR(int, 0x9f8d30)   /* page 6, CHARACTER SELECT: the pilot under the cursor, 0..8 row by row */
#define g_statBarsStale GAME_VAR(int, 0x9f8d68)   /* 1: the pilot shown changed, the stat bars to be loaded again */
#define g_unusedProfileCameraSpeed GAME_VAR(float, 0x9f8e50)   /* only written: 0.1 by profile_quitGame, 0.05 when a key or click comes while g_profileQuitting (profile_processInput, profile_screenKeys) */
#define g_profileQuitSkip GAME_VAR(int, 0x9f8e54)   /* 0 from profile_quitGame; 5 once a key or click came while g_profileQuitting (profile_processInput and profile_screenKeys answer only while it is not 5). The game quits on the next frame anyway */
#define g_profileRevealClock GAME_VAR(float, 0x9f8ee4)   /* a float: the time to the next step of g_profileReveal; cleared when the pilot cursor moves */
#define g_profileDialogY GAME_VAR(int, 0x9f8f0c)
#define g_profilePage GAME_VAR(int, 0x9f8f10)   /* the profile screen's page: 1 the list, 2 a new name typed (profile_typeNewName), 3 the delete question (profile_askDelete), 4 logging in (profile_logIn; no keys), 5 the log-out question (profile_askLogOut), 6 CHARACTER SELECT (the pilot grid) */
#define g_unusedProfileCameraZoom GAME_VAR(float, 0x9f8f14)   /* only written: 80 by profile_quitGame, 100 by profile_processInput / profile_screenKeys */
#define g_profileDialogX GAME_VAR(int, 0x9f8f1c)   /* page 3's dialog frame */
#define g_unusedProfileCameraTime GAME_VAR(int, 0x9f8f30)   /* only written (0) by profile_quitGame, profile_processInput, profile_screenKeys */
#define g_profileMessage GAME_VAR(int, 0x9f8f34)   /* page 2: 1 while the 'name already taken' message window shows (set when profile_nameExists finds the typed name; drawn by profile_drawMessageWindow); a click, OK or right click clears it and typing starts again (profile_typeNewName) */
#define g_playerCount GAME_VAR(int, 0x9fd950)
#define g_textures GAME_VAR(TextureManager *, 0xa0e010)
#define g_music GAME_VAR(void *, 0xa0e670)   /* the playing music: DirectShow's IAMMultiMediaStream (music_play: CoCreateInstance(CLSID_AMMultiMediaStream), OpenFile, run); NULL when none (music_stop releases it) */
#define g_desktopH GAME_VAR(int, 0xa0e814)
#define g_desktopBits GAME_VAR(int, 0xa0e91c)
#define g_desktopW GAME_VAR(int, 0xa0e92c)   /* the desktop's mode before the switch */
#define g_glWindowMade GAME_VAR(int, 0xa0e930)   /* glWindow_init made its own window (only on its path without a given window; set once, a second call refused). The game always passes its main window (menu_enterState: glWindow_init(.., g_mainWindow, g_windowDC)), so it stays 0 */
#define g_glWindow GAME_VAR(void *, 0xa0e934)
#define g_glWindowDc GAME_VAR(void *, 0xa0e938)   /* the GL window's device context: the DC given to glWindow_init (g_windowDC), or the own window's (glWindow_wndProc WM_CREATE); gfx_swapBuffers swaps it, glWindow_setDisplayModeBy queries it */
#define g_glWindowContext GAME_VAR(void *, 0xa0e93c)   /* the GL context of glWindow's own window (glWindow_wndProc: wglCreateContext on WM_CREATE, deleted on WM_DESTROY); never made in the game, which passes its own window (its context is g_glContext) */
#define g_modeChanged GAME_VAR(int, 0xa0e940)   /* the display mode was switched (to be put back) */
#define g_loadTexture GAME_VAR(int, 0xa0e980)   /* the backdrop's texture id */
#define g_loadFade GAME_VAR(float, 0xa0e984)   /* the fade's time, 0 .. 1 s */
#define g_loadScroll GAME_VAR(float, 0xa0ea88)   /* the loading screen's time (TimeSync_frameTime summed since loading_drawScreen(-1)): the backdrop cylinder's texture v runs from it to it + 10, so it scrolls; not a progress fraction */
#define g_loadGame GAME_VAR(Scene *, 0xa0ea8c)   /* the game object being loaded (game_processLoadingMode's this): loading_draw reads its sessionMode (+8), awaitingHostRound, gameMode */
#define g_white GAME_VAR(u32, 0xa1f23c)   /* four bytes 0xff: an opaque white colour */
#define g_unlit GAME_VAR(u32, 0xa1f278)   /* the colour of a vertex out of a light's reach */
#define g_ptxClamp GAME_VAR(const u8 *, 0xa1f300)   /* the PTX decoder's clamp: points 0x100 into g_ptxClampTable (ptx_initClampTable), so g_ptxClamp[v] is v limited to 0 .. 255 for v from -0x100 (ptx_toRgb / ptx_toRgba; ptx_inverseDct from +0x80) */
#define g_netqCursor GAME_VAR(int, 0xb116e0)   /* the player netq_receive looks at first (turns 0..15) */
#define g_packetsSkipped GAME_VAR(int, 0xb116e4)   /* packets that came out of turn (netq_receive: a number other than the one due, the expected number moved past it). Any count lights the match's resend warning (match_frame clears it); 0x80 or more: 'network unstable' and the match is left (match_frame), or the loading stops (game_processLoadingMode) */
#define g_roomLoginRight GAME_VAR(int, 0x9dd360)
#define g_unusedRoomPanelEase GAME_VAR(float, 0x9dd560)   /* eased towards k_setupPanelTarget by room_slideMenu (menu_slide) while g_roomPanelsSliding, but read only there to ease itself: nothing uses the value; 0 from menuState800_enterGameRoom */
#define g_missionRow GAME_VAR(int, 0x9f1058)
#define g_profileDialogBottom GAME_VAR(int, 0x9f8f28)
#define g_profileDialogRight GAME_VAR(int, 0x9f8f2c)
#define g_logOutDialogRight GAME_VAR(int, 0x9f93bc)
#define g_logOutDialogBottom GAME_VAR(int, 0x9f93c0)
#define g_armCursor GAME_VAR(int, 0x4dbc7c)
#define g_headCount GAME_VAR(int, 0x4dc780)
#define g_armCount GAME_VAR(int, 0x4dca90)
#define g_legCount GAME_VAR(int, 0x4dca94)
#define g_mechDetectionAngle GAME_VAR(float, 0x4dcaa4)
#define g_mechLockOnTime GAME_VAR(float, 0x4dcaac)
#define g_mechTargetKeepTime GAME_VAR(float, 0x4dcab0)
#define g_mechLegsInertia GAME_VAR(float, 0x4dcad4)
#define g_mechLegsSpeedCorrection GAME_VAR(float, 0x4dcad8)
#define g_mechLegsForwardBoost GAME_VAR(float, 0x4dcadc)
#define g_mechLegsSideBoost GAME_VAR(float, 0x4dcae0)
#define g_mechLegsBackBoost GAME_VAR(float, 0x4dcae4)
#define g_mechBoosterRestTime GAME_VAR(float, 0x4dcaf4)
#define g_boosterCursor GAME_VAR(int, 0x4dcb30)
#define g_chestCount GAME_VAR(int, 0x4dcc60)
#define g_headCursor GAME_VAR(int, 0x4dcc8c)
#define g_chestCursor GAME_VAR(int, 0x4dcf3c)
#define g_itemBonusShieldUnread GAME_VAR(float, 0x4dbc74)
#define g_itemBonusEpak GAME_VAR(float, 0x4dc248)
#define g_itemBonus60mm GAME_VAR(float, 0x4dc548)
#define g_itemBonusMissile GAME_VAR(float, 0x4dcb34)
#define g_itemBonus30mm GAME_VAR(float, 0x4dcc6c)
#define g_unusedArenaCamWord GAME_VAR(u32, 0x4dbaf4)
#define g_unusedClock3 GAME_VAR(double, 0x4dd080)
#define g_unusedClock2 GAME_VAR(double, 0x4dd0a8)
#define g_unusedClock1 GAME_VAR(double, 0x4dd560)
#define g_gameConnectTexture GAME_VAR(int, 0x4df450)
#define g_editingFragLimit GAME_VAR(int, 0x9dd388)
#define g_editingTimeLimit GAME_VAR(int, 0x9dd568)
#define g_unusedAccountWord GAME_VAR(int, 0x9dd6d0)
#define g_newIdFormTop GAME_VAR(int, 0x9dd6ec)
#define g_unusedRoomCamWord GAME_VAR(u32, 0x9dd848)
#define g_unusedArenaWord GAME_VAR(int, 0x9fd958)
#define g_netByteBuffer GAME_VAR(char *, 0xa052e4)
#define g_lobbyLeavePacket GAME_VAR(u8 *, 0xa0b318)
#define g_errorReported GAME_VAR(int, 0xa1efe0)
#define g_fatalReported GAME_VAR(int, 0xa1efe4)
#define k_m1101f GAME_VAR(float, 0x4a9470)
#define k_0_001f GAME_VAR(float, 0x4a9480)
#define k_1500f GAME_VAR(float, 0x4a949c)
#define k_2200f GAME_VAR(float, 0x4a95c8)
#define k_m1500f GAME_VAR(float, 0x4a96fc)
#define k_1500f_4a9700 GAME_VAR(float, 0x4a9700)
#define k_2_25f GAME_VAR(float, 0x4a970c)
#define k_1_95f GAME_VAR(float, 0x4a9710)
#define k_400f GAME_VAR(float, 0x4aa424)
#define k_3000f GAME_VAR(float, 0x4aa42c)
#define k_5000f GAME_VAR(float, 0x4aa430)
#define k_m0_001f GAME_VAR(float, 0x4aa4a0)
#define g_lobbyBlinkRate GAME_VAR(float, 0x4ad498)
#define g_sentChatBlock GAME_VAR(char *, 0x9fd944)
#define k_26f GAME_VAR(float, 0x4aa27c)
/* float constants of .rdata named by value (tools/name_constants.py) */
#define k_180f GAME_VAR(float, 0x4a945c)   /* 180 */
#define k_m164f GAME_VAR(float, 0x4a9484)   /* -164 */
#define k_0_002777778f GAME_VAR(float, 0x4a9488)   /* 0.00277777785 */
#define k_m168f GAME_VAR(float, 0x4a948c)   /* -168 */
#define k_0_2777778f GAME_VAR(float, 0x4a9490)   /* 0.277777791 */
#define k_m200f GAME_VAR(float, 0x4a94a0)   /* -200 */
#define k_m360f GAME_VAR(float, 0x4a94b0)   /* -360 */
#define k_105f GAME_VAR(float, 0x4a94b4)   /* 105 */
#define k_0_0051f GAME_VAR(float, 0x4a94d8)   /* 0.00510000018 */
#define k_0_03f GAME_VAR(float, 0x4a9568)   /* 0.0299999993 */
#define k_m1f_4a95f4 GAME_VAR(float, 0x4a95f4)   /* -1 */
#define k_0_333f GAME_VAR(float, 0x4a9704)   /* 0.333000004 */
#define k_6_66f GAME_VAR(float, 0x4a9714)   /* 6.65999985 */
#define k_450f GAME_VAR(float, 0x4a9718)   /* 450 */
#define k_0_001111111f GAME_VAR(float, 0x4a971c)   /* 0.00111111114 */
#define k_150f GAME_VAR(float, 0x4a9720)   /* 150 */
#define k_0_0005555556f GAME_VAR(float, 0x4a9724)   /* 0.000555555569 */
#define k_0_75f GAME_VAR(float, 0x4a9730)   /* 0.75 */
#define k_900f GAME_VAR(float, 0x4a9734)   /* 900 */
#define k_572_9578f GAME_VAR(float, 0x4a9738)   /* 572.957764 */
#define k_9000000f GAME_VAR(float, 0x4a973c)   /* 9000000 */
#define k_250000f GAME_VAR(float, 0x4a9740)   /* 250000 */
#define k_170f GAME_VAR(float, 0x4a9748)   /* 170 */
#define k_0_04f GAME_VAR(float, 0x4aa25c)   /* 0.0400000028 */
#define k_256f GAME_VAR(float, 0x4aa260)   /* 256 */
#define k_128f GAME_VAR(float, 0x4aa264)   /* 128 */
#define k_0_125f GAME_VAR(float, 0x4aa274)   /* 0.125 */
#define k_0_01666667f GAME_VAR(float, 0x4aa2a8)   /* 0.0166666675 */
#define k_0_2f_4aa400 GAME_VAR(float, 0x4aa400)   /* 0.200000003 */
#define k_0_7083333f GAME_VAR(float, 0x4aa414)   /* 0.708333313 */
#define k_m180f GAME_VAR(float, 0x4aa418)   /* -180 */
#define k_0_005f_4aa428 GAME_VAR(float, 0x4aa428)   /* 0.00499999989 */
#define k_4000f GAME_VAR(float, 0x4aa434)   /* 4000 */
#define k_1_1f GAME_VAR(float, 0x4aa438)   /* 1.10000002 */
#define k_16f GAME_VAR(float, 0x4aa43c)   /* 16 */
#define k_300f GAME_VAR(float, 0x4aa440)   /* 300 */
#define k_200000f GAME_VAR(float, 0x4aa444)   /* 200000 */
#define k_0_001745329f GAME_VAR(float, 0x4aa44c)   /* 0.00174532935 */
#define k_0_00125f GAME_VAR(float, 0x4aa450)   /* 0.00124999997 */
#define k_m0_002f GAME_VAR(float, 0x4aa470)   /* -0.00200000009 */
#define k_30000f GAME_VAR(float, 0x4aa474)   /* 30000 */
#define k_0_85f GAME_VAR(float, 0x4aa478)   /* 0.850000024 */
#define k_14_11765f GAME_VAR(float, 0x4aa48c)   /* 14.1176472 */
#define k_0_06666667f GAME_VAR(float, 0x4aa490)   /* 0.0666666701 */
#define k_14_0625f GAME_VAR(float, 0x4aa494)   /* 14.0625 */
#define k_75f GAME_VAR(float, 0x4aa504)   /* 75 */
