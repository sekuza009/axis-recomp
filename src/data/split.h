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
#define g_hangulLeadIndex_v ((signed char *)(AXIS_FENCE == 2 ? g_fence + 0x3000 : g_fence + 0x2fe0))
#else
extern signed char g_hangulLeadIndex_v[32];
#endif
#ifdef AXIS_FENCE
#define g_hangulVowelIndex_v ((signed char *)(AXIS_FENCE == 2 ? g_fence + 0x5000 : g_fence + 0x4fe0))
#else
extern signed char g_hangulVowelIndex_v[32];
#endif
#ifdef AXIS_FENCE
#define g_hangulTailIndex_v ((signed char *)(AXIS_FENCE == 2 ? g_fence + 0x7000 : g_fence + 0x6fe0))
#else
extern signed char g_hangulTailIndex_v[32];
#endif
#ifdef AXIS_FENCE
#define g_hangulVowelSetPlain_v ((signed char *)(AXIS_FENCE == 2 ? g_fence + 0x9000 : g_fence + 0x8fea))
#else
extern signed char g_hangulVowelSetPlain_v[22];
#endif
#ifdef AXIS_FENCE
#define g_hangulVowelSetTail_v ((signed char *)(AXIS_FENCE == 2 ? g_fence + 0xb000 : g_fence + 0xafea))
#else
extern signed char g_hangulVowelSetTail_v[22];
#endif
#ifdef AXIS_FENCE
#define g_hangulLeadSetPlain_v ((signed char *)(AXIS_FENCE == 2 ? g_fence + 0xd000 : g_fence + 0xcfec))
#else
extern signed char g_hangulLeadSetPlain_v[20];
#endif
#ifdef AXIS_FENCE
#define g_hangulLeadSetTail_v ((signed char *)(AXIS_FENCE == 2 ? g_fence + 0xf000 : g_fence + 0xefec))
#else
extern signed char g_hangulLeadSetTail_v[20];
#endif
#ifdef AXIS_FENCE
#define g_hangulTailSet_v ((signed char *)(AXIS_FENCE == 2 ? g_fence + 0x11000 : g_fence + 0x10fea))
#else
extern signed char g_hangulTailSet_v[22];
#endif
#ifdef AXIS_FENCE
#define g_textWrapX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x13000 : g_fence + 0x12ffc))
#else
extern u8 g_textWrapX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15000 : g_fence + 0x14ffc))
#else
extern u8 g_textBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_resolutionNames_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x17000 : g_fence + 0x16fe0))
#else
extern u32 g_resolutionNames_v[8];
#endif
#ifdef AXIS_FENCE
#define g_bindRows_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x19000 : g_fence + 0x18ff0))
#else
extern int g_bindRows_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pulse_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b000 : g_fence + 0x1affc))
#else
extern u8 g_pulse_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pulseStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d000 : g_fence + 0x1cffc))
#else
extern u8 g_pulseStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_flareSizeB_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f000 : g_fence + 0x1effc))
#else
extern u8 g_flareSizeB_v[4];
#endif
#ifdef AXIS_FENCE
#define g_flareSizeA_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x21000 : g_fence + 0x20ffc))
#else
extern u8 g_flareSizeA_v[4];
#endif
#ifdef AXIS_FENCE
#define g_flareStepB_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x23000 : g_fence + 0x22ffc))
#else
extern u8 g_flareStepB_v[4];
#endif
#ifdef AXIS_FENCE
#define g_flareStepA_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x25000 : g_fence + 0x24ffc))
#else
extern u8 g_flareStepA_v[4];
#endif
#ifdef AXIS_FENCE
#define g_timerFirstCall_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x27000 : g_fence + 0x26ffc))
#else
extern u8 g_timerFirstCall_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameRunning_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x29000 : g_fence + 0x28ffc))
#else
extern u8 g_gameRunning_v[4];
#endif
#ifdef AXIS_FENCE
#define g_keepCameraAsked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b000 : g_fence + 0x2affc))
#else
extern u8 g_keepCameraAsked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcEnterStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d000 : g_fence + 0x2cffc))
#else
extern u8 g_armcEnterStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcEnterStepF_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2f000 : g_fence + 0x2effc))
#else
extern u8 g_armcEnterStepF_v[4];
#endif
#ifdef AXIS_FENCE
#define g_replayWrap_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x31000 : g_fence + 0x30ffc))
#else
extern u8 g_replayWrap_v[4];
#endif
#ifdef AXIS_FENCE
#define g_musicVolumeSetting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x33000 : g_fence + 0x32ffc))
#else
extern u8 g_musicVolumeSetting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_componentDatPath_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x35000 : g_fence + 0x34ffc))
#else
extern u8 g_componentDatPath_v[4];
#endif
#ifdef AXIS_FENCE
#define g_insertCdMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x37000 : g_fence + 0x36ffc))
#else
extern u8 g_insertCdMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glCachedState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x39000 : g_fence + 0x38ffc))
#else
extern u8 g_glCachedState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewFov_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3b000 : g_fence + 0x3affc))
#else
extern u8 g_viewFov_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewNear_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3d000 : g_fence + 0x3cffc))
#else
extern u8 g_viewNear_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewFar_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3f000 : g_fence + 0x3effc))
#else
extern u8 g_viewFar_v[4];
#endif
#ifdef AXIS_FENCE
#define g_errorHook_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x41000 : g_fence + 0x40ffc))
#else
extern u8 g_errorHook_v[4];
#endif
#ifdef AXIS_FENCE
#define g_sortBounds_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x43000 : g_fence + 0x42000))
#else
extern int g_sortBounds_v[8192];
#endif
#ifdef AXIS_FENCE
#define g_catalogueFile_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4c000 : g_fence + 0x4bffc))
#else
extern u8 g_catalogueFile_v[4];
#endif
#ifdef AXIS_FENCE
#define g_keyTable1_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x4e000 : g_fence + 0x4dc00))
#else
extern int g_keyTable1_v[256];
#endif
#ifdef AXIS_FENCE
#define g_mouseState_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x50000 : g_fence + 0x4fff0))
#else
extern int g_mouseState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_keySeen_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x52000 : g_fence + 0x51c00))
#else
extern int g_keySeen_v[256];
#endif
#ifdef AXIS_FENCE
#define g_keyState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x54000 : g_fence + 0x53f00))
#else
extern u8 g_keyState_v[256];
#endif
#ifdef AXIS_FENCE
#define g_keyboardActive_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x56000 : g_fence + 0x55ffc))
#else
extern u8 g_keyboardActive_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mouseActive_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x58000 : g_fence + 0x57ffc))
#else
extern u8 g_mouseActive_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedKeyTable2Word0_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5a000 : g_fence + 0x59ffc))
#else
extern u8 g_unusedKeyTable2Word0_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedKeyTable2Flags_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5c000 : g_fence + 0x5bffe))
#else
extern u8 g_unusedKeyTable2Flags_v[2];
#endif
#ifdef AXIS_FENCE
#define g_unusedKeyTable2Word1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5e000 : g_fence + 0x5dffc))
#else
extern u8 g_unusedKeyTable2Word1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedKeyTable2Word2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x60000 : g_fence + 0x5fffc))
#else
extern u8 g_unusedKeyTable2Word2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_keyTable2_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x62000 : g_fence + 0x61c00))
#else
extern int g_keyTable2_v[256];
#endif
#ifdef AXIS_FENCE
#define g_textEndX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x64000 : g_fence + 0x63ffc))
#else
extern u8 g_textEndX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textEndY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x66000 : g_fence + 0x65ffc))
#else
extern u8 g_textEndY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_convertHangul_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x68000 : g_fence + 0x67ffc))
#else
extern u8 g_convertHangul_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hangulVowelGlyph_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6a000 : g_fence + 0x69ffc))
#else
extern u8 g_hangulVowelGlyph_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textCharWidth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6c000 : g_fence + 0x6bffc))
#else
extern u8 g_textCharWidth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hangulTailGlyph_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6e000 : g_fence + 0x6dffc))
#else
extern u8 g_hangulTailGlyph_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hangulLeadGlyph_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x70000 : g_fence + 0x6fffc))
#else
extern u8 g_hangulLeadGlyph_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingSkipped_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x72000 : g_fence + 0x71ffc))
#else
extern u8 g_briefingSkipped_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x74000 : g_fence + 0x73ffc))
#else
extern u8 g_mapTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapChoiceTable_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x76000 : g_fence + 0x75000))
#else
extern u8 g_mapChoiceTable_v[8192];
#endif
#ifdef AXIS_FENCE
#define g_mapListRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x79000 : g_fence + 0x78e60))
#else
extern int g_mapListRects_v[104];
#endif
#ifdef AXIS_FENCE
#define g_mapListKept_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7b000 : g_fence + 0x7affc))
#else
extern u8 g_mapListKept_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapChoiceKeptTable_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7d000 : g_fence + 0x7c000))
#else
extern u8 g_mapChoiceKeptTable_v[8192];
#endif
#ifdef AXIS_FENCE
#define g_mapListOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x80000 : g_fence + 0x7fffc))
#else
extern u8 g_mapListOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapListMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x82000 : g_fence + 0x81ffc))
#else
extern u8 g_mapListMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingNewArenaTimeLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x84000 : g_fence + 0x83ffc))
#else
extern u8 g_editingNewArenaTimeLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbySubState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x86000 : g_fence + 0x85ffc))
#else
extern u8 g_lobbySubState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newArenaName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x88000 : g_fence + 0x87fd0))
#else
extern char g_newArenaName_v[48];
#endif
#ifdef AXIS_FENCE
#define g_createQuitDialog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8a000 : g_fence + 0x89ffc))
#else
extern u8 g_createQuitDialog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaCorporation_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8c000 : g_fence + 0x8bffc))
#else
extern u8 g_arenaCorporation_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSex_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8e000 : g_fence + 0x8dffc))
#else
extern u8 g_arenaSex_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x90000 : g_fence + 0x8ffa0))
#else
extern int g_arenaNameDialogRects_v[24];
#endif
#ifdef AXIS_FENCE
#define g_createArenaRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x92000 : g_fence + 0x91f00))
#else
extern int g_createArenaRects_v[64];
#endif
#ifdef AXIS_FENCE
#define g_createArena2Rects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x94000 : g_fence + 0x93fe0))
#else
extern int g_createArena2Rects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x96000 : g_fence + 0x95ffc))
#else
extern u8 g_arenaJoinPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingArenaMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x98000 : g_fence + 0x97ffc))
#else
extern u8 g_editingArenaMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9a000 : g_fence + 0x99ffc))
#else
extern u8 g_arenaJoinRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaFull_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9c000 : g_fence + 0x9bffc))
#else
extern u8 g_arenaFull_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyConnectionOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9e000 : g_fence + 0x9dffc))
#else
extern u8 g_lobbyConnectionOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaListClickArmed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa0000 : g_fence + 0x9fffc))
#else
extern u8 g_arenaListClickArmed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa2000 : g_fence + 0xa1ee0))
#else
extern int g_arenaGameListRects_v[72];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptCamX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa4000 : g_fence + 0xa3ffc))
#else
extern u8 g_arenaKeptCamX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptCamY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa6000 : g_fence + 0xa5ffc))
#else
extern u8 g_arenaKeptCamY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptCamZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa8000 : g_fence + 0xa7ffc))
#else
extern u8 g_arenaKeptCamZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingNewArenaFragLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaa000 : g_fence + 0xa9ffc))
#else
extern u8 g_editingNewArenaFragLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverSearching_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xac000 : g_fence + 0xabffc))
#else
extern u8 g_serverSearching_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbySearching_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xae000 : g_fence + 0xadffc))
#else
extern u8 g_lobbySearching_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyPanelsOff_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb0000 : g_fence + 0xafffc))
#else
extern u8 g_lobbyPanelsOff_v[4];
#endif
#ifdef AXIS_FENCE
#define g_teamNames_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xb2000 : g_fence + 0xb1fc4))
#else
extern char g_teamNames_v[60];
#endif
#ifdef AXIS_FENCE
#define g_arenaConfirming_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb4000 : g_fence + 0xb3ffc))
#else
extern u8 g_arenaConfirming_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyRefreshing_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb6000 : g_fence + 0xb5ffc))
#else
extern u8 g_lobbyRefreshing_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoining_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb8000 : g_fence + 0xb7ffc))
#else
extern u8 g_arenaJoining_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xba000 : g_fence + 0xb9ffc))
#else
extern u8 g_arenaGameListLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbc000 : g_fence + 0xbbffc))
#else
extern u8 g_arenaGameListTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbe000 : g_fence + 0xbdffc))
#else
extern u8 g_arenaGameListRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc0000 : g_fence + 0xbfffc))
#else
extern u8 g_arenaGameListBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameTypeNames_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xc2000 : g_fence + 0xc1ed4))
#else
extern char g_gameTypeNames_v[300];
#endif
#ifdef AXIS_FENCE
#define g_arenaTunnelDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc4000 : g_fence + 0xc3ffc))
#else
extern u8 g_arenaTunnelDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyTopRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xc6000 : g_fence + 0xc5ff0))
#else
extern int g_lobbyTopRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyBlinkClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc8000 : g_fence + 0xc7ffc))
#else
extern u8 g_lobbyBlinkClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSearchStarted_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xca000 : g_fence + 0xc9ffc))
#else
extern u8 g_arenaSearchStarted_v[4];
#endif
#ifdef AXIS_FENCE
#define g_connectionAwaited_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcc000 : g_fence + 0xcbffc))
#else
extern u8 g_connectionAwaited_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameSum_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xce000 : g_fence + 0xcdffc))
#else
extern u8 g_arenaNameSum_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lanSearch_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd0000 : g_fence + 0xcfffc))
#else
extern u8 g_lanSearch_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaListFull_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd2000 : g_fence + 0xd1ffc))
#else
extern u8 g_arenaListFull_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverConnected_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd4000 : g_fence + 0xd3ffc))
#else
extern u8 g_serverConnected_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingNewArenaName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd6000 : g_fence + 0xd5ffc))
#else
extern u8 g_editingNewArenaName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptLookX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd8000 : g_fence + 0xd7ffc))
#else
extern u8 g_arenaKeptLookX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptLookY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xda000 : g_fence + 0xd9ffc))
#else
extern u8 g_arenaKeptLookY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptLookZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xdc000 : g_fence + 0xdbffc))
#else
extern u8 g_arenaKeptLookZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaHaveList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xde000 : g_fence + 0xddffc))
#else
extern u8 g_arenaHaveList_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingArenaPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe0000 : g_fence + 0xdfffc))
#else
extern u8 g_typingArenaPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaDialogBoxRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xe2000 : g_fence + 0xe1ff0))
#else
extern int g_arenaDialogBoxRects_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaListRefreshTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe4000 : g_fence + 0xe3ffc))
#else
extern u8 g_arenaListRefreshTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSearchClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe6000 : g_fence + 0xe5ffc))
#else
extern u8 g_arenaSearchClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newArenaForm_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xe8000 : g_fence + 0xe7ff0))
#else
extern int g_newArenaForm_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSearchTicks_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xea000 : g_fence + 0xe9ffc))
#else
extern u8 g_arenaSearchTicks_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaOnOff_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xec000 : g_fence + 0xebfd8))
#else
extern char g_arenaOnOff_v[40];
#endif
#ifdef AXIS_FENCE
#define g_arenaLobbyMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xee000 : g_fence + 0xedffc))
#else
extern u8 g_arenaLobbyMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyTopRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xf0000 : g_fence + 0xeffe0))
#else
extern int g_lobbyTopRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_lobbyTopEase_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xf2000 : g_fence + 0xf1ffc))
#else
extern float g_lobbyTopEase_v[1];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xf4000 : g_fence + 0xf3ffc))
#else
extern u8 g_arenaNameDialogLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xf6000 : g_fence + 0xf5ffc))
#else
extern u8 g_arenaNameDialogTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xf8000 : g_fence + 0xf7ffc))
#else
extern u8 g_arenaNameDialogRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xfa000 : g_fence + 0xf9ffc))
#else
extern u8 g_arenaNameDialogBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinWaiting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xfc000 : g_fence + 0xfbffc))
#else
extern u8 g_arenaJoinWaiting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaCreateRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xfe000 : g_fence + 0xfdfe0))
#else
extern int g_arenaCreateRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_arenaPanelBrightness_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x100000 : g_fence + 0xffffc))
#else
extern u8 g_arenaPanelBrightness_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaOnOff2_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x102000 : g_fence + 0x101fd8))
#else
extern char g_arenaOnOff2_v[40];
#endif
#ifdef AXIS_FENCE
#define g_typingArenaName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x104000 : g_fence + 0x103ffc))
#else
extern u8 g_typingArenaName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typedArenaNameText_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x106000 : g_fence + 0x105fe8))
#else
extern char g_typedArenaNameText_v[24];
#endif
#ifdef AXIS_FENCE
#define g_lobbyJoinStarted_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x108000 : g_fence + 0x107ffc))
#else
extern u8 g_lobbyJoinStarted_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyJoinRequest_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x10a000 : g_fence + 0x109ffc))
#else
extern u8 g_lobbyJoinRequest_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaLobbyState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x10c000 : g_fence + 0x10bffc))
#else
extern u8 g_arenaLobbyState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_receivedSession_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x10e000 : g_fence + 0x10dffc))
#else
extern u8 g_receivedSession_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x110000 : g_fence + 0x10fffc))
#else
extern u8 g_unusedArmcWord4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcAngle_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x112000 : g_fence + 0x111ffc))
#else
extern u8 g_armcAngle_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestPanelName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x114000 : g_fence + 0x113fc0))
#else
extern char g_chestPanelName_v[64];
#endif
#ifdef AXIS_FENCE
#define g_chestWeightLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x116000 : g_fence + 0x115ffc))
#else
extern u8 g_chestWeightLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestMaxArmor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x118000 : g_fence + 0x117ffc))
#else
extern u8 g_chestMaxArmor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestMaxShield_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x11a000 : g_fence + 0x119ffc))
#else
extern u8 g_chestMaxShield_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcTabColour_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x11c000 : g_fence + 0x11bff0))
#else
extern u32 g_armcTabColour_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcPreview_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x11e000 : g_fence + 0x11dffc))
#else
extern u8 g_armcPreview_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcPartSlot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x120000 : g_fence + 0x11fffc))
#else
extern u8 g_armcPartSlot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusCapacityPerLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x122000 : g_fence + 0x121ffc))
#else
extern u8 g_itemBonusCapacityPerLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusShieldUnread_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x124000 : g_fence + 0x123ffc))
#else
extern u8 g_itemBonusShieldUnread_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusDetectionRange_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x126000 : g_fence + 0x125ffc))
#else
extern u8 g_itemBonusDetectionRange_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armCursor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x128000 : g_fence + 0x127ffc))
#else
extern u8 g_armCursor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_emptyItemSlot0_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x12a000 : g_fence + 0x129ffc))
#else
extern u8 g_emptyItemSlot0_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcPartsRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x12c000 : g_fence + 0x12bf10))
#else
extern int g_armcPartsRects_v[60];
#endif
#ifdef AXIS_FENCE
#define g_boosterList_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x12e000 : g_fence + 0x12df38))
#else
extern int g_boosterList_v[50];
#endif
#ifdef AXIS_FENCE
#define g_armcSlot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x130000 : g_fence + 0x12fffc))
#else
extern u8 g_armcSlot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partRecords_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x132000 : g_fence + 0x131c80))
#else
extern u8 g_partRecords_v[896];
#endif
#ifdef AXIS_FENCE
#define g_armcTabColourDim_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x134000 : g_fence + 0x133ff0))
#else
extern u32 g_armcTabColourDim_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bestProgressSolo_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x136000 : g_fence + 0x135ffc))
#else
extern u8 g_bestProgressSolo_v[4];
#endif
#ifdef AXIS_FENCE
#define g_legPanelName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x138000 : g_fence + 0x137fc0))
#else
extern char g_legPanelName_v[64];
#endif
#ifdef AXIS_FENCE
#define g_legsStats_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x13a000 : g_fence + 0x139fe4))
#else
extern float g_legsStats_v[7];
#endif
#ifdef AXIS_FENCE
#define g_weaponCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x13c000 : g_fence + 0x13bffc))
#else
extern u8 g_weaponCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusEpak_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x13e000 : g_fence + 0x13dffc))
#else
extern u8 g_itemBonusEpak_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcFrom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x140000 : g_fence + 0x13fffc))
#else
extern u8 g_armcFrom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armPanelName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x142000 : g_fence + 0x141fc0))
#else
extern char g_armPanelName_v[64];
#endif
#ifdef AXIS_FENCE
#define g_armsStats_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x144000 : g_fence + 0x143fec))
#else
extern int g_armsStats_v[5];
#endif
#ifdef AXIS_FENCE
#define g_armsWeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x146000 : g_fence + 0x145ffc))
#else
extern u8 g_armsWeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMainRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x148000 : g_fence + 0x147ef0))
#else
extern int g_armcMainRects_v[68];
#endif
#ifdef AXIS_FENCE
#define g_headList_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x14a000 : g_fence + 0x149f38))
#else
extern int g_headList_v[50];
#endif
#ifdef AXIS_FENCE
#define g_armcColourSlot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x14c000 : g_fence + 0x14bffc))
#else
extern u8 g_armcColourSlot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bestLevelNet_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x14e000 : g_fence + 0x14dffc))
#else
extern u8 g_bestLevelNet_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonus60mm_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x150000 : g_fence + 0x14fffc))
#else
extern u8 g_itemBonus60mm_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcSessionMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x152000 : g_fence + 0x151ffc))
#else
extern u8 g_armcSessionMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_panelBoxes_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x154000 : g_fence + 0x153df0))
#else
extern u8 g_panelBoxes_v[528];
#endif
#ifdef AXIS_FENCE
#define g_armcParts_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x156000 : g_fence + 0x155fec))
#else
extern int g_armcParts_v[5];
#endif
#ifdef AXIS_FENCE
#define g_extraCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x158000 : g_fence + 0x157ffc))
#else
extern u8 g_extraCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcCursor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15a000 : g_fence + 0x159ffc))
#else
extern u8 g_armcCursor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15c000 : g_fence + 0x15bffc))
#else
extern u8 g_headCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unlockedLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15e000 : g_fence + 0x15dffc))
#else
extern u8 g_unlockedLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcUnusedFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x160000 : g_fence + 0x15fffc))
#else
extern u8 g_armcUnusedFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_totalWeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x162000 : g_fence + 0x161ffc))
#else
extern u8 g_totalWeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x164000 : g_fence + 0x163ffc))
#else
extern u8 g_armcState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x166000 : g_fence + 0x165ffc))
#else
extern u8 g_armcMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_weaponListTable_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x168000 : g_fence + 0x167f38))
#else
extern int g_weaponListTable_v[50];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x16a000 : g_fence + 0x169ffc))
#else
extern u8 g_unusedArmcWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcEntered_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x16c000 : g_fence + 0x16bffc))
#else
extern u8 g_armcEntered_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcSessionDue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x16e000 : g_fence + 0x16dffc))
#else
extern u8 g_armcSessionDue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x170000 : g_fence + 0x16fffc))
#else
extern u8 g_armcLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_savedMechPartIds_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x172000 : g_fence + 0x171fec))
#else
extern int g_savedMechPartIds_v[5];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusTargetKeep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x174000 : g_fence + 0x173ffc))
#else
extern u8 g_itemBonusTargetKeep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLastPart_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x176000 : g_fence + 0x175ffc))
#else
extern u8 g_armcLastPart_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusRechargeTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x178000 : g_fence + 0x177ffc))
#else
extern u8 g_itemBonusRechargeTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusLockOn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x17a000 : g_fence + 0x179ffc))
#else
extern u8 g_itemBonusLockOn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_legList_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x17c000 : g_fence + 0x17bf38))
#else
extern int g_legList_v[50];
#endif
#ifdef AXIS_FENCE
#define g_armList_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x17e000 : g_fence + 0x17df38))
#else
extern int g_armList_v[50];
#endif
#ifdef AXIS_FENCE
#define g_armcViewPoints_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x180000 : g_fence + 0x17ffa0))
#else
extern u32 g_armcViewPoints_v[24];
#endif
#ifdef AXIS_FENCE
#define g_armCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x182000 : g_fence + 0x181ffc))
#else
extern u8 g_armCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_legCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x184000 : g_fence + 0x183ffc))
#else
extern u8 g_legCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_coloursChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x186000 : g_fence + 0x185ffc))
#else
extern u8 g_coloursChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechDetectionRange_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x188000 : g_fence + 0x187ffc))
#else
extern u8 g_mechDetectionRange_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechDetectionAngle_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x18a000 : g_fence + 0x189ffc))
#else
extern u8 g_mechDetectionAngle_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechHackingLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x18c000 : g_fence + 0x18bffc))
#else
extern u8 g_mechHackingLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechLockOnTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x18e000 : g_fence + 0x18dffc))
#else
extern u8 g_mechLockOnTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechTargetKeepTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x190000 : g_fence + 0x18fffc))
#else
extern u8 g_mechTargetKeepTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechPartStats_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x192000 : g_fence + 0x191fe4))
#else
extern int g_mechPartStats_v[7];
#endif
#ifdef AXIS_FENCE
#define g_mechMobility_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x194000 : g_fence + 0x193ffc))
#else
extern u8 g_mechMobility_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechLegsValue2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x196000 : g_fence + 0x195ffc))
#else
extern u8 g_mechLegsValue2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechLegsSpeedCorrection_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x198000 : g_fence + 0x197ffc))
#else
extern u8 g_mechLegsSpeedCorrection_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechLegsBonus1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x19a000 : g_fence + 0x199ffc))
#else
extern u8 g_mechLegsBonus1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechLegsBonus2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x19c000 : g_fence + 0x19bffc))
#else
extern u8 g_mechLegsBonus2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechLegsBonus3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x19e000 : g_fence + 0x19dffc))
#else
extern u8 g_mechLegsBonus3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedMechStat_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a0000 : g_fence + 0x19fffc))
#else
extern u8 g_unusedMechStat_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechBoosterEnergy_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a2000 : g_fence + 0x1a1ffc))
#else
extern u8 g_mechBoosterEnergy_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechBoosterRecharge_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a4000 : g_fence + 0x1a3ffc))
#else
extern u8 g_mechBoosterRecharge_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechBoosterValue3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a6000 : g_fence + 0x1a5ffc))
#else
extern u8 g_mechBoosterValue3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechSpeeds_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x1a8000 : g_fence + 0x1a7fe8))
#else
extern float g_mechSpeeds_v[6];
#endif
#ifdef AXIS_FENCE
#define g_mechSettings_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1aa000 : g_fence + 0x1a9fe8))
#else
extern int g_mechSettings_v[6];
#endif
#ifdef AXIS_FENCE
#define g_boosterCursor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ac000 : g_fence + 0x1abffc))
#else
extern u8 g_boosterCursor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusMissile_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ae000 : g_fence + 0x1adffc))
#else
extern u8 g_itemBonusMissile_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcColourRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1b0000 : g_fence + 0x1afee0))
#else
extern int g_armcColourRects_v[72];
#endif
#ifdef AXIS_FENCE
#define g_mechChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b2000 : g_fence + 0x1b1ffc))
#else
extern u8 g_mechChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b4000 : g_fence + 0x1b3ffc))
#else
extern u8 g_chestCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b6000 : g_fence + 0x1b5ffc))
#else
extern u8 g_armcChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusShield_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b8000 : g_fence + 0x1b7ffc))
#else
extern u8 g_itemBonusShield_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonus30mm_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ba000 : g_fence + 0x1b9ffc))
#else
extern u8 g_itemBonus30mm_v[4];
#endif
#ifdef AXIS_FENCE
#define g_slotTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1bc000 : g_fence + 0x1bbfe4))
#else
extern int g_slotTextures_v[7];
#endif
#ifdef AXIS_FENCE
#define g_headCursor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1be000 : g_fence + 0x1bdffc))
#else
extern u8 g_headCursor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcStatsPanelLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c0000 : g_fence + 0x1bfffc))
#else
extern u8 g_armcStatsPanelLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcStatsPanelTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c2000 : g_fence + 0x1c1ffc))
#else
extern u8 g_armcStatsPanelTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcSliderLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c4000 : g_fence + 0x1c3ffc))
#else
extern u8 g_armcSliderLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcStatsPanelBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c6000 : g_fence + 0x1c5ffc))
#else
extern u8 g_armcStatsPanelBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusActiveTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c8000 : g_fence + 0x1c7ffc))
#else
extern u8 g_itemBonusActiveTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_extraListTable_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1ca000 : g_fence + 0x1c9f38))
#else
extern int g_extraListTable_v[50];
#endif
#ifdef AXIS_FENCE
#define g_chestList_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1cc000 : g_fence + 0x1cbf38))
#else
extern int g_chestList_v[50];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ce000 : g_fence + 0x1cdffc))
#else
extern u8 g_unusedArmcWord3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_boosterPanelName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x1d0000 : g_fence + 0x1cffc0))
#else
extern char g_boosterPanelName_v[64];
#endif
#ifdef AXIS_FENCE
#define g_boosterStats_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x1d2000 : g_fence + 0x1d1fd8))
#else
extern float g_boosterStats_v[10];
#endif
#ifdef AXIS_FENCE
#define g_armcSpin_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d4000 : g_fence + 0x1d3ffc))
#else
extern u8 g_armcSpin_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusWeightLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d6000 : g_fence + 0x1d5ffc))
#else
extern u8 g_itemBonusWeightLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusHacking_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d8000 : g_fence + 0x1d7ffc))
#else
extern u8 g_itemBonusHacking_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headPanelName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x1da000 : g_fence + 0x1d9fc0))
#else
extern char g_headPanelName_v[64];
#endif
#ifdef AXIS_FENCE
#define g_headDetectionRange_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1dc000 : g_fence + 0x1dbffc))
#else
extern u8 g_headDetectionRange_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headDetectionAngle_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1de000 : g_fence + 0x1ddffc))
#else
extern u8 g_headDetectionAngle_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headHackingLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e0000 : g_fence + 0x1dfffc))
#else
extern u8 g_headHackingLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headLockOnTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e2000 : g_fence + 0x1e1ffc))
#else
extern u8 g_headLockOnTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headTargetKeepTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e4000 : g_fence + 0x1e3ffc))
#else
extern u8 g_headTargetKeepTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headWeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e6000 : g_fence + 0x1e5ffc))
#else
extern u8 g_headWeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLeaving_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e8000 : g_fence + 0x1e7ffc))
#else
extern u8 g_armcLeaving_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ea000 : g_fence + 0x1e9ffc))
#else
extern u8 g_unusedArmcWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_savedMechSettings_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1ec000 : g_fence + 0x1ebfe8))
#else
extern int g_savedMechSettings_v[6];
#endif
#ifdef AXIS_FENCE
#define g_progressWentUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ee000 : g_fence + 0x1edffc))
#else
extern u8 g_progressWentUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestCursor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f0000 : g_fence + 0x1efffc))
#else
extern u8 g_chestCursor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcCameraBox_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x1f2000 : g_fence + 0x1f1f68))
#else
extern u32 g_armcCameraBox_v[38];
#endif
#ifdef AXIS_FENCE
#define g_armcZoom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f4000 : g_fence + 0x1f3ffc))
#else
extern u8 g_armcZoom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_colourChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f6000 : g_fence + 0x1f5ffc))
#else
extern u8 g_colourChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcHideInterface_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f8000 : g_fence + 0x1f7ffc))
#else
extern u8 g_armcHideInterface_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fpsSecondStart_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1fa000 : g_fence + 0x1f9ff8))
#else
extern u8 g_fpsSecondStart_v[8];
#endif
#ifdef AXIS_FENCE
#define g_menuFrameCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1fc000 : g_fence + 0x1fbffc))
#else
extern u8 g_menuFrameCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_messageBoxArgs_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1fe000 : g_fence + 0x1fdffc))
#else
extern u8 g_messageBoxArgs_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedStartupWord3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x200000 : g_fence + 0x1ffffc))
#else
extern u8 g_unusedStartupWord3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lastFrameClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x202000 : g_fence + 0x201ff8))
#else
extern u8 g_lastFrameClock_v[8];
#endif
#ifdef AXIS_FENCE
#define g_fpsFrameClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x204000 : g_fence + 0x203ff8))
#else
extern u8 g_fpsFrameClock_v[8];
#endif
#ifdef AXIS_FENCE
#define g_frameRate_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x206000 : g_fence + 0x205ff8))
#else
extern u8 g_frameRate_v[8];
#endif
#ifdef AXIS_FENCE
#define g_unusedStartupWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x208000 : g_fence + 0x207ffc))
#else
extern u8 g_unusedStartupWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fpsSecondSoFar_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x20a000 : g_fence + 0x209ff8))
#else
extern u8 g_fpsSecondSoFar_v[8];
#endif
#ifdef AXIS_FENCE
#define g_fps_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x20c000 : g_fence + 0x20bffc))
#else
extern u8 g_fps_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuVolume_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x20e000 : g_fence + 0x20dffc))
#else
extern u8 g_menuVolume_v[4];
#endif
#ifdef AXIS_FENCE
#define g_launcherCheck_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x210000 : g_fence + 0x20fff4))
#else
extern u8 g_launcherCheck_v[12];
#endif
#ifdef AXIS_FENCE
#define g_loadStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x212000 : g_fence + 0x211ffc))
#else
extern u8 g_loadStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursorBlink_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x214000 : g_fence + 0x213ffc))
#else
extern u8 g_cursorBlink_v[4];
#endif
#ifdef AXIS_FENCE
#define g_introZoom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x216000 : g_fence + 0x215ffc))
#else
extern u8 g_introZoom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPanelMoving_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x218000 : g_fence + 0x217ffc))
#else
extern u8 g_setupPanelMoving_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fxStatusTexts_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x21a000 : g_fence + 0x219f9c))
#else
extern char g_fxStatusTexts_v[100];
#endif
#ifdef AXIS_FENCE
#define g_setupTab_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x21c000 : g_fence + 0x21bffc))
#else
extern u8 g_setupTab_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupSoundRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x21e000 : g_fence + 0x21dff0))
#else
extern int g_setupSoundRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupColourDim_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x220000 : g_fence + 0x21fff0))
#else
extern u32 g_setupColourDim_v[4];
#endif
#ifdef AXIS_FENCE
#define g_simpleMenuTexts_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x222000 : g_fence + 0x221f9c))
#else
extern char g_simpleMenuTexts_v[100];
#endif
#ifdef AXIS_FENCE
#define g_crosshairName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x224000 : g_fence + 0x223fe0))
#else
extern char g_crosshairName_v[32];
#endif
#ifdef AXIS_FENCE
#define g_setupPressedClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x226000 : g_fence + 0x225ffc))
#else
extern u8 g_setupPressedClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_graphicEdited_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x228000 : g_fence + 0x227fe4))
#else
extern u32 g_graphicEdited_v[7];
#endif
#ifdef AXIS_FENCE
#define g_colourDepthTexts_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x22a000 : g_fence + 0x229f9c))
#else
extern char g_colourDepthTexts_v[100];
#endif
#ifdef AXIS_FENCE
#define g_viewFpsTexts_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x22c000 : g_fence + 0x22bf9c))
#else
extern char g_viewFpsTexts_v[100];
#endif
#ifdef AXIS_FENCE
#define g_linearFilterTexts_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x22e000 : g_fence + 0x22df9c))
#else
extern char g_linearFilterTexts_v[100];
#endif
#ifdef AXIS_FENCE
#define g_bindPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x230000 : g_fence + 0x22fffc))
#else
extern u8 g_bindPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x232000 : g_fence + 0x231ffc))
#else
extern u8 g_setupPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupSoundRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x234000 : g_fence + 0x233f60))
#else
extern int g_setupSoundRects_v[40];
#endif
#ifdef AXIS_FENCE
#define g_setupTunnelDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x236000 : g_fence + 0x235ffc))
#else
extern u8 g_setupTunnelDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupSliderRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x238000 : g_fence + 0x237fd0))
#else
extern int g_setupSliderRects_v[12];
#endif
#ifdef AXIS_FENCE
#define g_bindWaiting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x23a000 : g_fence + 0x239ffc))
#else
extern u8 g_bindWaiting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupOptionsRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x23c000 : g_fence + 0x23bff0))
#else
extern int g_setupOptionsRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupOptionsRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x23e000 : g_fence + 0x23df70))
#else
extern int g_setupOptionsRects_v[36];
#endif
#ifdef AXIS_FENCE
#define g_setupControlRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x240000 : g_fence + 0x23fff0))
#else
extern int g_setupControlRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPressed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x242000 : g_fence + 0x241ffc))
#else
extern u8 g_setupPressed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_soundEdited_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x244000 : g_fence + 0x243ff0))
#else
extern int g_soundEdited_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupControlRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x246000 : g_fence + 0x245ee0))
#else
extern int g_setupControlRects_v[72];
#endif
#ifdef AXIS_FENCE
#define g_setupTunnelAlpha_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x248000 : g_fence + 0x247ffc))
#else
extern u8 g_setupTunnelAlpha_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPanelPos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x24a000 : g_fence + 0x249ffc))
#else
extern u8 g_setupPanelPos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bindRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x24c000 : g_fence + 0x24bffc))
#else
extern u8 g_bindRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupColourLit_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x24e000 : g_fence + 0x24dff0))
#else
extern u32 g_setupColourLit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mipMapTexts_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x250000 : g_fence + 0x24ff9c))
#else
extern char g_mipMapTexts_v[100];
#endif
#ifdef AXIS_FENCE
#define g_controlsEdit_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x252000 : g_fence + 0x251ef0))
#else
extern int g_controlsEdit_v[68];
#endif
#ifdef AXIS_FENCE
#define g_emblemPulse_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x254000 : g_fence + 0x253ffc))
#else
extern u8 g_emblemPulse_v[4];
#endif
#ifdef AXIS_FENCE
#define g_emblemAlpha_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x256000 : g_fence + 0x255ffc))
#else
extern u8 g_emblemAlpha_v[4];
#endif
#ifdef AXIS_FENCE
#define g_logoFade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x258000 : g_fence + 0x257ffc))
#else
extern u8 g_logoFade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_logoFadeLate_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x25a000 : g_fence + 0x259ffc))
#else
extern u8 g_logoFadeLate_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursorBlinkTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x25c000 : g_fence + 0x25bffc))
#else
extern u8 g_cursorBlinkTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveStarted_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x25e000 : g_fence + 0x25dffc))
#else
extern u8 g_armcMoveStarted_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuCamX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x260000 : g_fence + 0x25fffc))
#else
extern u8 g_menuCamX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_freeCamHeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x262000 : g_fence + 0x261ffc))
#else
extern u8 g_freeCamHeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuCamZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x264000 : g_fence + 0x263ffc))
#else
extern u8 g_menuCamZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveEyeX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x266000 : g_fence + 0x265ffc))
#else
extern u8 g_armcMoveEyeX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveEyeY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x268000 : g_fence + 0x267ffc))
#else
extern u8 g_armcMoveEyeY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveEyeZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x26a000 : g_fence + 0x269ffc))
#else
extern u8 g_armcMoveEyeZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookSin_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x26c000 : g_fence + 0x26bffc))
#else
extern u8 g_armcLookSin_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookTilt_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x26e000 : g_fence + 0x26dffc))
#else
extern u8 g_armcLookTilt_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookCos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x270000 : g_fence + 0x26fffc))
#else
extern u8 g_armcLookCos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveTargetX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x272000 : g_fence + 0x271ffc))
#else
extern u8 g_armcMoveTargetX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveTargetY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x274000 : g_fence + 0x273ffc))
#else
extern u8 g_armcMoveTargetY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveTargetZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x276000 : g_fence + 0x275ffc))
#else
extern u8 g_armcMoveTargetZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_debugValue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x278000 : g_fence + 0x277ffc))
#else
extern u8 g_debugValue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcMoveWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x27a000 : g_fence + 0x279ffc))
#else
extern u8 g_unusedArmcMoveWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedPostMatchFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x27c000 : g_fence + 0x27bffc))
#else
extern u8 g_unusedPostMatchFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_watchChatOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x27e000 : g_fence + 0x27dffc))
#else
extern u8 g_watchChatOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x280000 : g_fence + 0x27fffc))
#else
extern u8 g_titleLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titlePoints_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x282000 : g_fence + 0x281ffc))
#else
extern u8 g_titlePoints_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleRating_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x284000 : g_fence + 0x283ffc))
#else
extern u8 g_titleRating_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleScore_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x286000 : g_fence + 0x285ffc))
#else
extern u8 g_titleScore_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleWins_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x288000 : g_fence + 0x287ffc))
#else
extern u8 g_titleWins_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleLosses_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x28a000 : g_fence + 0x289ffc))
#else
extern u8 g_titleLosses_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikMouse1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x28c000 : g_fence + 0x28bffc))
#else
extern u8 g_dikMouse1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuFramePhase_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x28e000 : g_fence + 0x28dffc))
#else
extern u8 g_menuFramePhase_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverAddressArg_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x290000 : g_fence + 0x28fc00))
#else
extern char g_serverAddressArg_v[1024];
#endif
#ifdef AXIS_FENCE
#define g_enteringMenus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x292000 : g_fence + 0x291ffc))
#else
extern u8 g_enteringMenus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuFrameTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x294000 : g_fence + 0x293ff8))
#else
extern int g_menuFrameTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_showCmd_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x296000 : g_fence + 0x295ffc))
#else
extern u8 g_showCmd_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x298000 : g_fence + 0x297ffc))
#else
extern u8 g_dikNumpad4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x29a000 : g_fence + 0x299ffc))
#else
extern u8 g_dikNumpad3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad6_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x29c000 : g_fence + 0x29bffc))
#else
extern u8 g_dikNumpad6_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad5_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x29e000 : g_fence + 0x29dffc))
#else
extern u8 g_dikNumpad5_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad8_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a0000 : g_fence + 0x29fffc))
#else
extern u8 g_dikNumpad8_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad7_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a2000 : g_fence + 0x2a1ffc))
#else
extern u8 g_dikNumpad7_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad9_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a4000 : g_fence + 0x2a3ffc))
#else
extern u8 g_dikNumpad9_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomFade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a6000 : g_fence + 0x2a5ffc))
#else
extern u8 g_roomFade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad0_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a8000 : g_fence + 0x2a7ffc))
#else
extern u8 g_dikNumpad0_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuOutlines_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x2aa000 : g_fence + 0x2a9ef8))
#else
extern int g_mainMenuOutlines_v[66];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpadDot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ac000 : g_fence + 0x2abffc))
#else
extern u8 g_dikNumpadDot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ae000 : g_fence + 0x2adffc))
#else
extern u8 g_dikNumpad2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpad1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b0000 : g_fence + 0x2afffc))
#else
extern u8 g_dikNumpad1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumLock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b2000 : g_fence + 0x2b1ffc))
#else
extern u8 g_dikNumLock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainWindow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b4000 : g_fence + 0x2b3ffc))
#else
extern u8 g_mainWindow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x2b6000 : g_fence + 0x2b5fd0))
#else
extern char g_playerName_v[48];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameSetUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b8000 : g_fence + 0x2b7ffc))
#else
extern u8 g_arenaGameSetUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_timerTick_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ba000 : g_fence + 0x2b9ff8))
#else
extern u8 g_timerTick_v[8];
#endif
#ifdef AXIS_FENCE
#define g_connectStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2bc000 : g_fence + 0x2bbffc))
#else
extern u8 g_connectStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mousePos_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x2be000 : g_fence + 0x2bdff8))
#else
extern int g_mousePos_v[2];
#endif
#ifdef AXIS_FENCE
#define g_mouseWheelTurned_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c0000 : g_fence + 0x2bfffc))
#else
extern u8 g_mouseWheelTurned_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mouseWheel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c2000 : g_fence + 0x2c1ffc))
#else
extern u8 g_mouseWheel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mouseClicked_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x2c4000 : g_fence + 0x2c3ff4))
#else
extern int g_mouseClicked_v[3];
#endif
#ifdef AXIS_FENCE
#define g_mouseButtonsHeld_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x2c6000 : g_fence + 0x2c5ff4))
#else
extern int g_mouseButtonsHeld_v[3];
#endif
#ifdef AXIS_FENCE
#define g_dikInsert_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c8000 : g_fence + 0x2c7ffc))
#else
extern u8 g_dikInsert_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikPeriod_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ca000 : g_fence + 0x2c9ffc))
#else
extern u8 g_dikPeriod_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuTunnelSpeed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2cc000 : g_fence + 0x2cbffc))
#else
extern u8 g_menuTunnelSpeed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerCorporation_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ce000 : g_fence + 0x2cdffc))
#else
extern u8 g_playerCorporation_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerSex_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d0000 : g_fence + 0x2cfffc))
#else
extern u8 g_playerSex_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchPlayerName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x2d2000 : g_fence + 0x2d1fe0))
#else
extern char g_matchPlayerName_v[32];
#endif
#ifdef AXIS_FENCE
#define g_mapInfoDir_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x2d4000 : g_fence + 0x2d3efb))
#else
extern char g_mapInfoDir_v[261];
#endif
#ifdef AXIS_FENCE
#define g_controls_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x2d6000 : g_fence + 0x2d5ef0))
#else
extern int g_controls_v[68];
#endif
#ifdef AXIS_FENCE
#define g_tunnelPulseStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d8000 : g_fence + 0x2d7ffc))
#else
extern u8 g_tunnelPulseStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuScaleY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2da000 : g_fence + 0x2d9ffc))
#else
extern u8 g_menuScaleY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverAnswerIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2dc000 : g_fence + 0x2dbffc))
#else
extern u8 g_serverAnswerIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleShown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2de000 : g_fence + 0x2ddffc))
#else
extern u8 g_titleShown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuEye_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x2e0000 : g_fence + 0x2dfff4))
#else
extern float g_menuEye_v[3];
#endif
#ifdef AXIS_FENCE
#define g_timerFrequency_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e2000 : g_fence + 0x2e1ff8))
#else
extern u8 g_timerFrequency_v[8];
#endif
#ifdef AXIS_FENCE
#define g_dikLWin_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e4000 : g_fence + 0x2e3ffc))
#else
extern u8 g_dikLWin_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursorFrame_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e6000 : g_fence + 0x2e5ffc))
#else
extern u8 g_cursorFrame_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x2e8000 : g_fence + 0x2e7ff8))
#else
extern int g_arenaMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_exitCode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ea000 : g_fence + 0x2e9ffc))
#else
extern u8 g_exitCode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikInsert_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ec000 : g_fence + 0x2ebffc))
#else
extern u8 g_dikInsert_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_vkTable_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x2ee000 : g_fence + 0x2edf1c))
#else
extern int g_vkTable_v[57];
#endif
#ifdef AXIS_FENCE
#define g_panelGlowStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2f0000 : g_fence + 0x2efffc))
#else
extern u8 g_panelGlowStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hudLayerBLeft_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x2f2000 : g_fence + 0x2f1e20))
#else
extern float g_hudLayerBLeft_v[120];
#endif
#ifdef AXIS_FENCE
#define g_hudLayerBTop_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x2f4000 : g_fence + 0x2f3e20))
#else
extern float g_hudLayerBTop_v[120];
#endif
#ifdef AXIS_FENCE
#define g_lobbyListRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2f6000 : g_fence + 0x2f5ffc))
#else
extern u8 g_lobbyListRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_messageBoxLine_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x2f8000 : g_fence + 0x2f7fb0))
#else
extern char g_messageBoxLine_v[80];
#endif
#ifdef AXIS_FENCE
#define g_camPoints_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x2fa000 : g_fence + 0x2f9fb0))
#else
extern float g_camPoints_v[20];
#endif
#ifdef AXIS_FENCE
#define g_dikF11_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2fc000 : g_fence + 0x2fbffc))
#else
extern u8 g_dikF11_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF12_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2fe000 : g_fence + 0x2fdffc))
#else
extern u8 g_dikF12_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF10_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x300000 : g_fence + 0x2ffffc))
#else
extern u8 g_dikF10_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedMenuReturnWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x302000 : g_fence + 0x301ffc))
#else
extern u8 g_unusedMenuReturnWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x304000 : g_fence + 0x303ffc))
#else
extern u8 g_dikNone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fragLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x306000 : g_fence + 0x305ffc))
#else
extern u8 g_fragLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLBracket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x308000 : g_fence + 0x307ffc))
#else
extern u8 g_dikLBracket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dialogPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x30a000 : g_fence + 0x309ffc))
#else
extern u8 g_dialogPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ladderMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x30c000 : g_fence + 0x30bff8))
#else
extern int g_ladderMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_dikPageUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x30e000 : g_fence + 0x30dffc))
#else
extern u8 g_dikPageUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursorFrameTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x310000 : g_fence + 0x30fffc))
#else
extern u8 g_cursorFrameTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupTopOutlines_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x312000 : g_fence + 0x311f50))
#else
extern int g_setupTopOutlines_v[44];
#endif
#ifdef AXIS_FENCE
#define g_roomSettingsName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x314000 : g_fence + 0x313fd0))
#else
extern char g_roomSettingsName_v[48];
#endif
#ifdef AXIS_FENCE
#define g_dikRAlt_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x316000 : g_fence + 0x315ffc))
#else
extern u8 g_dikRAlt_v[4];
#endif
#ifdef AXIS_FENCE
#define g_characterTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x318000 : g_fence + 0x317ffc))
#else
extern u8 g_characterTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleFrames_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x31a000 : g_fence + 0x319ffc))
#else
extern u8 g_titleFrames_v[4];
#endif
#ifdef AXIS_FENCE
#define g_screenH_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x31c000 : g_fence + 0x31bffc))
#else
extern u8 g_screenH_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik0_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x31e000 : g_fence + 0x31dffc))
#else
extern u8 g_dik0_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fovKeys_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x320000 : g_fence + 0x31fffc))
#else
extern u8 g_fovKeys_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x322000 : g_fence + 0x321ffc))
#else
extern u8 g_dik1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x324000 : g_fence + 0x323ffc))
#else
extern u8 g_dik2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x326000 : g_fence + 0x325ffc))
#else
extern u8 g_dik3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hudFontBottom_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x328000 : g_fence + 0x327c00))
#else
extern float g_hudFontBottom_v[256];
#endif
#ifdef AXIS_FENCE
#define g_dik4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x32a000 : g_fence + 0x329ffc))
#else
extern u8 g_dik4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hudFontRight_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x32c000 : g_fence + 0x32bc00))
#else
extern float g_hudFontRight_v[256];
#endif
#ifdef AXIS_FENCE
#define g_dik5_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x32e000 : g_fence + 0x32dffc))
#else
extern u8 g_dik5_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik6_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x330000 : g_fence + 0x32fffc))
#else
extern u8 g_dik6_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik7_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x332000 : g_fence + 0x331ffc))
#else
extern u8 g_dik7_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik8_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x334000 : g_fence + 0x333ffc))
#else
extern u8 g_dik8_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik9_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x336000 : g_fence + 0x335ffc))
#else
extern u8 g_dik9_v[4];
#endif
#ifdef AXIS_FENCE
#define g_crosshairTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x338000 : g_fence + 0x337ffc))
#else
extern u8 g_crosshairTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_soundSettings_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x33a000 : g_fence + 0x339ff0))
#else
extern int g_soundSettings_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpadSlash_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x33c000 : g_fence + 0x33bffc))
#else
extern u8 g_dikNumpadSlash_v[4];
#endif
#ifdef AXIS_FENCE
#define g_windowClass_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x33e000 : g_fence + 0x33dfd8))
#else
extern u8 g_windowClass_v[40];
#endif
#ifdef AXIS_FENCE
#define g_menuTunnelTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x340000 : g_fence + 0x33fffc))
#else
extern u8 g_menuTunnelTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikA_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x342000 : g_fence + 0x341ffc))
#else
extern u8 g_dikA_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikB_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x344000 : g_fence + 0x343ffc))
#else
extern u8 g_dikB_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikC_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x346000 : g_fence + 0x345ffc))
#else
extern u8 g_dikC_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikD_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x348000 : g_fence + 0x347ffc))
#else
extern u8 g_dikD_v[4];
#endif
#ifdef AXIS_FENCE
#define g_font5Bottom_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x34a000 : g_fence + 0x349c00))
#else
extern float g_font5Bottom_v[256];
#endif
#ifdef AXIS_FENCE
#define g_dikE_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x34c000 : g_fence + 0x34bffc))
#else
extern u8 g_dikE_v[4];
#endif
#ifdef AXIS_FENCE
#define g_font5Right_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x34e000 : g_fence + 0x34dc00))
#else
extern float g_font5Right_v[256];
#endif
#ifdef AXIS_FENCE
#define g_dikF_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x350000 : g_fence + 0x34fffc))
#else
extern u8 g_dikF_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikG_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x352000 : g_fence + 0x351ffc))
#else
extern u8 g_dikG_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikH_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x354000 : g_fence + 0x353ffc))
#else
extern u8 g_dikH_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikI_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x356000 : g_fence + 0x355ffc))
#else
extern u8 g_dikI_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikJ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x358000 : g_fence + 0x357ffc))
#else
extern u8 g_dikJ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_scroll_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x35a000 : g_fence + 0x359ffc))
#else
extern u8 g_scroll_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikK_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x35c000 : g_fence + 0x35bffc))
#else
extern u8 g_dikK_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikL_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x35e000 : g_fence + 0x35dffc))
#else
extern u8 g_dikL_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikM_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x360000 : g_fence + 0x35fffc))
#else
extern u8 g_dikM_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikN_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x362000 : g_fence + 0x361ffc))
#else
extern u8 g_dikN_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikO_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x364000 : g_fence + 0x363ffc))
#else
extern u8 g_dikO_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikP_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x366000 : g_fence + 0x365ffc))
#else
extern u8 g_dikP_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikQ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x368000 : g_fence + 0x367ffc))
#else
extern u8 g_dikQ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikR_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x36a000 : g_fence + 0x369ffc))
#else
extern u8 g_dikR_v[4];
#endif
#ifdef AXIS_FENCE
#define g_screenCentreX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x36c000 : g_fence + 0x36bffc))
#else
extern u8 g_screenCentreX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikS_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x36e000 : g_fence + 0x36dffc))
#else
extern u8 g_dikS_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikT_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x370000 : g_fence + 0x36fffc))
#else
extern u8 g_dikT_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursorTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x372000 : g_fence + 0x371ffc))
#else
extern u8 g_cursorTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikU_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x374000 : g_fence + 0x373ffc))
#else
extern u8 g_dikU_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikV_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x376000 : g_fence + 0x375ffc))
#else
extern u8 g_dikV_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikW_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x378000 : g_fence + 0x377ffc))
#else
extern u8 g_dikW_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x37a000 : g_fence + 0x379ffc))
#else
extern u8 g_dikX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x37c000 : g_fence + 0x37bffc))
#else
extern u8 g_dikY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x37e000 : g_fence + 0x37dffc))
#else
extern u8 g_dikZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hudLayerALeft_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x380000 : g_fence + 0x37fe70))
#else
extern float g_hudLayerALeft_v[100];
#endif
#ifdef AXIS_FENCE
#define g_hudLayerATop_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x382000 : g_fence + 0x381e70))
#else
extern float g_hudLayerATop_v[100];
#endif
#ifdef AXIS_FENCE
#define g_chatFieldFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x384000 : g_fence + 0x383ffc))
#else
extern u8 g_chatFieldFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tunnelTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x386000 : g_fence + 0x385ffc))
#else
extern u8 g_tunnelTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewAspect_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x388000 : g_fence + 0x387ffc))
#else
extern u8 g_viewAspect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_texture64x64_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x38a000 : g_fence + 0x389ebc))
#else
extern u8 g_texture64x64_v[840004];
#endif
#ifdef AXIS_FENCE
#define g_projMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x459000 : g_fence + 0x458ffc))
#else
extern u8 g_projMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEnd_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x45b000 : g_fence + 0x45affc))
#else
extern u8 g_dikEnd_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x45d000 : g_fence + 0x45cffc))
#else
extern u8 g_matchMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_perfCounter_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x45f000 : g_fence + 0x45effc))
#else
extern u8 g_perfCounter_v[4];
#endif
#ifdef AXIS_FENCE
#define g_timerHigh_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x461000 : g_fence + 0x460ffc))
#else
extern u8 g_timerHigh_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapAbouts_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x463000 : g_fence + 0x4620c0))
#else
extern char g_mapAbouts_v[8000];
#endif
#ifdef AXIS_FENCE
#define g_hudFontTop_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x466000 : g_fence + 0x465c00))
#else
extern float g_hudFontTop_v[256];
#endif
#ifdef AXIS_FENCE
#define g_hudFontLeft_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x468000 : g_fence + 0x467c00))
#else
extern float g_hudFontLeft_v[256];
#endif
#ifdef AXIS_FENCE
#define g_font5Top_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x46a000 : g_fence + 0x469c00))
#else
extern float g_font5Top_v[256];
#endif
#ifdef AXIS_FENCE
#define g_font5Left_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x46c000 : g_fence + 0x46bc00))
#else
extern float g_font5Left_v[256];
#endif
#ifdef AXIS_FENCE
#define g_listRefreshPeriod_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x46e000 : g_fence + 0x46dffc))
#else
extern u8 g_listRefreshPeriod_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x470000 : g_fence + 0x46ffe0))
#else
extern char g_arenaGameName_v[32];
#endif
#ifdef AXIS_FENCE
#define g_ctrlMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x472000 : g_fence + 0x471ff8))
#else
extern int g_ctrlMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_dikPageDown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x474000 : g_fence + 0x473ffc))
#else
extern u8 g_dikPageDown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_screenW_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x476000 : g_fence + 0x475ffc))
#else
extern u8 g_screenW_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hudLayerARight_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x478000 : g_fence + 0x477e70))
#else
extern float g_hudLayerARight_v[100];
#endif
#ifdef AXIS_FENCE
#define g_roomRecName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x47a000 : g_fence + 0x479fd0))
#else
extern char g_roomRecName_v[48];
#endif
#ifdef AXIS_FENCE
#define g_hudLayerABottom_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x47c000 : g_fence + 0x47be70))
#else
extern float g_hudLayerABottom_v[100];
#endif
#ifdef AXIS_FENCE
#define g_lobbyTopOutlines_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x47e000 : g_fence + 0x47df50))
#else
extern int g_lobbyTopOutlines_v[44];
#endif
#ifdef AXIS_FENCE
#define g_dikSpace_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x480000 : g_fence + 0x47fffc))
#else
extern u8 g_dikSpace_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchRunning_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x482000 : g_fence + 0x481ffc))
#else
extern u8 g_matchRunning_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikPageUp_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x484000 : g_fence + 0x483ffc))
#else
extern u8 g_dikPageUp_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_texture128x64_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x486000 : g_fence + 0x485ebc))
#else
extern u8 g_texture128x64_v[840004];
#endif
#ifdef AXIS_FENCE
#define g_desktopWidth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x555000 : g_fence + 0x554ffc))
#else
extern u8 g_desktopWidth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaMapCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x557000 : g_fence + 0x556ffc))
#else
extern u8 g_arenaMapCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netRole_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x559000 : g_fence + 0x558ffc))
#else
extern u8 g_netRole_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpadPlus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x55b000 : g_fence + 0x55affc))
#else
extern u8 g_dikNumpadPlus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lastScreen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x55d000 : g_fence + 0x55cffc))
#else
extern u8 g_lastScreen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikScrollLock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x55f000 : g_fence + 0x55effc))
#else
extern u8 g_dikScrollLock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_quitAsked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x561000 : g_fence + 0x560ffc))
#else
extern u8 g_quitAsked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hInstance_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x563000 : g_fence + 0x562ffc))
#else
extern u8 g_hInstance_v[4];
#endif
#ifdef AXIS_FENCE
#define g_timerShift_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x565000 : g_fence + 0x564ffc))
#else
extern u8 g_timerShift_v[4];
#endif
#ifdef AXIS_FENCE
#define g_nextScreen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x567000 : g_fence + 0x566ffc))
#else
extern u8 g_nextScreen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLShift_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x569000 : g_fence + 0x568ffc))
#else
extern u8 g_dikLShift_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikApps_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x56b000 : g_fence + 0x56affc))
#else
extern u8 g_dikApps_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEnter_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x56d000 : g_fence + 0x56cffc))
#else
extern u8 g_dikEnter_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x56f000 : g_fence + 0x56effc))
#else
extern u8 g_gameCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_highlightX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x571000 : g_fence + 0x570ffc))
#else
extern u8 g_highlightX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatHistory_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x573000 : g_fence + 0x572400))
#else
extern char g_chatHistory_v[3072];
#endif
#ifdef AXIS_FENCE
#define g_highlightY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x575000 : g_fence + 0x574ffc))
#else
extern u8 g_highlightY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuTunnel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x577000 : g_fence + 0x576ffc))
#else
extern u8 g_menuTunnel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikPrintScreen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x579000 : g_fence + 0x578ffc))
#else
extern u8 g_dikPrintScreen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_font8Right_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x57b000 : g_fence + 0x57ac00))
#else
extern float g_font8Right_v[256];
#endif
#ifdef AXIS_FENCE
#define g_font8Bottom_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x57d000 : g_fence + 0x57cc00))
#else
extern float g_font8Bottom_v[256];
#endif
#ifdef AXIS_FENCE
#define g_dikComma_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x57f000 : g_fence + 0x57effc))
#else
extern u8 g_dikComma_v[4];
#endif
#ifdef AXIS_FENCE
#define g_keysBlocked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x581000 : g_fence + 0x580ffc))
#else
extern u8 g_keysBlocked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuLook_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x583000 : g_fence + 0x582ff4))
#else
extern float g_menuLook_v[3];
#endif
#ifdef AXIS_FENCE
#define g_dikZ_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x585000 : g_fence + 0x584ffc))
#else
extern u8 g_dikZ_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewAngle_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x587000 : g_fence + 0x586ffc))
#else
extern u8 g_viewAngle_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikTab_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x589000 : g_fence + 0x588ffc))
#else
extern u8 g_dikTab_v[4];
#endif
#ifdef AXIS_FENCE
#define g_screenCentreY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x58b000 : g_fence + 0x58affc))
#else
extern u8 g_screenCentreY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_panelHovered_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x58d000 : g_fence + 0x58cffc))
#else
extern u8 g_panelHovered_v[4];
#endif
#ifdef AXIS_FENCE
#define g_paused_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x58f000 : g_fence + 0x58effc))
#else
extern u8 g_paused_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEscape_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x591000 : g_fence + 0x590ffc))
#else
extern u8 g_dikEscape_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpadEnter_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x593000 : g_fence + 0x592ffc))
#else
extern u8 g_dikNumpadEnter_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLCtrl_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x595000 : g_fence + 0x594ffc))
#else
extern u8 g_dikLCtrl_v[4];
#endif
#ifdef AXIS_FENCE
#define g_font8Top_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x597000 : g_fence + 0x596c00))
#else
extern float g_font8Top_v[256];
#endif
#ifdef AXIS_FENCE
#define g_font8Left_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x599000 : g_fence + 0x598c00))
#else
extern float g_font8Left_v[256];
#endif
#ifdef AXIS_FENCE
#define g_menuScaleX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x59b000 : g_fence + 0x59affc))
#else
extern u8 g_menuScaleX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x59d000 : g_fence + 0x59cffc))
#else
extern u8 g_gameListTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_repeatDown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x59f000 : g_fence + 0x59effc))
#else
extern u8 g_repeatDown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyListPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5a1000 : g_fence + 0x5a0ffc))
#else
extern u8 g_lobbyListPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikMouse3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5a3000 : g_fence + 0x5a2ffc))
#else
extern u8 g_dikMouse3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_highlightSize_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5a5000 : g_fence + 0x5a4ffc))
#else
extern u8 g_highlightSize_v[4];
#endif
#ifdef AXIS_FENCE
#define g_stageDir_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x5a7000 : g_fence + 0x5a6efb))
#else
extern char g_stageDir_v[261];
#endif
#ifdef AXIS_FENCE
#define g_panelGlow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5a9000 : g_fence + 0x5a8ffc))
#else
extern u8 g_panelGlow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapPreviewChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5ab000 : g_fence + 0x5aaffc))
#else
extern u8 g_mapPreviewChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_texture256x64_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5ad000 : g_fence + 0x5acebc))
#else
extern u8 g_texture256x64_v[840004];
#endif
#ifdef AXIS_FENCE
#define g_dialogChoice_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x67c000 : g_fence + 0x67bffc))
#else
extern u8 g_dialogChoice_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikApostrophe_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x67e000 : g_fence + 0x67dffc))
#else
extern u8 g_dikApostrophe_v[4];
#endif
#ifdef AXIS_FENCE
#define g_messages_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x680000 : g_fence + 0x67fb00))
#else
extern char g_messages_v[128256];
#endif
#ifdef AXIS_FENCE
#define g_dikEnd_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6a1000 : g_fence + 0x6a0ffc))
#else
extern u8 g_dikEnd_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikDown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6a3000 : g_fence + 0x6a2ffc))
#else
extern u8 g_dikDown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikGrave_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6a5000 : g_fence + 0x6a4ffc))
#else
extern u8 g_dikGrave_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikRWin_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6a7000 : g_fence + 0x6a6ffc))
#else
extern u8 g_dikRWin_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clearColour_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6a9000 : g_fence + 0x6a8ff0))
#else
extern u8 g_clearColour_v[16];
#endif
#ifdef AXIS_FENCE
#define g_fontHanJungJong_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6ab000 : g_fence + 0x6aaffc))
#else
extern u8 g_fontHanJungJong_v[4];
#endif
#ifdef AXIS_FENCE
#define g_startedByLauncher_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6ad000 : g_fence + 0x6acffc))
#else
extern u8 g_startedByLauncher_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chosenGameMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6af000 : g_fence + 0x6aeffc))
#else
extern u8 g_chosenGameMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cageTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6b1000 : g_fence + 0x6b0ffc))
#else
extern u8 g_cageTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikPageDown_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6b3000 : g_fence + 0x6b2ffc))
#else
extern u8 g_dikPageDown_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikMinus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6b5000 : g_fence + 0x6b4ffc))
#else
extern u8 g_dikMinus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikBack_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6b7000 : g_fence + 0x6b6ffc))
#else
extern u8 g_dikBack_v[4];
#endif
#ifdef AXIS_FENCE
#define g_repeatUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6b9000 : g_fence + 0x6b8ffc))
#else
extern u8 g_repeatUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikRBracket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6bb000 : g_fence + 0x6baffc))
#else
extern u8 g_dikRBracket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_camAims_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x6bd000 : g_fence + 0x6bcfb0))
#else
extern float g_camAims_v[20];
#endif
#ifdef AXIS_FENCE
#define g_screen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6bf000 : g_fence + 0x6beffc))
#else
extern u8 g_screen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_desktopDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6c1000 : g_fence + 0x6c0ffc))
#else
extern u8 g_desktopDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_logoTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6c3000 : g_fence + 0x6c2ffc))
#else
extern u8 g_logoTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpadMinus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6c5000 : g_fence + 0x6c4ffc))
#else
extern u8 g_dikNumpadMinus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuLookHome_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x6c7000 : g_fence + 0x6c6ff4))
#else
extern float g_menuLookHome_v[3];
#endif
#ifdef AXIS_FENCE
#define g_timeLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6c9000 : g_fence + 0x6c8ffc))
#else
extern u8 g_timeLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListWaiting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6cb000 : g_fence + 0x6caffc))
#else
extern u8 g_roomListWaiting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_startedFromLobby_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6cd000 : g_fence + 0x6ccffc))
#else
extern u8 g_startedFromLobby_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikDelete_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6cf000 : g_fence + 0x6ceffc))
#else
extern u8 g_dikDelete_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatEditLength_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6d1000 : g_fence + 0x6d0ffc))
#else
extern u8 g_chatEditLength_v[4];
#endif
#ifdef AXIS_FENCE
#define g_localPlayer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6d3000 : g_fence + 0x6d2ffc))
#else
extern u8 g_localPlayer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikCapsLock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6d5000 : g_fence + 0x6d4ffc))
#else
extern u8 g_dikCapsLock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikMouse2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6d7000 : g_fence + 0x6d6ffc))
#else
extern u8 g_dikMouse2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuFrameCounter_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6d9000 : g_fence + 0x6d8ffc))
#else
extern u8 g_menuFrameCounter_v[4];
#endif
#ifdef AXIS_FENCE
#define g_highlightShown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6db000 : g_fence + 0x6daffc))
#else
extern u8 g_highlightShown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_desktopHeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6dd000 : g_fence + 0x6dcffc))
#else
extern u8 g_desktopHeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fontAscii_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6df000 : g_fence + 0x6deffc))
#else
extern u8 g_fontAscii_v[4];
#endif
#ifdef AXIS_FENCE
#define g_joinedTitleNameCopy_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x6e1000 : g_fence + 0x6e0fe0))
#else
extern char g_joinedTitleNameCopy_v[32];
#endif
#ifdef AXIS_FENCE
#define g_dikSemicolon_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6e3000 : g_fence + 0x6e2ffc))
#else
extern u8 g_dikSemicolon_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedStartupWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6e5000 : g_fence + 0x6e4ffc))
#else
extern u8 g_unusedStartupWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x6e7000 : g_fence + 0x6e6ff8))
#else
extern int g_mainMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_desktopDC_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6e9000 : g_fence + 0x6e8ffc))
#else
extern u8 g_desktopDC_v[4];
#endif
#ifdef AXIS_FENCE
#define g_searchResult_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6eb000 : g_fence + 0x6eaffc))
#else
extern u8 g_searchResult_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEscape_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6ed000 : g_fence + 0x6ecffc))
#else
extern u8 g_dikEscape_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikWheelUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6ef000 : g_fence + 0x6eeffc))
#else
extern u8 g_dikWheelUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_texture128x128_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6f1000 : g_fence + 0x6f0ebc))
#else
extern u8 g_texture128x128_v[840004];
#endif
#ifdef AXIS_FENCE
#define g_textureSets_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x7c0000 : g_fence + 0x7bffe0))
#else
extern u32 g_textureSets_v[8];
#endif
#ifdef AXIS_FENCE
#define g_hudLayerBRight_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x7c2000 : g_fence + 0x7c1e20))
#else
extern float g_hudLayerBRight_v[120];
#endif
#ifdef AXIS_FENCE
#define g_hudLayerBBottom_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x7c4000 : g_fence + 0x7c3e20))
#else
extern float g_hudLayerBBottom_v[120];
#endif
#ifdef AXIS_FENCE
#define g_graphicSettings_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x7c6000 : g_fence + 0x7c5fe4))
#else
extern int g_graphicSettings_v[7];
#endif
#ifdef AXIS_FENCE
#define g_texture256x256_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7c8000 : g_fence + 0x7c7ebc))
#else
extern u8 g_texture256x256_v[840004];
#endif
#ifdef AXIS_FENCE
#define g_lastPanel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x897000 : g_fence + 0x896ffc))
#else
extern u8 g_lastPanel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikDelete_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x899000 : g_fence + 0x898ffc))
#else
extern u8 g_dikDelete_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaLeaving_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x89b000 : g_fence + 0x89affc))
#else
extern u8 g_arenaLeaving_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapNames_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x89d000 : g_fence + 0x89c380))
#else
extern char g_mapNames_v[3200];
#endif
#ifdef AXIS_FENCE
#define g_unusedRoomListWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x89f000 : g_fence + 0x89effc))
#else
extern u8 g_unusedRoomListWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikHome_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8a1000 : g_fence + 0x8a0ffc))
#else
extern u8 g_dikHome_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dialogOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8a3000 : g_fence + 0x8a2ffc))
#else
extern u8 g_dialogOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookYaw_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8a5000 : g_fence + 0x8a4ffc))
#else
extern u8 g_armcLookYaw_v[4];
#endif
#ifdef AXIS_FENCE
#define g_skirmishInfoCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8a7000 : g_fence + 0x8a6ffc))
#else
extern u8 g_skirmishInfoCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_texture256x128_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8a9000 : g_fence + 0x8a8ebc))
#else
extern u8 g_texture256x128_v[840004];
#endif
#ifdef AXIS_FENCE
#define g_mapPreviewTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x978000 : g_fence + 0x977ffc))
#else
extern u8 g_mapPreviewTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_outlinesCopy_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x97a000 : g_fence + 0x979f50))
#else
extern int g_outlinesCopy_v[44];
#endif
#ifdef AXIS_FENCE
#define g_chatCaretX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x97c000 : g_fence + 0x97bffc))
#else
extern u8 g_chatCaretX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatCaretY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x97e000 : g_fence + 0x97dffc))
#else
extern u8 g_chatCaretY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapRotation_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x980000 : g_fence + 0x97fffc))
#else
extern u8 g_mapRotation_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuFade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x982000 : g_fence + 0x981ffc))
#else
extern u8 g_menuFade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_excludedKey_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x984000 : g_fence + 0x983ffc))
#else
extern u8 g_excludedKey_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x986000 : g_fence + 0x985ffc))
#else
extern u8 g_dikF3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x988000 : g_fence + 0x987ffc))
#else
extern u8 g_dikF2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF5_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x98a000 : g_fence + 0x989ffc))
#else
extern u8 g_dikF5_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x98c000 : g_fence + 0x98bffc))
#else
extern u8 g_dikF4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF7_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x98e000 : g_fence + 0x98dffc))
#else
extern u8 g_dikF7_v[4];
#endif
#ifdef AXIS_FENCE
#define g_spiralTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x990000 : g_fence + 0x98ffe8))
#else
extern int g_spiralTextures_v[6];
#endif
#ifdef AXIS_FENCE
#define g_dikF6_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x992000 : g_fence + 0x991ffc))
#else
extern u8 g_dikF6_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF9_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x994000 : g_fence + 0x993ffc))
#else
extern u8 g_dikF9_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF8_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x996000 : g_fence + 0x995ffc))
#else
extern u8 g_dikF8_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikWheelDown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x998000 : g_fence + 0x997ffc))
#else
extern u8 g_dikWheelDown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_texturesOff_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x99a000 : g_fence + 0x999ffc))
#else
extern u8 g_texturesOff_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomSearchAnswerIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x99c000 : g_fence + 0x99bffc))
#else
extern u8 g_roomSearchAnswerIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyReply_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x99e000 : g_fence + 0x99dffc))
#else
extern u8 g_lobbyReply_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLAlt_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9a0000 : g_fence + 0x99fffc))
#else
extern u8 g_dikLAlt_v[4];
#endif
#ifdef AXIS_FENCE
#define g_highlightAlpha_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9a2000 : g_fence + 0x9a1ffc))
#else
extern u8 g_highlightAlpha_v[4];
#endif
#ifdef AXIS_FENCE
#define g_font16Top_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x9a4000 : g_fence + 0x9a3ba0))
#else
extern float g_font16Top_v[280];
#endif
#ifdef AXIS_FENCE
#define g_frameCounter40_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9a6000 : g_fence + 0x9a5ffc))
#else
extern u8 g_frameCounter40_v[4];
#endif
#ifdef AXIS_FENCE
#define g_font16Left_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x9a8000 : g_fence + 0x9a7ba0))
#else
extern float g_font16Left_v[280];
#endif
#ifdef AXIS_FENCE
#define g_introTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x9aa000 : g_fence + 0x9a9fe0))
#else
extern int g_introTextures_v[8];
#endif
#ifdef AXIS_FENCE
#define g_dikRCtrl_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ac000 : g_fence + 0x9abffc))
#else
extern u8 g_dikRCtrl_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fontAsciiLarge_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ae000 : g_fence + 0x9adffc))
#else
extern u8 g_fontAsciiLarge_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionStage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b0000 : g_fence + 0x9afffc))
#else
extern u8 g_missionStage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tunnelRings_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b2000 : g_fence + 0x9b1ffc))
#else
extern u8 g_tunnelRings_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b4000 : g_fence + 0x9b3ffc))
#else
extern u8 g_dikLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEquals_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b6000 : g_fence + 0x9b5ffc))
#else
extern u8 g_dikEquals_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fontHanCho_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b8000 : g_fence + 0x9b7ffc))
#else
extern u8 g_fontHanCho_v[4];
#endif
#ifdef AXIS_FENCE
#define g_joinedSessionRec_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ba000 : g_fence + 0x9b9fb6))
#else
extern u8 g_joinedSessionRec_v[74];
#endif
#ifdef AXIS_FENCE
#define g_dikHome_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9bc000 : g_fence + 0x9bbffc))
#else
extern u8 g_dikHome_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEnter_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9be000 : g_fence + 0x9bdffc))
#else
extern u8 g_dikEnter_v[4];
#endif
#ifdef AXIS_FENCE
#define g_language_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9c0000 : g_fence + 0x9bfffc))
#else
extern u8 g_language_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikBackslash_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9c2000 : g_fence + 0x9c1ffc))
#else
extern u8 g_dikBackslash_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dataDir_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x9c4000 : g_fence + 0x9c3efb))
#else
extern char g_dataDir_v[261];
#endif
#ifdef AXIS_FENCE
#define g_roomOutlines_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x9c6000 : g_fence + 0x9c5ef8))
#else
extern int g_roomOutlines_v[66];
#endif
#ifdef AXIS_FENCE
#define g_menuEyeHome_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x9c8000 : g_fence + 0x9c7ff4))
#else
extern float g_menuEyeHome_v[3];
#endif
#ifdef AXIS_FENCE
#define g_dikUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ca000 : g_fence + 0x9c9ffc))
#else
extern u8 g_dikUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_buttonTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9cc000 : g_fence + 0x9cbffc))
#else
extern u8 g_buttonTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNumpadStar_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ce000 : g_fence + 0x9cdffc))
#else
extern u8 g_dikNumpadStar_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikRShift_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9d0000 : g_fence + 0x9cfffc))
#else
extern u8 g_dikRShift_v[4];
#endif
#ifdef AXIS_FENCE
#define g_font16Bottom_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x9d2000 : g_fence + 0x9d1ba0))
#else
extern float g_font16Bottom_v[280];
#endif
#ifdef AXIS_FENCE
#define g_font16Right_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x9d4000 : g_fence + 0x9d3ba0))
#else
extern float g_font16Right_v[280];
#endif
#ifdef AXIS_FENCE
#define g_dikRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9d6000 : g_fence + 0x9d5ffc))
#else
extern u8 g_dikRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tunnelPulse_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9d8000 : g_fence + 0x9d7ffc))
#else
extern u8 g_tunnelPulse_v[4];
#endif
#ifdef AXIS_FENCE
#define g_timerClocks_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x9da000 : g_fence + 0x9d9ff0))
#else
extern u32 g_timerClocks_v[4];
#endif
#ifdef AXIS_FENCE
#define g_replayRunning_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9dc000 : g_fence + 0x9dbffc))
#else
extern u8 g_replayRunning_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuFadingIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9de000 : g_fence + 0x9ddffc))
#else
extern u8 g_mainMenuFadingIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pixelFormatFilled_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9e0000 : g_fence + 0x9dffff))
#else
extern u8 g_pixelFormatFilled_v[1];
#endif
#ifdef AXIS_FENCE
#define g_timerRepeatCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9e2000 : g_fence + 0x9e1ffc))
#else
extern u8 g_timerRepeatCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lastCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9e4000 : g_fence + 0x9e3ffc))
#else
extern u8 g_lastCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_directInputMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9e6000 : g_fence + 0x9e5ffc))
#else
extern u8 g_directInputMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLength_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9e8000 : g_fence + 0x9e7ffc))
#else
extern u8 g_chatLength_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fieldTabKey_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ea000 : g_fence + 0x9e9ffc))
#else
extern u8 g_fieldTabKey_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLine_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x9ec000 : g_fence + 0x9ebc00))
#else
extern char g_chatLine_v[1024];
#endif
#ifdef AXIS_FENCE
#define g_typedLength_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9ee000 : g_fence + 0x9edffc))
#else
extern u8 g_typedLength_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListClickTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9f0000 : g_fence + 0x9efffc))
#else
extern u8 g_gameListClickTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x9f2000 : g_fence + 0x9f1f10))
#else
extern int g_gameListRects_v[60];
#endif
#ifdef AXIS_FENCE
#define g_roomMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9f4000 : g_fence + 0x9f3ffc))
#else
extern u8 g_roomMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loginFormRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x9f6000 : g_fence + 0x9f5f90))
#else
extern int g_loginFormRects_v[28];
#endif
#ifdef AXIS_FENCE
#define g_retypePassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9f8000 : g_fence + 0x9f7ffc))
#else
extern u8 g_retypePassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomMessageRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x9fa000 : g_fence + 0x9f9ff0))
#else
extern int g_roomMessageRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedRoomWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9fc000 : g_fence + 0x9fbffc))
#else
extern u8 g_unusedRoomWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPrevPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9fe000 : g_fence + 0x9fdffc))
#else
extern u8 g_roomListPrevPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomForm_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa00000 : g_fence + 0x9ffff0))
#else
extern int g_roomForm_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginDue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa02000 : g_fence + 0xa01ffc))
#else
extern u8 g_roomLoginDue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingRoomName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa04000 : g_fence + 0xa03ffc))
#else
extern u8 g_typingRoomName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingSort_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa06000 : g_fence + 0xa05ffc))
#else
extern u8 g_rankingSort_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotStatsKept_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa08000 : g_fence + 0xa07fe0))
#else
extern int g_pilotStatsKept_v[8];
#endif
#ifdef AXIS_FENCE
#define g_roomListPrev_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa0a000 : g_fence + 0xa09ffc))
#else
extern u8 g_roomListPrev_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingEmail_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa0c000 : g_fence + 0xa0bffc))
#else
extern u8 g_editingEmail_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListStopRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa0e000 : g_fence + 0xa0dff0))
#else
extern int g_gameListStopRects_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPrevRank_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa10000 : g_fence + 0xa0fffc))
#else
extern u8 g_roomListPrevRank_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedLoginWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa12000 : g_fence + 0xa11ffc))
#else
extern u8 g_unusedLoginWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListLoaded_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa14000 : g_fence + 0xa13ffc))
#else
extern u8 g_gameListLoaded_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingAccountName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa16000 : g_fence + 0xa15ffc))
#else
extern u8 g_typingAccountName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListClickArmed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa18000 : g_fence + 0xa17ffc))
#else
extern u8 g_gameListClickArmed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingRequestPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa1a000 : g_fence + 0xa19ffc))
#else
extern u8 g_rankingRequestPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountNotice_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa1c000 : g_fence + 0xa1bffc))
#else
extern u8 g_accountNotice_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa1e000 : g_fence + 0xa1dffc))
#else
extern u8 g_roomLoginLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa20000 : g_fence + 0xa1fffc))
#else
extern u8 g_roomLoginTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa22000 : g_fence + 0xa21ffc))
#else
extern u8 g_roomLoginRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa24000 : g_fence + 0xa23ffc))
#else
extern u8 g_roomLoginBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPanelLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa26000 : g_fence + 0xa25ffc))
#else
extern u8 g_accountPanelLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPanelTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa28000 : g_fence + 0xa27ffc))
#else
extern u8 g_accountPanelTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPanelRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa2a000 : g_fence + 0xa29ffc))
#else
extern u8 g_accountPanelRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPanelBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa2c000 : g_fence + 0xa2bffc))
#else
extern u8 g_accountPanelBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingPasswordRepeat_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa2e000 : g_fence + 0xa2dffc))
#else
extern u8 g_editingPasswordRepeat_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingAccountPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa30000 : g_fence + 0xa2fffc))
#else
extern u8 g_editingAccountPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingRoomName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa32000 : g_fence + 0xa31ffc))
#else
extern u8 g_editingRoomName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListDistanceLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa34000 : g_fence + 0xa33ffc))
#else
extern u8 g_roomListDistanceLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingGamePassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa36000 : g_fence + 0xa35ffc))
#else
extern u8 g_typingGamePassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_leaveDialogRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa38000 : g_fence + 0xa37fe0))
#else
extern int g_leaveDialogRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_rankingHaveList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa3a000 : g_fence + 0xa39ffc))
#else
extern u8 g_rankingHaveList_v[4];
#endif
#ifdef AXIS_FENCE
#define g_popupRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa3c000 : g_fence + 0xa3bfe0))
#else
extern int g_popupRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_typingAccountPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa3e000 : g_fence + 0xa3dffc))
#else
extern u8 g_typingAccountPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomRefreshing_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa40000 : g_fence + 0xa3fffc))
#else
extern u8 g_roomRefreshing_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa42000 : g_fence + 0xa41fa0))
#else
extern int g_accountRects_v[24];
#endif
#ifdef AXIS_FENCE
#define g_openLoginName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa44000 : g_fence + 0xa43ffc))
#else
extern u8 g_openLoginName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomGameListLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa46000 : g_fence + 0xa45ffc))
#else
extern u8 g_roomGameListLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomGameListTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa48000 : g_fence + 0xa47ffc))
#else
extern u8 g_roomGameListTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomGameListRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa4a000 : g_fence + 0xa49ffc))
#else
extern u8 g_roomGameListRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomGameListBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa4c000 : g_fence + 0xa4bffc))
#else
extern u8 g_roomGameListBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPages_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa4e000 : g_fence + 0xa4dffc))
#else
extern u8 g_roomListPages_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListJoinClicked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa50000 : g_fence + 0xa4fffc))
#else
extern u8 g_gameListJoinClicked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa52000 : g_fence + 0xa51f70))
#else
extern int g_rankingRects_v[36];
#endif
#ifdef AXIS_FENCE
#define g_roomPanelEase_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa54000 : g_fence + 0xa53ffc))
#else
extern u8 g_roomPanelEase_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingAccountRepeat_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa56000 : g_fence + 0xa55ffc))
#else
extern u8 g_typingAccountRepeat_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomJoined_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa58000 : g_fence + 0xa57ffc))
#else
extern u8 g_roomJoined_v[4];
#endif
#ifdef AXIS_FENCE
#define g_joinedTitleName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xa5a000 : g_fence + 0xa59fca))
#else
extern char g_joinedTitleName_v[54];
#endif
#ifdef AXIS_FENCE
#define g_pilotStats_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa5c000 : g_fence + 0xa5bfe0))
#else
extern int g_pilotStats_v[8];
#endif
#ifdef AXIS_FENCE
#define g_roomTunnelDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa5e000 : g_fence + 0xa5dffc))
#else
extern u8 g_roomTunnelDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingOldPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa60000 : g_fence + 0xa5fffc))
#else
extern u8 g_editingOldPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomSearching_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa62000 : g_fence + 0xa61ffc))
#else
extern u8 g_roomSearching_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomAnswerAwaited_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa64000 : g_fence + 0xa63ffc))
#else
extern u8 g_roomAnswerAwaited_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingRoomPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa66000 : g_fence + 0xa65ffc))
#else
extern u8 g_editingRoomPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa68000 : g_fence + 0xa67ffc))
#else
extern u8 g_roomListPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingRoomPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa6a000 : g_fence + 0xa69ffc))
#else
extern u8 g_typingRoomPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomChatting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa6c000 : g_fence + 0xa6bffc))
#else
extern u8 g_roomChatting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingWaiting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa6e000 : g_fence + 0xa6dffc))
#else
extern u8 g_rankingWaiting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomPanelBrightness_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa70000 : g_fence + 0xa6fffc))
#else
extern u8 g_roomPanelBrightness_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListRefreshTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa72000 : g_fence + 0xa71ffc))
#else
extern u8 g_roomListRefreshTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomPopup_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa74000 : g_fence + 0xa73ffc))
#else
extern u8 g_roomPopup_v[4];
#endif
#ifdef AXIS_FENCE
#define g_joinPasswordTyped_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa76000 : g_fence + 0xa75ffc))
#else
extern u8 g_joinPasswordTyped_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingAccountEmail_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa78000 : g_fence + 0xa77ffc))
#else
extern u8 g_typingAccountEmail_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomAwaitingServer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa7a000 : g_fence + 0xa79ffc))
#else
extern u8 g_roomAwaitingServer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loginFormLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa7c000 : g_fence + 0xa7bffc))
#else
extern u8 g_loginFormLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loginFormBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa7e000 : g_fence + 0xa7dffc))
#else
extern u8 g_loginFormBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomSettingsRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa80000 : g_fence + 0xa7ff20))
#else
extern int g_roomSettingsRects_v[56];
#endif
#ifdef AXIS_FENCE
#define g_roomDialogOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa82000 : g_fence + 0xa81ffc))
#else
extern u8 g_roomDialogOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingLast_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa84000 : g_fence + 0xa83ffc))
#else
extern u8 g_rankingLast_v[4];
#endif
#ifdef AXIS_FENCE
#define g_createDialogRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa86000 : g_fence + 0xa85fb0))
#else
extern int g_createDialogRects_v[20];
#endif
#ifdef AXIS_FENCE
#define g_typingGameName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa88000 : g_fence + 0xa87ffc))
#else
extern u8 g_typingGameName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa8a000 : g_fence + 0xa89ffc))
#else
extern u8 g_roomState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomRequestOut_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa8c000 : g_fence + 0xa8bffc))
#else
extern u8 g_roomRequestOut_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingFirst_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa8e000 : g_fence + 0xa8dffc))
#else
extern u8 g_rankingFirst_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomNameSum_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa90000 : g_fence + 0xa8fffc))
#else
extern u8 g_roomNameSum_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomConnected_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa92000 : g_fence + 0xa91ffc))
#else
extern u8 g_roomConnected_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLeaveDialog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa94000 : g_fence + 0xa93ffc))
#else
extern u8 g_roomLeaveDialog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_languageId_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa96000 : g_fence + 0xa95ffe))
#else
extern u8 g_languageId_v[2];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckSeconds_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa98000 : g_fence + 0xa97ffc))
#else
extern u8 g_clockCheckSeconds_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedLastWParam_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa9a000 : g_fence + 0xa99ffc))
#else
extern u8 g_unusedLastWParam_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editOldProc_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa9c000 : g_fence + 0xa9bffc))
#else
extern u8 g_editOldProc_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hChatEdit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa9e000 : g_fence + 0xa9dffc))
#else
extern u8 g_hChatEdit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_argCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaa0000 : g_fence + 0xa9fffc))
#else
extern u8 g_argCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_launchMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaa2000 : g_fence + 0xaa1ffc))
#else
extern u8 g_launchMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckTick_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaa4000 : g_fence + 0xaa3ffc))
#else
extern u8 g_clockCheckTick_v[4];
#endif
#ifdef AXIS_FENCE
#define g_inputFont_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaa6000 : g_fence + 0xaa5ffc))
#else
extern u8 g_inputFont_v[4];
#endif
#ifdef AXIS_FENCE
#define g_startTicks_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaa8000 : g_fence + 0xaa7ffc))
#else
extern u8 g_startTicks_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckTickSeconds_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaaa000 : g_fence + 0xaa9ffc))
#else
extern u8 g_clockCheckTickSeconds_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedInitWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaac000 : g_fence + 0xaabffc))
#else
extern u8 g_unusedInitWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLineDone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaae000 : g_fence + 0xaadffc))
#else
extern u8 g_chatLineDone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckClosed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xab0000 : g_fence + 0xaafffc))
#else
extern u8 g_clockCheckClosed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xab2000 : g_fence + 0xab1ffc))
#else
extern u8 g_mapSelectLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xab4000 : g_fence + 0xab3ffc))
#else
extern u8 g_mapSelectTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xab6000 : g_fence + 0xab5ffc))
#else
extern u8 g_mapSelectRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xab8000 : g_fence + 0xab7ffc))
#else
extern u8 g_mapSelectBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLookKept_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xaba000 : g_fence + 0xab9ff4))
#else
extern float g_roomLookKept_v[3];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xabc000 : g_fence + 0xabbffc))
#else
extern u8 g_mapSelectCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectFirst_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xabe000 : g_fence + 0xabdffc))
#else
extern u8 g_mapSelectFirst_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomEyeKept_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xac0000 : g_fence + 0xabfff4))
#else
extern float g_roomEyeKept_v[3];
#endif
#ifdef AXIS_FENCE
#define g_unusedReplayListWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xac2000 : g_fence + 0xac1ffc))
#else
extern u8 g_unusedReplayListWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuHintStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xac4000 : g_fence + 0xac3ffc))
#else
extern u8 g_menuHintStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xac6000 : g_fence + 0xac5ee0))
#else
extern int g_mapSelectRects_v[72];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectDim_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xac8000 : g_fence + 0xac7ff0))
#else
extern u32 g_mapSelectDim_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuIdleTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaca000 : g_fence + 0xac9ffc))
#else
extern u8 g_menuIdleTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fileList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xacc000 : g_fence + 0xacb000))
#else
extern u8 g_fileList_v[69632];
#endif
#ifdef AXIS_FENCE
#define g_unusedReplayListWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xade000 : g_fence + 0xaddffc))
#else
extern u8 g_unusedReplayListWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuHintClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xae0000 : g_fence + 0xadfffc))
#else
extern u8 g_menuHintClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xae2000 : g_fence + 0xae1ffc))
#else
extern u8 g_mainMenuDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectLit_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xae4000 : g_fence + 0xae3ff0))
#else
extern u32 g_mapSelectLit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tunnelFlyingIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xae6000 : g_fence + 0xae5ffc))
#else
extern u8 g_tunnelFlyingIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuFrames_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xae8000 : g_fence + 0xae7ffc))
#else
extern u8 g_mainMenuFrames_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuPicked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaea000 : g_fence + 0xae9ffc))
#else
extern u8 g_mainMenuPicked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapListFlaggedCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaec000 : g_fence + 0xaebffc))
#else
extern u8 g_mapListFlaggedCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedMainMenuWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaee000 : g_fence + 0xaedffc))
#else
extern u8 g_unusedMainMenuWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_replayRandomOrder_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaf0000 : g_fence + 0xaefffc))
#else
extern u8 g_replayRandomOrder_v[4];
#endif
#ifdef AXIS_FENCE
#define g_skirmishColourDim_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xaf2000 : g_fence + 0xaf1ff0))
#else
extern u32 g_skirmishColourDim_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingStart_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaf4000 : g_fence + 0xaf3ffc))
#else
extern u8 g_briefingStart_v[4];
#endif
#ifdef AXIS_FENCE
#define g_skirmishDrawBackground_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaf6000 : g_fence + 0xaf5ffc))
#else
extern u8 g_skirmishDrawBackground_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionClearBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaf8000 : g_fence + 0xaf79c0))
#else
extern u8 g_missionClearBuffer_v[1600];
#endif
#ifdef AXIS_FENCE
#define g_briefingSource_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xafa000 : g_fence + 0xaf9ffc))
#else
extern u8 g_briefingSource_v[4];
#endif
#ifdef AXIS_FENCE
#define g_settingsState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xafc000 : g_fence + 0xafbffc))
#else
extern u8 g_settingsState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingShown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xafe000 : g_fence + 0xafdffc))
#else
extern u8 g_briefingShown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_settingsPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb00000 : g_fence + 0xaffffc))
#else
extern u8 g_settingsPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingEnd_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb02000 : g_fence + 0xb01ffc))
#else
extern u8 g_briefingEnd_v[4];
#endif
#ifdef AXIS_FENCE
#define g_skirmishColourLit_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xb04000 : g_fence + 0xb03ff0))
#else
extern u32 g_skirmishColourLit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedMissionSaveWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb06000 : g_fence + 0xb05ffc))
#else
extern u8 g_unusedMissionSaveWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_skirmishSettingsRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xb08000 : g_fence + 0xb07f60))
#else
extern int g_skirmishSettingsRects_v[40];
#endif
#ifdef AXIS_FENCE
#define g_missionHeader_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xb0a000 : g_fence + 0xb09ff0))
#else
extern u32 g_missionHeader_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missions_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb0c000 : g_fence + 0xb0b278))
#else
extern u8 g_missions_v[7560];
#endif
#ifdef AXIS_FENCE
#define g_skirmishRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb0f000 : g_fence + 0xb0effc))
#else
extern u8 g_skirmishRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingDone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb11000 : g_fence + 0xb10ffc))
#else
extern u8 g_briefingDone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_undoDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb13000 : g_fence + 0xb12ffc))
#else
extern u8 g_undoDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingText_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xb15000 : g_fence + 0xb149c0))
#else
extern char g_briefingText_v[1600];
#endif
#ifdef AXIS_FENCE
#define g_missionPicked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb17000 : g_fence + 0xb16ffc))
#else
extern u8 g_missionPicked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb19000 : g_fence + 0xb18ffc))
#else
extern u8 g_briefingX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb1b000 : g_fence + 0xb1affc))
#else
extern u8 g_briefingY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb1d000 : g_fence + 0xb1cffc))
#else
extern u8 g_briefingRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb1f000 : g_fence + 0xb1effc))
#else
extern u8 g_briefingBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb21000 : g_fence + 0xb20ffc))
#else
extern u8 g_briefingClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb23000 : g_fence + 0xb22ffc))
#else
extern u8 g_missionTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xb25000 : g_fence + 0xb24fc0))
#else
extern int g_briefingRects_v[16];
#endif
#ifdef AXIS_FENCE
#define g_mouseWasDown_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xb27000 : g_fence + 0xb26ff4))
#else
extern int g_mouseWasDown_v[3];
#endif
#ifdef AXIS_FENCE
#define g_campaign_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb29000 : g_fence + 0xb28c54))
#else
extern u8 g_campaign_v[940];
#endif
#ifdef AXIS_FENCE
#define g_pilotNoise_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb2b000 : g_fence + 0xb2a8f0))
#else
extern u8 g_pilotNoise_v[10000];
#endif
#ifdef AXIS_FENCE
#define g_profileHeader_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb2f000 : g_fence + 0xb2eefc))
#else
extern u8 g_profileHeader_v[260];
#endif
#ifdef AXIS_FENCE
#define g_missionStarted_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb31000 : g_fence + 0xb30ffc))
#else
extern u8 g_missionStarted_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionColourDim_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xb33000 : g_fence + 0xb32ff0))
#else
extern u32 g_missionColourDim_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb35000 : g_fence + 0xb34ffc))
#else
extern u8 g_missionPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileProgressSaved_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb37000 : g_fence + 0xb36ffc))
#else
extern u8 g_profileProgressSaved_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionBusy_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb39000 : g_fence + 0xb38ffc))
#else
extern u8 g_missionBusy_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionSelectRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xb3b000 : g_fence + 0xb3aff0))
#else
extern int g_missionSelectRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionColourLit_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xb3d000 : g_fence + 0xb3cff0))
#else
extern u32 g_missionColourLit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionChosen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb3f000 : g_fence + 0xb3effc))
#else
extern u8 g_missionChosen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionselRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xb41000 : g_fence + 0xb40fc0))
#else
extern int g_missionselRects_v[16];
#endif
#ifdef AXIS_FENCE
#define g_missionPreviewDue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb43000 : g_fence + 0xb42ffc))
#else
extern u8 g_missionPreviewDue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionShown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb45000 : g_fence + 0xb44ffc))
#else
extern u8 g_missionShown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionShowBackground_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb47000 : g_fence + 0xb46ffc))
#else
extern u8 g_missionShowBackground_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchChatCaretY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb49000 : g_fence + 0xb48ffc))
#else
extern u8 g_matchChatCaretY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchChatCaretX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb4b000 : g_fence + 0xb4affc))
#else
extern u8 g_matchChatCaretX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_keptChat_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xb4d000 : g_fence + 0xb4cc00))
#else
extern char g_keptChat_v[1024];
#endif
#ifdef AXIS_FENCE
#define g_chatTyping_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb4f000 : g_fence + 0xb4effc))
#else
extern u8 g_chatTyping_v[4];
#endif
#ifdef AXIS_FENCE
#define g_writeMatchLog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb51000 : g_fence + 0xb50ffc))
#else
extern u8 g_writeMatchLog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchLogWritten_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb53000 : g_fence + 0xb52ffc))
#else
extern u8 g_matchLogWritten_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchEndedByUser_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb55000 : g_fence + 0xb54ffc))
#else
extern u8 g_matchEndedByUser_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchEndedByServer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb57000 : g_fence + 0xb56ffc))
#else
extern u8 g_matchEndedByServer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedProfileCameraWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb59000 : g_fence + 0xb58ffc))
#else
extern u8 g_unusedProfileCameraWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_deleteDialogRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xb5b000 : g_fence + 0xb5afe0))
#else
extern int g_deleteDialogRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_profile9f6828_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb5d000 : g_fence + 0xb5cffc))
#else
extern u8 g_profile9f6828_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotSelectBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb5f000 : g_fence + 0xb5effc))
#else
extern u8 g_pilotSelectBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotSelectRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb61000 : g_fence + 0xb60ffc))
#else
extern u8 g_pilotSelectRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialog2X_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb63000 : g_fence + 0xb62ffc))
#else
extern u8 g_profileDialog2X_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileIntro_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb65000 : g_fence + 0xb64ffc))
#else
extern u8 g_profileIntro_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialog2Y_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb67000 : g_fence + 0xb66ffc))
#else
extern u8 g_profileDialog2Y_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialogOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb69000 : g_fence + 0xb68ffc))
#else
extern u8 g_profileDialogOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileFrameStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb6b000 : g_fence + 0xb6affc))
#else
extern u8 g_profileFrameStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileListTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb6d000 : g_fence + 0xb6cffc))
#else
extern u8 g_profileListTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotSelectTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb6f000 : g_fence + 0xb6effc))
#else
extern u8 g_pilotSelectTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotSelectLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb71000 : g_fence + 0xb70ffc))
#else
extern u8 g_pilotSelectLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_currentProfile_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb73000 : g_fence + 0xb72ffc))
#else
extern u8 g_currentProfile_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileListRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb75000 : g_fence + 0xb74ffc))
#else
extern u8 g_profileListRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xb77000 : g_fence + 0xb76f70))
#else
extern int g_profilePageRects_v[36];
#endif
#ifdef AXIS_FENCE
#define g_emblemCursor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb79000 : g_fence + 0xb78ffc))
#else
extern u8 g_emblemCursor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_statBars_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xb7b000 : g_fence + 0xb7afdc))
#else
extern float g_statBars_v[9];
#endif
#ifdef AXIS_FENCE
#define g_emblemMoved_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb7d000 : g_fence + 0xb7cffc))
#else
extern u8 g_emblemMoved_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chosenPilot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb7f000 : g_fence + 0xb7effc))
#else
extern u8 g_chosenPilot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileScreenReady_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb81000 : g_fence + 0xb80ffc))
#else
extern u8 g_profileScreenReady_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotChosen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb83000 : g_fence + 0xb82ffc))
#else
extern u8 g_pilotChosen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileListRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xb85000 : g_fence + 0xb84f30))
#else
extern int g_profileListRects_v[52];
#endif
#ifdef AXIS_FENCE
#define g_profilePageLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb87000 : g_fence + 0xb86ffc))
#else
extern u8 g_profilePageLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb89000 : g_fence + 0xb88ffc))
#else
extern u8 g_profilePageTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileIntroSpeed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb8b000 : g_fence + 0xb8affc))
#else
extern u8 g_profileIntroSpeed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileIntroState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb8d000 : g_fence + 0xb8cffc))
#else
extern u8 g_profileIntroState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb8f000 : g_fence + 0xb8effc))
#else
extern u8 g_profilePageRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb91000 : g_fence + 0xb90ffc))
#else
extern u8 g_profilePageBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newNameDialogTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb93000 : g_fence + 0xb92ffc))
#else
extern u8 g_newNameDialogTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newNameDialogLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb95000 : g_fence + 0xb94ffc))
#else
extern u8 g_newNameDialogLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_statBarTargets_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xb97000 : g_fence + 0xb96fdc))
#else
extern float g_statBarTargets_v[9];
#endif
#ifdef AXIS_FENCE
#define g_secondDialogRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xb99000 : g_fence + 0xb98fe0))
#else
extern int g_secondDialogRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_profileFrameAlpha_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb9b000 : g_fence + 0xb9affc))
#else
extern u8 g_profileFrameAlpha_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialogY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb9d000 : g_fence + 0xb9cffc))
#else
extern u8 g_profileDialogY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb9f000 : g_fence + 0xb9effc))
#else
extern u8 g_profilePage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileIntroZoom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xba1000 : g_fence + 0xba0ffc))
#else
extern u8 g_profileIntroZoom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileMessageTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xba3000 : g_fence + 0xba2ffc))
#else
extern u8 g_profileMessageTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialogX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xba5000 : g_fence + 0xba4ffc))
#else
extern u8 g_profileDialogX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newNameDialogRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xba7000 : g_fence + 0xba6ffc))
#else
extern u8 g_newNameDialogRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newNameDialogBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xba9000 : g_fence + 0xba8ffc))
#else
extern u8 g_newNameDialogBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialogBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbab000 : g_fence + 0xbaaffc))
#else
extern u8 g_profileDialogBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialogRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbad000 : g_fence + 0xbacffc))
#else
extern u8 g_profileDialogRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileIntroTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbaf000 : g_fence + 0xbaeffc))
#else
extern u8 g_profileIntroTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbb1000 : g_fence + 0xbb0ffc))
#else
extern u8 g_profileMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotSelectRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xbb3000 : g_fence + 0xbb2f50))
#else
extern int g_pilotSelectRects_v[44];
#endif
#ifdef AXIS_FENCE
#define g_profileCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbb5000 : g_fence + 0xbb4ffc))
#else
extern u8 g_profileCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileRowClicked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbb7000 : g_fence + 0xbb6ffc))
#else
extern u8 g_profileRowClicked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialogBox_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xbb9000 : g_fence + 0xbb8ff0))
#else
extern int g_profileDialogBox_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newNameDialogRects_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xbbb000 : g_fence + 0xbbafe0))
#else
extern int g_newNameDialogRects_v[8];
#endif
#ifdef AXIS_FENCE
#define g_profileDialog2Right_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbbd000 : g_fence + 0xbbcffc))
#else
extern u8 g_profileDialog2Right_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialog2Bottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbbf000 : g_fence + 0xbbeffc))
#else
extern u8 g_profileDialog2Bottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageKind_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbc1000 : g_fence + 0xbc0ffc))
#else
extern u8 g_netChatMessageKind_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbc3000 : g_fence + 0xbc2ffc))
#else
extern u8 g_netChatMessageWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbc5000 : g_fence + 0xbc4ffc))
#else
extern u8 g_netChatMessageWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageText_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbc7000 : g_fence + 0xbc6ffc))
#else
extern u8 g_netChatMessageText_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerSlotFlags_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xbc9000 : g_fence + 0xbc8fc0))
#else
extern int g_playerSlotFlags_v[16];
#endif
#ifdef AXIS_FENCE
#define g_resultMsg_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xbcb000 : g_fence + 0xbcaff8))
#else
extern u32 g_resultMsg_v[2];
#endif
#ifdef AXIS_FENCE
#define g_netSlotMsg_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xbcd000 : g_fence + 0xbccff8))
#else
extern u32 g_netSlotMsg_v[2];
#endif
#ifdef AXIS_FENCE
#define g_netSendPacket_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xbcf000 : g_fence + 0xbcebf4))
#else
extern u32 g_netSendPacket_v[259];
#endif
#ifdef AXIS_FENCE
#define g_slotTakenFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbd1000 : g_fence + 0xbd0ffc))
#else
extern u8 g_slotTakenFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netBlockSize_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbd3000 : g_fence + 0xbd2ffc))
#else
extern u8 g_netBlockSize_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbd5000 : g_fence + 0xbd4ffc))
#else
extern u8 g_chatLog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netHostGone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbd7000 : g_fence + 0xbd6ffc))
#else
extern u8 g_netHostGone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbd9000 : g_fence + 0xbd8ffc))
#else
extern u8 g_playerCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_watchedSlot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbdb000 : g_fence + 0xbdafff))
#else
extern u8 g_watchedSlot_v[1];
#endif
#ifdef AXIS_FENCE
#define g_chatLogged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbdd000 : g_fence + 0xbdcffc))
#else
extern u8 g_chatLogged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbdf000 : g_fence + 0xbde700))
#else
extern u8 g_roomList_v[30976];
#endif
#ifdef AXIS_FENCE
#define g_lobbyReplyRecord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbe8000 : g_fence + 0xbe7fa5))
#else
extern u8 g_lobbyReplyRecord_v[91];
#endif
#ifdef AXIS_FENCE
#define g_netNoticeRecord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbea000 : g_fence + 0xbe9fde))
#else
extern u8 g_netNoticeRecord_v[34];
#endif
#ifdef AXIS_FENCE
#define g_serverReply_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbec000 : g_fence + 0xbebfc2))
#else
extern u8 g_serverReply_v[62];
#endif
#ifdef AXIS_FENCE
#define g_serverPort_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbee000 : g_fence + 0xbedffe))
#else
extern u8 g_serverPort_v[2];
#endif
#ifdef AXIS_FENCE
#define g_unusedNetCloseWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbf0000 : g_fence + 0xbefffc))
#else
extern u8 g_unusedNetCloseWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyReplyCode_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xbf2000 : g_fence + 0xbf1ffc))
#else
extern int g_lobbyReplyCode_v[1];
#endif
#ifdef AXIS_FENCE
#define g_netJoinMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbf4000 : g_fence + 0xbf3ffc))
#else
extern u8 g_netJoinMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyTcpPort_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbf6000 : g_fence + 0xbf5ffc))
#else
extern u8 g_lobbyTcpPort_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbySocket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbf8000 : g_fence + 0xbf7ffc))
#else
extern u8 g_lobbySocket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ladderDns_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xbfa000 : g_fence + 0xbf9fce))
#else
extern char g_ladderDns_v[50];
#endif
#ifdef AXIS_FENCE
#define g_gameServerSocket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbfc000 : g_fence + 0xbfbffc))
#else
extern u8 g_gameServerSocket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ladderPort_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbfe000 : g_fence + 0xbfdffc))
#else
extern u8 g_ladderPort_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netRecvRecord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc00000 : g_fence + 0xbffef5))
#else
extern u8 g_netRecvRecord_v[267];
#endif
#ifdef AXIS_FENCE
#define g_serverList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc02000 : g_fence + 0xc01500))
#else
extern u8 g_serverList_v[23296];
#endif
#ifdef AXIS_FENCE
#define g_gameServerReplyCode_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xc09000 : g_fence + 0xc08ffc))
#else
extern int g_gameServerReplyCode_v[1];
#endif
#ifdef AXIS_FENCE
#define g_tcpDns_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xc0b000 : g_fence + 0xc0afce))
#else
extern char g_tcpDns_v[50];
#endif
#ifdef AXIS_FENCE
#define g_gameServerReply_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc0d000 : g_fence + 0xc0cf87))
#else
extern u8 g_gameServerReply_v[121];
#endif
#ifdef AXIS_FENCE
#define g_netConnected_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc0f000 : g_fence + 0xc0effc))
#else
extern u8 g_netConnected_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netLastRequest_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc11000 : g_fence + 0xc10ffc))
#else
extern u8 g_netLastRequest_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netSendName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc13000 : g_fence + 0xc12ffc))
#else
extern u8 g_netSendName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netSendBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc15000 : g_fence + 0xc14ffc))
#else
extern u8 g_netSendBuffer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netKindWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc17000 : g_fence + 0xc16ffc))
#else
extern u8 g_netKindWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc19000 : g_fence + 0xc18ffc))
#else
extern u8 g_roomPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netInfoPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc1b000 : g_fence + 0xc1affc))
#else
extern u8 g_netInfoPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netLobbyMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc1d000 : g_fence + 0xc1cffc))
#else
extern u8 g_netLobbyMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc1f000 : g_fence + 0xc1effc))
#else
extern u8 g_accountPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netRankingBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc21000 : g_fence + 0xc20ffc))
#else
extern u8 g_netRankingBuffer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc23000 : g_fence + 0xc22ffc))
#else
extern u8 g_arenaPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaInfoPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc25000 : g_fence + 0xc24ffc))
#else
extern u8 g_arenaInfoPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomRecordPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc27000 : g_fence + 0xc26ffc))
#else
extern u8 g_roomRecordPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netRequestWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc29000 : g_fence + 0xc28ffc))
#else
extern u8 g_netRequestWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netPlayerRecordPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc2b000 : g_fence + 0xc2affc))
#else
extern u8 g_netPlayerRecordPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netLeaveBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc2d000 : g_fence + 0xc2cffc))
#else
extern u8 g_netLeaveBuffer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netSelectionPacket_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc2f000 : g_fence + 0xc2effc))
#else
extern u8 g_netSelectionPacket_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netAccountBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc31000 : g_fence + 0xc30ffc))
#else
extern u8 g_netAccountBuffer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc33000 : g_fence + 0xc32ffc))
#else
extern u8 g_gameServerState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerListRefused_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc35000 : g_fence + 0xc34ffc))
#else
extern u8 g_playerListRefused_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netNoticeIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc37000 : g_fence + 0xc36ffc))
#else
extern u8 g_netNoticeIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc39000 : g_fence + 0xc38ffc))
#else
extern u8 g_roomListCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerListCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc3b000 : g_fence + 0xc3affc))
#else
extern u8 g_playerListCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc3d000 : g_fence + 0xc3cffc))
#else
extern u8 g_lobbyPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc3f000 : g_fence + 0xc3effc))
#else
extern u8 g_gameServerPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverListCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc41000 : g_fence + 0xc40ffc))
#else
extern u8 g_serverListCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverConnectionState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc43000 : g_fence + 0xc42ffc))
#else
extern u8 g_serverConnectionState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyStatus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc45000 : g_fence + 0xc44ffc))
#else
extern u8 g_lobbyStatus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerStatus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc47000 : g_fence + 0xc46ffc))
#else
extern u8 g_gameServerStatus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerAnswer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc49000 : g_fence + 0xc48ffc))
#else
extern u8 g_gameServerAnswer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerAnswer15_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc4b000 : g_fence + 0xc4affc))
#else
extern u8 g_gameServerAnswer15_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyConnectStatus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc4d000 : g_fence + 0xc4cffc))
#else
extern u8 g_lobbyConnectStatus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplaySessionList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc4f000 : g_fence + 0xc4effc))
#else
extern u8 g_dplaySessionList_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netQueueOnline_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc51000 : g_fence + 0xc50ffc))
#else
extern u8 g_netQueueOnline_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSessionOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc53000 : g_fence + 0xc52ffc))
#else
extern u8 g_arenaSessionOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplayLobby_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc55000 : g_fence + 0xc54ffc))
#else
extern u8 g_dplayLobby_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tcpProviderGuid_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc57000 : g_fence + 0xc56ff0))
#else
extern u8 g_tcpProviderGuid_v[16];
#endif
#ifdef AXIS_FENCE
#define g_sessionDesc_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc59000 : g_fence + 0xc58fb0))
#else
extern u8 g_sessionDesc_v[80];
#endif
#ifdef AXIS_FENCE
#define g_dplay_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc5b000 : g_fence + 0xc5affc))
#else
extern u8 g_dplay_v[4];
#endif
#ifdef AXIS_FENCE
#define g_modemProviderGuid_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc5d000 : g_fence + 0xc5cff0))
#else
extern u8 g_modemProviderGuid_v[16];
#endif
#ifdef AXIS_FENCE
#define g_connectionKind_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc5f000 : g_fence + 0xc5effc))
#else
extern u8 g_connectionKind_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplaySessionCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc61000 : g_fence + 0xc60ffc))
#else
extern u8 g_dplaySessionCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedSessionWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc63000 : g_fence + 0xc62ffc))
#else
extern u8 g_unusedSessionWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_localPlayerId_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc65000 : g_fence + 0xc64ffc))
#else
extern u8 g_localPlayerId_v[4];
#endif
#ifdef AXIS_FENCE
#define g_localPlayerData_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc67000 : g_fence + 0xc66ffc))
#else
extern u8 g_localPlayerData_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc69000 : g_fence + 0xc68ffc))
#else
extern u8 g_unusedDplayWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc6b000 : g_fence + 0xc6affc))
#else
extern u8 g_unusedDplayWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc6d000 : g_fence + 0xc6cffc))
#else
extern u8 g_unusedDplayWord3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc6f000 : g_fence + 0xc6effc))
#else
extern u8 g_unusedDplayWord4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ipxProviderGuid_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc71000 : g_fence + 0xc70ff0))
#else
extern u8 g_ipxProviderGuid_v[16];
#endif
#ifdef AXIS_FENCE
#define g_dottedAddress_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xc73000 : g_fence + 0xc72ff0))
#else
extern char g_dottedAddress_v[16];
#endif
#ifdef AXIS_FENCE
#define g_sessionTable_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xc75000 : g_fence + 0xc749c0))
#else
extern u32 g_sessionTable_v[400];
#endif
#ifdef AXIS_FENCE
#define g_connectionCopy_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc77000 : g_fence + 0xc76ffc))
#else
extern u8 g_connectionCopy_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serialProviderGuid_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc79000 : g_fence + 0xc78ff0))
#else
extern u8 g_serialProviderGuid_v[16];
#endif
#ifdef AXIS_FENCE
#define g_serviceProviderCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc7b000 : g_fence + 0xc7affc))
#else
extern u8 g_serviceProviderCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc7d000 : g_fence + 0xc7cffc))
#else
extern u8 g_arenaJoinTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_instanceGuid_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc7f000 : g_fence + 0xc7effc))
#else
extern u8 g_instanceGuid_v[4];
#endif
#ifdef AXIS_FENCE
#define g_storedConnection_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc81000 : g_fence + 0xc80ffc))
#else
extern u8 g_storedConnection_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dpConnections_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xc83000 : g_fence + 0xc82ff0))
#else
extern int g_dpConnections_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hostAddressBlock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc85000 : g_fence + 0xc84ffc))
#else
extern u8 g_hostAddressBlock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyConnectionBlock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc87000 : g_fence + 0xc86ffc))
#else
extern u8 g_lobbyConnectionBlock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_isHost_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc89000 : g_fence + 0xc88ffc))
#else
extern u8 g_isHost_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dpTimeout_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc8b000 : g_fence + 0xc8affc))
#else
extern u8 g_dpTimeout_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dpMaxBufferSize_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc8d000 : g_fence + 0xc8cffc))
#else
extern u8 g_dpMaxBufferSize_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dpMaxQueueSize_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc8f000 : g_fence + 0xc8effc))
#else
extern u8 g_dpMaxQueueSize_v[4];
#endif
#ifdef AXIS_FENCE
#define g_noAddress_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xc91000 : g_fence + 0xc90ffc))
#else
extern char g_noAddress_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pingDataEvent_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc93000 : g_fence + 0xc92ffc))
#else
extern u8 g_pingDataEvent_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverUsed_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xc95000 : g_fence + 0xc94c00))
#else
extern u32 g_serverUsed_v[256];
#endif
#ifdef AXIS_FENCE
#define g_unusedPingWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc97000 : g_fence + 0xc96ffc))
#else
extern u8 g_unusedPingWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedPingWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc99000 : g_fence + 0xc98ffc))
#else
extern u8 g_unusedPingWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pingStopEvent_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc9b000 : g_fence + 0xc9affc))
#else
extern u8 g_pingStopEvent_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverNames_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xc9d000 : g_fence + 0xc9cc00))
#else
extern u32 g_serverNames_v[1280];
#endif
#ifdef AXIS_FENCE
#define g_serverPing_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xca0000 : g_fence + 0xc9fc00))
#else
extern int g_serverPing_v[256];
#endif
#ifdef AXIS_FENCE
#define g_pingThreadId_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xca2000 : g_fence + 0xca1ffc))
#else
extern u8 g_pingThreadId_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pingThread_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xca4000 : g_fence + 0xca3ffc))
#else
extern u8 g_pingThread_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pingTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xca6000 : g_fence + 0xca5ffc))
#else
extern u8 g_pingTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverPingCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xca8000 : g_fence + 0xca7ffc))
#else
extern u8 g_serverPingCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netListDone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcaa000 : g_fence + 0xca9ffc))
#else
extern u8 g_netListDone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplaySlots_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xcac000 : g_fence + 0xcabff0))
#else
extern int g_dplaySlots_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxTablesReady_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcae000 : g_fence + 0xcadffc))
#else
extern u8 g_ptxTablesReady_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textures_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcb0000 : g_fence + 0xcafffc))
#else
extern u8 g_textures_v[4];
#endif
#ifdef AXIS_FENCE
#define g_musicDuration_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xcb2000 : g_fence + 0xcb1ff8))
#else
extern u32 g_musicDuration_v[2];
#endif
#ifdef AXIS_FENCE
#define g_soundBaseVolume_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcb4000 : g_fence + 0xcb3ffc))
#else
extern u8 g_soundBaseVolume_v[4];
#endif
#ifdef AXIS_FENCE
#define g_music_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcb6000 : g_fence + 0xcb5ffc))
#else
extern u8 g_music_v[4];
#endif
#ifdef AXIS_FENCE
#define g_musicFile_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xcb8000 : g_fence + 0xcb7efc))
#else
extern char g_musicFile_v[260];
#endif
#ifdef AXIS_FENCE
#define g_vecOriginXyz_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xcba000 : g_fence + 0xcb9ff4))
#else
extern float g_vecOriginXyz_v[3];
#endif
#ifdef AXIS_FENCE
#define g_vecUnitZXyz_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xcbc000 : g_fence + 0xcbbff4))
#else
extern float g_vecUnitZXyz_v[3];
#endif
#ifdef AXIS_FENCE
#define g_vecZeroXyz_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xcbe000 : g_fence + 0xcbdff4))
#else
extern float g_vecZeroXyz_v[3];
#endif
#ifdef AXIS_FENCE
#define g_directSound_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcc0000 : g_fence + 0xcbfffc))
#else
extern u8 g_directSound_v[4];
#endif
#ifdef AXIS_FENCE
#define g_primarySoundBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcc2000 : g_fence + 0xcc1ffc))
#else
extern u8 g_primarySoundBuffer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_soundOn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcc4000 : g_fence + 0xcc3ffc))
#else
extern u8 g_soundOn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glWidth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcc6000 : g_fence + 0xcc5ffc))
#else
extern u8 g_glWidth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_desktopH_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcc8000 : g_fence + 0xcc7ffc))
#else
extern u8 g_desktopH_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glColourBits_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcca000 : g_fence + 0xcc9ffc))
#else
extern u8 g_glColourBits_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glTitle_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xccc000 : g_fence + 0xccbf00))
#else
extern char g_glTitle_v[256];
#endif
#ifdef AXIS_FENCE
#define g_desktopBits_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcce000 : g_fence + 0xccdffc))
#else
extern u8 g_desktopBits_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fullScreen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcd0000 : g_fence + 0xccfffc))
#else
extern u8 g_fullScreen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glHeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcd2000 : g_fence + 0xcd1ffc))
#else
extern u8 g_glHeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_desktopW_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcd4000 : g_fence + 0xcd3ffc))
#else
extern u8 g_desktopW_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glWindowMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcd6000 : g_fence + 0xcd5ffc))
#else
extern u8 g_glWindowMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glWindow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcd8000 : g_fence + 0xcd7ffc))
#else
extern u8 g_glWindow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hdc_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcda000 : g_fence + 0xcd9ffc))
#else
extern u8 g_hdc_v[4];
#endif
#ifdef AXIS_FENCE
#define g_context_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcdc000 : g_fence + 0xcdbffc))
#else
extern u8 g_context_v[4];
#endif
#ifdef AXIS_FENCE
#define g_modeChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcde000 : g_fence + 0xcddffc))
#else
extern u8 g_modeChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loadTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xce0000 : g_fence + 0xcdffc8))
#else
extern u8 g_loadTimer_v[56];
#endif
#ifdef AXIS_FENCE
#define g_loadTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xce2000 : g_fence + 0xce1ffc))
#else
extern u8 g_loadTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loadFade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xce4000 : g_fence + 0xce3ffc))
#else
extern u8 g_loadFade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loadProgress_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xce6000 : g_fence + 0xce5ffc))
#else
extern u8 g_loadProgress_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loadGame_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xce8000 : g_fence + 0xce7ffc))
#else
extern u8 g_loadGame_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapMissing_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcea000 : g_fence + 0xce9ffc))
#else
extern u8 g_mapMissing_v[4];
#endif
#ifdef AXIS_FENCE
#define g_penPropTopLeft_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xcec000 : g_fence + 0xcebcb8))
#else
extern float g_penPropTopLeft_v[210];
#endif
#ifdef AXIS_FENCE
#define g_penPropBottomRight_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xcee000 : g_fence + 0xcedcb8))
#else
extern float g_penPropBottomRight_v[210];
#endif
#ifdef AXIS_FENCE
#define g_penFixedBottomRight_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xcf0000 : g_fence + 0xcefcb8))
#else
extern float g_penFixedBottomRight_v[210];
#endif
#ifdef AXIS_FENCE
#define g_penFixedTopLeft_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xcf2000 : g_fence + 0xcf1cb8))
#else
extern float g_penFixedTopLeft_v[210];
#endif
#ifdef AXIS_FENCE
#define g_penPropBottomLeft_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xcf4000 : g_fence + 0xcf3cb8))
#else
extern float g_penPropBottomLeft_v[210];
#endif
#ifdef AXIS_FENCE
#define g_penFixedWidths_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xcf6000 : g_fence + 0xcf5e5c))
#else
extern int g_penFixedWidths_v[105];
#endif
#ifdef AXIS_FENCE
#define g_penFixedBottomLeft_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xcf8000 : g_fence + 0xcf7cb8))
#else
extern float g_penFixedBottomLeft_v[210];
#endif
#ifdef AXIS_FENCE
#define g_penFixedTopRight_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xcfa000 : g_fence + 0xcf9cb8))
#else
extern float g_penFixedTopRight_v[210];
#endif
#ifdef AXIS_FENCE
#define g_penPropTopRight_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xcfc000 : g_fence + 0xcfbcb8))
#else
extern float g_penPropTopRight_v[210];
#endif
#ifdef AXIS_FENCE
#define g_penFontNeverSet_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcfe000 : g_fence + 0xcfdffc))
#else
extern u8 g_penFontNeverSet_v[4];
#endif
#ifdef AXIS_FENCE
#define g_penFontTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd00000 : g_fence + 0xcffffc))
#else
extern u8 g_penFontTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tan10Table_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xd02000 : g_fence + 0xd01fb8))
#else
extern float g_tan10Table_v[18];
#endif
#ifdef AXIS_FENCE
#define g_randTable_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xd04000 : g_fence + 0xd03000))
#else
extern int g_randTable_v[4096];
#endif
#ifdef AXIS_FENCE
#define g_tanTable_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xd09000 : g_fence + 0xd087c0))
#else
extern float g_tanTable_v[3600];
#endif
#ifdef AXIS_FENCE
#define g_cosTable_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xd0e000 : g_fence + 0xd0d7c0))
#else
extern float g_cosTable_v[3600];
#endif
#ifdef AXIS_FENCE
#define g_sinTable_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xd13000 : g_fence + 0xd127c0))
#else
extern float g_sinTable_v[3600];
#endif
#ifdef AXIS_FENCE
#define g_randPos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd18000 : g_fence + 0xd17ffc))
#else
extern u8 g_randPos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciCallback_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd1a000 : g_fence + 0xd19ffc))
#else
extern u8 g_mciCallback_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciFrom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd1c000 : g_fence + 0xd1bffc))
#else
extern u8 g_mciFrom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciTo_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd1e000 : g_fence + 0xd1dffc))
#else
extern u8 g_mciTo_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciDevice_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd20000 : g_fence + 0xd1fffc))
#else
extern u8 g_mciDevice_v[4];
#endif
#ifdef AXIS_FENCE
#define g_errorLogging_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd22000 : g_fence + 0xd21ffc))
#else
extern u8 g_errorLogging_v[4];
#endif
#ifdef AXIS_FENCE
#define g_errorCleanupHook_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd24000 : g_fence + 0xd23ffc))
#else
extern u8 g_errorCleanupHook_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textColours_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd26000 : g_fence + 0xd25f00))
#else
extern u8 g_textColours_v[256];
#endif
#ifdef AXIS_FENCE
#define g_packedBlue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd28000 : g_fence + 0xd27ffc))
#else
extern u8 g_packedBlue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_packedGrey_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd2a000 : g_fence + 0xd29ffc))
#else
extern u8 g_packedGrey_v[4];
#endif
#ifdef AXIS_FENCE
#define g_packedYellow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd2c000 : g_fence + 0xd2bffc))
#else
extern u8 g_packedYellow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_realClear_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xd2e000 : g_fence + 0xd2dff0))
#else
extern float g_realClear_v[4];
#endif
#ifdef AXIS_FENCE
#define g_defaultColour_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd30000 : g_fence + 0xd2fffc))
#else
extern u8 g_defaultColour_v[4];
#endif
#ifdef AXIS_FENCE
#define g_realBlue_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xd32000 : g_fence + 0xd31ff0))
#else
extern float g_realBlue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_colourMaskRed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd34000 : g_fence + 0xd33ffc))
#else
extern u8 g_colourMaskRed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_realWhite_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xd36000 : g_fence + 0xd35ff0))
#else
extern float g_realWhite_v[4];
#endif
#ifdef AXIS_FENCE
#define g_realGreen_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xd38000 : g_fence + 0xd37ff0))
#else
extern float g_realGreen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_realRed_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xd3a000 : g_fence + 0xd39ff0))
#else
extern float g_realRed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_realBlack_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xd3c000 : g_fence + 0xd3bff0))
#else
extern float g_realBlack_v[4];
#endif
#ifdef AXIS_FENCE
#define g_defaultColours_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xd3e000 : g_fence + 0xd3dfc0))
#else
extern u32 g_defaultColours_v[16];
#endif
#ifdef AXIS_FENCE
#define g_realYellow_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xd40000 : g_fence + 0xd3fff0))
#else
extern float g_realYellow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_packedGreen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd42000 : g_fence + 0xd41ffc))
#else
extern u8 g_packedGreen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_realGrey_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xd44000 : g_fence + 0xd43ff0))
#else
extern float g_realGrey_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clamp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd46000 : g_fence + 0xd45ffc))
#else
extern u8 g_clamp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxCbBlue_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xd48000 : g_fence + 0xd47c00))
#else
extern int g_ptxCbBlue_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxYCbCrTables_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xd4a000 : g_fence + 0xd49000))
#else
extern int g_ptxYCbCrTables_v[2048];
#endif
#ifdef AXIS_FENCE
#define g_ptxBitPos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd4d000 : g_fence + 0xd4cffc))
#else
extern u8 g_ptxBitPos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxPixels_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd4f000 : g_fence + 0xd4e000))
#else
extern u8 g_ptxPixels_v[262144];
#endif
#ifdef AXIS_FENCE
#define g_bitStream_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd90000 : g_fence + 0xd8fffc))
#else
extern u8 g_bitStream_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxCbGreen_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xd92000 : g_fence + 0xd91c00))
#else
extern int g_ptxCbGreen_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxClampTable_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd94000 : g_fence + 0xd93a80))
#else
extern u8 g_ptxClampTable_v[1408];
#endif
#ifdef AXIS_FENCE
#define g_ptxPlanes_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd96000 : g_fence + 0xd95000))
#else
extern u8 g_ptxPlanes_v[262144];
#endif
#ifdef AXIS_FENCE
#define g_ptxCrRed_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xdd7000 : g_fence + 0xdd6c00))
#else
extern int g_ptxCrRed_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxLastDc_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xdd9000 : g_fence + 0xdd8ffc))
#else
extern u8 g_ptxLastDc_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxCrGreen_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xddb000 : g_fence + 0xddac00))
#else
extern int g_ptxCrGreen_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxDequant_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xddd000 : g_fence + 0xddce00))
#else
extern float g_ptxDequant_v[128];
#endif
#ifdef AXIS_FENCE
#define g_ptxQuant_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xddf000 : g_fence + 0xddee00))
#else
extern int g_ptxQuant_v[128];
#endif
#ifdef AXIS_FENCE
#define g_ptxTable_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xde1000 : g_fence + 0xde0ffc))
#else
extern u8 g_ptxTable_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxData_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xde3000 : g_fence + 0xde2000))
#else
extern u8 g_ptxData_v[262144];
#endif
#ifdef AXIS_FENCE
#define g_logHook_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe24000 : g_fence + 0xe23ffc))
#else
extern u8 g_logHook_v[4];
#endif
#ifdef AXIS_FENCE
#define g_cursorPoint_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xe26000 : g_fence + 0xe25ff8))
#else
extern int g_cursorPoint_v[2];
#endif
#ifdef AXIS_FENCE
#define g_asyncKeySeen_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xe28000 : g_fence + 0xe27c00))
#else
extern int g_asyncKeySeen_v[256];
#endif
#ifdef AXIS_FENCE
#define g_sortState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe2a000 : g_fence + 0xe29fe8))
#else
extern u8 g_sortState_v[49176];
#endif
#ifdef AXIS_FENCE
#define g_currentStageName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe38000 : g_fence + 0xe37ffc))
#else
extern u8 g_currentStageName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_packetQueue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe3a000 : g_fence + 0xe39fc0))
#else
extern u8 g_packetQueue_v[139328];
#endif
#ifdef AXIS_FENCE
#define g_nextNumber_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xe5e000 : g_fence + 0xe5dfc0))
#else
extern int g_nextNumber_v[16];
#endif
#ifdef AXIS_FENCE
#define g_cursor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe60000 : g_fence + 0xe5fffc))
#else
extern u8 g_cursor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_resends_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe62000 : g_fence + 0xe61ffc))
#else
extern u8 g_resends_v[4];
#endif
#ifdef AXIS_FENCE
#define g_displayModeChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe64000 : g_fence + 0xe63fff))
#else
extern u8 g_displayModeChanged_v[1];
#endif
#ifdef AXIS_FENCE
#define g_displayModeLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe66000 : g_fence + 0xe65fff))
#else
extern u8 g_displayModeLeft_v[1];
#endif
#ifdef AXIS_FENCE
#define g_otherModeWidth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe68000 : g_fence + 0xe67ffc))
#else
extern u8 g_otherModeWidth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_otherModeHeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe6a000 : g_fence + 0xe69ffc))
#else
extern u8 g_otherModeHeight_v[4];
#endif
