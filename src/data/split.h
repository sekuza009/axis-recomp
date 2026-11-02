/* split.h (tools/mkdatasrc.py): the variables split out of g_data, and in a fence build (AXIS_FENCE) their places
   in g_fence: AXIS_FENCE 1 at the end of their pages, the guard page after; 2 after the guard page */
#pragma once
#ifdef AXIS_FENCE
extern u8 g_fence[];
#endif
#ifdef AXIS_FENCE
#define g_mouseTaken_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1000 : g_fence + 0xffc))
#else
extern u8 g_mouseTaken_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textWrapX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3000 : g_fence + 0x2ffc))
#else
extern u8 g_textWrapX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5000 : g_fence + 0x4ffc))
#else
extern u8 g_textBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_resolutionNames_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x7000 : g_fence + 0x6fe0))
#else
extern u32 g_resolutionNames_v[8];
#endif
#ifdef AXIS_FENCE
#define g_bindRows_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x9000 : g_fence + 0x8ff0))
#else
extern int g_bindRows_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pulse_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb000 : g_fence + 0xaffc))
#else
extern u8 g_pulse_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pulseStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd000 : g_fence + 0xcffc))
#else
extern u8 g_pulseStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_flareSizeB_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xf000 : g_fence + 0xeffc))
#else
extern u8 g_flareSizeB_v[4];
#endif
#ifdef AXIS_FENCE
#define g_flareSizeA_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x11000 : g_fence + 0x10ffc))
#else
extern u8 g_flareSizeA_v[4];
#endif
#ifdef AXIS_FENCE
#define g_flareStepB_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x13000 : g_fence + 0x12ffc))
#else
extern u8 g_flareStepB_v[4];
#endif
#ifdef AXIS_FENCE
#define g_flareStepA_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15000 : g_fence + 0x14ffc))
#else
extern u8 g_flareStepA_v[4];
#endif
#ifdef AXIS_FENCE
#define g_timerFirstCall_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x17000 : g_fence + 0x16ffc))
#else
extern u8 g_timerFirstCall_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameRunning_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x19000 : g_fence + 0x18ffc))
#else
extern u8 g_gameRunning_v[4];
#endif
#ifdef AXIS_FENCE
#define g_keepCameraAsked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b000 : g_fence + 0x1affc))
#else
extern u8 g_keepCameraAsked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcEnterStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d000 : g_fence + 0x1cffc))
#else
extern u8 g_armcEnterStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcEnterStepF_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f000 : g_fence + 0x1effc))
#else
extern u8 g_armcEnterStepF_v[4];
#endif
#ifdef AXIS_FENCE
#define g_replayWrap_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x21000 : g_fence + 0x20ffc))
#else
extern u8 g_replayWrap_v[4];
#endif
#ifdef AXIS_FENCE
#define g_musicVolumeSetting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x23000 : g_fence + 0x22ffc))
#else
extern u8 g_musicVolumeSetting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_componentDatPath_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x25000 : g_fence + 0x24ffc))
#else
extern u8 g_componentDatPath_v[4];
#endif
#ifdef AXIS_FENCE
#define g_insertCdMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x27000 : g_fence + 0x26ffc))
#else
extern u8 g_insertCdMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glCachedState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x29000 : g_fence + 0x28ffc))
#else
extern u8 g_glCachedState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewFov_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b000 : g_fence + 0x2affc))
#else
extern u8 g_viewFov_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewNear_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d000 : g_fence + 0x2cffc))
#else
extern u8 g_viewNear_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewFar_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2f000 : g_fence + 0x2effc))
#else
extern u8 g_viewFar_v[4];
#endif
#ifdef AXIS_FENCE
#define g_errorHook_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x31000 : g_fence + 0x30ffc))
#else
extern u8 g_errorHook_v[4];
#endif
#ifdef AXIS_FENCE
#define g_catalogueFile_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x33000 : g_fence + 0x32ffc))
#else
extern u8 g_catalogueFile_v[4];
#endif
#ifdef AXIS_FENCE
#define g_keySeen_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x35000 : g_fence + 0x34c00))
#else
extern int g_keySeen_v[256];
#endif
#ifdef AXIS_FENCE
#define g_keyboardActive_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x37000 : g_fence + 0x36ffc))
#else
extern u8 g_keyboardActive_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mouseActive_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x39000 : g_fence + 0x38ffc))
#else
extern u8 g_mouseActive_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedKeyTable2Word0_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3b000 : g_fence + 0x3affc))
#else
extern u8 g_unusedKeyTable2Word0_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedKeyTable2Flags_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3d000 : g_fence + 0x3cffe))
#else
extern u8 g_unusedKeyTable2Flags_v[2];
#endif
#ifdef AXIS_FENCE
#define g_unusedKeyTable2Word1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3f000 : g_fence + 0x3effc))
#else
extern u8 g_unusedKeyTable2Word1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedKeyTable2Word2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x41000 : g_fence + 0x40ffc))
#else
extern u8 g_unusedKeyTable2Word2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textEndX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x43000 : g_fence + 0x42ffc))
#else
extern u8 g_textEndX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textEndY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x45000 : g_fence + 0x44ffc))
#else
extern u8 g_textEndY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_convertHangul_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x47000 : g_fence + 0x46ffc))
#else
extern u8 g_convertHangul_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hangulVowelGlyph_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x49000 : g_fence + 0x48ffc))
#else
extern u8 g_hangulVowelGlyph_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textCharWidth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4b000 : g_fence + 0x4affc))
#else
extern u8 g_textCharWidth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hangulTailGlyph_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4d000 : g_fence + 0x4cffc))
#else
extern u8 g_hangulTailGlyph_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hangulLeadGlyph_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4f000 : g_fence + 0x4effc))
#else
extern u8 g_hangulLeadGlyph_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingSkipped_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x51000 : g_fence + 0x50ffc))
#else
extern u8 g_briefingSkipped_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x53000 : g_fence + 0x52ffc))
#else
extern u8 g_mapTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapListRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x55000 : g_fence + 0x54e60))
#else
extern int g_mapListRects_v[104];
#endif
#ifdef AXIS_FENCE
#define g_mapListKept_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x57000 : g_fence + 0x56ffc))
#else
extern u8 g_mapListKept_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapListMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x59000 : g_fence + 0x58ffc))
#else
extern u8 g_mapListMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingNewArenaTimeLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5b000 : g_fence + 0x5affc))
#else
extern u8 g_editingNewArenaTimeLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbySubState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5d000 : g_fence + 0x5cffc))
#else
extern u8 g_lobbySubState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newArenaName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x5f000 : g_fence + 0x5efd0))
#else
extern char g_newArenaName_v[48];
#endif
#ifdef AXIS_FENCE
#define g_createQuitDialog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x61000 : g_fence + 0x60ffc))
#else
extern u8 g_createQuitDialog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaCorporation_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x63000 : g_fence + 0x62ffc))
#else
extern u8 g_arenaCorporation_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSex_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x65000 : g_fence + 0x64ffc))
#else
extern u8 g_arenaSex_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x67000 : g_fence + 0x66fa0))
#else
extern int g_arenaNameDialogRects_v[24];
#endif
#ifdef AXIS_FENCE
#define g_createArenaRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x69000 : g_fence + 0x68f00))
#else
extern int g_createArenaRects_v[64];
#endif
#ifdef AXIS_FENCE
#define g_createArena2Rects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x6b000 : g_fence + 0x6afe0))
#else
extern int g_createArena2Rects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6d000 : g_fence + 0x6cffc))
#else
extern u8 g_arenaJoinPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingArenaMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6f000 : g_fence + 0x6effc))
#else
extern u8 g_editingArenaMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x71000 : g_fence + 0x70ffc))
#else
extern u8 g_arenaJoinRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaFull_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x73000 : g_fence + 0x72ffc))
#else
extern u8 g_arenaFull_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyConnectionOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x75000 : g_fence + 0x74ffc))
#else
extern u8 g_lobbyConnectionOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaListClickArmed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x77000 : g_fence + 0x76ffc))
#else
extern u8 g_arenaListClickArmed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x79000 : g_fence + 0x78ee0))
#else
extern int g_arenaGameListRects_v[72];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptCamX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7b000 : g_fence + 0x7affc))
#else
extern u8 g_arenaKeptCamX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptCamY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7d000 : g_fence + 0x7cffc))
#else
extern u8 g_arenaKeptCamY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptCamZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7f000 : g_fence + 0x7effc))
#else
extern u8 g_arenaKeptCamZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingNewArenaFragLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x81000 : g_fence + 0x80ffc))
#else
extern u8 g_editingNewArenaFragLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverSearching_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x83000 : g_fence + 0x82ffc))
#else
extern u8 g_serverSearching_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbySearching_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x85000 : g_fence + 0x84ffc))
#else
extern u8 g_lobbySearching_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyPanelsOff_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x87000 : g_fence + 0x86ffc))
#else
extern u8 g_lobbyPanelsOff_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaConfirming_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x89000 : g_fence + 0x88ffc))
#else
extern u8 g_arenaConfirming_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyRefreshing_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8b000 : g_fence + 0x8affc))
#else
extern u8 g_lobbyRefreshing_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoining_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8d000 : g_fence + 0x8cffc))
#else
extern u8 g_arenaJoining_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8f000 : g_fence + 0x8effc))
#else
extern u8 g_arenaGameListLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x91000 : g_fence + 0x90ffc))
#else
extern u8 g_arenaGameListTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x93000 : g_fence + 0x92ffc))
#else
extern u8 g_arenaGameListRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x95000 : g_fence + 0x94ffc))
#else
extern u8 g_arenaGameListBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaTunnelDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x97000 : g_fence + 0x96ffc))
#else
extern u8 g_arenaTunnelDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyTopRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x99000 : g_fence + 0x98ff0))
#else
extern int g_lobbyTopRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyBlinkClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b000 : g_fence + 0x9affc))
#else
extern u8 g_lobbyBlinkClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSearchStarted_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9d000 : g_fence + 0x9cffc))
#else
extern u8 g_arenaSearchStarted_v[4];
#endif
#ifdef AXIS_FENCE
#define g_connectionAwaited_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9f000 : g_fence + 0x9effc))
#else
extern u8 g_connectionAwaited_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameSum_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa1000 : g_fence + 0xa0ffc))
#else
extern u8 g_arenaNameSum_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lanSearch_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa3000 : g_fence + 0xa2ffc))
#else
extern u8 g_lanSearch_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaListFull_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa5000 : g_fence + 0xa4ffc))
#else
extern u8 g_arenaListFull_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverConnected_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa7000 : g_fence + 0xa6ffc))
#else
extern u8 g_serverConnected_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingNewArenaName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa9000 : g_fence + 0xa8ffc))
#else
extern u8 g_editingNewArenaName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptLookX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xab000 : g_fence + 0xaaffc))
#else
extern u8 g_arenaKeptLookX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptLookY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xad000 : g_fence + 0xacffc))
#else
extern u8 g_arenaKeptLookY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptLookZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaf000 : g_fence + 0xaeffc))
#else
extern u8 g_arenaKeptLookZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaHaveList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb1000 : g_fence + 0xb0ffc))
#else
extern u8 g_arenaHaveList_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingArenaPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb3000 : g_fence + 0xb2ffc))
#else
extern u8 g_typingArenaPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaDialogBoxRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xb5000 : g_fence + 0xb4ff0))
#else
extern int g_arenaDialogBoxRects_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaListRefreshTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb7000 : g_fence + 0xb6ffc))
#else
extern u8 g_arenaListRefreshTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSearchClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb9000 : g_fence + 0xb8ffc))
#else
extern u8 g_arenaSearchClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newArenaForm_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xbb000 : g_fence + 0xbaff0))
#else
extern int g_newArenaForm_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSearchTicks_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbd000 : g_fence + 0xbcffc))
#else
extern u8 g_arenaSearchTicks_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaLobbyMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbf000 : g_fence + 0xbeffc))
#else
extern u8 g_arenaLobbyMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc1000 : g_fence + 0xc0ffc))
#else
extern u8 g_arenaNameDialogLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc3000 : g_fence + 0xc2ffc))
#else
extern u8 g_arenaNameDialogTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc5000 : g_fence + 0xc4ffc))
#else
extern u8 g_arenaNameDialogRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc7000 : g_fence + 0xc6ffc))
#else
extern u8 g_arenaNameDialogBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinWaiting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc9000 : g_fence + 0xc8ffc))
#else
extern u8 g_arenaJoinWaiting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaCreateRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xcb000 : g_fence + 0xcafe0))
#else
extern int g_arenaCreateRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_arenaPanelBrightness_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcd000 : g_fence + 0xccffc))
#else
extern u8 g_arenaPanelBrightness_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingArenaName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcf000 : g_fence + 0xceffc))
#else
extern u8 g_typingArenaName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typedArenaNameText_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xd1000 : g_fence + 0xd0fe8))
#else
extern char g_typedArenaNameText_v[24];
#endif
#ifdef AXIS_FENCE
#define g_lobbyJoinStarted_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd3000 : g_fence + 0xd2ffc))
#else
extern u8 g_lobbyJoinStarted_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyJoinRequest_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd5000 : g_fence + 0xd4ffc))
#else
extern u8 g_lobbyJoinRequest_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaLobbyState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd7000 : g_fence + 0xd6ffc))
#else
extern u8 g_arenaLobbyState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_receivedSession_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd9000 : g_fence + 0xd8ffc))
#else
extern u8 g_receivedSession_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xdb000 : g_fence + 0xdaffc))
#else
extern u8 g_unusedArmcWord4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcAngle_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xdd000 : g_fence + 0xdcffc))
#else
extern u8 g_armcAngle_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestWeightLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xdf000 : g_fence + 0xdeffc))
#else
extern u8 g_chestWeightLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestMaxArmor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe1000 : g_fence + 0xe0ffc))
#else
extern u8 g_chestMaxArmor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestMaxShield_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe3000 : g_fence + 0xe2ffc))
#else
extern u8 g_chestMaxShield_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcTabColour_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xe5000 : g_fence + 0xe4ff0))
#else
extern u32 g_armcTabColour_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcPreview_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe7000 : g_fence + 0xe6ffc))
#else
extern u8 g_armcPreview_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcPartSlot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe9000 : g_fence + 0xe8ffc))
#else
extern u8 g_armcPartSlot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusCapacityPerLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xeb000 : g_fence + 0xeaffc))
#else
extern u8 g_itemBonusCapacityPerLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusDetectionRange_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xed000 : g_fence + 0xecffc))
#else
extern u8 g_itemBonusDetectionRange_v[4];
#endif
#ifdef AXIS_FENCE
#define g_emptyItemSlot0_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xef000 : g_fence + 0xeeffc))
#else
extern u8 g_emptyItemSlot0_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcPartsRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xf1000 : g_fence + 0xf0f10))
#else
extern int g_armcPartsRects_v[60];
#endif
#ifdef AXIS_FENCE
#define g_armcSlot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xf3000 : g_fence + 0xf2ffc))
#else
extern u8 g_armcSlot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partRecords_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xf5000 : g_fence + 0xf4c80))
#else
extern u8 g_partRecords_v[896];
#endif
#ifdef AXIS_FENCE
#define g_armcTabColourDim_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xf7000 : g_fence + 0xf6ff0))
#else
extern u32 g_armcTabColourDim_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bestProgressSolo_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xf9000 : g_fence + 0xf8ffc))
#else
extern u8 g_bestProgressSolo_v[4];
#endif
#ifdef AXIS_FENCE
#define g_legsStats_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xfb000 : g_fence + 0xfafe4))
#else
extern float g_legsStats_v[7];
#endif
#ifdef AXIS_FENCE
#define g_weaponCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xfd000 : g_fence + 0xfcffc))
#else
extern u8 g_weaponCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcFrom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xff000 : g_fence + 0xfeffc))
#else
extern u8 g_armcFrom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armsStats_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x101000 : g_fence + 0x100fec))
#else
extern int g_armsStats_v[5];
#endif
#ifdef AXIS_FENCE
#define g_armsWeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x103000 : g_fence + 0x102ffc))
#else
extern u8 g_armsWeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMainRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x105000 : g_fence + 0x104ef0))
#else
extern int g_armcMainRects_v[68];
#endif
#ifdef AXIS_FENCE
#define g_armcColourSlot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x107000 : g_fence + 0x106ffc))
#else
extern u8 g_armcColourSlot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bestLevelNet_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x109000 : g_fence + 0x108ffc))
#else
extern u8 g_bestLevelNet_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcSessionMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x10b000 : g_fence + 0x10affc))
#else
extern u8 g_armcSessionMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox0Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x10d000 : g_fence + 0x10cffc))
#else
extern u8 g_partBox0Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox1Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x10f000 : g_fence + 0x10effc))
#else
extern u8 g_partBox1Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox2Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x111000 : g_fence + 0x110ffc))
#else
extern u8 g_partBox2Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox3Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x113000 : g_fence + 0x112ffc))
#else
extern u8 g_partBox3Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox4Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x115000 : g_fence + 0x114ffc))
#else
extern u8 g_partBox4Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox5Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x117000 : g_fence + 0x116ffc))
#else
extern u8 g_partBox5Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcParts_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x119000 : g_fence + 0x118fec))
#else
extern int g_armcParts_v[5];
#endif
#ifdef AXIS_FENCE
#define g_extraCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x11b000 : g_fence + 0x11affc))
#else
extern u8 g_extraCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcCursor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x11d000 : g_fence + 0x11cffc))
#else
extern u8 g_armcCursor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unlockedLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x11f000 : g_fence + 0x11effc))
#else
extern u8 g_unlockedLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcUnusedFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x121000 : g_fence + 0x120ffc))
#else
extern u8 g_armcUnusedFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_totalWeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x123000 : g_fence + 0x122ffc))
#else
extern u8 g_totalWeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x125000 : g_fence + 0x124ffc))
#else
extern u8 g_armcState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x127000 : g_fence + 0x126ffc))
#else
extern u8 g_armcMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x129000 : g_fence + 0x128ffc))
#else
extern u8 g_unusedArmcWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcEntered_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x12b000 : g_fence + 0x12affc))
#else
extern u8 g_armcEntered_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcSessionDue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x12d000 : g_fence + 0x12cffc))
#else
extern u8 g_armcSessionDue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x12f000 : g_fence + 0x12effc))
#else
extern u8 g_armcLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_savedMechPartIds_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x131000 : g_fence + 0x130fec))
#else
extern int g_savedMechPartIds_v[5];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusTargetKeep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x133000 : g_fence + 0x132ffc))
#else
extern u8 g_itemBonusTargetKeep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLastPart_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x135000 : g_fence + 0x134ffc))
#else
extern u8 g_armcLastPart_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusRechargeTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x137000 : g_fence + 0x136ffc))
#else
extern u8 g_itemBonusRechargeTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusLockOn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x139000 : g_fence + 0x138ffc))
#else
extern u8 g_itemBonusLockOn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcViewPoints_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x13b000 : g_fence + 0x13afa0))
#else
extern u32 g_armcViewPoints_v[24];
#endif
#ifdef AXIS_FENCE
#define g_coloursChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x13d000 : g_fence + 0x13cffc))
#else
extern u8 g_coloursChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechDetectionRange_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x13f000 : g_fence + 0x13effc))
#else
extern u8 g_mechDetectionRange_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechHackingLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x141000 : g_fence + 0x140ffc))
#else
extern u8 g_mechHackingLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechPartStats_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x143000 : g_fence + 0x142fe4))
#else
extern int g_mechPartStats_v[7];
#endif
#ifdef AXIS_FENCE
#define g_mechMobility_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x145000 : g_fence + 0x144ffc))
#else
extern u8 g_mechMobility_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedMechStat_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x147000 : g_fence + 0x146ffc))
#else
extern u8 g_unusedMechStat_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechBoosterEnergy_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x149000 : g_fence + 0x148ffc))
#else
extern u8 g_mechBoosterEnergy_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechBoosterRecharge_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x14b000 : g_fence + 0x14affc))
#else
extern u8 g_mechBoosterRecharge_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechSpeeds_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x14d000 : g_fence + 0x14cfe8))
#else
extern float g_mechSpeeds_v[6];
#endif
#ifdef AXIS_FENCE
#define g_mechSettings_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x14f000 : g_fence + 0x14efe8))
#else
extern int g_mechSettings_v[6];
#endif
#ifdef AXIS_FENCE
#define g_armcColourRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x151000 : g_fence + 0x150ee0))
#else
extern int g_armcColourRects_v[72];
#endif
#ifdef AXIS_FENCE
#define g_mechChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x153000 : g_fence + 0x152ffc))
#else
extern u8 g_mechChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x155000 : g_fence + 0x154ffc))
#else
extern u8 g_armcChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusShield_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x157000 : g_fence + 0x156ffc))
#else
extern u8 g_itemBonusShield_v[4];
#endif
#ifdef AXIS_FENCE
#define g_slotTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x159000 : g_fence + 0x158fe4))
#else
extern int g_slotTextures_v[7];
#endif
#ifdef AXIS_FENCE
#define g_armcStatsPanelLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15b000 : g_fence + 0x15affc))
#else
extern u8 g_armcStatsPanelLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcStatsPanelTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15d000 : g_fence + 0x15cffc))
#else
extern u8 g_armcStatsPanelTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcSliderLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15f000 : g_fence + 0x15effc))
#else
extern u8 g_armcSliderLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcStatsPanelBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x161000 : g_fence + 0x160ffc))
#else
extern u8 g_armcStatsPanelBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusActiveTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x163000 : g_fence + 0x162ffc))
#else
extern u8 g_itemBonusActiveTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x165000 : g_fence + 0x164ffc))
#else
extern u8 g_unusedArmcWord3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_boosterStats_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x167000 : g_fence + 0x166fd8))
#else
extern float g_boosterStats_v[10];
#endif
#ifdef AXIS_FENCE
#define g_armcSpin_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x169000 : g_fence + 0x168ffc))
#else
extern u8 g_armcSpin_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusWeightLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x16b000 : g_fence + 0x16affc))
#else
extern u8 g_itemBonusWeightLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusHacking_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x16d000 : g_fence + 0x16cffc))
#else
extern u8 g_itemBonusHacking_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headDetectionRange_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x16f000 : g_fence + 0x16effc))
#else
extern u8 g_headDetectionRange_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headDetectionAngle_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x171000 : g_fence + 0x170ffc))
#else
extern u8 g_headDetectionAngle_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headHackingLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x173000 : g_fence + 0x172ffc))
#else
extern u8 g_headHackingLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headLockOnTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x175000 : g_fence + 0x174ffc))
#else
extern u8 g_headLockOnTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headTargetKeepTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x177000 : g_fence + 0x176ffc))
#else
extern u8 g_headTargetKeepTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headWeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x179000 : g_fence + 0x178ffc))
#else
extern u8 g_headWeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLeaving_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x17b000 : g_fence + 0x17affc))
#else
extern u8 g_armcLeaving_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x17d000 : g_fence + 0x17cffc))
#else
extern u8 g_unusedArmcWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_savedMechSettings_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x17f000 : g_fence + 0x17efe8))
#else
extern int g_savedMechSettings_v[6];
#endif
#ifdef AXIS_FENCE
#define g_progressWentUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x181000 : g_fence + 0x180ffc))
#else
extern u8 g_progressWentUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcCameraBox_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x183000 : g_fence + 0x182f68))
#else
extern u32 g_armcCameraBox_v[38];
#endif
#ifdef AXIS_FENCE
#define g_armcZoom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x185000 : g_fence + 0x184ffc))
#else
extern u8 g_armcZoom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_colourChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x187000 : g_fence + 0x186ffc))
#else
extern u8 g_colourChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcHideInterface_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x189000 : g_fence + 0x188ffc))
#else
extern u8 g_armcHideInterface_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fpsSecondStart_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x18b000 : g_fence + 0x18aff8))
#else
extern u8 g_fpsSecondStart_v[8];
#endif
#ifdef AXIS_FENCE
#define g_menuFrameCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x18d000 : g_fence + 0x18cffc))
#else
extern u8 g_menuFrameCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_messageBoxArgs_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x18f000 : g_fence + 0x18effc))
#else
extern u8 g_messageBoxArgs_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedStartupWord3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x191000 : g_fence + 0x190ffc))
#else
extern u8 g_unusedStartupWord3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lastFrameClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x193000 : g_fence + 0x192ff8))
#else
extern u8 g_lastFrameClock_v[8];
#endif
#ifdef AXIS_FENCE
#define g_fpsFrameClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x195000 : g_fence + 0x194ff8))
#else
extern u8 g_fpsFrameClock_v[8];
#endif
#ifdef AXIS_FENCE
#define g_frameRate_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x197000 : g_fence + 0x196ff8))
#else
extern u8 g_frameRate_v[8];
#endif
#ifdef AXIS_FENCE
#define g_unusedStartupWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x199000 : g_fence + 0x198ffc))
#else
extern u8 g_unusedStartupWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fpsSecondSoFar_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x19b000 : g_fence + 0x19aff8))
#else
extern u8 g_fpsSecondSoFar_v[8];
#endif
#ifdef AXIS_FENCE
#define g_fps_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x19d000 : g_fence + 0x19cffc))
#else
extern u8 g_fps_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuVolume_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x19f000 : g_fence + 0x19effc))
#else
extern u8 g_menuVolume_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loadStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a1000 : g_fence + 0x1a0ffc))
#else
extern u8 g_loadStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursorBlink_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a3000 : g_fence + 0x1a2ffc))
#else
extern u8 g_cursorBlink_v[4];
#endif
#ifdef AXIS_FENCE
#define g_introZoom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a5000 : g_fence + 0x1a4ffc))
#else
extern u8 g_introZoom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPanelMoving_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a7000 : g_fence + 0x1a6ffc))
#else
extern u8 g_setupPanelMoving_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupTab_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a9000 : g_fence + 0x1a8ffc))
#else
extern u8 g_setupTab_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupSoundRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1ab000 : g_fence + 0x1aaff0))
#else
extern int g_setupSoundRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupColourDim_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x1ad000 : g_fence + 0x1acff0))
#else
extern u32 g_setupColourDim_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPressedClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1af000 : g_fence + 0x1aeffc))
#else
extern u8 g_setupPressedClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_graphicEdited_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x1b1000 : g_fence + 0x1b0fe4))
#else
extern u32 g_graphicEdited_v[7];
#endif
#ifdef AXIS_FENCE
#define g_bindPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b3000 : g_fence + 0x1b2ffc))
#else
extern u8 g_bindPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b5000 : g_fence + 0x1b4ffc))
#else
extern u8 g_setupPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupSoundRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1b7000 : g_fence + 0x1b6f60))
#else
extern int g_setupSoundRects_v[40];
#endif
#ifdef AXIS_FENCE
#define g_setupTunnelDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b9000 : g_fence + 0x1b8ffc))
#else
extern u8 g_setupTunnelDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupSliderRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1bb000 : g_fence + 0x1bafd0))
#else
extern int g_setupSliderRects_v[12];
#endif
#ifdef AXIS_FENCE
#define g_bindWaiting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1bd000 : g_fence + 0x1bcffc))
#else
extern u8 g_bindWaiting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupOptionsRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1bf000 : g_fence + 0x1beff0))
#else
extern int g_setupOptionsRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupOptionsRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1c1000 : g_fence + 0x1c0f70))
#else
extern int g_setupOptionsRects_v[36];
#endif
#ifdef AXIS_FENCE
#define g_setupControlRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1c3000 : g_fence + 0x1c2ff0))
#else
extern int g_setupControlRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPressed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c5000 : g_fence + 0x1c4ffc))
#else
extern u8 g_setupPressed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_soundEdited_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1c7000 : g_fence + 0x1c6ff0))
#else
extern int g_soundEdited_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupControlRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1c9000 : g_fence + 0x1c8ee0))
#else
extern int g_setupControlRects_v[72];
#endif
#ifdef AXIS_FENCE
#define g_setupTunnelAlpha_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1cb000 : g_fence + 0x1caffc))
#else
extern u8 g_setupTunnelAlpha_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPanelPos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1cd000 : g_fence + 0x1ccffc))
#else
extern u8 g_setupPanelPos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bindRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1cf000 : g_fence + 0x1ceffc))
#else
extern u8 g_bindRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupColourLit_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x1d1000 : g_fence + 0x1d0ff0))
#else
extern u32 g_setupColourLit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_controlsEdit_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1d3000 : g_fence + 0x1d2ef0))
#else
extern int g_controlsEdit_v[68];
#endif
#ifdef AXIS_FENCE
#define g_emblemPulse_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d5000 : g_fence + 0x1d4ffc))
#else
extern u8 g_emblemPulse_v[4];
#endif
#ifdef AXIS_FENCE
#define g_emblemAlpha_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d7000 : g_fence + 0x1d6ffc))
#else
extern u8 g_emblemAlpha_v[4];
#endif
#ifdef AXIS_FENCE
#define g_logoFade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d9000 : g_fence + 0x1d8ffc))
#else
extern u8 g_logoFade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_logoFadeLate_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1db000 : g_fence + 0x1daffc))
#else
extern u8 g_logoFadeLate_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursorBlinkTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1dd000 : g_fence + 0x1dcffc))
#else
extern u8 g_cursorBlinkTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveStarted_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1df000 : g_fence + 0x1deffc))
#else
extern u8 g_armcMoveStarted_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuCamX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e1000 : g_fence + 0x1e0ffc))
#else
extern u8 g_menuCamX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_freeCamHeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e3000 : g_fence + 0x1e2ffc))
#else
extern u8 g_freeCamHeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuCamZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e5000 : g_fence + 0x1e4ffc))
#else
extern u8 g_menuCamZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveEyeX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e7000 : g_fence + 0x1e6ffc))
#else
extern u8 g_armcMoveEyeX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveEyeY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e9000 : g_fence + 0x1e8ffc))
#else
extern u8 g_armcMoveEyeY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveEyeZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1eb000 : g_fence + 0x1eaffc))
#else
extern u8 g_armcMoveEyeZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookSin_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ed000 : g_fence + 0x1ecffc))
#else
extern u8 g_armcLookSin_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookTilt_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ef000 : g_fence + 0x1eeffc))
#else
extern u8 g_armcLookTilt_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookCos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f1000 : g_fence + 0x1f0ffc))
#else
extern u8 g_armcLookCos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveTargetX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f3000 : g_fence + 0x1f2ffc))
#else
extern u8 g_armcMoveTargetX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveTargetY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f5000 : g_fence + 0x1f4ffc))
#else
extern u8 g_armcMoveTargetY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveTargetZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f7000 : g_fence + 0x1f6ffc))
#else
extern u8 g_armcMoveTargetZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_debugValue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f9000 : g_fence + 0x1f8ffc))
#else
extern u8 g_debugValue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcMoveWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1fb000 : g_fence + 0x1faffc))
#else
extern u8 g_unusedArmcMoveWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedPostMatchFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1fd000 : g_fence + 0x1fcffc))
#else
extern u8 g_unusedPostMatchFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_watchChatOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ff000 : g_fence + 0x1feffc))
#else
extern u8 g_watchChatOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x201000 : g_fence + 0x200ffc))
#else
extern u8 g_titleLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titlePoints_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x203000 : g_fence + 0x202ffc))
#else
extern u8 g_titlePoints_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleRating_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x205000 : g_fence + 0x204ffc))
#else
extern u8 g_titleRating_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleScore_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x207000 : g_fence + 0x206ffc))
#else
extern u8 g_titleScore_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleWins_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x209000 : g_fence + 0x208ffc))
#else
extern u8 g_titleWins_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleLosses_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x20b000 : g_fence + 0x20affc))
#else
extern u8 g_titleLosses_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikMouse1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x20d000 : g_fence + 0x20cffc))
#else
extern u8 g_dikMouse1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuFramePhase_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x20f000 : g_fence + 0x20effc))
#else
extern u8 g_menuFramePhase_v[4];
#endif
#ifdef AXIS_FENCE
#define g_enteringMenus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x211000 : g_fence + 0x210ffc))
#else
extern u8 g_enteringMenus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuFrameTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x213000 : g_fence + 0x212ff8))
#else
extern int g_menuFrameTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_showCmd_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x215000 : g_fence + 0x214ffc))
#else
extern u8 g_showCmd_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x217000 : g_fence + 0x216ffc))
#else
extern u8 g_dikNumpad4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x219000 : g_fence + 0x218ffc))
#else
extern u8 g_dikNumpad3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad6_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x21b000 : g_fence + 0x21affc))
#else
extern u8 g_dikNumpad6_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad5_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x21d000 : g_fence + 0x21cffc))
#else
extern u8 g_dikNumpad5_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad8_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x21f000 : g_fence + 0x21effc))
#else
extern u8 g_dikNumpad8_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad7_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x221000 : g_fence + 0x220ffc))
#else
extern u8 g_dikNumpad7_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad9_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x223000 : g_fence + 0x222ffc))
#else
extern u8 g_dikNumpad9_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomFade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x225000 : g_fence + 0x224ffc))
#else
extern u8 g_roomFade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad0_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x227000 : g_fence + 0x226ffc))
#else
extern u8 g_dikNumpad0_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpadDot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x229000 : g_fence + 0x228ffc))
#else
extern u8 g_dikNumpadDot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x22b000 : g_fence + 0x22affc))
#else
extern u8 g_dikNumpad2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x22d000 : g_fence + 0x22cffc))
#else
extern u8 g_dikNumpad1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumLock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x22f000 : g_fence + 0x22effc))
#else
extern u8 g_dikNumLock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainWindow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x231000 : g_fence + 0x230ffc))
#else
extern u8 g_mainWindow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x233000 : g_fence + 0x232fd0))
#else
extern char g_playerName_v[48];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameSetUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x235000 : g_fence + 0x234ffc))
#else
extern u8 g_arenaGameSetUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_timerTick_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x237000 : g_fence + 0x236ff8))
#else
extern u8 g_timerTick_v[8];
#endif
#ifdef AXIS_FENCE
#define g_connectStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x239000 : g_fence + 0x238ffc))
#else
extern u8 g_connectStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mousePos_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x23b000 : g_fence + 0x23aff8))
#else
extern int g_mousePos_v[2];
#endif
#ifdef AXIS_FENCE
#define g_mouseWheelTurned_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x23d000 : g_fence + 0x23cffc))
#else
extern u8 g_mouseWheelTurned_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mouseWheel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x23f000 : g_fence + 0x23effc))
#else
extern u8 g_mouseWheel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mouseClicked_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x241000 : g_fence + 0x240ff4))
#else
extern int g_mouseClicked_v[3];
#endif
#ifdef AXIS_FENCE
#define g_mouseButtonsHeld_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x243000 : g_fence + 0x242ff4))
#else
extern int g_mouseButtonsHeld_v[3];
#endif
#ifdef AXIS_FENCE
#define g_dikInsert_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x245000 : g_fence + 0x244ffc))
#else
extern u8 g_dikInsert_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikPeriod_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x247000 : g_fence + 0x246ffc))
#else
extern u8 g_dikPeriod_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuTunnelSpeed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x249000 : g_fence + 0x248ffc))
#else
extern u8 g_menuTunnelSpeed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerCorporation_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x24b000 : g_fence + 0x24affc))
#else
extern u8 g_playerCorporation_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerSex_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x24d000 : g_fence + 0x24cffc))
#else
extern u8 g_playerSex_v[4];
#endif
#ifdef AXIS_FENCE
#define g_controls_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x24f000 : g_fence + 0x24eef0))
#else
extern int g_controls_v[68];
#endif
#ifdef AXIS_FENCE
#define g_tunnelPulseStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x251000 : g_fence + 0x250ffc))
#else
extern u8 g_tunnelPulseStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuScaleY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x253000 : g_fence + 0x252ffc))
#else
extern u8 g_menuScaleY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverAnswerIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x255000 : g_fence + 0x254ffc))
#else
extern u8 g_serverAnswerIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleShown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x257000 : g_fence + 0x256ffc))
#else
extern u8 g_titleShown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuEye_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x259000 : g_fence + 0x258ff4))
#else
extern float g_menuEye_v[3];
#endif
#ifdef AXIS_FENCE
#define g_timerFrequency_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x25b000 : g_fence + 0x25aff8))
#else
extern u8 g_timerFrequency_v[8];
#endif
#ifdef AXIS_FENCE
#define g_dikLWin_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x25d000 : g_fence + 0x25cffc))
#else
extern u8 g_dikLWin_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursorFrame_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x25f000 : g_fence + 0x25effc))
#else
extern u8 g_cursorFrame_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x261000 : g_fence + 0x260ff8))
#else
extern int g_arenaMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_exitCode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x263000 : g_fence + 0x262ffc))
#else
extern u8 g_exitCode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikInsert_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x265000 : g_fence + 0x264ffc))
#else
extern u8 g_dikInsert_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_panelGlowStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x267000 : g_fence + 0x266ffc))
#else
extern u8 g_panelGlowStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyListRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x269000 : g_fence + 0x268ffc))
#else
extern u8 g_lobbyListRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_camPoints_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x26b000 : g_fence + 0x26afb0))
#else
extern float g_camPoints_v[20];
#endif
#ifdef AXIS_FENCE
#define g_dikF11_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x26d000 : g_fence + 0x26cffc))
#else
extern u8 g_dikF11_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF12_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x26f000 : g_fence + 0x26effc))
#else
extern u8 g_dikF12_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF10_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x271000 : g_fence + 0x270ffc))
#else
extern u8 g_dikF10_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedMenuReturnWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x273000 : g_fence + 0x272ffc))
#else
extern u8 g_unusedMenuReturnWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x275000 : g_fence + 0x274ffc))
#else
extern u8 g_dikNone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fragLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x277000 : g_fence + 0x276ffc))
#else
extern u8 g_fragLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLBracket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x279000 : g_fence + 0x278ffc))
#else
extern u8 g_dikLBracket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dialogPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x27b000 : g_fence + 0x27affc))
#else
extern u8 g_dialogPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ladderMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x27d000 : g_fence + 0x27cff8))
#else
extern int g_ladderMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_dikPageUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x27f000 : g_fence + 0x27effc))
#else
extern u8 g_dikPageUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursorFrameTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x281000 : g_fence + 0x280ffc))
#else
extern u8 g_cursorFrameTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomSettingsName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x283000 : g_fence + 0x282fd0))
#else
extern char g_roomSettingsName_v[48];
#endif
#ifdef AXIS_FENCE
#define g_dikRAlt_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x285000 : g_fence + 0x284ffc))
#else
extern u8 g_dikRAlt_v[4];
#endif
#ifdef AXIS_FENCE
#define g_characterTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x287000 : g_fence + 0x286ffc))
#else
extern u8 g_characterTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleFrames_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x289000 : g_fence + 0x288ffc))
#else
extern u8 g_titleFrames_v[4];
#endif
#ifdef AXIS_FENCE
#define g_screenH_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x28b000 : g_fence + 0x28affc))
#else
extern u8 g_screenH_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik0_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x28d000 : g_fence + 0x28cffc))
#else
extern u8 g_dik0_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fovKeys_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x28f000 : g_fence + 0x28effc))
#else
extern u8 g_fovKeys_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x291000 : g_fence + 0x290ffc))
#else
extern u8 g_dik1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x293000 : g_fence + 0x292ffc))
#else
extern u8 g_dik2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x295000 : g_fence + 0x294ffc))
#else
extern u8 g_dik3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x297000 : g_fence + 0x296ffc))
#else
extern u8 g_dik4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik5_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x299000 : g_fence + 0x298ffc))
#else
extern u8 g_dik5_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik6_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x29b000 : g_fence + 0x29affc))
#else
extern u8 g_dik6_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik7_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x29d000 : g_fence + 0x29cffc))
#else
extern u8 g_dik7_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik8_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x29f000 : g_fence + 0x29effc))
#else
extern u8 g_dik8_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik9_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a1000 : g_fence + 0x2a0ffc))
#else
extern u8 g_dik9_v[4];
#endif
#ifdef AXIS_FENCE
#define g_crosshairTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a3000 : g_fence + 0x2a2ffc))
#else
extern u8 g_crosshairTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_soundSettings_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x2a5000 : g_fence + 0x2a4ff0))
#else
extern int g_soundSettings_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpadSlash_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a7000 : g_fence + 0x2a6ffc))
#else
extern u8 g_dikNumpadSlash_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuTunnelTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a9000 : g_fence + 0x2a8ffc))
#else
extern u8 g_menuTunnelTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikA_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ab000 : g_fence + 0x2aaffc))
#else
extern u8 g_dikA_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikB_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ad000 : g_fence + 0x2acffc))
#else
extern u8 g_dikB_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikC_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2af000 : g_fence + 0x2aeffc))
#else
extern u8 g_dikC_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikD_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b1000 : g_fence + 0x2b0ffc))
#else
extern u8 g_dikD_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikE_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b3000 : g_fence + 0x2b2ffc))
#else
extern u8 g_dikE_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b5000 : g_fence + 0x2b4ffc))
#else
extern u8 g_dikF_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikG_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b7000 : g_fence + 0x2b6ffc))
#else
extern u8 g_dikG_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikH_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b9000 : g_fence + 0x2b8ffc))
#else
extern u8 g_dikH_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikI_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2bb000 : g_fence + 0x2baffc))
#else
extern u8 g_dikI_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikJ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2bd000 : g_fence + 0x2bcffc))
#else
extern u8 g_dikJ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_scroll_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2bf000 : g_fence + 0x2beffc))
#else
extern u8 g_scroll_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikK_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c1000 : g_fence + 0x2c0ffc))
#else
extern u8 g_dikK_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikL_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c3000 : g_fence + 0x2c2ffc))
#else
extern u8 g_dikL_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikM_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c5000 : g_fence + 0x2c4ffc))
#else
extern u8 g_dikM_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikN_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c7000 : g_fence + 0x2c6ffc))
#else
extern u8 g_dikN_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikO_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c9000 : g_fence + 0x2c8ffc))
#else
extern u8 g_dikO_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikP_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2cb000 : g_fence + 0x2caffc))
#else
extern u8 g_dikP_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikQ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2cd000 : g_fence + 0x2ccffc))
#else
extern u8 g_dikQ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikR_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2cf000 : g_fence + 0x2ceffc))
#else
extern u8 g_dikR_v[4];
#endif
#ifdef AXIS_FENCE
#define g_screenCentreX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d1000 : g_fence + 0x2d0ffc))
#else
extern u8 g_screenCentreX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikS_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d3000 : g_fence + 0x2d2ffc))
#else
extern u8 g_dikS_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikT_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d5000 : g_fence + 0x2d4ffc))
#else
extern u8 g_dikT_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursorTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d7000 : g_fence + 0x2d6ffc))
#else
extern u8 g_cursorTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikU_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d9000 : g_fence + 0x2d8ffc))
#else
extern u8 g_dikU_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikV_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2db000 : g_fence + 0x2daffc))
#else
extern u8 g_dikV_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikW_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2dd000 : g_fence + 0x2dcffc))
#else
extern u8 g_dikW_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2df000 : g_fence + 0x2deffc))
#else
extern u8 g_dikX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e1000 : g_fence + 0x2e0ffc))
#else
extern u8 g_dikY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e3000 : g_fence + 0x2e2ffc))
#else
extern u8 g_dikZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatFieldFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e5000 : g_fence + 0x2e4ffc))
#else
extern u8 g_chatFieldFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tunnelTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e7000 : g_fence + 0x2e6ffc))
#else
extern u8 g_tunnelTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewAspect_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e9000 : g_fence + 0x2e8ffc))
#else
extern u8 g_viewAspect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_texture64x64_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2eb000 : g_fence + 0x2eaebc))
#else
extern u8 g_texture64x64_v[840004];
#endif
#ifdef AXIS_FENCE
#define g_projMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3ba000 : g_fence + 0x3b9ffc))
#else
extern u8 g_projMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEnd_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3bc000 : g_fence + 0x3bbffc))
#else
extern u8 g_dikEnd_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3be000 : g_fence + 0x3bdffc))
#else
extern u8 g_matchMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_perfCounter_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3c0000 : g_fence + 0x3bfffc))
#else
extern u8 g_perfCounter_v[4];
#endif
#ifdef AXIS_FENCE
#define g_timerHigh_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3c2000 : g_fence + 0x3c1ffc))
#else
extern u8 g_timerHigh_v[4];
#endif
#ifdef AXIS_FENCE
#define g_listRefreshPeriod_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3c4000 : g_fence + 0x3c3ffc))
#else
extern u8 g_listRefreshPeriod_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ctrlMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x3c6000 : g_fence + 0x3c5ff8))
#else
extern int g_ctrlMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_dikPageDown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3c8000 : g_fence + 0x3c7ffc))
#else
extern u8 g_dikPageDown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_screenW_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3ca000 : g_fence + 0x3c9ffc))
#else
extern u8 g_screenW_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomRecName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x3cc000 : g_fence + 0x3cbfd0))
#else
extern char g_roomRecName_v[48];
#endif
#ifdef AXIS_FENCE
#define g_dikSpace_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3ce000 : g_fence + 0x3cdffc))
#else
extern u8 g_dikSpace_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchRunning_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3d0000 : g_fence + 0x3cfffc))
#else
extern u8 g_matchRunning_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikPageUp_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3d2000 : g_fence + 0x3d1ffc))
#else
extern u8 g_dikPageUp_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_texture128x64_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3d4000 : g_fence + 0x3d3ebc))
#else
extern u8 g_texture128x64_v[840004];
#endif
#ifdef AXIS_FENCE
#define g_desktopWidth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4a3000 : g_fence + 0x4a2ffc))
#else
extern u8 g_desktopWidth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaMapCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4a5000 : g_fence + 0x4a4ffc))
#else
extern u8 g_arenaMapCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netRole_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4a7000 : g_fence + 0x4a6ffc))
#else
extern u8 g_netRole_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpadPlus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4a9000 : g_fence + 0x4a8ffc))
#else
extern u8 g_dikNumpadPlus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lastScreen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4ab000 : g_fence + 0x4aaffc))
#else
extern u8 g_lastScreen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikScrollLock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4ad000 : g_fence + 0x4acffc))
#else
extern u8 g_dikScrollLock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_quitAsked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4af000 : g_fence + 0x4aeffc))
#else
extern u8 g_quitAsked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hInstance_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4b1000 : g_fence + 0x4b0ffc))
#else
extern u8 g_hInstance_v[4];
#endif
#ifdef AXIS_FENCE
#define g_timerShift_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4b3000 : g_fence + 0x4b2ffc))
#else
extern u8 g_timerShift_v[4];
#endif
#ifdef AXIS_FENCE
#define g_nextScreen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4b5000 : g_fence + 0x4b4ffc))
#else
extern u8 g_nextScreen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLShift_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4b7000 : g_fence + 0x4b6ffc))
#else
extern u8 g_dikLShift_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikApps_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4b9000 : g_fence + 0x4b8ffc))
#else
extern u8 g_dikApps_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEnter_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4bb000 : g_fence + 0x4baffc))
#else
extern u8 g_dikEnter_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4bd000 : g_fence + 0x4bcffc))
#else
extern u8 g_gameCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_highlightX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4bf000 : g_fence + 0x4beffc))
#else
extern u8 g_highlightX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_highlightY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4c1000 : g_fence + 0x4c0ffc))
#else
extern u8 g_highlightY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuTunnel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4c3000 : g_fence + 0x4c2ffc))
#else
extern u8 g_menuTunnel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikPrintScreen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4c5000 : g_fence + 0x4c4ffc))
#else
extern u8 g_dikPrintScreen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikComma_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4c7000 : g_fence + 0x4c6ffc))
#else
extern u8 g_dikComma_v[4];
#endif
#ifdef AXIS_FENCE
#define g_keysBlocked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4c9000 : g_fence + 0x4c8ffc))
#else
extern u8 g_keysBlocked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuLook_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x4cb000 : g_fence + 0x4caff4))
#else
extern float g_menuLook_v[3];
#endif
#ifdef AXIS_FENCE
#define g_dikZ_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4cd000 : g_fence + 0x4ccffc))
#else
extern u8 g_dikZ_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewAngle_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4cf000 : g_fence + 0x4ceffc))
#else
extern u8 g_viewAngle_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikTab_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4d1000 : g_fence + 0x4d0ffc))
#else
extern u8 g_dikTab_v[4];
#endif
#ifdef AXIS_FENCE
#define g_screenCentreY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4d3000 : g_fence + 0x4d2ffc))
#else
extern u8 g_screenCentreY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_panelHovered_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4d5000 : g_fence + 0x4d4ffc))
#else
extern u8 g_panelHovered_v[4];
#endif
#ifdef AXIS_FENCE
#define g_paused_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4d7000 : g_fence + 0x4d6ffc))
#else
extern u8 g_paused_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEscape_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4d9000 : g_fence + 0x4d8ffc))
#else
extern u8 g_dikEscape_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpadEnter_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4db000 : g_fence + 0x4daffc))
#else
extern u8 g_dikNumpadEnter_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLCtrl_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4dd000 : g_fence + 0x4dcffc))
#else
extern u8 g_dikLCtrl_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuScaleX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4df000 : g_fence + 0x4deffc))
#else
extern u8 g_menuScaleX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4e1000 : g_fence + 0x4e0ffc))
#else
extern u8 g_gameListTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_repeatDown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4e3000 : g_fence + 0x4e2ffc))
#else
extern u8 g_repeatDown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyListPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4e5000 : g_fence + 0x4e4ffc))
#else
extern u8 g_lobbyListPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikMouse3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4e7000 : g_fence + 0x4e6ffc))
#else
extern u8 g_dikMouse3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_highlightSize_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4e9000 : g_fence + 0x4e8ffc))
#else
extern u8 g_highlightSize_v[4];
#endif
#ifdef AXIS_FENCE
#define g_panelGlow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4eb000 : g_fence + 0x4eaffc))
#else
extern u8 g_panelGlow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapPreviewChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4ed000 : g_fence + 0x4ecffc))
#else
extern u8 g_mapPreviewChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_texture256x64_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4ef000 : g_fence + 0x4eeebc))
#else
extern u8 g_texture256x64_v[840004];
#endif
#ifdef AXIS_FENCE
#define g_dialogChoice_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5be000 : g_fence + 0x5bdffc))
#else
extern u8 g_dialogChoice_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikApostrophe_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5c0000 : g_fence + 0x5bfffc))
#else
extern u8 g_dikApostrophe_v[4];
#endif
#ifdef AXIS_FENCE
#define g_messages_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x5c2000 : g_fence + 0x5c1b00))
#else
extern char g_messages_v[128256];
#endif
#ifdef AXIS_FENCE
#define g_dikEnd_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5e3000 : g_fence + 0x5e2ffc))
#else
extern u8 g_dikEnd_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikDown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5e5000 : g_fence + 0x5e4ffc))
#else
extern u8 g_dikDown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikGrave_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5e7000 : g_fence + 0x5e6ffc))
#else
extern u8 g_dikGrave_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikRWin_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5e9000 : g_fence + 0x5e8ffc))
#else
extern u8 g_dikRWin_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fontHanJungJong_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5eb000 : g_fence + 0x5eaffc))
#else
extern u8 g_fontHanJungJong_v[4];
#endif
#ifdef AXIS_FENCE
#define g_startedByLauncher_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5ed000 : g_fence + 0x5ecffc))
#else
extern u8 g_startedByLauncher_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chosenGameMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5ef000 : g_fence + 0x5eeffc))
#else
extern u8 g_chosenGameMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cageTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5f1000 : g_fence + 0x5f0ffc))
#else
extern u8 g_cageTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikPageDown_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5f3000 : g_fence + 0x5f2ffc))
#else
extern u8 g_dikPageDown_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikMinus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5f5000 : g_fence + 0x5f4ffc))
#else
extern u8 g_dikMinus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikBack_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5f7000 : g_fence + 0x5f6ffc))
#else
extern u8 g_dikBack_v[4];
#endif
#ifdef AXIS_FENCE
#define g_repeatUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5f9000 : g_fence + 0x5f8ffc))
#else
extern u8 g_repeatUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikRBracket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5fb000 : g_fence + 0x5faffc))
#else
extern u8 g_dikRBracket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_camAims_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x5fd000 : g_fence + 0x5fcfb0))
#else
extern float g_camAims_v[20];
#endif
#ifdef AXIS_FENCE
#define g_screen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5ff000 : g_fence + 0x5feffc))
#else
extern u8 g_screen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_desktopDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x601000 : g_fence + 0x600ffc))
#else
extern u8 g_desktopDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_logoTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x603000 : g_fence + 0x602ffc))
#else
extern u8 g_logoTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpadMinus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x605000 : g_fence + 0x604ffc))
#else
extern u8 g_dikNumpadMinus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuLookHome_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x607000 : g_fence + 0x606ff4))
#else
extern float g_menuLookHome_v[3];
#endif
#ifdef AXIS_FENCE
#define g_timeLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x609000 : g_fence + 0x608ffc))
#else
extern u8 g_timeLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListWaiting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x60b000 : g_fence + 0x60affc))
#else
extern u8 g_roomListWaiting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_startedFromLobby_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x60d000 : g_fence + 0x60cffc))
#else
extern u8 g_startedFromLobby_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikDelete_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x60f000 : g_fence + 0x60effc))
#else
extern u8 g_dikDelete_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatEditLength_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x611000 : g_fence + 0x610ffc))
#else
extern u8 g_chatEditLength_v[4];
#endif
#ifdef AXIS_FENCE
#define g_localPlayer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x613000 : g_fence + 0x612ffc))
#else
extern u8 g_localPlayer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikCapsLock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x615000 : g_fence + 0x614ffc))
#else
extern u8 g_dikCapsLock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikMouse2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x617000 : g_fence + 0x616ffc))
#else
extern u8 g_dikMouse2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuFrameCounter_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x619000 : g_fence + 0x618ffc))
#else
extern u8 g_menuFrameCounter_v[4];
#endif
#ifdef AXIS_FENCE
#define g_highlightShown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x61b000 : g_fence + 0x61affc))
#else
extern u8 g_highlightShown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_desktopHeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x61d000 : g_fence + 0x61cffc))
#else
extern u8 g_desktopHeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fontAscii_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x61f000 : g_fence + 0x61effc))
#else
extern u8 g_fontAscii_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikSemicolon_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x621000 : g_fence + 0x620ffc))
#else
extern u8 g_dikSemicolon_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedStartupWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x623000 : g_fence + 0x622ffc))
#else
extern u8 g_unusedStartupWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x625000 : g_fence + 0x624ff8))
#else
extern int g_mainMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_desktopDC_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x627000 : g_fence + 0x626ffc))
#else
extern u8 g_desktopDC_v[4];
#endif
#ifdef AXIS_FENCE
#define g_searchResult_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x629000 : g_fence + 0x628ffc))
#else
extern u8 g_searchResult_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEscape_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x62b000 : g_fence + 0x62affc))
#else
extern u8 g_dikEscape_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikWheelUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x62d000 : g_fence + 0x62cffc))
#else
extern u8 g_dikWheelUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_texture128x128_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x62f000 : g_fence + 0x62eebc))
#else
extern u8 g_texture128x128_v[840004];
#endif
#ifdef AXIS_FENCE
#define g_textureSets_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x6fe000 : g_fence + 0x6fdfe0))
#else
extern u32 g_textureSets_v[8];
#endif
#ifdef AXIS_FENCE
#define g_graphicSettings_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x700000 : g_fence + 0x6fffe4))
#else
extern int g_graphicSettings_v[7];
#endif
#ifdef AXIS_FENCE
#define g_texture256x256_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x702000 : g_fence + 0x701ebc))
#else
extern u8 g_texture256x256_v[840004];
#endif
#ifdef AXIS_FENCE
#define g_lastPanel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7d1000 : g_fence + 0x7d0ffc))
#else
extern u8 g_lastPanel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikDelete_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7d3000 : g_fence + 0x7d2ffc))
#else
extern u8 g_dikDelete_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaLeaving_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7d5000 : g_fence + 0x7d4ffc))
#else
extern u8 g_arenaLeaving_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedRoomListWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7d7000 : g_fence + 0x7d6ffc))
#else
extern u8 g_unusedRoomListWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikHome_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7d9000 : g_fence + 0x7d8ffc))
#else
extern u8 g_dikHome_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dialogOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7db000 : g_fence + 0x7daffc))
#else
extern u8 g_dialogOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookYaw_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7dd000 : g_fence + 0x7dcffc))
#else
extern u8 g_armcLookYaw_v[4];
#endif
#ifdef AXIS_FENCE
#define g_skirmishInfoCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7df000 : g_fence + 0x7deffc))
#else
extern u8 g_skirmishInfoCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_texture256x128_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7e1000 : g_fence + 0x7e0ebc))
#else
extern u8 g_texture256x128_v[840004];
#endif
#ifdef AXIS_FENCE
#define g_mapPreviewTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8b0000 : g_fence + 0x8afffc))
#else
extern u8 g_mapPreviewTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatCaretX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8b2000 : g_fence + 0x8b1ffc))
#else
extern u8 g_chatCaretX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatCaretY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8b4000 : g_fence + 0x8b3ffc))
#else
extern u8 g_chatCaretY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapRotation_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8b6000 : g_fence + 0x8b5ffc))
#else
extern u8 g_mapRotation_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuFade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8b8000 : g_fence + 0x8b7ffc))
#else
extern u8 g_menuFade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_excludedKey_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8ba000 : g_fence + 0x8b9ffc))
#else
extern u8 g_excludedKey_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8bc000 : g_fence + 0x8bbffc))
#else
extern u8 g_dikF3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8be000 : g_fence + 0x8bdffc))
#else
extern u8 g_dikF2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF5_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8c0000 : g_fence + 0x8bfffc))
#else
extern u8 g_dikF5_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8c2000 : g_fence + 0x8c1ffc))
#else
extern u8 g_dikF4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF7_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8c4000 : g_fence + 0x8c3ffc))
#else
extern u8 g_dikF7_v[4];
#endif
#ifdef AXIS_FENCE
#define g_spiralTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x8c6000 : g_fence + 0x8c5fe8))
#else
extern int g_spiralTextures_v[6];
#endif
#ifdef AXIS_FENCE
#define g_dikF6_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8c8000 : g_fence + 0x8c7ffc))
#else
extern u8 g_dikF6_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF9_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8ca000 : g_fence + 0x8c9ffc))
#else
extern u8 g_dikF9_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF8_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8cc000 : g_fence + 0x8cbffc))
#else
extern u8 g_dikF8_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikWheelDown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8ce000 : g_fence + 0x8cdffc))
#else
extern u8 g_dikWheelDown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_texturesOff_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8d0000 : g_fence + 0x8cfffc))
#else
extern u8 g_texturesOff_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomSearchAnswerIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8d2000 : g_fence + 0x8d1ffc))
#else
extern u8 g_roomSearchAnswerIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyReply_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8d4000 : g_fence + 0x8d3ffc))
#else
extern u8 g_lobbyReply_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLAlt_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8d6000 : g_fence + 0x8d5ffc))
#else
extern u8 g_dikLAlt_v[4];
#endif
#ifdef AXIS_FENCE
#define g_highlightAlpha_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8d8000 : g_fence + 0x8d7ffc))
#else
extern u8 g_highlightAlpha_v[4];
#endif
#ifdef AXIS_FENCE
#define g_frameCounter40_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8da000 : g_fence + 0x8d9ffc))
#else
extern u8 g_frameCounter40_v[4];
#endif
#ifdef AXIS_FENCE
#define g_introTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x8dc000 : g_fence + 0x8dbfe0))
#else
extern int g_introTextures_v[8];
#endif
#ifdef AXIS_FENCE
#define g_dikRCtrl_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8de000 : g_fence + 0x8ddffc))
#else
extern u8 g_dikRCtrl_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fontAsciiLarge_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8e0000 : g_fence + 0x8dfffc))
#else
extern u8 g_fontAsciiLarge_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionStage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8e2000 : g_fence + 0x8e1ffc))
#else
extern u8 g_missionStage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tunnelRings_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8e4000 : g_fence + 0x8e3ffc))
#else
extern u8 g_tunnelRings_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8e6000 : g_fence + 0x8e5ffc))
#else
extern u8 g_dikLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEquals_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8e8000 : g_fence + 0x8e7ffc))
#else
extern u8 g_dikEquals_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fontHanCho_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8ea000 : g_fence + 0x8e9ffc))
#else
extern u8 g_fontHanCho_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikHome_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8ec000 : g_fence + 0x8ebffc))
#else
extern u8 g_dikHome_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEnter_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8ee000 : g_fence + 0x8edffc))
#else
extern u8 g_dikEnter_v[4];
#endif
#ifdef AXIS_FENCE
#define g_language_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8f0000 : g_fence + 0x8efffc))
#else
extern u8 g_language_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikBackslash_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8f2000 : g_fence + 0x8f1ffc))
#else
extern u8 g_dikBackslash_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuEyeHome_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x8f4000 : g_fence + 0x8f3ff4))
#else
extern float g_menuEyeHome_v[3];
#endif
#ifdef AXIS_FENCE
#define g_dikUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8f6000 : g_fence + 0x8f5ffc))
#else
extern u8 g_dikUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_buttonTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8f8000 : g_fence + 0x8f7ffc))
#else
extern u8 g_buttonTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpadStar_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8fa000 : g_fence + 0x8f9ffc))
#else
extern u8 g_dikNumpadStar_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikRShift_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8fc000 : g_fence + 0x8fbffc))
#else
extern u8 g_dikRShift_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8fe000 : g_fence + 0x8fdffc))
#else
extern u8 g_dikRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tunnelPulse_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x900000 : g_fence + 0x8ffffc))
#else
extern u8 g_tunnelPulse_v[4];
#endif
#ifdef AXIS_FENCE
#define g_timerClocks_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x902000 : g_fence + 0x901ff0))
#else
extern u32 g_timerClocks_v[4];
#endif
#ifdef AXIS_FENCE
#define g_replayRunning_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x904000 : g_fence + 0x903ffc))
#else
extern u8 g_replayRunning_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuFadingIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x906000 : g_fence + 0x905ffc))
#else
extern u8 g_mainMenuFadingIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pixelFormatFilled_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x908000 : g_fence + 0x907fff))
#else
extern u8 g_pixelFormatFilled_v[1];
#endif
#ifdef AXIS_FENCE
#define g_timerRepeatCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x90a000 : g_fence + 0x909ffc))
#else
extern u8 g_timerRepeatCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lastCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x90c000 : g_fence + 0x90bffc))
#else
extern u8 g_lastCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_directInputMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x90e000 : g_fence + 0x90dffc))
#else
extern u8 g_directInputMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLength_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x910000 : g_fence + 0x90fffc))
#else
extern u8 g_chatLength_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fieldTabKey_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x912000 : g_fence + 0x911ffc))
#else
extern u8 g_fieldTabKey_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLine_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x914000 : g_fence + 0x913c00))
#else
extern char g_chatLine_v[1024];
#endif
#ifdef AXIS_FENCE
#define g_typedLength_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x916000 : g_fence + 0x915ffc))
#else
extern u8 g_typedLength_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListClickTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x918000 : g_fence + 0x917ffc))
#else
extern u8 g_gameListClickTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x91a000 : g_fence + 0x919f10))
#else
extern int g_gameListRects_v[60];
#endif
#ifdef AXIS_FENCE
#define g_roomMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x91c000 : g_fence + 0x91bffc))
#else
extern u8 g_roomMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loginFormRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x91e000 : g_fence + 0x91df90))
#else
extern int g_loginFormRects_v[28];
#endif
#ifdef AXIS_FENCE
#define g_retypePassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x920000 : g_fence + 0x91fffc))
#else
extern u8 g_retypePassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomMessageRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x922000 : g_fence + 0x921ff0))
#else
extern int g_roomMessageRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedRoomWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x924000 : g_fence + 0x923ffc))
#else
extern u8 g_unusedRoomWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPrevPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x926000 : g_fence + 0x925ffc))
#else
extern u8 g_roomListPrevPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomForm_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x928000 : g_fence + 0x927ff0))
#else
extern int g_roomForm_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginDue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x92a000 : g_fence + 0x929ffc))
#else
extern u8 g_roomLoginDue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingRoomName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x92c000 : g_fence + 0x92bffc))
#else
extern u8 g_typingRoomName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingSort_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x92e000 : g_fence + 0x92dffc))
#else
extern u8 g_rankingSort_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotStatsKept_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x930000 : g_fence + 0x92ffe0))
#else
extern int g_pilotStatsKept_v[8];
#endif
#ifdef AXIS_FENCE
#define g_roomListPrev_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x932000 : g_fence + 0x931ffc))
#else
extern u8 g_roomListPrev_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingEmail_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x934000 : g_fence + 0x933ffc))
#else
extern u8 g_editingEmail_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListStopRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x936000 : g_fence + 0x935ff0))
#else
extern int g_gameListStopRects_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPrevRank_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x938000 : g_fence + 0x937ffc))
#else
extern u8 g_roomListPrevRank_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedLoginWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x93a000 : g_fence + 0x939ffc))
#else
extern u8 g_unusedLoginWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListLoaded_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x93c000 : g_fence + 0x93bffc))
#else
extern u8 g_gameListLoaded_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingAccountName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x93e000 : g_fence + 0x93dffc))
#else
extern u8 g_typingAccountName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListClickArmed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x940000 : g_fence + 0x93fffc))
#else
extern u8 g_gameListClickArmed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingRequestPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x942000 : g_fence + 0x941ffc))
#else
extern u8 g_rankingRequestPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountNotice_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x944000 : g_fence + 0x943ffc))
#else
extern u8 g_accountNotice_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x946000 : g_fence + 0x945ffc))
#else
extern u8 g_roomLoginLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x948000 : g_fence + 0x947ffc))
#else
extern u8 g_roomLoginTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x94a000 : g_fence + 0x949ffc))
#else
extern u8 g_roomLoginRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x94c000 : g_fence + 0x94bffc))
#else
extern u8 g_roomLoginBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPanelLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x94e000 : g_fence + 0x94dffc))
#else
extern u8 g_accountPanelLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPanelTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x950000 : g_fence + 0x94fffc))
#else
extern u8 g_accountPanelTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPanelRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x952000 : g_fence + 0x951ffc))
#else
extern u8 g_accountPanelRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPanelBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x954000 : g_fence + 0x953ffc))
#else
extern u8 g_accountPanelBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingPasswordRepeat_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x956000 : g_fence + 0x955ffc))
#else
extern u8 g_editingPasswordRepeat_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingAccountPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x958000 : g_fence + 0x957ffc))
#else
extern u8 g_editingAccountPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingRoomName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x95a000 : g_fence + 0x959ffc))
#else
extern u8 g_editingRoomName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListDistanceLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x95c000 : g_fence + 0x95bffc))
#else
extern u8 g_roomListDistanceLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingGamePassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x95e000 : g_fence + 0x95dffc))
#else
extern u8 g_typingGamePassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_leaveDialogRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x960000 : g_fence + 0x95ffe0))
#else
extern int g_leaveDialogRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_rankingHaveList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x962000 : g_fence + 0x961ffc))
#else
extern u8 g_rankingHaveList_v[4];
#endif
#ifdef AXIS_FENCE
#define g_popupRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x964000 : g_fence + 0x963fe0))
#else
extern int g_popupRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_typingAccountPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x966000 : g_fence + 0x965ffc))
#else
extern u8 g_typingAccountPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomRefreshing_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x968000 : g_fence + 0x967ffc))
#else
extern u8 g_roomRefreshing_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x96a000 : g_fence + 0x969fa0))
#else
extern int g_accountRects_v[24];
#endif
#ifdef AXIS_FENCE
#define g_openLoginName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x96c000 : g_fence + 0x96bffc))
#else
extern u8 g_openLoginName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomGameListLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x96e000 : g_fence + 0x96dffc))
#else
extern u8 g_roomGameListLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomGameListTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x970000 : g_fence + 0x96fffc))
#else
extern u8 g_roomGameListTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomGameListRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x972000 : g_fence + 0x971ffc))
#else
extern u8 g_roomGameListRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomGameListBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x974000 : g_fence + 0x973ffc))
#else
extern u8 g_roomGameListBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPages_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x976000 : g_fence + 0x975ffc))
#else
extern u8 g_roomListPages_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListJoinClicked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x978000 : g_fence + 0x977ffc))
#else
extern u8 g_gameListJoinClicked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x97a000 : g_fence + 0x979f70))
#else
extern int g_rankingRects_v[36];
#endif
#ifdef AXIS_FENCE
#define g_roomPanelEase_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x97c000 : g_fence + 0x97bffc))
#else
extern u8 g_roomPanelEase_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingAccountRepeat_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x97e000 : g_fence + 0x97dffc))
#else
extern u8 g_typingAccountRepeat_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomJoined_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x980000 : g_fence + 0x97fffc))
#else
extern u8 g_roomJoined_v[4];
#endif
#ifdef AXIS_FENCE
#define g_joinedTitleName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x982000 : g_fence + 0x981fca))
#else
extern char g_joinedTitleName_v[54];
#endif
#ifdef AXIS_FENCE
#define g_pilotStats_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x984000 : g_fence + 0x983fe0))
#else
extern int g_pilotStats_v[8];
#endif
#ifdef AXIS_FENCE
#define g_roomTunnelDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x986000 : g_fence + 0x985ffc))
#else
extern u8 g_roomTunnelDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingOldPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x988000 : g_fence + 0x987ffc))
#else
extern u8 g_editingOldPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomSearching_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x98a000 : g_fence + 0x989ffc))
#else
extern u8 g_roomSearching_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomAnswerAwaited_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x98c000 : g_fence + 0x98bffc))
#else
extern u8 g_roomAnswerAwaited_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingRoomPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x98e000 : g_fence + 0x98dffc))
#else
extern u8 g_editingRoomPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x990000 : g_fence + 0x98fffc))
#else
extern u8 g_roomListPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingRoomPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x992000 : g_fence + 0x991ffc))
#else
extern u8 g_typingRoomPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomChatting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x994000 : g_fence + 0x993ffc))
#else
extern u8 g_roomChatting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingWaiting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x996000 : g_fence + 0x995ffc))
#else
extern u8 g_rankingWaiting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomPanelBrightness_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x998000 : g_fence + 0x997ffc))
#else
extern u8 g_roomPanelBrightness_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListRefreshTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x99a000 : g_fence + 0x999ffc))
#else
extern u8 g_roomListRefreshTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomPopup_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x99c000 : g_fence + 0x99bffc))
#else
extern u8 g_roomPopup_v[4];
#endif
#ifdef AXIS_FENCE
#define g_joinPasswordTyped_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x99e000 : g_fence + 0x99dffc))
#else
extern u8 g_joinPasswordTyped_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingAccountEmail_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9a0000 : g_fence + 0x99fffc))
#else
extern u8 g_typingAccountEmail_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomAwaitingServer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9a2000 : g_fence + 0x9a1ffc))
#else
extern u8 g_roomAwaitingServer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loginFormLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9a4000 : g_fence + 0x9a3ffc))
#else
extern u8 g_loginFormLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loginFormBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9a6000 : g_fence + 0x9a5ffc))
#else
extern u8 g_loginFormBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomSettingsRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x9a8000 : g_fence + 0x9a7f20))
#else
extern int g_roomSettingsRects_v[56];
#endif
#ifdef AXIS_FENCE
#define g_roomDialogOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9aa000 : g_fence + 0x9a9ffc))
#else
extern u8 g_roomDialogOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingLast_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ac000 : g_fence + 0x9abffc))
#else
extern u8 g_rankingLast_v[4];
#endif
#ifdef AXIS_FENCE
#define g_createDialogRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x9ae000 : g_fence + 0x9adfb0))
#else
extern int g_createDialogRects_v[20];
#endif
#ifdef AXIS_FENCE
#define g_typingGameName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b0000 : g_fence + 0x9afffc))
#else
extern u8 g_typingGameName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b2000 : g_fence + 0x9b1ffc))
#else
extern u8 g_roomState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomRequestOut_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b4000 : g_fence + 0x9b3ffc))
#else
extern u8 g_roomRequestOut_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingFirst_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b6000 : g_fence + 0x9b5ffc))
#else
extern u8 g_rankingFirst_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomNameSum_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b8000 : g_fence + 0x9b7ffc))
#else
extern u8 g_roomNameSum_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomConnected_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ba000 : g_fence + 0x9b9ffc))
#else
extern u8 g_roomConnected_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLeaveDialog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9bc000 : g_fence + 0x9bbffc))
#else
extern u8 g_roomLeaveDialog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_languageId_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9be000 : g_fence + 0x9bdffe))
#else
extern u8 g_languageId_v[2];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckSeconds_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9c0000 : g_fence + 0x9bfffc))
#else
extern u8 g_clockCheckSeconds_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedLastWParam_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9c2000 : g_fence + 0x9c1ffc))
#else
extern u8 g_unusedLastWParam_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editOldProc_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9c4000 : g_fence + 0x9c3ffc))
#else
extern u8 g_editOldProc_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hChatEdit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9c6000 : g_fence + 0x9c5ffc))
#else
extern u8 g_hChatEdit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_argCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9c8000 : g_fence + 0x9c7ffc))
#else
extern u8 g_argCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_launchMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ca000 : g_fence + 0x9c9ffc))
#else
extern u8 g_launchMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckTick_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9cc000 : g_fence + 0x9cbffc))
#else
extern u8 g_clockCheckTick_v[4];
#endif
#ifdef AXIS_FENCE
#define g_inputFont_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ce000 : g_fence + 0x9cdffc))
#else
extern u8 g_inputFont_v[4];
#endif
#ifdef AXIS_FENCE
#define g_startTicks_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9d0000 : g_fence + 0x9cfffc))
#else
extern u8 g_startTicks_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckTickSeconds_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9d2000 : g_fence + 0x9d1ffc))
#else
extern u8 g_clockCheckTickSeconds_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedInitWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9d4000 : g_fence + 0x9d3ffc))
#else
extern u8 g_unusedInitWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLineDone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9d6000 : g_fence + 0x9d5ffc))
#else
extern u8 g_chatLineDone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckClosed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9d8000 : g_fence + 0x9d7ffc))
#else
extern u8 g_clockCheckClosed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9da000 : g_fence + 0x9d9ffc))
#else
extern u8 g_mapSelectLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9dc000 : g_fence + 0x9dbffc))
#else
extern u8 g_mapSelectTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9de000 : g_fence + 0x9ddffc))
#else
extern u8 g_mapSelectRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9e0000 : g_fence + 0x9dfffc))
#else
extern u8 g_mapSelectBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLookKept_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x9e2000 : g_fence + 0x9e1ff4))
#else
extern float g_roomLookKept_v[3];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9e4000 : g_fence + 0x9e3ffc))
#else
extern u8 g_mapSelectCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectFirst_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9e6000 : g_fence + 0x9e5ffc))
#else
extern u8 g_mapSelectFirst_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomEyeKept_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x9e8000 : g_fence + 0x9e7ff4))
#else
extern float g_roomEyeKept_v[3];
#endif
#ifdef AXIS_FENCE
#define g_unusedReplayListWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ea000 : g_fence + 0x9e9ffc))
#else
extern u8 g_unusedReplayListWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuHintStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ec000 : g_fence + 0x9ebffc))
#else
extern u8 g_menuHintStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x9ee000 : g_fence + 0x9edee0))
#else
extern int g_mapSelectRects_v[72];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectDim_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x9f0000 : g_fence + 0x9efff0))
#else
extern u32 g_mapSelectDim_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuIdleTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9f2000 : g_fence + 0x9f1ffc))
#else
extern u8 g_menuIdleTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fileList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9f4000 : g_fence + 0x9f3000))
#else
extern u8 g_fileList_v[69632];
#endif
#ifdef AXIS_FENCE
#define g_unusedReplayListWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa06000 : g_fence + 0xa05ffc))
#else
extern u8 g_unusedReplayListWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuHintClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa08000 : g_fence + 0xa07ffc))
#else
extern u8 g_menuHintClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa0a000 : g_fence + 0xa09ffc))
#else
extern u8 g_mainMenuDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectLit_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xa0c000 : g_fence + 0xa0bff0))
#else
extern u32 g_mapSelectLit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tunnelFlyingIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa0e000 : g_fence + 0xa0dffc))
#else
extern u8 g_tunnelFlyingIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuFrames_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa10000 : g_fence + 0xa0fffc))
#else
extern u8 g_mainMenuFrames_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuPicked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa12000 : g_fence + 0xa11ffc))
#else
extern u8 g_mainMenuPicked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapListFlaggedCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa14000 : g_fence + 0xa13ffc))
#else
extern u8 g_mapListFlaggedCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedMainMenuWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa16000 : g_fence + 0xa15ffc))
#else
extern u8 g_unusedMainMenuWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_replayRandomOrder_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa18000 : g_fence + 0xa17ffc))
#else
extern u8 g_replayRandomOrder_v[4];
#endif
#ifdef AXIS_FENCE
#define g_skirmishColourDim_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xa1a000 : g_fence + 0xa19ff0))
#else
extern u32 g_skirmishColourDim_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingStart_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa1c000 : g_fence + 0xa1bffc))
#else
extern u8 g_briefingStart_v[4];
#endif
#ifdef AXIS_FENCE
#define g_skirmishDrawBackground_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa1e000 : g_fence + 0xa1dffc))
#else
extern u8 g_skirmishDrawBackground_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingSource_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa20000 : g_fence + 0xa1fffc))
#else
extern u8 g_briefingSource_v[4];
#endif
#ifdef AXIS_FENCE
#define g_settingsState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa22000 : g_fence + 0xa21ffc))
#else
extern u8 g_settingsState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingShown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa24000 : g_fence + 0xa23ffc))
#else
extern u8 g_briefingShown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_settingsPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa26000 : g_fence + 0xa25ffc))
#else
extern u8 g_settingsPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingEnd_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa28000 : g_fence + 0xa27ffc))
#else
extern u8 g_briefingEnd_v[4];
#endif
#ifdef AXIS_FENCE
#define g_skirmishColourLit_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xa2a000 : g_fence + 0xa29ff0))
#else
extern u32 g_skirmishColourLit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedMissionSaveWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa2c000 : g_fence + 0xa2bffc))
#else
extern u8 g_unusedMissionSaveWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_skirmishSettingsRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa2e000 : g_fence + 0xa2df60))
#else
extern int g_skirmishSettingsRects_v[40];
#endif
#ifdef AXIS_FENCE
#define g_missionHeader_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xa30000 : g_fence + 0xa2fff0))
#else
extern u32 g_missionHeader_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missions_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa32000 : g_fence + 0xa31278))
#else
extern u8 g_missions_v[7560];
#endif
#ifdef AXIS_FENCE
#define g_skirmishRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa35000 : g_fence + 0xa34ffc))
#else
extern u8 g_skirmishRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingDone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa37000 : g_fence + 0xa36ffc))
#else
extern u8 g_briefingDone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_undoDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa39000 : g_fence + 0xa38ffc))
#else
extern u8 g_undoDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingText_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xa3b000 : g_fence + 0xa3a9c0))
#else
extern char g_briefingText_v[1600];
#endif
#ifdef AXIS_FENCE
#define g_missionPicked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa3d000 : g_fence + 0xa3cffc))
#else
extern u8 g_missionPicked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa3f000 : g_fence + 0xa3effc))
#else
extern u8 g_briefingX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa41000 : g_fence + 0xa40ffc))
#else
extern u8 g_briefingY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa43000 : g_fence + 0xa42ffc))
#else
extern u8 g_briefingRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa45000 : g_fence + 0xa44ffc))
#else
extern u8 g_briefingBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa47000 : g_fence + 0xa46ffc))
#else
extern u8 g_briefingClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa49000 : g_fence + 0xa48ffc))
#else
extern u8 g_missionTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa4b000 : g_fence + 0xa4afc0))
#else
extern int g_briefingRects_v[16];
#endif
#ifdef AXIS_FENCE
#define g_campaign_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa4d000 : g_fence + 0xa4cc54))
#else
extern u8 g_campaign_v[940];
#endif
#ifdef AXIS_FENCE
#define g_missionStarted_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa4f000 : g_fence + 0xa4effc))
#else
extern u8 g_missionStarted_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionColourDim_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xa51000 : g_fence + 0xa50ff0))
#else
extern u32 g_missionColourDim_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa53000 : g_fence + 0xa52ffc))
#else
extern u8 g_missionPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileProgressSaved_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa55000 : g_fence + 0xa54ffc))
#else
extern u8 g_profileProgressSaved_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionBusy_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa57000 : g_fence + 0xa56ffc))
#else
extern u8 g_missionBusy_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionSelectRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa59000 : g_fence + 0xa58ff0))
#else
extern int g_missionSelectRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionColourLit_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xa5b000 : g_fence + 0xa5aff0))
#else
extern u32 g_missionColourLit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionChosen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa5d000 : g_fence + 0xa5cffc))
#else
extern u8 g_missionChosen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionselRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa5f000 : g_fence + 0xa5efc0))
#else
extern int g_missionselRects_v[16];
#endif
#ifdef AXIS_FENCE
#define g_missionPreviewDue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa61000 : g_fence + 0xa60ffc))
#else
extern u8 g_missionPreviewDue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionShown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa63000 : g_fence + 0xa62ffc))
#else
extern u8 g_missionShown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionShowBackground_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa65000 : g_fence + 0xa64ffc))
#else
extern u8 g_missionShowBackground_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchChatCaretY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa67000 : g_fence + 0xa66ffc))
#else
extern u8 g_matchChatCaretY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchChatCaretX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa69000 : g_fence + 0xa68ffc))
#else
extern u8 g_matchChatCaretX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_keptChat_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xa6b000 : g_fence + 0xa6ac00))
#else
extern char g_keptChat_v[1024];
#endif
#ifdef AXIS_FENCE
#define g_chatTyping_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa6d000 : g_fence + 0xa6cffc))
#else
extern u8 g_chatTyping_v[4];
#endif
#ifdef AXIS_FENCE
#define g_writeMatchLog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa6f000 : g_fence + 0xa6effc))
#else
extern u8 g_writeMatchLog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchLogWritten_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa71000 : g_fence + 0xa70ffc))
#else
extern u8 g_matchLogWritten_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchEndedByUser_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa73000 : g_fence + 0xa72ffc))
#else
extern u8 g_matchEndedByUser_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchEndedByServer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa75000 : g_fence + 0xa74ffc))
#else
extern u8 g_matchEndedByServer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedProfileCameraWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa77000 : g_fence + 0xa76ffc))
#else
extern u8 g_unusedProfileCameraWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_deleteDialogRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa79000 : g_fence + 0xa78fe0))
#else
extern int g_deleteDialogRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_profile9f6828_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa7b000 : g_fence + 0xa7affc))
#else
extern u8 g_profile9f6828_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotSelectBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa7d000 : g_fence + 0xa7cffc))
#else
extern u8 g_pilotSelectBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotSelectRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa7f000 : g_fence + 0xa7effc))
#else
extern u8 g_pilotSelectRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialog2X_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa81000 : g_fence + 0xa80ffc))
#else
extern u8 g_profileDialog2X_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileIntro_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa83000 : g_fence + 0xa82ffc))
#else
extern u8 g_profileIntro_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialog2Y_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa85000 : g_fence + 0xa84ffc))
#else
extern u8 g_profileDialog2Y_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialogOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa87000 : g_fence + 0xa86ffc))
#else
extern u8 g_profileDialogOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileFrameStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa89000 : g_fence + 0xa88ffc))
#else
extern u8 g_profileFrameStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileListTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa8b000 : g_fence + 0xa8affc))
#else
extern u8 g_profileListTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotSelectTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa8d000 : g_fence + 0xa8cffc))
#else
extern u8 g_pilotSelectTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotSelectLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa8f000 : g_fence + 0xa8effc))
#else
extern u8 g_pilotSelectLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_currentProfile_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa91000 : g_fence + 0xa90ffc))
#else
extern u8 g_currentProfile_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileListRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa93000 : g_fence + 0xa92ffc))
#else
extern u8 g_profileListRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa95000 : g_fence + 0xa94f70))
#else
extern int g_profilePageRects_v[36];
#endif
#ifdef AXIS_FENCE
#define g_emblemCursor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa97000 : g_fence + 0xa96ffc))
#else
extern u8 g_emblemCursor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_emblemMoved_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa99000 : g_fence + 0xa98ffc))
#else
extern u8 g_emblemMoved_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chosenPilot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa9b000 : g_fence + 0xa9affc))
#else
extern u8 g_chosenPilot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileScreenReady_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa9d000 : g_fence + 0xa9cffc))
#else
extern u8 g_profileScreenReady_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotChosen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa9f000 : g_fence + 0xa9effc))
#else
extern u8 g_pilotChosen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileListRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xaa1000 : g_fence + 0xaa0f30))
#else
extern int g_profileListRects_v[52];
#endif
#ifdef AXIS_FENCE
#define g_profilePageLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaa3000 : g_fence + 0xaa2ffc))
#else
extern u8 g_profilePageLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaa5000 : g_fence + 0xaa4ffc))
#else
extern u8 g_profilePageTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileIntroSpeed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaa7000 : g_fence + 0xaa6ffc))
#else
extern u8 g_profileIntroSpeed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileIntroState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaa9000 : g_fence + 0xaa8ffc))
#else
extern u8 g_profileIntroState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaab000 : g_fence + 0xaaaffc))
#else
extern u8 g_profilePageRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaad000 : g_fence + 0xaacffc))
#else
extern u8 g_profilePageBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newNameDialogTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaaf000 : g_fence + 0xaaeffc))
#else
extern u8 g_newNameDialogTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newNameDialogLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xab1000 : g_fence + 0xab0ffc))
#else
extern u8 g_newNameDialogLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_secondDialogRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xab3000 : g_fence + 0xab2fe0))
#else
extern int g_secondDialogRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_profileFrameAlpha_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xab5000 : g_fence + 0xab4ffc))
#else
extern u8 g_profileFrameAlpha_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialogY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xab7000 : g_fence + 0xab6ffc))
#else
extern u8 g_profileDialogY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xab9000 : g_fence + 0xab8ffc))
#else
extern u8 g_profilePage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileIntroZoom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xabb000 : g_fence + 0xabaffc))
#else
extern u8 g_profileIntroZoom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileMessageTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xabd000 : g_fence + 0xabcffc))
#else
extern u8 g_profileMessageTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialogX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xabf000 : g_fence + 0xabeffc))
#else
extern u8 g_profileDialogX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newNameDialogRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xac1000 : g_fence + 0xac0ffc))
#else
extern u8 g_newNameDialogRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newNameDialogBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xac3000 : g_fence + 0xac2ffc))
#else
extern u8 g_newNameDialogBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialogBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xac5000 : g_fence + 0xac4ffc))
#else
extern u8 g_profileDialogBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialogRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xac7000 : g_fence + 0xac6ffc))
#else
extern u8 g_profileDialogRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileIntroTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xac9000 : g_fence + 0xac8ffc))
#else
extern u8 g_profileIntroTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xacb000 : g_fence + 0xacaffc))
#else
extern u8 g_profileMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotSelectRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xacd000 : g_fence + 0xaccf50))
#else
extern int g_pilotSelectRects_v[44];
#endif
#ifdef AXIS_FENCE
#define g_profileCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xacf000 : g_fence + 0xaceffc))
#else
extern u8 g_profileCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileRowClicked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xad1000 : g_fence + 0xad0ffc))
#else
extern u8 g_profileRowClicked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newNameDialogRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xad3000 : g_fence + 0xad2fe0))
#else
extern int g_newNameDialogRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_profileDialog2Right_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xad5000 : g_fence + 0xad4ffc))
#else
extern u8 g_profileDialog2Right_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialog2Bottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xad7000 : g_fence + 0xad6ffc))
#else
extern u8 g_profileDialog2Bottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageKind_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xad9000 : g_fence + 0xad8ffc))
#else
extern u8 g_netChatMessageKind_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xadb000 : g_fence + 0xadaffc))
#else
extern u8 g_netChatMessageWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xadd000 : g_fence + 0xadcffc))
#else
extern u8 g_netChatMessageWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageText_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xadf000 : g_fence + 0xadeffc))
#else
extern u8 g_netChatMessageText_v[4];
#endif
#ifdef AXIS_FENCE
#define g_resultMsg_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xae1000 : g_fence + 0xae0ff8))
#else
extern u32 g_resultMsg_v[2];
#endif
#ifdef AXIS_FENCE
#define g_netSlotMsg_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xae3000 : g_fence + 0xae2ff8))
#else
extern u32 g_netSlotMsg_v[2];
#endif
#ifdef AXIS_FENCE
#define g_netSendPacket_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xae5000 : g_fence + 0xae4bf4))
#else
extern u32 g_netSendPacket_v[259];
#endif
#ifdef AXIS_FENCE
#define g_slotTakenFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xae7000 : g_fence + 0xae6ffc))
#else
extern u8 g_slotTakenFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netBlockSize_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xae9000 : g_fence + 0xae8ffc))
#else
extern u8 g_netBlockSize_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaeb000 : g_fence + 0xaeaffc))
#else
extern u8 g_chatLog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netHostGone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaed000 : g_fence + 0xaecffc))
#else
extern u8 g_netHostGone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaef000 : g_fence + 0xaeeffc))
#else
extern u8 g_playerCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_watchedSlot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaf1000 : g_fence + 0xaf0fff))
#else
extern u8 g_watchedSlot_v[1];
#endif
#ifdef AXIS_FENCE
#define g_chatLogged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaf3000 : g_fence + 0xaf2ffc))
#else
extern u8 g_chatLogged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaf5000 : g_fence + 0xaf41c0))
#else
extern u8 g_roomList_v[7744];
#endif
#ifdef AXIS_FENCE
#define g_lobbyReplyRecord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaf8000 : g_fence + 0xaf7fa5))
#else
extern u8 g_lobbyReplyRecord_v[91];
#endif
#ifdef AXIS_FENCE
#define g_netNoticeRecord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xafa000 : g_fence + 0xaf9fde))
#else
extern u8 g_netNoticeRecord_v[34];
#endif
#ifdef AXIS_FENCE
#define g_serverReply_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xafc000 : g_fence + 0xafbfc2))
#else
extern u8 g_serverReply_v[62];
#endif
#ifdef AXIS_FENCE
#define g_serverPort_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xafe000 : g_fence + 0xafdffe))
#else
extern u8 g_serverPort_v[2];
#endif
#ifdef AXIS_FENCE
#define g_unusedNetCloseWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb00000 : g_fence + 0xaffffc))
#else
extern u8 g_unusedNetCloseWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netJoinMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb02000 : g_fence + 0xb01ffc))
#else
extern u8 g_netJoinMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyTcpPort_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb04000 : g_fence + 0xb03ffc))
#else
extern u8 g_lobbyTcpPort_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbySocket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb06000 : g_fence + 0xb05ffc))
#else
extern u8 g_lobbySocket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerSocket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb08000 : g_fence + 0xb07ffc))
#else
extern u8 g_gameServerSocket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ladderPort_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb0a000 : g_fence + 0xb09ffc))
#else
extern u8 g_ladderPort_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netRecvRecord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb0c000 : g_fence + 0xb0bef5))
#else
extern u8 g_netRecvRecord_v[267];
#endif
#ifdef AXIS_FENCE
#define g_gameServerReply_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb0e000 : g_fence + 0xb0df87))
#else
extern u8 g_gameServerReply_v[121];
#endif
#ifdef AXIS_FENCE
#define g_netConnected_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb10000 : g_fence + 0xb0fffc))
#else
extern u8 g_netConnected_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netLastRequest_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb12000 : g_fence + 0xb11ffc))
#else
extern u8 g_netLastRequest_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netSendName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb14000 : g_fence + 0xb13ffc))
#else
extern u8 g_netSendName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netSendBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb16000 : g_fence + 0xb15ffc))
#else
extern u8 g_netSendBuffer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netKindWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb18000 : g_fence + 0xb17ffc))
#else
extern u8 g_netKindWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb1a000 : g_fence + 0xb19ffc))
#else
extern u8 g_roomPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netInfoPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb1c000 : g_fence + 0xb1bffc))
#else
extern u8 g_netInfoPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netLobbyMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb1e000 : g_fence + 0xb1dffc))
#else
extern u8 g_netLobbyMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb20000 : g_fence + 0xb1fffc))
#else
extern u8 g_accountPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netRankingBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb22000 : g_fence + 0xb21ffc))
#else
extern u8 g_netRankingBuffer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb24000 : g_fence + 0xb23ffc))
#else
extern u8 g_arenaPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaInfoPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb26000 : g_fence + 0xb25ffc))
#else
extern u8 g_arenaInfoPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomRecordPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb28000 : g_fence + 0xb27ffc))
#else
extern u8 g_roomRecordPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netRequestWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb2a000 : g_fence + 0xb29ffc))
#else
extern u8 g_netRequestWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netPlayerRecordPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb2c000 : g_fence + 0xb2bffc))
#else
extern u8 g_netPlayerRecordPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netLeaveBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb2e000 : g_fence + 0xb2dffc))
#else
extern u8 g_netLeaveBuffer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netSelectionPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb30000 : g_fence + 0xb2fffc))
#else
extern u8 g_netSelectionPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netAccountBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb32000 : g_fence + 0xb31ffc))
#else
extern u8 g_netAccountBuffer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb34000 : g_fence + 0xb33ffc))
#else
extern u8 g_gameServerState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerListRefused_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb36000 : g_fence + 0xb35ffc))
#else
extern u8 g_playerListRefused_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netNoticeIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb38000 : g_fence + 0xb37ffc))
#else
extern u8 g_netNoticeIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb3a000 : g_fence + 0xb39ffc))
#else
extern u8 g_roomListCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerListCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb3c000 : g_fence + 0xb3bffc))
#else
extern u8 g_playerListCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb3e000 : g_fence + 0xb3dffc))
#else
extern u8 g_lobbyPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb40000 : g_fence + 0xb3fffc))
#else
extern u8 g_gameServerPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverListCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb42000 : g_fence + 0xb41ffc))
#else
extern u8 g_serverListCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverConnectionState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb44000 : g_fence + 0xb43ffc))
#else
extern u8 g_serverConnectionState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyStatus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb46000 : g_fence + 0xb45ffc))
#else
extern u8 g_lobbyStatus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerStatus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb48000 : g_fence + 0xb47ffc))
#else
extern u8 g_gameServerStatus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerAnswer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb4a000 : g_fence + 0xb49ffc))
#else
extern u8 g_gameServerAnswer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerAnswer15_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb4c000 : g_fence + 0xb4bffc))
#else
extern u8 g_gameServerAnswer15_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyConnectStatus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb4e000 : g_fence + 0xb4dffc))
#else
extern u8 g_lobbyConnectStatus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplaySessionList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb50000 : g_fence + 0xb4fffc))
#else
extern u8 g_dplaySessionList_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netQueueOnline_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb52000 : g_fence + 0xb51ffc))
#else
extern u8 g_netQueueOnline_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSessionOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb54000 : g_fence + 0xb53ffc))
#else
extern u8 g_arenaSessionOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplayLobby_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb56000 : g_fence + 0xb55ffc))
#else
extern u8 g_dplayLobby_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplay_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb58000 : g_fence + 0xb57ffc))
#else
extern u8 g_dplay_v[4];
#endif
#ifdef AXIS_FENCE
#define g_connectionKind_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb5a000 : g_fence + 0xb59ffc))
#else
extern u8 g_connectionKind_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplaySessionCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb5c000 : g_fence + 0xb5bffc))
#else
extern u8 g_dplaySessionCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedSessionWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb5e000 : g_fence + 0xb5dffc))
#else
extern u8 g_unusedSessionWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_localPlayerId_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb60000 : g_fence + 0xb5fffc))
#else
extern u8 g_localPlayerId_v[4];
#endif
#ifdef AXIS_FENCE
#define g_localPlayerData_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb62000 : g_fence + 0xb61ffc))
#else
extern u8 g_localPlayerData_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb64000 : g_fence + 0xb63ffc))
#else
extern u8 g_unusedDplayWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb66000 : g_fence + 0xb65ffc))
#else
extern u8 g_unusedDplayWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb68000 : g_fence + 0xb67ffc))
#else
extern u8 g_unusedDplayWord3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb6a000 : g_fence + 0xb69ffc))
#else
extern u8 g_unusedDplayWord4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_connectionCopy_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb6c000 : g_fence + 0xb6bffc))
#else
extern u8 g_connectionCopy_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serviceProviderCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb6e000 : g_fence + 0xb6dffc))
#else
extern u8 g_serviceProviderCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb70000 : g_fence + 0xb6fffc))
#else
extern u8 g_arenaJoinTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_instanceGuid_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb72000 : g_fence + 0xb71ffc))
#else
extern u8 g_instanceGuid_v[4];
#endif
#ifdef AXIS_FENCE
#define g_storedConnection_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb74000 : g_fence + 0xb73ffc))
#else
extern u8 g_storedConnection_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dpConnections_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xb76000 : g_fence + 0xb75ff0))
#else
extern int g_dpConnections_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hostAddressBlock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb78000 : g_fence + 0xb77ffc))
#else
extern u8 g_hostAddressBlock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyConnectionBlock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb7a000 : g_fence + 0xb79ffc))
#else
extern u8 g_lobbyConnectionBlock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_isHost_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb7c000 : g_fence + 0xb7bffc))
#else
extern u8 g_isHost_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dpTimeout_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb7e000 : g_fence + 0xb7dffc))
#else
extern u8 g_dpTimeout_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dpMaxBufferSize_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb80000 : g_fence + 0xb7fffc))
#else
extern u8 g_dpMaxBufferSize_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dpMaxQueueSize_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb82000 : g_fence + 0xb81ffc))
#else
extern u8 g_dpMaxQueueSize_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pingDataEvent_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb84000 : g_fence + 0xb83ffc))
#else
extern u8 g_pingDataEvent_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedPingWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb86000 : g_fence + 0xb85ffc))
#else
extern u8 g_unusedPingWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedPingWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb88000 : g_fence + 0xb87ffc))
#else
extern u8 g_unusedPingWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pingStopEvent_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb8a000 : g_fence + 0xb89ffc))
#else
extern u8 g_pingStopEvent_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverNames_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xb8c000 : g_fence + 0xb8bc00))
#else
extern u32 g_serverNames_v[1280];
#endif
#ifdef AXIS_FENCE
#define g_pingThreadId_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb8f000 : g_fence + 0xb8effc))
#else
extern u8 g_pingThreadId_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pingThread_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb91000 : g_fence + 0xb90ffc))
#else
extern u8 g_pingThread_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pingTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb93000 : g_fence + 0xb92ffc))
#else
extern u8 g_pingTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverPingCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb95000 : g_fence + 0xb94ffc))
#else
extern u8 g_serverPingCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netListDone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb97000 : g_fence + 0xb96ffc))
#else
extern u8 g_netListDone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxTablesReady_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb99000 : g_fence + 0xb98ffc))
#else
extern u8 g_ptxTablesReady_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textures_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb9b000 : g_fence + 0xb9affc))
#else
extern u8 g_textures_v[4];
#endif
#ifdef AXIS_FENCE
#define g_musicDuration_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xb9d000 : g_fence + 0xb9cff8))
#else
extern u32 g_musicDuration_v[2];
#endif
#ifdef AXIS_FENCE
#define g_soundBaseVolume_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb9f000 : g_fence + 0xb9effc))
#else
extern u8 g_soundBaseVolume_v[4];
#endif
#ifdef AXIS_FENCE
#define g_music_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xba1000 : g_fence + 0xba0ffc))
#else
extern u8 g_music_v[4];
#endif
#ifdef AXIS_FENCE
#define g_vecOriginXyz_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xba3000 : g_fence + 0xba2ff4))
#else
extern float g_vecOriginXyz_v[3];
#endif
#ifdef AXIS_FENCE
#define g_vecUnitZXyz_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xba5000 : g_fence + 0xba4ff4))
#else
extern float g_vecUnitZXyz_v[3];
#endif
#ifdef AXIS_FENCE
#define g_vecZeroXyz_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xba7000 : g_fence + 0xba6ff4))
#else
extern float g_vecZeroXyz_v[3];
#endif
#ifdef AXIS_FENCE
#define g_directSound_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xba9000 : g_fence + 0xba8ffc))
#else
extern u8 g_directSound_v[4];
#endif
#ifdef AXIS_FENCE
#define g_primarySoundBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbab000 : g_fence + 0xbaaffc))
#else
extern u8 g_primarySoundBuffer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_soundOn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbad000 : g_fence + 0xbacffc))
#else
extern u8 g_soundOn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glWidth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbaf000 : g_fence + 0xbaeffc))
#else
extern u8 g_glWidth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_desktopH_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbb1000 : g_fence + 0xbb0ffc))
#else
extern u8 g_desktopH_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glColourBits_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbb3000 : g_fence + 0xbb2ffc))
#else
extern u8 g_glColourBits_v[4];
#endif
#ifdef AXIS_FENCE
#define g_desktopBits_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbb5000 : g_fence + 0xbb4ffc))
#else
extern u8 g_desktopBits_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fullScreen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbb7000 : g_fence + 0xbb6ffc))
#else
extern u8 g_fullScreen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glHeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbb9000 : g_fence + 0xbb8ffc))
#else
extern u8 g_glHeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_desktopW_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbbb000 : g_fence + 0xbbaffc))
#else
extern u8 g_desktopW_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glWindowMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbbd000 : g_fence + 0xbbcffc))
#else
extern u8 g_glWindowMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glWindow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbbf000 : g_fence + 0xbbeffc))
#else
extern u8 g_glWindow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hdc_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbc1000 : g_fence + 0xbc0ffc))
#else
extern u8 g_hdc_v[4];
#endif
#ifdef AXIS_FENCE
#define g_context_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbc3000 : g_fence + 0xbc2ffc))
#else
extern u8 g_context_v[4];
#endif
#ifdef AXIS_FENCE
#define g_modeChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbc5000 : g_fence + 0xbc4ffc))
#else
extern u8 g_modeChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loadTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbc7000 : g_fence + 0xbc6ffc))
#else
extern u8 g_loadTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loadFade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbc9000 : g_fence + 0xbc8ffc))
#else
extern u8 g_loadFade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loadProgress_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbcb000 : g_fence + 0xbcaffc))
#else
extern u8 g_loadProgress_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loadGame_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbcd000 : g_fence + 0xbccffc))
#else
extern u8 g_loadGame_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapMissing_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbcf000 : g_fence + 0xbceffc))
#else
extern u8 g_mapMissing_v[4];
#endif
#ifdef AXIS_FENCE
#define g_penFontNeverSet_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbd1000 : g_fence + 0xbd0ffc))
#else
extern u8 g_penFontNeverSet_v[4];
#endif
#ifdef AXIS_FENCE
#define g_penFontTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbd3000 : g_fence + 0xbd2ffc))
#else
extern u8 g_penFontTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tan10Table_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xbd5000 : g_fence + 0xbd4fb8))
#else
extern float g_tan10Table_v[18];
#endif
#ifdef AXIS_FENCE
#define g_randTable_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xbd7000 : g_fence + 0xbd6000))
#else
extern int g_randTable_v[4096];
#endif
#ifdef AXIS_FENCE
#define g_tanTable_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xbdc000 : g_fence + 0xbdb7c0))
#else
extern float g_tanTable_v[3600];
#endif
#ifdef AXIS_FENCE
#define g_cosTable_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xbe1000 : g_fence + 0xbe07c0))
#else
extern float g_cosTable_v[3600];
#endif
#ifdef AXIS_FENCE
#define g_sinTable_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xbe6000 : g_fence + 0xbe57c0))
#else
extern float g_sinTable_v[3600];
#endif
#ifdef AXIS_FENCE
#define g_randPos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbeb000 : g_fence + 0xbeaffc))
#else
extern u8 g_randPos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciCallback_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbed000 : g_fence + 0xbecffc))
#else
extern u8 g_mciCallback_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciFrom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbef000 : g_fence + 0xbeeffc))
#else
extern u8 g_mciFrom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciTo_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbf1000 : g_fence + 0xbf0ffc))
#else
extern u8 g_mciTo_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciDevice_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbf3000 : g_fence + 0xbf2ffc))
#else
extern u8 g_mciDevice_v[4];
#endif
#ifdef AXIS_FENCE
#define g_errorLogging_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbf5000 : g_fence + 0xbf4ffc))
#else
extern u8 g_errorLogging_v[4];
#endif
#ifdef AXIS_FENCE
#define g_errorCleanupHook_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbf7000 : g_fence + 0xbf6ffc))
#else
extern u8 g_errorCleanupHook_v[4];
#endif
#ifdef AXIS_FENCE
#define g_defaultColour_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbf9000 : g_fence + 0xbf8ffc))
#else
extern u8 g_defaultColour_v[4];
#endif
#ifdef AXIS_FENCE
#define g_colourMaskRed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbfb000 : g_fence + 0xbfaffc))
#else
extern u8 g_colourMaskRed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clamp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbfd000 : g_fence + 0xbfcffc))
#else
extern u8 g_clamp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxCbBlue_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xbff000 : g_fence + 0xbfec00))
#else
extern int g_ptxCbBlue_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxYCbCrTables_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xc01000 : g_fence + 0xc00000))
#else
extern int g_ptxYCbCrTables_v[2048];
#endif
#ifdef AXIS_FENCE
#define g_ptxBitPos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc04000 : g_fence + 0xc03ffc))
#else
extern u8 g_ptxBitPos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxPixels_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc06000 : g_fence + 0xc05000))
#else
extern u8 g_ptxPixels_v[262144];
#endif
#ifdef AXIS_FENCE
#define g_bitStream_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc47000 : g_fence + 0xc46ffc))
#else
extern u8 g_bitStream_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxCbGreen_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xc49000 : g_fence + 0xc48c00))
#else
extern int g_ptxCbGreen_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxClampTable_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc4b000 : g_fence + 0xc4aa80))
#else
extern u8 g_ptxClampTable_v[1408];
#endif
#ifdef AXIS_FENCE
#define g_ptxPlanes_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc4d000 : g_fence + 0xc4c000))
#else
extern u8 g_ptxPlanes_v[262144];
#endif
#ifdef AXIS_FENCE
#define g_ptxCrRed_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xc8e000 : g_fence + 0xc8dc00))
#else
extern int g_ptxCrRed_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxLastDc_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc90000 : g_fence + 0xc8fffc))
#else
extern u8 g_ptxLastDc_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxCrGreen_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xc92000 : g_fence + 0xc91c00))
#else
extern int g_ptxCrGreen_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxDequant_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xc94000 : g_fence + 0xc93e00))
#else
extern float g_ptxDequant_v[128];
#endif
#ifdef AXIS_FENCE
#define g_ptxQuant_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xc96000 : g_fence + 0xc95e00))
#else
extern int g_ptxQuant_v[128];
#endif
#ifdef AXIS_FENCE
#define g_ptxTable_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc98000 : g_fence + 0xc97ffc))
#else
extern u8 g_ptxTable_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxData_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc9a000 : g_fence + 0xc99000))
#else
extern u8 g_ptxData_v[262144];
#endif
#ifdef AXIS_FENCE
#define g_logHook_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcdb000 : g_fence + 0xcdaffc))
#else
extern u8 g_logHook_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursorPoint_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xcdd000 : g_fence + 0xcdcff8))
#else
extern int g_cursorPoint_v[2];
#endif
#ifdef AXIS_FENCE
#define g_currentStageName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcdf000 : g_fence + 0xcdeffc))
#else
extern u8 g_currentStageName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xce1000 : g_fence + 0xce0ffc))
#else
extern u8 g_cursor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_resends_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xce3000 : g_fence + 0xce2ffc))
#else
extern u8 g_resends_v[4];
#endif
#ifdef AXIS_FENCE
#define g_displayModeChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xce5000 : g_fence + 0xce4fff))
#else
extern u8 g_displayModeChanged_v[1];
#endif
#ifdef AXIS_FENCE
#define g_displayModeLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xce7000 : g_fence + 0xce6fff))
#else
extern u8 g_displayModeLeft_v[1];
#endif
#ifdef AXIS_FENCE
#define g_otherModeWidth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xce9000 : g_fence + 0xce8ffc))
#else
extern u8 g_otherModeWidth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_otherModeHeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xceb000 : g_fence + 0xceaffc))
#else
extern u8 g_otherModeHeight_v[4];
#endif
