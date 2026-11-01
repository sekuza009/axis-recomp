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
#define g_mapListMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x31000 : g_fence + 0x30ffc))
#else
extern u8 g_mapListMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingNewArenaTimeLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x33000 : g_fence + 0x32ffc))
#else
extern u8 g_editingNewArenaTimeLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newArenaName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x35000 : g_fence + 0x34fd0))
#else
extern char g_newArenaName_v[48];
#endif
#ifdef AXIS_FENCE
#define g_createQuitDialog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x37000 : g_fence + 0x36ffc))
#else
extern u8 g_createQuitDialog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaCorporation_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x39000 : g_fence + 0x38ffc))
#else
extern u8 g_arenaCorporation_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSex_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3b000 : g_fence + 0x3affc))
#else
extern u8 g_arenaSex_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3d000 : g_fence + 0x3cffc))
#else
extern u8 g_arenaJoinPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingArenaMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3f000 : g_fence + 0x3effc))
#else
extern u8 g_editingArenaMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x41000 : g_fence + 0x40ffc))
#else
extern u8 g_arenaJoinRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaFull_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x43000 : g_fence + 0x42ffc))
#else
extern u8 g_arenaFull_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyConnectionOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x45000 : g_fence + 0x44ffc))
#else
extern u8 g_lobbyConnectionOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaListClickArmed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x47000 : g_fence + 0x46ffc))
#else
extern u8 g_arenaListClickArmed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptCamX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x49000 : g_fence + 0x48ffc))
#else
extern u8 g_arenaKeptCamX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptCamY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4b000 : g_fence + 0x4affc))
#else
extern u8 g_arenaKeptCamY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptCamZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4d000 : g_fence + 0x4cffc))
#else
extern u8 g_arenaKeptCamZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingNewArenaFragLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4f000 : g_fence + 0x4effc))
#else
extern u8 g_editingNewArenaFragLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverSearching_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x51000 : g_fence + 0x50ffc))
#else
extern u8 g_serverSearching_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbySearching_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x53000 : g_fence + 0x52ffc))
#else
extern u8 g_lobbySearching_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyPanelsOff_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x55000 : g_fence + 0x54ffc))
#else
extern u8 g_lobbyPanelsOff_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaConfirming_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x57000 : g_fence + 0x56ffc))
#else
extern u8 g_arenaConfirming_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyRefreshing_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x59000 : g_fence + 0x58ffc))
#else
extern u8 g_lobbyRefreshing_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoining_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5b000 : g_fence + 0x5affc))
#else
extern u8 g_arenaJoining_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5d000 : g_fence + 0x5cffc))
#else
extern u8 g_arenaGameListLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x5f000 : g_fence + 0x5effc))
#else
extern u8 g_arenaGameListTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x61000 : g_fence + 0x60ffc))
#else
extern u8 g_arenaGameListRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameListBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x63000 : g_fence + 0x62ffc))
#else
extern u8 g_arenaGameListBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaTunnelDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x65000 : g_fence + 0x64ffc))
#else
extern u8 g_arenaTunnelDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaKeptLookZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x67000 : g_fence + 0x66ffc))
#else
extern u8 g_arenaKeptLookZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaHaveList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x69000 : g_fence + 0x68ffc))
#else
extern u8 g_arenaHaveList_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingArenaPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6b000 : g_fence + 0x6affc))
#else
extern u8 g_typingArenaPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaListRefreshTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6d000 : g_fence + 0x6cffc))
#else
extern u8 g_arenaListRefreshTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSearchClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x6f000 : g_fence + 0x6effc))
#else
extern u8 g_arenaSearchClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newArenaForm_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x71000 : g_fence + 0x70ff0))
#else
extern int g_newArenaForm_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSearchTicks_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x73000 : g_fence + 0x72ffc))
#else
extern u8 g_arenaSearchTicks_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaLobbyMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x75000 : g_fence + 0x74ffc))
#else
extern u8 g_arenaLobbyMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x77000 : g_fence + 0x76ffc))
#else
extern u8 g_arenaNameDialogLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x79000 : g_fence + 0x78ffc))
#else
extern u8 g_arenaNameDialogTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7b000 : g_fence + 0x7affc))
#else
extern u8 g_arenaNameDialogRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaNameDialogBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7d000 : g_fence + 0x7cffc))
#else
extern u8 g_arenaNameDialogBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinWaiting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x7f000 : g_fence + 0x7effc))
#else
extern u8 g_arenaJoinWaiting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaPanelBrightness_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x81000 : g_fence + 0x80ffc))
#else
extern u8 g_arenaPanelBrightness_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingArenaName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x83000 : g_fence + 0x82ffc))
#else
extern u8 g_typingArenaName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyJoinStarted_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x85000 : g_fence + 0x84ffc))
#else
extern u8 g_lobbyJoinStarted_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyJoinRequest_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x87000 : g_fence + 0x86ffc))
#else
extern u8 g_lobbyJoinRequest_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaLobbyState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x89000 : g_fence + 0x88ffc))
#else
extern u8 g_arenaLobbyState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_receivedSession_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8b000 : g_fence + 0x8affc))
#else
extern u8 g_receivedSession_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8d000 : g_fence + 0x8cffc))
#else
extern u8 g_unusedArmcWord4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestWeightLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x8f000 : g_fence + 0x8effc))
#else
extern u8 g_chestWeightLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestMaxArmor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x91000 : g_fence + 0x90ffc))
#else
extern u8 g_chestMaxArmor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chestMaxShield_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x93000 : g_fence + 0x92ffc))
#else
extern u8 g_chestMaxShield_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcTabColour_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x95000 : g_fence + 0x94ff0))
#else
extern u32 g_armcTabColour_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcPreview_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x97000 : g_fence + 0x96ffc))
#else
extern u8 g_armcPreview_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusCapacityPerLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x99000 : g_fence + 0x98ffc))
#else
extern u8 g_itemBonusCapacityPerLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusDetectionRange_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9b000 : g_fence + 0x9affc))
#else
extern u8 g_itemBonusDetectionRange_v[4];
#endif
#ifdef AXIS_FENCE
#define g_emptyItemSlot0_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9d000 : g_fence + 0x9cffc))
#else
extern u8 g_emptyItemSlot0_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcSlot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x9f000 : g_fence + 0x9effc))
#else
extern u8 g_armcSlot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcTabColourDim_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0xa1000 : g_fence + 0xa0ff0))
#else
extern u32 g_armcTabColourDim_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bestProgressSolo_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa3000 : g_fence + 0xa2ffc))
#else
extern u8 g_bestProgressSolo_v[4];
#endif
#ifdef AXIS_FENCE
#define g_legsStats_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xa5000 : g_fence + 0xa4fe4))
#else
extern float g_legsStats_v[7];
#endif
#ifdef AXIS_FENCE
#define g_armcFrom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xa7000 : g_fence + 0xa6ffc))
#else
extern u8 g_armcFrom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armsStats_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xa9000 : g_fence + 0xa8fec))
#else
extern int g_armsStats_v[5];
#endif
#ifdef AXIS_FENCE
#define g_armsWeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xab000 : g_fence + 0xaaffc))
#else
extern u8 g_armsWeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bestLevelNet_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xad000 : g_fence + 0xacffc))
#else
extern u8 g_bestLevelNet_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcSessionMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xaf000 : g_fence + 0xaeffc))
#else
extern u8 g_armcSessionMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox0Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb1000 : g_fence + 0xb0ffc))
#else
extern u8 g_partBox0Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox1Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb3000 : g_fence + 0xb2ffc))
#else
extern u8 g_partBox1Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox2Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb5000 : g_fence + 0xb4ffc))
#else
extern u8 g_partBox2Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox3Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb7000 : g_fence + 0xb6ffc))
#else
extern u8 g_partBox3Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox4Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xb9000 : g_fence + 0xb8ffc))
#else
extern u8 g_partBox4Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_partBox5Offset_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbb000 : g_fence + 0xbaffc))
#else
extern u8 g_partBox5Offset_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcParts_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xbd000 : g_fence + 0xbcfec))
#else
extern int g_armcParts_v[5];
#endif
#ifdef AXIS_FENCE
#define g_armcCursor_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xbf000 : g_fence + 0xbeffc))
#else
extern u8 g_armcCursor_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unlockedLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc1000 : g_fence + 0xc0ffc))
#else
extern u8 g_unlockedLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcUnusedFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc3000 : g_fence + 0xc2ffc))
#else
extern u8 g_armcUnusedFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_totalWeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc5000 : g_fence + 0xc4ffc))
#else
extern u8 g_totalWeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc7000 : g_fence + 0xc6ffc))
#else
extern u8 g_armcState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xc9000 : g_fence + 0xc8ffc))
#else
extern u8 g_unusedArmcWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcEntered_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcb000 : g_fence + 0xcaffc))
#else
extern u8 g_armcEntered_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xcd000 : g_fence + 0xccffc))
#else
extern u8 g_armcLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_savedMechPartIds_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xcf000 : g_fence + 0xcefec))
#else
extern int g_savedMechPartIds_v[5];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusTargetKeep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd1000 : g_fence + 0xd0ffc))
#else
extern u8 g_itemBonusTargetKeep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLastPart_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd3000 : g_fence + 0xd2ffc))
#else
extern u8 g_armcLastPart_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusRechargeTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd5000 : g_fence + 0xd4ffc))
#else
extern u8 g_itemBonusRechargeTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusLockOn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd7000 : g_fence + 0xd6ffc))
#else
extern u8 g_itemBonusLockOn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_coloursChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xd9000 : g_fence + 0xd8ffc))
#else
extern u8 g_coloursChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechDetectionRange_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xdb000 : g_fence + 0xdaffc))
#else
extern u8 g_mechDetectionRange_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechHackingLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xdd000 : g_fence + 0xdcffc))
#else
extern u8 g_mechHackingLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechPartStats_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xdf000 : g_fence + 0xdefe4))
#else
extern int g_mechPartStats_v[7];
#endif
#ifdef AXIS_FENCE
#define g_mechMobility_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe1000 : g_fence + 0xe0ffc))
#else
extern u8 g_mechMobility_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedMechStat_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe3000 : g_fence + 0xe2ffc))
#else
extern u8 g_unusedMechStat_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechBoosterEnergy_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe5000 : g_fence + 0xe4ffc))
#else
extern u8 g_mechBoosterEnergy_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechBoosterRecharge_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xe7000 : g_fence + 0xe6ffc))
#else
extern u8 g_mechBoosterRecharge_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mechSpeeds_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0xe9000 : g_fence + 0xe8fe8))
#else
extern float g_mechSpeeds_v[6];
#endif
#ifdef AXIS_FENCE
#define g_mechSettings_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xeb000 : g_fence + 0xeafe8))
#else
extern int g_mechSettings_v[6];
#endif
#ifdef AXIS_FENCE
#define g_mechChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xed000 : g_fence + 0xecffc))
#else
extern u8 g_mechChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xef000 : g_fence + 0xeeffc))
#else
extern u8 g_armcChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusShield_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xf1000 : g_fence + 0xf0ffc))
#else
extern u8 g_itemBonusShield_v[4];
#endif
#ifdef AXIS_FENCE
#define g_slotTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0xf3000 : g_fence + 0xf2fe8))
#else
extern int g_slotTextures_v[6];
#endif
#ifdef AXIS_FENCE
#define g_armcBuildTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xf5000 : g_fence + 0xf4ffc))
#else
extern u8 g_armcBuildTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcStatsPanelLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xf7000 : g_fence + 0xf6ffc))
#else
extern u8 g_armcStatsPanelLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcStatsPanelTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xf9000 : g_fence + 0xf8ffc))
#else
extern u8 g_armcStatsPanelTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcStatsPanelBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xfb000 : g_fence + 0xfaffc))
#else
extern u8 g_armcStatsPanelBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusActiveTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xfd000 : g_fence + 0xfcffc))
#else
extern u8 g_itemBonusActiveTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0xff000 : g_fence + 0xfeffc))
#else
extern u8 g_unusedArmcWord3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_boosterStats_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x101000 : g_fence + 0x100fd8))
#else
extern float g_boosterStats_v[10];
#endif
#ifdef AXIS_FENCE
#define g_armcSpin_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x103000 : g_fence + 0x102ffc))
#else
extern u8 g_armcSpin_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusWeightLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x105000 : g_fence + 0x104ffc))
#else
extern u8 g_itemBonusWeightLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_itemBonusHacking_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x107000 : g_fence + 0x106ffc))
#else
extern u8 g_itemBonusHacking_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headDetectionRange_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x109000 : g_fence + 0x108ffc))
#else
extern u8 g_headDetectionRange_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headDetectionAngle_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x10b000 : g_fence + 0x10affc))
#else
extern u8 g_headDetectionAngle_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headHackingLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x10d000 : g_fence + 0x10cffc))
#else
extern u8 g_headHackingLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headLockOnTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x10f000 : g_fence + 0x10effc))
#else
extern u8 g_headLockOnTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headTargetKeepTime_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x111000 : g_fence + 0x110ffc))
#else
extern u8 g_headTargetKeepTime_v[4];
#endif
#ifdef AXIS_FENCE
#define g_headWeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x113000 : g_fence + 0x112ffc))
#else
extern u8 g_headWeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLeaving_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x115000 : g_fence + 0x114ffc))
#else
extern u8 g_armcLeaving_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x117000 : g_fence + 0x116ffc))
#else
extern u8 g_unusedArmcWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_savedMechSettings_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x119000 : g_fence + 0x118fe8))
#else
extern int g_savedMechSettings_v[6];
#endif
#ifdef AXIS_FENCE
#define g_progressWentUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x11b000 : g_fence + 0x11affc))
#else
extern u8 g_progressWentUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcCameraBox_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x11d000 : g_fence + 0x11cf68))
#else
extern u32 g_armcCameraBox_v[38];
#endif
#ifdef AXIS_FENCE
#define g_armcZoom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x11f000 : g_fence + 0x11effc))
#else
extern u8 g_armcZoom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_colourChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x121000 : g_fence + 0x120ffc))
#else
extern u8 g_colourChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fpsSecondStart_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x123000 : g_fence + 0x122ff8))
#else
extern u8 g_fpsSecondStart_v[8];
#endif
#ifdef AXIS_FENCE
#define g_menuFrameCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x125000 : g_fence + 0x124ffc))
#else
extern u8 g_menuFrameCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_messageBoxArgs_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x127000 : g_fence + 0x126ffc))
#else
extern u8 g_messageBoxArgs_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedStartupWord3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x129000 : g_fence + 0x128ffc))
#else
extern u8 g_unusedStartupWord3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fpsFrameClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x12b000 : g_fence + 0x12aff8))
#else
extern u8 g_fpsFrameClock_v[8];
#endif
#ifdef AXIS_FENCE
#define g_frameRate_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x12d000 : g_fence + 0x12cff8))
#else
extern u8 g_frameRate_v[8];
#endif
#ifdef AXIS_FENCE
#define g_unusedStartupWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x12f000 : g_fence + 0x12effc))
#else
extern u8 g_unusedStartupWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fpsSecondSoFar_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x131000 : g_fence + 0x130ff8))
#else
extern u8 g_fpsSecondSoFar_v[8];
#endif
#ifdef AXIS_FENCE
#define g_fps_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x133000 : g_fence + 0x132ffc))
#else
extern u8 g_fps_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loadStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x135000 : g_fence + 0x134ffc))
#else
extern u8 g_loadStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_introZoom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x137000 : g_fence + 0x136ffc))
#else
extern u8 g_introZoom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPanelMoving_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x139000 : g_fence + 0x138ffc))
#else
extern u8 g_setupPanelMoving_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupSoundRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x13b000 : g_fence + 0x13aff0))
#else
extern int g_setupSoundRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPressedClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x13d000 : g_fence + 0x13cffc))
#else
extern u8 g_setupPressedClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_graphicEdited_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x13f000 : g_fence + 0x13efe4))
#else
extern u32 g_graphicEdited_v[7];
#endif
#ifdef AXIS_FENCE
#define g_bindPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x141000 : g_fence + 0x140ffc))
#else
extern u8 g_bindPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x143000 : g_fence + 0x142ffc))
#else
extern u8 g_setupPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupTunnelDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x145000 : g_fence + 0x144ffc))
#else
extern u8 g_setupTunnelDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bindWaiting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x147000 : g_fence + 0x146ffc))
#else
extern u8 g_bindWaiting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupOptionsTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x149000 : g_fence + 0x148ffc))
#else
extern u8 g_setupOptionsTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupControlRect_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x14b000 : g_fence + 0x14aff0))
#else
extern int g_setupControlRect_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPressed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x14d000 : g_fence + 0x14cffc))
#else
extern u8 g_setupPressed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_soundEdited_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x14f000 : g_fence + 0x14eff0))
#else
extern int g_soundEdited_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupTunnelAlpha_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x151000 : g_fence + 0x150ffc))
#else
extern u8 g_setupTunnelAlpha_v[4];
#endif
#ifdef AXIS_FENCE
#define g_setupPanelPos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x153000 : g_fence + 0x152ffc))
#else
extern u8 g_setupPanelPos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_bindRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x155000 : g_fence + 0x154ffc))
#else
extern u8 g_bindRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_controlsEdit_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x157000 : g_fence + 0x156ef0))
#else
extern int g_controlsEdit_v[68];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveStarted_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x159000 : g_fence + 0x158ffc))
#else
extern u8 g_armcMoveStarted_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuCamX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15b000 : g_fence + 0x15affc))
#else
extern u8 g_menuCamX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_freeCamHeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15d000 : g_fence + 0x15cffc))
#else
extern u8 g_freeCamHeight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuCamZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x15f000 : g_fence + 0x15effc))
#else
extern u8 g_menuCamZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveEyeX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x161000 : g_fence + 0x160ffc))
#else
extern u8 g_armcMoveEyeX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveEyeY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x163000 : g_fence + 0x162ffc))
#else
extern u8 g_armcMoveEyeY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveEyeZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x165000 : g_fence + 0x164ffc))
#else
extern u8 g_armcMoveEyeZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookSin_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x167000 : g_fence + 0x166ffc))
#else
extern u8 g_armcLookSin_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookTilt_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x169000 : g_fence + 0x168ffc))
#else
extern u8 g_armcLookTilt_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookCos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x16b000 : g_fence + 0x16affc))
#else
extern u8 g_armcLookCos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveTargetX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x16d000 : g_fence + 0x16cffc))
#else
extern u8 g_armcMoveTargetX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveTargetY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x16f000 : g_fence + 0x16effc))
#else
extern u8 g_armcMoveTargetY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcMoveTargetZ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x171000 : g_fence + 0x170ffc))
#else
extern u8 g_armcMoveTargetZ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_debugValue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x173000 : g_fence + 0x172ffc))
#else
extern u8 g_debugValue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedArmcMoveWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x175000 : g_fence + 0x174ffc))
#else
extern u8 g_unusedArmcMoveWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedPostMatchFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x177000 : g_fence + 0x176ffc))
#else
extern u8 g_unusedPostMatchFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_watchChatOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x179000 : g_fence + 0x178ffc))
#else
extern u8 g_watchChatOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleLevel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x17b000 : g_fence + 0x17affc))
#else
extern u8 g_titleLevel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titlePoints_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x17d000 : g_fence + 0x17cffc))
#else
extern u8 g_titlePoints_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleRating_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x17f000 : g_fence + 0x17effc))
#else
extern u8 g_titleRating_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleScore_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x181000 : g_fence + 0x180ffc))
#else
extern u8 g_titleScore_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleWins_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x183000 : g_fence + 0x182ffc))
#else
extern u8 g_titleWins_v[4];
#endif
#ifdef AXIS_FENCE
#define g_titleLosses_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x185000 : g_fence + 0x184ffc))
#else
extern u8 g_titleLosses_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikMouse1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x187000 : g_fence + 0x186ffc))
#else
extern u8 g_dikMouse1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuFramePhase_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x189000 : g_fence + 0x188ffc))
#else
extern u8 g_menuFramePhase_v[4];
#endif
#ifdef AXIS_FENCE
#define g_enteringMenus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x18b000 : g_fence + 0x18affc))
#else
extern u8 g_enteringMenus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_showCmd_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x18d000 : g_fence + 0x18cffc))
#else
extern u8 g_showCmd_v[4];
#endif
#ifdef AXIS_FENCE
#define g_playerName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x18f000 : g_fence + 0x18efd0))
#else
extern char g_playerName_v[48];
#endif
#ifdef AXIS_FENCE
#define g_arenaGameSetUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x191000 : g_fence + 0x190ffc))
#else
extern u8 g_arenaGameSetUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_connectStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x193000 : g_fence + 0x192ffc))
#else
extern u8 g_connectStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mouseWheelTurned_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x195000 : g_fence + 0x194ffc))
#else
extern u8 g_mouseWheelTurned_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mouseWheel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x197000 : g_fence + 0x196ffc))
#else
extern u8 g_mouseWheel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mouseClicked_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x199000 : g_fence + 0x198ff4))
#else
extern int g_mouseClicked_v[3];
#endif
#ifdef AXIS_FENCE
#define g_mouseButtonsHeld_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x19b000 : g_fence + 0x19aff4))
#else
extern int g_mouseButtonsHeld_v[3];
#endif
#ifdef AXIS_FENCE
#define g_controls_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x19d000 : g_fence + 0x19cef0))
#else
extern int g_controls_v[68];
#endif
#ifdef AXIS_FENCE
#define g_tunnelPulseStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x19f000 : g_fence + 0x19effc))
#else
extern u8 g_tunnelPulseStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverAnswerIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a1000 : g_fence + 0x1a0ffc))
#else
extern u8 g_serverAnswerIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuEye_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x1a3000 : g_fence + 0x1a2ff4))
#else
extern float g_menuEye_v[3];
#endif
#ifdef AXIS_FENCE
#define g_arenaMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1a5000 : g_fence + 0x1a4ff8))
#else
extern int g_arenaMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_panelGlowStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a7000 : g_fence + 0x1a6ffc))
#else
extern u8 g_panelGlowStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyListRow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1a9000 : g_fence + 0x1a8ffc))
#else
extern u8 g_lobbyListRow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_camPoints_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x1ab000 : g_fence + 0x1aafb0))
#else
extern float g_camPoints_v[20];
#endif
#ifdef AXIS_FENCE
#define g_dikF11_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ad000 : g_fence + 0x1acffc))
#else
extern u8 g_dikF11_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedMenuReturnWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1af000 : g_fence + 0x1aeffc))
#else
extern u8 g_unusedMenuReturnWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikNone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b1000 : g_fence + 0x1b0ffc))
#else
extern u8 g_dikNone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ladderMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1b3000 : g_fence + 0x1b2ff8))
#else
extern int g_ladderMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_roomSettingsName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x1b5000 : g_fence + 0x1b4fd0))
#else
extern char g_roomSettingsName_v[48];
#endif
#ifdef AXIS_FENCE
#define g_dikRAlt_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b7000 : g_fence + 0x1b6ffc))
#else
extern u8 g_dikRAlt_v[4];
#endif
#ifdef AXIS_FENCE
#define g_characterTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1b9000 : g_fence + 0x1b8ffc))
#else
extern u8 g_characterTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fovKeys_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1bb000 : g_fence + 0x1baffc))
#else
extern u8 g_fovKeys_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1bd000 : g_fence + 0x1bcffc))
#else
extern u8 g_dik1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1bf000 : g_fence + 0x1beffc))
#else
extern u8 g_dik2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c1000 : g_fence + 0x1c0ffc))
#else
extern u8 g_dik3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dik4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c3000 : g_fence + 0x1c2ffc))
#else
extern u8 g_dik4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_crosshairTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c5000 : g_fence + 0x1c4ffc))
#else
extern u8 g_crosshairTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuTunnelTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c7000 : g_fence + 0x1c6ffc))
#else
extern u8 g_menuTunnelTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikA_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1c9000 : g_fence + 0x1c8ffc))
#else
extern u8 g_dikA_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikC_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1cb000 : g_fence + 0x1caffc))
#else
extern u8 g_dikC_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikD_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1cd000 : g_fence + 0x1ccffc))
#else
extern u8 g_dikD_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikG_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1cf000 : g_fence + 0x1ceffc))
#else
extern u8 g_dikG_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikI_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d1000 : g_fence + 0x1d0ffc))
#else
extern u8 g_dikI_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikJ_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d3000 : g_fence + 0x1d2ffc))
#else
extern u8 g_dikJ_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikL_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d5000 : g_fence + 0x1d4ffc))
#else
extern u8 g_dikL_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikM_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d7000 : g_fence + 0x1d6ffc))
#else
extern u8 g_dikM_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikN_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1d9000 : g_fence + 0x1d8ffc))
#else
extern u8 g_dikN_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikO_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1db000 : g_fence + 0x1daffc))
#else
extern u8 g_dikO_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikP_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1dd000 : g_fence + 0x1dcffc))
#else
extern u8 g_dikP_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikR_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1df000 : g_fence + 0x1deffc))
#else
extern u8 g_dikR_v[4];
#endif
#ifdef AXIS_FENCE
#define g_screenCentreX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e1000 : g_fence + 0x1e0ffc))
#else
extern u8 g_screenCentreX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikS_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e3000 : g_fence + 0x1e2ffc))
#else
extern u8 g_dikS_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikT_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e5000 : g_fence + 0x1e4ffc))
#else
extern u8 g_dikT_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikW_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e7000 : g_fence + 0x1e6ffc))
#else
extern u8 g_dikW_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1e9000 : g_fence + 0x1e8ffc))
#else
extern u8 g_dikX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_projMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1eb000 : g_fence + 0x1eaffc))
#else
extern u8 g_projMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_listRefreshPeriod_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ed000 : g_fence + 0x1ecffc))
#else
extern u8 g_listRefreshPeriod_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ctrlMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x1ef000 : g_fence + 0x1eeff8))
#else
extern int g_ctrlMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_roomRecName_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x1f1000 : g_fence + 0x1f0fd0))
#else
extern char g_roomRecName_v[48];
#endif
#ifdef AXIS_FENCE
#define g_dikSpace_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f3000 : g_fence + 0x1f2ffc))
#else
extern u8 g_dikSpace_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchRunning_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f5000 : g_fence + 0x1f4ffc))
#else
extern u8 g_matchRunning_v[4];
#endif
#ifdef AXIS_FENCE
#define g_desktopWidth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1f7000 : g_fence + 0x1f6ffc))
#else
extern u8 g_desktopWidth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuLook_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x1f9000 : g_fence + 0x1f8ff4))
#else
extern float g_menuLook_v[3];
#endif
#ifdef AXIS_FENCE
#define g_dikZ_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1fb000 : g_fence + 0x1faffc))
#else
extern u8 g_dikZ_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikTab_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1fd000 : g_fence + 0x1fcffc))
#else
extern u8 g_dikTab_v[4];
#endif
#ifdef AXIS_FENCE
#define g_screenCentreY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x1ff000 : g_fence + 0x1feffc))
#else
extern u8 g_screenCentreY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_panelHovered_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x201000 : g_fence + 0x200ffc))
#else
extern u8 g_panelHovered_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEscape_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x203000 : g_fence + 0x202ffc))
#else
extern u8 g_dikEscape_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLCtrl_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x205000 : g_fence + 0x204ffc))
#else
extern u8 g_dikLCtrl_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x207000 : g_fence + 0x206ffc))
#else
extern u8 g_gameListTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyListPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x209000 : g_fence + 0x208ffc))
#else
extern u8 g_lobbyListPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_panelGlow_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x20b000 : g_fence + 0x20affc))
#else
extern u8 g_panelGlow_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapPreviewChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x20d000 : g_fence + 0x20cffc))
#else
extern u8 g_mapPreviewChanged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_messages_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x20f000 : g_fence + 0x20eb00))
#else
extern char g_messages_v[128256];
#endif
#ifdef AXIS_FENCE
#define g_dikDown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x230000 : g_fence + 0x22fffc))
#else
extern u8 g_dikDown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_startedByLauncher_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x232000 : g_fence + 0x231ffc))
#else
extern u8 g_startedByLauncher_v[4];
#endif
#ifdef AXIS_FENCE
#define g_camAims_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x234000 : g_fence + 0x233fb0))
#else
extern float g_camAims_v[20];
#endif
#ifdef AXIS_FENCE
#define g_desktopDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x236000 : g_fence + 0x235ffc))
#else
extern u8 g_desktopDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuLookHome_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x238000 : g_fence + 0x237ff4))
#else
extern float g_menuLookHome_v[3];
#endif
#ifdef AXIS_FENCE
#define g_unusedStartupWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x23a000 : g_fence + 0x239ffc))
#else
extern u8 g_unusedStartupWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x23c000 : g_fence + 0x23bff8))
#else
extern int g_mainMenuTextures_v[2];
#endif
#ifdef AXIS_FENCE
#define g_desktopDC_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x23e000 : g_fence + 0x23dffc))
#else
extern u8 g_desktopDC_v[4];
#endif
#ifdef AXIS_FENCE
#define g_searchResult_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x240000 : g_fence + 0x23fffc))
#else
extern u8 g_searchResult_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEscape_2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x242000 : g_fence + 0x241ffc))
#else
extern u8 g_dikEscape_2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikWheelUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x244000 : g_fence + 0x243ffc))
#else
extern u8 g_dikWheelUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_graphicSettings_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x246000 : g_fence + 0x245fe4))
#else
extern int g_graphicSettings_v[7];
#endif
#ifdef AXIS_FENCE
#define g_lastPanel_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x248000 : g_fence + 0x247ffc))
#else
extern u8 g_lastPanel_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaLeaving_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x24a000 : g_fence + 0x249ffc))
#else
extern u8 g_arenaLeaving_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedRoomListWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x24c000 : g_fence + 0x24bffc))
#else
extern u8 g_unusedRoomListWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_armcLookYaw_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x24e000 : g_fence + 0x24dffc))
#else
extern u8 g_armcLookYaw_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapPreviewTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x250000 : g_fence + 0x24fffc))
#else
extern u8 g_mapPreviewTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_excludedKey_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x252000 : g_fence + 0x251ffc))
#else
extern u8 g_excludedKey_v[4];
#endif
#ifdef AXIS_FENCE
#define g_spiralTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x254000 : g_fence + 0x253fe8))
#else
extern int g_spiralTextures_v[6];
#endif
#ifdef AXIS_FENCE
#define g_dikWheelDown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x256000 : g_fence + 0x255ffc))
#else
extern u8 g_dikWheelDown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomSearchAnswerIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x258000 : g_fence + 0x257ffc))
#else
extern u8 g_roomSearchAnswerIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyReply_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x25a000 : g_fence + 0x259ffc))
#else
extern u8 g_lobbyReply_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLAlt_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x25c000 : g_fence + 0x25bffc))
#else
extern u8 g_dikLAlt_v[4];
#endif
#ifdef AXIS_FENCE
#define g_frameCounter40_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x25e000 : g_fence + 0x25dffc))
#else
extern u8 g_frameCounter40_v[4];
#endif
#ifdef AXIS_FENCE
#define g_introTextures_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x260000 : g_fence + 0x25ffe0))
#else
extern int g_introTextures_v[8];
#endif
#ifdef AXIS_FENCE
#define g_dikRCtrl_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x262000 : g_fence + 0x261ffc))
#else
extern u8 g_dikRCtrl_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tunnelRings_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x264000 : g_fence + 0x263ffc))
#else
extern u8 g_tunnelRings_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x266000 : g_fence + 0x265ffc))
#else
extern u8 g_dikLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikEnter_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x268000 : g_fence + 0x267ffc))
#else
extern u8 g_dikEnter_v[4];
#endif
#ifdef AXIS_FENCE
#define g_menuEyeHome_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x26a000 : g_fence + 0x269ff4))
#else
extern float g_menuEyeHome_v[3];
#endif
#ifdef AXIS_FENCE
#define g_dikUp_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x26c000 : g_fence + 0x26bffc))
#else
extern u8 g_dikUp_v[4];
#endif
#ifdef AXIS_FENCE
#define g_buttonTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x26e000 : g_fence + 0x26dffc))
#else
extern u8 g_buttonTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikRShift_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x270000 : g_fence + 0x26fffc))
#else
extern u8 g_dikRShift_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dikRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x272000 : g_fence + 0x271ffc))
#else
extern u8 g_dikRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_timerClocks_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x274000 : g_fence + 0x273ff0))
#else
extern u32 g_timerClocks_v[4];
#endif
#ifdef AXIS_FENCE
#define g_replayRunning_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x276000 : g_fence + 0x275ffc))
#else
extern u8 g_replayRunning_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mainMenuFadingIn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x278000 : g_fence + 0x277ffc))
#else
extern u8 g_mainMenuFadingIn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pixelFormatFilled_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x27a000 : g_fence + 0x279fff))
#else
extern u8 g_pixelFormatFilled_v[1];
#endif
#ifdef AXIS_FENCE
#define g_timerRepeatCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x27c000 : g_fence + 0x27bffc))
#else
extern u8 g_timerRepeatCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_directInputMade_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x27e000 : g_fence + 0x27dffc))
#else
extern u8 g_directInputMade_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fieldTabKey_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x280000 : g_fence + 0x27fffc))
#else
extern u8 g_fieldTabKey_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLine_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x282000 : g_fence + 0x281c00))
#else
extern char g_chatLine_v[1024];
#endif
#ifdef AXIS_FENCE
#define g_typedLength_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x284000 : g_fence + 0x283ffc))
#else
extern u8 g_typedLength_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListClickTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x286000 : g_fence + 0x285ffc))
#else
extern u8 g_gameListClickTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomMode_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x288000 : g_fence + 0x287ffc))
#else
extern u8 g_roomMode_v[4];
#endif
#ifdef AXIS_FENCE
#define g_retypePassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x28a000 : g_fence + 0x289ffc))
#else
extern u8 g_retypePassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedRoomWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x28c000 : g_fence + 0x28bffc))
#else
extern u8 g_unusedRoomWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPrevPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x28e000 : g_fence + 0x28dffc))
#else
extern u8 g_roomListPrevPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPrev_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x290000 : g_fence + 0x28fffc))
#else
extern u8 g_roomListPrev_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingEmail_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x292000 : g_fence + 0x291ffc))
#else
extern u8 g_editingEmail_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPrevRank_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x294000 : g_fence + 0x293ffc))
#else
extern u8 g_roomListPrevRank_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedLoginWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x296000 : g_fence + 0x295ffc))
#else
extern u8 g_unusedLoginWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListLoaded_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x298000 : g_fence + 0x297ffc))
#else
extern u8 g_gameListLoaded_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingAccountName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x29a000 : g_fence + 0x299ffc))
#else
extern u8 g_typingAccountName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListClickArmed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x29c000 : g_fence + 0x29bffc))
#else
extern u8 g_gameListClickArmed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingRequestPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x29e000 : g_fence + 0x29dffc))
#else
extern u8 g_rankingRequestPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountNotice_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a0000 : g_fence + 0x29fffc))
#else
extern u8 g_accountNotice_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a2000 : g_fence + 0x2a1ffc))
#else
extern u8 g_roomLoginLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a4000 : g_fence + 0x2a3ffc))
#else
extern u8 g_roomLoginTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLoginBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a6000 : g_fence + 0x2a5ffc))
#else
extern u8 g_roomLoginBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPanelLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2a8000 : g_fence + 0x2a7ffc))
#else
extern u8 g_accountPanelLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPanelTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2aa000 : g_fence + 0x2a9ffc))
#else
extern u8 g_accountPanelTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPanelRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ac000 : g_fence + 0x2abffc))
#else
extern u8 g_accountPanelRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_accountPanelBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ae000 : g_fence + 0x2adffc))
#else
extern u8 g_accountPanelBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingPasswordRepeat_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b0000 : g_fence + 0x2afffc))
#else
extern u8 g_editingPasswordRepeat_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingAccountPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b2000 : g_fence + 0x2b1ffc))
#else
extern u8 g_editingAccountPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingRoomName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b4000 : g_fence + 0x2b3ffc))
#else
extern u8 g_editingRoomName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListDistanceLimit_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b6000 : g_fence + 0x2b5ffc))
#else
extern u8 g_roomListDistanceLimit_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingGamePassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2b8000 : g_fence + 0x2b7ffc))
#else
extern u8 g_typingGamePassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingHaveList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ba000 : g_fence + 0x2b9ffc))
#else
extern u8 g_rankingHaveList_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingAccountPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2bc000 : g_fence + 0x2bbffc))
#else
extern u8 g_typingAccountPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomRefreshing_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2be000 : g_fence + 0x2bdffc))
#else
extern u8 g_roomRefreshing_v[4];
#endif
#ifdef AXIS_FENCE
#define g_openLoginName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c0000 : g_fence + 0x2bfffc))
#else
extern u8 g_openLoginName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomGameListLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c2000 : g_fence + 0x2c1ffc))
#else
extern u8 g_roomGameListLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomGameListTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c4000 : g_fence + 0x2c3ffc))
#else
extern u8 g_roomGameListTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomGameListRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c6000 : g_fence + 0x2c5ffc))
#else
extern u8 g_roomGameListRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomGameListBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2c8000 : g_fence + 0x2c7ffc))
#else
extern u8 g_roomGameListBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPages_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ca000 : g_fence + 0x2c9ffc))
#else
extern u8 g_roomListPages_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameListJoinClicked_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2cc000 : g_fence + 0x2cbffc))
#else
extern u8 g_gameListJoinClicked_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingAccountRepeat_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ce000 : g_fence + 0x2cdffc))
#else
extern u8 g_typingAccountRepeat_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomJoined_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d0000 : g_fence + 0x2cfffc))
#else
extern u8 g_roomJoined_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomTunnelDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d2000 : g_fence + 0x2d1ffc))
#else
extern u8 g_roomTunnelDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingOldPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d4000 : g_fence + 0x2d3ffc))
#else
extern u8 g_editingOldPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomSearching_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d6000 : g_fence + 0x2d5ffc))
#else
extern u8 g_roomSearching_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomAnswerAwaited_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2d8000 : g_fence + 0x2d7ffc))
#else
extern u8 g_roomAnswerAwaited_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editingRoomPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2da000 : g_fence + 0x2d9ffc))
#else
extern u8 g_editingRoomPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2dc000 : g_fence + 0x2dbffc))
#else
extern u8 g_roomListPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingRoomPassword_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2de000 : g_fence + 0x2ddffc))
#else
extern u8 g_typingRoomPassword_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomChatting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e0000 : g_fence + 0x2dfffc))
#else
extern u8 g_roomChatting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingWaiting_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e2000 : g_fence + 0x2e1ffc))
#else
extern u8 g_rankingWaiting_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomPanelBrightness_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e4000 : g_fence + 0x2e3ffc))
#else
extern u8 g_roomPanelBrightness_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomListRefreshTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e6000 : g_fence + 0x2e5ffc))
#else
extern u8 g_roomListRefreshTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomPopup_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2e8000 : g_fence + 0x2e7ffc))
#else
extern u8 g_roomPopup_v[4];
#endif
#ifdef AXIS_FENCE
#define g_joinPasswordTyped_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ea000 : g_fence + 0x2e9ffc))
#else
extern u8 g_joinPasswordTyped_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingAccountEmail_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ec000 : g_fence + 0x2ebffc))
#else
extern u8 g_typingAccountEmail_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomAwaitingServer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2ee000 : g_fence + 0x2edffc))
#else
extern u8 g_roomAwaitingServer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loginFormLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2f0000 : g_fence + 0x2efffc))
#else
extern u8 g_loginFormLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_loginFormBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2f2000 : g_fence + 0x2f1ffc))
#else
extern u8 g_loginFormBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomDialogOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2f4000 : g_fence + 0x2f3ffc))
#else
extern u8 g_roomDialogOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingLast_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2f6000 : g_fence + 0x2f5ffc))
#else
extern u8 g_rankingLast_v[4];
#endif
#ifdef AXIS_FENCE
#define g_typingGameName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2f8000 : g_fence + 0x2f7ffc))
#else
extern u8 g_typingGameName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2fa000 : g_fence + 0x2f9ffc))
#else
extern u8 g_roomState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomRequestOut_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2fc000 : g_fence + 0x2fbffc))
#else
extern u8 g_roomRequestOut_v[4];
#endif
#ifdef AXIS_FENCE
#define g_rankingFirst_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x2fe000 : g_fence + 0x2fdffc))
#else
extern u8 g_rankingFirst_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomNameSum_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x300000 : g_fence + 0x2ffffc))
#else
extern u8 g_roomNameSum_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomConnected_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x302000 : g_fence + 0x301ffc))
#else
extern u8 g_roomConnected_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomLeaveDialog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x304000 : g_fence + 0x303ffc))
#else
extern u8 g_roomLeaveDialog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_languageId_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x306000 : g_fence + 0x305ffe))
#else
extern u8 g_languageId_v[2];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckSeconds_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x308000 : g_fence + 0x307ffc))
#else
extern u8 g_clockCheckSeconds_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedLastWParam_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x30a000 : g_fence + 0x309ffc))
#else
extern u8 g_unusedLastWParam_v[4];
#endif
#ifdef AXIS_FENCE
#define g_editOldProc_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x30c000 : g_fence + 0x30bffc))
#else
extern u8 g_editOldProc_v[4];
#endif
#ifdef AXIS_FENCE
#define g_argCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x30e000 : g_fence + 0x30dffc))
#else
extern u8 g_argCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_launchMessage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x310000 : g_fence + 0x30fffc))
#else
extern u8 g_launchMessage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckTick_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x312000 : g_fence + 0x311ffc))
#else
extern u8 g_clockCheckTick_v[4];
#endif
#ifdef AXIS_FENCE
#define g_inputFont_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x314000 : g_fence + 0x313ffc))
#else
extern u8 g_inputFont_v[4];
#endif
#ifdef AXIS_FENCE
#define g_startTicks_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x316000 : g_fence + 0x315ffc))
#else
extern u8 g_startTicks_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckTickSeconds_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x318000 : g_fence + 0x317ffc))
#else
extern u8 g_clockCheckTickSeconds_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedInitWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x31a000 : g_fence + 0x319ffc))
#else
extern u8 g_unusedInitWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLineDone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x31c000 : g_fence + 0x31bffc))
#else
extern u8 g_chatLineDone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_clockCheckClosed_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x31e000 : g_fence + 0x31dffc))
#else
extern u8 g_clockCheckClosed_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x320000 : g_fence + 0x31fffc))
#else
extern u8 g_mapSelectLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x322000 : g_fence + 0x321ffc))
#else
extern u8 g_mapSelectTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x324000 : g_fence + 0x323ffc))
#else
extern u8 g_mapSelectRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapSelectBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x326000 : g_fence + 0x325ffc))
#else
extern u8 g_mapSelectBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fileList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x328000 : g_fence + 0x327000))
#else
extern u8 g_fileList_v[69632];
#endif
#ifdef AXIS_FENCE
#define g_unusedReplayListWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x33a000 : g_fence + 0x339ffc))
#else
extern u8 g_unusedReplayListWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingStart_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x33c000 : g_fence + 0x33bffc))
#else
extern u8 g_briefingStart_v[4];
#endif
#ifdef AXIS_FENCE
#define g_skirmishDrawBackground_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x33e000 : g_fence + 0x33dffc))
#else
extern u8 g_skirmishDrawBackground_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingSource_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x340000 : g_fence + 0x33fffc))
#else
extern u8 g_briefingSource_v[4];
#endif
#ifdef AXIS_FENCE
#define g_settingsState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x342000 : g_fence + 0x341ffc))
#else
extern u8 g_settingsState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingShown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x344000 : g_fence + 0x343ffc))
#else
extern u8 g_briefingShown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_settingsPage_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x346000 : g_fence + 0x345ffc))
#else
extern u8 g_settingsPage_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingEnd_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x348000 : g_fence + 0x347ffc))
#else
extern u8 g_briefingEnd_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedMissionSaveWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x34a000 : g_fence + 0x349ffc))
#else
extern u8 g_unusedMissionSaveWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missions_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x34c000 : g_fence + 0x34b278))
#else
extern u8 g_missions_v[7560];
#endif
#ifdef AXIS_FENCE
#define g_briefingDone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x34f000 : g_fence + 0x34effc))
#else
extern u8 g_briefingDone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_undoDepth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x351000 : g_fence + 0x350ffc))
#else
extern u8 g_undoDepth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingText_v ((char *)(AXIS_FENCE == 2 ? g_fence + 0x353000 : g_fence + 0x3529c0))
#else
extern char g_briefingText_v[1600];
#endif
#ifdef AXIS_FENCE
#define g_briefingRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x355000 : g_fence + 0x354ffc))
#else
extern u8 g_briefingRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x357000 : g_fence + 0x356ffc))
#else
extern u8 g_briefingBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_briefingClock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x359000 : g_fence + 0x358ffc))
#else
extern u8 g_briefingClock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileProgressSaved_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x35b000 : g_fence + 0x35affc))
#else
extern u8 g_profileProgressSaved_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionPreviewDue_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x35d000 : g_fence + 0x35cffc))
#else
extern u8 g_missionPreviewDue_v[4];
#endif
#ifdef AXIS_FENCE
#define g_missionShown_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x35f000 : g_fence + 0x35effc))
#else
extern u8 g_missionShown_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchChatCaretY_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x361000 : g_fence + 0x360ffc))
#else
extern u8 g_matchChatCaretY_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchChatCaretX_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x363000 : g_fence + 0x362ffc))
#else
extern u8 g_matchChatCaretX_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatTyping_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x365000 : g_fence + 0x364ffc))
#else
extern u8 g_chatTyping_v[4];
#endif
#ifdef AXIS_FENCE
#define g_writeMatchLog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x367000 : g_fence + 0x366ffc))
#else
extern u8 g_writeMatchLog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchLogWritten_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x369000 : g_fence + 0x368ffc))
#else
extern u8 g_matchLogWritten_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchEndedByUser_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x36b000 : g_fence + 0x36affc))
#else
extern u8 g_matchEndedByUser_v[4];
#endif
#ifdef AXIS_FENCE
#define g_matchEndedByServer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x36d000 : g_fence + 0x36cffc))
#else
extern u8 g_matchEndedByServer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedProfileCameraWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x36f000 : g_fence + 0x36effc))
#else
extern u8 g_unusedProfileCameraWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotSelectBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x371000 : g_fence + 0x370ffc))
#else
extern u8 g_pilotSelectBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotSelectRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x373000 : g_fence + 0x372ffc))
#else
extern u8 g_pilotSelectRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileDialogOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x375000 : g_fence + 0x374ffc))
#else
extern u8 g_profileDialogOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileFrameStep_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x377000 : g_fence + 0x376ffc))
#else
extern u8 g_profileFrameStep_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chosenPilot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x379000 : g_fence + 0x378ffc))
#else
extern u8 g_chosenPilot_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileScreenReady_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x37b000 : g_fence + 0x37affc))
#else
extern u8 g_profileScreenReady_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pilotChosen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x37d000 : g_fence + 0x37cffc))
#else
extern u8 g_pilotChosen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x37f000 : g_fence + 0x37effc))
#else
extern u8 g_profilePageLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x381000 : g_fence + 0x380ffc))
#else
extern u8 g_profilePageTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageRight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x383000 : g_fence + 0x382ffc))
#else
extern u8 g_profilePageRight_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profilePageBottom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x385000 : g_fence + 0x384ffc))
#else
extern u8 g_profilePageBottom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newNameDialogTop_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x387000 : g_fence + 0x386ffc))
#else
extern u8 g_newNameDialogTop_v[4];
#endif
#ifdef AXIS_FENCE
#define g_newNameDialogLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x389000 : g_fence + 0x388ffc))
#else
extern u8 g_newNameDialogLeft_v[4];
#endif
#ifdef AXIS_FENCE
#define g_profileFrameAlpha_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x38b000 : g_fence + 0x38affc))
#else
extern u8 g_profileFrameAlpha_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageKind_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x38d000 : g_fence + 0x38cffc))
#else
extern u8 g_netChatMessageKind_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x38f000 : g_fence + 0x38effc))
#else
extern u8 g_netChatMessageWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x391000 : g_fence + 0x390ffc))
#else
extern u8 g_netChatMessageWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netChatMessageText_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x393000 : g_fence + 0x392ffc))
#else
extern u8 g_netChatMessageText_v[4];
#endif
#ifdef AXIS_FENCE
#define g_slotTakenFlag_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x395000 : g_fence + 0x394ffc))
#else
extern u8 g_slotTakenFlag_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netBlockSize_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x397000 : g_fence + 0x396ffc))
#else
extern u8 g_netBlockSize_v[4];
#endif
#ifdef AXIS_FENCE
#define g_chatLog_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x399000 : g_fence + 0x398ffc))
#else
extern u8 g_chatLog_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netHostGone_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x39b000 : g_fence + 0x39affc))
#else
extern u8 g_netHostGone_v[4];
#endif
#ifdef AXIS_FENCE
#define g_watchedSlot_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x39d000 : g_fence + 0x39cfff))
#else
extern u8 g_watchedSlot_v[1];
#endif
#ifdef AXIS_FENCE
#define g_chatLogged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x39f000 : g_fence + 0x39effc))
#else
extern u8 g_chatLogged_v[4];
#endif
#ifdef AXIS_FENCE
#define g_roomList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3a1000 : g_fence + 0x3a01c0))
#else
extern u8 g_roomList_v[7744];
#endif
#ifdef AXIS_FENCE
#define g_lobbyPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3a4000 : g_fence + 0x3a3ffc))
#else
extern u8 g_lobbyPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerPending_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3a6000 : g_fence + 0x3a5ffc))
#else
extern u8 g_gameServerPending_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverListCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3a8000 : g_fence + 0x3a7ffc))
#else
extern u8 g_serverListCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverConnectionState_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3aa000 : g_fence + 0x3a9ffc))
#else
extern u8 g_serverConnectionState_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyStatus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3ac000 : g_fence + 0x3abffc))
#else
extern u8 g_lobbyStatus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerStatus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3ae000 : g_fence + 0x3adffc))
#else
extern u8 g_gameServerStatus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerAnswer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3b0000 : g_fence + 0x3afffc))
#else
extern u8 g_gameServerAnswer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_gameServerAnswer15_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3b2000 : g_fence + 0x3b1ffc))
#else
extern u8 g_gameServerAnswer15_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyConnectStatus_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3b4000 : g_fence + 0x3b3ffc))
#else
extern u8 g_lobbyConnectStatus_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplaySessionList_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3b6000 : g_fence + 0x3b5ffc))
#else
extern u8 g_dplaySessionList_v[4];
#endif
#ifdef AXIS_FENCE
#define g_netQueueOnline_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3b8000 : g_fence + 0x3b7ffc))
#else
extern u8 g_netQueueOnline_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaSessionOpen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3ba000 : g_fence + 0x3b9ffc))
#else
extern u8 g_arenaSessionOpen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplayLobby_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3bc000 : g_fence + 0x3bbffc))
#else
extern u8 g_dplayLobby_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplay_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3be000 : g_fence + 0x3bdffc))
#else
extern u8 g_dplay_v[4];
#endif
#ifdef AXIS_FENCE
#define g_connectionKind_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3c0000 : g_fence + 0x3bfffc))
#else
extern u8 g_connectionKind_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dplaySessionCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3c2000 : g_fence + 0x3c1ffc))
#else
extern u8 g_dplaySessionCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedSessionWord_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3c4000 : g_fence + 0x3c3ffc))
#else
extern u8 g_unusedSessionWord_v[4];
#endif
#ifdef AXIS_FENCE
#define g_localPlayerId_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3c6000 : g_fence + 0x3c5ffc))
#else
extern u8 g_localPlayerId_v[4];
#endif
#ifdef AXIS_FENCE
#define g_localPlayerData_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3c8000 : g_fence + 0x3c7ffc))
#else
extern u8 g_localPlayerData_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3ca000 : g_fence + 0x3c9ffc))
#else
extern u8 g_unusedDplayWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3cc000 : g_fence + 0x3cbffc))
#else
extern u8 g_unusedDplayWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord3_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3ce000 : g_fence + 0x3cdffc))
#else
extern u8 g_unusedDplayWord3_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedDplayWord4_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3d0000 : g_fence + 0x3cfffc))
#else
extern u8 g_unusedDplayWord4_v[4];
#endif
#ifdef AXIS_FENCE
#define g_connectionCopy_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3d2000 : g_fence + 0x3d1ffc))
#else
extern u8 g_connectionCopy_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serviceProviderCount_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3d4000 : g_fence + 0x3d3ffc))
#else
extern u8 g_serviceProviderCount_v[4];
#endif
#ifdef AXIS_FENCE
#define g_arenaJoinTimer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3d6000 : g_fence + 0x3d5ffc))
#else
extern u8 g_arenaJoinTimer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_instanceGuid_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3d8000 : g_fence + 0x3d7ffc))
#else
extern u8 g_instanceGuid_v[4];
#endif
#ifdef AXIS_FENCE
#define g_storedConnection_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3da000 : g_fence + 0x3d9ffc))
#else
extern u8 g_storedConnection_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dpConnections_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x3dc000 : g_fence + 0x3dbff0))
#else
extern int g_dpConnections_v[4];
#endif
#ifdef AXIS_FENCE
#define g_hostAddressBlock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3de000 : g_fence + 0x3ddffc))
#else
extern u8 g_hostAddressBlock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_lobbyConnectionBlock_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3e0000 : g_fence + 0x3dfffc))
#else
extern u8 g_lobbyConnectionBlock_v[4];
#endif
#ifdef AXIS_FENCE
#define g_isHost_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3e2000 : g_fence + 0x3e1ffc))
#else
extern u8 g_isHost_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dpTimeout_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3e4000 : g_fence + 0x3e3ffc))
#else
extern u8 g_dpTimeout_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dpMaxBufferSize_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3e6000 : g_fence + 0x3e5ffc))
#else
extern u8 g_dpMaxBufferSize_v[4];
#endif
#ifdef AXIS_FENCE
#define g_dpMaxQueueSize_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3e8000 : g_fence + 0x3e7ffc))
#else
extern u8 g_dpMaxQueueSize_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pingDataEvent_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3ea000 : g_fence + 0x3e9ffc))
#else
extern u8 g_pingDataEvent_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedPingWord1_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3ec000 : g_fence + 0x3ebffc))
#else
extern u8 g_unusedPingWord1_v[4];
#endif
#ifdef AXIS_FENCE
#define g_unusedPingWord2_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3ee000 : g_fence + 0x3edffc))
#else
extern u8 g_unusedPingWord2_v[4];
#endif
#ifdef AXIS_FENCE
#define g_pingStopEvent_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3f0000 : g_fence + 0x3efffc))
#else
extern u8 g_pingStopEvent_v[4];
#endif
#ifdef AXIS_FENCE
#define g_serverNames_v ((u32 *)(AXIS_FENCE == 2 ? g_fence + 0x3f2000 : g_fence + 0x3f1c00))
#else
extern u32 g_serverNames_v[1280];
#endif
#ifdef AXIS_FENCE
#define g_ptxTablesReady_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3f5000 : g_fence + 0x3f4ffc))
#else
extern u8 g_ptxTablesReady_v[4];
#endif
#ifdef AXIS_FENCE
#define g_soundBaseVolume_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3f7000 : g_fence + 0x3f6ffc))
#else
extern u8 g_soundBaseVolume_v[4];
#endif
#ifdef AXIS_FENCE
#define g_directSound_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3f9000 : g_fence + 0x3f8ffc))
#else
extern u8 g_directSound_v[4];
#endif
#ifdef AXIS_FENCE
#define g_primarySoundBuffer_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3fb000 : g_fence + 0x3faffc))
#else
extern u8 g_primarySoundBuffer_v[4];
#endif
#ifdef AXIS_FENCE
#define g_soundOn_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3fd000 : g_fence + 0x3fcffc))
#else
extern u8 g_soundOn_v[4];
#endif
#ifdef AXIS_FENCE
#define g_glColourBits_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x3ff000 : g_fence + 0x3feffc))
#else
extern u8 g_glColourBits_v[4];
#endif
#ifdef AXIS_FENCE
#define g_fullScreen_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x401000 : g_fence + 0x400ffc))
#else
extern u8 g_fullScreen_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mapMissing_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x403000 : g_fence + 0x402ffc))
#else
extern u8 g_mapMissing_v[4];
#endif
#ifdef AXIS_FENCE
#define g_penFontNeverSet_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x405000 : g_fence + 0x404ffc))
#else
extern u8 g_penFontNeverSet_v[4];
#endif
#ifdef AXIS_FENCE
#define g_penFontTexture_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x407000 : g_fence + 0x406ffc))
#else
extern u8 g_penFontTexture_v[4];
#endif
#ifdef AXIS_FENCE
#define g_tan10Table_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x409000 : g_fence + 0x408fb8))
#else
extern float g_tan10Table_v[18];
#endif
#ifdef AXIS_FENCE
#define g_randTable_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x40b000 : g_fence + 0x40a000))
#else
extern int g_randTable_v[4096];
#endif
#ifdef AXIS_FENCE
#define g_tanTable_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x410000 : g_fence + 0x40f7c0))
#else
extern float g_tanTable_v[3600];
#endif
#ifdef AXIS_FENCE
#define g_cosTable_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x415000 : g_fence + 0x4147c0))
#else
extern float g_cosTable_v[3600];
#endif
#ifdef AXIS_FENCE
#define g_sinTable_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x41a000 : g_fence + 0x4197c0))
#else
extern float g_sinTable_v[3600];
#endif
#ifdef AXIS_FENCE
#define g_randPos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x41f000 : g_fence + 0x41effc))
#else
extern u8 g_randPos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciCallback_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x421000 : g_fence + 0x420ffc))
#else
extern u8 g_mciCallback_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciFrom_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x423000 : g_fence + 0x422ffc))
#else
extern u8 g_mciFrom_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciTo_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x425000 : g_fence + 0x424ffc))
#else
extern u8 g_mciTo_v[4];
#endif
#ifdef AXIS_FENCE
#define g_mciDevice_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x427000 : g_fence + 0x426ffc))
#else
extern u8 g_mciDevice_v[4];
#endif
#ifdef AXIS_FENCE
#define g_errorLogging_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x429000 : g_fence + 0x428ffc))
#else
extern u8 g_errorLogging_v[4];
#endif
#ifdef AXIS_FENCE
#define g_errorCleanupHook_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x42b000 : g_fence + 0x42affc))
#else
extern u8 g_errorCleanupHook_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxCbBlue_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x42d000 : g_fence + 0x42cc00))
#else
extern int g_ptxCbBlue_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxYCbCrTables_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x42f000 : g_fence + 0x42e000))
#else
extern int g_ptxYCbCrTables_v[2048];
#endif
#ifdef AXIS_FENCE
#define g_ptxBitPos_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x432000 : g_fence + 0x431ffc))
#else
extern u8 g_ptxBitPos_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxPixels_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x434000 : g_fence + 0x433000))
#else
extern u8 g_ptxPixels_v[262144];
#endif
#ifdef AXIS_FENCE
#define g_bitStream_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x475000 : g_fence + 0x474ffc))
#else
extern u8 g_bitStream_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxCbGreen_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x477000 : g_fence + 0x476c00))
#else
extern int g_ptxCbGreen_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxClampTable_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x479000 : g_fence + 0x478a80))
#else
extern u8 g_ptxClampTable_v[1408];
#endif
#ifdef AXIS_FENCE
#define g_ptxPlanes_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x47b000 : g_fence + 0x47a000))
#else
extern u8 g_ptxPlanes_v[262144];
#endif
#ifdef AXIS_FENCE
#define g_ptxCrRed_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x4bc000 : g_fence + 0x4bbc00))
#else
extern int g_ptxCrRed_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxLastDc_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4be000 : g_fence + 0x4bdffc))
#else
extern u8 g_ptxLastDc_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxCrGreen_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x4c0000 : g_fence + 0x4bfc00))
#else
extern int g_ptxCrGreen_v[256];
#endif
#ifdef AXIS_FENCE
#define g_ptxDequant_v ((float *)(AXIS_FENCE == 2 ? g_fence + 0x4c2000 : g_fence + 0x4c1e00))
#else
extern float g_ptxDequant_v[128];
#endif
#ifdef AXIS_FENCE
#define g_ptxQuant_v ((int *)(AXIS_FENCE == 2 ? g_fence + 0x4c4000 : g_fence + 0x4c3e00))
#else
extern int g_ptxQuant_v[128];
#endif
#ifdef AXIS_FENCE
#define g_ptxTable_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4c6000 : g_fence + 0x4c5ffc))
#else
extern u8 g_ptxTable_v[4];
#endif
#ifdef AXIS_FENCE
#define g_ptxData_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x4c8000 : g_fence + 0x4c7000))
#else
extern u8 g_ptxData_v[262144];
#endif
#ifdef AXIS_FENCE
#define g_logHook_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x509000 : g_fence + 0x508ffc))
#else
extern u8 g_logHook_v[4];
#endif
#ifdef AXIS_FENCE
#define g_currentStageName_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x50b000 : g_fence + 0x50affc))
#else
extern u8 g_currentStageName_v[4];
#endif
#ifdef AXIS_FENCE
#define g_displayModeChanged_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x50d000 : g_fence + 0x50cfff))
#else
extern u8 g_displayModeChanged_v[1];
#endif
#ifdef AXIS_FENCE
#define g_displayModeLeft_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x50f000 : g_fence + 0x50efff))
#else
extern u8 g_displayModeLeft_v[1];
#endif
#ifdef AXIS_FENCE
#define g_otherModeWidth_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x511000 : g_fence + 0x510ffc))
#else
extern u8 g_otherModeWidth_v[4];
#endif
#ifdef AXIS_FENCE
#define g_otherModeHeight_v ((u8 *)(AXIS_FENCE == 2 ? g_fence + 0x513000 : g_fence + 0x512ffc))
#else
extern u8 g_otherModeHeight_v[4];
#endif
