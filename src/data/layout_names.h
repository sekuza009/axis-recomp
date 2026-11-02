/* layout_names.h (tools/mkdatasrc.py): in AxisRC.exe (AXIS_DIRECT) the named globals that are members of
   g_rdata / g_data (src/data/layout.h) as those members; the others stay GAME_VAR (src/globals.h), which IMG()
   routes to the same place */
#pragma once
#include "layout.h"
extern struct GameRdata g_rdata;
extern struct GameData g_data;
#include "split.h"   /* (the variables split out of g_data) */
#undef g_accountClan
#define g_accountClan (*(int *)((u8 *)g_pilotStatsKept_v + 0x8))
#undef g_accountEmail
#define g_accountEmail ((char *)g_data.g_accountEmail_)
#undef g_accountName
#define g_accountName ((char *)g_data.g_accountName_)
#undef g_accountNotice
#define g_accountNotice (*(int *)g_accountNotice_v)
#undef g_accountOldPassword
#define g_accountOldPassword ((char *)g_data.g_accountOldPassword_)
#undef g_accountPacket
#define g_accountPacket (*(char * *)g_accountPacket_v)
#undef g_accountPanelBottom
#define g_accountPanelBottom (*(int *)g_accountPanelBottom_v)
#undef g_accountPanelLeft
#define g_accountPanelLeft (*(int *)g_accountPanelLeft_v)
#undef g_accountPanelRight
#define g_accountPanelRight (*(int *)g_accountPanelRight_v)
#undef g_accountPanelTop
#define g_accountPanelTop (*(int *)g_accountPanelTop_v)
#undef g_accountPassword
#define g_accountPassword ((char *)g_data.g_accountPassword_)
#undef g_accountPasswordRepeat
#define g_accountPasswordRepeat ((char *)g_data.g_accountPasswordRepeat_)
#undef g_accountRects
#define g_accountRects ((int *)g_accountRects_v)
#undef g_arenaBright
#define g_arenaBright ((u32 *)g_data.g_arenaBright_)
#undef g_arenaConfirming
#define g_arenaConfirming (*(int *)g_arenaConfirming_v)
#undef g_arenaCorporation
#define g_arenaCorporation (*(int *)g_arenaCorporation_v)
#undef g_arenaCreateRects
#define g_arenaCreateRects ((int *)g_arenaCreateRects_v)
#undef g_arenaCustomize
#define g_arenaCustomize (*(u8 *)((u8 *)g_playerName_v + 0x22))
#undef g_arenaDialogBoxRects
#define g_arenaDialogBoxRects ((int *)g_arenaDialogBoxRects_v)
#undef g_arenaDim
#define g_arenaDim ((u32 *)g_data.g_arenaDim_)
#undef g_arenaFileClan
#define g_arenaFileClan (g_data.g_arenaFileClan_)
#undef g_arenaFileClan4
#define g_arenaFileClan4 (g_data.g_arenaFileClan4_)
#undef g_arenaFileFragLimit
#define g_arenaFileFragLimit (g_data.g_arenaFileFragLimit_)
#undef g_arenaFileGameType
#define g_arenaFileGameType (g_data.g_arenaFileGameType_)
#undef g_arenaFileMap
#define g_arenaFileMap (g_data.g_arenaFileMap_)
#undef g_arenaFilePlayers
#define g_arenaFilePlayers (g_data.g_arenaFilePlayers_)
#undef g_arenaFragLimit
#define g_arenaFragLimit (*(u8 *)((u8 *)g_playerName_v + 0x24))
#undef g_arenaFragLimitTyped
#define g_arenaFragLimitTyped (*(u8 *)((u8 *)g_newArenaName_v + 0x24))
#undef g_arenaFull
#define g_arenaFull (*(int *)g_arenaFull_v)
#undef g_arenaGameListBottom
#define g_arenaGameListBottom (*(int *)g_arenaGameListBottom_v)
#undef g_arenaGameListLeft
#define g_arenaGameListLeft (*(int *)g_arenaGameListLeft_v)
#undef g_arenaGameListRects
#define g_arenaGameListRects ((int *)g_arenaGameListRects_v)
#undef g_arenaGameListRight
#define g_arenaGameListRight (*(int *)g_arenaGameListRight_v)
#undef g_arenaGameListTop
#define g_arenaGameListTop (*(int *)g_arenaGameListTop_v)
#undef g_arenaGameName
#define g_arenaGameName ((char *)g_arenaGameName_v)
#undef g_arenaGameSetUp
#define g_arenaGameSetUp (*(int *)g_arenaGameSetUp_v)
#undef g_arenaGameType
#define g_arenaGameType (*(u8 *)((u8 *)g_playerName_v + 0x23))
#undef g_arenaHaveList
#define g_arenaHaveList (*(int *)g_arenaHaveList_v)
#undef g_arenaInfoPacket
#define g_arenaInfoPacket (*(u8 * *)g_arenaInfoPacket_v)
#undef g_arenaJoinPending
#define g_arenaJoinPending (*(int *)g_arenaJoinPending_v)
#undef g_arenaJoinRow
#define g_arenaJoinRow (*(int *)g_arenaJoinRow_v)
#undef g_arenaJoinTimer
#define g_arenaJoinTimer (*(u32 *)g_arenaJoinTimer_v)
#undef g_arenaJoinWaiting
#define g_arenaJoinWaiting (*(int *)g_arenaJoinWaiting_v)
#undef g_arenaJoining
#define g_arenaJoining (*(int *)g_arenaJoining_v)
#undef g_arenaKeptCamX
#define g_arenaKeptCamX (*(float *)g_arenaKeptCamX_v)
#undef g_arenaKeptCamY
#define g_arenaKeptCamY (*(int *)g_arenaKeptCamY_v)
#undef g_arenaKeptCamZ
#define g_arenaKeptCamZ (*(int *)g_arenaKeptCamZ_v)
#undef g_arenaKeptLookX
#define g_arenaKeptLookX (*(int *)g_arenaKeptLookX_v)
#undef g_arenaKeptLookY
#define g_arenaKeptLookY (*(int *)g_arenaKeptLookY_v)
#undef g_arenaKeptLookZ
#define g_arenaKeptLookZ (*(int *)g_arenaKeptLookZ_v)
#undef g_arenaLeaving
#define g_arenaLeaving (*(int *)g_arenaLeaving_v)
#undef g_arenaListClickArmed
#define g_arenaListClickArmed (*(int *)g_arenaListClickArmed_v)
#undef g_arenaListFull
#define g_arenaListFull (*(int *)g_arenaListFull_v)
#undef g_arenaListRefreshTimer
#define g_arenaListRefreshTimer (*(float *)g_arenaListRefreshTimer_v)
#undef g_arenaLobbyMode
#define g_arenaLobbyMode (*(int *)g_arenaLobbyMode_v)
#undef g_arenaLobbyState
#define g_arenaLobbyState (*(int *)g_arenaLobbyState_v)
#undef g_arenaMap
#define g_arenaMap (*(signed char *)((u8 *)g_playerName_v + 0x20))
#undef g_arenaMapCount
#define g_arenaMapCount (*(int *)g_arenaMapCount_v)
#undef g_arenaMenuTextures
#define g_arenaMenuTextures ((int *)g_arenaMenuTextures_v)
#undef g_arenaMessageText
#define g_arenaMessageText (g_data.g_arenaMessageText_)
#undef g_arenaMessageText4
#define g_arenaMessageText4 (g_data.g_arenaMessageText4_)
#undef g_arenaName
#define g_arenaName ((char *)g_data.g_arenaName_)
#undef g_arenaNameDialogBottom
#define g_arenaNameDialogBottom (*(int *)g_arenaNameDialogBottom_v)
#undef g_arenaNameDialogLeft
#define g_arenaNameDialogLeft (*(int *)g_arenaNameDialogLeft_v)
#undef g_arenaNameDialogRects
#define g_arenaNameDialogRects ((int *)g_arenaNameDialogRects_v)
#undef g_arenaNameDialogRight
#define g_arenaNameDialogRight (*(int *)g_arenaNameDialogRight_v)
#undef g_arenaNameDialogTop
#define g_arenaNameDialogTop (*(int *)g_arenaNameDialogTop_v)
#undef g_arenaNameSum
#define g_arenaNameSum (*(int *)g_arenaNameSum_v)
#undef g_arenaPacket
#define g_arenaPacket (*(u8 * *)g_arenaPacket_v)
#undef g_arenaPanelBrightness
#define g_arenaPanelBrightness (*(u32 *)g_arenaPanelBrightness_v)
#undef g_arenaPlayers
#define g_arenaPlayers (*(u8 *)((u8 *)g_playerName_v + 0x21))
#undef g_arenaSearchClock
#define g_arenaSearchClock (*(float *)g_arenaSearchClock_v)
#undef g_arenaSearchStarted
#define g_arenaSearchStarted (*(int *)g_arenaSearchStarted_v)
#undef g_arenaSearchTicks
#define g_arenaSearchTicks (*(int *)g_arenaSearchTicks_v)
#undef g_arenaSessionOpen
#define g_arenaSessionOpen (*(int *)g_arenaSessionOpen_v)
#undef g_arenaSex
#define g_arenaSex (*(int *)g_arenaSex_v)
#undef g_arenaTimeLimit
#define g_arenaTimeLimit (*(u8 *)((u8 *)g_playerName_v + 0x25))
#undef g_arenaTimeLimitTyped
#define g_arenaTimeLimitTyped (*(u8 *)((u8 *)g_newArenaName_v + 0x25))
#undef g_arenaTunnelDepth
#define g_arenaTunnelDepth (*(u32 *)g_arenaTunnelDepth_v)
#undef g_argCount
#define g_argCount (*(int *)g_argCount_v)
#undef g_armCount
#define g_armCount (*(int *)g_armCount_v)
#undef g_armCursor
#define g_armCursor (*(int *)g_armCursor_v)
#undef g_armList
#define g_armList ((int *)g_armList_v)
#undef g_armPanelName
#define g_armPanelName ((char *)g_armPanelName_v)
#undef g_armcAngle
#define g_armcAngle (*(float *)g_armcAngle_v)
#undef g_armcBuildTexture
#define g_armcBuildTexture (*(int *)((u8 *)g_slotTextures_v + 0x18))
#undef g_armcCamDistance
#define g_armcCamDistance (*(float *)((u8 *)g_menuEye_v + 0x8))
#undef g_armcCamHeight
#define g_armcCamHeight (*(float *)((u8 *)g_menuEye_v + 0x4))
#undef g_armcCameraBox
#define g_armcCameraBox ((u32 *)g_armcCameraBox_v)
#undef g_armcChanged
#define g_armcChanged (*(int *)g_armcChanged_v)
#undef g_armcColourRects
#define g_armcColourRects ((int *)g_armcColourRects_v)
#undef g_armcColourSlot
#define g_armcColourSlot (*(int *)g_armcColourSlot_v)
#undef g_armcColours
#define g_armcColours ((float *)g_data.g_armcColours_)
#undef g_armcCursor
#define g_armcCursor (*(int *)g_armcCursor_v)
#undef g_armcEnterStep
#define g_armcEnterStep (*(int *)g_armcEnterStep_v)
#undef g_armcEnterStepF
#define g_armcEnterStepF (*(float *)g_armcEnterStepF_v)
#undef g_armcEntered
#define g_armcEntered (*(int *)g_armcEntered_v)
#undef g_armcFrom
#define g_armcFrom (*(int *)g_armcFrom_v)
#undef g_armcHideInterface
#define g_armcHideInterface (*(int *)g_armcHideInterface_v)
#undef g_armcLastPart
#define g_armcLastPart (*(int *)g_armcLastPart_v)
#undef g_armcLeaving
#define g_armcLeaving (*(int *)g_armcLeaving_v)
#undef g_armcLevel
#define g_armcLevel (*(int *)g_armcLevel_v)
#undef g_armcLookCos
#define g_armcLookCos (*(float *)g_armcLookCos_v)
#undef g_armcLookSin
#define g_armcLookSin (*(float *)g_armcLookSin_v)
#undef g_armcLookTilt
#define g_armcLookTilt (*(float *)g_armcLookTilt_v)
#undef g_armcLookYaw
#define g_armcLookYaw (*(float *)g_armcLookYaw_v)
#undef g_armcMainRects
#define g_armcMainRects ((int *)g_armcMainRects_v)
#undef g_armcMode
#define g_armcMode (*(int *)g_armcMode_v)
#undef g_armcMoveEyeX
#define g_armcMoveEyeX (*(float *)g_armcMoveEyeX_v)
#undef g_armcMoveEyeY
#define g_armcMoveEyeY (*(int *)g_armcMoveEyeY_v)
#undef g_armcMoveEyeZ
#define g_armcMoveEyeZ (*(float *)g_armcMoveEyeZ_v)
#undef g_armcMoveStarted
#define g_armcMoveStarted (*(int *)g_armcMoveStarted_v)
#undef g_armcMoveTargetX
#define g_armcMoveTargetX (*(int *)g_armcMoveTargetX_v)
#undef g_armcMoveTargetY
#define g_armcMoveTargetY (*(int *)g_armcMoveTargetY_v)
#undef g_armcMoveTargetZ
#define g_armcMoveTargetZ (*(int *)g_armcMoveTargetZ_v)
#undef g_armcPanelDepth
#define g_armcPanelDepth (*(u32 *)((u8 *)g_armcCameraBox_v + 0x88))
#undef g_armcPartSlot
#define g_armcPartSlot (*(int *)g_armcPartSlot_v)
#undef g_armcParts
#define g_armcParts ((int *)g_armcParts_v)
#undef g_armcPartsRects
#define g_armcPartsRects ((int *)g_armcPartsRects_v)
#undef g_armcPreview
#define g_armcPreview (*(int *)g_armcPreview_v)
#undef g_armcSessionDue
#define g_armcSessionDue (*(int *)g_armcSessionDue_v)
#undef g_armcSessionMade
#define g_armcSessionMade (*(int *)g_armcSessionMade_v)
#undef g_armcSliderLeft
#define g_armcSliderLeft (*(int *)g_armcSliderLeft_v)
#undef g_armcSlot
#define g_armcSlot (*(int *)g_armcSlot_v)
#undef g_armcSpin
#define g_armcSpin (*(int *)g_armcSpin_v)
#undef g_armcState
#define g_armcState (*(int *)g_armcState_v)
#undef g_armcStatsPanelBottom
#define g_armcStatsPanelBottom (*(int *)g_armcStatsPanelBottom_v)
#undef g_armcStatsPanelLeft
#define g_armcStatsPanelLeft (*(int *)g_armcStatsPanelLeft_v)
#undef g_armcStatsPanelTop
#define g_armcStatsPanelTop (*(int *)g_armcStatsPanelTop_v)
#undef g_armcTabColour
#define g_armcTabColour ((u32 *)g_armcTabColour_v)
#undef g_armcTabColourDim
#define g_armcTabColourDim ((u32 *)g_armcTabColourDim_v)
#undef g_armcUnusedFlag
#define g_armcUnusedFlag (*(int *)g_armcUnusedFlag_v)
#undef g_armcValue
#define g_armcValue (*(int *)((u8 *)g_campaign_v + 0x100))
#undef g_armcViewPoint0Y
#define g_armcViewPoint0Y (*(u32 *)((u8 *)g_armcViewPoints_v + 0x4))
#undef g_armcViewPoint3Y
#define g_armcViewPoint3Y (*(u32 *)((u8 *)g_armcViewPoints_v + 0x34))
#undef g_armcViewPoint5Y
#define g_armcViewPoint5Y (*(u32 *)((u8 *)g_armcViewPoints_v + 0x54))
#undef g_armcViewPoints
#define g_armcViewPoints ((u32 *)g_armcViewPoints_v)
#undef g_armcZoom
#define g_armcZoom (*(float *)g_armcZoom_v)
#undef g_armsFcsLevel
#define g_armsFcsLevel (*(int *)((u8 *)g_armsStats_v + 0x0))
#undef g_armsStats
#define g_armsStats ((int *)g_armsStats_v)
#undef g_armsWeight
#define g_armsWeight (*(float *)g_armsWeight_v)
#undef g_bestLevelNet
#define g_bestLevelNet (*(int *)g_bestLevelNet_v)
#undef g_bestProgressSolo
#define g_bestProgressSolo (*(int *)g_bestProgressSolo_v)
#undef g_bindPage
#define g_bindPage (*(int *)g_bindPage_v)
#undef g_bindRow
#define g_bindRow (*(int *)g_bindRow_v)
#undef g_bindRows
#define g_bindRows ((int *)g_bindRows_v)
#undef g_bindWaiting
#define g_bindWaiting (*(int *)g_bindWaiting_v)
#undef g_bitStream
#define g_bitStream (*(const u8 * *)g_bitStream_v)
#undef g_boosterActiveTime
#define g_boosterActiveTime (*(float *)((u8 *)g_boosterStats_v + 0x4))
#undef g_boosterCursor
#define g_boosterCursor (*(int *)g_boosterCursor_v)
#undef g_boosterList
#define g_boosterList ((int *)g_boosterList_v)
#undef g_boosterNormalSpeed
#define g_boosterNormalSpeed (*(float *)((u8 *)g_boosterStats_v + 0x10))
#undef g_boosterPanelName
#define g_boosterPanelName ((char *)g_boosterPanelName_v)
#undef g_boosterRechargeDelay
#define g_boosterRechargeDelay (*(float *)((u8 *)g_boosterStats_v + 0xc))
#undef g_boosterRechargeTime
#define g_boosterRechargeTime (*(float *)((u8 *)g_boosterStats_v + 0x8))
#undef g_boosterStats
#define g_boosterStats ((float *)g_boosterStats_v)
#undef g_boosterThrustType
#define g_boosterThrustType (*(int *)((u8 *)g_boosterStats_v + 0x0))
#undef g_boosterWeight
#define g_boosterWeight (*(float *)((u8 *)g_boosterStats_v + 0x20))
#undef g_briefingBottom
#define g_briefingBottom (*(int *)g_briefingBottom_v)
#undef g_briefingClock
#define g_briefingClock (*(float *)g_briefingClock_v)
#undef g_briefingDone
#define g_briefingDone (*(int *)g_briefingDone_v)
#undef g_briefingEnd
#define g_briefingEnd (*(int *)g_briefingEnd_v)
#undef g_briefingRects
#define g_briefingRects ((int *)g_briefingRects_v)
#undef g_briefingRight
#define g_briefingRight (*(int *)g_briefingRight_v)
#undef g_briefingShown
#define g_briefingShown (*(int *)g_briefingShown_v)
#undef g_briefingSkipped
#define g_briefingSkipped (*(int *)g_briefingSkipped_v)
#undef g_briefingSource
#define g_briefingSource (*(u8 * *)g_briefingSource_v)
#undef g_briefingStart
#define g_briefingStart (*(int *)g_briefingStart_v)
#undef g_briefingText
#define g_briefingText ((char *)g_briefingText_v)
#undef g_briefingX
#define g_briefingX (*(int *)g_briefingX_v)
#undef g_briefingY
#define g_briefingY (*(int *)g_briefingY_v)
#undef g_buttonTexture
#define g_buttonTexture (*(int *)g_buttonTexture_v)
#undef g_cageTexture
#define g_cageTexture (*(int *)g_cageTexture_v)
#undef g_camAim0X
#define g_camAim0X (*(int *)((u8 *)g_camAims_v + 0x0))
#undef g_camAim0Y
#define g_camAim0Y (*(int *)((u8 *)g_camAims_v + 0x4))
#undef g_camAim0Z
#define g_camAim0Z (*(int *)((u8 *)g_camAims_v + 0x8))
#undef g_camAim1X
#define g_camAim1X (*(u32 *)((u8 *)g_camAims_v + 0x10))
#undef g_camAim1Y
#define g_camAim1Y (*(u32 *)((u8 *)g_camAims_v + 0x14))
#undef g_camAim1Z
#define g_camAim1Z (*(int *)((u8 *)g_camAims_v + 0x18))
#undef g_camAim2X
#define g_camAim2X (*(u32 *)((u8 *)g_camAims_v + 0x20))
#undef g_camAim2Y
#define g_camAim2Y (*(u32 *)((u8 *)g_camAims_v + 0x24))
#undef g_camAim2Z
#define g_camAim2Z (*(int *)((u8 *)g_camAims_v + 0x28))
#undef g_camAims
#define g_camAims ((float *)g_camAims_v)
#undef g_camPoint0X
#define g_camPoint0X (*(int *)((u8 *)g_camPoints_v + 0x0))
#undef g_camPoint0Y
#define g_camPoint0Y (*(int *)((u8 *)g_camPoints_v + 0x4))
#undef g_camPoint0Z
#define g_camPoint0Z (*(int *)((u8 *)g_camPoints_v + 0x8))
#undef g_camPoint1X
#define g_camPoint1X (*(u32 *)((u8 *)g_camPoints_v + 0x10))
#undef g_camPoint1Z
#define g_camPoint1Z (*(int *)((u8 *)g_camPoints_v + 0x18))
#undef g_camPoint2X
#define g_camPoint2X (*(u32 *)((u8 *)g_camPoints_v + 0x20))
#undef g_camPoint2Y
#define g_camPoint2Y (*(int *)((u8 *)g_camPoints_v + 0x24))
#undef g_camPoint2Z
#define g_camPoint2Z (*(int *)((u8 *)g_camPoints_v + 0x28))
#undef g_camPoints
#define g_camPoints ((float *)g_camPoints_v)
#undef g_campaign
#define g_campaign ((u8 *)g_campaign_v)
#undef g_catalogueFile
#define g_catalogueFile (*(const char * *)g_catalogueFile_v)
#undef g_cfgPlayerName
#define g_cfgPlayerName ((char *)g_data.g_cfgPlayerName_)
#undef g_cfgSimpleMenu
#define g_cfgSimpleMenu (*(int *)((u8 *)g_graphicSettings_v + 0x18))
#undef g_characterTexture
#define g_characterTexture (*(int *)g_characterTexture_v)
#undef g_chatCaretX
#define g_chatCaretX (*(int *)g_chatCaretX_v)
#undef g_chatCaretY
#define g_chatCaretY (*(int *)g_chatCaretY_v)
#undef g_chatEditLength
#define g_chatEditLength (*(int *)g_chatEditLength_v)
#undef g_chatFieldFlag
#define g_chatFieldFlag (*(int *)g_chatFieldFlag_v)
#undef g_chatLength
#define g_chatLength (*(int *)g_chatLength_v)
#undef g_chatLine
#define g_chatLine ((char *)g_chatLine_v)
#undef g_chatLineDone
#define g_chatLineDone (*(int *)g_chatLineDone_v)
#undef g_chatLog
#define g_chatLog (*(int *)g_chatLog_v)
#undef g_chatLogged
#define g_chatLogged (*(int *)g_chatLogged_v)
#undef g_chatTyping
#define g_chatTyping (*(int *)g_chatTyping_v)
#undef g_chestCount
#define g_chestCount (*(int *)g_chestCount_v)
#undef g_chestCursor
#define g_chestCursor (*(int *)g_chestCursor_v)
#undef g_chestList
#define g_chestList ((int *)g_chestList_v)
#undef g_chestMaxArmor
#define g_chestMaxArmor (*(int *)g_chestMaxArmor_v)
#undef g_chestMaxShield
#define g_chestMaxShield (*(int *)g_chestMaxShield_v)
#undef g_chestPanelName
#define g_chestPanelName ((char *)g_chestPanelName_v)
#undef g_chestWeightLimit
#define g_chestWeightLimit (*(float *)g_chestWeightLimit_v)
#undef g_chosenGameMode
#define g_chosenGameMode (*(int *)g_chosenGameMode_v)
#undef g_chosenPilot
#define g_chosenPilot (*(int *)g_chosenPilot_v)
#undef g_clamp
#define g_clamp (*(const u8 * *)g_clamp_v)
#undef g_clockCheckClosed
#define g_clockCheckClosed (*(int *)g_clockCheckClosed_v)
#undef g_clockCheckSeconds
#define g_clockCheckSeconds (*(int *)g_clockCheckSeconds_v)
#undef g_clockCheckTick
#define g_clockCheckTick (*(u32 *)g_clockCheckTick_v)
#undef g_clockCheckTickSeconds
#define g_clockCheckTickSeconds (*(u32 *)g_clockCheckTickSeconds_v)
#undef g_clockLastTime
#define g_clockLastTime ((u16 *)g_data.g_clockLastTime_)
#undef g_clockNow
#define g_clockNow (*(double *)((u8 *)g_timerClocks_v + 0x0))
#undef g_clockNowTime
#define g_clockNowTime ((u16 *)g_data.g_clockNowTime_)
#undef g_cmdSecret
#define g_cmdSecret (g_data.g_cmdSecret_)
#undef g_cmdTimeLimit
#define g_cmdTimeLimit (g_data.g_cmdTimeLimit_)
#undef g_colourChanged
#define g_colourChanged (*(int *)g_colourChanged_v)
#undef g_colourMaskRed
#define g_colourMaskRed (*(u32 *)g_colourMaskRed_v)
#undef g_coloursChanged
#define g_coloursChanged (*(int *)g_coloursChanged_v)
#undef g_componentDatPath
#define g_componentDatPath (*(u32 *)g_componentDatPath_v)
#undef g_connectStep
#define g_connectStep (*(int *)g_connectStep_v)
#undef g_connectionAwaited
#define g_connectionAwaited (*(int *)g_connectionAwaited_v)
#undef g_connectionCopy
#define g_connectionCopy (*(void * *)g_connectionCopy_v)
#undef g_connectionKind
#define g_connectionKind (*(int *)g_connectionKind_v)
#undef g_context
#define g_context (*(void * *)g_context_v)
#undef g_controls
#define g_controls ((int *)g_controls_v)
#undef g_controlsEdit
#define g_controlsEdit ((int *)g_controlsEdit_v)
#undef g_convertHangul
#define g_convertHangul (*(int *)g_convertHangul_v)
#undef g_cosTable
#define g_cosTable ((float *)g_cosTable_v)
#undef g_createArena2Rects
#define g_createArena2Rects ((int *)g_createArena2Rects_v)
#undef g_createArenaRects
#define g_createArenaRects ((int *)g_createArenaRects_v)
#undef g_createDialogRects
#define g_createDialogRects ((int *)g_createDialogRects_v)
#undef g_createQuitDialog
#define g_createQuitDialog (*(int *)g_createQuitDialog_v)
#undef g_crosshair
#define g_crosshair (*(int *)((u8 *)g_controlsEdit_v + 0x10c))
#undef g_crosshairSetting
#define g_crosshairSetting (*(int *)((u8 *)g_controls_v + 0x10c))
#undef g_crosshairTexture
#define g_crosshairTexture (*(int *)g_crosshairTexture_v)
#undef g_ctrlMenuTextures
#define g_ctrlMenuTextures ((int *)g_ctrlMenuTextures_v)
#undef g_currentProfile
#define g_currentProfile (*(int *)g_currentProfile_v)
#undef g_currentStageName
#define g_currentStageName (*(int *)g_currentStageName_v)
#undef g_cursor
#define g_cursor (*(int *)g_cursor_v)
#undef g_cursorBlink
#define g_cursorBlink (*(float *)g_cursorBlink_v)
#undef g_cursorBlinkTimer
#define g_cursorBlinkTimer (*(float *)g_cursorBlinkTimer_v)
#undef g_cursorFrame
#define g_cursorFrame (*(int *)g_cursorFrame_v)
#undef g_cursorFrameTime
#define g_cursorFrameTime (*(float *)g_cursorFrameTime_v)
#undef g_cursorPoint
#define g_cursorPoint ((int *)g_cursorPoint_v)
#undef g_cursorPos
#define g_cursorPos (*(int *)((u8 *)g_cursorPoint_v + 0x0))
#undef g_cursorPosY
#define g_cursorPosY (*(int *)((u8 *)g_cursorPoint_v + 0x4))
#undef g_cursorTexture
#define g_cursorTexture (*(int *)g_cursorTexture_v)
#undef g_dataDir
#define g_dataDir ((char *)g_data.g_dataDir_)
#undef g_debugValue
#define g_debugValue (*(int *)g_debugValue_v)
#undef g_defaultColour
#define g_defaultColour (*(int *)g_defaultColour_v)
#undef g_defaultColours
#define g_defaultColours ((u32 *)g_defaultColours_v)
#undef g_deleteDialogRects
#define g_deleteDialogRects ((int *)g_deleteDialogRects_v)
#undef g_desktopBits
#define g_desktopBits (*(int *)g_desktopBits_v)
#undef g_desktopDC
#define g_desktopDC (*(void * *)g_desktopDC_v)
#undef g_desktopDepth
#define g_desktopDepth (*(int *)g_desktopDepth_v)
#undef g_desktopH
#define g_desktopH (*(int *)g_desktopH_v)
#undef g_desktopHeight
#define g_desktopHeight (*(int *)g_desktopHeight_v)
#undef g_desktopW
#define g_desktopW (*(int *)g_desktopW_v)
#undef g_desktopWidth
#define g_desktopWidth (*(int *)g_desktopWidth_v)
#undef g_dialogChoice
#define g_dialogChoice (*(int *)g_dialogChoice_v)
#undef g_dialogFrameTexture
#define g_dialogFrameTexture (*(int *)((u8 *)g_menuFrameTextures_v + 0x4))
#undef g_dialogOpen
#define g_dialogOpen (*(int *)g_dialogOpen_v)
#undef g_dialogPending
#define g_dialogPending (*(int *)g_dialogPending_v)
#undef g_dik0
#define g_dik0 (*(int *)g_dik0_v)
#undef g_dik1
#define g_dik1 (*(int *)g_dik1_v)
#undef g_dik2
#define g_dik2 (*(int *)g_dik2_v)
#undef g_dik3
#define g_dik3 (*(int *)g_dik3_v)
#undef g_dik4
#define g_dik4 (*(int *)g_dik4_v)
#undef g_dik5
#define g_dik5 (*(int *)g_dik5_v)
#undef g_dik6
#define g_dik6 (*(int *)g_dik6_v)
#undef g_dik7
#define g_dik7 (*(int *)g_dik7_v)
#undef g_dik8
#define g_dik8 (*(int *)g_dik8_v)
#undef g_dik9
#define g_dik9 (*(int *)g_dik9_v)
#undef g_dikA
#define g_dikA (*(int *)g_dikA_v)
#undef g_dikApostrophe
#define g_dikApostrophe (*(int *)g_dikApostrophe_v)
#undef g_dikApps
#define g_dikApps (*(int *)g_dikApps_v)
#undef g_dikB
#define g_dikB (*(int *)g_dikB_v)
#undef g_dikBack
#define g_dikBack (*(int *)g_dikBack_v)
#undef g_dikBackslash
#define g_dikBackslash (*(int *)g_dikBackslash_v)
#undef g_dikC
#define g_dikC (*(int *)g_dikC_v)
#undef g_dikCapsLock
#define g_dikCapsLock (*(int *)g_dikCapsLock_v)
#undef g_dikComma
#define g_dikComma (*(int *)g_dikComma_v)
#undef g_dikD
#define g_dikD (*(int *)g_dikD_v)
#undef g_dikDelete
#define g_dikDelete (*(int *)g_dikDelete_v)
#undef g_dikDelete_2
#define g_dikDelete_2 (*(int *)g_dikDelete_2_v)
#undef g_dikDown
#define g_dikDown (*(int *)g_dikDown_v)
#undef g_dikE
#define g_dikE (*(int *)g_dikE_v)
#undef g_dikEnd
#define g_dikEnd (*(int *)g_dikEnd_v)
#undef g_dikEnd_2
#define g_dikEnd_2 (*(int *)g_dikEnd_2_v)
#undef g_dikEnter
#define g_dikEnter (*(int *)g_dikEnter_v)
#undef g_dikEnter_2
#define g_dikEnter_2 (*(int *)g_dikEnter_2_v)
#undef g_dikEquals
#define g_dikEquals (*(int *)g_dikEquals_v)
#undef g_dikEscape
#define g_dikEscape (*(int *)g_dikEscape_v)
#undef g_dikEscape_2
#define g_dikEscape_2 (*(int *)g_dikEscape_2_v)
#undef g_dikF
#define g_dikF (*(int *)g_dikF_v)
#undef g_dikF10
#define g_dikF10 (*(int *)g_dikF10_v)
#undef g_dikF11
#define g_dikF11 (*(int *)g_dikF11_v)
#undef g_dikF12
#define g_dikF12 (*(int *)g_dikF12_v)
#undef g_dikF2
#define g_dikF2 (*(int *)g_dikF2_v)
#undef g_dikF3
#define g_dikF3 (*(int *)g_dikF3_v)
#undef g_dikF4
#define g_dikF4 (*(int *)g_dikF4_v)
#undef g_dikF5
#define g_dikF5 (*(int *)g_dikF5_v)
#undef g_dikF6
#define g_dikF6 (*(int *)g_dikF6_v)
#undef g_dikF7
#define g_dikF7 (*(int *)g_dikF7_v)
#undef g_dikF8
#define g_dikF8 (*(int *)g_dikF8_v)
#undef g_dikF9
#define g_dikF9 (*(int *)g_dikF9_v)
#undef g_dikG
#define g_dikG (*(int *)g_dikG_v)
#undef g_dikGrave
#define g_dikGrave (*(int *)g_dikGrave_v)
#undef g_dikH
#define g_dikH (*(int *)g_dikH_v)
#undef g_dikHome
#define g_dikHome (*(int *)g_dikHome_v)
#undef g_dikHome_2
#define g_dikHome_2 (*(int *)g_dikHome_2_v)
#undef g_dikI
#define g_dikI (*(int *)g_dikI_v)
#undef g_dikInsert
#define g_dikInsert (*(int *)g_dikInsert_v)
#undef g_dikInsert_2
#define g_dikInsert_2 (*(int *)g_dikInsert_2_v)
#undef g_dikJ
#define g_dikJ (*(int *)g_dikJ_v)
#undef g_dikK
#define g_dikK (*(int *)g_dikK_v)
#undef g_dikL
#define g_dikL (*(int *)g_dikL_v)
#undef g_dikLAlt
#define g_dikLAlt (*(int *)g_dikLAlt_v)
#undef g_dikLBracket
#define g_dikLBracket (*(int *)g_dikLBracket_v)
#undef g_dikLCtrl
#define g_dikLCtrl (*(int *)g_dikLCtrl_v)
#undef g_dikLShift
#define g_dikLShift (*(int *)g_dikLShift_v)
#undef g_dikLWin
#define g_dikLWin (*(int *)g_dikLWin_v)
#undef g_dikLeft
#define g_dikLeft (*(int *)g_dikLeft_v)
#undef g_dikM
#define g_dikM (*(int *)g_dikM_v)
#undef g_dikMinus
#define g_dikMinus (*(int *)g_dikMinus_v)
#undef g_dikMouse1
#define g_dikMouse1 (*(int *)g_dikMouse1_v)
#undef g_dikMouse2
#define g_dikMouse2 (*(int *)g_dikMouse2_v)
#undef g_dikMouse3
#define g_dikMouse3 (*(int *)g_dikMouse3_v)
#undef g_dikN
#define g_dikN (*(int *)g_dikN_v)
#undef g_dikNone
#define g_dikNone (*(int *)g_dikNone_v)
#undef g_dikNumLock
#define g_dikNumLock (*(int *)g_dikNumLock_v)
#undef g_dikNumpad0
#define g_dikNumpad0 (*(int *)g_dikNumpad0_v)
#undef g_dikNumpad1
#define g_dikNumpad1 (*(int *)g_dikNumpad1_v)
#undef g_dikNumpad2
#define g_dikNumpad2 (*(int *)g_dikNumpad2_v)
#undef g_dikNumpad3
#define g_dikNumpad3 (*(int *)g_dikNumpad3_v)
#undef g_dikNumpad4
#define g_dikNumpad4 (*(int *)g_dikNumpad4_v)
#undef g_dikNumpad5
#define g_dikNumpad5 (*(int *)g_dikNumpad5_v)
#undef g_dikNumpad6
#define g_dikNumpad6 (*(int *)g_dikNumpad6_v)
#undef g_dikNumpad7
#define g_dikNumpad7 (*(int *)g_dikNumpad7_v)
#undef g_dikNumpad8
#define g_dikNumpad8 (*(int *)g_dikNumpad8_v)
#undef g_dikNumpad9
#define g_dikNumpad9 (*(int *)g_dikNumpad9_v)
#undef g_dikNumpadDot
#define g_dikNumpadDot (*(int *)g_dikNumpadDot_v)
#undef g_dikNumpadEnter
#define g_dikNumpadEnter (*(int *)g_dikNumpadEnter_v)
#undef g_dikNumpadMinus
#define g_dikNumpadMinus (*(int *)g_dikNumpadMinus_v)
#undef g_dikNumpadPlus
#define g_dikNumpadPlus (*(int *)g_dikNumpadPlus_v)
#undef g_dikNumpadSlash
#define g_dikNumpadSlash (*(int *)g_dikNumpadSlash_v)
#undef g_dikNumpadStar
#define g_dikNumpadStar (*(int *)g_dikNumpadStar_v)
#undef g_dikO
#define g_dikO (*(int *)g_dikO_v)
#undef g_dikP
#define g_dikP (*(int *)g_dikP_v)
#undef g_dikPageDown
#define g_dikPageDown (*(int *)g_dikPageDown_v)
#undef g_dikPageDown_2
#define g_dikPageDown_2 (*(int *)g_dikPageDown_2_v)
#undef g_dikPageUp
#define g_dikPageUp (*(int *)g_dikPageUp_v)
#undef g_dikPageUp_2
#define g_dikPageUp_2 (*(int *)g_dikPageUp_2_v)
#undef g_dikPeriod
#define g_dikPeriod (*(int *)g_dikPeriod_v)
#undef g_dikPrintScreen
#define g_dikPrintScreen (*(int *)g_dikPrintScreen_v)
#undef g_dikQ
#define g_dikQ (*(int *)g_dikQ_v)
#undef g_dikR
#define g_dikR (*(int *)g_dikR_v)
#undef g_dikRAlt
#define g_dikRAlt (*(int *)g_dikRAlt_v)
#undef g_dikRBracket
#define g_dikRBracket (*(int *)g_dikRBracket_v)
#undef g_dikRCtrl
#define g_dikRCtrl (*(int *)g_dikRCtrl_v)
#undef g_dikRShift
#define g_dikRShift (*(int *)g_dikRShift_v)
#undef g_dikRWin
#define g_dikRWin (*(int *)g_dikRWin_v)
#undef g_dikRight
#define g_dikRight (*(int *)g_dikRight_v)
#undef g_dikS
#define g_dikS (*(int *)g_dikS_v)
#undef g_dikScrollLock
#define g_dikScrollLock (*(int *)g_dikScrollLock_v)
#undef g_dikSemicolon
#define g_dikSemicolon (*(int *)g_dikSemicolon_v)
#undef g_dikSlash
#define g_dikSlash (g_data.g_dikSlash_)
#undef g_dikSpace
#define g_dikSpace (*(int *)g_dikSpace_v)
#undef g_dikT
#define g_dikT (*(int *)g_dikT_v)
#undef g_dikTab
#define g_dikTab (*(int *)g_dikTab_v)
#undef g_dikU
#define g_dikU (*(int *)g_dikU_v)
#undef g_dikUp
#define g_dikUp (*(int *)g_dikUp_v)
#undef g_dikV
#define g_dikV (*(int *)g_dikV_v)
#undef g_dikW
#define g_dikW (*(int *)g_dikW_v)
#undef g_dikWheelDown
#define g_dikWheelDown (*(int *)g_dikWheelDown_v)
#undef g_dikWheelUp
#define g_dikWheelUp (*(int *)g_dikWheelUp_v)
#undef g_dikX
#define g_dikX (*(int *)g_dikX_v)
#undef g_dikY
#define g_dikY (*(int *)g_dikY_v)
#undef g_dikZ
#define g_dikZ (*(int *)g_dikZ_v)
#undef g_dikZ_2
#define g_dikZ_2 (*(int *)g_dikZ_2_v)
#undef g_directInput
#define g_directInput (g_data.g_directInput_)
#undef g_directInputMade
#define g_directInputMade (*(int *)g_directInputMade_v)
#undef g_directSound
#define g_directSound (*(void * *)g_directSound_v)
#undef g_displayModeChanged
#define g_displayModeChanged (*(u8 *)g_displayModeChanged_v)
#undef g_displayModeLeft
#define g_displayModeLeft (*(u8 *)g_displayModeLeft_v)
#undef g_dottedAddress
#define g_dottedAddress ((char *)g_dottedAddress_v)
#undef g_dpConnections
#define g_dpConnections ((int *)g_dpConnections_v)
#undef g_dpMaxBufferSize
#define g_dpMaxBufferSize (*(u32 *)g_dpMaxBufferSize_v)
#undef g_dpMaxQueueSize
#define g_dpMaxQueueSize (*(u32 *)g_dpMaxQueueSize_v)
#undef g_dpTimeout
#define g_dpTimeout (*(u32 *)g_dpTimeout_v)
#undef g_dplay
#define g_dplay (*(void * *)g_dplay_v)
#undef g_dplayLobby
#define g_dplayLobby (*(void * *)g_dplayLobby_v)
#undef g_dplaySessionCount
#define g_dplaySessionCount (*(int *)g_dplaySessionCount_v)
#undef g_dplaySessionList
#define g_dplaySessionList (*(int *)g_dplaySessionList_v)
#undef g_dplaySlots
#define g_dplaySlots ((int *)g_dplaySlots_v)
#undef g_editOldProc
#define g_editOldProc (*(u32 *)g_editOldProc_v)
#undef g_editingAccountPassword
#define g_editingAccountPassword (*(int *)g_editingAccountPassword_v)
#undef g_editingArenaMessage
#define g_editingArenaMessage (*(int *)g_editingArenaMessage_v)
#undef g_editingEmail
#define g_editingEmail (*(int *)g_editingEmail_v)
#undef g_editingNewArenaFragLimit
#define g_editingNewArenaFragLimit (*(int *)g_editingNewArenaFragLimit_v)
#undef g_editingNewArenaName
#define g_editingNewArenaName (*(int *)g_editingNewArenaName_v)
#undef g_editingNewArenaTimeLimit
#define g_editingNewArenaTimeLimit (*(int *)g_editingNewArenaTimeLimit_v)
#undef g_editingOldPassword
#define g_editingOldPassword (*(int *)g_editingOldPassword_v)
#undef g_editingPasswordRepeat
#define g_editingPasswordRepeat (*(int *)g_editingPasswordRepeat_v)
#undef g_editingRoomName
#define g_editingRoomName (*(int *)g_editingRoomName_v)
#undef g_editingRoomPassword
#define g_editingRoomPassword (*(int *)g_editingRoomPassword_v)
#undef g_effectsVolume
#define g_effectsVolume (*(int *)((u8 *)g_soundEdited_v + 0x4))
#undef g_emblemAlpha
#define g_emblemAlpha (*(float *)g_emblemAlpha_v)
#undef g_emblemCursor
#define g_emblemCursor (*(int *)g_emblemCursor_v)
#undef g_emblemMoved
#define g_emblemMoved (*(int *)g_emblemMoved_v)
#undef g_emblemPulse
#define g_emblemPulse (*(float *)g_emblemPulse_v)
#undef g_emptyItemSlot0
#define g_emptyItemSlot0 (*(int *)g_emptyItemSlot0_v)
#undef g_enteringMenus
#define g_enteringMenus (*(int *)g_enteringMenus_v)
#undef g_errorCleanupHook
#define g_errorCleanupHook (*(int *)g_errorCleanupHook_v)
#undef g_errorHook
#define g_errorHook (*(ErrorHook *)g_errorHook_v)
#undef g_errorLogging
#define g_errorLogging (*(int *)g_errorLogging_v)
#undef g_excludedKey
#define g_excludedKey (*(int *)g_excludedKey_v)
#undef g_exitCode
#define g_exitCode (*(int *)g_exitCode_v)
#undef g_extraCount
#define g_extraCount (*(int *)g_extraCount_v)
#undef g_extraListTable
#define g_extraListTable ((int *)g_extraListTable_v)
#undef g_fieldTabKey
#define g_fieldTabKey (*(int *)g_fieldTabKey_v)
#undef g_fileList
#define g_fileList ((u8 *)g_fileList_v)
#undef g_flareSizeA
#define g_flareSizeA (*(float *)g_flareSizeA_v)
#undef g_flareSizeB
#define g_flareSizeB (*(float *)g_flareSizeB_v)
#undef g_flareStepA
#define g_flareStepA (*(float *)g_flareStepA_v)
#undef g_flareStepB
#define g_flareStepB (*(float *)g_flareStepB_v)
#undef g_font16Bottom
#define g_font16Bottom ((float *)g_font16Bottom_v)
#undef g_font16Left
#define g_font16Left ((float *)g_font16Left_v)
#undef g_font16Right
#define g_font16Right ((float *)g_font16Right_v)
#undef g_font16Top
#define g_font16Top ((float *)g_font16Top_v)
#undef g_font5Bottom
#define g_font5Bottom ((float *)g_font5Bottom_v)
#undef g_font5Left
#define g_font5Left ((float *)g_font5Left_v)
#undef g_font5Right
#define g_font5Right ((float *)g_font5Right_v)
#undef g_font5Top
#define g_font5Top ((float *)g_font5Top_v)
#undef g_font8Bottom
#define g_font8Bottom ((float *)g_font8Bottom_v)
#undef g_font8Left
#define g_font8Left ((float *)g_font8Left_v)
#undef g_font8Right
#define g_font8Right ((float *)g_font8Right_v)
#undef g_font8Top
#define g_font8Top ((float *)g_font8Top_v)
#undef g_fontAscii
#define g_fontAscii (*(int *)g_fontAscii_v)
#undef g_fontAsciiLarge
#define g_fontAsciiLarge (*(int *)g_fontAsciiLarge_v)
#undef g_fontHanCho
#define g_fontHanCho (*(int *)g_fontHanCho_v)
#undef g_fontHanJungJong
#define g_fontHanJungJong (*(int *)g_fontHanJungJong_v)
#undef g_fovKeys
#define g_fovKeys (*(int *)g_fovKeys_v)
#undef g_fps
#define g_fps (*(float *)g_fps_v)
#undef g_fpsFrameClock
#define g_fpsFrameClock (*(double *)g_fpsFrameClock_v)
#undef g_fpsSecondSoFar
#define g_fpsSecondSoFar (*(double *)g_fpsSecondSoFar_v)
#undef g_fpsSecondStart
#define g_fpsSecondStart (*(double *)g_fpsSecondStart_v)
#undef g_fragLimit
#define g_fragLimit (*(int *)g_fragLimit_v)
#undef g_frameCounter40
#define g_frameCounter40 (*(int *)g_frameCounter40_v)
#undef g_frameRate
#define g_frameRate (*(double *)g_frameRate_v)
#undef g_frameTime
#define g_frameTime (g_data.g_frameTime_)
#undef g_freeCamHeight
#define g_freeCamHeight (*(float *)g_freeCamHeight_v)
#undef g_fullScreen
#define g_fullScreen (*(int *)g_fullScreen_v)
#undef g_gameCount
#define g_gameCount (*(int *)g_gameCount_v)
#undef g_gameList
#define g_gameList ((u8 *)g_data.g_gameList_)
#undef g_gameListClickArmed
#define g_gameListClickArmed (*(int *)g_gameListClickArmed_v)
#undef g_gameListClickTimer
#define g_gameListClickTimer (*(float *)g_gameListClickTimer_v)
#undef g_gameListJoinClicked
#define g_gameListJoinClicked (*(int *)g_gameListJoinClicked_v)
#undef g_gameListLoaded
#define g_gameListLoaded (*(int *)g_gameListLoaded_v)
#undef g_gameListRects
#define g_gameListRects ((int *)g_gameListRects_v)
#undef g_gameListStopRects
#define g_gameListStopRects ((int *)g_gameListStopRects_v)
#undef g_gameListTop
#define g_gameListTop (*(int *)g_gameListTop_v)
#undef g_gameRunning
#define g_gameRunning (*(int *)g_gameRunning_v)
#undef g_gameServerAnswer
#define g_gameServerAnswer (*(int *)g_gameServerAnswer_v)
#undef g_gameServerAnswer15
#define g_gameServerAnswer15 (*(int *)g_gameServerAnswer15_v)
#undef g_gameServerPending
#define g_gameServerPending (*(int *)g_gameServerPending_v)
#undef g_gameServerReply
#define g_gameServerReply ((u8 *)g_gameServerReply_v)
#undef g_gameServerReplyKind
#define g_gameServerReplyKind (*(u32 *)((u8 *)g_gameServerReply_v + 0x68))
#undef g_gameServerSocket
#define g_gameServerSocket (*(int *)g_gameServerSocket_v)
#undef g_gameServerState
#define g_gameServerState (*(int *)g_gameServerState_v)
#undef g_gameServerStatus
#define g_gameServerStatus (*(int *)g_gameServerStatus_v)
#undef g_glCachedState
#define g_glCachedState (*(int *)g_glCachedState_v)
#undef g_glColourBits
#define g_glColourBits (*(int *)g_glColourBits_v)
#undef g_glContext
#define g_glContext (g_data.g_glContext_)
#undef g_glDepthBits
#define g_glDepthBits (g_data.g_glDepthBits_)
#undef g_glHeight
#define g_glHeight (*(int *)g_glHeight_v)
#undef g_glWidth
#define g_glWidth (*(int *)g_glWidth_v)
#undef g_glWindow
#define g_glWindow (*(void * *)g_glWindow_v)
#undef g_glWindowMade
#define g_glWindowMade (*(int *)g_glWindowMade_v)
#undef g_graphicEdited
#define g_graphicEdited ((u32 *)g_graphicEdited_v)
#undef g_graphicSettings
#define g_graphicSettings ((int *)g_graphicSettings_v)
#undef g_hChatEdit
#define g_hChatEdit (*(void * *)g_hChatEdit_v)
#undef g_hInstance
#define g_hInstance (*(void * *)g_hInstance_v)
#undef g_hangulLeadGlyph
#define g_hangulLeadGlyph (*(int *)g_hangulLeadGlyph_v)
#undef g_hangulTailGlyph
#define g_hangulTailGlyph (*(int *)g_hangulTailGlyph_v)
#undef g_hangulVowelGlyph
#define g_hangulVowelGlyph (*(int *)g_hangulVowelGlyph_v)
#undef g_hdc
#define g_hdc (*(void * *)g_hdc_v)
#undef g_headCount
#define g_headCount (*(int *)g_headCount_v)
#undef g_headCursor
#define g_headCursor (*(int *)g_headCursor_v)
#undef g_headDetectionAngle
#define g_headDetectionAngle (*(float *)g_headDetectionAngle_v)
#undef g_headDetectionRange
#define g_headDetectionRange (*(float *)g_headDetectionRange_v)
#undef g_headHackingLevel
#define g_headHackingLevel (*(int *)g_headHackingLevel_v)
#undef g_headList
#define g_headList ((int *)g_headList_v)
#undef g_headLockOnTime
#define g_headLockOnTime (*(float *)g_headLockOnTime_v)
#undef g_headPanelName
#define g_headPanelName ((char *)g_headPanelName_v)
#undef g_headTargetKeepTime
#define g_headTargetKeepTime (*(float *)g_headTargetKeepTime_v)
#undef g_headWeight
#define g_headWeight (*(float *)g_headWeight_v)
#undef g_highlightAlpha
#define g_highlightAlpha (*(float *)g_highlightAlpha_v)
#undef g_highlightShown
#define g_highlightShown (*(int *)g_highlightShown_v)
#undef g_highlightSize
#define g_highlightSize (*(float *)g_highlightSize_v)
#undef g_highlightX
#define g_highlightX (*(int *)g_highlightX_v)
#undef g_highlightY
#define g_highlightY (*(int *)g_highlightY_v)
#undef g_hostAddressBlock
#define g_hostAddressBlock (*(void * *)g_hostAddressBlock_v)
#undef g_hostResultFlag
#define g_hostResultFlag (*(int *)((u8 *)g_resultMsg_v + 0x4))
#undef g_hudFontBottom
#define g_hudFontBottom ((float *)g_hudFontBottom_v)
#undef g_hudFontLeft
#define g_hudFontLeft ((float *)g_hudFontLeft_v)
#undef g_hudFontRight
#define g_hudFontRight ((float *)g_hudFontRight_v)
#undef g_hudFontTop
#define g_hudFontTop ((float *)g_hudFontTop_v)
#undef g_hudLayerABottom
#define g_hudLayerABottom ((float *)g_hudLayerABottom_v)
#undef g_hudLayerALeft
#define g_hudLayerALeft ((float *)g_hudLayerALeft_v)
#undef g_hudLayerARight
#define g_hudLayerARight ((float *)g_hudLayerARight_v)
#undef g_hudLayerATop
#define g_hudLayerATop ((float *)g_hudLayerATop_v)
#undef g_hudLayerBBottom
#define g_hudLayerBBottom ((float *)g_hudLayerBBottom_v)
#undef g_hudLayerBLeft
#define g_hudLayerBLeft ((float *)g_hudLayerBLeft_v)
#undef g_hudLayerBRight
#define g_hudLayerBRight ((float *)g_hudLayerBRight_v)
#undef g_hudLayerBTop
#define g_hudLayerBTop ((float *)g_hudLayerBTop_v)
#undef g_inputFont
#define g_inputFont (*(void * *)g_inputFont_v)
#undef g_insertCdMessage
#define g_insertCdMessage (*(const char * *)g_insertCdMessage_v)
#undef g_instanceGuid
#define g_instanceGuid (*(const void * *)g_instanceGuid_v)
#undef g_introTextures
#define g_introTextures ((int *)g_introTextures_v)
#undef g_introZoom
#define g_introZoom (*(float *)g_introZoom_v)
#undef g_ipxProviderGuid
#define g_ipxProviderGuid ((u8 *)g_ipxProviderGuid_v)
#undef g_isHost
#define g_isHost (*(int *)g_isHost_v)
#undef g_itemBonusActiveTime
#define g_itemBonusActiveTime (*(float *)g_itemBonusActiveTime_v)
#undef g_itemBonusCapacityPerLevel
#define g_itemBonusCapacityPerLevel (*(float *)g_itemBonusCapacityPerLevel_v)
#undef g_itemBonusDetectionRange
#define g_itemBonusDetectionRange (*(float *)g_itemBonusDetectionRange_v)
#undef g_itemBonusHacking
#define g_itemBonusHacking (*(float *)g_itemBonusHacking_v)
#undef g_itemBonusLockOn
#define g_itemBonusLockOn (*(float *)g_itemBonusLockOn_v)
#undef g_itemBonusRechargeTime
#define g_itemBonusRechargeTime (*(float *)g_itemBonusRechargeTime_v)
#undef g_itemBonusShield
#define g_itemBonusShield (*(float *)g_itemBonusShield_v)
#undef g_itemBonusTargetKeep
#define g_itemBonusTargetKeep (*(float *)g_itemBonusTargetKeep_v)
#undef g_itemBonusWeightLimit
#define g_itemBonusWeightLimit (*(float *)g_itemBonusWeightLimit_v)
#undef g_itemSlot4
#define g_itemSlot4 (*(int *)((u8 *)g_mechSettings_v + 0x0))
#undef g_itemSlot5
#define g_itemSlot5 (*(int *)((u8 *)g_mechSettings_v + 0x4))
#undef g_joinPasswordTyped
#define g_joinPasswordTyped (*(int *)g_joinPasswordTyped_v)
#undef g_joinedSessionFlag
#define g_joinedSessionFlag (*(u8 *)((u8 *)g_netNoticeRecord_v + 0x1))
#undef g_joinedTitleLevel
#define g_joinedTitleLevel (*(int *)((u8 *)g_joinedTitleName_v + 0x1e))
#undef g_joinedTitleName
#define g_joinedTitleName ((char *)g_joinedTitleName_v)
#undef g_joinedTitlePoints
#define g_joinedTitlePoints (*(int *)((u8 *)g_joinedTitleName_v + 0x22))
#undef g_joinedTitleRating
#define g_joinedTitleRating (*(int *)((u8 *)g_joinedTitleName_v + 0x26))
#undef g_keepCameraAsked
#define g_keepCameraAsked (*(int *)g_keepCameraAsked_v)
#undef g_keptChat
#define g_keptChat ((char *)g_keptChat_v)
#undef g_keptChatLine
#define g_keptChatLine (*(char *)((u8 *)g_keptChat_v + 0x0))
#undef g_keyEnter
#define g_keyEnter (*(int *)((u8 *)g_mouseClicked_v + 0x4))
#undef g_keyFreeCam0
#define g_keyFreeCam0 (*(int *)((u8 *)g_controls_v + 0x0))
#undef g_keyFreeCam1
#define g_keyFreeCam1 (*(int *)((u8 *)g_controls_v + 0x8))
#undef g_keyFreeCam2
#define g_keyFreeCam2 (*(int *)((u8 *)g_controls_v + 0x10))
#undef g_keyFreeCam3
#define g_keyFreeCam3 (*(int *)((u8 *)g_controls_v + 0x18))
#undef g_keyLoadingSkip
#define g_keyLoadingSkip (*(int *)((u8 *)g_controls_v + 0xc8))
#undef g_keyLoadingSkip2
#define g_keyLoadingSkip2 (*(int *)((u8 *)g_controls_v + 0xcc))
#undef g_keySeen
#define g_keySeen ((int *)g_keySeen_v)
#undef g_keyState
#define g_keyState ((u8 *)g_keyState_v)
#undef g_keyWatchChat
#define g_keyWatchChat (*(int *)((u8 *)g_controls_v + 0xa8))
#undef g_keyboard
#define g_keyboard (g_data.g_keyboard_)
#undef g_keyboardActive
#define g_keyboardActive (*(int *)g_keyboardActive_v)
#undef g_keysBlocked
#define g_keysBlocked (*(int *)g_keysBlocked_v)
#undef g_ladderMenuTextures
#define g_ladderMenuTextures ((int *)g_ladderMenuTextures_v)
#undef g_ladderPort
#define g_ladderPort (*(int *)g_ladderPort_v)
#undef g_lanSearch
#define g_lanSearch (*(int *)g_lanSearch_v)
#undef g_language
#define g_language (*(int *)g_language_v)
#undef g_languageId
#define g_languageId (*(u16 *)g_languageId_v)
#undef g_lastCount
#define g_lastCount (*(u32 *)g_lastCount_v)
#undef g_lastCrosshair
#define g_lastCrosshair (*(int *)((u8 *)g_bindRows_v + 0xc))
#undef g_lastFrameClock
#define g_lastFrameClock (*(double *)g_lastFrameClock_v)
#undef g_lastPanel
#define g_lastPanel (*(int *)g_lastPanel_v)
#undef g_lastScreen
#define g_lastScreen (*(int *)g_lastScreen_v)
#undef g_lastTime
#define g_lastTime (*(double *)((u8 *)g_timerClocks_v + 0x8))
#undef g_launchMessage
#define g_launchMessage (*(const char * *)g_launchMessage_v)
#undef g_launcherCheck
#define g_launcherCheck ((u8 *)g_launcherCheck_v)
#undef g_leaveDialogRects
#define g_leaveDialogRects ((int *)g_leaveDialogRects_v)
#undef g_legCount
#define g_legCount (*(int *)g_legCount_v)
#undef g_legList
#define g_legList ((int *)g_legList_v)
#undef g_legPanelName
#define g_legPanelName ((char *)g_legPanelName_v)
#undef g_legsMaxWeight
#define g_legsMaxWeight (*(float *)((u8 *)g_mechSpeeds_v + 0x14))
#undef g_legsSpeedCorrection
#define g_legsSpeedCorrection (*(float *)((u8 *)g_legsStats_v + 0x8))
#undef g_legsStats
#define g_legsStats ((float *)g_legsStats_v)
#undef g_legsWeight
#define g_legsWeight (*(float *)((u8 *)g_legsStats_v + 0x18))
#undef g_listRefreshPeriod
#define g_listRefreshPeriod (*(int *)g_listRefreshPeriod_v)
#undef g_loadFade
#define g_loadFade (*(float *)g_loadFade_v)
#undef g_loadGame
#define g_loadGame (*(u8 * *)g_loadGame_v)
#undef g_loadProgress
#define g_loadProgress (*(float *)g_loadProgress_v)
#undef g_loadStep
#define g_loadStep (*(int *)g_loadStep_v)
#undef g_loadTexture
#define g_loadTexture (*(int *)g_loadTexture_v)
#undef g_loadTimer
#define g_loadTimer ((u8 *)g_loadTimer_v)
#undef g_lobbyBlinkClock
#define g_lobbyBlinkClock (*(float *)g_lobbyBlinkClock_v)
#undef g_lobbyConnectStatus
#define g_lobbyConnectStatus (*(int *)g_lobbyConnectStatus_v)
#undef g_lobbyConnectionBlock
#define g_lobbyConnectionBlock (*(void * *)g_lobbyConnectionBlock_v)
#undef g_lobbyConnectionOpen
#define g_lobbyConnectionOpen (*(int *)g_lobbyConnectionOpen_v)
#undef g_lobbyJoinRequest
#define g_lobbyJoinRequest (*(int *)g_lobbyJoinRequest_v)
#undef g_lobbyJoinStarted
#define g_lobbyJoinStarted (*(int *)g_lobbyJoinStarted_v)
#undef g_lobbyListPage
#define g_lobbyListPage (*(int *)g_lobbyListPage_v)
#undef g_lobbyListRow
#define g_lobbyListRow (*(int *)g_lobbyListRow_v)
#undef g_lobbyPanelsOff
#define g_lobbyPanelsOff (*(int *)g_lobbyPanelsOff_v)
#undef g_lobbyPending
#define g_lobbyPending (*(int *)g_lobbyPending_v)
#undef g_lobbyRefreshing
#define g_lobbyRefreshing (*(int *)g_lobbyRefreshing_v)
#undef g_lobbyReply
#define g_lobbyReply (*(int *)g_lobbyReply_v)
#undef g_lobbyReplyKind
#define g_lobbyReplyKind (*(u32 *)((u8 *)g_lobbyReplyRecord_v + 0x4a))
#undef g_lobbyReplyRecord
#define g_lobbyReplyRecord ((u8 *)g_lobbyReplyRecord_v)
#undef g_lobbySearching
#define g_lobbySearching (*(int *)g_lobbySearching_v)
#undef g_lobbySocket
#define g_lobbySocket (*(u32 *)g_lobbySocket_v)
#undef g_lobbyStatus
#define g_lobbyStatus (*(int *)g_lobbyStatus_v)
#undef g_lobbySubState
#define g_lobbySubState (*(int *)g_lobbySubState_v)
#undef g_lobbyTcpPort
#define g_lobbyTcpPort (*(int *)g_lobbyTcpPort_v)
#undef g_lobbyTopOutlines
#define g_lobbyTopOutlines ((int *)g_lobbyTopOutlines_v)
#undef g_lobbyTopRect
#define g_lobbyTopRect ((int *)g_lobbyTopRect_v)
#undef g_localAddress
#define g_localAddress ((char *)g_data.g_localAddress_)
#undef g_localPlayer
#define g_localPlayer (*(int *)g_localPlayer_v)
#undef g_localPlayerData
#define g_localPlayerData (*(u32 *)g_localPlayerData_v)
#undef g_localPlayerId
#define g_localPlayerId (*(u32 *)g_localPlayerId_v)
#undef g_logBMPRGBFile
#define g_logBMPRGBFile ((u32 *)g_data.g_logBMPRGBFile_)
#undef g_logCollisionVolume
#define g_logCollisionVolume ((u32 *)g_data.g_logCollisionVolume_)
#undef g_logConsole
#define g_logConsole ((u32 *)g_data.g_logConsole_)
#undef g_logHook
#define g_logHook (*(void * *)g_logHook_v)
#undef g_logLight
#define g_logLight ((u32 *)g_data.g_logLight_)
#undef g_logPackedColor
#define g_logPackedColor ((u32 *)g_data.g_logPackedColor_)
#undef g_logRealColor
#define g_logRealColor ((u32 *)g_data.g_logRealColor_)
#undef g_logScene
#define g_logScene ((u32 *)g_data.g_logScene_)
#undef g_logShape
#define g_logShape ((u32 *)g_data.g_logShape_)
#undef g_logShapeManager
#define g_logShapeManager ((u32 *)g_data.g_logShapeManager_)
#undef g_logSkeleton
#define g_logSkeleton ((u32 *)g_data.g_logSkeleton_)
#undef g_logSkeletonManager
#define g_logSkeletonManager ((u32 *)g_data.g_logSkeletonManager_)
#undef g_logSound
#define g_logSound ((u32 *)g_data.g_logSound_)
#undef g_logStage
#define g_logStage ((u32 *)g_data.g_logStage_)
#undef g_logTexture
#define g_logTexture ((u32 *)g_data.g_logTexture_)
#undef g_logTextureManager
#define g_logTextureManager ((u32 *)g_data.g_logTextureManager_)
#undef g_logTimeSync
#define g_logTimeSync ((u32 *)g_data.g_logTimeSync_)
#undef g_logUnit
#define g_logUnit ((u32 *)g_data.g_logUnit_)
#undef g_logUnitPartInfo
#define g_logUnitPartInfo ((u32 *)g_data.g_logUnitPartInfo_)
#undef g_logUnitPoseInfo
#define g_logUnitPoseInfo ((u32 *)g_data.g_logUnitPoseInfo_)
#undef g_logViewVolume
#define g_logViewVolume ((u32 *)g_data.g_logViewVolume_)
#undef g_loginFormBottom
#define g_loginFormBottom (*(int *)g_loginFormBottom_v)
#undef g_loginFormLeft
#define g_loginFormLeft (*(int *)g_loginFormLeft_v)
#undef g_loginFormRects
#define g_loginFormRects ((int *)g_loginFormRects_v)
#undef g_loginToSend
#define g_loginToSend (g_data.g_loginToSend_)
#undef g_logoFade
#define g_logoFade (*(float *)g_logoFade_v)
#undef g_logoFadeLate
#define g_logoFadeLate (*(float *)g_logoFadeLate_v)
#undef g_logoTexture
#define g_logoTexture (*(int *)g_logoTexture_v)
#undef g_mainMenuDepth
#define g_mainMenuDepth (*(u32 *)g_mainMenuDepth_v)
#undef g_mainMenuFadingIn
#define g_mainMenuFadingIn (*(int *)g_mainMenuFadingIn_v)
#undef g_mainMenuFrames
#define g_mainMenuFrames (*(int *)g_mainMenuFrames_v)
#undef g_mainMenuOutlines
#define g_mainMenuOutlines ((int *)g_mainMenuOutlines_v)
#undef g_mainMenuPicked
#define g_mainMenuPicked (*(int *)g_mainMenuPicked_v)
#undef g_mainMenuTextures
#define g_mainMenuTextures ((int *)g_mainMenuTextures_v)
#undef g_mainWindow
#define g_mainWindow (*(void * *)g_mainWindow_v)
#undef g_mapChoiceKeptTable
#define g_mapChoiceKeptTable ((u8 *)g_mapChoiceKeptTable_v)
#undef g_mapChoiceTable
#define g_mapChoiceTable ((u8 *)g_mapChoiceTable_v)
#undef g_mapEntry22On
#define g_mapEntry22On (*(int *)((u8 *)g_mapChoiceKeptTable_v + 0xb0))
#undef g_mapEntry23On
#define g_mapEntry23On (*(int *)((u8 *)g_mapChoiceKeptTable_v + 0xb8))
#undef g_mapEntry24On
#define g_mapEntry24On (*(int *)((u8 *)g_mapChoiceKeptTable_v + 0xc0))
#undef g_mapListFlaggedCount
#define g_mapListFlaggedCount (*(int *)g_mapListFlaggedCount_v)
#undef g_mapListKept
#define g_mapListKept (*(int *)g_mapListKept_v)
#undef g_mapListMade
#define g_mapListMade (*(int *)g_mapListMade_v)
#undef g_mapListOpen
#define g_mapListOpen (*(int *)g_mapListOpen_v)
#undef g_mapListRects
#define g_mapListRects ((int *)g_mapListRects_v)
#undef g_mapMissing
#define g_mapMissing (*(int *)g_mapMissing_v)
#undef g_mapNames
#define g_mapNames ((char *)g_data.g_mapNames_)
#undef g_mapPreviewChanged
#define g_mapPreviewChanged (*(int *)g_mapPreviewChanged_v)
#undef g_mapPreviewTexture
#define g_mapPreviewTexture (*(int *)g_mapPreviewTexture_v)
#undef g_mapRotation
#define g_mapRotation (*(int *)g_mapRotation_v)
#undef g_mapSelectBottom
#define g_mapSelectBottom (*(int *)g_mapSelectBottom_v)
#undef g_mapSelectCount
#define g_mapSelectCount (*(int *)g_mapSelectCount_v)
#undef g_mapSelectDim
#define g_mapSelectDim ((u32 *)g_mapSelectDim_v)
#undef g_mapSelectDimA
#define g_mapSelectDimA (*(u32 *)((u8 *)g_mapSelectDim_v + 0xc))
#undef g_mapSelectDimB
#define g_mapSelectDimB (*(u32 *)((u8 *)g_mapSelectDim_v + 0x8))
#undef g_mapSelectDimG
#define g_mapSelectDimG (*(u32 *)((u8 *)g_mapSelectDim_v + 0x4))
#undef g_mapSelectDimR
#define g_mapSelectDimR (*(u32 *)((u8 *)g_mapSelectDim_v + 0x0))
#undef g_mapSelectFirst
#define g_mapSelectFirst (*(int *)g_mapSelectFirst_v)
#undef g_mapSelectLeft
#define g_mapSelectLeft (*(int *)g_mapSelectLeft_v)
#undef g_mapSelectLit
#define g_mapSelectLit ((u32 *)g_mapSelectLit_v)
#undef g_mapSelectLitA
#define g_mapSelectLitA (*(u32 *)((u8 *)g_mapSelectLit_v + 0xc))
#undef g_mapSelectLitB
#define g_mapSelectLitB (*(u32 *)((u8 *)g_mapSelectLit_v + 0x8))
#undef g_mapSelectLitG
#define g_mapSelectLitG (*(u32 *)((u8 *)g_mapSelectLit_v + 0x4))
#undef g_mapSelectLitR
#define g_mapSelectLitR (*(int *)((u8 *)g_mapSelectLit_v + 0x0))
#undef g_mapSelectRects
#define g_mapSelectRects ((int *)g_mapSelectRects_v)
#undef g_mapSelectRight
#define g_mapSelectRight (*(int *)g_mapSelectRight_v)
#undef g_mapSelectTop
#define g_mapSelectTop (*(int *)g_mapSelectTop_v)
#undef g_mapTitle
#define g_mapTitle ((char *)g_data.g_mapTitle_)
#undef g_mapTop
#define g_mapTop (*(int *)g_mapTop_v)
#undef g_matchChatCaretX
#define g_matchChatCaretX (*(int *)g_matchChatCaretX_v)
#undef g_matchChatCaretY
#define g_matchChatCaretY (*(int *)g_matchChatCaretY_v)
#undef g_matchEndedByServer
#define g_matchEndedByServer (*(int *)g_matchEndedByServer_v)
#undef g_matchEndedByUser
#define g_matchEndedByUser (*(int *)g_matchEndedByUser_v)
#undef g_matchLogWritten
#define g_matchLogWritten (*(int *)g_matchLogWritten_v)
#undef g_matchMode
#define g_matchMode (*(int *)g_matchMode_v)
#undef g_matchRunning
#define g_matchRunning (*(int *)g_matchRunning_v)
#undef g_mciCallback
#define g_mciCallback (*(u32 *)g_mciCallback_v)
#undef g_mciDevice
#define g_mciDevice (*(u32 *)g_mciDevice_v)
#undef g_mciFrom
#define g_mciFrom (*(u32 *)g_mciFrom_v)
#undef g_mciTo
#define g_mciTo (*(u32 *)g_mciTo_v)
#undef g_mechBoosterEnergy
#define g_mechBoosterEnergy (*(float *)g_mechBoosterEnergy_v)
#undef g_mechBoosterRecharge
#define g_mechBoosterRecharge (*(float *)g_mechBoosterRecharge_v)
#undef g_mechBoosterValue3
#define g_mechBoosterValue3 (*(float *)g_mechBoosterValue3_v)
#undef g_mechChanged
#define g_mechChanged (*(int *)g_mechChanged_v)
#undef g_mechDetectionAngle
#define g_mechDetectionAngle (*(float *)g_mechDetectionAngle_v)
#undef g_mechDetectionRange
#define g_mechDetectionRange (*(float *)g_mechDetectionRange_v)
#undef g_mechHackingLevel
#define g_mechHackingLevel (*(int *)g_mechHackingLevel_v)
#undef g_mechItem2
#define g_mechItem2 (*(u32 *)((u8 *)g_mechSettings_v + 0x8))
#undef g_mechItem3
#define g_mechItem3 (*(u32 *)((u8 *)g_mechSettings_v + 0xc))
#undef g_mechItem4
#define g_mechItem4 (*(u32 *)((u8 *)g_mechSettings_v + 0x10))
#undef g_mechItem5
#define g_mechItem5 (*(u32 *)((u8 *)g_mechSettings_v + 0x14))
#undef g_mechLegsBonus1
#define g_mechLegsBonus1 (*(float *)g_mechLegsBonus1_v)
#undef g_mechLegsBonus2
#define g_mechLegsBonus2 (*(float *)g_mechLegsBonus2_v)
#undef g_mechLegsBonus3
#define g_mechLegsBonus3 (*(float *)g_mechLegsBonus3_v)
#undef g_mechLegsSpeedCorrection
#define g_mechLegsSpeedCorrection (*(float *)g_mechLegsSpeedCorrection_v)
#undef g_mechLegsValue2
#define g_mechLegsValue2 (*(float *)g_mechLegsValue2_v)
#undef g_mechLockOnTime
#define g_mechLockOnTime (*(float *)g_mechLockOnTime_v)
#undef g_mechMaxSpeedBwd
#define g_mechMaxSpeedBwd (*(float *)((u8 *)g_mechSpeeds_v + 0x8))
#undef g_mechMobility
#define g_mechMobility (*(float *)g_mechMobility_v)
#undef g_mechNormalSpeed
#define g_mechNormalSpeed (*(float *)((u8 *)g_mechSpeeds_v + 0x0))
#undef g_mechPartStats
#define g_mechPartStats ((int *)g_mechPartStats_v)
#undef g_mechSettings
#define g_mechSettings ((int *)g_mechSettings_v)
#undef g_mechSpeeds
#define g_mechSpeeds ((float *)g_mechSpeeds_v)
#undef g_mechTargetKeepTime
#define g_mechTargetKeepTime (*(float *)g_mechTargetKeepTime_v)
#undef g_menuCamX
#define g_menuCamX (*(u32 *)g_menuCamX_v)
#undef g_menuCamZ
#define g_menuCamZ (*(u32 *)g_menuCamZ_v)
#undef g_menuCameraHeight
#define g_menuCameraHeight (*(int *)((u8 *)g_menuLook_v + 0x8))
#undef g_menuCameraLook
#define g_menuCameraLook (*(u32 *)((u8 *)g_menuLook_v + 0x0))
#undef g_menuCameraLookY
#define g_menuCameraLookY (*(u32 *)((u8 *)g_menuLook_v + 0x4))
#undef g_menuCameraPos
#define g_menuCameraPos (*(u32 *)((u8 *)g_menuEye_v + 0x0))
#undef g_menuCameraX
#define g_menuCameraX (*(int *)((u8 *)g_menuEyeHome_v + 0x0))
#undef g_menuCameraY
#define g_menuCameraY (*(int *)((u8 *)g_menuEyeHome_v + 0x4))
#undef g_menuCameraZ
#define g_menuCameraZ (*(int *)((u8 *)g_menuEyeHome_v + 0x8))
#undef g_menuEye
#define g_menuEye ((float *)g_menuEye_v)
#undef g_menuEyeHome
#define g_menuEyeHome ((float *)g_menuEyeHome_v)
#undef g_menuFade
#define g_menuFade (*(float *)g_menuFade_v)
#undef g_menuFrameCount
#define g_menuFrameCount (*(int *)g_menuFrameCount_v)
#undef g_menuFrameCounter
#define g_menuFrameCounter (*(int *)g_menuFrameCounter_v)
#undef g_menuFramePhase
#define g_menuFramePhase (*(int *)g_menuFramePhase_v)
#undef g_menuFrameTextures
#define g_menuFrameTextures ((int *)g_menuFrameTextures_v)
#undef g_menuHintClock
#define g_menuHintClock (*(int *)g_menuHintClock_v)
#undef g_menuHintStep
#define g_menuHintStep (*(u32 *)g_menuHintStep_v)
#undef g_menuIdleTime
#define g_menuIdleTime (*(int *)g_menuIdleTime_v)
#undef g_menuLook
#define g_menuLook ((float *)g_menuLook_v)
#undef g_menuLookAtX
#define g_menuLookAtX (*(int *)((u8 *)g_menuLookHome_v + 0x0))
#undef g_menuLookAtY
#define g_menuLookAtY (*(int *)((u8 *)g_menuLookHome_v + 0x4))
#undef g_menuLookAtZ
#define g_menuLookAtZ (*(int *)((u8 *)g_menuLookHome_v + 0x8))
#undef g_menuLookHome
#define g_menuLookHome ((float *)g_menuLookHome_v)
#undef g_menuScaleX
#define g_menuScaleX (*(float *)g_menuScaleX_v)
#undef g_menuScaleY
#define g_menuScaleY (*(float *)g_menuScaleY_v)
#undef g_menuTunnel
#define g_menuTunnel (*(TunnelRing * *)g_menuTunnel_v)
#undef g_menuTunnelSpeed
#define g_menuTunnelSpeed (*(u32 *)g_menuTunnelSpeed_v)
#undef g_menuTunnelTexture
#define g_menuTunnelTexture (*(int *)g_menuTunnelTexture_v)
#undef g_menuVolume
#define g_menuVolume (*(int *)g_menuVolume_v)
#undef g_messageBoxArgs
#define g_messageBoxArgs (*(va_list *)g_messageBoxArgs_v)
#undef g_messages
#define g_messages ((char *)g_messages_v)
#undef g_misHeader1
#define g_misHeader1 (*(int *)((u8 *)g_missionHeader_v + 0x4))
#undef g_misHeader2
#define g_misHeader2 (*(int *)((u8 *)g_missionHeader_v + 0x8))
#undef g_misHeader3
#define g_misHeader3 (*(int *)((u8 *)g_missionHeader_v + 0xc))
#undef g_missionBusy
#define g_missionBusy (*(int *)g_missionBusy_v)
#undef g_missionChosen
#define g_missionChosen (*(int *)g_missionChosen_v)
#undef g_missionClearBuffer
#define g_missionClearBuffer ((u8 *)g_missionClearBuffer_v)
#undef g_missionColourDim
#define g_missionColourDim ((u32 *)g_missionColourDim_v)
#undef g_missionColourLit
#define g_missionColourLit ((u32 *)g_missionColourLit_v)
#undef g_missionCount
#define g_missionCount (*(int *)((u8 *)g_missionHeader_v + 0x0))
#undef g_missionHeader
#define g_missionHeader ((u32 *)g_missionHeader_v)
#undef g_missionPage
#define g_missionPage (*(int *)g_missionPage_v)
#undef g_missionPicked
#define g_missionPicked (*(int *)g_missionPicked_v)
#undef g_missionPreviewDue
#define g_missionPreviewDue (*(int *)g_missionPreviewDue_v)
#undef g_missionSelectLeft
#define g_missionSelectLeft (*(int *)((u8 *)g_missionSelectRect_v + 0x0))
#undef g_missionSelectRect
#define g_missionSelectRect ((int *)g_missionSelectRect_v)
#undef g_missionSelectTop
#define g_missionSelectTop (*(int *)((u8 *)g_missionSelectRect_v + 0x4))
#undef g_missionShowBackground
#define g_missionShowBackground (*(int *)g_missionShowBackground_v)
#undef g_missionShown
#define g_missionShown (*(int *)g_missionShown_v)
#undef g_missionStage
#define g_missionStage (*(int *)g_missionStage_v)
#undef g_missionStarted
#define g_missionStarted (*(int *)g_missionStarted_v)
#undef g_missionTop
#define g_missionTop (*(int *)g_missionTop_v)
#undef g_missions
#define g_missions ((u8 *)g_missions_v)
#undef g_missionselRects
#define g_missionselRects ((int *)g_missionselRects_v)
#undef g_modeChanged
#define g_modeChanged (*(int *)g_modeChanged_v)
#undef g_modemProviderGuid
#define g_modemProviderGuid ((u8 *)g_modemProviderGuid_v)
#undef g_mouse
#define g_mouse (g_data.g_mouse_)
#undef g_mouse2Down
#define g_mouse2Down (*(int *)((u8 *)g_mouseButtonsHeld_v + 0x4))
#undef g_mouse3Down
#define g_mouse3Down (*(int *)((u8 *)g_mouseButtonsHeld_v + 0x8))
#undef g_mouseActive
#define g_mouseActive (*(int *)g_mouseActive_v)
#undef g_mouseButtonsHeld
#define g_mouseButtonsHeld ((int *)g_mouseButtonsHeld_v)
#undef g_mouseClicked
#define g_mouseClicked ((int *)g_mouseClicked_v)
#undef g_mouseInvert
#define g_mouseInvert (*(int *)((u8 *)g_controls_v + 0x100))
#undef g_mousePos
#define g_mousePos ((int *)g_mousePos_v)
#undef g_mouseSensitivity
#define g_mouseSensitivity (*(int *)((u8 *)g_controls_v + 0x108))
#undef g_mouseSmooth
#define g_mouseSmooth (*(int *)((u8 *)g_controls_v + 0x104))
#undef g_mouseTaken
#define g_mouseTaken (*(int *)g_mouseTaken_v)
#undef g_mouseWheel
#define g_mouseWheel (*(int *)g_mouseWheel_v)
#undef g_mouseWheelTurned
#define g_mouseWheelTurned (*(int *)g_mouseWheelTurned_v)
#undef g_mouseX
#define g_mouseX (*(int *)((u8 *)g_mousePos_v + 0x0))
#undef g_mouseY
#define g_mouseY (*(int *)((u8 *)g_mousePos_v + 0x4))
#undef g_music
#define g_music (*(void * *)g_music_v)
#undef g_musicDuration
#define g_musicDuration ((u32 *)g_musicDuration_v)
#undef g_musicEndHigh
#define g_musicEndHigh (*(int *)((u8 *)g_musicDuration_v + 0x4))
#undef g_musicLength
#define g_musicLength (*(u32 *)((u8 *)g_musicDuration_v + 0x0))
#undef g_musicVolume
#define g_musicVolume (*(int *)((u8 *)g_soundSettings_v + 0x4))
#undef g_musicVolumeSetting
#define g_musicVolumeSetting (*(int *)g_musicVolumeSetting_v)
#undef g_netAccountBuffer
#define g_netAccountBuffer (*(char * *)g_netAccountBuffer_v)
#undef g_netBlockSize
#define g_netBlockSize (*(u32 *)g_netBlockSize_v)
#undef g_netChatMessageKind
#define g_netChatMessageKind (*(int *)g_netChatMessageKind_v)
#undef g_netChatMessageText
#define g_netChatMessageText (*(int *)g_netChatMessageText_v)
#undef g_netChatMessageWord1
#define g_netChatMessageWord1 (*(int *)g_netChatMessageWord1_v)
#undef g_netChatMessageWord2
#define g_netChatMessageWord2 (*(int *)g_netChatMessageWord2_v)
#undef g_netClaimedSlot
#define g_netClaimedSlot (*(int *)((u8 *)g_netSlotMsg_v + 0x4))
#undef g_netConnected
#define g_netConnected (*(int *)g_netConnected_v)
#undef g_netHostGone
#define g_netHostGone (*(int *)g_netHostGone_v)
#undef g_netInfoPacket
#define g_netInfoPacket (*(u8 * *)g_netInfoPacket_v)
#undef g_netJoinMessage
#define g_netJoinMessage (*(char * *)g_netJoinMessage_v)
#undef g_netKindWord
#define g_netKindWord (*(u32 * *)g_netKindWord_v)
#undef g_netLastRequest
#define g_netLastRequest (*(int *)g_netLastRequest_v)
#undef g_netLeaveBuffer
#define g_netLeaveBuffer (*(char * *)g_netLeaveBuffer_v)
#undef g_netListDone
#define g_netListDone (*(int *)g_netListDone_v)
#undef g_netLobbyMessage
#define g_netLobbyMessage (*(u32 * *)g_netLobbyMessage_v)
#undef g_netNotice
#define g_netNotice (*(u8 *)((u8 *)g_netNoticeRecord_v + 0x0))
#undef g_netNoticeIn
#define g_netNoticeIn (*(int *)g_netNoticeIn_v)
#undef g_netNoticeRecord
#define g_netNoticeRecord ((u8 *)g_netNoticeRecord_v)
#undef g_netPacketMessageKind
#define g_netPacketMessageKind (*(int *)((u8 *)g_netSendPacket_v + 0x0))
#undef g_netPlayerList
#define g_netPlayerList ((u8 *)g_data.g_netPlayerList_)
#undef g_netPlayerRecordPacket
#define g_netPlayerRecordPacket (*(u8 * *)g_netPlayerRecordPacket_v)
#undef g_netQueueOnline
#define g_netQueueOnline (*(int *)g_netQueueOnline_v)
#undef g_netRankingBuffer
#define g_netRankingBuffer (*(int * *)g_netRankingBuffer_v)
#undef g_netRecvBuffer
#define g_netRecvBuffer (*(int *)((u8 *)g_netRecvRecord_v + 0x0))
#undef g_netRecvRecord
#define g_netRecvRecord ((u8 *)g_netRecvRecord_v)
#undef g_netRequestWord
#define g_netRequestWord (*(u32 *)g_netRequestWord_v)
#undef g_netRole
#define g_netRole (*(int *)g_netRole_v)
#undef g_netSelectionPacket
#define g_netSelectionPacket (*(u8 * *)g_netSelectionPacket_v)
#undef g_netSendBuffer
#define g_netSendBuffer (*(char * *)g_netSendBuffer_v)
#undef g_netSendName
#define g_netSendName (*(char * *)g_netSendName_v)
#undef g_netSendPacket
#define g_netSendPacket ((u32 *)g_netSendPacket_v)
#undef g_netSlotMessageKind
#define g_netSlotMessageKind (*(int *)((u8 *)g_netSlotMsg_v + 0x0))
#undef g_netSlotMsg
#define g_netSlotMsg ((u32 *)g_netSlotMsg_v)
#undef g_netSlots
#define g_netSlots ((u8 *)g_data.g_netSlots_)
#undef g_newArenaForm
#define g_newArenaForm ((int *)g_newArenaForm_v)
#undef g_newArenaFormBottom
#define g_newArenaFormBottom (*(int *)((u8 *)g_newArenaForm_v + 0xc))
#undef g_newArenaFormLeft
#define g_newArenaFormLeft (*(int *)((u8 *)g_newArenaForm_v + 0x0))
#undef g_newArenaFormRight
#define g_newArenaFormRight (*(int *)((u8 *)g_newArenaForm_v + 0x8))
#undef g_newArenaFormTop
#define g_newArenaFormTop (*(int *)((u8 *)g_newArenaForm_v + 0x4))
#undef g_newArenaKind
#define g_newArenaKind (*(u8 *)((u8 *)g_newArenaName_v + 0x22))
#undef g_newArenaMap
#define g_newArenaMap (*(signed char *)((u8 *)g_newArenaName_v + 0x20))
#undef g_newArenaMode
#define g_newArenaMode (*(u8 *)((u8 *)g_newArenaName_v + 0x23))
#undef g_newArenaName
#define g_newArenaName ((char *)g_newArenaName_v)
#undef g_newArenaPassword
#define g_newArenaPassword (*(int *)((u8 *)g_newArenaName_v + 0x26))
#undef g_newArenaPassword4
#define g_newArenaPassword4 (*(int *)((u8 *)g_newArenaName_v + 0x2a))
#undef g_newArenaPlayers
#define g_newArenaPlayers (*(u8 *)((u8 *)g_newArenaName_v + 0x21))
#undef g_newNameDialogBottom
#define g_newNameDialogBottom (*(int *)g_newNameDialogBottom_v)
#undef g_newNameDialogLeft
#define g_newNameDialogLeft (*(int *)g_newNameDialogLeft_v)
#undef g_newNameDialogRects
#define g_newNameDialogRects ((int *)g_newNameDialogRects_v)
#undef g_newNameDialogRight
#define g_newNameDialogRight (*(int *)g_newNameDialogRight_v)
#undef g_newNameDialogTop
#define g_newNameDialogTop (*(int *)g_newNameDialogTop_v)
#undef g_nextNumber
#define g_nextNumber ((int *)g_nextNumber_v)
#undef g_nextScreen
#define g_nextScreen (*(int *)g_nextScreen_v)
#undef g_openLoginName
#define g_openLoginName (*(int *)g_openLoginName_v)
#undef g_otherModeHeight
#define g_otherModeHeight (*(int *)g_otherModeHeight_v)
#undef g_otherModeWidth
#define g_otherModeWidth (*(int *)g_otherModeWidth_v)
#undef g_outlinesCopy
#define g_outlinesCopy ((int *)g_outlinesCopy_v)
#undef g_packedBlue
#define g_packedBlue ((u8 *)g_packedBlue_v)
#undef g_packedGreen
#define g_packedGreen ((u8 *)g_packedGreen_v)
#undef g_packedGrey
#define g_packedGrey ((u8 *)g_packedGrey_v)
#undef g_packedWhite
#define g_packedWhite ((u8 *)g_data.g_packedWhite_)
#undef g_packedYellow
#define g_packedYellow ((u8 *)g_packedYellow_v)
#undef g_packetQueue
#define g_packetQueue ((u8 *)g_packetQueue_v)
#undef g_panelBoxes
#define g_panelBoxes ((u8 *)g_panelBoxes_v)
#undef g_panelGlow
#define g_panelGlow (*(float *)g_panelGlow_v)
#undef g_panelGlowStep
#define g_panelGlowStep (*(u32 *)g_panelGlowStep_v)
#undef g_panelHovered
#define g_panelHovered (*(int *)g_panelHovered_v)
#undef g_partBox0Offset
#define g_partBox0Offset (*(u32 *)((u8 *)g_panelBoxes_v + 0x54))
#undef g_partBox1Offset
#define g_partBox1Offset (*(u32 *)((u8 *)g_panelBoxes_v + 0xac))
#undef g_partBox2Offset
#define g_partBox2Offset (*(u32 *)((u8 *)g_panelBoxes_v + 0x104))
#undef g_partBox3Offset
#define g_partBox3Offset (*(u32 *)((u8 *)g_panelBoxes_v + 0x15c))
#undef g_partBox4Offset
#define g_partBox4Offset (*(u32 *)((u8 *)g_panelBoxes_v + 0x1b4))
#undef g_partBox5Offset
#define g_partBox5Offset (*(u32 *)((u8 *)g_panelBoxes_v + 0x20c))
#undef g_partRecords
#define g_partRecords ((u8 *)g_partRecords_v)
#undef g_paused
#define g_paused (*(int *)g_paused_v)
#undef g_penFixedBottomLeft
#define g_penFixedBottomLeft ((float *)g_penFixedBottomLeft_v)
#undef g_penFixedBottomRight
#define g_penFixedBottomRight ((float *)g_penFixedBottomRight_v)
#undef g_penFixedTopLeft
#define g_penFixedTopLeft ((float *)g_penFixedTopLeft_v)
#undef g_penFixedTopRight
#define g_penFixedTopRight ((float *)g_penFixedTopRight_v)
#undef g_penFixedWidths
#define g_penFixedWidths ((int *)g_penFixedWidths_v)
#undef g_penFontNeverSet
#define g_penFontNeverSet (*(int *)g_penFontNeverSet_v)
#undef g_penFontTexture
#define g_penFontTexture (*(int *)g_penFontTexture_v)
#undef g_penPropBottomLeft
#define g_penPropBottomLeft ((float *)g_penPropBottomLeft_v)
#undef g_penPropBottomRight
#define g_penPropBottomRight ((float *)g_penPropBottomRight_v)
#undef g_penPropTopLeft
#define g_penPropTopLeft ((float *)g_penPropTopLeft_v)
#undef g_penPropTopRight
#define g_penPropTopRight ((float *)g_penPropTopRight_v)
#undef g_perfCounter
#define g_perfCounter (*(u32 *)g_perfCounter_v)
#undef g_pilotChosen
#define g_pilotChosen (*(int *)g_pilotChosen_v)
#undef g_pilotClan
#define g_pilotClan (*(int *)((u8 *)g_pilotStats_v + 0x8))
#undef g_pilotLevel
#define g_pilotLevel (*(int *)((u8 *)g_pilotStats_v + 0x0))
#undef g_pilotLevelKept
#define g_pilotLevelKept (*(int *)((u8 *)g_pilotStatsKept_v + 0x0))
#undef g_pilotLosses
#define g_pilotLosses (*(int *)((u8 *)g_pilotStats_v + 0x18))
#undef g_pilotLossesKept
#define g_pilotLossesKept (*(int *)((u8 *)g_pilotStatsKept_v + 0x18))
#undef g_pilotNoise
#define g_pilotNoise ((u8 *)g_pilotNoise_v)
#undef g_pilotPoints
#define g_pilotPoints (*(int *)((u8 *)g_pilotStats_v + 0x4))
#undef g_pilotPointsKept
#define g_pilotPointsKept (*(int *)((u8 *)g_pilotStatsKept_v + 0x4))
#undef g_pilotRating
#define g_pilotRating (*(int *)((u8 *)g_pilotStats_v + 0xc))
#undef g_pilotRatingKept
#define g_pilotRatingKept (*(int *)((u8 *)g_pilotStatsKept_v + 0xc))
#undef g_pilotScore
#define g_pilotScore (*(int *)((u8 *)g_pilotStats_v + 0x10))
#undef g_pilotScoreKept
#define g_pilotScoreKept (*(int *)((u8 *)g_pilotStatsKept_v + 0x10))
#undef g_pilotSelectBottom
#define g_pilotSelectBottom (*(int *)g_pilotSelectBottom_v)
#undef g_pilotSelectLeft
#define g_pilotSelectLeft (*(int *)g_pilotSelectLeft_v)
#undef g_pilotSelectRects
#define g_pilotSelectRects ((int *)g_pilotSelectRects_v)
#undef g_pilotSelectRight
#define g_pilotSelectRight (*(int *)g_pilotSelectRight_v)
#undef g_pilotSelectTop
#define g_pilotSelectTop (*(int *)g_pilotSelectTop_v)
#undef g_pilotStats
#define g_pilotStats ((int *)g_pilotStats_v)
#undef g_pilotStatsKept
#define g_pilotStatsKept ((int *)g_pilotStatsKept_v)
#undef g_pilotWinRate
#define g_pilotWinRate (*(float *)((u8 *)g_pilotStats_v + 0x1c))
#undef g_pilotWins
#define g_pilotWins (*(int *)((u8 *)g_pilotStats_v + 0x14))
#undef g_pilotWinsKept
#define g_pilotWinsKept (*(int *)((u8 *)g_pilotStatsKept_v + 0x14))
#undef g_pingDataEvent
#define g_pingDataEvent (*(void * *)g_pingDataEvent_v)
#undef g_pingStopEvent
#define g_pingStopEvent (*(void * *)g_pingStopEvent_v)
#undef g_pingThread
#define g_pingThread (*(void * *)g_pingThread_v)
#undef g_pingThreadId
#define g_pingThreadId (*(int *)g_pingThreadId_v)
#undef g_pingTime
#define g_pingTime (*(u32 *)g_pingTime_v)
#undef g_pixelFormatFilled
#define g_pixelFormatFilled (*(u8 *)g_pixelFormatFilled_v)
#undef g_playerCorporation
#define g_playerCorporation (*(int *)g_playerCorporation_v)
#undef g_playerCount
#define g_playerCount (*(int *)g_playerCount_v)
#undef g_playerHasClan
#define g_playerHasClan (*(u8 *)((u8 *)g_playerName_v + 0x2e))
#undef g_playerListCount
#define g_playerListCount (*(int *)g_playerListCount_v)
#undef g_playerListRefused
#define g_playerListRefused (*(int *)g_playerListRefused_v)
#undef g_playerName
#define g_playerName ((char *)g_playerName_v)
#undef g_playerSex
#define g_playerSex (*(int *)g_playerSex_v)
#undef g_playerSlotFlags
#define g_playerSlotFlags ((int *)g_playerSlotFlags_v)
#undef g_popupRects
#define g_popupRects ((int *)g_popupRects_v)
#undef g_primarySoundBuffer
#define g_primarySoundBuffer (*(void * *)g_primarySoundBuffer_v)
#undef g_profile9f6828
#define g_profile9f6828 (*(int *)g_profile9f6828_v)
#undef g_profile9f8ee4
#define g_profile9f8ee4 (g_data.g_profile9f8ee4_)
#undef g_profileColour
#define g_profileColour ((u32 *)g_data.g_profileColour_)
#undef g_profileCount
#define g_profileCount (*(int *)g_profileCount_v)
#undef g_profileDialog2Bottom
#define g_profileDialog2Bottom (*(int *)g_profileDialog2Bottom_v)
#undef g_profileDialog2Right
#define g_profileDialog2Right (*(int *)g_profileDialog2Right_v)
#undef g_profileDialog2X
#define g_profileDialog2X (*(int *)g_profileDialog2X_v)
#undef g_profileDialog2Y
#define g_profileDialog2Y (*(int *)g_profileDialog2Y_v)
#undef g_profileDialogBottom
#define g_profileDialogBottom (*(int *)g_profileDialogBottom_v)
#undef g_profileDialogOpen
#define g_profileDialogOpen (*(int *)g_profileDialogOpen_v)
#undef g_profileDialogRight
#define g_profileDialogRight (*(int *)g_profileDialogRight_v)
#undef g_profileDialogX
#define g_profileDialogX (*(int *)g_profileDialogX_v)
#undef g_profileDialogY
#define g_profileDialogY (*(int *)g_profileDialogY_v)
#undef g_profileDim
#define g_profileDim ((u32 *)g_data.g_profileDim_)
#undef g_profileFrameAlpha
#define g_profileFrameAlpha (*(float *)g_profileFrameAlpha_v)
#undef g_profileFrameStep
#define g_profileFrameStep (*(u32 *)g_profileFrameStep_v)
#undef g_profileHeader
#define g_profileHeader ((u8 *)g_profileHeader_v)
#undef g_profileIntro
#define g_profileIntro (*(int *)g_profileIntro_v)
#undef g_profileIntroSpeed
#define g_profileIntroSpeed (*(float *)g_profileIntroSpeed_v)
#undef g_profileIntroState
#define g_profileIntroState (*(int *)g_profileIntroState_v)
#undef g_profileIntroTime
#define g_profileIntroTime (*(int *)g_profileIntroTime_v)
#undef g_profileIntroZoom
#define g_profileIntroZoom (*(float *)g_profileIntroZoom_v)
#undef g_profileList
#define g_profileList ((char *)g_data.g_profileList_)
#undef g_profileListRects
#define g_profileListRects ((int *)g_profileListRects_v)
#undef g_profileListRow
#define g_profileListRow (*(int *)g_profileListRow_v)
#undef g_profileListTop
#define g_profileListTop (*(int *)g_profileListTop_v)
#undef g_profileMechArm
#define g_profileMechArm (*(int *)((u8 *)g_campaign_v + 0x2e8))
#undef g_profileMechBooster
#define g_profileMechBooster (*(int *)((u8 *)g_campaign_v + 0x2f0))
#undef g_profileMechChest
#define g_profileMechChest (*(int *)((u8 *)g_campaign_v + 0x2e4))
#undef g_profileMechItem0
#define g_profileMechItem0 (*(int *)((u8 *)g_campaign_v + 0x2fc))
#undef g_profileMechItem1
#define g_profileMechItem1 (*(int *)((u8 *)g_campaign_v + 0x300))
#undef g_profileMechItem2
#define g_profileMechItem2 (*(int *)((u8 *)g_campaign_v + 0x304))
#undef g_profileMechItem3
#define g_profileMechItem3 (*(int *)((u8 *)g_campaign_v + 0x308))
#undef g_profileMechItem4
#define g_profileMechItem4 (*(int *)((u8 *)g_campaign_v + 0x30c))
#undef g_profileMechItem5
#define g_profileMechItem5 (*(int *)((u8 *)g_campaign_v + 0x310))
#undef g_profileMechLeg
#define g_profileMechLeg (*(int *)((u8 *)g_campaign_v + 0x2ec))
#undef g_profileMechRecord
#define g_profileMechRecord (*(int *)((u8 *)g_campaign_v + 0x2e0))
#undef g_profileMessage
#define g_profileMessage (*(int *)g_profileMessage_v)
#undef g_profileMessageTime
#define g_profileMessageTime (*(float *)g_profileMessageTime_v)
#undef g_profileName
#define g_profileName ((char *)g_data.g_profileName_)
#undef g_profilePage
#define g_profilePage (*(int *)g_profilePage_v)
#undef g_profilePageBottom
#define g_profilePageBottom (*(int *)g_profilePageBottom_v)
#undef g_profilePageLeft
#define g_profilePageLeft (*(int *)g_profilePageLeft_v)
#undef g_profilePageRects
#define g_profilePageRects ((int *)g_profilePageRects_v)
#undef g_profilePageRight
#define g_profilePageRight (*(int *)g_profilePageRight_v)
#undef g_profilePageTop
#define g_profilePageTop (*(int *)g_profilePageTop_v)
#undef g_profileProgressSaved
#define g_profileProgressSaved (*(int *)g_profileProgressSaved_v)
#undef g_profileRecords
#define g_profileRecords ((u8 *)g_data.g_profileRecords_)
#undef g_profileRowClicked
#define g_profileRowClicked (*(int *)g_profileRowClicked_v)
#undef g_profileScreenReady
#define g_profileScreenReady (*(int *)g_profileScreenReady_v)
#undef g_progressWentUp
#define g_progressWentUp (*(int *)g_progressWentUp_v)
#undef g_projMode
#define g_projMode (*(int *)g_projMode_v)
#undef g_ptxBitPos
#define g_ptxBitPos (*(int *)g_ptxBitPos_v)
#undef g_ptxCbBlue
#define g_ptxCbBlue ((int *)g_ptxCbBlue_v)
#undef g_ptxCbGreen
#define g_ptxCbGreen ((int *)g_ptxCbGreen_v)
#undef g_ptxClampTable
#define g_ptxClampTable ((u8 *)g_ptxClampTable_v)
#undef g_ptxCrGreen
#define g_ptxCrGreen ((int *)g_ptxCrGreen_v)
#undef g_ptxCrRed
#define g_ptxCrRed ((int *)g_ptxCrRed_v)
#undef g_ptxData
#define g_ptxData ((u8 *)g_ptxData_v)
#undef g_ptxDequant
#define g_ptxDequant ((float *)g_ptxDequant_v)
#undef g_ptxLastDc
#define g_ptxLastDc (*(int *)g_ptxLastDc_v)
#undef g_ptxPixels
#define g_ptxPixels ((u8 *)g_ptxPixels_v)
#undef g_ptxPlanes
#define g_ptxPlanes ((u8 *)g_ptxPlanes_v)
#undef g_ptxQuant
#define g_ptxQuant ((int *)g_ptxQuant_v)
#undef g_ptxTable
#define g_ptxTable (*(int *)g_ptxTable_v)
#undef g_ptxTablesReady
#define g_ptxTablesReady (*(int *)g_ptxTablesReady_v)
#undef g_ptxYCbCrTables
#define g_ptxYCbCrTables ((int *)g_ptxYCbCrTables_v)
#undef g_pulse
#define g_pulse (*(float *)g_pulse_v)
#undef g_pulseStep
#define g_pulseStep (*(float *)g_pulseStep_v)
#undef g_quitAsked
#define g_quitAsked (*(int *)g_quitAsked_v)
#undef g_randPos
#define g_randPos (*(u32 *)g_randPos_v)
#undef g_randTable
#define g_randTable ((int *)g_randTable_v)
#undef g_rankingFirst
#define g_rankingFirst (*(int *)g_rankingFirst_v)
#undef g_rankingHaveList
#define g_rankingHaveList (*(int *)g_rankingHaveList_v)
#undef g_rankingLast
#define g_rankingLast (*(int *)g_rankingLast_v)
#undef g_rankingRects
#define g_rankingRects ((int *)g_rankingRects_v)
#undef g_rankingRequestPending
#define g_rankingRequestPending (*(int *)g_rankingRequestPending_v)
#undef g_rankingSort
#define g_rankingSort (*(int *)g_rankingSort_v)
#undef g_rankingWaiting
#define g_rankingWaiting (*(int *)g_rankingWaiting_v)
#undef g_realBlack
#define g_realBlack ((float *)g_realBlack_v)
#undef g_realBlue
#define g_realBlue ((float *)g_realBlue_v)
#undef g_realClear
#define g_realClear ((float *)g_realClear_v)
#undef g_realGreen
#define g_realGreen ((float *)g_realGreen_v)
#undef g_realGrey
#define g_realGrey ((float *)g_realGrey_v)
#undef g_realRed
#define g_realRed ((float *)g_realRed_v)
#undef g_realWhite
#define g_realWhite ((float *)g_realWhite_v)
#undef g_realYellow
#define g_realYellow ((float *)g_realYellow_v)
#undef g_receivedClan
#define g_receivedClan (*(int *)((u8 *)g_netNoticeRecord_v + 0x16))
#undef g_receivedSession
#define g_receivedSession (*(const u8 * *)g_receivedSession_v)
#undef g_rectColour
#define g_rectColour ((Colour *)g_data.g_rectColour_)
#undef g_repeatDown
#define g_repeatDown (*(float *)g_repeatDown_v)
#undef g_repeatUp
#define g_repeatUp (*(float *)g_repeatUp_v)
#undef g_replayRandomOrder
#define g_replayRandomOrder (*(int *)g_replayRandomOrder_v)
#undef g_replayRunning
#define g_replayRunning (*(int *)g_replayRunning_v)
#undef g_replayWrap
#define g_replayWrap (*(int *)g_replayWrap_v)
#undef g_resends
#define g_resends (*(int *)g_resends_v)
#undef g_resolutionNames
#define g_resolutionNames ((u32 *)g_resolutionNames_v)
#undef g_resultMessage
#define g_resultMessage (*(int *)((u8 *)g_resultMsg_v + 0x0))
#undef g_resultMsg
#define g_resultMsg ((u32 *)g_resultMsg_v)
#undef g_retypePassword
#define g_retypePassword (*(int *)g_retypePassword_v)
#undef g_roomAnswerAwaited
#define g_roomAnswerAwaited (*(int *)g_roomAnswerAwaited_v)
#undef g_roomAwaitingServer
#define g_roomAwaitingServer (*(int *)g_roomAwaitingServer_v)
#undef g_roomBright
#define g_roomBright ((u32 *)g_data.g_roomBright_)
#undef g_roomChatting
#define g_roomChatting (*(int *)g_roomChatting_v)
#undef g_roomColours
#define g_roomColours ((float *)g_data.g_roomColours_)
#undef g_roomConnected
#define g_roomConnected (*(int *)g_roomConnected_v)
#undef g_roomCustom
#define g_roomCustom (*(u8 *)((u8 *)g_roomSettingsName_v + 0x22))
#undef g_roomDialogOpen
#define g_roomDialogOpen (*(int *)g_roomDialogOpen_v)
#undef g_roomDim
#define g_roomDim ((u32 *)g_data.g_roomDim_)
#undef g_roomEyeKept
#define g_roomEyeKept ((float *)g_roomEyeKept_v)
#undef g_roomFade
#define g_roomFade (*(float *)g_roomFade_v)
#undef g_roomForm
#define g_roomForm ((int *)g_roomForm_v)
#undef g_roomFormBottom
#define g_roomFormBottom (*(int *)((u8 *)g_roomForm_v + 0xc))
#undef g_roomFormLeft
#define g_roomFormLeft (*(int *)((u8 *)g_roomForm_v + 0x0))
#undef g_roomFormRight
#define g_roomFormRight (*(int *)((u8 *)g_roomForm_v + 0x8))
#undef g_roomFormTop
#define g_roomFormTop (*(int *)((u8 *)g_roomForm_v + 0x4))
#undef g_roomFragLimit
#define g_roomFragLimit (*(u8 *)((u8 *)g_roomSettingsName_v + 0x24))
#undef g_roomGameListBottom
#define g_roomGameListBottom (*(int *)g_roomGameListBottom_v)
#undef g_roomGameListLeft
#define g_roomGameListLeft (*(int *)g_roomGameListLeft_v)
#undef g_roomGameListRight
#define g_roomGameListRight (*(int *)g_roomGameListRight_v)
#undef g_roomGameListTop
#define g_roomGameListTop (*(int *)g_roomGameListTop_v)
#undef g_roomGameMode
#define g_roomGameMode (*(u8 *)((u8 *)g_roomSettingsName_v + 0x23))
#undef g_roomJoined
#define g_roomJoined (*(int *)g_roomJoined_v)
#undef g_roomLeaveDialog
#define g_roomLeaveDialog (*(int *)g_roomLeaveDialog_v)
#undef g_roomList
#define g_roomList ((u8 *)g_roomList_v)
#undef g_roomListCount
#define g_roomListCount (*(int *)g_roomListCount_v)
#undef g_roomListDistanceLimit
#define g_roomListDistanceLimit (*(u32 *)g_roomListDistanceLimit_v)
#undef g_roomListPage
#define g_roomListPage (*(int *)g_roomListPage_v)
#undef g_roomListPages
#define g_roomListPages (*(int *)g_roomListPages_v)
#undef g_roomListPrev
#define g_roomListPrev (*(int *)g_roomListPrev_v)
#undef g_roomListPrevPage
#define g_roomListPrevPage (*(int *)g_roomListPrevPage_v)
#undef g_roomListPrevRank
#define g_roomListPrevRank (*(int *)g_roomListPrevRank_v)
#undef g_roomListRefreshTimer
#define g_roomListRefreshTimer (*(float *)g_roomListRefreshTimer_v)
#undef g_roomListWaiting
#define g_roomListWaiting (*(int *)g_roomListWaiting_v)
#undef g_roomLoginBottom
#define g_roomLoginBottom (*(int *)g_roomLoginBottom_v)
#undef g_roomLoginDue
#define g_roomLoginDue (*(int *)g_roomLoginDue_v)
#undef g_roomLoginLeft
#define g_roomLoginLeft (*(int *)g_roomLoginLeft_v)
#undef g_roomLoginRight
#define g_roomLoginRight (*(int *)g_roomLoginRight_v)
#undef g_roomLoginTop
#define g_roomLoginTop (*(int *)g_roomLoginTop_v)
#undef g_roomLookKept
#define g_roomLookKept ((float *)g_roomLookKept_v)
#undef g_roomMap
#define g_roomMap (*(u8 *)((u8 *)g_roomSettingsName_v + 0x20))
#undef g_roomMech
#define g_roomMech ((u8 *)g_data.g_roomMech_)
#undef g_roomMessageRect
#define g_roomMessageRect ((int *)g_roomMessageRect_v)
#undef g_roomMessageText
#define g_roomMessageText (g_data.g_roomMessageText_)
#undef g_roomMessageText4
#define g_roomMessageText4 (g_data.g_roomMessageText4_)
#undef g_roomMode
#define g_roomMode (*(int *)g_roomMode_v)
#undef g_roomNameSum
#define g_roomNameSum (*(int *)g_roomNameSum_v)
#undef g_roomOutlines
#define g_roomOutlines ((int *)g_roomOutlines_v)
#undef g_roomPacket
#define g_roomPacket (*(u8 * *)g_roomPacket_v)
#undef g_roomPanelBrightness
#define g_roomPanelBrightness (*(u32 *)g_roomPanelBrightness_v)
#undef g_roomPanelEase
#define g_roomPanelEase (*(float *)g_roomPanelEase_v)
#undef g_roomPlayers
#define g_roomPlayers (*(u8 *)((u8 *)g_roomSettingsName_v + 0x21))
#undef g_roomPopup
#define g_roomPopup (*(int *)g_roomPopup_v)
#undef g_roomRecCustom
#define g_roomRecCustom (*(u8 *)((u8 *)g_roomRecName_v + 0x22))
#undef g_roomRecFragLimit
#define g_roomRecFragLimit (*(u8 *)((u8 *)g_roomRecName_v + 0x24))
#undef g_roomRecGameMode
#define g_roomRecGameMode (*(u8 *)((u8 *)g_roomRecName_v + 0x23))
#undef g_roomRecMap
#define g_roomRecMap (*(signed char *)((u8 *)g_roomRecName_v + 0x20))
#undef g_roomRecName
#define g_roomRecName ((char *)g_roomRecName_v)
#undef g_roomRecPlayers
#define g_roomRecPlayers (*(u8 *)((u8 *)g_roomRecName_v + 0x21))
#undef g_roomRecTimeLimit
#define g_roomRecTimeLimit (*(u8 *)((u8 *)g_roomRecName_v + 0x25))
#undef g_roomRecordPacket
#define g_roomRecordPacket (*(u8 * *)g_roomRecordPacket_v)
#undef g_roomRefreshing
#define g_roomRefreshing (*(int *)g_roomRefreshing_v)
#undef g_roomRequestOut
#define g_roomRequestOut (*(int *)g_roomRequestOut_v)
#undef g_roomSearchAnswerIn
#define g_roomSearchAnswerIn (*(int *)g_roomSearchAnswerIn_v)
#undef g_roomSearching
#define g_roomSearching (*(int *)g_roomSearching_v)
#undef g_roomSettingsName
#define g_roomSettingsName ((char *)g_roomSettingsName_v)
#undef g_roomSettingsRects
#define g_roomSettingsRects ((int *)g_roomSettingsRects_v)
#undef g_roomSlideFarX
#define g_roomSlideFarX (*(u32 *)((u8 *)g_roomEyeKept_v + 0x0))
#undef g_roomSlideFarY
#define g_roomSlideFarY (*(u32 *)((u8 *)g_roomEyeKept_v + 0x4))
#undef g_roomSlideFarZ
#define g_roomSlideFarZ (*(u32 *)((u8 *)g_roomEyeKept_v + 0x8))
#undef g_roomSlideNearX
#define g_roomSlideNearX (*(u32 *)((u8 *)g_roomLookKept_v + 0x0))
#undef g_roomSlideNearY
#define g_roomSlideNearY (*(u32 *)((u8 *)g_roomLookKept_v + 0x4))
#undef g_roomSlideNearZ
#define g_roomSlideNearZ (*(u32 *)((u8 *)g_roomLookKept_v + 0x8))
#undef g_roomState
#define g_roomState (*(int *)g_roomState_v)
#undef g_roomTimeLimit
#define g_roomTimeLimit (*(u8 *)((u8 *)g_roomSettingsName_v + 0x25))
#undef g_roomTunnelDepth
#define g_roomTunnelDepth (*(u32 *)g_roomTunnelDepth_v)
#undef g_savedColourChoices
#define g_savedColourChoices ((u8 *)g_data.g_savedColourChoices_)
#undef g_savedMechArm
#define g_savedMechArm (*(int *)((u8 *)g_savedMechPartIds_v + 0x8))
#undef g_savedMechBooster
#define g_savedMechBooster (*(int *)((u8 *)g_savedMechPartIds_v + 0x10))
#undef g_savedMechChest
#define g_savedMechChest (*(int *)((u8 *)g_savedMechPartIds_v + 0x4))
#undef g_savedMechItem1
#define g_savedMechItem1 (*(int *)((u8 *)g_savedMechSettings_v + 0x4))
#undef g_savedMechItem2
#define g_savedMechItem2 (*(int *)((u8 *)g_savedMechSettings_v + 0x8))
#undef g_savedMechItem3
#define g_savedMechItem3 (*(int *)((u8 *)g_savedMechSettings_v + 0xc))
#undef g_savedMechItem4
#define g_savedMechItem4 (*(int *)((u8 *)g_savedMechSettings_v + 0x10))
#undef g_savedMechItem5
#define g_savedMechItem5 (*(int *)((u8 *)g_savedMechSettings_v + 0x14))
#undef g_savedMechLeg
#define g_savedMechLeg (*(int *)((u8 *)g_savedMechPartIds_v + 0xc))
#undef g_savedMechPartIds
#define g_savedMechPartIds ((int *)g_savedMechPartIds_v)
#undef g_savedMechParts
#define g_savedMechParts (*(int *)((u8 *)g_savedMechPartIds_v + 0x0))
#undef g_savedMechSettings
#define g_savedMechSettings ((int *)g_savedMechSettings_v)
#undef g_savedMechWeapons
#define g_savedMechWeapons (*(int *)((u8 *)g_savedMechSettings_v + 0x0))
#undef g_screen
#define g_screen (*(int *)g_screen_v)
#undef g_screenCentreX
#define g_screenCentreX (*(int *)g_screenCentreX_v)
#undef g_screenCentreY
#define g_screenCentreY (*(int *)g_screenCentreY_v)
#undef g_screenH
#define g_screenH (*(int *)g_screenH_v)
#undef g_screenW
#define g_screenW (*(int *)g_screenW_v)
#undef g_scroll
#define g_scroll (*(float *)g_scroll_v)
#undef g_searchResult
#define g_searchResult (*(int *)g_searchResult_v)
#undef g_secondDialogRects
#define g_secondDialogRects ((int *)g_secondDialogRects_v)
#undef g_sensitivitySlider
#define g_sensitivitySlider (*(int *)((u8 *)g_controlsEdit_v + 0x108))
#undef g_serialProviderGuid
#define g_serialProviderGuid ((u8 *)g_serialProviderGuid_v)
#undef g_serverAddress
#define g_serverAddress ((char *)g_data.g_serverAddress_)
#undef g_serverAddressArg
#define g_serverAddressArg ((char *)g_serverAddressArg_v)
#undef g_serverAnswerIn
#define g_serverAnswerIn (*(int *)g_serverAnswerIn_v)
#undef g_serverConnected
#define g_serverConnected (*(int *)g_serverConnected_v)
#undef g_serverConnectionState
#define g_serverConnectionState (*(int *)g_serverConnectionState_v)
#undef g_serverListCount
#define g_serverListCount (*(int *)g_serverListCount_v)
#undef g_serverNames
#define g_serverNames ((u32 *)g_serverNames_v)
#undef g_serverPing
#define g_serverPing ((int *)g_serverPing_v)
#undef g_serverPingCount
#define g_serverPingCount (*(int *)g_serverPingCount_v)
#undef g_serverPort
#define g_serverPort (*(u16 *)g_serverPort_v)
#undef g_serverReply
#define g_serverReply ((u8 *)g_serverReply_v)
#undef g_serverReplyKind
#define g_serverReplyKind (*(int *)((u8 *)g_serverReply_v + 0x1e))
#undef g_serverSearching
#define g_serverSearching (*(int *)g_serverSearching_v)
#undef g_serverUsed
#define g_serverUsed ((u32 *)g_serverUsed_v)
#undef g_serviceProviderCount
#define g_serviceProviderCount (*(int *)g_serviceProviderCount_v)
#undef g_sessionDesc
#define g_sessionDesc ((u8 *)g_sessionDesc_v)
#undef g_sessionTable
#define g_sessionTable ((u32 *)g_sessionTable_v)
#undef g_settingsPage
#define g_settingsPage (*(int *)g_settingsPage_v)
#undef g_settingsState
#define g_settingsState (*(int *)g_settingsState_v)
#undef g_setupColourDim
#define g_setupColourDim ((u32 *)g_setupColourDim_v)
#undef g_setupColourLit
#define g_setupColourLit ((u32 *)g_setupColourLit_v)
#undef g_setupControlLeft
#define g_setupControlLeft (*(int *)((u8 *)g_setupControlRect_v + 0x0))
#undef g_setupControlRect
#define g_setupControlRect ((int *)g_setupControlRect_v)
#undef g_setupControlRects
#define g_setupControlRects ((int *)g_setupControlRects_v)
#undef g_setupControlRight
#define g_setupControlRight (*(int *)((u8 *)g_setupControlRect_v + 0x8))
#undef g_setupControlTop
#define g_setupControlTop (*(int *)((u8 *)g_setupControlRect_v + 0x4))
#undef g_setupOptionsRect
#define g_setupOptionsRect ((int *)g_setupOptionsRect_v)
#undef g_setupOptionsRects
#define g_setupOptionsRects ((int *)g_setupOptionsRects_v)
#undef g_setupOptionsTop
#define g_setupOptionsTop (*(int *)((u8 *)g_setupOptionsRect_v + 0x4))
#undef g_setupPage
#define g_setupPage (*(int *)g_setupPage_v)
#undef g_setupPanelMoving
#define g_setupPanelMoving (*(int *)g_setupPanelMoving_v)
#undef g_setupPanelPos
#define g_setupPanelPos (*(float *)g_setupPanelPos_v)
#undef g_setupPressed
#define g_setupPressed (*(int *)g_setupPressed_v)
#undef g_setupPressedClock
#define g_setupPressedClock (*(float *)g_setupPressedClock_v)
#undef g_setupResolution
#define g_setupResolution (*(int *)((u8 *)g_graphicEdited_v + 0x0))
#undef g_setupSliderRects
#define g_setupSliderRects ((int *)g_setupSliderRects_v)
#undef g_setupSoundLeft
#define g_setupSoundLeft (*(int *)((u8 *)g_setupSoundRect_v + 0x0))
#undef g_setupSoundRect
#define g_setupSoundRect ((int *)g_setupSoundRect_v)
#undef g_setupSoundRects
#define g_setupSoundRects ((int *)g_setupSoundRects_v)
#undef g_setupSoundRight
#define g_setupSoundRight (*(int *)((u8 *)g_setupSoundRect_v + 0x8))
#undef g_setupTab
#define g_setupTab (*(int *)g_setupTab_v)
#undef g_setupTopOutlines
#define g_setupTopOutlines ((int *)g_setupTopOutlines_v)
#undef g_setupTunnelAlpha
#define g_setupTunnelAlpha (*(float *)g_setupTunnelAlpha_v)
#undef g_setupTunnelDepth
#define g_setupTunnelDepth (*(float *)g_setupTunnelDepth_v)
#undef g_showCmd
#define g_showCmd (*(int *)g_showCmd_v)
#undef g_sinTable
#define g_sinTable ((float *)g_sinTable_v)
#undef g_skirmishColourDim
#define g_skirmishColourDim ((u32 *)g_skirmishColourDim_v)
#undef g_skirmishColourLit
#define g_skirmishColourLit ((u32 *)g_skirmishColourLit_v)
#undef g_skirmishDrawBackground
#define g_skirmishDrawBackground (*(int *)g_skirmishDrawBackground_v)
#undef g_skirmishInfoCount
#define g_skirmishInfoCount (*(int *)g_skirmishInfoCount_v)
#undef g_skirmishRow
#define g_skirmishRow (*(int *)g_skirmishRow_v)
#undef g_skirmishSettingsRects
#define g_skirmishSettingsRects ((int *)g_skirmishSettingsRects_v)
#undef g_slotTakenFlag
#define g_slotTakenFlag (*(int *)g_slotTakenFlag_v)
#undef g_slotTextures
#define g_slotTextures ((int *)g_slotTextures_v)
#undef g_sortBounds
#define g_sortBounds ((int *)g_sortBounds_v)
#undef g_sortState
#define g_sortState ((u8 *)g_sortState_v)
#undef g_sound3D
#define g_sound3D (*(int *)((u8 *)g_soundSettings_v + 0xc))
#undef g_soundBaseVolume
#define g_soundBaseVolume (*(int *)g_soundBaseVolume_v)
#undef g_soundEdited
#define g_soundEdited ((int *)g_soundEdited_v)
#undef g_soundOn
#define g_soundOn (*(int *)g_soundOn_v)
#undef g_soundSettings
#define g_soundSettings ((int *)g_soundSettings_v)
#undef g_soundSwitch1
#define g_soundSwitch1 (*(int *)((u8 *)g_soundSettings_v + 0x8))
#undef g_soundToggle6
#define g_soundToggle6 (*(int *)((u8 *)g_soundEdited_v + 0x8))
#undef g_soundToggle7
#define g_soundToggle7 (*(int *)((u8 *)g_soundEdited_v + 0xc))
#undef g_soundVolume
#define g_soundVolume (*(int *)((u8 *)g_soundSettings_v + 0x0))
#undef g_spiralTextures
#define g_spiralTextures ((int *)g_spiralTextures_v)
#undef g_startTicks
#define g_startTicks (*(u32 *)g_startTicks_v)
#undef g_startedByLauncher
#define g_startedByLauncher (*(int *)g_startedByLauncher_v)
#undef g_startedFromLobby
#define g_startedFromLobby (*(int *)g_startedFromLobby_v)
#undef g_staticTex128x128
#define g_staticTex128x128 (*(u32 *)((u8 *)g_texture128x128_v + 0x0))
#undef g_staticTex128x64
#define g_staticTex128x64 (*(u32 *)((u8 *)g_texture128x64_v + 0x0))
#undef g_staticTex256x128
#define g_staticTex256x128 (*(u32 *)((u8 *)g_texture256x128_v + 0x0))
#undef g_staticTex256x256
#define g_staticTex256x256 (*(u32 *)((u8 *)g_texture256x256_v + 0x0))
#undef g_staticTex256x64
#define g_staticTex256x64 (*(u32 *)((u8 *)g_texture256x64_v + 0x0))
#undef g_staticTex64x64
#define g_staticTex64x64 (*(u32 *)((u8 *)g_texture64x64_v + 0x0))
#undef g_statusLine
#define g_statusLine (g_data.g_statusLine_)
#undef g_storedConnection
#define g_storedConnection (*(void * *)g_storedConnection_v)
#undef g_tan10Table
#define g_tan10Table ((float *)g_tan10Table_v)
#undef g_tanTable
#define g_tanTable ((float *)g_tanTable_v)
#undef g_tcpProviderGuid
#define g_tcpProviderGuid ((u8 *)g_tcpProviderGuid_v)
#undef g_textBottom
#define g_textBottom (*(int *)g_textBottom_v)
#undef g_textCharWidth
#define g_textCharWidth (*(int *)g_textCharWidth_v)
#undef g_textColour
#define g_textColour ((Colour *)g_data.g_textColour_)
#undef g_textColours
#define g_textColours ((Colour *)g_textColours_v)
#undef g_textEndX
#define g_textEndX (*(int *)g_textEndX_v)
#undef g_textEndY
#define g_textEndY (*(int *)g_textEndY_v)
#undef g_textWrapX
#define g_textWrapX (*(int *)g_textWrapX_v)
#undef g_texture128x128
#define g_texture128x128 ((u8 *)g_texture128x128_v)
#undef g_texture128x64
#define g_texture128x64 ((u8 *)g_texture128x64_v)
#undef g_texture256x128
#define g_texture256x128 ((u8 *)g_texture256x128_v)
#undef g_texture256x256
#define g_texture256x256 ((u8 *)g_texture256x256_v)
#undef g_texture256x64
#define g_texture256x64 ((u8 *)g_texture256x64_v)
#undef g_texture64x64
#define g_texture64x64 ((u8 *)g_texture64x64_v)
#undef g_textureManager
#define g_textureManager (*(u32 *)((u8 *)g_textureSets_v + 0x0))
#undef g_textureSetHeight
#define g_textureSetHeight (*(u32 *)((u8 *)g_graphicSettings_v + 0x10))
#undef g_textureSetWidth
#define g_textureSetWidth (*(u32 *)((u8 *)g_graphicSettings_v + 0xc))
#undef g_textureSets
#define g_textureSets ((u32 *)g_textureSets_v)
#undef g_textures
#define g_textures (*(TextureSets * *)g_textures_v)
#undef g_texturesOff
#define g_texturesOff (*(int *)g_texturesOff_v)
#undef g_timeLimit
#define g_timeLimit (*(int *)g_timeLimit_v)
#undef g_timerClocks
#define g_timerClocks ((u32 *)g_timerClocks_v)
#undef g_timerFirstCall
#define g_timerFirstCall (*(int *)g_timerFirstCall_v)
#undef g_timerFrequency
#define g_timerFrequency (*(u64 *)g_timerFrequency_v)
#undef g_timerHigh
#define g_timerHigh (*(u32 *)g_timerHigh_v)
#undef g_timerRepeatCount
#define g_timerRepeatCount (*(int *)g_timerRepeatCount_v)
#undef g_timerShift
#define g_timerShift (*(int *)g_timerShift_v)
#undef g_timerTick
#define g_timerTick (*(double *)g_timerTick_v)
#undef g_titleFrames
#define g_titleFrames (*(int *)g_titleFrames_v)
#undef g_titleLevel
#define g_titleLevel (*(int *)g_titleLevel_v)
#undef g_titleLosses
#define g_titleLosses (*(int *)g_titleLosses_v)
#undef g_titleName
#define g_titleName ((char *)g_data.g_titleName_)
#undef g_titlePoints
#define g_titlePoints (*(int *)g_titlePoints_v)
#undef g_titleRating
#define g_titleRating (*(int *)g_titleRating_v)
#undef g_titleScore
#define g_titleScore (*(int *)g_titleScore_v)
#undef g_titleShown
#define g_titleShown (*(int *)g_titleShown_v)
#undef g_titleWins
#define g_titleWins (*(int *)g_titleWins_v)
#undef g_totalWeight
#define g_totalWeight (*(float *)g_totalWeight_v)
#undef g_tunnelFlyingIn
#define g_tunnelFlyingIn (*(int *)g_tunnelFlyingIn_v)
#undef g_tunnelPulse
#define g_tunnelPulse (*(float *)g_tunnelPulse_v)
#undef g_tunnelPulseStep
#define g_tunnelPulseStep (*(u32 *)g_tunnelPulseStep_v)
#undef g_tunnelRings
#define g_tunnelRings (*(int *)g_tunnelRings_v)
#undef g_tunnelTexture
#define g_tunnelTexture (*(int *)g_tunnelTexture_v)
#undef g_typedArenaName
#define g_typedArenaName (*(char *)((u8 *)g_typedArenaNameText_v + 0x0))
#undef g_typedArenaName4
#define g_typedArenaName4 (*(int *)((u8 *)g_typedArenaNameText_v + 0x4))
#undef g_typedArenaNameText
#define g_typedArenaNameText ((char *)g_typedArenaNameText_v)
#undef g_typedLength
#define g_typedLength (*(int *)g_typedLength_v)
#undef g_typingAccountEmail
#define g_typingAccountEmail (*(int *)g_typingAccountEmail_v)
#undef g_typingAccountName
#define g_typingAccountName (*(int *)g_typingAccountName_v)
#undef g_typingAccountPassword
#define g_typingAccountPassword (*(int *)g_typingAccountPassword_v)
#undef g_typingAccountRepeat
#define g_typingAccountRepeat (*(int *)g_typingAccountRepeat_v)
#undef g_typingArenaName
#define g_typingArenaName (*(int *)g_typingArenaName_v)
#undef g_typingArenaPassword
#define g_typingArenaPassword (*(int *)g_typingArenaPassword_v)
#undef g_typingGameName
#define g_typingGameName (*(int *)g_typingGameName_v)
#undef g_typingGamePassword
#define g_typingGamePassword (*(int *)g_typingGamePassword_v)
#undef g_typingRoomName
#define g_typingRoomName (*(int *)g_typingRoomName_v)
#undef g_typingRoomPassword
#define g_typingRoomPassword (*(int *)g_typingRoomPassword_v)
#undef g_undoDepth
#define g_undoDepth (*(int *)g_undoDepth_v)
#undef g_unlit
#define g_unlit (g_data.g_unlit_)
#undef g_unlockedLevel
#define g_unlockedLevel (*(int *)g_unlockedLevel_v)
#undef g_unusedArmcMoveWord
#define g_unusedArmcMoveWord (*(u32 *)g_unusedArmcMoveWord_v)
#undef g_unusedArmcWord1
#define g_unusedArmcWord1 (*(int *)g_unusedArmcWord1_v)
#undef g_unusedArmcWord2
#define g_unusedArmcWord2 (*(int *)g_unusedArmcWord2_v)
#undef g_unusedArmcWord3
#define g_unusedArmcWord3 (*(int *)g_unusedArmcWord3_v)
#undef g_unusedArmcWord4
#define g_unusedArmcWord4 (*(int *)g_unusedArmcWord4_v)
#undef g_unusedDplayWord1
#define g_unusedDplayWord1 (*(int *)g_unusedDplayWord1_v)
#undef g_unusedDplayWord2
#define g_unusedDplayWord2 (*(int *)g_unusedDplayWord2_v)
#undef g_unusedDplayWord3
#define g_unusedDplayWord3 (*(int *)g_unusedDplayWord3_v)
#undef g_unusedDplayWord4
#define g_unusedDplayWord4 (*(int *)g_unusedDplayWord4_v)
#undef g_unusedInitWord
#define g_unusedInitWord (*(int *)g_unusedInitWord_v)
#undef g_unusedKeyTable2Flags
#define g_unusedKeyTable2Flags (*(u16 *)g_unusedKeyTable2Flags_v)
#undef g_unusedKeyTable2Word0
#define g_unusedKeyTable2Word0 (*(int *)g_unusedKeyTable2Word0_v)
#undef g_unusedKeyTable2Word1
#define g_unusedKeyTable2Word1 (*(int *)g_unusedKeyTable2Word1_v)
#undef g_unusedKeyTable2Word2
#define g_unusedKeyTable2Word2 (*(int *)g_unusedKeyTable2Word2_v)
#undef g_unusedLastWParam
#define g_unusedLastWParam (*(u32 *)g_unusedLastWParam_v)
#undef g_unusedLoginWord
#define g_unusedLoginWord (*(int *)g_unusedLoginWord_v)
#undef g_unusedMainMenuWord
#define g_unusedMainMenuWord (*(int *)g_unusedMainMenuWord_v)
#undef g_unusedMechStat
#define g_unusedMechStat (*(int *)g_unusedMechStat_v)
#undef g_unusedMenuReturnWord
#define g_unusedMenuReturnWord (*(int *)g_unusedMenuReturnWord_v)
#undef g_unusedMissionSaveWord
#define g_unusedMissionSaveWord (*(int *)g_unusedMissionSaveWord_v)
#undef g_unusedNetCloseWord
#define g_unusedNetCloseWord (*(int *)g_unusedNetCloseWord_v)
#undef g_unusedPingWord1
#define g_unusedPingWord1 (*(int *)g_unusedPingWord1_v)
#undef g_unusedPingWord2
#define g_unusedPingWord2 (*(int *)g_unusedPingWord2_v)
#undef g_unusedPlayerRecord26
#define g_unusedPlayerRecord26 (*(u32 *)((u8 *)g_playerName_v + 0x26))
#undef g_unusedPlayerRecord2a
#define g_unusedPlayerRecord2a (*(u32 *)((u8 *)g_playerName_v + 0x2a))
#undef g_unusedPostMatchFlag
#define g_unusedPostMatchFlag (*(int *)g_unusedPostMatchFlag_v)
#undef g_unusedProfileCameraWord
#define g_unusedProfileCameraWord (*(int *)g_unusedProfileCameraWord_v)
#undef g_unusedReplayListWord1
#define g_unusedReplayListWord1 (*(int *)g_unusedReplayListWord1_v)
#undef g_unusedReplayListWord2
#define g_unusedReplayListWord2 (*(int *)g_unusedReplayListWord2_v)
#undef g_unusedRoomListWord
#define g_unusedRoomListWord (*(int *)g_unusedRoomListWord_v)
#undef g_unusedRoomWord
#define g_unusedRoomWord (*(int *)g_unusedRoomWord_v)
#undef g_unusedSessionWord
#define g_unusedSessionWord (*(int *)g_unusedSessionWord_v)
#undef g_unusedStartupWord1
#define g_unusedStartupWord1 (*(int *)g_unusedStartupWord1_v)
#undef g_unusedStartupWord2
#define g_unusedStartupWord2 (*(u32 *)g_unusedStartupWord2_v)
#undef g_unusedStartupWord3
#define g_unusedStartupWord3 (*(int *)g_unusedStartupWord3_v)
#undef g_vecOrigin
#define g_vecOrigin (*(float *)((u8 *)g_vecOriginXyz_v + 0x0))
#undef g_vecOriginXyz
#define g_vecOriginXyz ((float *)g_vecOriginXyz_v)
#undef g_vecUnitX
#define g_vecUnitX ((float *)g_data.g_vecUnitX_)
#undef g_vecUnitY
#define g_vecUnitY ((float *)g_data.g_vecUnitY_)
#undef g_vecUnitZ
#define g_vecUnitZ (*(float *)((u8 *)g_vecUnitZXyz_v + 0x0))
#undef g_vecUnitZXyz
#define g_vecUnitZXyz ((float *)g_vecUnitZXyz_v)
#undef g_vecZero
#define g_vecZero (*(float *)((u8 *)g_vecZeroXyz_v + 0x0))
#undef g_vecZero2
#define g_vecZero2 ((float *)g_data.g_vecZero2_)
#undef g_vecZeroXyz
#define g_vecZeroXyz ((float *)g_vecZeroXyz_v)
#undef g_videoDepth
#define g_videoDepth (*(int *)((u8 *)g_graphicSettings_v + 0x4))
#undef g_videoMode
#define g_videoMode (*(u32 *)((u8 *)g_graphicSettings_v + 0x0))
#undef g_viewAngle
#define g_viewAngle (*(float *)g_viewAngle_v)
#undef g_viewAspect
#define g_viewAspect (*(float *)g_viewAspect_v)
#undef g_viewFar
#define g_viewFar (*(float *)g_viewFar_v)
#undef g_viewFov
#define g_viewFov (*(float *)g_viewFov_v)
#undef g_viewNear
#define g_viewNear (*(float *)g_viewNear_v)
#undef g_viewedPartIndex
#define g_viewedPartIndex (*(int *)((u8 *)g_partRecords_v + 0x348))
#undef g_viewedPartKind
#define g_viewedPartKind (*(int *)((u8 *)g_partRecords_v + 0x344))
#undef g_vkTable
#define g_vkTable ((int *)g_vkTable_v)
#undef g_volumeSetting
#define g_volumeSetting (*(int *)((u8 *)g_soundEdited_v + 0x0))
#undef g_watchChatOpen
#define g_watchChatOpen (*(int *)g_watchChatOpen_v)
#undef g_watchedSlot
#define g_watchedSlot (*(u8 *)g_watchedSlot_v)
#undef g_weaponCount
#define g_weaponCount (*(int *)g_weaponCount_v)
#undef g_weaponListTable
#define g_weaponListTable ((int *)g_weaponListTable_v)
#undef g_writeMatchLog
#define g_writeMatchLog (*(int *)g_writeMatchLog_v)
#undef k_0_00390625f
#define k_0_00390625f (g_rdata.k_0_00390625f_)
#undef k_0_01f
#define k_0_01f (g_rdata.k_0_01f_)
#undef k_0_25f
#define k_0_25f (g_rdata.k_0_25f_)
#undef k_0_3
#define k_0_3 (g_rdata.k_0_3_)
#undef k_0_95f
#define k_0_95f (g_rdata.k_0_95f_)
#undef k_1
#define k_1 (g_rdata.k_1_)
#undef k_100
#define k_100 (g_rdata.k_100_)
#undef k_100f
#define k_100f (g_rdata.k_100f_)
#undef k_10f
#define k_10f (g_rdata.k_10f_)
#undef k_120f
#define k_120f (g_rdata.k_120f_)
#undef k_1800f
#define k_1800f (g_rdata.k_1800f_)
#undef k_1_4
#define k_1_4 (g_rdata.k_1_4_)
#undef k_1_40625f
#define k_1_40625f (g_rdata.k_1_40625f_)
#undef k_1f
#define k_1f (g_rdata.k_1f_)
#undef k_2000000
#define k_2000000 (g_rdata.k_2000000_)
#undef k_2000f
#define k_2000f (g_rdata.k_2000f_)
#undef k_200f
#define k_200f (g_rdata.k_200f_)
#undef k_20f
#define k_20f (g_rdata.k_20f_)
#undef k_23
#define k_23 (g_rdata.k_23_)
#undef k_25
#define k_25 (g_rdata.k_25_)
#undef k_38f
#define k_38f (g_rdata.k_38f_)
#undef k_3_6f
#define k_3_6f (g_rdata.k_3_6f_)
#undef k_45f
#define k_45f (g_rdata.k_45f_)
#undef k_49f
#define k_49f (g_rdata.k_49f_)
#undef k_500f
#define k_500f (g_rdata.k_500f_)
#undef k_50f
#define k_50f (g_rdata.k_50f_)
#undef k_60
#define k_60 (g_rdata.k_60_)
#undef k_60f
#define k_60f (g_rdata.k_60f_)
#undef k_69_9
#define k_69_9 (g_rdata.k_69_9_)
#undef k_8
#define k_8 (g_rdata.k_8_)
#undef k_90f
#define k_90f (g_rdata.k_90f_)
#undef k_armcDistance
#define k_armcDistance (g_rdata.k_armcDistance_)
#undef k_armcDistanceRoom
#define k_armcDistanceRoom (g_rdata.k_armcDistanceRoom_)
#undef k_cameraSnapDistance
#define k_cameraSnapDistance (g_rdata.k_cameraSnapDistance_)
#undef k_clockRate
#define k_clockRate (g_rdata.k_clockRate_)
#undef k_m0_5f
#define k_m0_5f (g_rdata.k_m0_5f_)
#undef k_m100f
#define k_m100f (g_rdata.k_m100f_)
#undef k_m1100f
#define k_m1100f (g_rdata.k_m1100f_)
#undef k_m50f
#define k_m50f (g_rdata.k_m50f_)
#undef k_m549_99f
#define k_m549_99f (g_rdata.k_m549_99f_)
#undef k_m549_9f
#define k_m549_9f (g_rdata.k_m549_9f_)
#undef k_m549f
#define k_m549f (g_rdata.k_m549f_)
#undef k_m890f
#define k_m890f (g_rdata.k_m890f_)
#undef k_pi
#define k_pi (g_rdata.k_pi_)
#undef k_setupPanelTarget
#define k_setupPanelTarget (g_rdata.k_setupPanelTarget_)
#undef k_tenth
#define k_tenth (g_rdata.k_tenth_)
#undef k_tenthsToDegrees
#define k_tenthsToDegrees (g_rdata.k_tenthsToDegrees_)
/* names that are no member of their own type: at IMG()'s place */
#undef k_setupPanelEnd
#define k_setupPanelEnd (*(double *)IMG(0x4a9440))
#undef k_degToRad
#define k_degToRad (*(double *)IMG(0x4aa290))
#undef k_tenthDegreeRad
#define k_tenthDegreeRad (*(double *)IMG(0x4aa298))
#undef k_clockRate3
#define k_clockRate3 (*(float *)IMG(0x4aa498))
#undef k_oneOver180
#define k_oneOver180 (*(double *)IMG(0x4a9540))
#undef k_3600f
#define k_3600f (*(float *)IMG(0x4a94c8))
#undef k_10000f
#define k_10000f (*(float *)IMG(0x4a9708))
#undef k_0f
#define k_0f (*(float *)IMG(0x4a93e8))
#undef k_2f
#define k_2f (*(float *)IMG(0x4a93fc))
#undef k_0_5f
#define k_0_5f (*(float *)IMG(0x4a942c))
#undef k_360f
#define k_360f (*(float *)IMG(0x4a9460))
#undef k_m1f
#define k_m1f (*(float *)IMG(0x4a9474))
#undef k_4f
#define k_4f (*(float *)IMG(0x4a947c))
#undef k_550f
#define k_550f (*(float *)IMG(0x4a9498))
#undef k_m2f
#define k_m2f (*(float *)IMG(0x4a94a8))
#undef k_0_01
#define k_0_01 (*(double *)IMG(0x4a94c0))
#undef k_0_9f
#define k_0_9f (*(float *)IMG(0x4a9508))
#undef k_m1000f
#define k_m1000f (*(float *)IMG(0x4a95c0))
#undef k_27_7778f
#define k_27_7778f (*(float *)IMG(0x4a9750))
#undef k_1em8f
#define k_1em8f (*(float *)IMG(0x4aa268))
#undef k_0_0078125f
#define k_0_0078125f (*(float *)IMG(0x4aa420))
#undef k_1em8
#define k_1em8 (*(double *)IMG(0x4aa458))
#undef g_imp_wsprintfA
#define g_imp_wsprintfA (*(void * *)IMG(0x4a92f0))
#undef k_5f
#define k_5f (*(float *)IMG(0x4a93d0))
#undef k_0_07f
#define k_0_07f (*(float *)IMG(0x4a946c))
#undef k_1000000f
#define k_1000000f (*(float *)IMG(0x4a94ec))
#undef k_0_2f
#define k_0_2f (*(float *)IMG(0x4a94f8))
#undef k_640f
#define k_640f (*(float *)IMG(0x4a9510))
#undef k_3f
#define k_3f (*(float *)IMG(0x4a9534))
#undef k_0_28125f
#define k_0_28125f (*(float *)IMG(0x4a9564))
#undef k_890f
#define k_890f (*(float *)IMG(0x4a972c))
#undef k_27
#define k_27 (*(double *)IMG(0x4aa408))
#undef g_scene
#define g_scene (*(Scene * *)IMG(0x9087b4))
#undef g_white
#define g_white (*(u32 *)IMG(0xa1f23c))
