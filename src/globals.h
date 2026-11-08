/* globals.h: the game's global variables named (tools/name_globals.py adds them): each is the game's own
   memory at its address, with the type it is used as. A use with another type is written (*(type *)&name)
   (tools/names/retype_uses.py). */
#pragma once

#define g_lobbyConnectionOpen GAME_VAR(int, 0x4db718)   /* 1 while the lobby server connection is open (lobby_openConnection, arenaGames_mouse button 1 / key T); lobby_openConnection skips reconnecting when set; 0 on disconnect, back / S, or a LAN search started; 0 on entering the arena list */
#define g_lobbySearching GAME_VAR(int, 0x4db858)   /* 1 while the arena list waits for the lobby server's game list (lobby_openConnection, button 1 / key T); ended when the answer is in (g_serverAnswerIn, g_searchResult) or the list is merged; part of lobby_busy; the room list frame also clears it */
#define g_lobbyRefreshing GAME_VAR(int, 0x4db8b8)   /* 1 while the arena list fills after the lobby's list came (g_searchResult 1): arena_mergeReceivedSessions every g_listRefreshPeriod (g_arenaListRefreshTimer), last merge and 0 once g_netListDone; 0 when cancelled (back / S); part of lobby_busy. The game room's list (gameList_pageFrame) also sets it on its own list's answer, and nothing there reads or clears it: it stays 1 until the arena list is entered */
#define g_listBlinkClock GAME_VAR(float, 0x4dba80)   /* the lists' searching clock: counts down by g_listBlinkRate x g_frameTime (blink step = clock/3 % 15; back to 1000 below 10); 1 when a search / refresh stops (games_stop); also the LAN search's time-out (150 at its start; arena_gamesPageFrame ends the search at 0); shared by the arena list, the game room's list and the ranking page */
#define g_lanSearch GAME_VAR(int, 0x4dba90)   /* 1 while the arena list's local-network search runs (arenaGames_mouse button 0 / key I): the list frame polls dplay_listSessions 10x a frame until g_listBlinkClock (from 150) runs out, then arenaList_rebuild and 0; part of lobby_busy */
#define g_arenaCameraMode GAME_VAR(int, 0x4dbb3c)   /* the arena lobby camera's move (arena_camera): 1 going to the sub-screen's point (g_lobbySubState; set by the lobby_enter* functions), 0 going home (leaving: back, joined, hosted), 2 arrived; the lobby pages draw and take clicks only at 2 */
#define g_joinTimedOut GAME_VAR(int, 0x4dbb78)   /* a join's DirectPlay session search timed out (WM_TIMER 0x378 after 30 ticks); the next join answer (arena_joinAnswer / room_joinAnswer) leaves the session with message 0x44 CONNETION TIME OUT */
#define g_enteringMenus GAME_VAR(int, 0x4deb48)   /* 1 while the menu tunnel camera enters the menus (menuTunnel_advance: rings of 950 steps, eye and look x / y at 0): set by reset_menus, entering screen 300 (screen_enter) and EXIT to the pilot screen; cleared when the ring move ends or on a main menu choice */
#define g_dialogFrameTexture GAME_VAR(int, 0x4deb50)   /* texture id of iftex/boxscreen (g_menuFrameTextures[1], loaded at start-up): the window frame every dialog draws (menu_drawTexture / menu_drawTextureFlipped in the menu dialogs, lists, forms and setup pages) */
#define g_hostAnswer GAME_VAR(int, 0x4ded60)   /* the server's answer to a hosting announcement: 2 none / handled (set by lobby_announceArena, room_announceGame, lobby_openConnection, gameList_refresh), 1 allowed (arena_takeHostAnswer / room_hostingStep host now), 0 other reply, 3 version outdated (g_arenaUpdateNotice), 4 refused (MSG 0x46 / 0x2a SERVER IS BUSY); WndProc sets it from g_lobbyStatus / g_gameServerStatus (0x66 -> 1, 0x67 -> 3, 0x29 / 0x28 -> 4, else 0) */
#define g_rightClick GAME_VAR(int, 0x4ded8c)   /* g_mouseClicked[1]: the right button clicked this frame */
#define g_playerCorporation GAME_VAR(int, 0x4dedd0)   /* the player's corporation (team colour): 0 RED, 1 BLUE, 2 YELLOW (axis.cfg set_player color: cfg_readPlayer / cfg_writePlayer; 0 by default); the player data passed to dplay_host / dplay_join in the arena; copied to / from g_arenaCorporation */
#define g_serverAnswerIn GAME_VAR(int, 0x4df018)   /* 1 when the lobby server's game-list answer is in: WndProc on g_lobbyListAnswer 0x29 / 0xca / 0xcb (with g_searchResult 4 / 1 / 3); the arena list frame handles it while g_lobbySearching and clears it; also set by lobby_stopSearch and the cancel / back keys */
#define g_matchMode GAME_VAR(int, 0x5ae9c4)   /* the kind of match set up / played: 0 none (solo; after a replay), 1 an arena (the lobby), 2 the game room's (a Ladder game: Scene.ladderGame), 3 the skirmish campaign; written into replays' headers, and on leaving a match picks the screen to return to (game_return*) */
#define g_listRefreshPeriod GAME_VAR(int, 0x5b1914)   /* the game lists' merge period in 1/60 s (g_frameTime): 30 when a list opens or is refreshed (lobby_enterArenaList, lobby_openConnection, gameList_refresh, room list entry), 5 after each merge; compared with g_arenaListRefreshTimer / g_roomListRefreshTimer */
#define g_panelGlow GAME_VAR(float, 0x680ccc)   /* the hovered menu panel's glow: 40 when a new panel is hovered (g_lastPanel changes), then moved by g_panelGlowStep x g_frameTime between 2 and 38 while g_panelHovered; the panel's highlight alpha is 1 minus a fraction of it (setup_pages.c) */
#define g_chosenGameMode GAME_VAR(int, 0x76d368)   /* the game mode of the match to start (0 DEATH MATCH, 1 TEAM DEATH MATCH .. 14 ACCEPT ADVANCED MODE; odd modes up to 11 are team games): from the arena record, a joined session, room or skirmish round; set_round (14 up: the map's own mode); replay header */
#define g_launchedForNetGame GAME_VAR(int, 0x76d410)   /* started by the launcher for a network game: command line "-net" (axiswl.dat present: host) or "<x> -ip <server>" (join); skips the file checks, drives the automatic start (g_launchStartStep) and quits after the match (game_postMatch) */
#define g_mapRotation GAME_VAR(int, 0x9da3e0)   /* the match's map rotation: 1 every chosen map (g_mapChoiceKeptTable) in turn, 0 the one map g_mapIndex (match_start); from the arena record (g_arenaRotation), a joined session or room; 0 in skirmish, 1 solo; replay header; read at a round's end */
#define g_launchStartStep GAME_VAR(int, 0x9da49c)   /* the launcher-started game's automatic start (g_launchedForNetGame): 0 none (also cleared by menu_showMessage), 0x65 profile logged in, 0x66 menus entered (ARM CENTER), 0x67 ARM CENTER left (menu_cameras then calls arena_startFromLauncher), 0x68 hosting / 0x69 joining (menu_frame then takes no mouse or keys) */
#define g_buttonTexture GAME_VAR(int, 0x9db0a4)   /* texture id of iftex/option (loaded at start-up): the buttons and tabs of the menus' dialogs, game lists, map lists and ARM CENTER pages */
#define g_roomCameraMode GAME_VAR(int, 0x9dce48)   /* the game room camera's move (room_camera): 1 going to the page's point (g_roomState), 0 going home (leaving a page), 2 arrived; the room's pages (game list, ranking, settings, login) draw and take clicks only at 2 */
#define g_roomLoginDue GAME_VAR(int, 0x9dd1c8)   /* 1 once the Ladder login's LOG IN is asked (click or I key: roomLogin_clicks / roomLogin_keys) until answered or cancelled; the dialog's buttons are blocked meanwhile; cleared by a bad-character message (login_send, account_sendChange), cancel2 or leaving */
#define g_lineToLoginId GAME_VAR(int, 0x9dd1cc)   /* 1 when the input line belongs to the Ladder login's ID field (roomLogin_clicks button 0, field steps): roomLogin_endTyping then copies g_inputLine into g_accountName (30 bytes) and clears it */
#define g_rankingPage GAME_VAR(int, 0x9dd6ac)   /* the Ladder ranking's page shown (0 .. 99, not past g_rankingLastPage): ranking_page asks for ranks page x 10 + 1 on (message 0x15); stepped by ranking_prevPage / ranking_nextPage; put back from g_rankingPrevPage when a wait is cancelled */
#define g_roomRequestOut GAME_VAR(int, 0x9dd838)   /* 1 while the Ladder login sent by login_send awaits the game server's answer (roomLogin_update: g_gameServerAnswer 33 accepted, 42 update notice, others messages); the dialog shows a connecting box and only cancel2 works (roomLogin_keys) */
#define g_replayFileCount GAME_VAR(int, 0x9dd928)   /* the number of replays (.ape files in the autoplay folder) listed into g_replayList by autoplay_listFiles (at most 1023; 0 when replayList_open starts): the replay selection dialog's rows; replaySelect_ok copies it to g_replayListCount */
#define g_currentProfile GAME_VAR(int, 0x9f8c58)   /* index of the current pilot profile in g_profiles (0x48-byte records): written to / read from axisuser.dat's header (from g_profileChosen on writing; the profile matching g_profileName on reading); its name gives g_profileName and g_cfgPlayerName */
#define g_netLastRequest GAME_VAR(int, 0xa0b300)   /* the kind of the last packet sent that awaits a reply (net_send: 10 .. 12, 13 the game list, 14 / 15, 17 .. 22, 27 .. 29); the reply reader (0x452620) reads the answer by it; 0 once the reply ends (list complete, player list end) or the sockets close */
#define g_lobbyListAnswer GAME_VAR(int, 0xa0b36c)   /* the lobby server's answer to the game-list request (net_receiveLobbyReply): 0xca the list complete (ping thread started), 0xcb reply kind 2 (WndProc -> g_searchResult 3: update notice), 0x29 reply kind 3 (-> result 4: MSG 0x46 SERVER IS BUSY); 0 none (cleared when leaving) */
#define g_dplaySessionCount GAME_VAR(int, 0xa0b41c)   /* the number of DirectPlay sessions in g_sessionTable: net_addSession adds one, net_freeSessionList empties it, dplay_openConnection sets 0; net_getSession's range check (taken inclusive); net_sessionCount returns it */
#define g_localPlayerId GAME_VAR(u32, 0xa0b424)   /* the local DirectPlay player's id (CreatePlayer in dplay_hostSession / dplay_joinSession): the sender of net_sendMessage and chat lines, the claimed slot's id; destroyed and 0 in dplay_release; 0 on dplay_openConnection */
#define g_lobbyConnectionBlock GAME_VAR(void *, 0xa0baf4)   /* the GlobalAlloc'ed DPLCONNECTION of a DirectPlay lobby that started the game (dplay_lobbyConnect): flags 0x44 and 16 players set, ConnectEx, the player created with its name, g_isHost from its flags; freed and 0 in dplay_release */
#define g_isHost GAME_VAR(int, 0xa0baf8)   /* 1 when this machine hosts the DirectPlay session (dplay_hostSession, or a lobby connection's create flag), 0 joined; the host claims slots for joining players (net_handleSystemMessage) and sends the host-left message (dplay_leaveSession, game_postMatch) */
#define g_pingTime GAME_VAR(u32, 0xa0d798)   /* the last ICMP ping's round trip in ms (net_ping: 0 when the echo failed without a time, 1 for 0 ms); net_pingAllServers stores it (less 400 when above 1000) into g_serverPing; 0 before each ping (net_pingServer) */
#define g_netListDone GAME_VAR(int, 0xa0d7a0)   /* 1 when the server pinging is over (net_pingAllServers) or a list is left / cancelled; 0 by net_clearServers; stops the ping loop, ends the arena / room list refresh with a last merge, and lets the merges clear their search flags */
#define g_soundBaseVolume GAME_VAR(int, 0xa0e66c)   /* the sound effects' base level from the volume setting (sound_setVolume: p = g_soundVolume x v / 100; -1000 below 0, 0 above 100, else (p x 5 - 500) x 20 x k_0_1f); sounds play at volume% of the range -10000 .. it, or at it for volume above 100 */
#define g_randPos GAME_VAR(u32, 0xa1efb8)   /* the position in the game's random table g_randTable (4096 values): each draw (rand_below and the match_start / actor_frame / frame_loops random helpers) takes entry pos & 0xfff and adds 1 */
#define g_joinThroughServer GAME_VAR(int, 0x4dbaac)   /* the game list is the lobby server's (1, lobby_openConnection / arenaGames connect) rather than the LAN search's (0, set when the DirectPlay search starts); picks the join path: password check + arena_askJoinPassword (1) or arena_joinSession via g_lanJoinRequest (0) */
#define g_lanJoinRequest GAME_VAR(int, 0x4dbbf0)   /* join the selected LAN (DirectPlay-listed) game: set by lobby_join when the list is not the server's (g_joinThroughServer 0); arena_gamesPageFrame then calls arena_joinSession(g_pickedGame) */
#define g_setupTunnelDepth GAME_VAR(float, 0x4ddd90)   /* the setup screen tunnel's depth (glTranslatef z of its walls, setup_pages.c): -1400 on entering the setup, run down with the panel's ease (setup_easePanel) until past k_panelSlideEnd, then -1650; -1650 when a tab opens (setup_keys.c) */
#define g_arenaMap GAME_VAR(signed char, 0x4ded40)   /* the arena record's map (g_arenaName +0x20, signed byte 0 .. 21; axis.cfg set_server map): g_mapIndex when hosting, sent in the arena packet; special_map may change it */
#define g_arenaMaxPlayers GAME_VAR(u8, 0x4ded41)   /* the arena record's most players (+0x21; 0 .. 16, else 8; axis.cfg set_server numofplayer): passed to dplay_host, sent in the arena packet (see g_arenaMap) */
#define g_arenaGameType GAME_VAR(u8, 0x4ded43)   /* the arena record's game type (+0x23; 0 DEATH MATCH .. 14 ACCEPT ADVANCED MODE, else 0; axis.cfg set_server type): g_chosenGameMode when hosting, sent in the arena packet (see g_arenaMap) */
#define g_arenaFragLimit GAME_VAR(u8, 0x4ded44)   /* the arena record's frag limit (+0x24; at most 250, else 30): g_fragLimit when hosting, sent in the arena packet; the two limits are also read together as one word (see g_arenaMap) */
#define g_arenaTimeLimit GAME_VAR(u8, 0x4ded45)   /* the arena record's time limit (+0x25; at most 250, else 30): g_timeLimit when hosting, sent in the arena packet (see g_arenaFragLimit) */
#define g_playerCustomize GAME_VAR(int, 0x4dedd4)   /* axis.cfg's "set_player customize" ON (1) / OFF (cfg_readPlayer / cfg_writePlayer; copied to and from g_arenaCustomize by arena_loadPlayerSettings / arena_savePlayerSettings); nothing else reads it */
#define g_panelGlowStep GAME_VAR(float, 0x4df454)   /* the hovered panel's glow step per frame time: +1 or -1 (g_panelGlow bounces between 2 and 38) */
#define g_fragLimit GAME_VAR(int, 0x4df8e8)   /* the match's frag limit: from the arena record, a joined session or room, or the skirmish round; into the rotation rounds and the scene (match_start), the replay header, the loading screen (FRAG LIMIT: %d) and axiswl.log */
#define g_soundVolume GAME_VAR(int, 0x4e0c90)   /* the sound effects' volume 0 .. 100 (axis.cfg sound block, default 100; g_soundSettings[0]): sound_setVolume turns it into g_soundBaseVolume; also gives g_menuVolume ((v x 5 - 500) x 4) at loading */
#define g_desktopWidth GAME_VAR(int, 0x67eefc)   /* the desktop's width in pixels (GetSystemMetrics(SM_CXSCREEN) at start-up, win32.c): the screen width for video mode 7 DESKTOP (app_screenSizeForMode), the size the display mode goes back to, the ending movie's width */
#define g_menuCameraLook GAME_VAR(float, 0x680378)   /* the menu camera's look-at x (g_menuLook[0]; y and z follow) */
#define g_launchedAsHost GAME_VAR(int, 0x76d364)   /* started by the launcher with "-net" and axiswl.dat present: arena_startFromLauncher hosts the arena from axiswl.dat's settings (0: it joins g_serverAddressArg instead) */
#define g_timeLimit GAME_VAR(int, 0x76d408)   /* the match's time limit: from the arena record, a joined session or room, or the skirmish round; into the rotation rounds and the scene (match_start), the replay header, the loading screen (TIME LIMIT: %d) and axiswl.log */
#define g_rankingListIn GAME_VAR(int, 0x76d40c)   /* 1 when the ranking's player list has all arrived (WndProc, from g_playerListDone): ranking_page then fills the page (ranking_fillPage), keeps the sort and page, and clears it; cleared on a page / sort change or a cancelled wait */
#define g_desktopHeight GAME_VAR(int, 0x76d430)   /* the desktop's height in pixels (GetSystemMetrics(SM_CYSCREEN) at start-up): see g_desktopWidth */
#define g_windowDC GAME_VAR(void *, 0x76d480)   /* the game window's DC (WM_CREATE; SwapBuffers on it); at start-up briefly the desktop's, for its depth */
#define g_videoMode GAME_VAR(u32, 0x83a9c0)   /* the screen size choice (axis.cfg graphics section): 0 640x480, 1 1280x720, 2 1600x900, 3 1920x1080, 4 2560x1440, 5 3840x2160, 6 1024x768, 7 DESKTOP (g_desktopWidth x g_desktopHeight); app_screenSizeForMode sets g_screenW / g_screenH from it */
#define g_videoDepth GAME_VAR(int, 0x83a9c4)   /* the colour depth choice: 0 16 bits, 1 32 bits (axis.cfg "32"); used as (v + 1) * 16 colour bits */
#define g_lastPanel GAME_VAR(int, 0x907b24)   /* the menu panel hovered last (hovered_panel, the main menu's panels): hovering another restarts the glow (g_panelGlow 40, g_panelGlowStep -1); 999 (none) when the arena list, room list or arena screen is entered */
#define g_roomSearchAnswerIn GAME_VAR(int, 0x9da498)   /* 1 when the game server's room-list answer is in: WndProc on g_roomListAnswer 0x28 / 0xca / 0xcb (with g_searchResult 4 / 1 / 3); the room list frame handles it while g_roomSearching and clears it */
#define g_replayShowOn GAME_VAR(int, 0x9db994)   /* picked replays are being shown (replaySelect_ok sets it): on the main menu (screen 300) menu_frame zooms in and starts the next replay (g_replayRunning); it stays set between replays until the game-menu key during one (replay_frame clears it); the main menu takes no clicks / keys while it is 1 */
#define g_lineMaxLength GAME_VAR(int, 0x9dcd30)   /* the open text field's length (menu_clearInputBuffer's argument: 0x10 pilot name / replay name, 0x14 address, 0x32 the watch chat, 0x38 the match chat (match_openTextField), a field's bufferLength ...): the bytes of g_inputLine wiped when the line is cancelled (menu_closeInputLine, newNameDialog_clicks) */
#define g_rankingRequestPending GAME_VAR(int, 0x9dd350)   /* 1 when a ranking page is to be asked for: ranking_page sends message 0x15 (the sort column's code and the page's first rank), starts the wait (g_rankingWaiting) and clears it; set by page / sort changes and once the page's frame has opened */
#define g_rankingHaveList GAME_VAR(int, 0x9dd3b0)   /* 1 while the ranking table has rows to show (after ranking_fillPage, or a wait cancelled with the old list); 0 on a page / sort change or on closing; the table draws its rows only then */
#define g_lineToLoginPassword GAME_VAR(int, 0x9dd6b0)   /* 1 when the input line belongs to the Ladder login's password field (button 1, field steps; 1 on entering the login): roomLogin_endTyping then copies g_inputLine into g_accountPassword (12 bytes) and clears it */
#define g_roomConnected GAME_VAR(int, 0x9dd84c)   /* 1 while logged in to the Ladder game server (the login record taken, or a new ID accepted: answer 33); its WM_TIMER 0x115c then sends keep-alive packet 0x18 (WndProc, the edit control's proc); 0 at start-up and on leaving the room */
#define g_argCount GAME_VAR(int, 0x9dd88c)   /* the number of words in the launch command line (app_parseCommandLine, pointers in g_launchArgs): 1 for "-net" (host from axiswl.dat), 3 for "<x> -ip <server>"; 0 for an empty or too long line */
#define g_replayRandomOrder GAME_VAR(int, 0x9eeac0)   /* the replay show's RANDOM option (tick box in the replay selection dialog, R key): 1 the next replay is picked at random (replay_next), 0 in order; 0 by default (resets.c) */
#define g_chosenPilot GAME_VAR(int, 0x9f8d6c)   /* the pilot (character) of the profile chosen in the list (its record +0x40), set by profile_drawChosenPilot, which draws its portrait, name, corporation, sex, age and stats */
#define g_hostGoneMessageFlag GAME_VAR(int, 0x9f941c)   /* word +4 of the type-2 message at g_netHostLeftMessageKind (0x9f9418) that the host sends when it closes the session (dplay_leaveSession, game_postMatch's send_host_leaving, freeCam_keys): 1 while sent; receivers copy it into g_netHostGone and free the session (net_handleMessage case 2) */
#define g_netBlockSize GAME_VAR(u32, 0x9fd940)   /* the receive buffer size for DirectPlay messages in net_receiveAll (grown when DirectPlay says it is too small): the length passed to net_handleMessage (a type 7 message over 0x49 bytes is dropped); 0 after the buffer is freed */
#define g_roomListAnswer GAME_VAR(int, 0xa0b34c)   /* the game server's answer to the room-list request (net_receiveGameServerReply): 0xca the list complete (ping thread started), 0x28 reply kinds 2 / 3 (WndProc -> g_searchResult 4: MSG 0x2a SERVER IS BUSY); 0 none */
#define g_serverListCount GAME_VAR(int, 0xa0b368)   /* the number of arena servers the lobby listed into g_serverList (net_addServerRecord); to g_serverPingCount when the list completes; arena_mergeReceivedSessions' new-entries flag; 0 on a new search; the arena list's page count when not a LAN list */
#define g_sessionListOpen GAME_VAR(int, 0xa0b384)   /* 1 while the DirectPlay session list is in use (dplay_openConnection sets it); dplay_leaveSession / net_freeSessionList need it */
#define g_serverPingCount GAME_VAR(int, 0xa0d79c)   /* the number of listed servers to ping and merge (net_pingAllServers, the merges): the server or room count when the list completes (net_receiveLobbyReply / net_receiveGameServerReply); 0 by net_clearServers */
#define g_glWidth GAME_VAR(int, 0xa0e810)   /* the GL window's width in pixels (glWindow_init / glWindow_resize): its display mode in full screen, the projection and viewport (gfx_setMatchProjection), the HUD's 2D box; gfx_getWidth returns it */
#define g_glHeight GAME_VAR(int, 0xa0e928)   /* the GL window's height in pixels (see g_glWidth); gfx_getHeight returns it */
#define g_replayWrap GAME_VAR(int, 0x4b2a7c)   /* the replay show's AUTO REPEAT option (tick box in the replay selection dialog): 1 (the default, resets.c) the list starts over after the last replay, else the viewer quits there (replay_next) */
#define g_joinRow GAME_VAR(int, 0x4db710)   /* the game list row being joined (arena_joinListed / room_joinListed; 99999 for the address typed in, g_typedArenaAddress): the join answer (arena_joinAnswer / room_joinAnswer) joins that g_sessionList entry; arena_joinAnswer sets 0 after a typed one */
#define g_arenaServerList GAME_VAR(int, 0x4dbaa8)   /* the arena list shows the lobby server's games (lobby_openConnection sets 1; the LAN rebuild arenaList_rebuild clears it): rows with the lock icon and the ping; while g_arenaLanListBuilt is 0 the page count is g_serverListCount */
#define g_arenaLanListBuilt GAME_VAR(int, 0x4dbac8)   /* the LAN search's list built (arenaList_rebuild: g_sessionList from DirectPlay's sessions, count g_gameCount); cleared when the server is connected or the screen entered */
#define g_typingArenaPassword GAME_VAR(int, 0x4dbacc)   /* 1 while the new arena form's password field is typed (arena_editPassword): once typing ends the line goes into g_newArenaPassword (8 bytes) and it clears; blocks the form's and host-error box's clicks meanwhile */
#define g_arenaListClickTimer GAME_VAR(float, 0x4dbaf8)   /* the arena list's double-click window: grows by g_frameTime while g_arenaListClickArmed (a row clicked once); past 20 the click is disarmed; reset to 0 on each row click */
#define g_playerSetupLeft GAME_VAR(int, 0x4dbb68)   /* left x of the arena lobby's SETUP PLAYER dialog (100 on entering the arena screen; layouts.c places its fields from it): its frame, texture, buttons and corner ornaments (game_lists.c, lobby_states.c) */
#define g_playerSetupRight GAME_VAR(int, 0x4dbb70)   /* right x of the SETUP PLAYER dialog (540; see g_playerSetupLeft) */
#define g_playerSetupBottom GAME_VAR(int, 0x4dbb74)   /* bottom y of the SETUP PLAYER dialog (400; see g_playerSetupLeft) */
#define g_typingArenaPlayerName GAME_VAR(int, 0x4dbbd0)   /* the player's name (g_arenaPlayerName, 16 characters) being typed on the arena lobby's player page */
#define g_emptySlot0Asked GAME_VAR(int, 0x4dbc80)   /* 1 asks the weapons preview to empty item slot 0 (armc_updateWeaponsPreview: armc_itemSlotRecord(0, 0), then 0; armc_updatePartsPreview only clears it); never set to 1 (0 in .bss), so it never happens */
#define g_savedMechHead GAME_VAR(int, 0x4dc878)   /* the saved mech's head part (g_savedMechPartIds[0]; chest, arm, leg, booster follow) */
#define g_mechChanged GAME_VAR(int, 0x4dcc58)   /* 1 when the mech's parts changed (armc_stepPart, the ARM CENTER opened): armc_updatePartsPreview then puts the stepped part on the preview mech, reads the panels and stats again and clears it */
#define g_savedMechItemSlot4 GAME_VAR(int, 0x4dcf18)   /* the saved mech's item in slot 4 (g_savedMechSlotItems[0]: an extra item; [1] slot 5, [2] .. [5] weapon slots 0 .. 3): from record byte 5 / the profile's record (armc_state.c: into g_itemSlot4) */
#define g_setupPanelMoving GAME_VAR(int, 0x4dda60)   /* 1 while the setup screen's panel eases in (1 on entering the setup; setup_easePanel moves it and clears it at the end); no panel is hovered meanwhile; 0 when a tab opens (setup_keys.c) */
#define g_arenaRotation GAME_VAR(u8, 0x4ded42)   /* the arena record's map rotation switch (+0x22; axis.cfg "set_server customize" ON / OFF): g_mapRotation when hosting, the high byte of dplay_host's map word, sent in the arena packet; 0 for a launcher-started host */
#define g_menuEyeX GAME_VAR(float, 0x4df024)   /* the menu camera's eye x (g_menuEye[0]; y and z follow) */
#define g_characterTexture GAME_VAR(int, 0x4dfa00)   /* texture id of iftex/character (loaded at start-up): the pilot portraits (the profile screen's pilot select and chosen pilot, the skirmish screen) */
#define g_panelHovered GAME_VAR(int, 0x680398)   /* 1 while the pointer is on a menu panel (hovered_panel; on the main menu also not while the replay dialog is open); the panel glow (g_panelGlow) only moves then */
#define g_mapPreviewChanged GAME_VAR(int, 0x680cd0)   /* 1 when the map preview image must be loaded again (a map choice stepped, the arena / room create page entered): map_preview_box calls the reload, which loads g_mapPreviewTexture and clears it */
#define g_searchResult GAME_VAR(int, 0x76d484)   /* the outcome of the lobby / room list request, set with g_serverAnswerIn / g_roomSearchAnswerIn by WndProc: 1 list complete (refresh starts), 3 update notice, 4 server busy (message 0x46 / 0x2a); 0 when a request starts; -1 cancelled (back / S) */
#define g_mapPreviewTexture GAME_VAR(int, 0x9da324)   /* texture id of the chosen map's preview (<g_stageDir><map>/<map>): loaded by the map preview reload (room_clicks.c) and the skirmish screen; drawn in the create forms' map box (unless rotation: CUSTOM) and on the skirmish screen */
#define g_dikF1 GAME_VAR(int, 0x9da440)   /* the DirectInput scan code of F1 (0x3b, store_tables.c): opens the replay list on the main menu; on the controls tab it only gives a sound and is never bound */
#define g_replayRunning GAME_VAR(int, 0x9db990)   /* 1 while replays are shown: set by menu_frame when the main menu's replay show zoom ends (screen 9999); the start-up then plays the replays (scene_startSession(.., 3)) and game_postMatch takes match mode 0; cleared by reset_menus */
#define g_retypePassword GAME_VAR(int, 0x9dced0)   /* 1 when the Ladder login's password is to be typed again (set on entering the login, screen_enter.c / room_dialogs.c): roomLogin_update copies the account record back and opens the password field empty (roomLogin_editPassword), then clears it */
#define g_loginToSend GAME_VAR(int, 0x9dd198)   /* 1 when the Ladder login is to be sent (LOG IN clicked, or the I key): roomLogin_update then ends typing, calls login_send and clears it; 0 on entering the login */
#define g_rankingPrevPage GAME_VAR(int, 0x9dd1b4)   /* the ranking page before the last change (ranking_prevPage / ranking_nextPage) or the one last answered (ranking_page): put back into g_rankingPage when the wait is cancelled (button 3, S key) */
#define g_rankingPrevSort GAME_VAR(int, 0x9dd300)   /* the ranking's sort column before the last change (ranking_cycleSort, the sort buttons) or the one last answered: put back into g_rankingSort when the wait is cancelled */
#define g_typingLoginPassword GAME_VAR(int, 0x9dd38c)   /* 1 while the Ladder login's password field is typed (roomLogin_editPassword): once typing ends roomLogin_update takes the line into g_accountPassword (12 bytes) and moves on by g_fieldStep; its stars are not drawn meanwhile */
#define g_rankingLast GAME_VAR(int, 0x9dd7dc)   /* the last rank on the ranking page shown (page x 10 + 10; 10 on entering): set by ranking_page and the table's draw, which shows "first ~ last"; only drawn */
#define g_typingLoginId GAME_VAR(int, 0x9dd830)   /* 1 while the Ladder login's ID field is typed (roomLogin_editId): once typing ends roomLogin_update takes the line into g_accountName (30 bytes) and moves on by g_fieldStep; the ID is not drawn meanwhile */
#define g_startTicks GAME_VAR(u32, 0x9dd8e8)   /* timeGetTime (ms) at start-up and at each clock check: sys_checkClockTampering compares the seconds since by it with those of the system clock (g_clockLastTime) */
#define g_tunnelFlyingIn GAME_VAR(int, 0x9eeaa8)   /* 1 while the main menu's tunnel flies in after a screen change (menuTunnel_advance); mainmenu_drawMenu clears it once g_mainMenuDepth reaches -550; no panel is hovered meanwhile */
#define g_profileRowClicked GAME_VAR(int, 0x9f900c)   /* 1 after a profile row click, for a double click: the same row clicked again before g_profileRowClickTime passes 20 (1/60 s) opens the log-in (g_profilePage 4); profile_listPage clears it when the time is up */
#define g_localSlot GAME_VAR(u8, 0x9fd954)   /* the local player's slot (0 .. 15): taken by net_claimLocalSlot or given by the host (net_handleMessage kind 6); sent in every packet (net_sendPacketData); also picks the slot's camera record in g_slotCams (freeCam_mouseLook, freeCam_keys) */
#define g_lobbySocket GAME_VAR(u32, 0xa055f8)   /* the lobby server's TCP socket (net_connect(100): connect_socket, status 200): the arena packets, game-list request and keep-alives go on it, net_receiveLobbyReply reads it; 0 once closed (net_closeSockets / net_disconnect) */
#define g_gameServerSocket GAME_VAR(int, 0xa05630)   /* the Ladder game server's TCP socket (net_connect(0x65), status 201): room list, login, ranking and room packets; game_postMatch returns to the game room when it is open; 0 once closed */
#define g_playerListDone GAME_VAR(int, 0xa0b350)   /* 1 when the game server's player (ranking) list has ended (net_receivePlayerListReply kind 1, the reply reader); WndProc then raises g_rankingListIn; cleared on a new ranking request */
#define g_roomListCount GAME_VAR(int, 0xa0b358)   /* the number of rooms the game server listed into g_roomList (net_addRoomRecord); to g_serverPingCount when the list completes; room_mergeReceivedSessions' new-entries flag; 0 on a new search; the room list's page count */
#define g_playerListCount GAME_VAR(int, 0xa0b35c)   /* the number of ranked players received into g_netPlayerList (net_addPlayerRecord); 0 on a new ranking request */
#define g_gameServerReportsOff GAME_VAR(int, 0xa0b364)   /* 1: nothing about the hosted room goes to the game server (net_handleSystemMessage's room-info updates, net_disconnect's leave packet 0x16), as g_lobbyReportsOff does for the lobby; never set (only written 0: gameList_mouse 0x436020 / 0x43616f, gameList_keys 0x4374e2; .bss), so those sends always go */
#define g_connectedServer GAME_VAR(int, 0xa0b380)   /* which server's socket is connected: 200 the lobby (g_lobbySocket), 201 the game server (g_gameServerSocket), 0 none (net_disconnect / net_closeSockets); net_handleSystemMessage sends the hosted record to that one */
#define g_localPlayerData GAME_VAR(u32, 0xa0b428)   /* the local player's data word given to dplay_hostSession / dplay_joinSession (the arena passes g_playerCorporation, the room 0); 2 bytes of it go into a claimed slot's packet +0x22 (net_takePlayerSlot); 0 on dplay_openConnection */
#define g_connectionCopy GAME_VAR(void *, 0xa0bab0)   /* the last GlobalAlloc'ed copy of a DirectPlay connection's data (dplay_enumConnections), stored by provider kind in g_dpConnections; freed in dplay_release but not cleared */
#define g_providerGuid GAME_VAR(const void *, 0xa0bad8)   /* points at the chosen DirectPlay service provider's GUID (g_tcpProviderGuid / ipx / modem / serial by connection kind, dplay_initConnection); the TCP compound address's DPAID_ServiceProvider data; also copied into the session descriptions' guidInstance (dplay_hostSession, dplay_enumSessions) */
#define g_storedConnection GAME_VAR(void *, 0xa0badc)   /* the connection data DirectPlay is initialised with (InitializeConnection in dplay_initConnection): g_dpConnections[kind], or for TCP/IP the compound address g_hostAddressBlock */
#define g_hostAddressBlock GAME_VAR(void *, 0xa0baf0)   /* the malloc'ed TCP/IP compound address (service provider and host address, CreateCompoundAddress) made by dplay_initConnection(0, ..); becomes g_storedConnection; freed and 0 in dplay_release */
#define g_pingStartEvent GAME_VAR(void *, 0xa0bb10)   /* the ping thread's wake-up event: set to make net_pingThreadProc ping the listed servers; reset when the thread is told to end (g_pingStopEvent) */
#define g_ptxTablesReady GAME_VAR(int, 0xa0e00c)   /* 1 once the PTX decoder's tables are set up (ptx_initTables on the first texture-dat image loaded by tex_loadImage) */
#define g_fullScreen GAME_VAR(int, 0xa0e920)   /* the GL window's full-screen flag (glWindow_init's argument): with 1 the display mode is changed to the window size (glWindow_setDisplayModeBy; cleared when that fails at init); checked again by glWindow_resize */
#define g_textWrapX GAME_VAR(int, 0x4ad490)   /* the text drawing's wrap x in pixels (text_setWrapX: 640 at start-up): text_passes.c starts a new line past it */
#define g_textBottom GAME_VAR(int, 0x4ad494)   /* the text drawing's bottom y in pixels (text_setBottom: 480 at start-up): text_passes.c stops drawing there */
#define g_lastCrosshair GAME_VAR(int, 0x4b04f8)   /* the crosshair whose texture the setup screen looked up last (-1 when the controls tab opens): a different g_crosshairEdit loads texture/crosshair/crosshairN into g_crosshairTexture */
#define g_timerFirstCall GAME_VAR(int, 0x4b1048)   /* 1 until timer_now's first call, which only takes the performance counter reading (g_timerLastCount) and clears it */
#define g_keepCameraAsked GAME_VAR(int, 0x4b2a70)   /* 1 after the menu tunnel camera finished a ring move (menuTunnel_advance): the next still frame keeps the camera again (camera_keep) and clears it */
#define g_matchProjMode GAME_VAR(int, 0x4c4de8)   /* the projection gfx_setMatchProjection set last (1 the 3D one, 0 the HUD's 2D one; -1 none: glWindow_init / glWindow_resize) */
#define g_convertHangul GAME_VAR(int, 0x4d23d0)   /* 1 (set at start-up, app_startupLoad): text drawing converts double-byte Korean syllables (text_hangulConvert) before splitting them into glyphs (text_passes.c) */
#define g_newArenaFragLimit GAME_VAR(u8, 0x4db54c)   /* the new arena form's frag limit (g_newArenaName record +0x24, GameSettings.limit[0]; 0 .. 250) */
#define g_newArenaTimeLimit GAME_VAR(u8, 0x4db54d)   /* the new arena form's time limit (g_newArenaName record +0x25, GameSettings.limit[1]; 0 .. 250) */
#define g_arenaListRefreshTimer GAME_VAR(float, 0x4dbaf0)   /* the arena list's refresh timer in 1/60 s: grows by g_frameTime while g_lobbyRefreshing; past g_listRefreshPeriod arena_mergeReceivedSessions runs and it goes back to 0; 0 on entering the arena list */
#define g_totalWeight GAME_VAR(float, 0x4dc78c)   /* the ARM CENTER mech's total weight: the ten parts' weights summed each frame by armc_drawWeightLine (shown red when above g_loadLimit); over the limit the stats panel's overload_loss / speed_overload_loss rows take off 4 x the excess share */
#define g_itemSlot4 GAME_VAR(int, 0x4dcb18)   /* g_armcSlotItems[0]: the item in slot 4, one of the extra list (g_extraListTable; -1 none; values seen 13 .. 34; the special items 27 .. 35 give bonuses, armc_applyExtraItemBonuses); from g_savedMechItemSlot4 by armc_loadSavedMech, kept back by armc_saveSelection */
#define g_itemSlot5 GAME_VAR(int, 0x4dcb1c)   /* g_armcSlotItems[1]: the extra item in slot 5 (see g_itemSlot4; from g_savedMechItemSlot5; armc_extraItemEquipped stops an item being taken twice) */
#define g_retintAllParts GAME_VAR(int, 0x4dd074)   /* 1: the ARM CENTER's parts all re-tinted with their own slots' colours on the next armc_retintParts (which clears it); set only by armc_makeSession when the scene session is made (the slider changes are g_coloursChanged) */
#define g_setupPanelPos GAME_VAR(float, 0x4de03c)   /* the setup screen's slide-in ease value: 0 on entry (menuState600_enterSetup), eased toward k_panelSlideTarget by setup_easePanel while g_setupPanelMoving; each step's size also pulls g_setupTunnelDepth in */
#define g_crosshairEdit GAME_VAR(int, 0x4de1cc)   /* the setup page's crosshair (0 .. 7): g_controlsEdit[0x43], the edit copy of g_crosshairSetting (copied in / out with g_controlsEdit) */
#define g_mouseInvert GAME_VAR(int, 0x4df000)   /* axis.cfg's "set_mouse convertmouse" ON (1) / OFF (0): the mouse's vertical offset negated in matches and replays (mouse_offset, replay_frame); default 0 (input_setDefaultBindings) */
#define g_mouseSensitivity GAME_VAR(int, 0x4df008)   /* axis.cfg's "set_mouse sensitivity" (default 50): the mouse offsets scaled by ((s x 0.02)^2 + 1) / 2 (mouse_offset, match_combatInput, replay_frame) */
#define g_crosshairSetting GAME_VAR(int, 0x4df00c)   /* axis.cfg's "set_mouse crosshairs" (0 .. 7, default 0): the match loads "Texture/Crosshair/Crosshair<n>" (game_processLoadingMode); edited on the setup page as g_crosshairEdit */
#define g_roomMap GAME_VAR(signed char, 0x4df9e8)   /* the room form's map (GameSettings.map at g_roomSettingsName + 0x20): stepped by room_stepMap (skipping 22 .. 24), copied from / to g_roomRecMap; its preview by room_loadMapPreview */
#define g_roomFragLimit GAME_VAR(u8, 0x4df9ec)   /* the room form's frag limit (g_roomSettingsName + 0x24): +5 up to 50 by room_settingsClicks, or typed (roomSettings_keys); 10 by room_setLadderDefaults; from g_roomRecFragLimit */
#define g_roomTimeLimit GAME_VAR(u8, 0x4df9ed)   /* the room form's time limit (g_roomSettingsName + 0x25): +5 up to 60 by room_settingsClicks, or typed (roomSettings_keys); 10 by room_setLadderDefaults; from g_roomRecTimeLimit */
#define g_sound3D GAME_VAR(int, 0x4e0c98)   /* axis.cfg's "3dsound": only the setup page and axis.cfg use it (3D SOUND does nothing) */
#define g_menuTunnelTexture GAME_VAR(int, 0x4e0cd0)   /* texture id of "iftex/menu34" (menu_loadTextures): the menu tunnels' panel and stripe layers (setup_drawTunnel layers 0 / 1, menu_tunnel layers 0 / 1) */
#define g_desktopDepth GAME_VAR(int, 0x76d3ec)   /* the desktop's colour depth (GetDeviceCaps BITSPIXEL, app_init): passed when the desktop mode is put back (app_shutdown, a failed app_startupLoad); app_setDisplayMode ignores it */
#define g_frameCounter40 GAME_VAR(int, 0x9da908)   /* frames counted by menu_drawTextCursor, back to 0 past 40; nothing else reads it */
#define g_lastTime GAME_VAR(double, 0x9db988)   /* the time timer_now last returned (seconds, double; g_timerClocks[1]): a new time equal to it 100000 calls in a row is moved on by 1 (g_timerRepeatCount) */
#define g_pixelFormatFilled GAME_VAR(u8, 0x9dbefc)   /* bit 0 set once gfx_setPixelFormat has filled the game's pixel format descriptor (0x4b1020: (g_videoDepth + 1) x 16 colour bits, 16 depth bits) */
#define g_directInputMade GAME_VAR(int, 0x9dbf0c)   /* 1 once app_startupLoad has made DirectInput (input_createDirectInput), so it is made only once */
#define g_rankingPrevRank GAME_VAR(int, 0x9dd328)   /* the ranking: the previous page's last rank (ranking_fillPage stores it; the next page's first row takes it when its value ties g_rankingPrevValue); 0 from ranking_enter / ranking_cycleSort */
#define g_editingRoomName GAME_VAR(int, 0x9dd380)   /* 1 while the room form's game name is typed (room_editGameName); roomSettings_keys takes the line into g_roomSettingsName and clears it; room_enterCreatePage clears it */
#define g_openLoginName GAME_VAR(int, 0x9dd4a0)   /* 1: newIdForm_update opens the name field (newIdForm_openField(0)) on its next call and clears it; set by room_openNewIdForm */
#define g_rankingLastPage GAME_VAR(int, 0x9dd4b8)   /* the ranking's last page: 999 until a page shows an empty row (ranking_drawTable stores g_rankingPage there); ranking_nextPage stops at it */
#define g_newIdAnswerAwaited GAME_VAR(int, 0x9dd6a4)   /* 1 once the new ID was sent (newId_register): newIdConfirm_update then reads the server's answer (g_newIdAnswer) */
#define g_roomListRefreshTimer GAME_VAR(float, 0x9dd6c0)   /* the time (1/60 s, g_frameTime) since the room's game list was last merged while it refreshes (gameList_pageFrame, g_roomRefreshing): past g_listRefreshPeriod room_mergeReceivedSessions runs and it is reset to 0; room_enterGameList clears it */
#define g_roomPanelsSliding GAME_VAR(int, 0x9dd7d8)   /* 1 while the game room's panels slide in (menuState800_enterGameRoom sets it; room_slideMenu (menu_slide) clears it when g_roomTunnelDepth is past k_panelSlideEnd): the room's keys, clicks and panel hover are off meanwhile */
#define g_rankingFirst GAME_VAR(int, 0x9dd83c)   /* the ranking page's first rank shown ("first ~ last"; page * 10 + 1): written by ranking_enter / ranking_drawTable / ranking_page, never read */
#define g_inputFont GAME_VAR(void *, 0x9dd8e4)   /* the 12-pixel Fixedsys font (CreateFontIndirectA) given to the hidden EDIT control by editField_createEdit (WM_SETFONT); made anew each call, never deleted */
#define g_clockCheckQuits GAME_VAR(int, 0x9dd904)   /* 1: a clock found set back closes the game (sys_checkClockTampering posts WM_CLOSE); 0: only the message and the check restarted. app_init sets 1 before the first check; nothing clears it */
#define g_replayListCount GAME_VAR(int, 0x9eeab8)   /* how many g_replayList entries scene_startSession (mode 3, replays) scans for picked ones: g_replayFileCount, set by replaySelect_ok */
#define g_writeMatchLog GAME_VAR(int, 0x9f67ec)   /* 1 when a round has ended (round_over): match_frame then writes the match log (in a launcher net game, g_launchedForNetGame) and clears it */
#define g_lastChatLine GAME_VAR(char *, 0x9fd948)   /* the last chat line: a received one as "<name> > <text>" in a GlobalAlloc block (net_formatChatLine), or g_inputLine for one the free camera sent (freeCam_keys); only net_handleMessage reads it (to zero it, the old block not freed) */
#define g_lastChatLineSet GAME_VAR(int, 0x9fd95c)   /* 1 when g_lastChatLine was set (net_handleMessage, freeCam_keys; 0 for an empty line): never read */
#define g_netConnected GAME_VAR(int, 0xa0b2fc)   /* 1 while connected to a server (net_connect sets it before connecting); net_disconnect only sends the leave records and closes the sockets while it is 1, then clears it */
#define g_lobbyReportsOff GAME_VAR(int, 0xa0b360)   /* 1: nothing about the hosted arena goes to the lobby server (net_handleSystemMessage's player join/leave updates, net_disconnect's leave record): set entering the arena list (lobby_enterArenaList) and on WM_CLOSE; cleared entering a create page (lobby_enterCreate, room_enterCreatePage) */
#define g_gameServerAnswer GAME_VAR(int, 0xa0b378)   /* the game server's answer to request 14, the login (net_recv: 0x1f, 0x20, 0x21 accepted, 0x22, 0x28, 0x2a); roomLogin_update acts on it and clears it; roomLogin_keys' cancel clears it */
#define g_dplaySessionOpen GAME_VAR(int, 0xa0b390)   /* 1 once dplay_openConnection has opened a session; dplay_leaveSession does nothing unless it is 1 (and g_sessionListOpen), then clears it */
#define g_serviceProviderCount GAME_VAR(int, 0xa0bac8)   /* DirectPlay service providers seen by dplay_enumConnections (counts up to 9; picks the slot of its local name buffer) */
#define g_pingStopEvent GAME_VAR(void *, 0xa0bf1c)   /* the ping thread's stop event (net_startPingThread): set by net_stopPingThread so net_pingThreadProc calls ExitThread; closed by net_closeThreadHandles */
#define g_glColourBits GAME_VAR(int, 0xa0e818)   /* glWindow_init's colourBits, kept for the display mode and the pixel format; the game passes g_videoDepth (match_enter), so it holds that 0 / 1 choice, not a bit count */
#define g_glDepthBits GAME_VAR(int, 0xa0e924)   /* glWindow_init's depthBits, kept for the pixel format (glWindow_setupPixelFormat's depth bits) */
#define g_defaultColour GAME_VAR(int, 0xa1f220)   /* a packed colour, 0 (colour_initPackedClear): fills player flag images (playerRecord_resetFlag) and the flag atlas (scene_reset), and is the stage's defaultColour (stage_resetMatrixAndPoints) */
#define g_logHook GAME_VAR(void *, 0xae2ec8)   /* the log hook log_message hands each formatted message to (none: nothing): loading_drawScreen while game_processLoadingMode loads a match, 0 once loading ends */
#define g_displayModeChanged GAME_VAR(u8, 0xb12a80)   /* 1 while the game has the display in a mode other than the desktop's (app_setDisplayMode); cleared when the desktop mode is put back; game_wndProc (WM_ACTIVATEAPP) gives the mode up when deactivated */
#define k_cameraSnapDistance GAME_VAR(double, 0x4a93d8)
#define k_0_025f GAME_VAR(float, 0x4a9428)
#define k_panelSlideEnd GAME_VAR(double, 0x4a9440)   /* the double -1649.9: a menu panel slide ends once the tunnel depth is no longer above it (setup_easePanel; menu_slide for the arena lobby and the game room); the depth is then set to -1650 */
#define k_panelSlideTarget GAME_VAR(float, 0x4a9448)   /* 250.0: the value a menu panel slide eases toward (setup_easePanel's g_setupPanelPos; menu_slide's g_lobbySlideEase / g_roomSlideEase) */
#define k_tenth GAME_VAR(float, 0x4a955c)
#define k_degToRad GAME_VAR(double, 0x4aa290)
#define k_tenthDegreeRad GAME_VAR(double, 0x4aa298)
#define k_15f GAME_VAR(float, 0x4aa498)
#define g_errorHook GAME_VAR(ErrorHook, 0x4c57cc)   /* the error hook (stamp, text) every error report ends in (error_log.c report: its eax returned): sys_messageBoxOverActive (0x46c580) in the image; nothing assigns it at run time */
#define g_unlockedLevel GAME_VAR(int, 0x4dc784)   /* the level the ARM CENTER's part lists are unlocked up to (armc_buildPartLists sets it with g_armcLevel, then reads it for the weapon and extra lists) */
#define g_loadLimit GAME_VAR(float, 0x4dcb0c)   /* the stats panel's load limit: the actor's Actor.loadMax (the chest's weightLimit x the pilot's MAX.LOAD factor x the items' loadFactor; armc_readMechStats) */
#define g_cursorBlinkTimer GAME_VAR(float, 0x4de1f0)   /* the text cursor's blink: grows by frame time x 0.035 each menu_drawTextCursor, back to 0 past 0.9; the cursor's alpha is 1 - it */
#define g_freeCamLookX GAME_VAR(float, 0x4de344)   /* X of the free (watching) camera's look-at point: moved by freeCam_keys (W / S) and freeCam_stepLeft / freeCam_stepRight; copied to g_menuCameraLook and the local slot's g_slotCams record */
#define g_freeCamLookZ GAME_VAR(float, 0x4de34c)   /* Z of the free camera's look-at point (see g_freeCamLookX; copied to g_menuCameraLookZ) */
#define g_crosshairTexture GAME_VAR(int, 0x4e0c8c)   /* texture id of the setup page's crosshair preview: looked up again (tex_getIdByName on g_crosshairName) when g_crosshairEdit changes (mouse_tab) */
#define g_perfCounterLow GAME_VAR(u32, 0x5ae9c8)   /* the last QueryPerformanceCounter reading's low word (timer_now; the high word in g_perfCounterHigh): never read */
#define g_arenaFileTimeLimit GAME_VAR(int, 0x5b1954)   /* axiswl.dat's timelimit (arena_loadSettings; arena_startFromLauncher takes its low byte into g_arenaTimeLimit) */
#define g_arenaFileSecret GAME_VAR(int, 0x5b1958)   /* axiswl.dat's "secret" (arena_loadSettings): its low byte becomes g_arenaLocked in arena_startFromLauncher (1: a password game) */
#define g_textureManager GAME_VAR(u32, 0x83a5e0)   /* the global TextureManager's vtable word (0x4a9570; TextureManager_ctor): the object's start, its banks set in app_startupLoad and g_textures pointed at it */
#define g_pilotLevelKept GAME_VAR(int, 0x9dd240)   /* the kept copy of the pilot's record (g_pilotStatsKept[0], its level): set from the Ladder record (room_copyAccountRecord), synced with g_pilotLevel (pilotRecord_syncCopies, record_send); 1 from newId_register */
#define g_gameListLoaded GAME_VAR(int, 0x9dd330)   /* 1 once the room's game list has been asked for (gameList_refresh): gameList_draw shows the rows only then; room_enterGameList clears it */
#define g_typingAccountName GAME_VAR(int, 0x9dd348)   /* 1 while the new-ID form's name field is typed (newIdForm_openField; set again to reopen it after a bad name, newIdForm_check); newIdForm_endTyping takes the line into g_accountName */
#define g_typingAccountPassword GAME_VAR(int, 0x9dd3f8)   /* 1 while the new-ID form's password is typed (see g_typingAccountName; into g_accountPassword; reopened when empty, unrepeated or bad) */
#define g_typingAccountRepeat GAME_VAR(int, 0x9dd564)   /* 1 while the new-ID form's password repeat is typed (see g_typingAccountName; into g_accountPasswordRepeat) */
#define g_roomTunnelDepth GAME_VAR(float, 0x9dd698)   /* the game room's tunnel depth (room_drawTunnel): -1400 from menuState800_enterGameRoom, slid in by room_slideMenu (menu_slide) until past k_panelSlideEnd, then -1650 */
#define g_editingRoomPassword GAME_VAR(int, 0x9dd6a8)   /* 1 while the room form's password is typed (room_editPassword, hidden); roomSettings_keys takes it into the form's password and clears it */
#define g_typingRoomJoinPassword GAME_VAR(int, 0x9dd6c8)   /* 1 while a picked game's join password is typed (room_editJoinPassword); gameList_pageFrame then compares it with the game's (message 0x27 when wrong) and clears it */
#define g_typingAccountEmail GAME_VAR(int, 0x9dd6cc)   /* 1 while the new-ID form's e-mail is typed (see g_typingAccountName; into g_accountEmail; reopened when bad, message 0x81) */
#define g_editOldProc GAME_VAR(u32, 0x9dd868)   /* the hidden EDIT control's own window procedure (SetWindowLongA GWL_WNDPROC in editField_createEdit): editField_editProc passes what it does not swallow on to it (CallWindowProcA) */
#define g_profileMechHead GAME_VAR(int, 0x9f19f8)   /* the profile's mech: its head part (the record's first word; chest .. booster follow to 0x9f1a08) */
#define g_netHostLeftMessageKind GAME_VAR(int, 0x9f9418)   /* the host-leaving game message: its kind word (2; net_resetState) then the flag word g_hostGoneMessageFlag (+4); the host sends it (net_sendMessage) from game_postMatch, freeCam_keys (cancel) and dplay_leaveSession; receivers (net_handleMessage kind 2) put +4 into g_netHostGone and reset the slots */
#define g_slotTakenFlag GAME_VAR(int, 0x9f9838)   /* 1 when the local player holds its network slot: the host from netq_reset(1) / net_claimLocalSlot, a joining machine on message 6; net_hasSlot returns it (packets are sent only then) */
#define g_outOfRank GAME_VAR(u8, 0xa052c1)   /* the rank reply's byte +1 (g_rankReply): 1 when out of the first 1000; account_takeRank then stores rank 0 */
#define g_serverPort GAME_VAR(u16, 0xa05326)   /* the port of the server being connected to: g_lobbyTcpPort (kind 100) or g_ladderPort (101) by net_resetConnection; connect_socket connects there */
#define g_pingThreadId GAME_VAR(int, 0xa0d784)   /* the ping thread's id (CreateThread in net_startPingThread); cleared by net_closeThreadHandles; not otherwise read */
#define g_pingThread GAME_VAR(void *, 0xa0d788)   /* the ping thread's handle (net_startPingThread, running net_pingThreadProc); closed by net_closeThreadHandles */
#define g_musicLength GAME_VAR(u32, 0xa0e018)   /* the music's duration, low word (GetDuration's 64-bit STREAM_TIME in music_play; high word g_musicEndHigh): music_loopIfEnded restarts the music once the play position reaches it */
#define g_primarySoundBuffer GAME_VAR(void *, 0xa0e808)   /* DirectSound's primary buffer (sound_init: 44.1 kHz 16-bit stereo, set playing looped); not used after */
#define g_errorLogging GAME_VAR(int, 0xa1efdc)   /* ERROR.TXT logging on (== 1): never written by the game (bss, 0), so the error functions never append to ERROR.TXT */
#define g_cursorX GAME_VAR(int, 0xae2f18)   /* the cursor's x (screen pixels; g_cursorPoint[0], input_getCursorPos) */
#define g_crtErrno GAME_VAR(int, 0xaef35c)   /* the C runtime's errno (set by its own code: EINVAL, ENOENT ..) */
#define g_otherModeWidth GAME_VAR(int, 0xb12a84)   /* width of the last non-desktop display mode set (app_setDisplayMode); game_wndProc sets that mode again when the game is activated after giving it up (g_displayModeLeft); with g_otherModeHeight */
#define g_arenaCorporation GAME_VAR(int, 0x4db580)   /* the lobby player's corporation: 0 by arena_defaultPlayer, from axis.cfg's g_playerCorporation (arena_loadPlayerSettings), back into it by arena_savePlayerSettings */
#define g_arenaCustomize GAME_VAR(int, 0x4db584)   /* the lobby player's customize switch (axis.cfg's set_player customize ON 1 / OFF 0): 0 by arena_defaultPlayer, from / to g_playerCustomize (arena_loadPlayerSettings / arena_savePlayerSettings); nothing else reads it */
#define g_sessionFound GAME_VAR(int, 0x4db708)   /* 1 once the session search (WM_TIMER 0x378) found the picked game's session (g_receivedSession): arena_joinAnswer / room_joinAnswer then join it; cleared when a search starts (arena_joinListed, room_joinListed) and after the answer */
#define g_arenaTunnelDepth GAME_VAR(float, 0x4dba68)   /* the arena lobby's tunnel depth (its tunnel drawing, setup_pages.c): -1400 from menuState400_enter, slid in by lobby_slidePanels (menu_slide); -1650 from lobby_enterPlayerScreen / lobby_enterArenaList / lobby_enterCreate */
#define g_playerSetupTop GAME_VAR(int, 0x4dbb6c)   /* top of the arena lobby's player setup panel (0x64 from menuState400_enter; with g_playerSetupLeft): its frame, buttons and hit rects (lobby_drawPlayerSetup, lobbyPlayer_draw, playerSetup_layout) */
#define g_unusedArenaFloat GAME_VAR(float, 0x4dbba0)   /* 0.7 stored on entering the player / list / create pages (lobby_enterPlayerScreen, lobby_enterArenaList, lobby_enterCreate); never read */
#define g_bestProgressSolo GAME_VAR(int, 0x4dc1e0)   /* the highest solo progress (g_progress) the ARM CENTER has been opened with (armc_open): a higher g_progress sets g_progressWentUp, then it is raised */
#define g_bestLevelNet GAME_VAR(int, 0x4dc4b4)   /* the highest pilot level the ARM CENTER has been opened with from a game room (armc_open: a higher g_pilotLevel sets g_progressWentUp, then it is raised); set to g_pilotLevel by login_takeAccountRecord and newId_register"; run: 1 */
#define g_savedMechChest GAME_VAR(int, 0x4dc87c)   /* the saved mech's chest part (g_savedMechHead + 1): from g_profileMechChest (mech_loadFromProfile) or g_roomMech[1] (mech_unpackFromRecord); back by mech_storeToProfile; 0 by mech_setEmpty */
#define g_savedMechArm GAME_VAR(int, 0x4dc880)   /* the saved mech's arm part (see g_savedMechChest; profile g_profileMechArm, record byte 2) */
#define g_savedMechLeg GAME_VAR(int, 0x4dc884)   /* the saved mech's leg part (see g_savedMechChest; profile g_profileMechLeg, record byte 3) */
#define g_savedMechBooster GAME_VAR(int, 0x4dc888)   /* the saved mech's booster part (see g_savedMechChest; profile g_profileMechBooster, record byte 4) */
#define g_savedMechItemSlot5 GAME_VAR(int, 0x4dcf1c)   /* the saved mech's item in slot 5 (g_savedMechSlotItems[1]; into g_itemSlot5) */
#define g_savedMechWeaponSlot0 GAME_VAR(int, 0x4dcf20)   /* the saved mech's item in weapon slot 0 (g_savedMechSlotItems[2]; into g_mechWeaponSlot0) */
#define g_savedMechWeaponSlot1 GAME_VAR(int, 0x4dcf24)   /* the saved mech's item in weapon slot 1 (g_savedMechSlotItems[3]; into g_mechWeaponSlot1) */
#define g_savedMechWeaponSlot2 GAME_VAR(int, 0x4dcf28)   /* the saved mech's item in weapon slot 2 (g_savedMechSlotItems[4]; into g_mechWeaponSlot2) */
#define g_savedMechWeaponSlot3 GAME_VAR(int, 0x4dcf2c)   /* the saved mech's item in weapon slot 3 (g_savedMechSlotItems[5]; into g_mechWeaponSlot3) */
#define g_fpsFrameCount GAME_VAR(int, 0x4dd0b0)   /* frames counted this second for the fps readout (menu_frame, only while g_showFps; cleared when a second has passed, g_fps = frames / seconds); app_startupLoad zeroes it */
#define g_debugValue GAME_VAR(int, 0x4de6e0)   /* stepped by keys 1 / 2 / 3 / 4 (+1 / +10 / -1 / -10, not below 1) in freeCam_keys; never read elsewhere */
#define g_mouseWheel GAME_VAR(int, 0x4ded7c)   /* the wheel's notches this frame (input_updateMouse: z / -120, down positive): input_isDown / input_justPressed's WHEEL-UP (< 0) / WHEEL-DOWN (> 0), and the setup page's key binding (setup_controlTabClicks) */
#define g_musicVolume GAME_VAR(int, 0x4e0c94)   /* axis.cfg's music volume (cfg_readSound, default 100; the sound tab's BGM switch 0 / 100): below 50 music_play plays nothing; round_start passes it to music_setVolumeSetting */
#define g_stereoReverse GAME_VAR(int, 0x4e0c9c)   /* axis.cfg's "stereoreverse": sound_play3D pans the other way */
#define g_roomRecMap GAME_VAR(signed char, 0x5b1b50)   /* the room settings record's map (g_roomRecName + 0x20, the registry's "Map", 0 .. g_mapCount-1: map_step skips 22 .. 24, so 25 and up occur too): into g_roomMap (22 .. 24 become 0, room_loadSettingsRecord); written by reg_writeLadderSettings' copy and room_keepSettings */
#define g_roomRecMaxPlayers GAME_VAR(signed char, 0x5b1b51)   /* the room record's player count (the registry's "PlayerNum", 0 .. 16, else 8): into g_roomMaxPlayers; 8 by room_setLadderDefaults and roomSettings_page when out of range */
#define g_roomRecFragLimit GAME_VAR(u8, 0x5b1b54)   /* the room record's frag limit (the registry's "FlagLimit", kept 5 .. 30): into g_roomFragLimit; a joined game's (room_joinAnswer); roomSettings_page makes over 50 into 30 */
#define g_roomRecTimeLimit GAME_VAR(u8, 0x5b1b55)   /* the room record's time limit (the registry's "TimeLimit", kept 5 .. 30): into g_roomTimeLimit; a joined game's (room_joinAnswer); roomSettings_page makes over 60 into 30 */
#define g_netRole GAME_VAR(int, 0x67ef04)   /* the network role for the next match: 1 host (lobby_hostArenaIpx / TcpIp, arena_takeHostAnswer, hostError_clicks, room_hostingStep), 2 joining (take_session, room_joinAnswer); match_enter starts a client unless 1 */
#define g_listAnswered GAME_VAR(int, 0x680bb8)   /* the games heard from so far, the left number of the lists' "n / total" counter (answered_count): +1 for each newly answered server (merge, pinged or not), the DirectPlay session count (arenaList_rebuild), 0 when a list is opened or refreshed (lobby_openConnection, arenaGames_mouse / keys, gameList_mouse / keys) */
#define g_cfgLinearFilter GAME_VAR(u32, 0x83a9cc)   /* axis.cfg's "set_graphic linearfiltering" (g_cfgSwitches[0]; 1 by cfg_init's defaults): handed to every texture bank's tex_initBy in app_startupLoad */
#define g_cfgMipmaps GAME_VAR(u32, 0x83a9d0)   /* axis.cfg's "set_graphic mipmapping" (g_cfgSwitches[1]; 1 by cfg_init's defaults): handed to every texture bank's tex_initBy in app_startupLoad */
#define g_timerRepeatCount GAME_VAR(int, 0x9dbf00)   /* timer_now's count of calls in a row returning the same time as g_lastTime; past 100000 the time is moved on by 1 and it restarts at 0 */
#define g_accountRank GAME_VAR(int, 0x9dd248)   /* the account page's rank (account_takeRank: the rank reply's, 0 when out of the first 1000); 0 shows MSG(374, "OUT OF RANK(1000)") */
#define g_rankingPrevValue GAME_VAR(float, 0x9dd384)   /* the ranking: the previous page's last sort value (ranking_fillPage stores it, the next page's first row ties with it); 10,000,000 from ranking_enter / ranking_cycleSort */
#define g_rankingWaiting GAME_VAR(int, 0x9dd6b8)   /* 1 while the ranking page waits for a requested list (set when the request is sent; cleared when g_rankingListIn arrives or on cancel: button 3, S); blocks other buttons and C / Esc; ranking_enter clears it */
#define g_unusedRoomFloat GAME_VAR(float, 0x9dd6bc)   /* 0.7 stored on entering each game room page (menuState800_enterGameRoom, room_enterAccountPage, room_enterGameList, room_enterCreatePage, ranking_enter); never read */
#define g_launchMessage GAME_VAR(const char *, 0x9dd8c8)   /* the launch failure message, by system language (game_WinMain): Korean or "Axisplay.exe has been expired"; shown when app_readLauncherCheck fails */
#define g_replaySelectOpen GAME_VAR(int, 0x9eeab4)   /* the main menu's replay selection dialog is open (F1: mainmenu_processKeys -> replayList_open; closed by replaySelect_ok / its cancel and back keys / its button 7; menuState300_enter clears it): the main menu's keys and clicks go to the dialog, menuState300_frame draws it, mainmenu_drawMenu lights no panel */
#define g_profileMechItem0 GAME_VAR(int, 0x9f1a14)   /* the profile's mech item for slot 4 (into / from g_savedMechItemSlot4: mech_loadFromProfile / mech_storeToProfile); -1 for a new profile */
#define g_profileMechItem1 GAME_VAR(int, 0x9f1a18)   /* the profile's item for slot 5 (g_savedMechItemSlot5; 0x11 for a new profile) */
#define g_profileMechItem2 GAME_VAR(int, 0x9f1a1c)   /* the profile's weapon slot 0 item (g_savedMechWeaponSlot0; 0 for a new profile) */
#define g_profileMechItem3 GAME_VAR(int, 0x9f1a20)   /* the profile's weapon slot 1 item (g_savedMechWeaponSlot1; 2 for a new profile) */
#define g_profileMechItem4 GAME_VAR(int, 0x9f1a24)   /* the profile's weapon slot 2 item (g_savedMechWeaponSlot2; 8 for a new profile) */
#define g_profileMechItem5 GAME_VAR(int, 0x9f1a28)   /* the profile's weapon slot 3 item (g_savedMechWeaponSlot3; -1 for a new profile) */
#define g_arenaPacket GAME_VAR(ArenaRecord *, 0xa0b310)   /* buffer (0x5b bytes, ArenaRecord) of the hosted arena's record: filled and sent as request 10 by lobby_announceArena; copied into the info (arena_info) and leave (net_disconnect) packets */
#define g_accountPacket GAME_VAR(AccountPacket *, 0xa0b320)   /* buffer (0x10b bytes, AccountPacket) of the account record: the new ID (newId_register, request 15) or the login (login_send, request 14); net_send puts this machine's address in it */
#define g_roomPacket GAME_VAR(RoomRecord *, 0xa0b328)   /* buffer (0x79 bytes, RoomRecord) of the room's announced game: filled by room_announceGame (request 0x12); copied into the info (room_info) and leave packets (net_disconnect, game_postMatch) */
#define g_dplayLobby GAME_VAR(void *, 0xa0b398)   /* the IDirectPlayLobby3A object (CoCreateInstance in dplay_lobbyConnect): connection settings, ConnectEx and compound addresses; released by dplay_release */
#define g_roomMaxPlayers GAME_VAR(u8, 0x4df9e9)   /* the room form's player count (g_roomSettingsName + 0x21): +2 (4 .. 16, then 2) by room_settingsClicks; 8 by room_setLadderDefaults; from g_roomRecMaxPlayers */
#define g_roomRotation GAME_VAR(u8, 0x4df9ea)   /* the room form's map rotation (GameSettings.rotation, +0x22; the registry's "Customize"): while set room_stepMap does not change the map; read by room_drawMapPreview; 0 on room_enterCreatePage */
#define g_roomRecRotation GAME_VAR(u8, 0x5b1b52)   /* the room record's map rotation (g_roomRecName + 0x22; see g_roomRotation): into g_roomRotation (room_loadSettingsRecord, room_copyAccountRecord); 0 by room_setLadderDefaults */
#define g_profileMechChest GAME_VAR(int, 0x9f19fc)   /* the profile's mech chest part (into / from g_savedMechChest: mech_loadFromProfile / mech_storeToProfile; 0 for a new profile) */
#define g_profileMechArm GAME_VAR(int, 0x9f1a00)   /* the profile's mech arm part (see g_profileMechChest) */
#define g_profileMechLeg GAME_VAR(int, 0x9f1a04)   /* the profile's mech leg part (see g_profileMechChest) */
#define g_profileMechBooster GAME_VAR(int, 0x9f1a08)   /* the profile's mech booster part (see g_profileMechChest; the last word new profiles zero from g_profileMechHead) */
#define g_mainWindow GAME_VAR(void *, 0x4ded18)   /* the main window (CreateWindowExA "AXIS" popup, app_init): owner of DirectInput / DirectSound / net_asyncSelect, the timers 0x29a / 0x115c / 0x309 / 0x378 and the edit field; PostMessage WM_CLOSE quits (app_closeWindow) etc. */
#define g_hInstance GAME_VAR(void *, 0x67ef18)   /* the program's instance (set in app_init); only read as the hidden EDIT window's instance (editField_createEdit) */
#define g_textEndX GAME_VAR(int, 0x4d23c8)   /* x where the last ASCII text pass stopped (text_ascii8Pass / 16 / 32; not the 5-pixel text_ascii5Pass nor the Korean passes); the briefing's typing cursor is drawn there (briefing_typeOut) */
#define g_textEndY GAME_VAR(int, 0x4d23cc)   /* y where the last ASCII text pass stopped (see g_textEndX) */
#define g_mapListOpen GAME_VAR(int, 0x4db508)   /* the map rotation list is open over the arena create page / room settings: 1 by mapList_startEdit (lobby button 15, room button 13), 0 by mapList_ok / mapList_mouse / mapList_keys / mapList_init; routes keys and clicks to mapList_keys / mapList_mouse, draws mapList_draw */
#define g_typingArenaAddress GAME_VAR(int, 0x4db714)   /* a game's IP address is being typed in the arena list (arena_editAddress: P key or its button; INPUT IP-ADDRESS box); when the field closes arena_gamesPageFrame copies it to g_typedArenaAddress and joins it (arena_joinListed(99999)) if not empty, then clears it */
#define g_joinConnecting GAME_VAR(int, 0x4db8b4)   /* a join's connection is being waited for (arena_joinListed / room_joinListed set it with the 2 s timer 0x378): the CONNECTING TO THE GAME SERVER / PLEASE WAIT box with CANCEL (arena_drawGameList, gameList_draw); its CANCEL/keys stop the join (arena_joinAnswer, room_joinAnswer, gameList_stopJoin, arenaJoinBox_clicks clear it) */
#define g_arenaJoinNeedsPassword GAME_VAR(int, 0x4db8bc)   /* the arena game picked is locked and its password is being asked (arena_askJoinPassword sets 1, else 0; TYPE GAME PASSWORD box); arena_gamesPageFrame checks the typed one against the session's (message 0x27 when wrong) and clears it */
#define g_armcPreview GAME_VAR(int, 0x4dbc68)   /* the ARM CENTER's 3D mech preview is on: 1 once the session is made (armc_makeSession), 0 on armc_open / armc_snapCameraToPoint0; gates the page previews, the weight line and the part names; while 0 and no session the LOADING MECHANIC DATA box shows */
#define g_armcSessionMade GAME_VAR(int, 0x4dc54c)   /* the ARM CENTER's scene session has been made (armc_makeSession sets 1; armc_open clears it); menuState700_armCenter makes it once g_armcSessionDue is set and shows the loading box until then */
#define g_armcState GAME_VAR(int, 0x4dc790)   /* the ARM CENTER's camera / state: 1 travelling in (armc_open), 2 arrived or home (armc_cameraStep; page drawn and input taken), 0 going home (armc_exit, armc_rightClickLeave); input and drawing skip 0 / 1 */
#define g_coloursChanged GAME_VAR(int, 0x4dca98)   /* a colour slider was set where the pointer clicked (armc_colours.c: the hue / saturation / value setters set 1, on a click only); armc_updatePartsPreview then applies the colour slot (armc_applyColourSlot) and clears it */
#define g_armcSlotChanged GAME_VAR(int, 0x4dcc64)   /* the weapons page's chosen slot changed (armc_takeCursorItem sets 1); armc_drawWeaponsScreen then retakes that slot's snapshot (armc_loadSnapshotTexture, which clears it); also cleared by armc_openWeaponsPage */
#define g_loadStep GAME_VAR(int, 0x4dda34)   /* start-up progress step: 0 at menuState100_intro, +1 per step (menuState100_intro, frontEnd_startUp, the menu texture loads in loading.c); frontEnd_drawProgress draws a bar of 16 pixels a step */
#define g_replayZoomTime GAME_VAR(float, 0x4dda48)   /* the main menu's zoom into a chosen replay (while g_replayShowOn on screen 300): g_frameTime added each frame (menu_frame); at 100 the replay starts (screen 9999, g_replayRunning); cleared by menuState100_intro, menuState210_enter, game_returnTo*; menuState210_frame draws nothing while it is above 0 */
#define g_bindPage GAME_VAR(int, 0x4ddce8)   /* setup controls tab's page 0 .. 3 (MOVE / SHOOT / MISC / MOUSE): keys M S I U or a click on tabs 0 .. 3 (setup_controlTabKeys / Clicks); 0 on setup_selectControlTab; picks rows for setup_bindKey and setup_drawControlsPage */
#define g_setupCameraMode GAME_VAR(int, 0x4ddcec)   /* the setup screen's camera (setup_camera): 1 going to the open tab's menu point (tab_opened), 0 going home (the page closed: OK / back / cancel), 2 arrived (page shown, or home); the tunnel's alpha eases to 0.3 in 1 and 0.5 in 0 (setup_drawTunnel) */
#define g_bindWaiting GAME_VAR(int, 0x4dddc8)   /* setup controls tab waits for a new key for the selected row (1 on Enter / click; drawn magenta): the next key, mouse button or wheel goes to setup_bindKey, Esc cancels (setup_controlTabKeys / Clicks); 0 on setup_selectControlTab */
#define g_setupEffectVolume GAME_VAR(int, 0x4dde98)   /* the sound tab's EFFECT SOUND volume being edited (0 .. 100; g_soundEdited[0]); OK makes it g_soundVolume (axis.cfg set_sound effectvolume) */
#define g_whiteFade GAME_VAR(float, 0x4deb74)   /* the white fade over the screen while the menus are left for a match (+0.015 x g_frameTime a frame, drawn alpha capped at 1): room_drawWhiteFade (game room) and menu_drawWhiteFade (arena lobby, main menu: menuState300_frame); cleared by arena_camera, room_camera, skirmish_camera */
#define g_tunnelPulseStep GAME_VAR(float, 0x4df010)   /* direction (+1 / -1 a frame) of g_tunnelPulse bouncing between 0 and 100 (tunnel_stepPulseScroll in setup_pages.c); 1 at menuState100_intro and menuState600_enterSetup */
#define g_menuScaleY GAME_VAR(float, 0x4df014)   /* the menus' 480-line coordinates to screen pixels: g_screenH / 480 (app_startupLoad); used by menu_vertex */
#define g_freeCamZoom GAME_VAR(int, 0x4e0464)   /* the free camera's zoom (Z in freeCam_keys toggles 1 / 2): 1 narrows g_viewAngle by 5 each menu frame down to 5, 2 widens it by 5 up to 45 (menu_frame, after SwapBuffers); other values leave it */
#define g_projMode GAME_VAR(int, 0x5ae9bc)   /* projection set last by gfx_setProjection2D3D (skipped when the same): 1 the 3D perspective (g_viewAngle, depth 1 .. 20000), other the menus' 2D ortho; -1 forces a reset (game_wndProc WM_CREATE / WM_SIZE, gfx_setMatchProjection); 1 after gfx_initGLState */
#define g_mapCount GAME_VAR(int, 0x67ef00)   /* mapinfo.dat's map count (data_loadMapInfo); g_mapNames / g_mapAbouts hold that many */
#define g_leavingForMatch GAME_VAR(int, 0x67ef14)   /* 1 while the menus are being left for a match: set when an arena / room game is hosted or joined (lobby_hostArenaTcpIp, lobby_hostArenaIpx, arena_takeHostAnswer, arena_joinAnswer, room_hostingStep, room_clicks) or a skirmish / mission starts (menu_misc.c:481); the menu tunnel then runs 2200-step rings, the white fade (g_whiteFade) runs, the top pages ignore keys / clicks and menu_slide moves to screen 9999. Cleared at start-up (app_startupLoad), on a host failure (lobby_hostArenaIpx), and by leave_game on the way back */
#define g_menuCameraLookZ GAME_VAR(float, 0x680380)   /* the menu camera's look-at point: z (gluLookAt centre z; g_menuCameraLook / g_menuCameraLookY the x / y) */
#define g_menuScaleX GAME_VAR(float, 0x680bac)   /* the menus' 640-column coordinates to screen pixels: g_screenW / 640 (app_startupLoad); used by menu_vertex and the menus' 4:3 box */
#define g_arenaUpdateNotice GAME_VAR(int, 0x907b2c)   /* the THIS PROGRAM HAS BEEN UPDATED notice is up in the arena lobby (server answer 3: arena_takeHostAnswer, gameList_pageFrame, arena_gamesPageFrame, room_hostingStep); takes keys / clicks (createUpdateNotice_keys / _clicks ...), which clear it */
#define g_tunnelRings GAME_VAR(int, 0x9dae10)   /* the menu tunnel's ring count: +1 tunnel_addRing, -1 menuTunnel_advance, 0 tunnel_restart; back key / right click go back a screen only while > 0 (lobbyTop_keys, mainmenu_processKeys, setup_topPageKeys, room_pageClicks ...) */
#define g_rankingSort GAME_VAR(int, 0x9dd1d0)   /* the ranking page's sort column: 0 power, 1 kills, 2 exp, 3 rate (ranking_fillPage, ranking_drawTable); cycled 0 .. 2 by ranking_cycleSort, set by a column click (ranking_clicks), the old one kept in g_rankingPrevSort and restored on cancel */
#define g_roomRefreshing GAME_VAR(int, 0x9dd3fc)   /* the game room's game list is refreshing after a search answer (gameList_pageFrame sets 1): every g_listRefreshPeriod room_mergeReceivedSessions; cleared on g_netListDone, a stop or gameList_refresh; blinks SEARCHING and blocks joins (sound 6) */
#define g_roomJoinStarted GAME_VAR(int, 0x9dd56c)   /* a join of the picked game was asked in the game room's list (gameList_mouse / keys set it after room_askJoinPassword); gameList_pageFrame then joins (room_joinListed) or checks the typed password; cleared by room_joinListed, a wrong password and room_enterGameList */
#define g_roomJoinNeedsPassword GAME_VAR(int, 0x9dd6b4)   /* the room game picked is locked and its password is being asked (room_askJoinPassword sets 1, else 0); gameList_pageFrame checks the typed one against the session's (message 0x27 when wrong) and clears it; blocks the list's mouse / keys */
#define g_newIdConfirmChoice GAME_VAR(int, 0x9dd6c4)   /* the new ID confirmation's choice: 1 OK (registers it, newId_register), 2 cancel (state back), 0 none (newIdConfirm_keys O / C, newIdConfirm_clicks; room_openNewIdConfirm clears it; newIdConfirm_update acts and clears) */
#define g_roomState GAME_VAR(int, 0x9dd834)   /* the game room's (800) page: 0 account, 1 game list, 2 game settings, 4 ranking, 66 login, 77 new-ID form, 88 new-ID confirmation, 99 the room's menu (menuState800_gameRoom, room_keysByState, room_clicksByState); set by the room's dialogs / page openers */
#define g_roomUpdateNotice GAME_VAR(int, 0x9dd850)   /* the THIS PROGRAM HAS BEEN UPDATED notice over the room's login / new-ID confirmation (roomLogin_update, newIdConfirm_update set 1); takes keys / clicks there (roomUpdateNotice_keys, updateNotice_clicks), which clear it */
#define g_replaySelectFirst GAME_VAR(int, 0x9dd92c)   /* the first replay shown in the replay selection dialog's 10 rows (replaySelect_drawNames); 0 on replayList_open; scrolled by one within g_replayFileCount (menu_states.c); a row click toggles g_replaySelectFirst + row */
#define g_missionsState GAME_VAR(int, 0x9ef1f0)   /* the mission screen's (900) camera state (missions_camera): 1 travelling in (menuState900_enterMissions), 2 arrived (page drawn, keys taken), 0 going home (missions_leave); the tunnel is drawn while not 2 */
#define g_missionsPage GAME_VAR(int, 0x9ef1f8)   /* the mission screen's (900) page: 10 the list (missions_frameList), 20 the mission settings (mission_loadBriefing); -1 once its camera is home again (menu_camera2's third flag, as g_skirmishLeft for the skirmish screen) */
#define g_briefingEnd GAME_VAR(int, 0x9ef200)   /* end offset of the chosen mission's briefing text: its block size (mission_loadBriefing); briefing_typeOut sets g_briefingDone once the typed text reaches it */
#define g_briefingDone GAME_VAR(int, 0x9f105c)   /* the briefing's text is fully typed out (briefing_typeOut sets 1 at g_briefingEnd); 0 on mission_loadBriefing / briefing_prevPage; while 0 (and the page not full) the typing cursor is drawn */
#define g_briefingPage GAME_VAR(int, 0x9f1060)   /* the briefing's page shown (index into g_briefingPageStarts): 0 on mission_loadBriefing, +1 briefing_nextPage (N, once the page is full), -1 briefing_prevPage (P); enables the page-back button (missionBriefing_draw) */
#define g_selectedCharacter GAME_VAR(int, 0x9f1818)   /* the local pilot's character (index into g_characterProfiles): the profile's (profile_saveProgress etc. in files.c); its skills feed the ARM CENTER stats, mech_setAll and the match's player record (match_start.c) */
#define g_profileFrameStep GAME_VAR(float, 0x9f8c48)   /* direction (+1 / -1 a frame) of g_profileFrameAlpha bouncing between 2 and 38 on the pilot screen's frame (profile_drawPilotSelect); -1 with alpha 40 on a restart (load_stat_bars, profile_resetStatBars) */
#define g_profileCount GAME_VAR(int, 0x9f9008)   /* number of pilot profiles in axisuser.dat (read by profile_readHeader, written with them; +1 profile_create, -1 profile_deleteChosen); bounds the profile list (profileList_drawNames, profileList_keys / _mouse, profile_nameExists) */
#define g_dplay GAME_VAR(void *, 0xa0b404)   /* the IDirectPlay4A object (dplay_createObject in dplay_create / dplay_initConnection, or the lobby's in dplay_joinSession): Receive / Send (dplay_receive / dplay_send), session enum, host, join; released and NULL in dplay_release */
#define g_connectionKind GAME_VAR(int, 0xa0b418)   /* DirectPlay connection kind (slot) in use: 0 TCP/IP (host resolved first), 1 .. 3 the others (1 the LAN / IPX search), 4 none (dplay_leaveSession); set by dplay_openConnection; picks the slot in dplay_listSessions / dplay_host / dplay_join */
#define g_directSound GAME_VAR(void *, 0xa0e804)   /* the IDirectSound object (DirectSoundCreate in sound_init; NULL when it fails); sound_loadWav makes buffers on it; released by sound_releaseDirectSound */
#define g_soundOn GAME_VAR(int, 0xa0e80c)   /* sound works: 1 when sound_init succeeds (app_startupLoad, sound_init), else 0; checked by sound_playMenu, sound_setVolume, sound_playFile, sound_play3D, sound_freeAll etc. */
#define g_ptxBitPos GAME_VAR(int, 0xa21704)   /* bit position in g_bitStream of the PTX image decoder (ptx_readBits, ptx_readDcDiff, ptx_readAcSymbol); 0 on ptx_startBitReader */
#define g_ptxLastDc GAME_VAR(int, 0xaa268c)   /* the PTX decoder's running DC value: each block's DC difference added (ptx_readBlock: block[0]); 0 on ptx_startBitReader */
#define g_roomSearching GAME_VAR(int, 0x9dd6a0)   /* the game room's list is searching (1 on gameList_refresh, search key R / button in gameList_mouse / _keys); on the answer (g_roomSearchAnswerIn) gameList_pageFrame handles the result, clears it and starts g_roomRefreshing; blocks joins */
#define k_0_1f GAME_VAR(float, 0x4a93ec)
#define k_oneOver180 GAME_VAR(double, 0x4a9540)
#define k_pi GAME_VAR(double, 0x4a9548)
#define g_receivedSession GAME_VAR(const u8 *, 0x4dbbf8)   /* session 0 of the DirectPlay list (net_getSession(0)) found by the 0x378 join timer (game_wndProc, up to 30 ticks); its guid copied into the joined record by arena_joinAnswer / room_joinAnswer */
#define g_setupMusicVolume GAME_VAR(int, 0x4dde9c)   /* the sound tab's BGM switch being edited (g_soundEdited[1]): 0 off / 100 on (setup_soundTabClicks button 5 flips it at 50); OK makes it g_musicVolume (axis.cfg set_sound musicvolume) */
#define g_roomInfoPacket GAME_VAR(u8 *, 0xa0b32c)   /* 0x79-byte room record buffer (net_resetConnection; freed net_freeBuffers): the host's room info with the player count (room_info in net_handleSystemMessage, game server 201); sent as message 20 (net_send) */
#define g_roomLeavePacket GAME_VAR(u8 *, 0xa0b330)   /* 0x79-byte room record buffer (net_resetConnection): the room's leave message 0x16 to the game server (net_send sets byte 0 to 1; net_disconnect fills it from g_roomPacket; game_postMatch copies host name / address) */
#define g_arenaListClickArmed GAME_VAR(int, 0x4db71c)   /* the arena game list's double-click window: set by a click on a row (arenaGames_mouse); a second click on the same row while set joins (lobby_join); cleared after 20 of g_frameTime (arena_gamesPageFrame, g_arenaListClickTimer) */
#define g_serverSearching GAME_VAR(int, 0x4db854)   /* the arena list is searching through the lobby server (T key / its button: lobby_openConnection, arenaGames_keys / arenaGames_mouse); cleared by a LAN search, which first closes that connection (net_disconnect) */
#define g_lanSearchStarted GAME_VAR(int, 0x4dba84)   /* a local-network search has opened a DirectPlay session (arenaGames_mouse / keys button 0: dplay_openConnection(1, NULL), g_lanSearch); left (dplay_leaveSession) before another search or a join (arena_joinListed) */
#define g_connectionAwaited GAME_VAR(int, 0x4dba88)   /* a server answer (g_hostAnswer 2) is awaited: set by lobby_openConnection, lobby_announceArena, room_announceGame, gameList_refresh; lobbyCreate_frame / roomSettings_page poll the outcome while set; cleared by arena_takeHostAnswer / room_hostingStep */
#define g_lobbyJoinStarted GAME_VAR(int, 0x4dbbec)   /* a join of the picked arena game was asked (J / click / double-click: arena_gamesPageFrame, arenaGames_keys); arena_gamesPageFrame then joins (arena_joinListed) or checks the typed password; cleared on a wrong password and by arena_joinSession / arena_joinListed */
#define g_hostingState GAME_VAR(int, 0x4dbbf4)   /* the hosting state (arena or game room): 0 none (lobby_enterCreate, room_enterCreatePage, leave_game), 1 hosted on IPX / without the lobby (lobby_hostArenaIpx, hostError_keys / _clicks), 2 on TCP/IP or announced to a server; at 2 timer 0x29a sends keep-alive 0x17 */
#define g_hostGameSetUp GAME_VAR(int, 0x4ded54)   /* the hosted game's settings are taken (arena_takeHostAnswer, lobby_announceArena, room_hostingStep etc. set 1; cleared when hosting fails, on create-page entry and game_returnToGameRoom); while set the create page's hosting keys / clicks do nothing */
#define g_menuCameraLookY GAME_VAR(float, 0x68037c)   /* the menu camera's look-at point: y (gluLookAt centre y) */
#define g_gameListClickTimer GAME_VAR(float, 0x9dcd40)   /* the room game list's double-click clock: g_frameTime added while g_gameListClickArmed (gameList_pageFrame), the window closed above 20; 0 on each row click (gameList_mouse) */
#define g_gameListClickArmed GAME_VAR(int, 0x9dd34c)   /* the room game list's double-click window: set by a click on a row (gameList_mouse); a second click on the same row while set joins (room_askJoinPassword); cleared after 20 of g_frameTime (gameList_pageFrame) */
#define g_dikMouse1 GAME_VAR(int, 0x4de73c)   /* 0xfa (input_initDikCodes): the left mouse button's key code: default FIRE binding (g_controls + 0x50); bound by a click while a binding waits (setup_controlTabClicks) */
#define g_dikF11 GAME_VAR(int, 0x4df8d0)   /* 0x57 (DIK_F11, input_initDikCodes): cycles HIDDEN MESSAGE BOX MODE / SCREENSHOT MODE / NORMAL MODE in a match (match_combatInput) and a replay (replay_frame) */
#define g_dikNone GAME_VAR(int, 0x4df8e4)   /* 0 (input_initDikCodes): the unbound key value: empty slots of the default bindings (input_setDefaultBindings, setup_defaultBindings), setup_bindKey clears slots to it, setup's key tab shows nothing for it */
#define g_dikPageUp GAME_VAR(int, 0x4df90c)   /* 0xc9 (DIK_PRIOR, input_initDikCodes): with left Ctrl and right Alt held sets g_progress to 16 on the skirmish round screen (skirmish_roundKeys) */
#define g_dikRAlt GAME_VAR(int, 0x4df9fc)   /* 0xb8 (DIK_RMENU, input_initDikCodes): held with left Ctrl for the Page Up progress key (skirmish_roundKeys) */
#define g_dik1 GAME_VAR(int, 0x4e0468)   /* 0x02 (DIK_1, input_initDikCodes): default HAND WEAPON 1; follow key 1 in a match (match_playFrame) and all ten in a replay (replay_frame); item slot 0 (armc_weaponsPageKeys); g_debugValue +1 (freeCam_keys) */
#define g_dik2 GAME_VAR(int, 0x4e046c)   /* 0x03 (DIK_2): default HAND WEAPON 2; follow key 2 (match_playFrame); item slot 1 (armc_weaponsPageKeys); g_debugValue +10 (freeCam_keys) */
#define g_dik3 GAME_VAR(int, 0x4e0470)   /* 0x04 (DIK_3): default HAND WEAPON 3; follow key 3 (match_playFrame); item slot 2 (armc_weaponsPageKeys); g_debugValue -1 (freeCam_keys) */
#define g_dik4 GAME_VAR(int, 0x4e0874)   /* 0x05 (DIK_4): default HAND WEAPON 4; follow key 4 (match_playFrame); item slot 3 (armc_weaponsPageKeys); g_debugValue -10 (freeCam_keys) */
#define g_dikA GAME_VAR(int, 0x4e0cd4)   /* 0x1e (DIK_A): default LEFT STEP (g_keyStepLeft); menu key A: main menu choice 4, room_keys opens the ARM CENTER, OK in setup tabs, ARM CENTER pages, mapList_keys, replaySelect_keys (all in), missions_listKeys */
#define g_dikC GAME_VAR(int, 0x4e0cdc)   /* 0x2e (DIK_C; game.h alias g_keyBack): default TEAM CHAT; menu close / cancel key C (notices, hostError_keys, newIdConfirm_keys, ranking_keys, account_keys ...), opens the create page (lobbyTop_keys, room_keys), setup's control tab */
#define g_dikD GAME_VAR(int, 0x4e0ce0)   /* 0x20 (DIK_D): default RIGHT STEP (g_keyStepRight); menu key D: mapList_keys, lobbyPlayer_keys, replaySelect_keys (all out), profileList_keys (delete), setup_controlTabKeys (defaults) */
#define g_dikG GAME_VAR(int, 0x4e14ec)   /* 0x22 (DIK_G): setup_topPageKeys opens the graphics tab; the ARM CENTER parts page's fourth part key (slot_keys H E S G B, armc_keys.c) */
#define g_dikI GAME_VAR(int, 0x4e14f4)   /* 0x17 (DIK_I): menu key I: hosts IPX (arenaCreate_keys), LAN search (arenaGames_keys), log in (profileList_keys), send (roomLogin_keys), the MISC page (setup_controlTabKeys) */
#define g_dikJ GAME_VAR(int, 0x4e14f8)   /* 0x24 (DIK_J): menu key J: joins the selected game (gameList_keys, arenaGames_keys), opens the game list (lobbyTop_keys, room_keys) */
#define g_dikL GAME_VAR(int, 0x4e1504)   /* 0x26 (DIK_L): to the ARM CENTER colour page (armc_partsPageKeys, armc_weaponsPageKeys); main menu choice 2 (mainmenu_processKeys) */
#define g_dikM GAME_VAR(int, 0x4e1508)   /* 0x32 (DIK_M): main menu choice 1; the MOVE page (setup_controlTabKeys); with left Ctrl + left Alt toggles g_armcHideInterface (armc_processInput) */
#define g_dikN GAME_VAR(int, 0x4e150c)   /* 0x31 (DIK_N): menu key N: briefing next page (missions_briefingKeys), new profile (profileList_keys), new ID (roomLogin_keys) */
#define g_dikO GAME_VAR(int, 0x4e1510)   /* 0x18 (DIK_O; game.h alias g_keyOk): menu OK key: notices / dialogs (createUpdateNotice_keys, hostError_keys, mapList_keys, lobbyPlayer_keys, newIdConfirm_keys, account_keys), start (roomSettings_keys), pages' confirm */
#define g_dikP GAME_VAR(int, 0x4e1514)   /* 0x19 (DIK_P): menu key P: ARM CENTER parts page, player screen (lobbyTop_keys), type an IP (arenaGames_keys), account page (room_keys), briefing page back (missions_briefingKeys) */
#define g_dikR GAME_VAR(int, 0x4e151c)   /* 0x13 (DIK_R): default ALTITUDE UP; menu key R: ARM CENTER spin toggle, room list search (gameList_keys), replay random order (replaySelect_keys), ranking (room_keys) */
#define g_dikS GAME_VAR(int, 0x4e1524)   /* 0x1f (DIK_S): default BACKWARD (g_keyBackward); menu key S: main menu choice 3, setup sound tab, SHOOT page, stop search (gameList_keys, arenaGames_keys), ranking_keys, ARM CENTER third part key */
#define g_dikT GAME_VAR(int, 0x4e1528)   /* 0x14 (DIK_T): menu key T: announce or host TCP/IP (arenaCreate_keys), search through the lobby server (arenaGames_keys) */
#define g_dikW GAME_VAR(int, 0x4e1538)   /* 0x11 (DIK_W): default FORWARD (g_keyForward); to the ARM CENTER weapons page (armc_partsPageKeys, armc_colourPageKeys) */
#define g_dikX GAME_VAR(int, 0x4e153c)   /* 0x2d (DIK_X): default USE ITEM; menu leave key X (lobbyTop_keys, room_keys, setup_topPageKeys); main menu choice 5 */
#define g_dikSpace GAME_VAR(int, 0x5b1da8)   /* 0x39 (DIK_SPACE): default BOOSTER; selects in the in-match Esc menu (match_combatInput); slow motion while held in a replay (replay_frame); closes a message box / the title (messageBox_keyClose, title_keyDismiss) */
#define g_dikLShift GAME_VAR(int, 0x67ef24)   /* 0x2a (DIK_LSHIFT; game.h alias g_keyLeftShift): default ZOOM; follow keys +10 (match_playFrame, replay_frame); a modifier: game type back (arena_createClick, room_settingsClicks), field back (newIdForm_keys) */
#define g_dikZ_2 GAME_VAR(int, 0x680388)   /* 0x2c (DIK_Z, a second copy of g_dikZ): toggles g_freeCamZoom 1 / 2 (freeCam_keys) */
#define g_dikTab GAME_VAR(int, 0x680390)   /* 0x0f (DIK_TAB; game.h alias g_keyToggle): default SCORE; next field (newIdForm_keys), a two-button dialog's highlight (roomLogin_keys) */
#define g_dikEscape GAME_VAR(int, 0x6803a0)   /* 0x01 (DIK_ESCAPE; game.h alias g_keyCancel): cancel in the in-match Esc menu (match_combatInput); closes a message box / the title; leaves the profile pages (pilotSelect_keys, the profile key handlers) */
#define g_dikLCtrl GAME_VAR(int, 0x6803a8)   /* 0x1d (DIK_LCONTROL; game.h alias g_keyLeftCtrl): held for Ctrl+Alt+M (armc_processInput) and Ctrl+RAlt+PageUp (skirmish_roundKeys); a modifier for game type back (arena_createClick, room_settingsClicks, mapList_stepGameType) */
#define g_dikDown GAME_VAR(int, 0x76d330)   /* 0xd0 (DIK_DOWN; game.h alias g_keyDown): next in the in-match Esc menu (match_combatInput); the menus' down key (lists, ARM CENTER, setup) */
#define g_dikDelete GAME_VAR(int, 0x76d414)   /* 0xd3 (DIK_DELETE): deletes the chosen profile (profileList_keys, as D) */
#define g_dikMouse2 GAME_VAR(int, 0x76d424)   /* 0xfb (input_initDikCodes): the right mouse button's key code: default ALTITUDE binding (g_controls + 0x30); bound by a right click while a binding waits (setup_controlTabClicks) */
#define g_dikEscape_2 GAME_VAR(int, 0x76d48c)   /* 0x01 (DIK_ESCAPE, second copy; game.h alias g_keyCancel2): default GAME MENU (g_keyGameMenu); the menus' back / leave key (room_keys, mainmenu_processKeys with tunnel rings, close keys of dialogs ...) */
#define g_dikWheelDown GAME_VAR(int, 0x76d490)   /* 0xfe: the wheel turned down / towards the user (key name "WHEEL-DOWN"; input_isDown: g_mouseWheel > 0) */
#define g_dikWheelUp GAME_VAR(int, 0x9da490)   /* 0xfd: the wheel turned up / away from the user (key name "WHEEL-UP"; input_isDown: g_mouseWheel < 0) */
#define g_dikLAlt GAME_VAR(int, 0x9da4a0)   /* 0x38 (DIK_LMENU): held with left Ctrl for M toggling g_armcHideInterface (armc_processInput) */
#define g_dikRCtrl GAME_VAR(int, 0x9dad8c)   /* 0x9d (DIK_RCONTROL; game.h alias g_keyRightCtrl): default ALT SHOOT; a modifier for game type back (arena_createClick, room_settingsClicks, mapList_stepGameType) */
#define g_dikLeft GAME_VAR(int, 0x9dae14)   /* 0xcb (DIK_LEFT; game.h alias g_keyLeft): default LEFT TURN; previous in the in-match Esc menu (match_combatInput); the menus' left key */
#define g_dikEnter GAME_VAR(int, 0x9dae70)   /* 0x1c (DIK_RETURN; game.h alias g_keyClick): default CHAT (g_keyChat); selects in the in-match Esc menu; skip while held in a replay; closes a message box; the menus' fire / click key */
#define g_dikUp GAME_VAR(int, 0x9db0a0)   /* 0xc8 (DIK_UP; game.h alias g_keyUp): previous in the in-match Esc menu (match_combatInput); the menus' up key */
#define g_dikRShift GAME_VAR(int, 0x9db0ac)   /* 0x36 (DIK_RSHIFT; game.h alias g_keyRightShift): a modifier for game type back (arena_createClick, room_settingsClicks, mapList_stepGameType) and field back (newIdForm_keys, roomLogin_keys) */
#define g_dikRight GAME_VAR(int, 0x9db974)   /* 0xcd (DIK_RIGHT; game.h alias g_keyRight): default RIGHT TURN; next in the in-match Esc menu (match_combatInput); the menus' right key */
#define g_gameRunning GAME_VAR(int, 0x4b2790)   /* game_WinMain's message loop runs while set (1 at its start); cleared by game_wndProc on exit mode 0 just before ExitProcess */
#define g_viewFov GAME_VAR(float, 0x4c4dec)   /* the match view's vertical field of view in degrees (gluPerspective fovy in gfx_setMatchProjection; stage_setupView); 90 in the exe's data; view_fov / view_setFov; zoom_view moves it within 10 .. 60 */
#define g_viewNear GAME_VAR(float, 0x4c4df0)   /* the match view's near plane (100): read by view_nearPlane (stage_setupView) and gfx_setMatchProjection; never written in src */
#define g_viewFar GAME_VAR(float, 0x4c4df4)   /* the match view's far plane (1e6): read by view_farPlane (stage_setupView) and gfx_setMatchProjection; never written in src */
#define g_catalogueFile GAME_VAR(const char *, 0x4d05a4)   /* "Data/Component.dat": passed to catalogue_loadComponents when the local player joins (match_frame) */
#define g_hostErrorBox GAME_VAR(int, 0x4db55c)   /* the create-arena screen's NETWORK INITIALIZE ERROR box is up: set 1 when hosting an IPX arena fails (lobby_hostArenaIpx); cleared by its C / O keys, buttons 0x10 / 0x11, a right click (hostError_keys, hostError_clicks) and lobby_enterCreate */
#define g_editingNewArenaName GAME_VAR(int, 0x4dbab0)   /* the CREATE ARENA form's game name (30) is being typed: set by arena_editGameName; arenaCreate_keys takes the finished line into g_newArenaName (blank: unchanged) and clears it; blocks the clicks; cleared by menuState400_enter, lobby_enterCreate */
#define g_joinPollTicks GAME_VAR(int, 0x4dbb10)   /* ticks of the join timer 0x378 (2 s; WndProc: dplay_listSessions each tick until a session arrives); past 30 the join gives up (g_joinTimedOut set). Zeroed when a join starts or ends: arena_joinListed, room_joinListed, arena_joinAnswer, room_joinAnswer, gameList_stopJoin, gameList_keys, arenaGames_keys, arenaJoinBox_clicks */
#define g_armcUnusedFlag GAME_VAR(int, 0x4dc788)   /* cleared to 0 by armc_open and armc_showPartsPage; never set or read */
#define g_armcLeaving GAME_VAR(int, 0x4dcf10)   /* the ARM CENTER is being left: set 1 by armc_exit, cleared by armc_open; while set menuState700_armCenter (state 2) skips the camera ease, the 3D view and the panels */
#define g_progressWentUp GAME_VAR(int, 0x4dcf34)   /* 1 when the ARM CENTER opens (armc_open) with the pilot's level (from a game room) or progress (solo) above its best so far (g_bestLevelNet / g_bestProgressSolo); 0 at each armc_open and when a profile is made current (profile_makeCurrent); never read */
#define g_watchChatOpen GAME_VAR(int, 0x4de6fc)   /* the chat line is open while watching with the free camera (screen 9999): set by g_keyChat in freeCam_keys (50 characters); cleared when the line closes (sent by net_sendChat unless empty); freeCam_mouseLook does nothing while set */
#define g_roomGameMode GAME_VAR(signed char, 0x4df9eb)   /* the room form's game mode (GameSettings.mode at g_roomSettingsName + 0x23; 0 .. 9, the mode names MSG(791) + mode * 0x80) */
#define g_roomRecGameMode GAME_VAR(signed char, 0x5b1b53)   /* the registry record's game mode (GameSettings.mode at g_roomRecName + 0x23); roomSettings_page resets it to 0 outside 0 .. 11 */
#define g_matchRunning GAME_VAR(int, 0x5b1dac)   /* set 1 by match_enter, 0 by app_startupLoad and game_postMatch; never read */
#define g_cfgSimpleMenu GAME_VAR(int, 0x83a9d8)   /* axis.cfg's "set_graphic simplemenu" switch (g_cfgSwitches[3], 1 ON; cfg_readGraphics / cfg_writeGraphic; 0 by cfg_init); app_screenSizeForMode copies it into g_simpleMenu */
#define g_pilotExpKept GAME_VAR(int, 0x9dd244)   /* exp of the kept copy of the pilot's record (PilotStats at g_pilotLevelKept): from g_pilotExp (room_copyAccountRecord), made equal / capped by pilotRecord_syncCopies, set by record_send, 0 by newId_register */
#define g_pilotKillsKept GAME_VAR(int, 0x9dd254)   /* kills of the kept pilot record (see g_pilotExpKept); compared with g_pilotKills in pilotRecord_syncCopies */
#define g_accountRankDue GAME_VAR(int, 0x9dd354)   /* the rank reply is in and the account page is to take it: set by game_wndProc when g_rankReplyIn; account_page then calls account_takeRank, which clears it; cleared by room_enterAccountPage */
#define g_pilotLevel GAME_VAR(int, 0x9dd5d8)   /* the pilot's Ladder level (g_pilotStats +0): login reply +0xef (login_takeAccountRecord), 1 for a new ID, from the exp in record_send; room ARM CENTER parts unlocked to level - 1; not 20: armc_resetSeraphimParts (match_enter); shown with its rank badge */
#define g_pilotExp GAME_VAR(int, 0x9dd5dc)   /* the pilot's exp (g_pilotStats +4): login reply +0xff (login_takeAccountRecord, also into g_ladderExp), 0 for a new ID, set by record_send / pilotRecord_syncCopies; shown on the account panel (account_drawPanel) */
#define g_pilotKills GAME_VAR(int, 0x9dd5ec)   /* the pilot's kills (g_pilotStats +0x14): login reply +0xf7 (login_takeAccountRecord, also into g_ladderKills), 0 for a new ID, set by record_send / pilotRecord_syncCopies; shown on the account panel (account_drawPanel) */
#define g_roomAwaitingServer GAME_VAR(int, 0x9dd6d4)   /* the account page waits for the rank reply: set 1 by room_enterAccountPage (request 29 sent); cleared by account_takeRank, room_initCameraPoints, menu_returnToMainFromRoom, menuState800 entry; while 1 the page shows DOWNLOADING RANKING DATA, only Esc works */
#define g_skirmishPreviewDue GAME_VAR(int, 0x9f63b0)   /* the skirmish screen's map preview is to be loaded: set by menuState500_enterSkirmish and skirmish_roundChosen; skirmish_roundScreen loads "<g_stageDir><map>/<map>" into g_mapPreviewTexture and clears it */
#define g_chatTyping GAME_VAR(int, 0x9f67e8)   /* set when a match text field opens (match_openTextField: the chat line, or the Esc menu's replay name); cleared by match_endTyping only when the line is not empty (an empty line leaves it 1); never read */
#define g_matchLogWritten GAME_VAR(int, 0x9f67f0)   /* set 1 when match_frame writes the round-end match log (g_writeMatchLog, raised by round_over; launched for a net game); the log on leaving the match is written only while it is 0; never cleared */
#define g_matchEndedByUser GAME_VAR(int, 0x9f67f4)   /* the local player ended the match: set 1 by match_frame when the host / solo player quits (msg_userEndsGame or msg_serverEndsGame), 0 when a client quits; with g_matchEndedByServer picks the end-of-match log's format (match_frame) */
#define g_matchEndedByServer GAME_VAR(int, 0x9f67f8)   /* set 1 when the server's end-of-game packet (type 3, 'k') starts the match's end (net_processGamePacket); picks the end-of-match log's format (match_frame); never cleared */
#define g_profileLogInAsked GAME_VAR(int, 0x9f6840)   /* LOG IN chosen on the profile screen (button 2, key I, or the chosen row clicked twice: page 4, profile_logIn; the pilot grid is page 6); profile_logIn does nothing without it; cleared only on entering the screen (menuState210_enter) */
#define g_profileRowClickTime GAME_VAR(float, 0x9f8f18)   /* the time (1/60 s, g_frameTime) since a profile row was clicked (g_profileRowClicked); past 20 the click is forgotten; a second click on the same row within it opens the pilot grid (a double click) */
#define g_netHostGone GAME_VAR(int, 0x9fd94c)   /* the network game is over: set when slot 0 (the host) is freed (net_freeSlotsOf), when the TCP sockets are closed (net_closeSockets), or to the word at +4 of a type 2 game message (net_handleMessage); cleared by net_resetState / match_setupOrStartRound. Read by net_hostGone (0x4a86e0: the match quits) and net_handleSystemMessage (no per-player slot freeing once set) */
#define g_rankReplyIn GAME_VAR(int, 0xa0b354)   /* the reply to request 29 (the rank) has arrived: set by net_recv when g_rankReplyCode is not 0; game_wndProc then sets g_accountRankDue; cleared by account_takeRank */
#define g_newIdAnswer GAME_VAR(int, 0xa0b37c)   /* the game server's answer to request 15, the new ID's registration (newId_register): 0x21 accepted, 0x1e refused (message 0x22), 0x2a the update notice, 0x28 no answer; newIdConfirm_update reads and clears it */
#define g_mapMissing GAME_VAR(int, 0xa0ea94)   /* the match's map has no name (g_mapNames[g_mapIndex] empty): set 1 by game_processLoadingMode's stage 1 (else 0), which stops the load; game_postMatch shows message 6 and clears it */
#define g_errorCleanupHook GAME_VAR(Cleanup, 0xa1efe8)   /* function run before exit(1) by the fatal error reporters (error_log.c terminate: sys_errorTerminate, sys_fatalError); set from ErrorLog_ctor's cleanupHook; 0 none */
#define g_displayModeLeft GAME_VAR(u8, 0xb12a81)   /* the game's display mode was given up in the background: set 1 by game_wndProc's WM_ACTIVATEAPP (deactivated with g_displayModeChanged: desktop mode back, minimised); on reactivation cleared and g_otherModeWidth x g_otherModeHeight set again */
#define g_otherModeHeight GAME_VAR(int, 0xb12a88)   /* height of the last non-desktop display mode set (app_setDisplayMode); set again with g_otherModeWidth when the game is reactivated (game_wndProc, g_displayModeLeft) */
#define g_energyBarWidth GAME_VAR(float, 0xb68ce0)   /* 8: the HUD energy bar's left edge in HUD units, where the installed exe's patch moved it (its section .axnet); hud_main.c (in the test build read through the operand that uses it, the patch DLL may move it again) */
#define g_energyBarHeight GAME_VAR(float, 0xb68ce4)   /* 160: the HUD energy bar's length in HUD units (see g_energyBarWidth) */
#define k_69_9 GAME_VAR(double, 0x4a93e0)
#define k_100f GAME_VAR(float, 0x4a93f4)
#define k_10f GAME_VAR(float, 0x4a9418)
#define k_3600f GAME_VAR(float, 0x4a94c8)
#define k_10000f GAME_VAR(float, 0x4a9708)
#define g_mapListMade GAME_VAR(int, 0x4db510)   /* the rotation's map on / off list was made once: mapList_init turns on the first g_mapCount maps only while it is 0, then sets it 1 */
#define g_editingNewArenaTimeLimit GAME_VAR(int, 0x4db518)   /* the CREATE ARENA form's time limit is being typed (arena_editTimeLimit); arenaCreate_keys takes the number (0 .. 250, else 250) into g_newArenaTimeLimit and clears it (see g_editingNewArenaName) */
#define g_typingArenaJoinPassword GAME_VAR(int, 0x4db70c)   /* the password of a locked game is being typed (arena_editJoinPassword); once the field closes arena_gamesPageFrame takes the line into g_arenaJoinPassword, clears it and checks it against the session's */
#define g_editingNewArenaFragLimit GAME_VAR(int, 0x4db850)   /* the CREATE ARENA form's frag limit is being typed (arena_editFragLimit); arenaCreate_keys takes the number (0 .. 250, else 250) into g_newArenaFragLimit and clears it (see g_editingNewArenaName) */
#define g_lobbyPanelsSliding GAME_VAR(int, 0x4db85c)   /* the arena lobby's top menu is sliding in: set by menuState400_enter; while set lobby_slidePanels (menu_slide) eases g_lobbySlideEase and moves g_arenaTunnelDepth, clearing it at the end (depth -1650), and lobbyTop_drawMenu hovers no panel. lobby_enterPlayerScreen / lobby_enterArenaList / lobby_enterCreate clear it */
#define g_armcCameraTravelling GAME_VAR(int, 0x4dc868)   /* the ARM CENTER's camera is between the menus and the ARM CENTER: set by armc_open and while it flies home (armc_cameraStep, state 0), cleared when it arrives (state 2); while set (and not from the lobby, g_armcFrom 2) menuState700_armCenter draws the menus' background */
#define g_ladderLevel GAME_VAR(int, 0x4de71e)   /* the Ladder record's level (g_ladderName +0x1e): 1 for a new ID (newId_register), g_pilotLevel at login (login_takeAccountRecord); pilotRecord_syncCopies puts the Ladder record into the pilot records when their kills or exp are past it */
#define g_mouseWheelTurned GAME_VAR(int, 0x4ded70)   /* the wheel turned this frame: input_updateMouse sets 1 when the read's wheel is not 0, else 0 (0 at WM_CREATE); setup_controlTabClicks binds WHEEL-UP / WHEEL-DOWN with it */
#define g_mouse2Down GAME_VAR(int, 0x4ded98)   /* the right mouse button held (g_mouseButtonsHeld[1]: 0 / 0x80; input_updateMouse): key 0xfb in input_isDown; turns the ARM CENTER's preview (armc_drawPreview3D) */
#define g_camPoint0X GAME_VAR(float, 0x4df870)   /* X of the menu camera's target point 0 (g_camPoints[0]: arena_camera / armc_cameraStep ease the eye to it, menu_cameraToPoint0 / armc_snapCameraToPoint0 snap): 35 lobby / setup, 20 game room, 0 ARM CENTER and skirmish */
#define g_camPoint0Y GAME_VAR(float, 0x4df874)   /* Y of the menu camera's target point 0 (see g_camPoint0X): 0, -10 in the game room */
#define g_camPoint0Z GAME_VAR(float, 0x4df878)   /* Z of the menu camera's target point 0 (see g_camPoint0X): the look-at's depth (camera_pointsAtLookZ, lobby_enterPlayerScreen); 100, or -1000 from the game room (armc_open); 100 for the briefing camera */
#define g_camAim0X GAME_VAR(float, 0x76d388)   /* X of the menu camera's look-at point 0 (g_camAims[0]; see g_camPoint0X): -70 lobby / setup / game room, 0 ARM CENTER and skirmish */
#define g_camAim0Y GAME_VAR(float, 0x76d38c)   /* Y of the menu camera's look-at point 0 (see g_camAim0X): 35 lobby / setup, 55 game room, 0 ARM CENTER and skirmish */
#define g_camAim0Z GAME_VAR(float, 0x76d390)   /* Z of the menu camera's look-at point 0 (see g_camAim0X): the look-at's depth (camera_pointsAtLookZ); 0, or -1100 from the game room (armc_open) */
#define g_editingEmail GAME_VAR(int, 0x9dd304)   /* the account page's e-mail (50) is being typed: set by edit_account (field 3); account_page takes the line into g_accountEmail; cleared by room_enterAccountPage; account_drawPanel leaves the e-mail out while set */
#define g_editingPasswordRepeat GAME_VAR(int, 0x9dd378)   /* the account page's new password repeat (12, hidden) is being typed: set by edit_account (field 2); account_page takes the line into g_accountPasswordRepeat; cleared by room_enterAccountPage (see g_editingEmail) */
#define g_editingAccountPassword GAME_VAR(int, 0x9dd37c)   /* the account page's new password (12, hidden) is being typed: set by edit_account (field 1); account_page takes the line into g_accountPassword; cleared by room_enterAccountPage (see g_editingEmail) */
#define g_pilotPower GAME_VAR(float, 0x9dd5e4)   /* the pilot's power (float, g_pilotStats +0xc): login reply +0x103 (also into g_ladderPower), from g_ladderPower in pilotRecord_syncCopies, set by record_send; shown "%.2f" on the account panel (account_drawPanel) */
#define g_editingOldPassword GAME_VAR(int, 0x9dd69c)   /* the account page's old password (12, hidden) is being typed: set by edit_account (field 0); account_page takes the line into g_accountOldPassword; cleared by room_enterAccountPage (see g_editingEmail) */
#define g_editLineDone GAME_VAR(int, 0x9dd900)   /* set 1 when the hidden edit field closes (edit_close on Enter / Esc; Tab in the game room, editField_editProc); never read or cleared */
#define g_penFontTexture GAME_VAR(int, 0xa106ac)   /* texture ID of the pen font / HUD texture (bank ID / 512, slot ID % 512): set by pen_init (tex_getIdByName); bound by hud_drawDigits and font_penDraw */
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
#define g_tunnelStep GAME_VAR(int, 0x4b2a74)   /* the menu tunnel's step this frame: frame time x 30, truncated (menuTunnel_advance, which loads it back as the float g_tunnelStepF; a ring's moveSteps grows by it) */
#define g_tunnelStepF GAME_VAR(float, 0x4b2a78)   /* g_tunnelStep as a float: menuTunnel_advance moves the eye and look point this far down (in) or up (out) the tunnel each frame */
#define g_musicVolumeSetting GAME_VAR(int, 0x4b42dc)   /* written by music_setVolumeSetting only; never read */
#define g_hangulVowelGlyph GAME_VAR(int, 0x4d23d4)   /* a Korean character's vowel glyph (vowel + vowelGlyphSet x 22; hangul_glyphs); drawn with g_hangulTailGlyph by a layered text pass (text_pass) */
#define g_hangulTailGlyph GAME_VAR(int, 0x4d23dc)   /* a Korean character's tail glyph (tail + tailGlyphSet x 28; hangul_glyphs, which returns it); drawn with g_hangulVowelGlyph by a layered text pass (text_pass) */
#define g_hangulLeadGlyph GAME_VAR(int, 0x4d60e0)   /* a Korean character's lead glyph (lead + leadGlyphSet x 20; hangul_glyphs); drawn alone by a text pass that is not layered (text_pass) */
#define g_newArenaFormLeft GAME_VAR(int, 0x4dbb00)   /* left of the CREATE ARENA form's window (g_newArenaForm; 40, menuState400_enter): its frame (lobbyCreate_frame), the form (arena_createDraw), the buttons (createArena_layout), the edit carets */
#define g_newArenaFormTop GAME_VAR(int, 0x4dbb04)   /* top of the CREATE ARENA form's window (see g_newArenaFormLeft): 30; also places the map preview (arena_drawMapPreview) */
#define g_newArenaFormRight GAME_VAR(int, 0x4dbb08)   /* right of the CREATE ARENA form's window (see g_newArenaFormLeft): 600 */
#define g_newArenaFormBottom GAME_VAR(int, 0x4dbb0c)   /* bottom of the CREATE ARENA form's window (see g_newArenaFormLeft): 450 */
#define g_armcLevel GAME_VAR(int, 0x4dc870)   /* the unlocked level the ARM CENTER's part lists were built to (armc_buildPartLists, as g_unlockedLevel); never read */
#define g_boosterCount GAME_VAR(int, 0x4dc890)   /* the booster list's length (g_boosterList; armc_buildPartLists) */
#define g_messageBoxArgs GAME_VAR(va_list, 0x4dd0b4)   /* sys_messageBox's va_list, kept while vsprintf formats the text, then cleared; never read */
#define g_setupSound3D GAME_VAR(int, 0x4ddea0)   /* the sound tab's 3D sound switch being edited (g_soundEdited[2]): flipped by button 6 (setup_soundTabClicks), shown ON / OFF (setup_drawSoundPage); OK (sound_ok) makes it g_sound3D */
#define g_setupStereoReverse GAME_VAR(int, 0x4ddea4)   /* the sound tab's stereo reverse switch being edited (g_soundEdited[3]): flipped by button 7 (setup_soundTabClicks), shown ON / OFF (setup_drawSoundPage); OK (sound_ok) makes it g_stereoReverse */
#define g_showCmd GAME_VAR(int, 0x4deb54)   /* WinMain's show command, kept by app_init; never read */
#define g_mouse3Down GAME_VAR(int, 0x4ded9c)   /* the middle (third) mouse button held (g_mouseButtonsHeld[2]: 0 / 0x80; input_updateMouse): key 0xfc in input_isDown */
#define g_keyChat GAME_VAR(int, 0x4defa8)   /* the chat key binding (DIK code, default Enter 0x1c; second key at g_controls +0xac): talk in a match (match_combatInput); opens the chat line when watching (freeCam_keys) */
#define g_keyGameMenu GAME_VAR(int, 0x4defc8)   /* the game-menu key binding (DIK code, default Escape 1; second key g_keyGameMenu2): asks to quit in a match (match_combatInput) or replay (replay_frame); stops the loading wait (game_processLoadingMode) */
#define g_keyGameMenu2 GAME_VAR(int, 0x4defcc)   /* second key of the game-menu binding (see g_keyGameMenu); default none */
#define g_screenCentreX GAME_VAR(int, 0x4e1520)   /* half the screen width (g_screenW / 2; app_startupLoad); never read */
#define g_texture64x64Vtable GAME_VAR(u32, 0x4e1878)   /* vtable word of the 64 x 64 texture set g_texture64x64 (Texture, 0x4a956c; static_initTex64x64) */
#define g_perfCounterHigh GAME_VAR(u32, 0x5ae9cc)   /* the last QueryPerformanceCounter reading's high word (timer_now; the low word in g_perfCounterLow); never read */
#define g_texture128x64Vtable GAME_VAR(u32, 0x5b1db8)   /* vtable word of the 128 x 64 texture set g_texture128x64 (Texture, 0x4a956c; static_initTex128x64) */
#define g_screenCentreY GAME_VAR(int, 0x680394)   /* half the screen height (g_screenH / 2; app_startupLoad); never read */
#define g_texture256x64Vtable GAME_VAR(u32, 0x680cd8)   /* vtable word of the 256 x 64 texture set g_texture256x64 (Texture, 0x4a956c; static_initTex256x64) */
#define g_menuLookHomeX GAME_VAR(float, 0x76d3f8)   /* the menu camera's home look-at point (g_menuLookHome[0]) */
#define g_menuLookHomeY GAME_VAR(float, 0x76d3fc)   /* Y of the menu camera's home look-at point (see g_menuLookHomeX) */
#define g_menuLookHomeZ GAME_VAR(float, 0x76d400)   /* Z of the menu camera's home look-at point (see g_menuLookHomeX): -550 in the menus, -1650 for the ARM CENTER from the game room and back in the arena lobby (armc_cameraStep) */
#define g_editFieldLength GAME_VAR(int, 0x76d418)   /* width in characters of the hidden edit field (editField_createEdit's chars); never read */
#define g_texture128x128Vtable GAME_VAR(u32, 0x76d498)   /* vtable word of the 128 x 128 texture set g_texture128x128 (Texture, 0x4a956c; static_initTex128x128) */
#define g_texture256x256Vtable GAME_VAR(u32, 0x83a9e0)   /* vtable word of the 256 x 256 texture set g_texture256x256 (Texture, 0x4a956c; static_initTex256x256) */
#define g_skirmishInfoCount GAME_VAR(int, 0x90d1d8)   /* the number of 0x5c-byte entries in g_skirmishInfo, read from skirmish.dat after its header and 25000 more bytes (data_loadSkirmishInfo) */
#define g_texture256x128Vtable GAME_VAR(u32, 0x90d1e0)   /* vtable word of the 256 x 128 texture set g_texture256x128 (Texture, 0x4a956c; static_initTex256x128) */
#define g_menuEyeHomeX GAME_VAR(float, 0x9db090)   /* the menu camera's home position (g_menuEyeHome[0]) */
#define g_menuEyeHomeY GAME_VAR(float, 0x9db094)   /* Y of the menu camera's home position (see g_menuEyeHomeX) */
#define g_menuEyeHomeZ GAME_VAR(float, 0x9db098)   /* Z of the menu camera's home position (see g_menuEyeHomeX): -450 for the briefing camera and the ARM CENTER, -1550 for the ARM CENTER from the game room and back in the arena lobby */
#define g_roomFormLeft GAME_VAR(int, 0x9dd1b8)   /* left of the game room's create-game form window (g_roomForm; 40, menuState800_enterGameRoom): its frame (roomSettings_page), the form (room_drawGameSettings), the buttons (roomSettings_layout), the edit carets */
#define g_roomFormTop GAME_VAR(int, 0x9dd1bc)   /* top of the game room's create-game form window (see g_roomFormLeft): 30; also places the map preview (room_drawMapPreview) */
#define g_roomFormRight GAME_VAR(int, 0x9dd1c0)   /* right of the game room's create-game form window (see g_roomFormLeft): 600 */
#define g_roomFormBottom GAME_VAR(int, 0x9dd1c4)   /* bottom of the game room's create-game form window (see g_roomFormLeft): 450 */
#define g_pilotPowerKept GAME_VAR(float, 0x9dd24c)   /* power (float) of the kept pilot record (see g_pilotExpKept): from g_ladderPower in pilotRecord_syncCopies, set by record_send */
#define g_pilotDeathsKept GAME_VAR(int, 0x9dd258)   /* deaths of the kept pilot record (see g_pilotExpKept): from g_pilotDeaths (room_copyAccountRecord), synced by pilotRecord_syncCopies, 0 by newId_register */
#define g_gameListRefreshClicked GAME_VAR(int, 0x9dd4bc)   /* set when the game room's list request goes out (REFRESH, button 1 = MSG(388) '$[0] REFRESH', or the R key; gameList_refresh succeeded); cleared by room_enterGameList; never read */
#define g_pilotDeaths GAME_VAR(int, 0x9dd5f0)   /* the pilot's deaths (g_pilotStats +0x18): login reply +0xfb (login_takeAccountRecord, also into g_ladderDeaths), 0 for a new ID, set by record_send / pilotRecord_syncCopies; shown on the account panel (account_drawPanel) */
#define g_pilotKillRate GAME_VAR(float, 0x9dd5f4)   /* the pilot's kill rate (float, g_pilotStats +0x1c): login reply +0x107 (login_takeAccountRecord), copied to the kept record, 0 for a new ID, set by record_send; shown "%.2f" on the account panel */
#define g_languageId GAME_VAR(u16, 0x9dd858)   /* GetSystemDefaultLangID's answer (game_WinMain; 0x412 / 0x812, Korean, set g_language 1); not read again */
#define g_clockCheckSeconds GAME_VAR(int, 0x9dd860)   /* seconds the system clock moved since the last clock check (sys_checkClockTampering); written only */
#define g_clockCheckTick GAME_VAR(u32, 0x9dd8e0)   /* timeGetTime at the last clock check (sys_checkClockTampering); written only */
#define g_clockCheckTickSeconds GAME_VAR(u32, 0x9dd8ec)   /* seconds by timeGetTime since g_startTicks at the last clock check (sys_checkClockTampering); written only */
#define g_progressSeen GAME_VAR(int, 0x9f62fc)   /* the campaign progress the skirmish screen has already announced: set from g_progress when a profile is made current (profile_makeCurrent); menuState500_enterSkirmish raises the briefing (g_skirmishNewPartsNotice) when g_progress has passed it, then catches it up */
#define g_skirmishChosen GAME_VAR(int, 0x9f6328)   /* the skirmish round picked: g_progress (at most 14) by menuState500_enterSkirmish, the clicked one by skirmish_roundChosen; never read */
#define g_netClaimedSlot GAME_VAR(int, 0x9f9424)   /* byte +4 of the 8-byte message g_netSlotMsg (kind g_netSlotMessageKind): the slot the host claims for a joining player (net_claimPlayerSlot in net_handleSystemMessage), sent to it; 0 by net_resetState */
#define g_lobbyReplyKind GAME_VAR(u32, 0xa052aa)   /* a lobby reply's kind (g_lobbyReplyRecord +0x4a; net_receiveLobbyReply): 0 a server for the list, 1 the list's end (pings started, g_lobbyListAnswer 0xca), 2 g_lobbyListAnswer 0xcb, 3 0x29 */
#define g_playerListReplyKind GAME_VAR(int, 0xa05306)   /* the game server's player-list reply's kind (g_playerListReply +0x1e; net_receivePlayerListReply): 0 a player (net_addPlayerRecord), 1 the list's end (g_playerListDone set) */
#define g_netAccountRequest GAME_VAR(char *, 0xa055e0)   /* the 0x1e-byte body of request 29 (0x1d, the rank): the Ladder ID (room_enterAccountPage); allocated by net_resetConnection, freed by net_freeBuffers */
#define g_gameServerReplyKind GAME_VAR(u32, 0xa0b2e8)   /* a game server room-list reply's kind (g_gameServerReply +0x68; net_receiveGameServerReply): 0 a room (net_addRoomRecord), 1 the list's end (pings started, g_roomListAnswer 0xca), 2 / 3 refused (0x28) */
#define g_lobbyKeepAlive GAME_VAR(char *, 0xa0b304)   /* the 16-byte buffer of packet 23 (0x17), the lobby keep-alive sent on timer 0x29a while hosting an arena (g_hostingState 2: WndProc / editField_editProc): the hosted arena's address (g_arenaPacket's ArenaRecord.address) */
#define g_gameServerKeepAlive GAME_VAR(char *, 0xa0b308)   /* the 16-byte buffer of packet 24 (0x18), the game server keep-alive sent on timer 0x115c while g_roomConnected: this machine's address (g_localAddress) */
#define g_netKindBuffer GAME_VAR(u32 *, 0xa0b30c)   /* the 4-byte buffer net_send puts a packet's kind in and sends first to the lobby (100) or game server (101); allocated by net_resetConnection, freed by net_freeBuffers */
#define g_arenaInfoPacket GAME_VAR(u8 *, 0xa0b314)   /* the 0x5b-byte packet 12 to the lobby: the hosted arena's record (g_arenaPacket) with the player count, rebuilt when a player comes or goes (net_handleSystemMessage, arena_info); allocated by net_resetConnection */
#define g_arenaListRequest GAME_VAR(u32 *, 0xa0b31c)   /* the 4-byte packet 13 to the lobby (lobby_openConnection writes 0x180001): asks for the arena list (net_send 13 clears g_serverList first; net_recv 13 -> net_receiveLobbyReply adds the servers) */
#define g_netRankingBuffer GAME_VAR(int *, 0xa0b324)   /* the 8-byte body of request 21 (0x15, a ranking page): the sort code (0x25 / 0x23 / 0x26 by g_rankingSort) and the first rank (page x 10 + 1) (ranking_page); allocated by net_resetConnection */
#define g_netPlayerRecordPacket GAME_VAR(u8 *, 0xa0b338)   /* the 0x36-byte packet 17 (0x11): the pilot's Ladder record (PlayerRecordPacket: name, games, kills, deaths, exp, power, level) filled by record_send (ladder_checkAndSendRecord); allocated by net_resetConnection */
#define g_netLeaveBuffer GAME_VAR(char *, 0xa0b33c)   /* request 25's (0x19) 0x1e-byte body: the Ladder ID, sent to the game server when the game room is left (room_leave); allocated by net_resetConnection */
#define g_netSelectionPacket GAME_VAR(u8 *, 0xa0b340)   /* the 0xb9-byte packet 27 (0x1b): the Ladder ID, the 11 mech bytes at +0x1e and the colours at +0x29 (armc_sendSelectionToNet); allocated by net_resetConnection */
#define g_netAccountBuffer GAME_VAR(char *, 0xa0b344)   /* the 0x5c-byte message 28 (0x1c), the account change (AccountForm: name, new password, e-mail; account_sendChange); allocated by net_resetConnection, freed by net_freeBuffers */
#define g_lobbyStatus GAME_VAR(int, 0xa0b370)   /* the lobby's status after request 10 (net_recv: 0x66 reply 0, 0x67 reply 1 (disconnected), 0x29 no reply in 3 s); WndProc's g_lobbySocket message 0x40a turns it into g_hostAnswer (0x29 -> 4, 0x66 -> 1, 0x67 -> 3, else 0) */
#define g_gameServerStatus GAME_VAR(int, 0xa0b374)   /* the game server's status after request 18 (net_recv: 0x66 reply 0, 0x67 reply 1 (disconnected), 0x28 no reply in 3 s); WndProc's game server socket message 0x40c turns it into g_hostAnswer (0x28 -> 4, 0x66 -> 1, 0x67 -> 3, else 0) */
#define g_joinTimer GAME_VAR(u32, 0xa0bad0)   /* the id SetTimer(0x378, 2000 ms) returns when a join's session search starts: the arena's (arena_joinListed) and the game room's (room_joinListed); never read (WndProc's WM_TIMER 0x378 kills the timer by its id) */
#define g_dpTimeout GAME_VAR(u32, 0xa0bb00)   /* the DirectPlay connection's DPCAPS.dwTimeout (ms; GetCaps in dplay_initConnection); never read */
#define g_dpMaxBufferSize GAME_VAR(u32, 0xa0bb04)   /* the DirectPlay connection's DPCAPS.dwMaxBufferSize (bytes; GetCaps in dplay_initConnection); never read */
#define g_dpMaxQueueSize GAME_VAR(u32, 0xa0bb08)   /* the DirectPlay connection's DPCAPS.dwMaxQueueSize (GetCaps in dplay_initConnection); never read */
#define g_musicEndHigh GAME_VAR(int, 0xa0e01c)   /* high dword of the music's 64-bit duration (g_musicDuration[1], with g_musicLength the low; music_play); music_loopIfEnded compares the play position with it to restart the music */
#define g_mciCallback GAME_VAR(u32, 0xa1efc8)   /* MCI parameter block word 0 (dwCallback) movie_pauseEnding sends with MCI_PAUSE (with g_mciFrom / g_mciTo); written by the original movie_playEnding (0x46c420, called by address; AxisRC.exe plays the movie with the patch layer's player instead) */
#define g_mciFrom GAME_VAR(u32, 0xa1efcc)   /* MCI parameter block word 1 (dwFrom) movie_pauseEnding sends with MCI_PAUSE (see g_mciCallback); written by the original movie_playEnding (0x46c420, called by address; AxisRC.exe plays the movie with the patch layer's player instead) */
#define g_mciTo GAME_VAR(u32, 0xa1efd0)   /* MCI parameter block word 2 (dwTo) movie_pauseEnding sends with MCI_PAUSE (see g_mciCallback); written by the original movie_playEnding (0x46c420, called by address; AxisRC.exe plays the movie with the patch layer's player instead) */
#define g_mciDevice GAME_VAR(u32, 0xa1efd8)   /* the ending movie's MCI device id movie_pauseEnding sends MCI_PAUSE to; written by the original movie_playEnding (0x46c420, called by address; AxisRC.exe plays the movie with the patch layer's player instead) */
#define g_cursorPosY GAME_VAR(int, 0xae2f1c)   /* the cursor's y (screen pixels; g_cursorPoint[1], with g_cursorX), from GetCursorPos in input_getCursorPos while the game window is in front */
#define k_m450f GAME_VAR(u32, 0x4a9454)   /* -450.0 (a float's bits): the ARM CENTER camera's distance (armc_open) and the pose clamp's lower bound in actor_processFrame (tenths of a degree) */
#define k_armcDistanceRoom GAME_VAR(u32, 0x4a9458)   /* -1550.0 (a float's bits): the same, the ARM CENTER opened from a game room */
#define g_newArenaMap GAME_VAR(signed char, 0x4db548)   /* the create-arena form's map (g_newArenaName record +0x20; 0 .. g_mapCount-1, 22 .. 24 skipped): lobby_loadArenaSettings sets it, arena_stepMap steps it (not with the rotation on), arena_loadMapPreview shows it */
#define g_newArenaMaxPlayers GAME_VAR(signed char, 0x4db549)   /* the create-arena form's most players (byte, record +0x21; lobby_loadArenaSettings; arena_createClick button 3 adds 2, past 16 back to 2) */
#define g_newArenaRotation GAME_VAR(signed char, 0x4db54a)   /* the create-arena form's map rotation (byte, record +0x22): 0 off, 1 on (arena_createClick button 4 toggles, game type to 14 when on); with it on arena_stepMap does nothing and arena_drawMapPreview shows the rotation */
#define g_newArenaMode GAME_VAR(signed char, 0x4db54b)   /* the create-arena form's game type (byte, record +0x23): 0 .. 13, and 14 when stepped only with the rotation on (arena_createClick button 5 steps it, Shift / Ctrl back); set from g_arenaGameType by lobby_loadArenaSettings unchecked, so axis.cfg's type 14 also comes in with the rotation off */
#define g_newArenaPassword GAME_VAR(int, 0x4db54e)   /* first dword of the create-arena form's 8-byte password text (record +0x26, with g_newArenaPassword4): cleared by lobby_loadArenaSettings, the typed line copied in by arenaCreate_keys */
#define g_armcViewedPartTexture GAME_VAR(int, 0x4dcc88)   /* g_slotTextures[6]: the snapshot texture of the part under the ARM CENTER cursor (armc_loadSnapshotTexture(6)); armc_drawWeaponsScreen draws it in the part box */
#define g_keyForward GAME_VAR(int, 0x4def00)   /* the forward key binding (g_controls[0]; default W, store_tables): held into Scene.holdForward in a match and replays, moves the free camera forward (freeCam_keys); written to axis.cfg with the other bindings */
#define g_keyBackward GAME_VAR(int, 0x4def08)   /* the backward key binding (g_controls[2]; default S): Scene.holdBackward in a match and replays; moves the free camera back (freeCam_keys) */
#define g_keyStepLeft GAME_VAR(int, 0x4def10)   /* the step-left key binding (g_controls[4]; default A): Scene.holdStepLeft in a match and replays; freeCam_stepLeft in freeCam_keys */
#define g_keyStepRight GAME_VAR(int, 0x4def18)   /* the step-right key binding (g_controls[6]; default D): Scene.holdStepRight in a match and replays; freeCam_stepRight in freeCam_keys */
#define g_camPoint1X GAME_VAR(float, 0x4df880)   /* x of menu camera point 1 (g_camPoints[4]): 35 for the arena list (lobby_enterArenaList) and lobby / setup screens, 20 for the room's (room_initCameraPoints, screen_enter); the menu cameras ease toward it */
#define g_camPoint1Z GAME_VAR(float, 0x4df888)   /* z of menu camera point 1 (see g_camPoint1X): the menu camera's look-at z (g_menuCameraLookZ) when lobby_enterArenaList runs */
#define g_camPoint2X GAME_VAR(float, 0x4df890)   /* x of menu camera point 2 (g_camPoints[8]): -35 for the create-arena page (lobby_enterCreate) and lobby / setup screens, 20 for the room's (room_initCameraPoints) */
#define g_camPoint2Y GAME_VAR(float, 0x4df894)   /* y of menu camera point 2 (see g_camPoint2X): 0 (lobby_enterCreate, lobby / setup screens) or 10 (room_initCameraPoints, the room) */
#define g_camPoint2Z GAME_VAR(float, 0x4df898)   /* z of menu camera point 2 (see g_camPoint2X): g_menuCameraLookZ when lobby_enterCreate runs */
#define g_arenaFileMap GAME_VAR(int, 0x5b1944)   /* the arena file's map (atoi; arena_startFromLauncher takes the low byte into g_arenaMap) */
#define g_arenaFilePlayers GAME_VAR(int, 0x5b1948)   /* the arena settings file's "maxplayer" value (atoi; arena_loadSettings); arena_startFromLauncher takes its low byte into g_arenaMaxPlayers */
#define g_arenaFileGameType GAME_VAR(int, 0x5b194c)   /* the arena settings file's "gametype" value (atoi; arena_loadSettings); arena_startFromLauncher takes its low byte into g_arenaGameType */
#define g_arenaFileFragLimit GAME_VAR(int, 0x5b1950)   /* the arena settings file's "fraglimit" value (atoi; arena_loadSettings); arena_startFromLauncher takes its low byte into g_arenaFragLimit */
#define g_camAim1X GAME_VAR(float, 0x76d398)   /* x of menu camera look-at point 1 (g_camAims[4]): -70 (lobby_enterArenaList, room_initCameraPoints, screen_enter); the menu cameras ease the look-at toward it */
#define g_camAim1Y GAME_VAR(float, 0x76d39c)   /* y of menu camera look-at point 1 (see g_camAim1X): -35 (lobby_enterArenaList, lobby / setup screens) or 0 (room_initCameraPoints, the room) */
#define g_camAim1Z GAME_VAR(float, 0x76d3a0)   /* z of menu camera look-at point 1 (see g_camAim1X): g_menuCameraLookZ when lobby_enterArenaList runs */
#define g_camAim2X GAME_VAR(float, 0x76d3a8)   /* x of menu camera look-at point 2 (g_camAims[8]): 70 (lobby_enterCreate, lobby / setup screens) or -70 (room_initCameraPoints, the room) */
#define g_camAim2Y GAME_VAR(float, 0x76d3ac)   /* y of menu camera look-at point 2 (see g_camAim2X): 35 (lobby_enterCreate, lobby / setup screens) or -55 (room_initCameraPoints, the room) */
#define g_camAim2Z GAME_VAR(float, 0x76d3b0)   /* z of menu camera look-at point 2 (see g_camAim2X): g_menuCameraLookZ when lobby_enterCreate runs */
#define g_pilotGamesKept GAME_VAR(int, 0x9dd250)   /* the kept copy of the pilot's games played (with g_pilotLevelKept ..): room_copyAccountRecord copies g_pilotGames in, pilotRecord_syncCopies sets it to g_ladderGames, record_send (ladder_checkAndSendRecord) stores the record's, and take_back reads it back when the record's kills are 300 past the copy's; newId_register clears it */
#define g_pilotGames GAME_VAR(int, 0x9dd5e8)   /* the pilot's games played, from the server's account record (g_profileReply +0xf3, login_takeAccountRecord); copied to g_pilotGamesKept and g_ladderGames, set to g_ladderGames by pilotRecord_syncCopies; cleared by newId_register */
#define g_menuLookKeptX GAME_VAR(float, 0x9dd918)   /* the menu camera's look-at point (g_menuLook) kept by menuTunnel_advance (camera_keep) and put back a ring further when a tunnel move ends; X (with g_menuLookKeptY / Z; objects.h g_menuLookKept) */
#define g_menuLookKeptY GAME_VAR(float, 0x9dd91c)   /* y of the menu camera's kept look-at point (see g_menuLookKeptX); 0 from reset_menus */
#define g_menuLookKeptZ GAME_VAR(float, 0x9dd920)   /* z of the menu camera's kept look-at point (see g_menuLookKeptX); reset_menus sets it to the near z */
#define g_menuEyeKeptX GAME_VAR(float, 0x9dd930)   /* the menu camera's position (g_menuEye) kept by menuTunnel_advance (camera_keep; EYE_KEPT), X (with Y / Z; objects.h g_menuEyeKept) */
#define g_menuEyeKeptY GAME_VAR(float, 0x9dd934)   /* y of the menu camera's kept position (see g_menuEyeKeptX); 0 from reset_menus */
#define g_menuEyeKeptZ GAME_VAR(float, 0x9dd938)   /* z of the menu camera's kept position (see g_menuEyeKeptX); reset_menus sets it to the far z */
#define g_mainMenuFrames GAME_VAR(int, 0x9eeab0)   /* frames counted while the main menu's tunnel flies in (mainmenu_drawMenu, g_tunnelFlyingIn); 0 from menuState300_enter; never read */
#define g_matchTextFieldY GAME_VAR(int, 0x9f63c4)   /* the y given to match_openTextField for a match text field (the chat line, or the Esc menu's replay name; with g_matchTextFieldX): every caller passes 0; never read */
#define g_matchTextFieldX GAME_VAR(int, 0x9f63c8)   /* the x given to match_openTextField for a match text field (the chat line, or the Esc menu's replay name; with g_matchTextFieldY): every caller passes 0; never read */
#define g_textHitBottom GAME_VAR(int, 0x4d7348)   /* 1 once an ASCII text pass (text_ascii8Pass / 16 / 32) stopped at g_textBottom; the briefing takes it as its page being full: briefing_typeOut stops typing and its cursor, briefing_nextPage only then turns the page, the NEXT button is lit (mission_list.c). Cleared by app_startupLoad, mission_loadBriefing, briefing_nextPage / prevPage */
#define g_armcSlot GAME_VAR(int, 0x4dbe48)   /* the ARM CENTER item slot being picked: 0 .. 3 weapons, 4 .. 5 other items, -1 none (armc_pickSlot; armc_takeCursorItem puts the cursor's item in it; 0 from armc_open / armc_openWeaponsPage) */
#define g_armcFrom GAME_VAR(int, 0x4dc24c)   /* where the ARM CENTER was opened from: 1 the main menu (menu_tunnel / menu_records; menuState400_enter also sets 1 on entering the arena lobby), 2 the arena's player screen (lobby_playerScreenClicks), 3 the game room (room_clicks), 0 cleared (lobby_enterPlayerScreen, the camera's way back); armc_exit picks the way back and what a confirm does by it */
#define g_armcCursor GAME_VAR(int, 0x4dc77c)   /* the ARM CENTER's cursor in the item list of g_armcSlot (index in g_weaponListTable for slots 0 .. 3, g_extraListTable for 4 .. 5; wraps round, armc_showCursorItem) */
#define g_armcPageRight GAME_VAR(int, 0x4dcc98)   /* the ARM CENTER window's right edge (630, armc_open); with g_armcPageLeft / Top / Bottom the window every page draws in. The colour sliders start 184 units left of it (armc_colours.c) */
#define g_armcSpin GAME_VAR(int, 0x4dceac)   /* 1 while the ARM CENTER's mech preview turns (g_armcAngle += frame time x 8, tenths of a degree); 1 from armc_open, toggled by R and the rotate buttons (armc_*PageKeys, armc_*PageClicks) */
#define g_unusedArmcViewCountdown GAME_VAR(float, 0x4dcfd8)   /* float; set to 1 on each change of the part in view (armc_open, armc_partsPageClicks, armc_partsPageKeys, armc_readPartPanels), then lowered by 0.1 a frame time down to -2 (menuState700_armCenter); nothing else reads it */
#define g_setupPressedClock GAME_VAR(float, 0x4ddb98)   /* the glow time of the setup arrow last pressed (g_setupArrowPressed): 5 on a press (volume_down / up, slider_press), lowered by the frame time in setup_drawSoundPage, then the arrow is -1 again; 0 when a tab opens */
#define g_setupArrowPressed GAME_VAR(int, 0x4dde90)   /* the setup arrow last pressed: the sound tab's volume arrows (volume_down / up) or the controls tab's mouse-sensitivity minus / plus (slider_press): 0 down / minus, 1 up / plus; -1 none (a tab opened, or its glow g_setupPressedClock ran out). setup_drawSoundPage also has lit arrows a row lower for 2 / 3, which nothing sets */
#define g_setupTunnelAlpha GAME_VAR(float, 0x4de038)   /* the alpha of the tunnel behind the setup pages: 0.7 when a tab opens, eased to 0.3 (g_setupCameraMode 1) or 0.5 (mode 0) in setup_drawTunnel, which draws its layers with it */
#define g_bindRow GAME_VAR(int, 0x4de040)   /* the controls tab's selected row on the page g_bindPage: -1 none (setup_selectControlTab); Up / Down step it; a click starts waiting for a key (g_bindWaiting; setup_bindKey) or, on row 10, toggles g_bindToggle */
#define g_menuEyeY GAME_VAR(float, 0x4df028)   /* g_menuEye[1]: the menu camera's position, y (float) */
#define g_menuEyeZ GAME_VAR(float, 0x4df02c)   /* g_menuEye[2]: the menu camera's position, z (along the tunnel; float) */
#define g_gameCount GAME_VAR(int, 0x67ef30)   /* the number of games in g_sessionList (the arena lobby's and game room's list; net_sessions' merge appends, arenaList_rebuild sets it); 0 when a list screen opens or is refreshed */
#define g_menuTunnel GAME_VAR(TunnelRing *, 0x67fb3c)   /* the head of the menus' background tunnel's linked list of rings (tunnel_appendRing / tunnel_addRing add, armc_freeRing frees); menu_drawBackground moves (menuTunnel_advance) and draws it */
#define g_briefingStart GAME_VAR(int, 0x9eeba4)   /* the offset in the briefing text (g_briefingSource) where the page shown starts (briefing_nextPage / briefing_prevPage from g_briefingPageStarts; 0 from mission_loadBriefing); briefing_typeOut copies from it */
#define g_briefingSource GAME_VAR(u8 *, 0x9ef1ec)   /* the mission's briefing text block (crt_malloc'd, read from the mission file by mission_loadBriefing, the old one freed); briefing_typeOut types it out */
#define g_briefingShown GAME_VAR(int, 0x9ef1f4)   /* the characters of the briefing page typed out so far (briefing_typeOut adds one each time g_briefingClock passes 1.4, CR LF and double-byte characters at once); 0 on a new page or mission */
#define g_missionCount GAME_VAR(int, 0x9ef2c0)   /* the number of missions in the mission file (read by the mission file loader in files.c; 0 from menu_init); missionList_draw shows up to 8 */
#define g_missionPicked GAME_VAR(int, 0x9f16a4)   /* the mission picked in the mission list (index in g_missions): lit and its briefing line drawn by missionList_draw, loaded by mission_loadBriefing (missions_listKeys, room_clicks); 0 when the screen opens */
#define g_missionsWindowLeft GAME_VAR(int, 0x9f16a8)   /* the mission screen's window, left (10; with g_missionsWindowTop, g_missionsWindowRight 0x276, g_missionsWindowBottom 0x1cc): the mission list, its briefing and the skirmish settings all draw in it */
#define g_missionsWindowTop GAME_VAR(int, 0x9f16ac)   /* the mission screen's window, top (0x14; see g_missionsWindowLeft) */
#define g_briefingClock GAME_VAR(float, 0x9f16b8)   /* the briefing's typing clock: frame times added (briefing_typeOut); past 1.4 one more character shows and it goes back to 0; 0 from mission_loadBriefing */
#define g_skirmishRoundShown GAME_VAR(int, 0x9f63b4)   /* the skirmish screen's round on show (0 .. 14, at most g_progress; Left / Right step it) */
#define g_profileFrameAlpha GAME_VAR(float, 0x9f8f08)   /* the pilot select's pulsing frame: 40 at the start (load_stat_bars, profile_resetStatBars), then moved by g_profileFrameStep x frame time between 2 and 38; drawn with alpha 1 - it x k_0_025f (profile_drawPilotSelect) */
#define g_netQueueOnline GAME_VAR(int, 0xa0b388)   /* 1 while a DirectPlay connection is open (dplay_openConnection sets it, dplay_leaveSession clears it); netq_poll and netq_receive (netq_online) do nothing without it */
#define g_bitStream GAME_VAR(const u8 *, 0xa61708)   /* the PTX picture decoder's bit stream (ptx_startBitReader sets it with g_ptxBitPos 0); ptx_readBits reads bits from it, high bit first */
#define g_imp_wsprintfA GAME_VAR(void *, 0x4a92f0)   /* the import address of wsprintfA; net_formatChatLine calls through it to make a chat line "%s > %s" (name, text) */
#define g_componentDatPath GAME_VAR(const char *, 0x4b4414)   /* -> "Data/Component.dat" (0x4b4418): the component catalogue's path; actor_processFrame passes it to the catalogue load (0x473780) when the local player's actor passes from dying to dead */
#define g_insertCdMessage GAME_VAR(const char *, 0x4b4568)   /* -> "Please insert Axis CD in your CD-ROM drive!" (0x4b2528): scene_startSession's fatal message when cd_findDrive fails */
#define g_unusedKeyTable2Word0 GAME_VAR(int, 0x4d1fb0)   /* cleared by input_clearKeyTable2 (with g_unusedKeyTable2, a table never read); never read */
#define g_unusedKeyTable2Flags GAME_VAR(u16, 0x4d1fba)   /* set to 0x8000 by input_clearKeyTable2; never read */
#define g_unusedKeyTable2Word1 GAME_VAR(int, 0x4d1fbc)   /* cleared by input_clearKeyTable2; never read */
#define g_unusedKeyTable2Word2 GAME_VAR(int, 0x4d1fc0)   /* cleared by input_clearKeyTable2; never read */
#define g_mapEntry22On GAME_VAR(int, 0x4d95b8)   /* g_mapChoiceKeptTable[22].chosen: map 22 in the arena rotation; mapList_init turns it off (maps 22 .. 24 can't be chosen) */
#define g_mapEntry23On GAME_VAR(int, 0x4d95c0)   /* g_mapChoiceKeptTable[23].chosen: map 23 in the arena rotation; mapList_init turns it off */
#define g_mapEntry24On GAME_VAR(int, 0x4d95c8)   /* g_mapChoiceKeptTable[24].chosen: map 24 in the arena rotation; mapList_init turns it off */
#define g_arenaJoinPassword GAME_VAR(int, 0x4db520)   /* first dword of the typed password (8 bytes) to join a locked arena game (with g_arenaJoinPassword4): cleared by arena_editJoinPassword, the typed line copied in and checked against the game's by arena_gamesPageFrame */
#define g_arenaJoinPassword4 GAME_VAR(int, 0x4db524)   /* second dword of the typed join password (see g_arenaJoinPassword); cleared by arena_editJoinPassword */
#define g_newArenaPassword4 GAME_VAR(int, 0x4db552)   /* second dword of the create-arena form's password (see g_newArenaPassword); cleared by lobby_loadArenaSettings */
#define g_arenaListPlayers GAME_VAR(int, 0x4dba8c)   /* the players of all arenas merged into the list so far (each SessionEntry.players added by arena_mergeReceivedSessions; 0 from lobby_openConnection); nothing else reads it */
#define g_typedArenaAddress GAME_VAR(int, 0x4dbbd4)   /* the first word of g_typedArenaAddressText (char[24]) (arena_editAddress clears it as a dword with g_typedArenaAddress4) */
#define g_typedArenaAddress4 GAME_VAR(int, 0x4dbbd8)   /* second dword of g_typedArenaAddressText (see g_typedArenaAddress); cleared by arena_editAddress */
#define g_unusedArmcWord4 GAME_VAR(int, 0x4dbc00)   /* cleared by armc_open; never read */
#define g_chestMaxArmor GAME_VAR(int, 0x4dbc4c)   /* the chest part's maxArmor for the ARM CENTER's chest panel (armc_readPartPanels); section_chest shows it as MAX ARMOR with its skill bonus */
#define g_chestMaxShield GAME_VAR(int, 0x4dbc50)   /* the chest part's maxShield for the chest panel (armc_readPartPanels); section_chest shows it as MAX SHIELD with its skill and item bonus */
#define g_viewedPartAmmoType GAME_VAR(int, 0x4dc194)   /* g_viewedPart's PartInfo.ammoType (+0x44): BULLET TYPE 0 .. 3, -1 a special weapon */
#define g_viewedPartAmmoPerShot GAME_VAR(int, 0x4dc198)   /* g_viewedPart's PartInfo.ammoPerShot (+0x48); for a special weapon (ammoType -1) armc_viewedPartRecord overwrites it with the item's actorItems index (shown as message 745 + it) */
#define g_panel0Speed GAME_VAR(float, 0x4dc5a4)   /* g_panels[0].speed: ARM CENTER background panel 0's turning speed (0.15, armc_initPanels; armc_drawPanels turns panels 1 .. 5 only, so this one is never read) */
#define g_panel1Speed GAME_VAR(float, 0x4dc5fc)   /* g_panels[1].speed: ARM CENTER background panel 1's turning speed (-0.35, armc_initPanels); armc_drawPanels adds it x frame time to the panel's angle */
#define g_panel2Speed GAME_VAR(float, 0x4dc654)   /* g_panels[2].speed: background panel 2's turning speed (-1.5, armc_initPanels; see g_panel1Speed) */
#define g_panel3Speed GAME_VAR(float, 0x4dc6ac)   /* g_panels[3].speed: background panel 3's turning speed (1.5, armc_initPanels; see g_panel1Speed) */
#define g_panel4Speed GAME_VAR(float, 0x4dc704)   /* g_panels[4].speed: background panel 4's turning speed (-0.18, armc_initPanels; see g_panel1Speed) */
#define g_panel5Speed GAME_VAR(float, 0x4dc75c)   /* g_panels[5].speed: background panel 5's turning speed (0.18, armc_initPanels; see g_panel1Speed) */
#define g_unusedArmcWord1 GAME_VAR(int, 0x4dc864)   /* cleared by armc_openWeaponsPage; never read */
#define g_unusedArmcPoint0Y GAME_VAR(float, 0x4dca34)   /* 300.0: g_armcViewPoints[1] (point 0's y), set by armc_initCameraPoints; the whole table 0x4dca30 .. 0x4dca8c is never read */
#define g_unusedArmcPoint3Y GAME_VAR(float, 0x4dca64)   /* -500.0: g_armcViewPoints point 3's y, set by armc_initCameraPoints; never read (see g_unusedArmcPoint0Y) */
#define g_unusedArmcPoint5Y GAME_VAR(float, 0x4dca84)   /* 350.0: g_armcViewPoints point 5's y, set by armc_initCameraPoints; never read (see g_unusedArmcPoint0Y) */
#define g_mechDetectionRange GAME_VAR(float, 0x4dcaa0)   /* the mech's detection range for the ARM CENTER's whole-mech panel: sqrt(Actor.detectionRangeSq) x 0.01 (armc_readMechStats); section_mech shows it as "%.1f(m)" */
#define g_mechHackingLevel GAME_VAR(int, 0x4dcaa8)   /* the mech's hacking level (Actor.hackingLevel; armc_readMechStats); section_mech shows it as "%d(Lv)" */
#define g_unusedMechStat GAME_VAR(int, 0x4dcae8)   /* the booster type's thrust type, set by armc_readMechStats; never read (the panel uses g_boosterThrustType) */
#define g_mechMaxSpeedBwd GAME_VAR(float, 0x4dcb00)   /* the mech's top backward speed: -(g_mechNormalSpeed x Actor.runTop[1]) (km/h; armc_readMechStats); section_mech shows it last of MAX SPEED */
#define g_mechWeaponSlot0 GAME_VAR(int, 0x4dcb20)   /* g_armcSlotItems[2]: the item in weapon slot 0 (armc_items.c slot_item(0); -1 empty); g_armcSlotItems[0 .. 1] are the item slots 4 / 5 (g_itemSlot4 / 5) */
#define g_mechWeaponSlot1 GAME_VAR(int, 0x4dcb24)   /* g_armcSlotItems[3]: the item in weapon slot 1 (-1 empty) */
#define g_mechWeaponSlot2 GAME_VAR(int, 0x4dcb28)   /* g_armcSlotItems[4]: the item in weapon slot 2 (-1 empty) */
#define g_mechWeaponSlot3 GAME_VAR(int, 0x4dcb2c)   /* g_armcSlotItems[5]: the item in weapon slot 3 (-1 empty) */
#define g_unusedArmcWord3 GAME_VAR(int, 0x4dce38)   /* set to 5 by armc_open; never read */
#define g_boosterThrustType GAME_VAR(int, 0x4dce80)   /* the booster part's thrust type (g_boosterStats[0], an int; armc_readPartPanels); section_booster shows its name, MSG(651 + it) ("PLASMA THRUST ENGINE" ..) */
#define g_headHackingLevel GAME_VAR(int, 0x4dcf00)   /* the head part's hacking level (armc_readPartPanels); section_head shows it as HACKING LEVEL with the item bonus (g_itemBonusHacking) */
#define g_unusedArmcWord2 GAME_VAR(int, 0x4dcf14)   /* set to 1 by armc_openWeaponsPage; never read */
#define g_armcPanelDepth GAME_VAR(float, 0x4dcfc8)   /* z of the panels' origin point (g_armcCameraBox + 0x88, 0 from armc_initCameraBox; its y + 0x84 gives the panels' heights); armc_drawPanels glTranslate's z */
#define g_unusedStartupWord3 GAME_VAR(int, 0x4dd0b8)   /* cleared by app_startupLoad; never read */
#define g_unusedStartupWord2 GAME_VAR(u32, 0x4dd96c)   /* cleared by app_startupLoad; never read */
#define g_setupResolution GAME_VAR(int, 0x4ddba0)   /* g_graphicEdited[0]: the graphics tab's screen size being edited (index in g_resolutionNames, 0 .. 7); setup_drawGraphicPage shows its name */
#define g_freeCamLookY GAME_VAR(float, 0x4de348)   /* Y of the free camera's look-at point (between g_freeCamLookX and Z), used as its height: freeCam_keys puts the eye 10 above it, the look-at g_freeCamTilt above it, and stores it as the local slot camera's y; nothing in src writes it (stays 0) */
#define g_unusedFreeCamMoveWord GAME_VAR(u32, 0x4de6f0)   /* set to 30.0 by freeCam_mouseLook when a click starts a free-camera move; never read */
#define g_unusedPostMatchFlag GAME_VAR(int, 0x4de6f8)   /* set to 1 by game_postMatch and by freeCam_keys on Cancel (before game_returnToMainMenu); never read */
#define g_arenaPassword GAME_VAR(u32, 0x4ded46)   /* char[8] (GameSettings.password of g_arenaName): the arena's password, sent with it */
#define g_arenaPassword4 GAME_VAR(u32, 0x4ded4a)   /* bytes 4 .. 7 of the arena's password (g_arenaPassword, char[8]): cleared by arena_startFromLauncher before the file's password is copied in; never read on its own */
#define g_arenaLocked GAME_VAR(u8, 0x4ded4e)   /* GameSettings.locked: 1 a password game (the arena file's "secret") */
#define g_menuTunnelSpeed GAME_VAR(float, 0x4deda8)   /* the menu tunnel's stripe scroll speed (g_tunnelStripeScroll gains it x g_frameTime in tunnel_stepPulseScroll): set to 1.0 by menuState100_intro and menuState600_enterSetup, never anything else */
#define g_mouseSmooth GAME_VAR(int, 0x4df004)   /* SMOOTH MOUSE (axis.cfg smoothmouse; g_controls[0x41], edited as g_mouseSwitchesEdit[1]): 1 ON, default 0 (input_setDefaultBindings); only saved / loaded (cfg_writeKeyBindings / cfg_readKeyBindings), nothing else reads it */
#define g_unusedMenuReturnWord GAME_VAR(int, 0x4df8e0)   /* cleared by menuState100_intro, reset_menus and profile_logIn; never read */
#define g_arenaFilePassword GAME_VAR(u32, 0x5b193c)   /* the arena file's (axiswl.dat) "password" value, 8 bytes (arena_loadSettings: both dwords cleared, then strcpy); arena_startFromLauncher copies it into g_arenaPassword when the file's secret is 1 */
#define g_arenaFilePassword4 GAME_VAR(u32, 0x5b1940)   /* bytes 4 .. 7 of g_arenaFilePassword: cleared by arena_loadSettings before the password is copied in; never read on its own */
#define g_unusedStartupWord1 GAME_VAR(int, 0x76d474)   /* cleared by app_startupLoad; never read */
#define g_unusedRoomListWord GAME_VAR(int, 0x9087b0)   /* cleared by lobby_openConnection and gameList_refresh; never read */
#define g_freeCamYaw GAME_VAR(float, 0x90d1cc)   /* the match's free (watching) camera's heading in degrees, 0 .. 360: freeCam_mouseLook (screen 9999) turns it by the pointer, freeCam_stepLeft / freeCam_stepRight step sideways from it (+90), turn_update keeps its sine / cosine and puts it in the local slot's (g_localSlot) g_slotCams record */
#define g_unusedRoomWord GAME_VAR(int, 0x9dd1b0)   /* cleared by menu_returnToMainFromRoom and menuState800_enterGameRoom; never read */
#define g_unusedLoginWord GAME_VAR(int, 0x9dd32c)   /* cleared by newIdForm_openField and room_openLogin (with the g_typingAccount* flags); never read */
#define g_pilotRank GAME_VAR(int, 0x9dd5e0)   /* the pilot's rank (g_pilotStats[2]): account_takeRank sets it (with g_accountRank) from the rank reply's g_receivedRank, 0 when out of the first 1000 (g_outOfRank); no other use in src */
#define g_roomListPlayers GAME_VAR(int, 0x9dd840)   /* the players of all rooms merged into the game list so far (each SessionEntry.players added by room_mergeReceivedSessions; 0 from room_enterGameList / gameList_refresh); nothing else reads it */
#define g_unusedActive GAME_VAR(u32, 0x9dd864)   /* the last WM_ACTIVATEAPP wParam (1 activated, 0 deactivated), stored by game_wndProc; never read */
#define g_unusedInitWord GAME_VAR(int, 0x9dd8f8)   /* cleared by app_init; never read */
#define g_unusedReplayListWord1 GAME_VAR(int, 0x9dd944)   /* cleared by replayList_open; never read */
#define g_unusedReplayListWord2 GAME_VAR(int, 0x9eea88)   /* cleared by replayList_open; never read */
#define g_unusedMainMenuWord GAME_VAR(int, 0x9eeabc)   /* cleared by replaySelect_allOut (with g_replayWrap 1, g_replayRandomOrder 0); never read */
#define g_missionsDrawBackground GAME_VAR(int, 0x9eeba8)   /* 1: the mission list (screen 900) draws the menu background (menuState900_missions): set by menuState900_enterMissions and while its camera goes home (menu_camera2 mode 0), cleared once it arrives out (mode 1) */
#define g_unusedBriefingWord GAME_VAR(int, 0x9ef218)   /* cleared by mission_loadBriefing; never read */
#define g_misHeader1 GAME_VAR(int, 0x9ef2c4)   /* second word of axis.mis's 16-byte header (after g_missionCount; read by mission_loadAxisMis, cleared by missions_clear); never read */
#define g_misHeader2 GAME_VAR(int, 0x9ef2c8)   /* third word of axis.mis's header (see g_misHeader1); never read */
#define g_misHeader3 GAME_VAR(int, 0x9ef2cc)   /* fourth word of axis.mis's header (see g_misHeader1); never read */
#define g_unusedProfileCameraWord GAME_VAR(int, 0x9f6800)   /* set to -1 by profile_quitGame (with the other unused profile camera words); never read */
#define g_profileNoneAtEntry GAME_VAR(int, 0x9f8d70)   /* 1: the profile screen was entered with no profiles (menuState210_enter sets it when g_profileCount is 0, else clears it): profile_listPage then runs the new-name dialog (profile_typeNewName) while a dialog is up; otherwise it returns 0 */
#define g_netChatMessageKind GAME_VAR(int, 0x9f93c8)   /* +0 of the unsent chat-message template: net_resetState sets it to 0 then 1 (net_sendChat builds its own type-1 block); never read */
#define g_netChatMessageWord1 GAME_VAR(int, 0x9f93cc)   /* +4 of the unsent chat-message template (see g_netChatMessageKind): cleared by net_resetState; never read */
#define g_netChatMessageFrom GAME_VAR(int, 0x9f93d0)   /* +8 of the unsent chat-message template (net_resetState clears it; never read): in net_sendChat's layout the sender's player id */
#define g_netChatMessageText GAME_VAR(int, 0x9f93d4)   /* +0xc of the unsent chat-message template (net_sendChat's text offset): cleared by net_resetState; never read */
#define g_netSlotMessageKind GAME_VAR(int, 0x9f9420)   /* kind word of g_netSlotMsg (6; net_resetState), the 8-byte message the host sends a joining player (net_handleSystemMessage, system message 3) with its slot g_netClaimedSlot at +4 */
#define g_netPacketMessageKind GAME_VAR(int, 0x9f9428)   /* kind word of g_netSendPacket (7; net_resetState clears the 0x103 words then sets it), the game-packet message sent by net_sendPacketData */
#define g_receivedRank GAME_VAR(int, 0xa052d6)   /* +0x16 of the rank reply (request 29, g_rankReply): the pilot's rank; account_takeRank copies it into g_pilotRank / g_accountRank unless g_outOfRank */
#define g_unusedNetResetWord GAME_VAR(int, 0xa05328)   /* cleared by net_resetConnection; never read */
#define g_lobbyTcpPort GAME_VAR(int, 0xa055f4)   /* the lobby's TCP port, HKCU SelectServer TcpPort (reg_readServerSettings; e.g. 2020); net_resetConnection(100) takes its low 16 bits as g_serverPort; net_clearServerSettings clears it */
#define g_ladderPort GAME_VAR(int, 0xa05634)   /* the Ladder game server's TCP port, HKCU SelectServer LadderPort (reg_readServerSettings; e.g. 2040); net_resetConnection(101) takes its low 16 bits as g_serverPort; net_clearServerSettings clears it */
#define g_profileReplyResult GAME_VAR(int, 0xa05638)   /* the Ladder server's profile reply's result code: the first dword of g_profileReply (requests 14 login / 15 create ID; 0x21 ok, 0x1f no such ID, 0x20 wrong password, 0x22 ID in use, 0x1e ID taken) */
#define g_roomListRequest GAME_VAR(u32 *, 0xa0b334)   /* the 4-byte body of request 19 (list rooms; 01 00 18 00 = 0x180001, written through it by gameList_refresh), sent to the game server by net_send(19); allocated by net_resetConnection, freed by net_freeBuffers */
#define g_unusedSessionWord GAME_VAR(int, 0xa0b420)   /* cleared by dplay_openConnection; never read */
#define g_unusedDplayWord1 GAME_VAR(int, 0xa0b42c)   /* cleared by dplay_init; never read */
#define g_unusedDplayWord2 GAME_VAR(int, 0xa0b430)   /* cleared by dplay_init; never read */
#define g_unusedDplayWord3 GAME_VAR(int, 0xa0b434)   /* cleared by dplay_init; never read */
#define g_unusedDplayWord4 GAME_VAR(int, 0xa0b438)   /* cleared by dplay_init; never read */
#define g_unusedPingWord1 GAME_VAR(int, 0xa0bf14)   /* cleared by net_pingServer; never read */
#define g_unusedPingWord2 GAME_VAR(int, 0xa0bf18)   /* cleared by net_pingServer; never read */
#define g_vecOrigin GAME_VAR(float, 0xa0e7a8)   /* X of the origin point (0, 0, 0; set only by vec_initOrigin): copied as a start (scene_startSession cameraPos, map_loadPlayInfoFrom startPos) and used as a point in ObjectList_poseBones, actor_processFrame, particle_placeAtMatrix */
#define g_vecUnitZ GAME_VAR(float, 0xa0e7c8)   /* X of the unit Z axis (0, 0, 1; vec_initAxisZ): scene_startSession sets the camera direction to its negative, actor_processFrame copies it as a shot direction */
#define g_vecZero GAME_VAR(float, 0xa0e7e8)   /* X of the zero vector (0, 0, 0; vec_initZero): copied to clear velocities and moves (actor_setupFromParts, actor_processFrame, bullet_init, free_keys, space_collideBlock) and as a particle's colour (spawn_at) */
#define g_penInitialized GAME_VAR(int, 0xa106a8)   /* pen_init's duplicate guard: 1 would make a second pen_init only report 'pen duplicate initialization - penInit()' and return 0; never written (0 always), so the guard never fires */
#define g_packedRed GAME_VAR(u32, 0xa1f238)   /* packed RGBA red (bytes ff 00 00 ff; colour_initPackedRed): the debug grid's line colour (match_mechTestFrame, Scene.debugGrid) and the fill of a texture's colour mask when it has no _COLOR mask (colour_fill) */
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
#define g_arenaKeptCamX GAME_VAR(float, 0x4db840)   /* X of the arena lobby camera's eye where it last snapped to its menu point (menu_camera for arena_camera); armc_cameraStep puts the eye back there on returning to the lobby (g_armcFrom 2, state 400) */
#define g_arenaKeptCamY GAME_VAR(float, 0x4db844)   /* Y of the arena lobby camera's kept eye (see g_arenaKeptCamX) */
#define g_arenaKeptCamZ GAME_VAR(float, 0x4db848)   /* Z of the arena lobby camera's kept eye (see g_arenaKeptCamX) */
#define g_arenaKeptLookX GAME_VAR(float, 0x4dbab8)   /* X of the arena lobby camera's kept look point (g_menuCameraLook; see g_arenaKeptCamX) */
#define g_arenaKeptLookY GAME_VAR(float, 0x4dbabc)   /* Y of the arena lobby camera's kept look point (see g_arenaKeptLookX) */
#define g_arenaKeptLookZ GAME_VAR(float, 0x4dbac0)   /* Z of the arena lobby camera's kept look point (see g_arenaKeptLookX) */
#define g_chestWeightLimit GAME_VAR(float, 0x4dbc48)   /* the chest part's weight limit in tons (armc_readPartPanels): the chest panel's WEIGHT LIMIT, with skill 4's and g_itemBonusWeightLimit's bonus (section_chest) */
#define g_itemBonusCapacityPerLevel GAME_VAR(float, 0x4dbc70)   /* 0.3 when extra item 27 (BE-VOX EXPANSION MAGAZINE) is fitted, else 0 (armc_applyExtraItemBonuses): the arms panel's capacity bonus per level of each ammo capacity (section_arms) */
#define g_itemBonusDetectionRange GAME_VAR(float, 0x4dbc78)   /* 100 when extra item 32 (SE-S10 SENSOR ARRAY) is fitted, else 0 (armc_applyExtraItemBonuses): added to the head panel's DETECTION RANGE bonus in m (section_head) */
#define g_legsSpeedCorrection GAME_VAR(float, 0x4dc230)   /* the legs' speed correction x 100 (percent; g_legsStats[2], armc_readPartPanels): the legs panel's SPD CORRECTION line, and section_booster adds it as a percent of the booster's NORMAL SPEED bonus */
#define g_legsWeight GAME_VAR(float, 0x4dc240)   /* the legs part's weight in tons (armc_readPartPanels): the legs panel's WEIGHT (section_legs) and one of the sum in armc_drawWeightLine */
#define g_armsFcsLevel GAME_VAR(int, 0x4dc290)   /* the arms' FIRE CONTROL SYSTEM level (g_armsStats[0], copied from the arm part by armc_readPartPanels): shown as "%d(Lv)" by section_arms */
#define g_armsWeight GAME_VAR(float, 0x4dc2a4)   /* the arm part's weight in tons (armc_readPartPanels): the arms panel's WEIGHT (section_arms) and one of the sum in armc_drawWeightLine */
#define g_itemBonusTargetKeep GAME_VAR(float, 0x4dc88c)   /* 1 when extra item 32 (SE-S10 SENSOR ARRAY) is fitted, else 0 (armc_applyExtraItemBonuses): bonus factor on the head's TARGET KEEPING TIME (section_head: x g_headTargetKeepTime / 1000 sec) */
#define g_itemBonusRechargeTime GAME_VAR(float, 0x4dc894)   /* -0.1 when extra item 33 (TEP-34L BOOST GENERATOR) is fitted, else 0 (armc_applyExtraItemBonuses): bonus factor on the booster's RECHARGE TIME (section_booster) */
#define g_itemBonusLockOn GAME_VAR(float, 0x4dc898)   /* 0.5 when extra item 32 (SE-S10 SENSOR ARRAY) is fitted, else 0 (armc_applyExtraItemBonuses): bonus factor on the head's LOCK ON EFFICIENCY percent (section_head) */
#define g_mechMobility GAME_VAR(float, 0x4dcad0)   /* the mech's mobility (Actor.mobility, armc_readMechStats): the whole-mech panel's MOBILITY, "%.2f" (section_mech) */
#define g_mechBoostTime GAME_VAR(float, 0x4dcaec)   /* the mech's boost time in ms (Actor.boostTime x 1000): the first figure of BOOSTER ENERGY (message 680), shown / 1000 in seconds */
#define g_mechBoosterRecharge GAME_VAR(float, 0x4dcaf0)   /* the mech's booster recharge time in ms (Actor.rechargeTime x 1000, armc_readMechStats): the second figure of BOOSTER ENERGY (message 680), shown / 1000 in seconds (section_mech) */
#define g_mechNormalSpeed GAME_VAR(float, 0x4dcaf8)   /* the mech's normal speed in km/h (Actor.speed x 0.036, armc_readMechStats; g_mechSpeeds[0]): the panel's NORMAL SPEED and the base of the top speeds (runTop x it, g_mechMaxSpeedBwd) (section_mech) */
#define g_itemBonusShield GAME_VAR(float, 0x4dcc68)   /* 0.3 when extra item 35 (SH-4 FORCEFIELD BOOSTER) is fitted, else 0 (armc_applyExtraItemBonuses): added to skill 2's fraction for the chest's MAX SHIELD bonus (section_chest) */
#define g_hasItemCapacity GAME_VAR(int, 0x4dcb10)   /* extra item 27 (BE-VOX EXPANSION MAGAZINE) is fitted (armc_applyExtraItemBonuses; written only) */
#define g_hasItemEpak GAME_VAR(int, 0x4dcea8)   /* extra item 28 (BE-EOX E-PAK EXTRA MAGAZINE) is fitted (armc_applyExtraItemBonuses; written only) */
#define g_hasItem30mm GAME_VAR(int, 0x4dcc5c)   /* extra item 29 (BE-30X 30MM EXTRA MAGAZINE) is fitted (armc_applyExtraItemBonuses; written only) */
#define g_hasItem60mm GAME_VAR(int, 0x4dbc54)   /* extra item 30 (BE-60X 60MM EXTRA MAGAZINE) is fitted (armc_applyExtraItemBonuses; written only) */
#define g_hasItemMissile GAME_VAR(int, 0x4dbe44)   /* extra item 31 (BE-ROX EXTRA ROCKET CHAMBER) is fitted (armc_applyExtraItemBonuses; written only) */
#define g_hasItemSensor GAME_VAR(int, 0x4dc794)   /* extra item 32 (SE-S10 SENSOR ARRAY) is fitted (armc_applyExtraItemBonuses; written only) */
#define g_hasItemBooster GAME_VAR(int, 0x4dbd78)   /* extra item 33 (TEP-34L BOOST GENERATOR) is fitted (armc_applyExtraItemBonuses; read there) */
#define g_hasItemWeight GAME_VAR(int, 0x4dc774)   /* extra item 34 (BP-2001 GRAVITY CONTROLLER) is fitted (armc_applyExtraItemBonuses; read there) */
#define g_hasItemShield GAME_VAR(int, 0x4dcf30)   /* extra item 35 (SH-4 FORCEFIELD BOOSTER) is fitted (armc_applyExtraItemBonuses; read there) */
#define g_itemBonusActiveTime GAME_VAR(float, 0x4dcca0)   /* 0.5 when extra item 33 (TEP-34L BOOST GENERATOR) is fitted, else 0 (armc_applyExtraItemBonuses): bonus factor on the booster's ACTIVE TIME (section_booster) */
#define g_boosterActiveTime GAME_VAR(float, 0x4dce84)   /* the booster's active time in ms (times[0] x 1000, armc_readPartPanels; g_boosterStats[1]): the booster panel's ACTIVE TIME, shown / 1000 in seconds (section_booster) */
#define g_boosterRechargeTime GAME_VAR(float, 0x4dce88)   /* the booster's recharge time in ms (times[1] x 1000, armc_readPartPanels): the booster panel's RECHARGE TIME, shown / 1000 in seconds, with g_itemBonusRechargeTime's bonus (section_booster) */
#define g_boosterRechargeDelay GAME_VAR(float, 0x4dce8c)   /* the booster's recharge delay in ms (times[2] x 1000, armc_readPartPanels): the booster panel's DELAY FOR RECHARGE, shown / 1000 in seconds (section_booster) */
#define g_boosterNormalSpeed GAME_VAR(float, 0x4dce90)   /* the booster's normal speed in km/h (speeds[0] x 0.036, armc_readPartPanels; first of four speeds): the booster panel's NORMAL SPEED with skill 1's and g_legsSpeedCorrection's bonus (section_booster) */
#define g_boosterWeight GAME_VAR(float, 0x4dcea0)   /* the booster's weight in tons (armc_readPartPanels): the booster panel's WEIGHT "%.1f(Ton)" (section_booster) and one of the sum in armc_drawWeightLine */
#define g_itemBonusWeightLimit GAME_VAR(float, 0x4dceb0)   /* 0.2 when extra item 34 (BP-2001 GRAVITY CONTROLLER) is fitted, else 0 (armc_applyExtraItemBonuses): bonus fraction of g_chestWeightLimit in the chest's WEIGHT LIMIT (section_chest) */
#define g_itemBonusHacking GAME_VAR(float, 0x4dceb4)   /* 3 when extra item 32 (SE-S10 SENSOR ARRAY) is fitted, else 0 (armc_applyExtraItemBonuses): the head panel's HACKING LEVEL bonus (section_head, level_bonus) */
#define g_headDetectionRange GAME_VAR(float, 0x4dcef8)   /* the head's detection range in m (detectionRange x 0.01, armc_readPartPanels): the head panel's DETECTION RANGE, with skill 3's and g_itemBonusDetectionRange's bonus (section_head) */
#define g_headDetectionAngle GAME_VAR(float, 0x4dcefc)   /* the head's detection angle in degrees (detectionAngle in tenths x 0.1, armc_readPartPanels): the head panel's DETECTION ANGLE, with skill 3's bonus (section_head) */
#define g_headLockOnTime GAME_VAR(float, 0x4dcf04)   /* the head's lock-on time x 100 (armc_readPartPanels): section_head shows LOCK ON EFFICIENCY as 100 / it x 100 percent */
#define g_headTargetKeepTime GAME_VAR(float, 0x4dcf08)   /* the head's target keeping time in ms (targetKeepTime x 1000, armc_readPartPanels): the head panel's TARGET KEEPING TIME, shown / 1000 in seconds (section_head) */
#define g_headWeight GAME_VAR(float, 0x4dcf0c)   /* the head's weight in tons (armc_readPartPanels): the head panel's WEIGHT (section_head) and one of the sum in armc_drawWeightLine */
#define g_fpsSecondStart GAME_VAR(double, 0x4dd0a0)   /* timer_now time (seconds) the fps counter's current second began (menu_frame, only while g_showFps): reset to now once a second has passed */
#define g_lastFrameClock GAME_VAR(double, 0x4dd0c8)   /* timer_now time (seconds) of the last frame (menu_frame): g_frameRate = 1 / (now - it); cleared by menuState100_intro */
#define g_fpsFrameClock GAME_VAR(double, 0x4dd550)   /* timer_now time (seconds) of the last frame counted for the fps readout (menu_frame, only while g_showFps); never read */
#define g_frameRate GAME_VAR(double, 0x4dd558)   /* the frame rate, 1 / seconds since the last frame (menu_frame); g_frameTime = 60 / it (1 past 20); never read elsewhere */
#define g_fpsSecondSoFar GAME_VAR(double, 0x4dd978)   /* seconds since g_fpsSecondStart, as of this frame (menu_frame, only while g_showFps); menu_frame divides the frames counted by it for g_fps */
#define g_fps GAME_VAR(float, 0x4dd980)   /* the fps readout: frames counted / seconds, set once a second (menu_frame, only while g_showFps); no reader in src */
#define g_freeCamMoveStarted GAME_VAR(int, 0x4de340)   /* set to 1 by the first click in the free camera (freeCam_mouseLook) and never cleared: later clicks start nothing; read only there */
#define g_freeCamMoveEyeX GAME_VAR(float, 0x4de350)   /* X of an eye point 2000 along the free camera's heading from the slot's g_slotCams position (sin x 2000 + x), set on the first click (freeCam_mouseLook); never read */
#define g_freeCamMoveEyeY GAME_VAR(float, 0x4de354)   /* Y of the free camera's click eye point (the slot's g_slotCams y; see g_freeCamMoveEyeX); never read */
#define g_freeCamMoveEyeZ GAME_VAR(float, 0x4de358)   /* Z of the free camera's click eye point (cos x 2000 + the slot's z; see g_freeCamMoveEyeX); never read */
#define g_freeCamTurnSin GAME_VAR(float, 0x4de6c0)   /* sin of the free camera's turn (g_freeCamYaw, degrees), set by freeCam_mouseLook's turn_update; freeCam_keys moves the camera forward / back by it (with g_freeCamTurnCos) */
#define g_freeCamTilt GAME_VAR(float, 0x4de6c4)   /* the free camera's look height offset, -50 .. 50: freeCam_mouseLook moves it by the pointer's offset from y 240 x 0.1 x g_frameTime; freeCam_keys looks at g_freeCamLookY + it */
#define g_freeCamTurnCos GAME_VAR(float, 0x4de6c8)   /* cos of the free camera's turn (g_freeCamYaw, degrees), set by turn_update; freeCam_keys moves the camera by it and puts the eye at z - it x 50 (with g_freeCamTurnSin) */
#define g_freeCamMoveTargetX GAME_VAR(float, 0x4de6d0)   /* X of the local slot's g_slotCams position, copied on the free camera's first click (freeCam_mouseLook); never read */
#define g_freeCamMoveTargetY GAME_VAR(float, 0x4de6d4)   /* Y of the free camera's click target (see g_freeCamMoveTargetX); never read */
#define g_freeCamMoveTargetZ GAME_VAR(float, 0x4de6d8)   /* Z of the free camera's click target (see g_freeCamMoveTargetX); never read */
#define g_ladderPassword GAME_VAR(int, 0x9dd58e)   /* the Ladder password (12 bytes; g_ladderId + 0x1e): its first dword */
#define g_ladderPassword4 GAME_VAR(int, 0x9dd592)   /* the Ladder password's second dword (bytes 4 .. 7; see g_ladderPassword): cleared by menuState800_enterGameRoom */
#define g_ladderPassword8 GAME_VAR(int, 0x9dd596)   /* the Ladder password's third dword (bytes 8 .. 11; see g_ladderPassword): cleared by menuState800_enterGameRoom */
#define g_replaySelectDimR GAME_VAR(float, 0x9dda70)   /* R of the replay selection dialog's dim colour (0.3, 0.7, 0.7, 1; menuState300_enter): rows not hovered (replaySelect_drawDialog) */
#define g_replaySelectDimG GAME_VAR(float, 0x9dda74)   /* G of the replay selection dialog's dim colour (see g_replaySelectDimR) */
#define g_replaySelectDimB GAME_VAR(float, 0x9dda78)   /* B of the replay selection dialog's dim colour (see g_replaySelectDimR) */
#define g_replaySelectDimA GAME_VAR(float, 0x9dda7c)   /* A of the replay selection dialog's dim colour (see g_replaySelectDimR) */
#define g_replaySelectLitR GAME_VAR(float, 0x9eea98)   /* R of the replay selection dialog's bright colour (0, 1, 1, 1; menuState300_enter): its title and the hovered row (replaySelect_drawDialog) */
#define g_replaySelectLitG GAME_VAR(float, 0x9eea9c)   /* G of the replay selection dialog's bright colour (see g_replaySelectLitR) */
#define g_replaySelectLitB GAME_VAR(float, 0x9eeaa0)   /* B of the replay selection dialog's bright colour (see g_replaySelectLitR) */
#define g_replaySelectLitA GAME_VAR(float, 0x9eeaa4)   /* A of the replay selection dialog's bright colour (see g_replaySelectLitR) */
#define g_keptChatLine GAME_VAR(char, 0x9f63e4)   /* first byte of g_keptChat, the typed line kept by match_endTyping (0x400 bytes from g_inputLine): the match's chat_keys sends it (cheat code, macro or chat line); the esc menu uses it as a replay name (esc_name) */
#define g_rankReplyCode GAME_VAR(u8, 0xa052c0)   /* the first byte of the 0x22-byte reply to request 29 (my rank; g_rankReply): 1 when a reply came (net_recv sets g_rankReplyIn when it is non-zero); +1 g_outOfRank, +0x16 g_receivedRank */
#define g_arenaGameListLeft GAME_VAR(int, 0x4db8c8)   /* the arena lobby's game-list window: left (20, menuState400_enter); drawn by arena_gamesPageFrame / arena_drawGameList, its buttons and the join-password field (edit_fields ARENA_JOIN, arena_editAddress caret) placed from it */
#define g_arenaGameListTop GAME_VAR(int, 0x4db8cc)   /* the arena lobby's game-list window: top (20, menuState400_enter; see g_arenaGameListLeft) */
#define g_arenaGameListRight GAME_VAR(int, 0x4db8d0)   /* the arena lobby's game-list window: right (0x262 = 610, menuState400_enter; see g_arenaGameListLeft) */
#define g_arenaGameListBottom GAME_VAR(int, 0x4db8d4)   /* the arena lobby's game-list window: bottom (0x1c2 = 450, menuState400_enter; see g_arenaGameListLeft) */
#define g_armcPageLeft GAME_VAR(int, 0x4dcc90)   /* the ARM CENTER page's frame (10, 10, 0x276, 0x1d6 = the 640x480 screen less a margin; armc_open): left */
#define g_armcPageTop GAME_VAR(int, 0x4dcc94)   /* the ARM CENTER page's frame: top (10; armc_open; see g_armcPageLeft); also the y of the mode tabs and the weight line */
#define g_armcPageBottom GAME_VAR(int, 0x4dcc9c)   /* the ARM CENTER page's frame: bottom (0x1d6 = 470; armc_open; see g_armcPageLeft) */
#define g_setupSoundLeft GAME_VAR(int, 0x4ddad0)   /* the setup screen's SOUND page window: left (50, menuState600_enterSetup; first word of g_setupSoundRect); its drawing (setup_drawSoundPage), button rects and the volume slider's pointer x (track 0x90 in) are placed from it */
#define g_setupSoundRight GAME_VAR(int, 0x4ddad8)   /* the setup screen's SOUND page window: right (0x24e = 590, menuState600_enterSetup; see g_setupSoundLeft) */
#define g_setupGraphicTop GAME_VAR(int, 0x4dddd4)   /* the setup screen's GRAPHIC page window: top (30, menuState600_enterSetup; second word of g_setupGraphicRect) */
#define g_setupControlLeft GAME_VAR(int, 0x4dde80)   /* the setup screen's CONTROL page window: left (40, menuState600_enterSetup); its drawing (setup_drawControlsPage), rows, slider rects and the sensitivity bar's pointer x (slider_press) placed from it */
#define g_setupControlTop GAME_VAR(int, 0x4dde84)   /* the setup screen's CONTROL page window: top (30, menuState600_enterSetup; see g_setupControlLeft) */
#define g_setupControlRight GAME_VAR(int, 0x4dde88)   /* the setup screen's CONTROL page window: right (0x24e = 590, menuState600_enterSetup; see g_setupControlLeft) */
#define g_sensitivitySlider GAME_VAR(int, 0x4de1c8)   /* the mouse sensitivity being edited on the controls tab (g_controlsEdit[0x42], 0 .. 100, default 50): copied from g_controls by setup_selectControlTab, stepped / set by slider_press, drawn as the bar (setup_drawControlsPage), copied back on OK */
#define g_ladderExp GAME_VAR(int, 0x4de722)   /* the Ladder record's exp (g_ladderName +0x22): the match score added by ladder_addMatchScores, the room level from it (match_setup, level_fromPoints); cut to 2 a kill when above 150 a kill (ladder_checkAndSendRecord); sent in the record packet */
#define g_ladderPower GAME_VAR(float, 0x4de726)   /* the Ladder record's power (float, g_ladderName +0x26): kill rate x 0.01 x exp (power_from_rate in ladder_checkAndSendRecord); copied from g_pilotPower (login_takeAccountRecord, newId_register); sent in the record packet */
#define g_ladderGames GAME_VAR(int, 0x4de72a)   /* the Ladder record's rounds played (g_ladderName +0x2a): +1 at a Ladder match's setup (match_setup) and at each next round / restart (main_loop); 0 for a new ID (newId_register); sent in the record packet */
#define g_ladderKills GAME_VAR(int, 0x4de72e)   /* the Ladder record's kills (g_ladderName +0x2e): the local player's new kills added by ladder_addMatchScores; 0 for a new ID; used for the kill rate and sent in the record packet (ladder_checkAndSendRecord) */
#define g_ladderDeaths GAME_VAR(int, 0x4de732)   /* the Ladder record's deaths (g_ladderName +0x32): the local player's new deaths added by ladder_addMatchScores; 0 for a new ID; used for the kill rate and sent in the record packet (ladder_checkAndSendRecord) */
#define g_menuFramePhase GAME_VAR(int, 0x4de740)   /* the dialog-frame opening animation's phase (menu_drawFrameOpening): 1 lines grow from the left / bottom, 2 those fade while lines grow from the right / top, 3 the panel grows, then back to 1 (g_frameOpening cleared); set to 1 by menuState210_enter */
#define g_gameListRow GAME_VAR(int, 0x4df818)   /* the selected game's row among the nine shown (0 .. 8; g_gameListTop + it = g_pickedGame), shared by the arena lobby's list and the game room's (Ladder) list */
#define g_gameListTop GAME_VAR(int, 0x680bb0)   /* the first game shown in the game list (index into g_sessionList; nine rows from it; + g_gameListRow = g_pickedGame): scrolled by the list keys (arenaGames_keys, game_lists), 0 when a list is (re)loaded; shared by the arena lobby and game room lists */
#define g_menuFrameCounter GAME_VAR(int, 0x76d428)   /* the dialog-frame opening animation's frame count within its phase (menu_drawFrameOpening; see g_menuFramePhase): +1 a frame, the lines' length / fade = count x g_frameTime x a speed; back to 0 when count x 64 x frame time passes 640; 0 in menuState210_enter */
#define g_clockNow GAME_VAR(double, 0x9db980)   /* the timer's time in seconds (double; first of g_timerClocks): advanced by timer_now from the performance counter (g_timerTick a count), cleared by timer_init; also stored by menu_frame each frame */
#define g_fieldStep GAME_VAR(int, 0x9dc428)   /* the focus step a key asks of the login / new-ID / account forms: 20 on to the next field, 10 back, 0 none. Set by the hidden edit control every text field types into (editField_editProc: Enter 20; Tab in the game room 20, with Shift 10) when it closes a field, and also by roomLogin_keys / newIdForm_keys from the DirectInput Tab (+Shift) and toggle keys while no field is open; consumed and cleared by roomLogin_update, newIdForm_update, account_page */
#define g_roomLoginLeft GAME_VAR(int, 0x9dd358)   /* the game room's Ladder login dialog: left (0x32 = 50, menuState800_enterGameRoom); roomLogin_draw, its layout, buttons and the ID / password fields (edit_fields ROOM_LOGIN; also newIdForm_keys' login_field positions) placed from it */
#define g_roomLoginTop GAME_VAR(int, 0x9dd35c)   /* the game room's Ladder login dialog: top (0x6e = 110, menuState800_enterGameRoom; see g_roomLoginLeft) */
#define g_roomLoginBottom GAME_VAR(int, 0x9dd364)   /* the game room's Ladder login dialog: bottom (0x172 = 370, menuState800_enterGameRoom; see g_roomLoginLeft); its buttons sit 0x30 above it */
#define g_accountPanelLeft GAME_VAR(int, 0x9dd368)   /* the game room's account page window: left (0x3c = 60, menuState800_enterGameRoom); drawn by account_page / account_drawPanel, its fields (edit_fields ACCOUNT) and buttons placed from it */
#define g_accountPanelTop GAME_VAR(int, 0x9dd36c)   /* the game room's account page window: top (0x1e = 30, menuState800_enterGameRoom; see g_accountPanelLeft) */
#define g_accountPanelRight GAME_VAR(int, 0x9dd370)   /* the game room's account page window: right (0x244 = 580, menuState800_enterGameRoom; see g_accountPanelLeft) */
#define g_accountPanelBottom GAME_VAR(int, 0x9dd374)   /* the game room's account page window: bottom (0x1c2 = 450, menuState800_enterGameRoom; see g_accountPanelLeft) */
#define g_roomGameListLeft GAME_VAR(int, 0x9dd4a8)   /* the game room's (Ladder) game-list window: left (0x14 = 20, menuState800_enterGameRoom); drawn by gameList_pageFrame / gameList_draw, its buttons and the join-password field (edit_fields ROOM_JOIN) placed from it */
#define g_roomGameListTop GAME_VAR(int, 0x9dd4ac)   /* the game room's game-list window: top (0x28 = 40, menuState800_enterGameRoom; see g_roomGameListLeft) */
#define g_roomGameListRight GAME_VAR(int, 0x9dd4b0)   /* the game room's game-list window: right (0x26c = 620, menuState800_enterGameRoom; see g_roomGameListLeft) */
#define g_roomGameListBottom GAME_VAR(int, 0x9dd4b4)   /* the game room's game-list window: bottom (0x1b8 = 440, menuState800_enterGameRoom; see g_roomGameListLeft) */
#define g_newIdFormLeft GAME_VAR(int, 0x9dd6e8)   /* the new-ID form's (CREATE NEW ID) window: left (0x1e = 30; room_openNewIdForm sets 30, 50, 610, 430); newIdForm_draw, its fields (newIdForm_openField, rows 0x30 apart) and buttons placed from it */
#define g_newIdFormRight GAME_VAR(int, 0x9dd6f0)   /* the new-ID form's window: right (0x262 = 610, room_openNewIdForm); read only as the frame's x1 in newIdForm_draw */
#define g_newIdFormBottom GAME_VAR(int, 0x9dd6f4)   /* the new-ID form's window: bottom (0x1ae = 430, room_openNewIdForm); its two buttons placed 0x2c / 0x30 above it (newIdForm_draw, newIdForm_keys) */
#define g_replaySelectLeft GAME_VAR(int, 0x9dd908)   /* the main menu's replay selection dialog: left (0x50 = 80, set by replayList_open); mainmenu_drawReplaySelect, replaySelect_drawNames and its button rects placed from it */
#define g_replaySelectTop GAME_VAR(int, 0x9dd90c)   /* the replay selection dialog: top (0x28 = 40, replayList_open; see g_replaySelectLeft) */
#define g_replaySelectRight GAME_VAR(int, 0x9dd910)   /* the replay selection dialog: right (0x230 = 560, replayList_open; see g_replaySelectLeft) */
#define g_replaySelectBottom GAME_VAR(int, 0x9dd914)   /* the replay selection dialog: bottom (0x1b8 = 440, replayList_open; see g_replaySelectLeft) */
#define g_menuHintStep GAME_VAR(float, 0x9dd948)   /* the AUTOPLAY-F1 hint's fade step per time unit: +0.05 rising, -0.05 falling (mainmenu_drawMenu; 0.05 again on any panel hover and at menuState300_enter) */
#define g_menuIdleTime GAME_VAR(float, 0x9dda80)   /* time in 1/60 s with no main-menu panel under the pointer (mainmenu_drawMenu adds g_frameTime; 0 on a hover / when the hint finishes); the AUTOPLAY-F1 hint shows past 120 */
#define g_menuHintFade GAME_VAR(float, 0x9eea8c)   /* the AUTOPLAY-F1 hint's fade (mainmenu_drawMenu): + g_menuHintStep x g_frameTime; past 3 set to 1 and falling, below 0 set to 0 and rising (idle restarts); drawn with alpha min(1, this) */
#define g_mainMenuDepth GAME_VAR(float, 0x9eea90)   /* the main menu tunnel's camera depth: -300 at menuState300_enter, flown down to -550 while g_tunnelFlyingIn (mainmenu_drawMenu), passed to menu_tunnel */
#define g_missionsWindowRight GAME_VAR(int, 0x9f16b0)   /* the mission screen's (900) window: right (0x276); left / top g_missionsWindowLeft / g_missionsWindowTop */
#define g_missionsWindowBottom GAME_VAR(int, 0x9f16b4)   /* the mission screen's (900) window: bottom (0x1cc) */
#define g_skirmishRectLeft GAME_VAR(int, 0x9f6308)   /* the skirmish screen's window: left (0x28 = 40, menuState500_enterSkirmish; first word of g_skirmishRect / g_skirmishBox); skirmish.c's drawing and the button rects placed from it */
#define g_skirmishRectTop GAME_VAR(int, 0x9f630c)   /* the skirmish screen's window: top (10, menuState500_enterSkirmish; see g_skirmishRectLeft) */
#define g_pilotSelectBottom GAME_VAR(int, 0x9f682c)   /* the pilot-select (CHARACTER SELECT) dialog: bottom (0x1c2 = 450, menuState210_enter; see g_pilotSelectLeft); its buttons sit 0x40 above it */
#define g_pilotSelectRight GAME_VAR(int, 0x9f6830)   /* the pilot-select dialog: right (0x262 = 610, menuState210_enter; see g_pilotSelectLeft) */
#define g_profileListTop GAME_VAR(int, 0x9f8c4c)   /* the first profile shown in the pilot screen's list (13 rows; + g_profileListRow = g_profileChosen): set by menuState210_enter, profile_create, profile_deleteChosen and the list keys; saved in / read from axisuser.dat's header (profile_readHeader) */
#define g_pilotSelectTop GAME_VAR(int, 0x9f8c50)   /* the pilot-select dialog: top (0x14 = 20, menuState210_enter; see g_pilotSelectLeft); the portraits are laid out 86 apart from it */
#define g_pilotSelectLeft GAME_VAR(int, 0x9f8c54)   /* the pilot-select (CHARACTER SELECT) dialog: left (0x1e = 30, menuState210_enter); pilotSelect_page draws its frame, the portrait grid (3 a row, 86 apart) and buttons placed from it */
#define g_profileListRow GAME_VAR(int, 0x9f8c5c)   /* the cursor's row in the pilot screen's profile list (0 .. 12; g_profileListTop + it = g_profileChosen): set by menuState210_enter, profile_create, profile_deleteChosen and the list keys; saved in / read from axisuser.dat's header */
#define g_profileChosen GAME_VAR(int, 0x9f8d74)   /* the profile chosen in the list (index into g_profiles; = g_profileListTop + g_profileListRow) */
#define g_profilePageLeft GAME_VAR(int, 0x9f8e48)   /* the pilot screen's profile page window: left (0x3c = 60, menuState210_enter); profile_listPage's frame, the names (profileList_drawNames), profile_drawManagementWindow / profile_drawChosenPilot and the button rects placed from it */
#define g_profilePageTop GAME_VAR(int, 0x9f8e4c)   /* the pilot screen's profile page window: top (0x3c = 60, menuState210_enter; see g_profilePageLeft) */
#define g_profilePageRight GAME_VAR(int, 0x9f8ea0)   /* the pilot screen's profile page window: right (0x244 = 580, menuState210_enter; see g_profilePageLeft) */
#define g_profilePageBottom GAME_VAR(int, 0x9f8ea4)   /* the pilot screen's profile page window: bottom (0x1a4 = 420, menuState210_enter; see g_profilePageLeft) */
#define g_newNameDialogTop GAME_VAR(int, 0x9f8ea8)   /* the pilot screen's new-name dialog (REGISTRY PROFILE) and message window: top (0x96 = 150, menuState210_enter; see g_newNameDialogLeft); the name's caret 0x38 below it */
#define g_newNameDialogLeft GAME_VAR(int, 0x9f8eac)   /* the pilot screen's new-name dialog (REGISTRY PROFILE) and profile message window: left (0x78 = 120, menuState210_enter); profile_newNamePage, the button rects (newNameDialog_layout) and the name caret (profile_typeNewName) placed from it */
#define g_newNameDialogRight GAME_VAR(int, 0x9f8f20)   /* the new-name dialog / message window: right (0x208 = 520, menuState210_enter; see g_newNameDialogLeft) */
#define g_newNameDialogBottom GAME_VAR(int, 0x9f8f24)   /* the new-name dialog / message window: bottom (0x118 = 280, menuState210_enter; see g_newNameDialogLeft) */
#define g_ptxHuffSet GAME_VAR(int, 0xaa2e94)   /* the PTX decoder's Huffman table set in use: 0 luma, 1 chroma (planes 1 and 2; set per plane in ptx_read); selects the DC / AC code tables in ptx_readDcDiff / ptx_readAcSymbol; 0 from ptx_initTables */
#define g_dikNumpad4 GAME_VAR(int, 0x4deb58)   /* 0x4b (DIK_NUMPAD4; input_initDikCodes): camera preset 4 (spectating, match_combatInput: cameraSlot 4; replay_frame: cameraMode 4) */
#define g_dikNumpad3 GAME_VAR(int, 0x4deb5c)   /* 0x51 (DIK_NUMPAD3; input_initDikCodes): camera preset 3 (spectating, match_combatInput: cameraSlot 3; replay_frame: cameraMode 3) */
#define g_dikNumpad6 GAME_VAR(int, 0x4deb60)   /* 0x4d (DIK_NUMPAD6; input_initDikCodes): camera preset 6 (spectating, match_combatInput: cameraSlot 6; replay_frame: cameraMode 6) */
#define g_dikNumpad5 GAME_VAR(int, 0x4deb64)   /* 0x4c (DIK_NUMPAD5; input_initDikCodes): camera preset 5 (spectating, match_combatInput: cameraSlot 5; replay_frame: cameraMode 5) */
#define g_dikNumpad8 GAME_VAR(int, 0x4deb68)   /* 0x48 (DIK_NUMPAD8; input_initDikCodes): camera preset 8 (spectating, match_combatInput: cameraSlot 8; replay_frame: cameraMode 8) */
#define g_dikNumpad7 GAME_VAR(int, 0x4deb6c)   /* 0x47 (DIK_NUMPAD7; input_initDikCodes): camera preset 7 (spectating, match_combatInput: cameraSlot 7; replay_frame: cameraMode 7) */
#define g_dikNumpad9 GAME_VAR(int, 0x4deb70)   /* 0x49 (DIK_NUMPAD9; input_initDikCodes): camera preset 9 (spectating, match_combatInput: cameraSlot 9; replay_frame: cameraMode 9) */
#define g_dikNumpad0 GAME_VAR(int, 0x4deb78)   /* 0x52 (DIK_NUMPAD0; input_initDikCodes): camera preset 0 / 10 (spectating, match_combatInput: cameraSlot 0; replay_frame: cameraMode 0) */
#define g_dikNumpadDot GAME_VAR(int, 0x4dec88)   /* 0x53 (DIK_DECIMAL, the numpad dot; input_initDikCodes); not read anywhere else */
#define g_dikNumpad2 GAME_VAR(int, 0x4dec8c)   /* 0x50 (DIK_NUMPAD2; input_initDikCodes): camera preset 2 (spectating, match_combatInput: cameraSlot 2; replay_frame: cameraMode 2) */
#define g_dikNumpad1 GAME_VAR(int, 0x4dec90)   /* 0x4f (DIK_NUMPAD1; input_initDikCodes): camera preset 1 (spectating, match_combatInput: cameraSlot 1; replay_frame: cameraMode 1) */
#define g_dikNumLock GAME_VAR(int, 0x4dec94)   /* 0x45 (DIK_NUMLOCK; input_initDikCodes); not read anywhere else */
#define g_dikInsert GAME_VAR(int, 0x4deda0)   /* 0xd2 (DIK_INSERT; input_initDikCodes); not read anywhere else (g_dikInsert_2 holds the same code) */
#define g_dikPeriod GAME_VAR(int, 0x4deda4)   /* 0x34 (DIK_PERIOD; input_initDikCodes); not read anywhere else */
#define g_dikLWin GAME_VAR(int, 0x4df038)   /* 0xdb (DIK_LWIN; input_initDikCodes); not read anywhere else */
#define g_dikInsert_2 GAME_VAR(int, 0x4df04c)   /* 0xd2 (DIK_INSERT, a second copy; input_initDikCodes); not read anywhere else */
#define g_dikF12 GAME_VAR(int, 0x4df8d4)   /* 0x58 (DIK_F12; input_initDikCodes); not read anywhere else */
#define g_dikF10 GAME_VAR(int, 0x4df8dc)   /* 0x44 (DIK_F10; input_initDikCodes): the default key of binding 29 (g_controls +0xe8; input_setDefaultBindings and setup's defaults); that binding is not read by match code */
#define g_dikLBracket GAME_VAR(int, 0x4df8fc)   /* 0x1a (DIK_LBRACKET; input_initDikCodes); not read anywhere else */
#define g_dik0 GAME_VAR(int, 0x4e0460)   /* 0xb (DIK_0; input_initDikCodes): follow key 10 while spectating (match_combatInput: followKey 9) */
#define g_dik5 GAME_VAR(int, 0x4e0c78)   /* 0x6 (DIK_5; input_initDikCodes): default key of binding 13 (R SHOULDER weapon, g_controls +0x68); follow key 5 (15 with left shift) while spectating (match_combatInput); ARM CENTER weapons page item slot 4 (armc_weaponsPageKeys) */
#define g_dik6 GAME_VAR(int, 0x4e0c7c)   /* 0x7 (DIK_6; input_initDikCodes): default key of binding 14 (L SHOULDER weapon, g_controls +0x70); follow key 6 (16 with left shift) while spectating (match_combatInput); ARM CENTER weapons page item slot 5 (armc_weaponsPageKeys) */
#define g_dik7 GAME_VAR(int, 0x4e0c80)   /* 0x8 (DIK_7; input_initDikCodes): follow key 7 while spectating (match_combatInput: followKey 6) */
#define g_dik8 GAME_VAR(int, 0x4e0c84)   /* 0x9 (DIK_8; input_initDikCodes): follow key 8 while spectating (match_combatInput: followKey 7) */
#define g_dik9 GAME_VAR(int, 0x4e0c88)   /* 0xa (DIK_9; input_initDikCodes): follow key 9 while spectating (match_combatInput: followKey 8) */
#define g_dikNumpadSlash GAME_VAR(int, 0x4e0ca0)   /* 0xb5 (DIK_DIVIDE, the numpad slash; input_initDikCodes); not read anywhere else */
#define g_dikB GAME_VAR(int, 0x4e0cd8)   /* 0x30 (DIK_B; input_initDikCodes): default key of binding 24 (g_controls +0xc0; input_setDefaultBindings); ARM CENTER slot key 4 (booster) on the parts and colour pages (armc_partsPageKeys, armc_colourPageKeys) */
#define g_dikE GAME_VAR(int, 0x4e10e4)   /* 0x12 (DIK_E; input_initDikCodes): default key of binding 12, next weapon (g_controls +0x60; match_combatInput nextWeaponPressed); ARM CENTER slot key 1 (chest) on the parts and colour pages (armc_partsPageKeys, armc_colourPageKeys) */
#define g_dikF GAME_VAR(int, 0x4e14e8)   /* 0x21 (DIK_F; input_initDikCodes): default key of binding 9, down (g_controls +0x48, holdDown; input_setDefaultBindings) */
#define g_dikH GAME_VAR(int, 0x4e14f0)   /* 0x23 (DIK_H; input_initDikCodes): ARM CENTER slot key 0 (head) on the parts and colour pages (armc_partsPageKeys, armc_colourPageKeys) */
#define g_dikK GAME_VAR(int, 0x4e1500)   /* 0x25 (DIK_K; input_initDikCodes): the main menu's key for choice 0, SKIRMISH PLAY (mainmenu_processKeys, menu_choice) */
#define g_dikQ GAME_VAR(int, 0x4e1518)   /* 0x10 (DIK_Q; input_initDikCodes): default key of binding 11, previous weapon (g_controls +0x58; match_combatInput prevWeaponPressed) */
#define g_dikU GAME_VAR(int, 0x4e1530)   /* 0x16 (DIK_U; input_initDikCodes): picks the controls tab's page 3, MOUSE (setup_controlTabKeys, g_bindPage) */
#define g_dikV GAME_VAR(int, 0x4e1534)   /* 0x2f (DIK_V; input_initDikCodes): default key of binding 30, the camera mode cycle (g_controls +0xf0; match_combatInput respawnCameraMode) */
#define g_dikY GAME_VAR(int, 0x4e1540)   /* 0x15 (DIK_Y; input_initDikCodes); not read anywhere else */
#define g_dikZ GAME_VAR(int, 0x4e1544)   /* 0x2c (DIK_Z; input_initDikCodes); not read anywhere else (g_dikZ_2 holds the same code) */
#define g_dikEnd GAME_VAR(int, 0x5ae9c0)   /* 0xcf (DIK_END; input_initDikCodes); not read anywhere else */
#define g_dikSlash GAME_VAR(int, 0x5b1974)   /* 0x35 (DIK_SLASH; input_initDikCodes); not read anywhere else */
#define g_dikPageDown GAME_VAR(int, 0x5b1980)   /* 0xd1 (DIK_NEXT, page down; input_initDikCodes); not read anywhere else */
#define g_dikPageUp_2 GAME_VAR(int, 0x5b1db0)   /* 0xc9 (DIK_PRIOR, page up, a second copy; input_initDikCodes); not read anywhere else */
#define g_dikNumpadPlus GAME_VAR(int, 0x67ef08)   /* 0x4e (DIK_ADD, the numpad plus; input_initDikCodes); not read anywhere else */
#define g_dikScrollLock GAME_VAR(int, 0x67ef10)   /* 0x46 (DIK_SCROLL; input_initDikCodes); not read anywhere else */
#define g_dikApps GAME_VAR(int, 0x67ef28)   /* 0xdd (DIK_APPS; input_initDikCodes); not read anywhere else */
#define g_dikEnter_2 GAME_VAR(int, 0x67ef2c)   /* 0x1c: DIK_RETURN, a second copy (set by input_initDikCodes; never read) */
#define g_dikPrintScreen GAME_VAR(int, 0x67fb40)   /* 0xb7: DIK_SYSRQ, the Print Screen key (set by input_initDikCodes; never read) */
#define g_dikComma GAME_VAR(int, 0x680368)   /* 0x33: DIK_COMMA (set by input_initDikCodes; never read) */
#define g_dikNumpadEnter GAME_VAR(int, 0x6803a4)   /* 0x9c: DIK_NUMPADENTER (set by input_initDikCodes; never read) */
#define g_dikMouse3 GAME_VAR(int, 0x680bbc)   /* 0xfc: the third mouse button, the game's own code after 0xfa / 0xfb for buttons 1 / 2 (set by input_initDikCodes; never read) */
#define g_dikApostrophe GAME_VAR(int, 0x74de20)   /* 0x28: DIK_APOSTROPHE (set by input_initDikCodes; never read) */
#define g_dikEnd_2 GAME_VAR(int, 0x76d32c)   /* 0xcf: DIK_END, a second copy (set by input_initDikCodes; never read) */
#define g_dikGrave GAME_VAR(int, 0x76d334)   /* 0x29: DIK_GRAVE, the grave accent key (set by input_initDikCodes; never read) */
#define g_dikRWin GAME_VAR(int, 0x76d338)   /* 0xdc: DIK_RWIN, the right Windows key (set by input_initDikCodes; never read) */
#define g_dikPageDown_2 GAME_VAR(int, 0x76d370)   /* 0xd1: DIK_NEXT, Page Down, a second copy (set by input_initDikCodes; never read) */
#define g_dikMinus GAME_VAR(int, 0x76d374)   /* 0x0c: DIK_MINUS (set by input_initDikCodes; never read) */
#define g_dikBack GAME_VAR(int, 0x76d378)   /* 0x0e: DIK_BACK, Backspace (set by input_initDikCodes; never read) */
#define g_dikRBracket GAME_VAR(int, 0x76d380)   /* 0x1b: DIK_RBRACKET (set by input_initDikCodes; never read) */
#define g_dikNumpadMinus GAME_VAR(int, 0x76d3f4)   /* 0x4a: DIK_SUBTRACT, numpad minus (set by input_initDikCodes; never read) */
#define g_dikCapsLock GAME_VAR(int, 0x76d420)   /* 0x3a: DIK_CAPITAL, Caps Lock (set by input_initDikCodes; never read) */
#define g_dikSemicolon GAME_VAR(int, 0x76d470)   /* 0x27: DIK_SEMICOLON (set by input_initDikCodes; never read) */
#define g_dikDelete_2 GAME_VAR(int, 0x907b28)   /* 0xd3: DIK_DELETE, a second copy (set by input_initDikCodes; never read) */
#define g_dikHome GAME_VAR(int, 0x90d1c0)   /* 0xc7: DIK_HOME (set by input_initDikCodes; never read) */
#define g_dikF3 GAME_VAR(int, 0x9da448)   /* 0x3d: DIK_F3 (set by input_initDikCodes; never read) */
#define g_dikF2 GAME_VAR(int, 0x9da44c)   /* 0x3c: DIK_F2 (set by input_initDikCodes; never read) */
#define g_dikF5 GAME_VAR(int, 0x9da450)   /* 0x3f: DIK_F5 (input_initDikCodes); the default key of the control at g_controls + 0xd8 (k_defaultBindings, also into g_controlsEdit) */
#define g_dikF4 GAME_VAR(int, 0x9da454)   /* 0x3e: DIK_F4 (input_initDikCodes); the default key of the control at g_controls + 0xd0 (k_defaultBindings, also into g_controlsEdit) */
#define g_dikF7 GAME_VAR(int, 0x9da458)   /* 0x41: DIK_F7 (set by input_initDikCodes; never read) */
#define g_dikF6 GAME_VAR(int, 0x9da474)   /* 0x40: DIK_F6 (set by input_initDikCodes; never read) */
#define g_dikF9 GAME_VAR(int, 0x9da478)   /* 0x43: DIK_F9 (set by input_initDikCodes; never read) */
#define g_dikF8 GAME_VAR(int, 0x9da47c)   /* 0x42: DIK_F8 (set by input_initDikCodes; never read) */
#define g_dikEquals GAME_VAR(int, 0x9dae18)   /* 0x0d: DIK_EQUALS (set by input_initDikCodes; never read) */
#define g_dikHome_2 GAME_VAR(int, 0x9dae6c)   /* 0xc7: DIK_HOME, a second copy (set by input_initDikCodes; never read) */
#define g_dikBackslash GAME_VAR(int, 0x9dae78)   /* 0x2b: DIK_BACKSLASH (set by input_initDikCodes; never read) */
#define g_dikNumpadStar GAME_VAR(int, 0x9db0a8)   /* 0x37: DIK_MULTIPLY, numpad star (set by input_initDikCodes; never read) */
/* moved from game.h and the files' own defines (tools/promote_locals.py) */
#define g_mouseTaken GAME_VAR(int, 0x4ad17c)   /* 1 in the exe's data and never written: input_reacquireMouse always takes the mouse again (0 would let it go) */
#define g_pulse GAME_VAR(float, 0x4b06fc)   /* the bands' colour pulse, 0.05 .. 0.95 */
#define g_pulseStep GAME_VAR(float, 0x4b0700)   /* g_pulse's step per time unit (x g_frameTime; menu_tunnel.c pulse): -0.01 once it reaches 0.95, 0.01 once at 0.05 */
#define g_flareSizeB GAME_VAR(float, 0x4b0704)   /* a breathing half-size shared by two screens: in the menu tunnel flare 3's (10 .. 48; menuState300_enter / armc_exit set 10); in the ARM CENTER part panel 3's half width (200 .. 600; armc_initPanels sets 200; armc_drawPanels) */
#define g_flareSizeA GAME_VAR(float, 0x4b0708)   /* a breathing half-size shared by two screens: in the menu tunnel flare 2's (menuState300_enter / armc_exit set 48); in the ARM CENTER panel 2's half width (200 .. 600; g_panelSize2, armc_drawPanels) */
#define g_flareStepB GAME_VAR(float, 0x4b070c)   /* g_flareSizeB's step: menu tunnel flare 3 (breathe) -0.2 / +0.2 x g_frameTime at 48 / 10; ARM CENTER panel 3's rate (g_panelRate3: -2 / +2 x g_frameTime at 600 / 200); set 0.2 by menuState300_enter / armc_exit */
#define g_flareStepA GAME_VAR(float, 0x4b0710)   /* g_flareSizeA's step, the same for tunnel flare 2 / ARM CENTER panel 2 (g_panelRate2; see g_flareStepB); set -0.2 by menuState300_enter / armc_exit */
#define g_frameTime GAME_VAR(float, 0x4b071c)   /* the last frame's time in 1/60 s (menu_frame: 60 / the frame rate, 1 when above 20); screen cameras clamp it again before use (1 above their limit: arena_camera, armc_cameraStep, setup_camera, room_camera, skirmish_camera, missions camera, menu_titleEmblemTransition (above 3); menuTunnel_advance sets 2 above 10) */
#define g_directInput GAME_VAR(void *, 0x4d1e98)   /* the IDirectInput object (input_createDirectInput: DirectInputCreateA, version 0x700); makes the keyboard and mouse devices (input_initKeyboard / input_createMouse); released by input_releaseAll */
#define g_keyboard GAME_VAR(void *, 0x4d1fa0)   /* the DirectInput keyboard device (input_initKeyboard: GUID_SysKeyboard, non-exclusive, foreground); read into g_keyState (read_keys); released and NULLed by input_releaseKeyboard, re-acquired by input_reacquireKeyboard */
#define g_mouse GAME_VAR(void *, 0x4d1fa4)   /* the DirectInput mouse device (input_createMouse: GUID_SysMouse, exclusive, foreground); read into g_mouseState (input_readMouse); input_reacquireMouse acquires / unacquires it; released and NULLed by input_releaseMouse */
#define g_keyboardReady GAME_VAR(int, 0x4d1fa8)   /* 1 once the DirectInput keyboard is made and acquired (input_initKeyboard); 0 when released (input_releaseKeyboard: while a text field takes typing through Windows, and at shutdown); while 0 the key reads give 0 */
#define g_mouseReady GAME_VAR(int, 0x4d1fac)   /* 1 once the DirectInput mouse device is made and set up (input_createMouse, which returns at once while it is set); 0 when released (input_releaseMouse) */
#define g_textCharWidth GAME_VAR(int, 0x4d23d8)   /* the Korean passes' advance for a single-byte character other than a space (text_pass); set per call by text_begin: 8 (draw8 / centred8), 13 (draw16 / centredLines16), 26 (draw32), 18 (centredLines32), 6 (draw5 / centred5) */
#define g_mapTop GAME_VAR(int, 0x4d7350)   /* the first map shown in the arena's map rotation list (up to 10 rows from it; map_list.c, scrolled by its arrows) */
#define g_mapListKept GAME_VAR(int, 0x4d94fc)   /* 1 once a list has been kept (mapList_ok); never read */
#define g_lobbySubState GAME_VAR(int, 0x4db51c)   /* the lobby's page: 5 the top menu, 0 player setup, 1 join, 2 create */
#define g_armcAngle GAME_VAR(float, 0x4dbc04)   /* the ARM CENTER preview's turn in tenths of a degree, 0 .. 3600: + frame time x 8 while g_armcSpin, back to 0 at 3600; drawn as x 0.1 degrees (armc_misc.c preview, armc_drawPreview3D) */
#define g_armcPartSlot GAME_VAR(int, 0x4dbc6c)   /* the parts page's slot in view: 0 head, 1 chest, 2 arm, 3 leg, 4 booster, 5 the whole mech (VIEW ALL, key A; set at entry) */
#define g_weaponCount GAME_VAR(int, 0x4dc244)   /* the weapon list's length (g_weaponListTable, first entry -1 = none; armc_buildPartLists: 1 + the unlocked weapons); g_armcCursor wraps at it for slots 0 .. 3 (armc_showCursorItem, armc_pickSlot, ARM CENTER keys) */
#define g_armcColourSlot GAME_VAR(int, 0x4dc4b0)   /* the colour slot being edited */
#define g_extraCount GAME_VAR(int, 0x4dc778)   /* the extra-item list's length (g_extraListTable, first entry -1 = none; armc_buildPartLists); g_armcCursor wraps at it for item slots 4 / 5 (armc_showCursorItem, armc_pickSlot) */
#define g_armcMode GAME_VAR(int, 0x4dc798)   /* the ARM CENTER's page: 1 the parts, 2 the weapons, 3 the colours; 0 once its camera is home on leaving (armc_cameraStep); 4 is dispatched (armc_processInput, armc_mouse) but never set */
#define g_armcSessionDue GAME_VAR(int, 0x4dc86c)   /* the "please wait" box was shown: the session is made next */
#define g_armcHideInterface GAME_VAR(int, 0x4dd078)   /* Ctrl+Alt+M: the screen without its interface */
#define g_menuVolume GAME_VAR(int, 0x4dd984)   /* DirectSound volume of the menu sounds: (v * 5 - 500) * 4 of the setting */
#define g_menuRepeatClock GAME_VAR(float, 0x4dda44)   /* the menus' hold-to-repeat clock in 1/60 s: menu_frame adds g_frameTime (back to 100 past 1e6); a held scroll arrow / key acts again once it reaches the caller's threshold (5 in the map, arena, game and replay lists, 1 for the setup sliders and bindings) and sets it to 0; screen entries and most menu clicks / keys clear it */
#define g_setupTab GAME_VAR(int, 0x4ddac8)   /* 0 sound, 1 graphics, 2 controls, 0x29a the top page */
#define g_emblemAlphaStep GAME_VAR(float, 0x4de1d8)   /* its change per time unit: 0.02 from app_startupLoad, then +-0.018 (menu_titleEmblemTransition) */
#define g_emblemAlpha GAME_VAR(float, 0x4de1e0)   /* the pulsing layer's alpha: 0.1 at start-up (loading.c), then pulsing between 0.2 and 0.9 (menu_titleEmblemTransition) */
#define g_logoFade GAME_VAR(float, 0x4de1e8)   /* the title logo (iftex/axis_title) fading OUT: 0 .. 1 by 0.1 a time unit; drawn with alpha 1 - this until it reaches 1 */
#define g_unusedLogoFade GAME_VAR(float, 0x4de1ec)   /* only written (menu_titleEmblemTransition: a second fade running twice as fast from 0.2) */
#define g_timerTick GAME_VAR(double, 0x4ded58)   /* seconds per (shifted) tick */
#define g_mouseX GAME_VAR(int, 0x4ded68)   /* the pointer: in the menus 640 x 480 units (input_updateMouse adds the mouse's movement and keeps it to 0..630 / 0..474, or the patch's wide clamp); in a match (screen 9999) not clamped and put back each frame to the window's centre in pixels (gfx_getWidth() / 2: match_combatInput, match_setupOrStartRound, and the replay viewer's replay_frame) */
#define g_mouseY GAME_VAR(int, 0x4ded6c)   /* the pointer's Y (see g_mouseX): menus 0 .. 474 (input_updateMouse); 230 at start-up and the intro, 240 on WM_CREATE; in a match put back to gfx_getHeight() / 2 each frame; the hit tests read it */
#define g_titleClosing GAME_VAR(int, 0x4df01c)   /* 1: a key (title_keyDismiss) or click (title_clickDismiss) dismissed the title: its layers fade and spread over g_titleCloseFrames, the profile screen (210) after 19 frames; 0 from menuState100_intro */
#define g_timerFrequency GAME_VAR(u64, 0x4df030)   /* QueryPerformanceFrequency's result */
#define g_cursorFrame GAME_VAR(int, 0x4df03c)   /* the mouse pointer's animation frame, 0..14 */
#define g_exitCode GAME_VAR(int, 0x4df048)   /* how the game closes (app_closeWindow's code; WM_DESTROY acts on it): 0 quit, 1 start AxisGL.exe again (graphics changed), 2 start axispatch.exe "nstower", 3 start DServer.exe "1", 99 the ending movie */
#define g_dialogPending GAME_VAR(int, 0x4df900)   /* a message box is up: it takes the keys */
#define g_cursorFrameTime GAME_VAR(float, 0x4df910)   /* frame time collected towards the next frame (5 units) */
#define g_titleCloseFrames GAME_VAR(int, 0x4e0458)   /* frames since the title was dismissed (g_titleClosing; from 0): indexes g_titleSpread and fades both layers by 0.02 a frame; the profile screen at 19 */
#define g_screenH GAME_VAR(int, 0x4e045c)   /* the screen height in pixels: 480 (app_init), then by g_videoMode (app_screenSizeForMode: 480 .. 2160, or the desktop's); the window, display mode, glWindow_init, 2D projection (menu_2d.c) and g_viewAspect use it */
#define g_tunnelStripeScroll GAME_VAR(float, 0x4e14fc)   /* the menu tunnel's stripes' scroll (every screen's tunnel: menu_tunnel / setup_drawTunnel; tunnel_stepPulseScroll adds g_menuTunnelSpeed per time unit): runs 0 .. 200, then 0 */
#define g_cursorTexture GAME_VAR(int, 0x4e152c)   /* the pointer's sprite sheet (texture id) */
#define g_inputLineHidden GAME_VAR(int, 0x4e1868)   /* 1: the input line shows as stars (password fields); 0 for names */
#define g_ringBandTexture GAME_VAR(int, 0x4e186c)   /* \"iftex/cylinder\" (menu_loadTextures): the background tunnel rings' outer bands (menu_drawBackground3D, menu_tunnel.c outer_bands; not bound with SIMPLE MENU) */
#define g_viewAspect GAME_VAR(float, 0x4e1870)   /* gluPerspective's aspect: the screen's width / height, but narrowed and eased back while the menu cameras fly (set to 0.1, or lowered by 0.07 x the frame time while above 0, so it can end slightly below 0: menu_camera*, armc_cameraStep, the room and skirmish cameras), and lowered by 0.05 x the frame time, set to 0.01 once below it, while the replay zooms in (menu_frame) */
#define g_screenW GAME_VAR(int, 0x5b1998)   /* the screen width in pixels: 640 (app_init), then by g_videoMode (app_screenSizeForMode: 640 .. 3840, or the desktop's); see g_screenH */
#define g_lastScreen GAME_VAR(int, 0x67ef0c)   /* the screen whose set-up ran last (menu_enterState: menuStateN_enter / match_enter, then g_lastScreen = g_screen); menu_frame / app_frameByScreen run that set-up when g_screen differs. Screens that set themselves up store it too (200, 300, 500, 700, 800, 900) */
#define g_timerShift GAME_VAR(int, 0x67ef1c)   /* how far the counter is shifted right */
#define g_nextScreen GAME_VAR(int, 0x67ef20)   /* the front-end screen to go to: taken into g_screen when the tunnel's move ends (menuTunnel_advance); 300 the main menu */
#define g_pointerGlideX GAME_VAR(int, 0x67ef34)   /* where the mouse pointer glides to (menu units) while g_pointerGliding: the focused button or field of a two-button question, or of the login / new-ID dialog */
#define g_pointerGlideY GAME_VAR(int, 0x67fb38)   /* Y the pointer glides to (see g_pointerGlideX): a two-button question's button (dialog y + 0x4a; profile ask / dialog keys) or a room dialog field (login_field / highlight_choice); read by glide_page and menuState800_gameRoom */
#define g_menuCameraMove GAME_VAR(int, 0x680370)   /* the menu camera's move along the tunnel (menu_tunnel.c): 0 still, 1 / 3 moving in / out a ring, 2 / 4 the view swinging up first; the menus ignore keys while not 0 */
#define g_viewAngle GAME_VAR(float, 0x68038c)   /* the 3D view's vertical angle (degrees) */
#define g_textFieldOpen GAME_VAR(int, 0x68039c)   /* 1: a text field has the keys (typing a name, password or chat line; edit_fields.c); the other input is off */
#define g_repeatDown GAME_VAR(float, 0x680bb4)   /* time units until a held down key steps again (key_repeat: 4 after a step, less g_frameTime, 0 when released): replaySelect_keys, missions_listKeys, profileList_keys; cleared by menuState900_enterMissions */
#define g_pointerGlideTime GAME_VAR(float, 0x680bc0)   /* the pointer glide's time left (20 time units, less g_frameTime each frame); below 0 the glide stops (g_pointerGliding 0) */
#define g_dialogFocus GAME_VAR(int, 0x74de1c)   /* the item with the keyboard focus in a dialog: in the profile questions (pages 3 and 5) 0 the left button, 1 the right; in the Ladder login 0 .. 3 (name, password, buttons; roomLogin_keys); in the new-ID form the field 0 .. 2 (newIdForm_keys) */
#define g_fontHanJungJong GAME_VAR(int, 0x76d360)   /* Hangul vowels and finals */
#define g_cageTexture GAME_VAR(int, 0x76d36c)   /* texture id of "iftex/cylinder_menu" (menu_loadTextures); bound for the tunnel rings' grey cages (menu_tunnel.c cages, not in g_simpleMenu) */
#define g_repeatUp GAME_VAR(float, 0x76d37c)   /* time units until a held Up key steps again (key_repeat: 4 after a step, less g_frameTime, 0 when released; g_repeatDown the Down key's): replaySelect_keys, missions_listKeys, profileList_keys; cleared by menuState900_enterMissions */
#define g_screen GAME_VAR(int, 0x76d3e8)   /* the front end's screen: 100 intro, 200 title, 210 profile, 300 main menu, 400 lobby,
                                                         500 skirmish, 600 setup, 700 armour, 800 game room, 900 the mission list (axis.mis; never
                                                         entered), 9999 in a match */
#define g_logoTexture GAME_VAR(int, 0x76d3f0)   /* texture id of "iftex/axis_title" (app_startupLoad); the start-up screen's logo (menu_states.c draw_logo) and the title's (menu_titleEmblemTransition: 160, 60 .. 480, 316, fading by g_logoFade) */
#define g_pickedGame GAME_VAR(int, 0x76d41c)   /* the game picked in the arena lobby's / game room's game list: an index into g_sessionList (g_gameListTop + g_gameListRow); joined with arena_joinSession / room_joinListed, its password and lock checked */
#define g_pointerGliding GAME_VAR(int, 0x76d42c)   /* 1: the mouse pointer glides to (g_pointerGlideX, g_pointerGlideY) until g_pointerGlideTime runs out (menuState800_gameRoom, the profile question pages) */
#define g_fontAscii GAME_VAR(int, 0x76d448)   /* ASCII, 5- and 8-unit fonts */
#define g_scene GAME_VAR(Scene *, 0x9087b4)   /* the scene object (Console_ctor'ed once by app_startupLoad, 0 only if its allocation failed; kept for the whole run: the ARM CENTER's preview and stats use it outside matches too) */
#define g_glContext GAME_VAR(void *, 0x9087b8)   /* the game window's GL context (game_wndProc WM_CREATE: wglCreateContext(g_windowDC), made current); set NULL on WM_CLOSE; nothing else reads it */
#define g_frameOpening GAME_VAR(int, 0x90d1c4)   /* 1: a panel's frame is opening (menu_drawFrameOpening's three-phase animation, which clears this when it ends): meanwhile the screen draws only that frame and takes no keys or clicks. Set when a menu camera arrives (menu_camera / menu_camera2) and when a profile dialog opens */
#define g_editCaretX GAME_VAR(int, 0x9da3d8)   /* where the line being typed is drawn (menu units) */
#define g_editCaretY GAME_VAR(int, 0x9da3dc)   /* Y where the line being typed is drawn (menu units; see g_editCaretX): menu_drawInputLine (app_frame) and the Windows edit control's place (y + 0x21; editField_createEdit); set by each text field's start */
#define g_menuKeyGuard GAME_VAR(float, 0x9da434)   /* a key delay (time units): 5 when a screen or text field opens (10 or 20 for some); app_frame takes g_frameTime off; the menu keys (menu_processKeys) and the hidden edit control's Enter (editField_editProc) wait until it is not above 0 */
#define g_simpleMenu GAME_VAR(int, 0x9da494)   /* SIMPLE MENU (the graphics setting, from g_cfgSimpleMenu; the setup page's button 6 flips it): the menus' 3D background (the tunnel's bands, flares and cages) is not drawn, only moved on */
#define g_unusedHighlightAlpha GAME_VAR(float, 0x9da4a4)   /* only written (0.4 when a dialog's focus moves, 0.2 by profile_askDelete / profile_askLogOut) */
#define g_fontAsciiLarge GAME_VAR(int, 0x9dad90)   /* ASCII, 16- and 32-unit fonts */
#define g_mapIndex GAME_VAR(int, 0x9dad94)   /* the map being played or loaded: an index into g_mapNames (the skirmish round, the arena / room game's map, the rotation's current map; -1 none). Saved in replays */
#define g_fontHanCho GAME_VAR(int, 0x9dae1c)   /* font textures (ids): Hangul initial consonants */
#define g_language GAME_VAR(int, 0x9dae74)   /* the language: 1 Korean (system language 0x412 / 0x812, WinMain), 2 English. It picks msgkor/msgeng.dat, profkor/profeng.dat, the message boxes, the ARM CENTER text widths and the message lines (msg_players.c KOREAN / ENGLISH) */
#define g_tunnelPulse GAME_VAR(float, 0x9db978)   /* bounces 0 .. 100 */
#define g_timerLastCount GAME_VAR(u32, 0x9dbf08)   /* timer_now's last counter reading (shifted by g_timerShift) */
#define g_inputLineLength GAME_VAR(int, 0x9dbf10)   /* characters in the input line (g_inputLine): set from the field's text when a text field opens (edit_fields.c, arena_editAddress), 0 when it is emptied or closed (menu_clearInputBuffer, menu_closeInputLine); menu_drawInputLine puts the caret at x + it x 8 */
#define g_skirmishInfo16Mode GAME_VAR(int, 0x9dbfa4)   /* where a 16th skirmish record's gameMode would be (g_skirmishInfo + 16 x 0x5c + 0x4c), past the 15 skirmish.dat fills: make_rotation's solo rotation reads it as the next mode (Scene.nextMode); an unnamed gap otherwise */
#define g_hEditField GAME_VAR(void *, 0x9dd888)   /* the hidden EDIT control typing goes to */
#define g_missionTop GAME_VAR(int, 0x9f16bc)   /* the first mission shown in the (unused) mission list: up to 8 rows from it (missionList_draw), g_missionPicked = it + g_missionRow; 0 from menuState900_enterMissions */
#define g_skirmishNewPartsNotice GAME_VAR(int, 0x9f62e0)   /* 1: the skirmish screen shows the "YOU'VE GOT NEW PARTS AND WEAPONS" notice (skirmish_frameNewPartsNotice), raised when a new round is reached (menuState500_enter); a click (newPartsNotice_clickClose) or Esc / Enter (newPartsNotice_keys) closes it */
#define g_skirmishState GAME_VAR(int, 0x9f62f8)   /* the skirmish screen's camera state (menu_camera2): 1 flying in (menuState500_enter), 2 there: the screen is up (keys, no tunnel), 0 flying home (skirmish_leave); 2 again once home */
#define g_skirmishLeft GAME_VAR(int, 0x9f6300)   /* -1 once the skirmish camera is home again (menu_camera2's third flag: the screen was left for the main menu); 0 from menuState500_enter. While it is set the screen draws nothing of its own and takes no keys or clicks */
#define g_skirmishShowBackground GAME_VAR(int, 0x9f63b8)   /* 1: the skirmish screen draws the menu background (menuState500_skirmish -> menu_drawBackground); 1 from menuState500_enter, 0 once the camera arrives, 1 again while it flies home (menu_camera2) */
#define g_profileReveal GAME_VAR(int, 0x9f6828)   /* CHARACTER SELECT: the chosen pilot's portrait cell grown by twice this (menu units) a side, 0 .. 8 (one more each time g_profileRevealClock passes 1); 0 when the pilot cursor moves (pilotSelect_keys, pilotSelect_clicks) or the selection resets (pilotSelect_reset) */
#define g_logOutDialogX GAME_VAR(int, 0x9f6834)   /* left of page 5's (log-out question) dialog frame, 120 (menuState210_enter); with g_logOutDialogY / Right / Bottom; logOutDialog_layout places its buttons from it */
#define g_profileQuitting GAME_VAR(int, 0x9f6838)   /* 1: the log-out question was answered yes (profile_quitGame, from profile_logOutKeys / profile_logOutClicks): the profile screen's next frame quits the game (menuState210_frame -> app_quitGame) and the pointer is no longer drawn (menu_frame); 0 from menuState210_enter */
#define g_logOutDialogY GAME_VAR(int, 0x9f683c)   /* top of page 5's (log-out question) dialog frame, 150 (menuState210_enter; see g_logOutDialogX); also places the buttons and the pointer's glide target */
#define g_pilotSelectCursor GAME_VAR(int, 0x9f8d30)   /* page 6, CHARACTER SELECT: the pilot under the cursor, 0..8 row by row */
#define g_statBarsStale GAME_VAR(int, 0x9f8d68)   /* 1: the pilot shown changed, the stat bars to be loaded again */
#define g_unusedProfileCameraSpeed GAME_VAR(float, 0x9f8e50)   /* only written: 0.1 by profile_quitGame, 0.05 when a key or click comes while g_profileQuitting (profile_screenClicks, profile_screenKeys) */
#define g_profileQuitSkip GAME_VAR(int, 0x9f8e54)   /* 0 from profile_quitGame; 5 once a key or click came while g_profileQuitting (profile_screenClicks and profile_screenKeys answer only while it is not 5). The game quits on the next frame anyway */
#define g_profileRevealClock GAME_VAR(float, 0x9f8ee4)   /* time units since g_profileReveal last stepped (+ g_frameTime while it is below 8; past 1 it goes back to 0 and g_profileReveal steps; profile_drawPilotSelect); 0 when the pilot cursor moves (pilotSelect_keys, pilotSelect_clicks) or the selection resets (pilotSelect_reset) */
#define g_deleteDialogY GAME_VAR(int, 0x9f8f0c)   /* top of page 3's (delete question) dialog frame, 150 (menuState210_enter; see g_deleteDialogX); also places the buttons and the pointer's glide target */
#define g_profilePage GAME_VAR(int, 0x9f8f10)   /* the profile screen's page: 1 the list, 2 a new name typed (profile_typeNewName), 3 the delete question (profile_askDelete), 4 logging in (profile_logIn; no keys), 5 the log-out question (profile_askLogOut), 6 CHARACTER SELECT (the pilot grid) */
#define g_unusedProfileCameraZoom GAME_VAR(float, 0x9f8f14)   /* only written: 80 by profile_quitGame, 100 by profile_screenClicks / profile_screenKeys */
#define g_deleteDialogX GAME_VAR(int, 0x9f8f1c)   /* left of page 3's (delete question) dialog frame, 120 (menuState210_enter); with g_deleteDialogY / Right / Bottom; deleteDialog_layout places its buttons from it (profile_askDelete, profile_drawDeleteQuestion, profile_deletePage) */
#define g_unusedProfileCameraTime GAME_VAR(int, 0x9f8f30)   /* only written (0) by profile_quitGame, profile_screenClicks, profile_screenKeys */
#define g_profileMessage GAME_VAR(int, 0x9f8f34)   /* page 2: 1 while the 'name already taken' message window shows (set when profile_nameExists finds the typed name; drawn by profile_drawMessageWindow); a click, OK or right click clears it and typing starts again (profile_typeNewName) */
#define g_playerCount GAME_VAR(int, 0x9fd950)   /* the session's player count from a DPSYS_CREATEPLAYERORGROUP message (msg[3]; net_handleSystemMessage, TCP/IP host only); sent in the arena / room info packet (one less when a player left) */
#define g_textures GAME_VAR(TextureManager *, 0xa0e010)   /* the game's texture manager (= &g_textureManager, set by app_startupLoad): textures looked up by name (tex_getIdByName) and bound as banks[id / 512], id % 512 (tex_bind) everywhere */
#define g_music GAME_VAR(void *, 0xa0e670)   /* the playing music: DirectShow's IAMMultiMediaStream (music_play: CoCreateInstance(CLSID_AMMultiMediaStream), OpenFile, run); NULL when none (music_stop releases it) */
#define g_desktopH GAME_VAR(int, 0xa0e814)   /* the desktop's height before the first mode switch (glWindow_setDisplayModeBy: GetDeviceCaps VERTRES); put back by glWindow_restoreDisplayMode (see g_desktopW) */
#define g_desktopBits GAME_VAR(int, 0xa0e91c)   /* the desktop's bits per pixel before the first mode switch (glWindow_setDisplayModeBy: GetDeviceCaps BITSPIXEL); put back by glWindow_restoreDisplayMode */
#define g_desktopW GAME_VAR(int, 0xa0e92c)   /* the desktop's width before the first mode switch (glWindow_setDisplayModeBy: GetDeviceCaps HORZRES); put back by glWindow_restoreDisplayMode (with g_desktopH, g_desktopBits) */
#define g_glWindowMade GAME_VAR(int, 0xa0e930)   /* glWindow_init made its own window (only on its path without a given window; set once, a second call refused). The game always passes its main window (menu_enterState: glWindow_init(.., g_mainWindow, g_windowDC)), so it stays 0 */
#define g_glWindow GAME_VAR(void *, 0xa0e934)   /* glWindow_init's window: its own pop-up when given none, else the window passed in (the game's main window); returned by glWindow_init, not read elsewhere */
#define g_glWindowDc GAME_VAR(void *, 0xa0e938)   /* the GL window's device context: the DC given to glWindow_init (g_windowDC), or the own window's (glWindow_wndProc WM_CREATE); gfx_swapBuffers swaps it, glWindow_setDisplayModeBy queries it */
#define g_glWindowContext GAME_VAR(void *, 0xa0e93c)   /* the GL context of glWindow's own window (glWindow_wndProc: wglCreateContext on WM_CREATE, deleted on WM_DESTROY); never made in the game, which passes its own window (its context is g_glContext) */
#define g_modeChanged GAME_VAR(int, 0xa0e940)   /* glWindow's display mode was switched (glWindow_setDisplayModeBy; the desktop's mode, g_desktopW / H / Bits, kept before it; put back and cleared by glWindow_restoreDisplayMode). Only on glWindow's full-screen path, which the game never takes (its own switch is app_setDisplayMode, g_displayModeChanged) */
#define g_loadTexture GAME_VAR(int, 0xa0e980)   /* the backdrop's texture id */
#define g_loadFade GAME_VAR(float, 0xa0e984)   /* the fade's time, 0 .. 1 s */
#define g_loadScroll GAME_VAR(float, 0xa0ea88)   /* the loading screen's time (TimeSync_frameTime summed since loading_drawScreen(-1)): the backdrop cylinder's texture v runs from it to it + 10, so it scrolls; not a progress fraction */
#define g_loadGame GAME_VAR(Scene *, 0xa0ea8c)   /* the game object being loaded (game_processLoadingMode's this): loading_draw reads its sessionMode (+8), awaitingHostRound, gameMode */
#define g_white GAME_VAR(u32, 0xa1f23c)   /* the packed opaque white colour ff ff ff ff as one word (the same four bytes as objects.h g_packedWhite, colour_initPackedWhite): point and mark colours (shapes_skeletons.c, frame_loops.c) */
#define g_unlit GAME_VAR(u32, 0xa1f278)   /* the colour of a vertex out of a light's reach */
#define g_ptxClamp GAME_VAR(const u8 *, 0xa1f300)   /* the PTX decoder's clamp: points 0x100 into g_ptxClampTable (ptx_initClampTable), so g_ptxClamp[v] is v limited to 0 .. 255 for v from -0x100 (ptx_toRgb / ptx_toRgba; ptx_inverseDct from +0x80) */
#define g_netqCursor GAME_VAR(int, 0xb116e0)   /* the player netq_receive looks at first (turns 0..15) */
#define g_packetsSkipped GAME_VAR(int, 0xb116e4)   /* packets that came out of turn (netq_receive: a number other than the one due, the expected number moved past it). Any count lights the match's resend warning (match_frame clears it); 0x80 or more: 'network unstable' and the match is left (match_frame), or the loading stops (game_processLoadingMode) */
#define g_roomLoginRight GAME_VAR(int, 0x9dd360)   /* right edge of the Ladder login dialog, 590 (menuState800_enterGameRoom; roomLogin_draw's frame; see g_roomLoginLeft) */
#define g_roomSlideEase GAME_VAR(float, 0x9dd560)   /* the game room's tunnel-slide value (room_slideMenu / menu_slide: eased toward k_panelSlideTarget while g_roomPanelsSliding; each step, (250 - it) x g_frameTime x 0.1, also pushes g_roomTunnelDepth back); 0 on entering (menuState800_enterGameRoom). Twin of g_lobbySlideEase */
#define g_missionRow GAME_VAR(int, 0x9f1058)   /* the mission list's cursor row on screen, 0 .. 7 (missions_cursorUp / Down, missions_clickRow); g_missionPicked = g_missionTop + row; cleared by menuState900_enterMissions */
#define g_deleteDialogBottom GAME_VAR(int, 0x9f8f28)   /* bottom of page 3's (delete question) dialog frame, 270 (menuState210_enter; see g_deleteDialogX) */
#define g_deleteDialogRight GAME_VAR(int, 0x9f8f2c)   /* right edge of page 3's (delete question) dialog frame, 520 (menuState210_enter; see g_deleteDialogX) */
#define g_logOutDialogRight GAME_VAR(int, 0x9f93bc)   /* right edge of page 5's (log-out question) dialog frame, 520 (menuState210_enter; see g_logOutDialogX) */
#define g_logOutDialogBottom GAME_VAR(int, 0x9f93c0)   /* bottom of page 5's (log-out question) dialog frame, 270 (menuState210_enter; see g_logOutDialogX) */
#define g_armCursor GAME_VAR(int, 0x4dbc7c)   /* the arm list's cursor (armc_stepPart / armc_syncPartCursors, beside g_armCount / g_armList) */
#define g_headCount GAME_VAR(int, 0x4dc780)   /* the head list's length (g_headList; armc_buildPartLists); wraps g_headCursor (armc_stepPart, armc_syncPartCursors) */
#define g_armCount GAME_VAR(int, 0x4dca90)   /* the arm list's length (g_armList; armc_buildPartLists); wraps g_armCursor (armc_stepPart, armc_syncPartCursors) */
#define g_legCount GAME_VAR(int, 0x4dca94)   /* the leg list's length (g_legList; armc_buildPartLists); wraps g_legCursor (armc_stepPart, armc_syncPartCursors) */
#define g_mechDetectionAngle GAME_VAR(float, 0x4dcaa4)   /* the local mech's Actor.detectionAngle x k_0_1f (armc_readMechStats); never read */
#define g_mechLockOnTime GAME_VAR(float, 0x4dcaac)   /* the local mech's Actor.lockOnTime x 100 (armc_readMechStats); never read */
#define g_mechTargetKeepTime GAME_VAR(float, 0x4dcab0)   /* the local mech's Actor.targetKeepTime x 1000 (armc_readMechStats); never read */
#define g_mechLegsInertia GAME_VAR(float, 0x4dcad4)   /* the leg type's inertia (LegType.inertia; armc_readMechStats); never read */
#define g_mechLegsSpeedCorrection GAME_VAR(float, 0x4dcad8)   /* the leg type's speedCorrection x 100 (armc_readMechStats); never read */
#define g_mechLegsForwardBoost GAME_VAR(float, 0x4dcadc)   /* the leg type's forwardBoostCorrection x 100 (armc_readMechStats); never read */
#define g_mechLegsSideBoost GAME_VAR(float, 0x4dcae0)   /* the leg type's sideBoostCorrection x 100 (armc_readMechStats); never read */
#define g_mechLegsBackBoost GAME_VAR(float, 0x4dcae4)   /* the leg type's backBoostCorrection x 100 (armc_readMechStats); never read */
#define g_mechBoosterRestTime GAME_VAR(float, 0x4dcaf4)   /* the local mech's Actor.restTime x 1000 (armc_readMechStats); never read */
#define g_boosterCursor GAME_VAR(int, 0x4dcb30)   /* the booster list's cursor (armc_stepPart / armc_syncPartCursors, beside g_boosterCount / g_boosterList) */
#define g_legCursor GAME_VAR(int, 0x4dcea4)   /* the leg list's cursor (armc_stepPart / armc_syncPartCursors, beside g_legCount / g_legList); right after g_boosterStats' nine floats */
#define g_chestCount GAME_VAR(int, 0x4dcc60)   /* the chest list's length (g_chestList; armc_buildPartLists); wraps g_chestCursor (armc_stepPart, armc_syncPartCursors) */
#define g_headCursor GAME_VAR(int, 0x4dcc8c)   /* the head list's cursor (armc_stepPart / armc_syncPartCursors, beside g_headCount / g_headList) */
#define g_chestCursor GAME_VAR(int, 0x4dcf3c)   /* the chest list's cursor (armc_stepPart / armc_syncPartCursors, beside g_chestCount / g_chestList) */
#define g_itemBonusShieldUnread GAME_VAR(float, 0x4dbc74)   /* 1 when extra item 35 (SH-4 FORCEFIELD BOOSTER) is fitted, else 0 (armc_applyExtraItemBonuses); never read */
#define g_itemBonusEpak GAME_VAR(float, 0x4dc248)   /* 100 when extra item 28 (E-PAK EXTRA MAGAZINE) is fitted, else 0 (armc_applyExtraItemBonuses); added to CAPACITY FOR E-PAK's bonus in the arms stats (section_arms) */
#define g_itemBonus60mm GAME_VAR(float, 0x4dc548)   /* 100 when extra item 30 (60MM EXTRA MAGAZINE) is fitted, else 0 (armc_applyExtraItemBonuses); added to CAPACITY FOR 60MM's bonus (section_arms) */
#define g_itemBonusMissile GAME_VAR(float, 0x4dcb34)   /* 50 when extra item 31 (EXTRA ROCKET CHAMBER) is fitted, else 0 (armc_applyExtraItemBonuses); added to CAPACITY FOR MISSLE's bonus (section_arms) */
#define g_itemBonus30mm GAME_VAR(float, 0x4dcc6c)   /* 100 when extra item 29 (30MM EXTRA MAGAZINE) is fitted, else 0 (armc_applyExtraItemBonuses); added to CAPACITY FOR 30MM's bonus (section_arms) */
#define g_unusedArenaCamWord GAME_VAR(u32, 0x4dbaf4)   /* set to 150.0 (a float's bits) by the arena camera on each frame it flies home for a match (g_leavingForMatch 1; menu_camera's third word); never read */
#define g_unusedClock3 GAME_VAR(double, 0x4dd080)   /* a double cleared by menuState100_intro (with g_unusedClock1 / 2 and g_lastFrameClock); never read */
#define g_unusedClock2 GAME_VAR(double, 0x4dd0a8)   /* a double cleared by menuState100_intro (see g_unusedClock3); never read */
#define g_unusedClock1 GAME_VAR(double, 0x4dd560)   /* a double cleared by menuState100_intro (see g_unusedClock3); never read */
#define g_gameConnectTexture GAME_VAR(int, 0x4df450)   /* texture id of "iftex/gameconnect" (menu_loadTextures); never read */
#define g_editingFragLimit GAME_VAR(int, 0x9dd388)   /* a typed room frag limit pending: roomSettings_keys would atoi the line into g_roomFragLimit; hides the value (room_drawGameSettings), blocks room_settingsClicks; nothing sets it to 1 (cleared by room_enterCreatePage) */
#define g_editingTimeLimit GAME_VAR(int, 0x9dd568)   /* a typed room time limit pending, into g_roomTimeLimit; as g_editingFragLimit (nothing sets it to 1; cleared by room_enterCreatePage) */
#define g_unusedAccountWord GAME_VAR(int, 0x9dd6d0)   /* cleared by room_enterAccountPage (with the account fields' editing flags); never read */
#define g_newIdFormTop GAME_VAR(int, 0x9dd6ec)   /* top of the new-ID form (newIdForm_draw's frame and texture, newIdForm_layout's field rects); see g_newIdFormLeft */
#define g_unusedRoomCamWord GAME_VAR(u32, 0x9dd848)   /* set to 150.0 (a float's bits) by the room camera while it flies home for a match (room_camera via menu_camera's third word, g_leavingForMatch 1); never read */
#define g_unusedArenaWord GAME_VAR(int, 0x9fd958)   /* set to 15 by menuState400_enter; never read */
#define g_netByteBuffer GAME_VAR(char *, 0xa052e4)   /* a 1-byte zeroed send buffer (net_resetConnection; freed by net_freeBuffers); sent to the game server as request 26's body (net_send) */
#define g_lobbyLeavePacket GAME_VAR(u8 *, 0xa0b318)   /* the 0x5b-byte lobby leave packet (net_resetConnection; freed by net_freeBuffers): net_disconnect copies the hosted arena's record (g_arenaPacket) into it and sends it as message 0xb; net_send kind 11 */
#define g_errorReported GAME_VAR(int, 0xa1efe0)   /* set to 1 when an error message is reported (sys_errorMessage / sys_errorMessageNoName); never read */
#define g_fatalReported GAME_VAR(int, 0xa1efe4)   /* set to 1 when a fatal error is reported (sys_errorTerminate / sys_fatalError, before exit); never read */
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
#define g_listBlinkRate GAME_VAR(float, 0x4ad498)   /* 1.0 in the exe's data, never written: the rate g_listBlinkClock counts down by, x g_frameTime (game_lists.c lists' searching blink, room_clicks.c) */
#define g_sentChatBlock GAME_VAR(char *, 0x9fd944)   /* the last chat line sent, as "<name> > <text>" in a GlobalAlloc block (net_sendChat via net_formatChatLine); never read or freed */
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
