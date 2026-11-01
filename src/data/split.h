/* split.h (tools/mkdatasrc.py): the variables split out of g_data, and in a fence build (AXIS_FENCE) their places
   in g_fence: AXIS_FENCE 1 at the end of their pages, the guard page after; 2 after the guard page */
#pragma once
#ifdef AXIS_FENCE
extern u8 g_fence[];
#endif
#ifdef AXIS_FENCE
#define g_timerFirstCall_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1000 : g_fence + 0xffc))
#else
extern u8 g_timerFirstCall_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameRunning_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3000 : g_fence + 0x2ffc))
#else
extern u8 g_gameRunning_v[4];
#endif
#ifdef AXIS_FENCE
#define g_keepCameraAsked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5000 : g_fence + 0x4ffc))
#else
extern u8 g_keepCameraAsked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcEnterStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7000 : g_fence + 0x6ffc))
#else
extern u8 g_armcEnterStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_musicVolumeSetting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9000 : g_fence + 0x8ffc))
#else
extern u8 g_musicVolumeSetting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_componentDatPath_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb000 : g_fence + 0xaffc))
#else
extern u8 g_componentDatPath_v[4];
#endif
#ifdef AXIS_FENCE
#define g_insertCdMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd000 : g_fence + 0xcffc))
#else
extern u8 g_insertCdMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glCachedState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xf000 : g_fence + 0xeffc))
#else
extern u8 g_glCachedState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewFov_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x11000 : g_fence + 0x10ffc))
#else
extern u8 g_viewFov_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewNear_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x13000 : g_fence + 0x12ffc))
#else
extern u8 g_viewNear_v[4];
#endif
#ifdef AXIS_FENCE
#define g_viewFar_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15000 : g_fence + 0x14ffc))
#else
extern u8 g_viewFar_v[4];
#endif
#ifdef AXIS_FENCE
#define g_catalogueFile_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x17000 : g_fence + 0x16ffc))
#else
extern u8 g_catalogueFile_v[4];
#endif
#ifdef AXIS_FENCE
#define g_keySeen_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x19000 : g_fence + 0x18c00))
#else
extern int g_keySeen_v[256];
#endif
#ifdef AXIS_FENCE
#define g_unusedKeyTable2Word0_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b000 : g_fence + 0x1affc))
#else
extern u8 g_unusedKeyTable2Word0_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedKeyTable2Flags_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d000 : g_fence + 0x1cffe))
#else
extern u8 g_unusedKeyTable2Flags_v[2];
#endif
#ifdef AXIS_FENCE
#define g_unusedKeyTable2Word1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f000 : g_fence + 0x1effc))
#else
extern u8 g_unusedKeyTable2Word1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedKeyTable2Word2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x21000 : g_fence + 0x20ffc))
#else
extern u8 g_unusedKeyTable2Word2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textEndX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x23000 : g_fence + 0x22ffc))
#else
extern u8 g_textEndX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_textEndY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x25000 : g_fence + 0x24ffc))
#else
extern u8 g_textEndY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_convertHangul_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x27000 : g_fence + 0x26ffc))
#else
extern u8 g_convertHangul_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hangulVowelGlyph_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x29000 : g_fence + 0x28ffc))
#else
extern u8 g_hangulVowelGlyph_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hangulTailGlyph_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b000 : g_fence + 0x2affc))
#else
extern u8 g_hangulTailGlyph_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hangulLeadGlyph_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d000 : g_fence + 0x2cffc))
#else
extern u8 g_hangulLeadGlyph_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingSkipped_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2f000 : g_fence + 0x2effc))
#else
extern u8 g_briefingSkipped_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapEntry22On_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x31000 : g_fence + 0x30ffc))
#else
extern u8 g_mapEntry22On_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapEntry23On_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x33000 : g_fence + 0x32ffc))
#else
extern u8 g_mapEntry23On_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapEntry24On_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x35000 : g_fence + 0x34ffc))
#else
extern u8 g_mapEntry24On_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapListOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x37000 : g_fence + 0x36ffc))
#else
extern u8 g_mapListOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapListMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x39000 : g_fence + 0x38ffc))
#else
extern u8 g_mapListMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3b000 : g_fence + 0x3affc))
#else
extern u8 g_arenaJoinPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingArenaMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3d000 : g_fence + 0x3cffc))
#else
extern u8 g_editingArenaMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3f000 : g_fence + 0x3effc))
#else
extern u8 g_arenaJoinRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaFull_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x41000 : g_fence + 0x40ffc))
#else
extern u8 g_arenaFull_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyConnectionOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x43000 : g_fence + 0x42ffc))
#else
extern u8 g_lobbyConnectionOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaListClickArmed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x45000 : g_fence + 0x44ffc))
#else
extern u8 g_arenaListClickArmed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptCamX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x47000 : g_fence + 0x46ffc))
#else
extern u8 g_arenaKeptCamX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptCamY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x49000 : g_fence + 0x48ffc))
#else
extern u8 g_arenaKeptCamY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptCamZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4b000 : g_fence + 0x4affc))
#else
extern u8 g_arenaKeptCamZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaConfirming_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4d000 : g_fence + 0x4cffc))
#else
extern u8 g_arenaConfirming_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaTunnelDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4f000 : g_fence + 0x4effc))
#else
extern u8 g_arenaTunnelDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestWeightLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x51000 : g_fence + 0x50ffc))
#else
extern u8 g_chestWeightLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestMaxArmor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x53000 : g_fence + 0x52ffc))
#else
extern u8 g_chestMaxArmor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestMaxShield_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x55000 : g_fence + 0x54ffc))
#else
extern u8 g_chestMaxShield_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcSlot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x57000 : g_fence + 0x56ffc))
#else
extern u8 g_armcSlot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bestLevelNet_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x59000 : g_fence + 0x58ffc))
#else
extern u8 g_bestLevelNet_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcSessionMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5b000 : g_fence + 0x5affc))
#else
extern u8 g_armcSessionMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox0Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5d000 : g_fence + 0x5cffc))
#else
extern u8 g_partBox0Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox1Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5f000 : g_fence + 0x5effc))
#else
extern u8 g_partBox1Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox2Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x61000 : g_fence + 0x60ffc))
#else
extern u8 g_partBox2Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox3Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x63000 : g_fence + 0x62ffc))
#else
extern u8 g_partBox3Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox4Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x65000 : g_fence + 0x64ffc))
#else
extern u8 g_partBox4Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox5Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x67000 : g_fence + 0x66ffc))
#else
extern u8 g_partBox5Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x69000 : g_fence + 0x68ffc))
#else
extern u8 g_unusedArmcWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcEntered_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6b000 : g_fence + 0x6affc))
#else
extern u8 g_armcEntered_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6d000 : g_fence + 0x6cffc))
#else
extern u8 g_armcLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_coloursChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6f000 : g_fence + 0x6effc))
#else
extern u8 g_coloursChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechDetectionRange_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x71000 : g_fence + 0x70ffc))
#else
extern u8 g_mechDetectionRange_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x73000 : g_fence + 0x72ffc))
#else
extern u8 g_mechChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x75000 : g_fence + 0x74ffc))
#else
extern u8 g_armcChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusShield_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x77000 : g_fence + 0x76ffc))
#else
extern u8 g_itemBonusShield_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x79000 : g_fence + 0x78ffc))
#else
extern u8 g_unusedArmcWord3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_boosterThrustType_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7b000 : g_fence + 0x7affc))
#else
extern u8 g_boosterThrustType_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headDetectionRange_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7d000 : g_fence + 0x7cffc))
#else
extern u8 g_headDetectionRange_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headDetectionAngle_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7f000 : g_fence + 0x7effc))
#else
extern u8 g_headDetectionAngle_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcZoom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x81000 : g_fence + 0x80ffc))
#else
extern u8 g_armcZoom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_colourChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x83000 : g_fence + 0x82ffc))
#else
extern u8 g_colourChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fpsSecondStart_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x85000 : g_fence + 0x84ff8))
#else
extern u8 g_fpsSecondStart_v[8];
#endif
#ifdef AXIS_FENCE
#define g_menuFrameCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x87000 : g_fence + 0x86ffc))
#else
extern u8 g_menuFrameCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_messageBoxArgs_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x89000 : g_fence + 0x88ffc))
#else
extern u8 g_messageBoxArgs_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedStartupWord3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8b000 : g_fence + 0x8affc))
#else
extern u8 g_unusedStartupWord3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fpsFrameClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8d000 : g_fence + 0x8cff8))
#else
extern u8 g_fpsFrameClock_v[8];
#endif
#ifdef AXIS_FENCE
#define g_frameRate_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8f000 : g_fence + 0x8eff8))
#else
extern u8 g_frameRate_v[8];
#endif
#ifdef AXIS_FENCE
#define g_unusedStartupWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x91000 : g_fence + 0x90ffc))
#else
extern u8 g_unusedStartupWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fpsSecondSoFar_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x93000 : g_fence + 0x92ff8))
#else
extern u8 g_fpsSecondSoFar_v[8];
#endif
#ifdef AXIS_FENCE
#define g_fps_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x95000 : g_fence + 0x94ffc))
#else
extern u8 g_fps_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loadStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x97000 : g_fence + 0x96ffc))
#else
extern u8 g_loadStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPressedClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x99000 : g_fence + 0x98ffc))
#else
extern u8 g_setupPressedClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bindPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b000 : g_fence + 0x9affc))
#else
extern u8 g_bindPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9d000 : g_fence + 0x9cffc))
#else
extern u8 g_setupPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupTunnelDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9f000 : g_fence + 0x9effc))
#else
extern u8 g_setupTunnelDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bindWaiting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa1000 : g_fence + 0xa0ffc))
#else
extern u8 g_bindWaiting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupTunnelAlpha_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa3000 : g_fence + 0xa2ffc))
#else
extern u8 g_setupTunnelAlpha_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPanelPos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa5000 : g_fence + 0xa4ffc))
#else
extern u8 g_setupPanelPos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bindRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa7000 : g_fence + 0xa6ffc))
#else
extern u8 g_bindRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveStarted_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa9000 : g_fence + 0xa8ffc))
#else
extern u8 g_armcMoveStarted_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuCamX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xab000 : g_fence + 0xaaffc))
#else
extern u8 g_menuCamX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_freeCamHeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xad000 : g_fence + 0xacffc))
#else
extern u8 g_freeCamHeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuCamZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaf000 : g_fence + 0xaeffc))
#else
extern u8 g_menuCamZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveEyeX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb1000 : g_fence + 0xb0ffc))
#else
extern u8 g_armcMoveEyeX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveEyeY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb3000 : g_fence + 0xb2ffc))
#else
extern u8 g_armcMoveEyeY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveEyeZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb5000 : g_fence + 0xb4ffc))
#else
extern u8 g_armcMoveEyeZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookSin_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb7000 : g_fence + 0xb6ffc))
#else
extern u8 g_armcLookSin_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookTilt_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb9000 : g_fence + 0xb8ffc))
#else
extern u8 g_armcLookTilt_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookCos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbb000 : g_fence + 0xbaffc))
#else
extern u8 g_armcLookCos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveTargetX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbd000 : g_fence + 0xbcffc))
#else
extern u8 g_armcMoveTargetX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveTargetY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbf000 : g_fence + 0xbeffc))
#else
extern u8 g_armcMoveTargetY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveTargetZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc1000 : g_fence + 0xc0ffc))
#else
extern u8 g_armcMoveTargetZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_debugValue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc3000 : g_fence + 0xc2ffc))
#else
extern u8 g_debugValue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcMoveWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc5000 : g_fence + 0xc4ffc))
#else
extern u8 g_unusedArmcMoveWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedPostMatchFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc7000 : g_fence + 0xc6ffc))
#else
extern u8 g_unusedPostMatchFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_watchChatOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc9000 : g_fence + 0xc8ffc))
#else
extern u8 g_watchChatOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_enteringMenus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcb000 : g_fence + 0xcaffc))
#else
extern u8 g_enteringMenus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_showCmd_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcd000 : g_fence + 0xccffc))
#else
extern u8 g_showCmd_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xcf000 : g_fence + 0xceff8))
#else
extern int g_arenaMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_panelGlowStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd1000 : g_fence + 0xd0ffc))
#else
extern u8 g_panelGlowStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikF11_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd3000 : g_fence + 0xd2ffc))
#else
extern u8 g_dikF11_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ladderMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xd5000 : g_fence + 0xd4ff8))
#else
extern int g_ladderMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_fovKeys_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd7000 : g_fence + 0xd6ffc))
#else
extern u8 g_fovKeys_v[4];
#endif
#ifdef AXIS_FENCE
#define g_crosshairTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd9000 : g_fence + 0xd8ffc))
#else
extern u8 g_crosshairTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuTunnelTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xdb000 : g_fence + 0xdaffc))
#else
extern u8 g_menuTunnelTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_projMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xdd000 : g_fence + 0xdcffc))
#else
extern u8 g_projMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_listRefreshPeriod_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xdf000 : g_fence + 0xdeffc))
#else
extern u8 g_listRefreshPeriod_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ctrlMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xe1000 : g_fence + 0xe0ff8))
#else
extern int g_ctrlMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_desktopWidth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe3000 : g_fence + 0xe2ffc))
#else
extern u8 g_desktopWidth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_panelGlow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe5000 : g_fence + 0xe4ffc))
#else
extern u8 g_panelGlow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapPreviewChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe7000 : g_fence + 0xe6ffc))
#else
extern u8 g_mapPreviewChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_messages_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0xe9000 : g_fence + 0xe8b00))
#else
extern char g_messages_v[128256];
#endif
#ifdef AXIS_FENCE
#define g_dikDown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x10a000 : g_fence + 0x109ffc))
#else
extern u8 g_dikDown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_startedByLauncher_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x10c000 : g_fence + 0x10bffc))
#else
extern u8 g_startedByLauncher_v[4];
#endif
#ifdef AXIS_FENCE
#define g_desktopDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x10e000 : g_fence + 0x10dffc))
#else
extern u8 g_desktopDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedStartupWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x110000 : g_fence + 0x10fffc))
#else
extern u8 g_unusedStartupWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x112000 : g_fence + 0x111ff8))
#else
extern int g_mainMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_desktopDC_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x114000 : g_fence + 0x113ffc))
#else
extern u8 g_desktopDC_v[4];
#endif
#ifdef AXIS_FENCE
#define g_searchResult_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x116000 : g_fence + 0x115ffc))
#else
extern u8 g_searchResult_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lastPanel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x118000 : g_fence + 0x117ffc))
#else
extern u8 g_lastPanel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedRoomListWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x11a000 : g_fence + 0x119ffc))
#else
extern u8 g_unusedRoomListWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookYaw_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x11c000 : g_fence + 0x11bffc))
#else
extern u8 g_armcLookYaw_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapPreviewTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x11e000 : g_fence + 0x11dffc))
#else
extern u8 g_mapPreviewTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_excludedKey_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x120000 : g_fence + 0x11fffc))
#else
extern u8 g_excludedKey_v[4];
#endif
#ifdef AXIS_FENCE
#define g_spiralTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x122000 : g_fence + 0x121fe8))
#else
extern int g_spiralTextures_v[6];
#endif
#ifdef AXIS_FENCE
#define g_dikWheelDown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x124000 : g_fence + 0x123ffc))
#else
extern u8 g_dikWheelDown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_frameCounter40_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x126000 : g_fence + 0x125ffc))
#else
extern u8 g_frameCounter40_v[4];
#endif
#ifdef AXIS_FENCE
#define g_introTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x128000 : g_fence + 0x127fe0))
#else
extern int g_introTextures_v[8];
#endif
#ifdef AXIS_FENCE
#define g_dikRCtrl_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x12a000 : g_fence + 0x129ffc))
#else
extern u8 g_dikRCtrl_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tunnelRings_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x12c000 : g_fence + 0x12bffc))
#else
extern u8 g_tunnelRings_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x12e000 : g_fence + 0x12dffc))
#else
extern u8 g_dikLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x130000 : g_fence + 0x12fffc))
#else
extern u8 g_dikRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pixelFormatFilled_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x132000 : g_fence + 0x131fff))
#else
extern u8 g_pixelFormatFilled_v[1];
#endif
#ifdef AXIS_FENCE
#define g_timerRepeatCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x134000 : g_fence + 0x133ffc))
#else
extern u8 g_timerRepeatCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_directInputMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x136000 : g_fence + 0x135ffc))
#else
extern u8 g_directInputMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fieldTabKey_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x138000 : g_fence + 0x137ffc))
#else
extern u8 g_fieldTabKey_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLine_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x13a000 : g_fence + 0x139c00))
#else
extern char g_chatLine_v[1024];
#endif
#ifdef AXIS_FENCE
#define g_typedLength_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x13c000 : g_fence + 0x13bffc))
#else
extern u8 g_typedLength_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListClickTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x13e000 : g_fence + 0x13dffc))
#else
extern u8 g_gameListClickTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_retypePassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x140000 : g_fence + 0x13fffc))
#else
extern u8 g_retypePassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loginToSend_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x142000 : g_fence + 0x141ffc))
#else
extern u8 g_loginToSend_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPrev_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x144000 : g_fence + 0x143ffc))
#else
extern u8 g_roomListPrev_v[4];
#endif
#ifdef AXIS_FENCE
#define g_openLoginName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x146000 : g_fence + 0x145ffc))
#else
extern u8 g_openLoginName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomTunnelDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x148000 : g_fence + 0x147ffc))
#else
extern u8 g_roomTunnelDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomDialogOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x14a000 : g_fence + 0x149ffc))
#else
extern u8 g_roomDialogOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingLast_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x14c000 : g_fence + 0x14bffc))
#else
extern u8 g_rankingLast_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingGameName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x14e000 : g_fence + 0x14dffc))
#else
extern u8 g_typingGameName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_argCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x150000 : g_fence + 0x14fffc))
#else
extern u8 g_argCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_launchMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x152000 : g_fence + 0x151ffc))
#else
extern u8 g_launchMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckTick_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x154000 : g_fence + 0x153ffc))
#else
extern u8 g_clockCheckTick_v[4];
#endif
#ifdef AXIS_FENCE
#define g_inputFont_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x156000 : g_fence + 0x155ffc))
#else
extern u8 g_inputFont_v[4];
#endif
#ifdef AXIS_FENCE
#define g_startTicks_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x158000 : g_fence + 0x157ffc))
#else
extern u8 g_startTicks_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckTickSeconds_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15a000 : g_fence + 0x159ffc))
#else
extern u8 g_clockCheckTickSeconds_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedInitWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15c000 : g_fence + 0x15bffc))
#else
extern u8 g_unusedInitWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLineDone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15e000 : g_fence + 0x15dffc))
#else
extern u8 g_chatLineDone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckClosed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x160000 : g_fence + 0x15fffc))
#else
extern u8 g_clockCheckClosed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fileList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x162000 : g_fence + 0x161000))
#else
extern u8 g_fileList_v[69632];
#endif
#ifdef AXIS_FENCE
#define g_unusedReplayListWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x174000 : g_fence + 0x173ffc))
#else
extern u8 g_unusedReplayListWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingStart_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x176000 : g_fence + 0x175ffc))
#else
extern u8 g_briefingStart_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingSource_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x178000 : g_fence + 0x177ffc))
#else
extern u8 g_briefingSource_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missions_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x17a000 : g_fence + 0x179278))
#else
extern u8 g_missions_v[7560];
#endif
#ifdef AXIS_FENCE
#define g_briefingDone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x17d000 : g_fence + 0x17cffc))
#else
extern u8 g_briefingDone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_undoDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x17f000 : g_fence + 0x17effc))
#else
extern u8 g_undoDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingText_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x181000 : g_fence + 0x1809c0))
#else
extern char g_briefingText_v[1600];
#endif
#ifdef AXIS_FENCE
#define g_profileProgressSaved_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x183000 : g_fence + 0x182ffc))
#else
extern u8 g_profileProgressSaved_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionPreviewDue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x185000 : g_fence + 0x184ffc))
#else
extern u8 g_missionPreviewDue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionShown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x187000 : g_fence + 0x186ffc))
#else
extern u8 g_missionShown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchChatCaretY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x189000 : g_fence + 0x188ffc))
#else
extern u8 g_matchChatCaretY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchChatCaretX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x18b000 : g_fence + 0x18affc))
#else
extern u8 g_matchChatCaretX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatTyping_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x18d000 : g_fence + 0x18cffc))
#else
extern u8 g_chatTyping_v[4];
#endif
#ifdef AXIS_FENCE
#define g_writeMatchLog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x18f000 : g_fence + 0x18effc))
#else
extern u8 g_writeMatchLog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchLogWritten_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x191000 : g_fence + 0x190ffc))
#else
extern u8 g_matchLogWritten_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchEndedByUser_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x193000 : g_fence + 0x192ffc))
#else
extern u8 g_matchEndedByUser_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchEndedByServer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x195000 : g_fence + 0x194ffc))
#else
extern u8 g_matchEndedByServer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedProfileCameraWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x197000 : g_fence + 0x196ffc))
#else
extern u8 g_unusedProfileCameraWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileFrameStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x199000 : g_fence + 0x198ffc))
#else
extern u8 g_profileFrameStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chosenPilot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x19b000 : g_fence + 0x19affc))
#else
extern u8 g_chosenPilot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x19d000 : g_fence + 0x19cffc))
#else
extern u8 g_profilePageRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileFrameAlpha_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x19f000 : g_fence + 0x19effc))
#else
extern u8 g_profileFrameAlpha_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageKind_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a1000 : g_fence + 0x1a0ffc))
#else
extern u8 g_netChatMessageKind_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a3000 : g_fence + 0x1a2ffc))
#else
extern u8 g_netChatMessageWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a5000 : g_fence + 0x1a4ffc))
#else
extern u8 g_netChatMessageWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageText_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a7000 : g_fence + 0x1a6ffc))
#else
extern u8 g_netChatMessageText_v[4];
#endif
#ifdef AXIS_FENCE
#define g_slotTakenFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a9000 : g_fence + 0x1a8ffc))
#else
extern u8 g_slotTakenFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netBlockSize_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ab000 : g_fence + 0x1aaffc))
#else
extern u8 g_netBlockSize_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ad000 : g_fence + 0x1acffc))
#else
extern u8 g_chatLog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netHostGone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1af000 : g_fence + 0x1aeffc))
#else
extern u8 g_netHostGone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_watchedSlot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b1000 : g_fence + 0x1b0fff))
#else
extern u8 g_watchedSlot_v[1];
#endif
#ifdef AXIS_FENCE
#define g_chatLogged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b3000 : g_fence + 0x1b2ffc))
#else
extern u8 g_chatLogged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b5000 : g_fence + 0x1b41c0))
#else
extern u8 g_roomList_v[7744];
#endif
#ifdef AXIS_FENCE
#define g_lobbyReplyKind_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b8000 : g_fence + 0x1b7ffc))
#else
extern u8 g_lobbyReplyKind_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverReplyKind_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ba000 : g_fence + 0x1b9ffc))
#else
extern u8 g_serverReplyKind_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverPort_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1bc000 : g_fence + 0x1bbffe))
#else
extern u8 g_serverPort_v[2];
#endif
#ifdef AXIS_FENCE
#define g_unusedNetCloseWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1be000 : g_fence + 0x1bdffc))
#else
extern u8 g_unusedNetCloseWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerReplyKind_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c0000 : g_fence + 0x1bfffc))
#else
extern u8 g_gameServerReplyKind_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netConnected_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c2000 : g_fence + 0x1c1ffc))
#else
extern u8 g_netConnected_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netLastRequest_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c4000 : g_fence + 0x1c3ffc))
#else
extern u8 g_netLastRequest_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplay_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c6000 : g_fence + 0x1c5ffc))
#else
extern u8 g_dplay_v[4];
#endif
#ifdef AXIS_FENCE
#define g_connectionKind_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c8000 : g_fence + 0x1c7ffc))
#else
extern u8 g_connectionKind_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplaySessionCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ca000 : g_fence + 0x1c9ffc))
#else
extern u8 g_dplaySessionCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedSessionWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1cc000 : g_fence + 0x1cbffc))
#else
extern u8 g_unusedSessionWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_localPlayerId_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ce000 : g_fence + 0x1cdffc))
#else
extern u8 g_localPlayerId_v[4];
#endif
#ifdef AXIS_FENCE
#define g_localPlayerData_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d0000 : g_fence + 0x1cfffc))
#else
extern u8 g_localPlayerData_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d2000 : g_fence + 0x1d1ffc))
#else
extern u8 g_unusedDplayWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d4000 : g_fence + 0x1d3ffc))
#else
extern u8 g_unusedDplayWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d6000 : g_fence + 0x1d5ffc))
#else
extern u8 g_unusedDplayWord3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d8000 : g_fence + 0x1d7ffc))
#else
extern u8 g_unusedDplayWord4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_connectionCopy_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1da000 : g_fence + 0x1d9ffc))
#else
extern u8 g_connectionCopy_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serviceProviderCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1dc000 : g_fence + 0x1dbffc))
#else
extern u8 g_serviceProviderCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1de000 : g_fence + 0x1ddffc))
#else
extern u8 g_arenaJoinTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_instanceGuid_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e0000 : g_fence + 0x1dfffc))
#else
extern u8 g_instanceGuid_v[4];
#endif
#ifdef AXIS_FENCE
#define g_storedConnection_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e2000 : g_fence + 0x1e1ffc))
#else
extern u8 g_storedConnection_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedPingWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e4000 : g_fence + 0x1e3ffc))
#else
extern u8 g_unusedPingWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedPingWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e6000 : g_fence + 0x1e5ffc))
#else
extern u8 g_unusedPingWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverNames_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x1e8000 : g_fence + 0x1e7c00))
#else
extern u32 g_serverNames_v[1280];
#endif
#ifdef AXIS_FENCE
#define g_ptxTablesReady_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1eb000 : g_fence + 0x1eaffc))
#else
extern u8 g_ptxTablesReady_v[4];
#endif
#ifdef AXIS_FENCE
#define g_soundBaseVolume_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ed000 : g_fence + 0x1ecffc))
#else
extern u8 g_soundBaseVolume_v[4];
#endif
#ifdef AXIS_FENCE
#define g_directSound_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ef000 : g_fence + 0x1eeffc))
#else
extern u8 g_directSound_v[4];
#endif
#ifdef AXIS_FENCE
#define g_primarySoundBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f1000 : g_fence + 0x1f0ffc))
#else
extern u8 g_primarySoundBuffer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_soundOn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f3000 : g_fence + 0x1f2ffc))
#else
extern u8 g_soundOn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glColourBits_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f5000 : g_fence + 0x1f4ffc))
#else
extern u8 g_glColourBits_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fullScreen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f7000 : g_fence + 0x1f6ffc))
#else
extern u8 g_fullScreen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapMissing_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f9000 : g_fence + 0x1f8ffc))
#else
extern u8 g_mapMissing_v[4];
#endif
#ifdef AXIS_FENCE
#define g_penFontNeverSet_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1fb000 : g_fence + 0x1faffc))
#else
extern u8 g_penFontNeverSet_v[4];
#endif
#ifdef AXIS_FENCE
#define g_penFontTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1fd000 : g_fence + 0x1fcffc))
#else
extern u8 g_penFontTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tan10Table_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x1ff000 : g_fence + 0x1fefb8))
#else
extern float g_tan10Table_v[18];
#endif
#ifdef AXIS_FENCE
#define g_randTable_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x201000 : g_fence + 0x200000))
#else
extern int g_randTable_v[4096];
#endif
#ifdef AXIS_FENCE
#define g_tanTable_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x206000 : g_fence + 0x2057c0))
#else
extern float g_tanTable_v[3600];
#endif
#ifdef AXIS_FENCE
#define g_cosTable_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x20b000 : g_fence + 0x20a7c0))
#else
extern float g_cosTable_v[3600];
#endif
#ifdef AXIS_FENCE
#define g_sinTable_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x210000 : g_fence + 0x20f7c0))
#else
extern float g_sinTable_v[3600];
#endif
#ifdef AXIS_FENCE
#define g_randPos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x215000 : g_fence + 0x214ffc))
#else
extern u8 g_randPos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciCallback_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x217000 : g_fence + 0x216ffc))
#else
extern u8 g_mciCallback_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciFrom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x219000 : g_fence + 0x218ffc))
#else
extern u8 g_mciFrom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciTo_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x21b000 : g_fence + 0x21affc))
#else
extern u8 g_mciTo_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciDevice_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x21d000 : g_fence + 0x21cffc))
#else
extern u8 g_mciDevice_v[4];
#endif
#ifdef AXIS_FENCE
#define g_errorLogging_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x21f000 : g_fence + 0x21effc))
#else
extern u8 g_errorLogging_v[4];
#endif
#ifdef AXIS_FENCE
#define g_errorCleanupHook_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x221000 : g_fence + 0x220ffc))
#else
extern u8 g_errorCleanupHook_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxCbBlue_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x223000 : g_fence + 0x222c00))
#else
extern int g_ptxCbBlue_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxYCbCrTables_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x225000 : g_fence + 0x224000))
#else
extern int g_ptxYCbCrTables_v[2048];
#endif
#ifdef AXIS_FENCE
#define g_ptxBitPos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x228000 : g_fence + 0x227ffc))
#else
extern u8 g_ptxBitPos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxPixels_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x22a000 : g_fence + 0x229000))
#else
extern u8 g_ptxPixels_v[262144];
#endif
#ifdef AXIS_FENCE
#define g_bitStream_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x26b000 : g_fence + 0x26affc))
#else
extern u8 g_bitStream_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxCbGreen_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x26d000 : g_fence + 0x26cc00))
#else
extern int g_ptxCbGreen_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxClampTable_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x26f000 : g_fence + 0x26ea80))
#else
extern u8 g_ptxClampTable_v[1408];
#endif
#ifdef AXIS_FENCE
#define g_ptxPlanes_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x271000 : g_fence + 0x270000))
#else
extern u8 g_ptxPlanes_v[262144];
#endif
#ifdef AXIS_FENCE
#define g_ptxCrRed_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x2b2000 : g_fence + 0x2b1c00))
#else
extern int g_ptxCrRed_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxLastDc_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b4000 : g_fence + 0x2b3ffc))
#else
extern u8 g_ptxLastDc_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxCrGreen_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x2b6000 : g_fence + 0x2b5c00))
#else
extern int g_ptxCrGreen_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxDequant_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x2b8000 : g_fence + 0x2b7e00))
#else
extern float g_ptxDequant_v[128];
#endif
#ifdef AXIS_FENCE
#define g_ptxQuant_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x2ba000 : g_fence + 0x2b9e00))
#else
extern int g_ptxQuant_v[128];
#endif
#ifdef AXIS_FENCE
#define g_ptxTable_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2bc000 : g_fence + 0x2bbffc))
#else
extern u8 g_ptxTable_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxData_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2be000 : g_fence + 0x2bd000))
#else
extern u8 g_ptxData_v[262144];
#endif
#ifdef AXIS_FENCE
#define g_logHook_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ff000 : g_fence + 0x2feffc))
#else
extern u8 g_logHook_v[4];
#endif
#ifdef AXIS_FENCE
#define g_currentStageName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x301000 : g_fence + 0x300ffc))
#else
extern u8 g_currentStageName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_displayModeChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x303000 : g_fence + 0x302fff))
#else
extern u8 g_displayModeChanged_v[1];
#endif
#ifdef AXIS_FENCE
#define g_displayModeLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x305000 : g_fence + 0x304fff))
#else
extern u8 g_displayModeLeft_v[1];
#endif
#ifdef AXIS_FENCE
#define g_otherModeWidth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x307000 : g_fence + 0x306ffc))
#else
extern u8 g_otherModeWidth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_otherModeHeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x309000 : g_fence + 0x308ffc))
#else
extern u8 g_otherModeHeight_v[4];
#endif
