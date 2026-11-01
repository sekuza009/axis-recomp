/* layout_names.h (tools/mkdatasrc.py): in AxisRC.exe (AXIS_DIRECT) the named globals that are members of
   g_rdata / g_data (src/data/layout.h) as those members; the others stay GAME_VAR (src/globals.h), which IMG()
   routes to the same place */
#pragma once
#include "layout.h"
extern struct GameRdata g_rdata;
extern struct GameData g_data;
#include "split.h"   /* (the variables split out of g_data) */
#undef g_accountClan
#define g_accountClan (g_data.g_accountClan_)
#undef g_accountEmail
#define g_accountEmail ((char *)g_data.g_accountEmail_)
#undef g_accountName
#define g_accountName ((char *)g_data.g_accountName_)
#undef g_accountNotice
#define g_accountNotice (g_data.g_accountNotice_)
#undef g_accountOldPassword
#define g_accountOldPassword ((char *)g_data.g_accountOldPassword_)
#undef g_accountPacket
#define g_accountPacket (g_data.g_accountPacket_)
#undef g_accountPanelBottom
#define g_accountPanelBottom (g_data.g_accountPanelBottom_)
#undef g_accountPanelLeft
#define g_accountPanelLeft (g_data.g_accountPanelLeft_)
#undef g_accountPanelRight
#define g_accountPanelRight (g_data.g_accountPanelRight_)
#undef g_accountPanelTop
#define g_accountPanelTop (g_data.g_accountPanelTop_)
#undef g_accountPassword
#define g_accountPassword ((char *)g_data.g_accountPassword_)
#undef g_accountPasswordRepeat
#define g_accountPasswordRepeat ((char *)g_data.g_accountPasswordRepeat_)
#undef g_arenaBright
#define g_arenaBright ((u32 *)g_data.g_arenaBright_)
#undef g_arenaConfirming
#define g_arenaConfirming (*(int *)g_arenaConfirming_v)
#undef g_arenaCorporation
#define g_arenaCorporation (g_data.g_arenaCorporation_)
#undef g_arenaCustomize
#define g_arenaCustomize (g_data.g_arenaCustomize_)
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
#define g_arenaFragLimit (g_data.g_arenaFragLimit_)
#undef g_arenaFragLimitTyped
#define g_arenaFragLimitTyped (g_data.g_arenaFragLimitTyped_)
#undef g_arenaFull
#define g_arenaFull (*(int *)g_arenaFull_v)
#undef g_arenaGameListBottom
#define g_arenaGameListBottom (g_data.g_arenaGameListBottom_)
#undef g_arenaGameListLeft
#define g_arenaGameListLeft (g_data.g_arenaGameListLeft_)
#undef g_arenaGameListRight
#define g_arenaGameListRight (g_data.g_arenaGameListRight_)
#undef g_arenaGameListTop
#define g_arenaGameListTop (g_data.g_arenaGameListTop_)
#undef g_arenaGameSetUp
#define g_arenaGameSetUp (g_data.g_arenaGameSetUp_)
#undef g_arenaGameType
#define g_arenaGameType (g_data.g_arenaGameType_)
#undef g_arenaHaveList
#define g_arenaHaveList (g_data.g_arenaHaveList_)
#undef g_arenaInfoPacket
#define g_arenaInfoPacket (g_data.g_arenaInfoPacket_)
#undef g_arenaJoinPending
#define g_arenaJoinPending (*(int *)g_arenaJoinPending_v)
#undef g_arenaJoinRow
#define g_arenaJoinRow (*(int *)g_arenaJoinRow_v)
#undef g_arenaJoinTimer
#define g_arenaJoinTimer (*(u32 *)g_arenaJoinTimer_v)
#undef g_arenaJoinWaiting
#define g_arenaJoinWaiting (g_data.g_arenaJoinWaiting_)
#undef g_arenaJoining
#define g_arenaJoining (g_data.g_arenaJoining_)
#undef g_arenaKeptCamX
#define g_arenaKeptCamX (*(float *)g_arenaKeptCamX_v)
#undef g_arenaKeptCamY
#define g_arenaKeptCamY (*(int *)g_arenaKeptCamY_v)
#undef g_arenaKeptCamZ
#define g_arenaKeptCamZ (*(int *)g_arenaKeptCamZ_v)
#undef g_arenaKeptLookX
#define g_arenaKeptLookX (g_data.g_arenaKeptLookX_)
#undef g_arenaKeptLookY
#define g_arenaKeptLookY (g_data.g_arenaKeptLookY_)
#undef g_arenaKeptLookZ
#define g_arenaKeptLookZ (g_data.g_arenaKeptLookZ_)
#undef g_arenaLeaving
#define g_arenaLeaving (g_data.g_arenaLeaving_)
#undef g_arenaListClickArmed
#define g_arenaListClickArmed (*(int *)g_arenaListClickArmed_v)
#undef g_arenaListFull
#define g_arenaListFull (g_data.g_arenaListFull_)
#undef g_arenaListRefreshTimer
#define g_arenaListRefreshTimer (g_data.g_arenaListRefreshTimer_)
#undef g_arenaLobbyMode
#define g_arenaLobbyMode (g_data.g_arenaLobbyMode_)
#undef g_arenaLobbyState
#define g_arenaLobbyState (g_data.g_arenaLobbyState_)
#undef g_arenaMap
#define g_arenaMap (g_data.g_arenaMap_)
#undef g_arenaMapCount
#define g_arenaMapCount (g_data.g_arenaMapCount_)
#undef g_arenaMessageText
#define g_arenaMessageText (g_data.g_arenaMessageText_)
#undef g_arenaMessageText4
#define g_arenaMessageText4 (g_data.g_arenaMessageText4_)
#undef g_arenaName
#define g_arenaName ((char *)g_data.g_arenaName_)
#undef g_arenaNameDialogBottom
#define g_arenaNameDialogBottom (g_data.g_arenaNameDialogBottom_)
#undef g_arenaNameDialogLeft
#define g_arenaNameDialogLeft (g_data.g_arenaNameDialogLeft_)
#undef g_arenaNameDialogRight
#define g_arenaNameDialogRight (g_data.g_arenaNameDialogRight_)
#undef g_arenaNameDialogTop
#define g_arenaNameDialogTop (g_data.g_arenaNameDialogTop_)
#undef g_arenaNameSum
#define g_arenaNameSum (g_data.g_arenaNameSum_)
#undef g_arenaPacket
#define g_arenaPacket (g_data.g_arenaPacket_)
#undef g_arenaPanelBrightness
#define g_arenaPanelBrightness (g_data.g_arenaPanelBrightness_)
#undef g_arenaPlayers
#define g_arenaPlayers (g_data.g_arenaPlayers_)
#undef g_arenaSearchClock
#define g_arenaSearchClock (g_data.g_arenaSearchClock_)
#undef g_arenaSearchStarted
#define g_arenaSearchStarted (g_data.g_arenaSearchStarted_)
#undef g_arenaSearchTicks
#define g_arenaSearchTicks (g_data.g_arenaSearchTicks_)
#undef g_arenaSessionOpen
#define g_arenaSessionOpen (g_data.g_arenaSessionOpen_)
#undef g_arenaSex
#define g_arenaSex (g_data.g_arenaSex_)
#undef g_arenaTimeLimit
#define g_arenaTimeLimit (g_data.g_arenaTimeLimit_)
#undef g_arenaTimeLimitTyped
#define g_arenaTimeLimitTyped (g_data.g_arenaTimeLimitTyped_)
#undef g_arenaTunnelDepth
#define g_arenaTunnelDepth (*(u32 *)g_arenaTunnelDepth_v)
#undef g_argCount
#define g_argCount (*(int *)g_argCount_v)
#undef g_armcBuildTexture
#define g_armcBuildTexture (g_data.g_armcBuildTexture_)
#undef g_armcCamDistance
#define g_armcCamDistance (g_data.g_armcCamDistance_)
#undef g_armcCamHeight
#define g_armcCamHeight (g_data.g_armcCamHeight_)
#undef g_armcChanged
#define g_armcChanged (*(int *)g_armcChanged_v)
#undef g_armcColours
#define g_armcColours ((float *)g_data.g_armcColours_)
#undef g_armcCursor
#define g_armcCursor (g_data.g_armcCursor_)
#undef g_armcEnterStep
#define g_armcEnterStep (*(int *)g_armcEnterStep_v)
#undef g_armcEnterStepF
#define g_armcEnterStepF (g_data.g_armcEnterStepF_)
#undef g_armcEntered
#define g_armcEntered (*(int *)g_armcEntered_v)
#undef g_armcFrom
#define g_armcFrom (g_data.g_armcFrom_)
#undef g_armcLastPart
#define g_armcLastPart (g_data.g_armcLastPart_)
#undef g_armcLeaving
#define g_armcLeaving (g_data.g_armcLeaving_)
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
#define g_armcPanelDepth (g_data.g_armcPanelDepth_)
#undef g_armcPreview
#define g_armcPreview (g_data.g_armcPreview_)
#undef g_armcSessionMade
#define g_armcSessionMade (*(int *)g_armcSessionMade_v)
#undef g_armcSliderLeft
#define g_armcSliderLeft (g_data.g_armcSliderLeft_)
#undef g_armcSlot
#define g_armcSlot (*(int *)g_armcSlot_v)
#undef g_armcSpin
#define g_armcSpin (g_data.g_armcSpin_)
#undef g_armcState
#define g_armcState (g_data.g_armcState_)
#undef g_armcStatsPanelBottom
#define g_armcStatsPanelBottom (g_data.g_armcStatsPanelBottom_)
#undef g_armcStatsPanelLeft
#define g_armcStatsPanelLeft (g_data.g_armcStatsPanelLeft_)
#undef g_armcStatsPanelTop
#define g_armcStatsPanelTop (g_data.g_armcStatsPanelTop_)
#undef g_armcUnusedFlag
#define g_armcUnusedFlag (g_data.g_armcUnusedFlag_)
#undef g_armcValue
#define g_armcValue (g_data.g_armcValue_)
#undef g_armcViewPoint0Y
#define g_armcViewPoint0Y (g_data.g_armcViewPoint0Y_)
#undef g_armcViewPoint3Y
#define g_armcViewPoint3Y (g_data.g_armcViewPoint3Y_)
#undef g_armcViewPoint5Y
#define g_armcViewPoint5Y (g_data.g_armcViewPoint5Y_)
#undef g_armcZoom
#define g_armcZoom (*(float *)g_armcZoom_v)
#undef g_armsFcsLevel
#define g_armsFcsLevel (g_data.g_armsFcsLevel_)
#undef g_armsWeight
#define g_armsWeight (g_data.g_armsWeight_)
#undef g_bestLevelNet
#define g_bestLevelNet (*(int *)g_bestLevelNet_v)
#undef g_bestProgressSolo
#define g_bestProgressSolo (g_data.g_bestProgressSolo_)
#undef g_bindPage
#define g_bindPage (*(int *)g_bindPage_v)
#undef g_bindRow
#define g_bindRow (*(int *)g_bindRow_v)
#undef g_bindWaiting
#define g_bindWaiting (*(int *)g_bindWaiting_v)
#undef g_bitStream
#define g_bitStream (*(const u8 * *)g_bitStream_v)
#undef g_boosterActiveTime
#define g_boosterActiveTime (g_data.g_boosterActiveTime_)
#undef g_boosterNormalSpeed
#define g_boosterNormalSpeed (g_data.g_boosterNormalSpeed_)
#undef g_boosterRechargeDelay
#define g_boosterRechargeDelay (g_data.g_boosterRechargeDelay_)
#undef g_boosterRechargeTime
#define g_boosterRechargeTime (g_data.g_boosterRechargeTime_)
#undef g_boosterThrustType
#define g_boosterThrustType (*(int *)g_boosterThrustType_v)
#undef g_boosterWeight
#define g_boosterWeight (g_data.g_boosterWeight_)
#undef g_briefingBottom
#define g_briefingBottom (g_data.g_briefingBottom_)
#undef g_briefingClock
#define g_briefingClock (g_data.g_briefingClock_)
#undef g_briefingDone
#define g_briefingDone (*(int *)g_briefingDone_v)
#undef g_briefingEnd
#define g_briefingEnd (g_data.g_briefingEnd_)
#undef g_briefingRight
#define g_briefingRight (g_data.g_briefingRight_)
#undef g_briefingShown
#define g_briefingShown (g_data.g_briefingShown_)
#undef g_briefingSkipped
#define g_briefingSkipped (*(int *)g_briefingSkipped_v)
#undef g_briefingSource
#define g_briefingSource (*(u8 * *)g_briefingSource_v)
#undef g_briefingStart
#define g_briefingStart (*(int *)g_briefingStart_v)
#undef g_briefingText
#define g_briefingText ((char *)g_briefingText_v)
#undef g_briefingX
#define g_briefingX (g_data.g_briefingX_)
#undef g_briefingY
#define g_briefingY (g_data.g_briefingY_)
#undef g_buttonTexture
#define g_buttonTexture (g_data.g_buttonTexture_)
#undef g_camAim0X
#define g_camAim0X (g_data.g_camAim0X_)
#undef g_camAim0Y
#define g_camAim0Y (g_data.g_camAim0Y_)
#undef g_camAim0Z
#define g_camAim0Z (g_data.g_camAim0Z_)
#undef g_camAim1X
#define g_camAim1X (g_data.g_camAim1X_)
#undef g_camAim1Y
#define g_camAim1Y (g_data.g_camAim1Y_)
#undef g_camAim1Z
#define g_camAim1Z (g_data.g_camAim1Z_)
#undef g_camAim2X
#define g_camAim2X (g_data.g_camAim2X_)
#undef g_camAim2Y
#define g_camAim2Y (g_data.g_camAim2Y_)
#undef g_camAim2Z
#define g_camAim2Z (g_data.g_camAim2Z_)
#undef g_camPoint0X
#define g_camPoint0X (g_data.g_camPoint0X_)
#undef g_camPoint0Y
#define g_camPoint0Y (g_data.g_camPoint0Y_)
#undef g_camPoint0Z
#define g_camPoint0Z (g_data.g_camPoint0Z_)
#undef g_camPoint1X
#define g_camPoint1X (g_data.g_camPoint1X_)
#undef g_camPoint1Z
#define g_camPoint1Z (g_data.g_camPoint1Z_)
#undef g_camPoint2X
#define g_camPoint2X (g_data.g_camPoint2X_)
#undef g_camPoint2Y
#define g_camPoint2Y (g_data.g_camPoint2Y_)
#undef g_camPoint2Z
#define g_camPoint2Z (g_data.g_camPoint2Z_)
#undef g_catalogueFile
#define g_catalogueFile (*(const char * *)g_catalogueFile_v)
#undef g_cfgPlayerName
#define g_cfgPlayerName ((char *)g_data.g_cfgPlayerName_)
#undef g_cfgSimpleMenu
#define g_cfgSimpleMenu (g_data.g_cfgSimpleMenu_)
#undef g_characterTexture
#define g_characterTexture (g_data.g_characterTexture_)
#undef g_chatEditLength
#define g_chatEditLength (g_data.g_chatEditLength_)
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
#undef g_chestMaxArmor
#define g_chestMaxArmor (*(int *)g_chestMaxArmor_v)
#undef g_chestMaxShield
#define g_chestMaxShield (*(int *)g_chestMaxShield_v)
#undef g_chestWeightLimit
#define g_chestWeightLimit (*(float *)g_chestWeightLimit_v)
#undef g_chosenGameMode
#define g_chosenGameMode (g_data.g_chosenGameMode_)
#undef g_chosenPilot
#define g_chosenPilot (*(int *)g_chosenPilot_v)
#undef g_clockCheckClosed
#define g_clockCheckClosed (*(int *)g_clockCheckClosed_v)
#undef g_clockCheckSeconds
#define g_clockCheckSeconds (g_data.g_clockCheckSeconds_)
#undef g_clockCheckTick
#define g_clockCheckTick (*(u32 *)g_clockCheckTick_v)
#undef g_clockCheckTickSeconds
#define g_clockCheckTickSeconds (*(u32 *)g_clockCheckTickSeconds_v)
#undef g_clockLastTime
#define g_clockLastTime ((u16 *)g_data.g_clockLastTime_)
#undef g_clockNow
#define g_clockNow (g_data.g_clockNow_)
#undef g_clockNowTime
#define g_clockNowTime ((u16 *)g_data.g_clockNowTime_)
#undef g_cmdSecret
#define g_cmdSecret (g_data.g_cmdSecret_)
#undef g_cmdTimeLimit
#define g_cmdTimeLimit (g_data.g_cmdTimeLimit_)
#undef g_colourChanged
#define g_colourChanged (*(int *)g_colourChanged_v)
#undef g_colourMaskRed
#define g_colourMaskRed (g_data.g_colourMaskRed_)
#undef g_coloursChanged
#define g_coloursChanged (*(int *)g_coloursChanged_v)
#undef g_componentDatPath
#define g_componentDatPath (*(u32 *)g_componentDatPath_v)
#undef g_connectStep
#define g_connectStep (g_data.g_connectStep_)
#undef g_connectionAwaited
#define g_connectionAwaited (g_data.g_connectionAwaited_)
#undef g_connectionCopy
#define g_connectionCopy (*(void * *)g_connectionCopy_v)
#undef g_connectionKind
#define g_connectionKind (*(int *)g_connectionKind_v)
#undef g_convertHangul
#define g_convertHangul (*(int *)g_convertHangul_v)
#undef g_cosTable
#define g_cosTable ((float *)g_cosTable_v)
#undef g_createQuitDialog
#define g_createQuitDialog (g_data.g_createQuitDialog_)
#undef g_crosshair
#define g_crosshair (g_data.g_crosshair_)
#undef g_crosshairSetting
#define g_crosshairSetting (g_data.g_crosshairSetting_)
#undef g_crosshairTexture
#define g_crosshairTexture (*(int *)g_crosshairTexture_v)
#undef g_currentProfile
#define g_currentProfile (g_data.g_currentProfile_)
#undef g_currentStageName
#define g_currentStageName (*(int *)g_currentStageName_v)
#undef g_cursorBlinkTimer
#define g_cursorBlinkTimer (g_data.g_cursorBlinkTimer_)
#undef g_cursorPos
#define g_cursorPos (g_data.g_cursorPos_)
#undef g_cursorPosY
#define g_cursorPosY (g_data.g_cursorPosY_)
#undef g_dataDir
#define g_dataDir ((char *)g_data.g_dataDir_)
#undef g_debugValue
#define g_debugValue (*(int *)g_debugValue_v)
#undef g_defaultColour
#define g_defaultColour (g_data.g_defaultColour_)
#undef g_desktopDC
#define g_desktopDC (*(void * *)g_desktopDC_v)
#undef g_desktopDepth
#define g_desktopDepth (*(int *)g_desktopDepth_v)
#undef g_desktopHeight
#define g_desktopHeight (g_data.g_desktopHeight_)
#undef g_desktopWidth
#define g_desktopWidth (*(int *)g_desktopWidth_v)
#undef g_dialogFrameTexture
#define g_dialogFrameTexture (g_data.g_dialogFrameTexture_)
#undef g_dik1
#define g_dik1 (g_data.g_dik1_)
#undef g_dik2
#define g_dik2 (g_data.g_dik2_)
#undef g_dik3
#define g_dik3 (g_data.g_dik3_)
#undef g_dik4
#define g_dik4 (g_data.g_dik4_)
#undef g_dikA
#define g_dikA (g_data.g_dikA_)
#undef g_dikC
#define g_dikC (g_data.g_dikC_)
#undef g_dikD
#define g_dikD (g_data.g_dikD_)
#undef g_dikDelete
#define g_dikDelete (g_data.g_dikDelete_)
#undef g_dikDown
#define g_dikDown (*(int *)g_dikDown_v)
#undef g_dikEnter
#define g_dikEnter (g_data.g_dikEnter_)
#undef g_dikEscape
#define g_dikEscape (g_data.g_dikEscape_)
#undef g_dikEscape_2
#define g_dikEscape_2 (g_data.g_dikEscape_2_)
#undef g_dikF11
#define g_dikF11 (*(int *)g_dikF11_v)
#undef g_dikG
#define g_dikG (g_data.g_dikG_)
#undef g_dikI
#define g_dikI (g_data.g_dikI_)
#undef g_dikJ
#define g_dikJ (g_data.g_dikJ_)
#undef g_dikL
#define g_dikL (g_data.g_dikL_)
#undef g_dikLAlt
#define g_dikLAlt (g_data.g_dikLAlt_)
#undef g_dikLCtrl
#define g_dikLCtrl (g_data.g_dikLCtrl_)
#undef g_dikLShift
#define g_dikLShift (g_data.g_dikLShift_)
#undef g_dikLeft
#define g_dikLeft (*(int *)g_dikLeft_v)
#undef g_dikM
#define g_dikM (g_data.g_dikM_)
#undef g_dikMouse1
#define g_dikMouse1 (g_data.g_dikMouse1_)
#undef g_dikMouse2
#define g_dikMouse2 (g_data.g_dikMouse2_)
#undef g_dikN
#define g_dikN (g_data.g_dikN_)
#undef g_dikNone
#define g_dikNone (g_data.g_dikNone_)
#undef g_dikO
#define g_dikO (g_data.g_dikO_)
#undef g_dikP
#define g_dikP (g_data.g_dikP_)
#undef g_dikPageUp
#define g_dikPageUp (g_data.g_dikPageUp_)
#undef g_dikR
#define g_dikR (g_data.g_dikR_)
#undef g_dikRAlt
#define g_dikRAlt (g_data.g_dikRAlt_)
#undef g_dikRCtrl
#define g_dikRCtrl (*(int *)g_dikRCtrl_v)
#undef g_dikRShift
#define g_dikRShift (g_data.g_dikRShift_)
#undef g_dikRight
#define g_dikRight (*(int *)g_dikRight_v)
#undef g_dikS
#define g_dikS (g_data.g_dikS_)
#undef g_dikSpace
#define g_dikSpace (g_data.g_dikSpace_)
#undef g_dikT
#define g_dikT (g_data.g_dikT_)
#undef g_dikTab
#define g_dikTab (g_data.g_dikTab_)
#undef g_dikUp
#define g_dikUp (g_data.g_dikUp_)
#undef g_dikW
#define g_dikW (g_data.g_dikW_)
#undef g_dikWheelDown
#define g_dikWheelDown (*(int *)g_dikWheelDown_v)
#undef g_dikWheelUp
#define g_dikWheelUp (g_data.g_dikWheelUp_)
#undef g_dikX
#define g_dikX (g_data.g_dikX_)
#undef g_dikZ_2
#define g_dikZ_2 (g_data.g_dikZ_2_)
#undef g_directInputMade
#define g_directInputMade (*(int *)g_directInputMade_v)
#undef g_directSound
#define g_directSound (*(void * *)g_directSound_v)
#undef g_displayModeChanged
#define g_displayModeChanged (*(u8 *)g_displayModeChanged_v)
#undef g_displayModeLeft
#define g_displayModeLeft (*(u8 *)g_displayModeLeft_v)
#undef g_dpMaxBufferSize
#define g_dpMaxBufferSize (g_data.g_dpMaxBufferSize_)
#undef g_dpMaxQueueSize
#define g_dpMaxQueueSize (g_data.g_dpMaxQueueSize_)
#undef g_dpTimeout
#define g_dpTimeout (g_data.g_dpTimeout_)
#undef g_dplay
#define g_dplay (*(void * *)g_dplay_v)
#undef g_dplayLobby
#define g_dplayLobby (g_data.g_dplayLobby_)
#undef g_dplaySessionCount
#define g_dplaySessionCount (*(int *)g_dplaySessionCount_v)
#undef g_dplaySessionList
#define g_dplaySessionList (g_data.g_dplaySessionList_)
#undef g_editOldProc
#define g_editOldProc (g_data.g_editOldProc_)
#undef g_editingAccountPassword
#define g_editingAccountPassword (g_data.g_editingAccountPassword_)
#undef g_editingArenaMessage
#define g_editingArenaMessage (*(int *)g_editingArenaMessage_v)
#undef g_editingEmail
#define g_editingEmail (g_data.g_editingEmail_)
#undef g_editingNewArenaFragLimit
#define g_editingNewArenaFragLimit (g_data.g_editingNewArenaFragLimit_)
#undef g_editingNewArenaName
#define g_editingNewArenaName (g_data.g_editingNewArenaName_)
#undef g_editingNewArenaTimeLimit
#define g_editingNewArenaTimeLimit (g_data.g_editingNewArenaTimeLimit_)
#undef g_editingOldPassword
#define g_editingOldPassword (g_data.g_editingOldPassword_)
#undef g_editingPasswordRepeat
#define g_editingPasswordRepeat (g_data.g_editingPasswordRepeat_)
#undef g_editingRoomName
#define g_editingRoomName (g_data.g_editingRoomName_)
#undef g_editingRoomPassword
#define g_editingRoomPassword (g_data.g_editingRoomPassword_)
#undef g_effectsVolume
#define g_effectsVolume (g_data.g_effectsVolume_)
#undef g_emptyItemSlot0
#define g_emptyItemSlot0 (g_data.g_emptyItemSlot0_)
#undef g_enteringMenus
#define g_enteringMenus (*(int *)g_enteringMenus_v)
#undef g_errorCleanupHook
#define g_errorCleanupHook (*(int *)g_errorCleanupHook_v)
#undef g_errorLogging
#define g_errorLogging (*(int *)g_errorLogging_v)
#undef g_excludedKey
#define g_excludedKey (*(int *)g_excludedKey_v)
#undef g_fieldTabKey
#define g_fieldTabKey (*(int *)g_fieldTabKey_v)
#undef g_fileList
#define g_fileList ((u8 *)g_fileList_v)
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
#define g_fragLimit (g_data.g_fragLimit_)
#undef g_frameCounter40
#define g_frameCounter40 (*(int *)g_frameCounter40_v)
#undef g_frameRate
#define g_frameRate (*(double *)g_frameRate_v)
#undef g_freeCamHeight
#define g_freeCamHeight (*(float *)g_freeCamHeight_v)
#undef g_fullScreen
#define g_fullScreen (*(int *)g_fullScreen_v)
#undef g_gameCount
#define g_gameCount (g_data.g_gameCount_)
#undef g_gameList
#define g_gameList ((u8 *)g_data.g_gameList_)
#undef g_gameListClickArmed
#define g_gameListClickArmed (g_data.g_gameListClickArmed_)
#undef g_gameListClickTimer
#define g_gameListClickTimer (*(float *)g_gameListClickTimer_v)
#undef g_gameListJoinClicked
#define g_gameListJoinClicked (g_data.g_gameListJoinClicked_)
#undef g_gameListLoaded
#define g_gameListLoaded (g_data.g_gameListLoaded_)
#undef g_gameListTop
#define g_gameListTop (g_data.g_gameListTop_)
#undef g_gameRunning
#define g_gameRunning (*(int *)g_gameRunning_v)
#undef g_gameServerAnswer
#define g_gameServerAnswer (g_data.g_gameServerAnswer_)
#undef g_gameServerAnswer15
#define g_gameServerAnswer15 (g_data.g_gameServerAnswer15_)
#undef g_gameServerPending
#define g_gameServerPending (g_data.g_gameServerPending_)
#undef g_gameServerReplyKind
#define g_gameServerReplyKind (*(u32 *)g_gameServerReplyKind_v)
#undef g_gameServerSocket
#define g_gameServerSocket (g_data.g_gameServerSocket_)
#undef g_gameServerState
#define g_gameServerState (g_data.g_gameServerState_)
#undef g_gameServerStatus
#define g_gameServerStatus (g_data.g_gameServerStatus_)
#undef g_glCachedState
#define g_glCachedState (*(int *)g_glCachedState_v)
#undef g_glColourBits
#define g_glColourBits (*(int *)g_glColourBits_v)
#undef g_glDepthBits
#define g_glDepthBits (g_data.g_glDepthBits_)
#undef g_glHeight
#define g_glHeight (g_data.g_glHeight_)
#undef g_glWidth
#define g_glWidth (g_data.g_glWidth_)
#undef g_hInstance
#define g_hInstance (g_data.g_hInstance_)
#undef g_hangulLeadGlyph
#define g_hangulLeadGlyph (*(int *)g_hangulLeadGlyph_v)
#undef g_hangulTailGlyph
#define g_hangulTailGlyph (*(int *)g_hangulTailGlyph_v)
#undef g_hangulVowelGlyph
#define g_hangulVowelGlyph (*(int *)g_hangulVowelGlyph_v)
#undef g_headDetectionAngle
#define g_headDetectionAngle (*(float *)g_headDetectionAngle_v)
#undef g_headDetectionRange
#define g_headDetectionRange (*(float *)g_headDetectionRange_v)
#undef g_headHackingLevel
#define g_headHackingLevel (g_data.g_headHackingLevel_)
#undef g_headLockOnTime
#define g_headLockOnTime (g_data.g_headLockOnTime_)
#undef g_headTargetKeepTime
#define g_headTargetKeepTime (g_data.g_headTargetKeepTime_)
#undef g_headWeight
#define g_headWeight (g_data.g_headWeight_)
#undef g_hostAddressBlock
#define g_hostAddressBlock (g_data.g_hostAddressBlock_)
#undef g_hostResultFlag
#define g_hostResultFlag (g_data.g_hostResultFlag_)
#undef g_inputFont
#define g_inputFont (*(void * *)g_inputFont_v)
#undef g_insertCdMessage
#define g_insertCdMessage (*(const char * *)g_insertCdMessage_v)
#undef g_instanceGuid
#define g_instanceGuid (*(const void * *)g_instanceGuid_v)
#undef g_introZoom
#define g_introZoom (g_data.g_introZoom_)
#undef g_isHost
#define g_isHost (g_data.g_isHost_)
#undef g_itemBonusActiveTime
#define g_itemBonusActiveTime (g_data.g_itemBonusActiveTime_)
#undef g_itemBonusCapacityPerLevel
#define g_itemBonusCapacityPerLevel (g_data.g_itemBonusCapacityPerLevel_)
#undef g_itemBonusDetectionRange
#define g_itemBonusDetectionRange (g_data.g_itemBonusDetectionRange_)
#undef g_itemBonusHacking
#define g_itemBonusHacking (g_data.g_itemBonusHacking_)
#undef g_itemBonusLockOn
#define g_itemBonusLockOn (g_data.g_itemBonusLockOn_)
#undef g_itemBonusRechargeTime
#define g_itemBonusRechargeTime (g_data.g_itemBonusRechargeTime_)
#undef g_itemBonusShield
#define g_itemBonusShield (*(float *)g_itemBonusShield_v)
#undef g_itemBonusTargetKeep
#define g_itemBonusTargetKeep (g_data.g_itemBonusTargetKeep_)
#undef g_itemBonusWeightLimit
#define g_itemBonusWeightLimit (g_data.g_itemBonusWeightLimit_)
#undef g_itemSlot4
#define g_itemSlot4 (g_data.g_itemSlot4_)
#undef g_itemSlot5
#define g_itemSlot5 (g_data.g_itemSlot5_)
#undef g_joinPasswordTyped
#define g_joinPasswordTyped (g_data.g_joinPasswordTyped_)
#undef g_joinedSessionFlag
#define g_joinedSessionFlag (g_data.g_joinedSessionFlag_)
#undef g_joinedTitleLevel
#define g_joinedTitleLevel (g_data.g_joinedTitleLevel_)
#undef g_joinedTitleName
#define g_joinedTitleName ((char *)g_data.g_joinedTitleName_)
#undef g_joinedTitlePoints
#define g_joinedTitlePoints (g_data.g_joinedTitlePoints_)
#undef g_joinedTitleRating
#define g_joinedTitleRating (g_data.g_joinedTitleRating_)
#undef g_keepCameraAsked
#define g_keepCameraAsked (*(int *)g_keepCameraAsked_v)
#undef g_keptChatLine
#define g_keptChatLine (g_data.g_keptChatLine_)
#undef g_keyEnter
#define g_keyEnter (g_data.g_keyEnter_)
#undef g_keyFreeCam0
#define g_keyFreeCam0 (g_data.g_keyFreeCam0_)
#undef g_keyFreeCam1
#define g_keyFreeCam1 (g_data.g_keyFreeCam1_)
#undef g_keyFreeCam2
#define g_keyFreeCam2 (g_data.g_keyFreeCam2_)
#undef g_keyFreeCam3
#define g_keyFreeCam3 (g_data.g_keyFreeCam3_)
#undef g_keyLoadingSkip
#define g_keyLoadingSkip (g_data.g_keyLoadingSkip_)
#undef g_keyLoadingSkip2
#define g_keyLoadingSkip2 (g_data.g_keyLoadingSkip2_)
#undef g_keySeen
#define g_keySeen ((int *)g_keySeen_v)
#undef g_keyWatchChat
#define g_keyWatchChat (g_data.g_keyWatchChat_)
#undef g_ladderPort
#define g_ladderPort (g_data.g_ladderPort_)
#undef g_lanSearch
#define g_lanSearch (g_data.g_lanSearch_)
#undef g_languageId
#define g_languageId (g_data.g_languageId_)
#undef g_lastCrosshair
#define g_lastCrosshair (g_data.g_lastCrosshair_)
#undef g_lastFrameClock
#define g_lastFrameClock (g_data.g_lastFrameClock_)
#undef g_lastPanel
#define g_lastPanel (*(int *)g_lastPanel_v)
#undef g_lastTime
#define g_lastTime (g_data.g_lastTime_)
#undef g_launchMessage
#define g_launchMessage (*(const char * *)g_launchMessage_v)
#undef g_legsMaxWeight
#define g_legsMaxWeight (g_data.g_legsMaxWeight_)
#undef g_legsSpeedCorrection
#define g_legsSpeedCorrection (g_data.g_legsSpeedCorrection_)
#undef g_legsWeight
#define g_legsWeight (g_data.g_legsWeight_)
#undef g_listRefreshPeriod
#define g_listRefreshPeriod (*(int *)g_listRefreshPeriod_v)
#undef g_loadStep
#define g_loadStep (*(int *)g_loadStep_v)
#undef g_lobbyBlinkClock
#define g_lobbyBlinkClock (g_data.g_lobbyBlinkClock_)
#undef g_lobbyConnectStatus
#define g_lobbyConnectStatus (g_data.g_lobbyConnectStatus_)
#undef g_lobbyConnectionBlock
#define g_lobbyConnectionBlock (g_data.g_lobbyConnectionBlock_)
#undef g_lobbyConnectionOpen
#define g_lobbyConnectionOpen (*(int *)g_lobbyConnectionOpen_v)
#undef g_lobbyJoinRequest
#define g_lobbyJoinRequest (g_data.g_lobbyJoinRequest_)
#undef g_lobbyJoinStarted
#define g_lobbyJoinStarted (g_data.g_lobbyJoinStarted_)
#undef g_lobbyListPage
#define g_lobbyListPage (g_data.g_lobbyListPage_)
#undef g_lobbyListRow
#define g_lobbyListRow (g_data.g_lobbyListRow_)
#undef g_lobbyPanelsOff
#define g_lobbyPanelsOff (g_data.g_lobbyPanelsOff_)
#undef g_lobbyPending
#define g_lobbyPending (g_data.g_lobbyPending_)
#undef g_lobbyRefreshing
#define g_lobbyRefreshing (g_data.g_lobbyRefreshing_)
#undef g_lobbyReply
#define g_lobbyReply (g_data.g_lobbyReply_)
#undef g_lobbyReplyKind
#define g_lobbyReplyKind (*(u32 *)g_lobbyReplyKind_v)
#undef g_lobbySearching
#define g_lobbySearching (g_data.g_lobbySearching_)
#undef g_lobbySocket
#define g_lobbySocket (g_data.g_lobbySocket_)
#undef g_lobbyStatus
#define g_lobbyStatus (g_data.g_lobbyStatus_)
#undef g_lobbyTcpPort
#define g_lobbyTcpPort (g_data.g_lobbyTcpPort_)
#undef g_localAddress
#define g_localAddress ((char *)g_data.g_localAddress_)
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
#define g_loginFormBottom (g_data.g_loginFormBottom_)
#undef g_loginFormLeft
#define g_loginFormLeft (g_data.g_loginFormLeft_)
#undef g_loginToSend
#define g_loginToSend (*(int *)g_loginToSend_v)
#undef g_mainMenuDepth
#define g_mainMenuDepth (g_data.g_mainMenuDepth_)
#undef g_mainMenuFadingIn
#define g_mainMenuFadingIn (g_data.g_mainMenuFadingIn_)
#undef g_mainMenuFrames
#define g_mainMenuFrames (g_data.g_mainMenuFrames_)
#undef g_mainMenuPicked
#define g_mainMenuPicked (g_data.g_mainMenuPicked_)
#undef g_mainWindow
#define g_mainWindow (g_data.g_mainWindow_)
#undef g_mapEntry22On
#define g_mapEntry22On (*(int *)g_mapEntry22On_v)
#undef g_mapEntry23On
#define g_mapEntry23On (*(int *)g_mapEntry23On_v)
#undef g_mapEntry24On
#define g_mapEntry24On (*(int *)g_mapEntry24On_v)
#undef g_mapListFlaggedCount
#define g_mapListFlaggedCount (g_data.g_mapListFlaggedCount_)
#undef g_mapListMade
#define g_mapListMade (*(int *)g_mapListMade_v)
#undef g_mapListOpen
#define g_mapListOpen (*(int *)g_mapListOpen_v)
#undef g_mapMissing
#define g_mapMissing (*(int *)g_mapMissing_v)
#undef g_mapNames
#define g_mapNames ((char *)g_data.g_mapNames_)
#undef g_mapPreviewChanged
#define g_mapPreviewChanged (*(int *)g_mapPreviewChanged_v)
#undef g_mapPreviewTexture
#define g_mapPreviewTexture (*(int *)g_mapPreviewTexture_v)
#undef g_mapRotation
#define g_mapRotation (g_data.g_mapRotation_)
#undef g_mapSelectBottom
#define g_mapSelectBottom (g_data.g_mapSelectBottom_)
#undef g_mapSelectCount
#define g_mapSelectCount (g_data.g_mapSelectCount_)
#undef g_mapSelectDimA
#define g_mapSelectDimA (g_data.g_mapSelectDimA_)
#undef g_mapSelectDimB
#define g_mapSelectDimB (g_data.g_mapSelectDimB_)
#undef g_mapSelectDimG
#define g_mapSelectDimG (g_data.g_mapSelectDimG_)
#undef g_mapSelectDimR
#define g_mapSelectDimR (g_data.g_mapSelectDimR_)
#undef g_mapSelectFirst
#define g_mapSelectFirst (g_data.g_mapSelectFirst_)
#undef g_mapSelectLeft
#define g_mapSelectLeft (g_data.g_mapSelectLeft_)
#undef g_mapSelectLitA
#define g_mapSelectLitA (g_data.g_mapSelectLitA_)
#undef g_mapSelectLitB
#define g_mapSelectLitB (g_data.g_mapSelectLitB_)
#undef g_mapSelectLitG
#define g_mapSelectLitG (g_data.g_mapSelectLitG_)
#undef g_mapSelectLitR
#define g_mapSelectLitR (g_data.g_mapSelectLitR_)
#undef g_mapSelectRight
#define g_mapSelectRight (g_data.g_mapSelectRight_)
#undef g_mapSelectTop
#define g_mapSelectTop (g_data.g_mapSelectTop_)
#undef g_mapTitle
#define g_mapTitle ((char *)g_data.g_mapTitle_)
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
#define g_matchMode (g_data.g_matchMode_)
#undef g_matchRunning
#define g_matchRunning (g_data.g_matchRunning_)
#undef g_mciCallback
#define g_mciCallback (*(u32 *)g_mciCallback_v)
#undef g_mciDevice
#define g_mciDevice (*(u32 *)g_mciDevice_v)
#undef g_mciFrom
#define g_mciFrom (*(u32 *)g_mciFrom_v)
#undef g_mciTo
#define g_mciTo (*(u32 *)g_mciTo_v)
#undef g_mechBoosterEnergy
#define g_mechBoosterEnergy (g_data.g_mechBoosterEnergy_)
#undef g_mechBoosterRecharge
#define g_mechBoosterRecharge (g_data.g_mechBoosterRecharge_)
#undef g_mechChanged
#define g_mechChanged (*(int *)g_mechChanged_v)
#undef g_mechDetectionRange
#define g_mechDetectionRange (*(float *)g_mechDetectionRange_v)
#undef g_mechHackingLevel
#define g_mechHackingLevel (g_data.g_mechHackingLevel_)
#undef g_mechItem2
#define g_mechItem2 (g_data.g_mechItem2_)
#undef g_mechItem3
#define g_mechItem3 (g_data.g_mechItem3_)
#undef g_mechItem4
#define g_mechItem4 (g_data.g_mechItem4_)
#undef g_mechItem5
#define g_mechItem5 (g_data.g_mechItem5_)
#undef g_mechMaxSpeedBwd
#define g_mechMaxSpeedBwd (g_data.g_mechMaxSpeedBwd_)
#undef g_mechMobility
#define g_mechMobility (g_data.g_mechMobility_)
#undef g_mechNormalSpeed
#define g_mechNormalSpeed (g_data.g_mechNormalSpeed_)
#undef g_menuCamX
#define g_menuCamX (*(u32 *)g_menuCamX_v)
#undef g_menuCamZ
#define g_menuCamZ (*(u32 *)g_menuCamZ_v)
#undef g_menuCameraHeight
#define g_menuCameraHeight (g_data.g_menuCameraHeight_)
#undef g_menuCameraLook
#define g_menuCameraLook (g_data.g_menuCameraLook_)
#undef g_menuCameraLookY
#define g_menuCameraLookY (g_data.g_menuCameraLookY_)
#undef g_menuCameraPos
#define g_menuCameraPos (g_data.g_menuCameraPos_)
#undef g_menuCameraX
#define g_menuCameraX (g_data.g_menuCameraX_)
#undef g_menuCameraY
#define g_menuCameraY (g_data.g_menuCameraY_)
#undef g_menuCameraZ
#define g_menuCameraZ (g_data.g_menuCameraZ_)
#undef g_menuFrameCount
#define g_menuFrameCount (*(int *)g_menuFrameCount_v)
#undef g_menuFrameCounter
#define g_menuFrameCounter (g_data.g_menuFrameCounter_)
#undef g_menuFramePhase
#define g_menuFramePhase (g_data.g_menuFramePhase_)
#undef g_menuHintClock
#define g_menuHintClock (g_data.g_menuHintClock_)
#undef g_menuHintStep
#define g_menuHintStep (g_data.g_menuHintStep_)
#undef g_menuIdleTime
#define g_menuIdleTime (g_data.g_menuIdleTime_)
#undef g_menuLookAtX
#define g_menuLookAtX (g_data.g_menuLookAtX_)
#undef g_menuLookAtY
#define g_menuLookAtY (g_data.g_menuLookAtY_)
#undef g_menuLookAtZ
#define g_menuLookAtZ (g_data.g_menuLookAtZ_)
#undef g_menuScaleX
#define g_menuScaleX (g_data.g_menuScaleX_)
#undef g_menuScaleY
#define g_menuScaleY (g_data.g_menuScaleY_)
#undef g_menuTunnelSpeed
#define g_menuTunnelSpeed (g_data.g_menuTunnelSpeed_)
#undef g_menuTunnelTexture
#define g_menuTunnelTexture (*(int *)g_menuTunnelTexture_v)
#undef g_messageBoxArgs
#define g_messageBoxArgs (*(va_list *)g_messageBoxArgs_v)
#undef g_messages
#define g_messages ((char *)g_messages_v)
#undef g_misHeader1
#define g_misHeader1 (g_data.g_misHeader1_)
#undef g_misHeader2
#define g_misHeader2 (g_data.g_misHeader2_)
#undef g_misHeader3
#define g_misHeader3 (g_data.g_misHeader3_)
#undef g_missionChosen
#define g_missionChosen (g_data.g_missionChosen_)
#undef g_missionCount
#define g_missionCount (g_data.g_missionCount_)
#undef g_missionPicked
#define g_missionPicked (g_data.g_missionPicked_)
#undef g_missionPreviewDue
#define g_missionPreviewDue (*(int *)g_missionPreviewDue_v)
#undef g_missionSelectLeft
#define g_missionSelectLeft (g_data.g_missionSelectLeft_)
#undef g_missionSelectTop
#define g_missionSelectTop (g_data.g_missionSelectTop_)
#undef g_missionShown
#define g_missionShown (*(int *)g_missionShown_v)
#undef g_missions
#define g_missions ((u8 *)g_missions_v)
#undef g_mouse2Down
#define g_mouse2Down (g_data.g_mouse2Down_)
#undef g_mouse3Down
#define g_mouse3Down (g_data.g_mouse3Down_)
#undef g_mouseInvert
#define g_mouseInvert (g_data.g_mouseInvert_)
#undef g_mouseSensitivity
#define g_mouseSensitivity (g_data.g_mouseSensitivity_)
#undef g_mouseSmooth
#define g_mouseSmooth (g_data.g_mouseSmooth_)
#undef g_mouseWheel
#define g_mouseWheel (g_data.g_mouseWheel_)
#undef g_mouseWheelTurned
#define g_mouseWheelTurned (g_data.g_mouseWheelTurned_)
#undef g_musicEndHigh
#define g_musicEndHigh (g_data.g_musicEndHigh_)
#undef g_musicLength
#define g_musicLength (g_data.g_musicLength_)
#undef g_musicVolume
#define g_musicVolume (g_data.g_musicVolume_)
#undef g_musicVolumeSetting
#define g_musicVolumeSetting (*(int *)g_musicVolumeSetting_v)
#undef g_netAccountBuffer
#define g_netAccountBuffer (g_data.g_netAccountBuffer_)
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
#define g_netClaimedSlot (g_data.g_netClaimedSlot_)
#undef g_netConnected
#define g_netConnected (*(int *)g_netConnected_v)
#undef g_netHostGone
#define g_netHostGone (*(int *)g_netHostGone_v)
#undef g_netInfoPacket
#define g_netInfoPacket (g_data.g_netInfoPacket_)
#undef g_netJoinMessage
#define g_netJoinMessage (g_data.g_netJoinMessage_)
#undef g_netKindWord
#define g_netKindWord (g_data.g_netKindWord_)
#undef g_netLastRequest
#define g_netLastRequest (*(int *)g_netLastRequest_v)
#undef g_netLeaveBuffer
#define g_netLeaveBuffer (g_data.g_netLeaveBuffer_)
#undef g_netListDone
#define g_netListDone (g_data.g_netListDone_)
#undef g_netLobbyMessage
#define g_netLobbyMessage (g_data.g_netLobbyMessage_)
#undef g_netNotice
#define g_netNotice (g_data.g_netNotice_)
#undef g_netNoticeIn
#define g_netNoticeIn (g_data.g_netNoticeIn_)
#undef g_netPacketMessageKind
#define g_netPacketMessageKind (g_data.g_netPacketMessageKind_)
#undef g_netPlayerList
#define g_netPlayerList ((u8 *)g_data.g_netPlayerList_)
#undef g_netPlayerRecordPacket
#define g_netPlayerRecordPacket (g_data.g_netPlayerRecordPacket_)
#undef g_netQueueOnline
#define g_netQueueOnline (g_data.g_netQueueOnline_)
#undef g_netRankingBuffer
#define g_netRankingBuffer (g_data.g_netRankingBuffer_)
#undef g_netRecvBuffer
#define g_netRecvBuffer (g_data.g_netRecvBuffer_)
#undef g_netRequestWord
#define g_netRequestWord (g_data.g_netRequestWord_)
#undef g_netRole
#define g_netRole (g_data.g_netRole_)
#undef g_netSelectionPacket
#define g_netSelectionPacket (g_data.g_netSelectionPacket_)
#undef g_netSendBuffer
#define g_netSendBuffer (g_data.g_netSendBuffer_)
#undef g_netSendName
#define g_netSendName (g_data.g_netSendName_)
#undef g_netSlotMessageKind
#define g_netSlotMessageKind (g_data.g_netSlotMessageKind_)
#undef g_netSlots
#define g_netSlots ((u8 *)g_data.g_netSlots_)
#undef g_newArenaFormBottom
#define g_newArenaFormBottom (g_data.g_newArenaFormBottom_)
#undef g_newArenaFormLeft
#define g_newArenaFormLeft (g_data.g_newArenaFormLeft_)
#undef g_newArenaFormRight
#define g_newArenaFormRight (g_data.g_newArenaFormRight_)
#undef g_newArenaFormTop
#define g_newArenaFormTop (g_data.g_newArenaFormTop_)
#undef g_newArenaKind
#define g_newArenaKind (g_data.g_newArenaKind_)
#undef g_newArenaMap
#define g_newArenaMap (g_data.g_newArenaMap_)
#undef g_newArenaMode
#define g_newArenaMode (g_data.g_newArenaMode_)
#undef g_newArenaName
#define g_newArenaName ((char *)g_data.g_newArenaName_)
#undef g_newArenaPassword
#define g_newArenaPassword (g_data.g_newArenaPassword_)
#undef g_newArenaPassword4
#define g_newArenaPassword4 (g_data.g_newArenaPassword4_)
#undef g_newArenaPlayers
#define g_newArenaPlayers (g_data.g_newArenaPlayers_)
#undef g_newNameDialogBottom
#define g_newNameDialogBottom (g_data.g_newNameDialogBottom_)
#undef g_newNameDialogLeft
#define g_newNameDialogLeft (g_data.g_newNameDialogLeft_)
#undef g_newNameDialogRight
#define g_newNameDialogRight (g_data.g_newNameDialogRight_)
#undef g_newNameDialogTop
#define g_newNameDialogTop (g_data.g_newNameDialogTop_)
#undef g_openLoginName
#define g_openLoginName (*(int *)g_openLoginName_v)
#undef g_otherModeHeight
#define g_otherModeHeight (*(int *)g_otherModeHeight_v)
#undef g_otherModeWidth
#define g_otherModeWidth (*(int *)g_otherModeWidth_v)
#undef g_packedWhite
#define g_packedWhite ((u8 *)g_data.g_packedWhite_)
#undef g_panelGlow
#define g_panelGlow (*(float *)g_panelGlow_v)
#undef g_panelGlowStep
#define g_panelGlowStep (*(u32 *)g_panelGlowStep_v)
#undef g_panelHovered
#define g_panelHovered (g_data.g_panelHovered_)
#undef g_partBox0Offset
#define g_partBox0Offset (*(u32 *)g_partBox0Offset_v)
#undef g_partBox1Offset
#define g_partBox1Offset (*(u32 *)g_partBox1Offset_v)
#undef g_partBox2Offset
#define g_partBox2Offset (*(u32 *)g_partBox2Offset_v)
#undef g_partBox3Offset
#define g_partBox3Offset (*(u32 *)g_partBox3Offset_v)
#undef g_partBox4Offset
#define g_partBox4Offset (*(u32 *)g_partBox4Offset_v)
#undef g_partBox5Offset
#define g_partBox5Offset (*(u32 *)g_partBox5Offset_v)
#undef g_penFontNeverSet
#define g_penFontNeverSet (*(int *)g_penFontNeverSet_v)
#undef g_penFontTexture
#define g_penFontTexture (*(int *)g_penFontTexture_v)
#undef g_perfCounter
#define g_perfCounter (g_data.g_perfCounter_)
#undef g_pilotChosen
#define g_pilotChosen (g_data.g_pilotChosen_)
#undef g_pilotClan
#define g_pilotClan (g_data.g_pilotClan_)
#undef g_pilotLevel
#define g_pilotLevel (g_data.g_pilotLevel_)
#undef g_pilotLevelKept
#define g_pilotLevelKept (g_data.g_pilotLevelKept_)
#undef g_pilotLosses
#define g_pilotLosses (g_data.g_pilotLosses_)
#undef g_pilotLossesKept
#define g_pilotLossesKept (g_data.g_pilotLossesKept_)
#undef g_pilotPoints
#define g_pilotPoints (g_data.g_pilotPoints_)
#undef g_pilotPointsKept
#define g_pilotPointsKept (g_data.g_pilotPointsKept_)
#undef g_pilotRating
#define g_pilotRating (g_data.g_pilotRating_)
#undef g_pilotRatingKept
#define g_pilotRatingKept (g_data.g_pilotRatingKept_)
#undef g_pilotScore
#define g_pilotScore (g_data.g_pilotScore_)
#undef g_pilotScoreKept
#define g_pilotScoreKept (g_data.g_pilotScoreKept_)
#undef g_pilotSelectBottom
#define g_pilotSelectBottom (g_data.g_pilotSelectBottom_)
#undef g_pilotSelectLeft
#define g_pilotSelectLeft (g_data.g_pilotSelectLeft_)
#undef g_pilotSelectRight
#define g_pilotSelectRight (g_data.g_pilotSelectRight_)
#undef g_pilotSelectTop
#define g_pilotSelectTop (g_data.g_pilotSelectTop_)
#undef g_pilotWinRate
#define g_pilotWinRate (g_data.g_pilotWinRate_)
#undef g_pilotWins
#define g_pilotWins (g_data.g_pilotWins_)
#undef g_pilotWinsKept
#define g_pilotWinsKept (g_data.g_pilotWinsKept_)
#undef g_pingDataEvent
#define g_pingDataEvent (g_data.g_pingDataEvent_)
#undef g_pingStopEvent
#define g_pingStopEvent (g_data.g_pingStopEvent_)
#undef g_pingThread
#define g_pingThread (g_data.g_pingThread_)
#undef g_pingThreadId
#define g_pingThreadId (g_data.g_pingThreadId_)
#undef g_pingTime
#define g_pingTime (g_data.g_pingTime_)
#undef g_pixelFormatFilled
#define g_pixelFormatFilled (*(u8 *)g_pixelFormatFilled_v)
#undef g_playerCorporation
#define g_playerCorporation (g_data.g_playerCorporation_)
#undef g_playerHasClan
#define g_playerHasClan (g_data.g_playerHasClan_)
#undef g_playerListCount
#define g_playerListCount (g_data.g_playerListCount_)
#undef g_playerListRefused
#define g_playerListRefused (g_data.g_playerListRefused_)
#undef g_playerName
#define g_playerName ((char *)g_data.g_playerName_)
#undef g_playerSex
#define g_playerSex (g_data.g_playerSex_)
#undef g_primarySoundBuffer
#define g_primarySoundBuffer (*(void * *)g_primarySoundBuffer_v)
#undef g_profileColour
#define g_profileColour ((u32 *)g_data.g_profileColour_)
#undef g_profileCount
#define g_profileCount (g_data.g_profileCount_)
#undef g_profileDialogOpen
#define g_profileDialogOpen (g_data.g_profileDialogOpen_)
#undef g_profileDim
#define g_profileDim ((u32 *)g_data.g_profileDim_)
#undef g_profileFrameAlpha
#define g_profileFrameAlpha (*(float *)g_profileFrameAlpha_v)
#undef g_profileFrameStep
#define g_profileFrameStep (*(u32 *)g_profileFrameStep_v)
#undef g_profileList
#define g_profileList ((char *)g_data.g_profileList_)
#undef g_profileListRow
#define g_profileListRow (g_data.g_profileListRow_)
#undef g_profileListTop
#define g_profileListTop (g_data.g_profileListTop_)
#undef g_profileMechArm
#define g_profileMechArm (g_data.g_profileMechArm_)
#undef g_profileMechBooster
#define g_profileMechBooster (g_data.g_profileMechBooster_)
#undef g_profileMechChest
#define g_profileMechChest (g_data.g_profileMechChest_)
#undef g_profileMechItem0
#define g_profileMechItem0 (g_data.g_profileMechItem0_)
#undef g_profileMechItem1
#define g_profileMechItem1 (g_data.g_profileMechItem1_)
#undef g_profileMechItem2
#define g_profileMechItem2 (g_data.g_profileMechItem2_)
#undef g_profileMechItem3
#define g_profileMechItem3 (g_data.g_profileMechItem3_)
#undef g_profileMechItem4
#define g_profileMechItem4 (g_data.g_profileMechItem4_)
#undef g_profileMechItem5
#define g_profileMechItem5 (g_data.g_profileMechItem5_)
#undef g_profileMechLeg
#define g_profileMechLeg (g_data.g_profileMechLeg_)
#undef g_profileMechRecord
#define g_profileMechRecord (g_data.g_profileMechRecord_)
#undef g_profileMessageTime
#define g_profileMessageTime (g_data.g_profileMessageTime_)
#undef g_profileName
#define g_profileName ((char *)g_data.g_profileName_)
#undef g_profilePageBottom
#define g_profilePageBottom (g_data.g_profilePageBottom_)
#undef g_profilePageLeft
#define g_profilePageLeft (g_data.g_profilePageLeft_)
#undef g_profilePageRight
#define g_profilePageRight (*(int *)g_profilePageRight_v)
#undef g_profilePageTop
#define g_profilePageTop (g_data.g_profilePageTop_)
#undef g_profileProgressSaved
#define g_profileProgressSaved (*(int *)g_profileProgressSaved_v)
#undef g_profileRecords
#define g_profileRecords ((u8 *)g_data.g_profileRecords_)
#undef g_profileRowClicked
#define g_profileRowClicked (g_data.g_profileRowClicked_)
#undef g_profileScreenReady
#define g_profileScreenReady (g_data.g_profileScreenReady_)
#undef g_progressWentUp
#define g_progressWentUp (g_data.g_progressWentUp_)
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
#undef g_quitAsked
#define g_quitAsked (g_data.g_quitAsked_)
#undef g_randPos
#define g_randPos (*(u32 *)g_randPos_v)
#undef g_randTable
#define g_randTable ((int *)g_randTable_v)
#undef g_rankingFirst
#define g_rankingFirst (g_data.g_rankingFirst_)
#undef g_rankingHaveList
#define g_rankingHaveList (g_data.g_rankingHaveList_)
#undef g_rankingLast
#define g_rankingLast (*(int *)g_rankingLast_v)
#undef g_rankingRequestPending
#define g_rankingRequestPending (g_data.g_rankingRequestPending_)
#undef g_rankingSort
#define g_rankingSort (g_data.g_rankingSort_)
#undef g_rankingWaiting
#define g_rankingWaiting (g_data.g_rankingWaiting_)
#undef g_receivedClan
#define g_receivedClan (g_data.g_receivedClan_)
#undef g_receivedSession
#define g_receivedSession (g_data.g_receivedSession_)
#undef g_rectColour
#define g_rectColour ((Colour *)g_data.g_rectColour_)
#undef g_replayRandomOrder
#define g_replayRandomOrder (g_data.g_replayRandomOrder_)
#undef g_replayRunning
#define g_replayRunning (g_data.g_replayRunning_)
#undef g_replayWrap
#define g_replayWrap (g_data.g_replayWrap_)
#undef g_resultMessage
#define g_resultMessage (g_data.g_resultMessage_)
#undef g_retypePassword
#define g_retypePassword (*(int *)g_retypePassword_v)
#undef g_roomAnswerAwaited
#define g_roomAnswerAwaited (g_data.g_roomAnswerAwaited_)
#undef g_roomAwaitingServer
#define g_roomAwaitingServer (g_data.g_roomAwaitingServer_)
#undef g_roomBright
#define g_roomBright ((u32 *)g_data.g_roomBright_)
#undef g_roomChatting
#define g_roomChatting (g_data.g_roomChatting_)
#undef g_roomColours
#define g_roomColours ((float *)g_data.g_roomColours_)
#undef g_roomConnected
#define g_roomConnected (g_data.g_roomConnected_)
#undef g_roomCustom
#define g_roomCustom (g_data.g_roomCustom_)
#undef g_roomDialogOpen
#define g_roomDialogOpen (*(int *)g_roomDialogOpen_v)
#undef g_roomDim
#define g_roomDim ((u32 *)g_data.g_roomDim_)
#undef g_roomFade
#define g_roomFade (g_data.g_roomFade_)
#undef g_roomFormBottom
#define g_roomFormBottom (g_data.g_roomFormBottom_)
#undef g_roomFormLeft
#define g_roomFormLeft (g_data.g_roomFormLeft_)
#undef g_roomFormRight
#define g_roomFormRight (g_data.g_roomFormRight_)
#undef g_roomFormTop
#define g_roomFormTop (g_data.g_roomFormTop_)
#undef g_roomFragLimit
#define g_roomFragLimit (g_data.g_roomFragLimit_)
#undef g_roomGameListBottom
#define g_roomGameListBottom (g_data.g_roomGameListBottom_)
#undef g_roomGameListLeft
#define g_roomGameListLeft (g_data.g_roomGameListLeft_)
#undef g_roomGameListRight
#define g_roomGameListRight (g_data.g_roomGameListRight_)
#undef g_roomGameListTop
#define g_roomGameListTop (g_data.g_roomGameListTop_)
#undef g_roomGameMode
#define g_roomGameMode (g_data.g_roomGameMode_)
#undef g_roomJoined
#define g_roomJoined (g_data.g_roomJoined_)
#undef g_roomLeaveDialog
#define g_roomLeaveDialog (g_data.g_roomLeaveDialog_)
#undef g_roomList
#define g_roomList ((u8 *)g_roomList_v)
#undef g_roomListCount
#define g_roomListCount (g_data.g_roomListCount_)
#undef g_roomListDistanceLimit
#define g_roomListDistanceLimit (g_data.g_roomListDistanceLimit_)
#undef g_roomListPage
#define g_roomListPage (g_data.g_roomListPage_)
#undef g_roomListPages
#define g_roomListPages (g_data.g_roomListPages_)
#undef g_roomListPrev
#define g_roomListPrev (*(int *)g_roomListPrev_v)
#undef g_roomListPrevPage
#define g_roomListPrevPage (g_data.g_roomListPrevPage_)
#undef g_roomListPrevRank
#define g_roomListPrevRank (g_data.g_roomListPrevRank_)
#undef g_roomListRefreshTimer
#define g_roomListRefreshTimer (g_data.g_roomListRefreshTimer_)
#undef g_roomListWaiting
#define g_roomListWaiting (g_data.g_roomListWaiting_)
#undef g_roomLoginBottom
#define g_roomLoginBottom (g_data.g_roomLoginBottom_)
#undef g_roomLoginDue
#define g_roomLoginDue (g_data.g_roomLoginDue_)
#undef g_roomLoginLeft
#define g_roomLoginLeft (g_data.g_roomLoginLeft_)
#undef g_roomLoginTop
#define g_roomLoginTop (g_data.g_roomLoginTop_)
#undef g_roomMap
#define g_roomMap (g_data.g_roomMap_)
#undef g_roomMech
#define g_roomMech ((u8 *)g_data.g_roomMech_)
#undef g_roomMessageText
#define g_roomMessageText (g_data.g_roomMessageText_)
#undef g_roomMessageText4
#define g_roomMessageText4 (g_data.g_roomMessageText4_)
#undef g_roomMode
#define g_roomMode (g_data.g_roomMode_)
#undef g_roomNameSum
#define g_roomNameSum (g_data.g_roomNameSum_)
#undef g_roomPacket
#define g_roomPacket (g_data.g_roomPacket_)
#undef g_roomPanelBrightness
#define g_roomPanelBrightness (g_data.g_roomPanelBrightness_)
#undef g_roomPlayers
#define g_roomPlayers (g_data.g_roomPlayers_)
#undef g_roomPopup
#define g_roomPopup (g_data.g_roomPopup_)
#undef g_roomRecCustom
#define g_roomRecCustom (g_data.g_roomRecCustom_)
#undef g_roomRecFragLimit
#define g_roomRecFragLimit (g_data.g_roomRecFragLimit_)
#undef g_roomRecGameMode
#define g_roomRecGameMode (g_data.g_roomRecGameMode_)
#undef g_roomRecMap
#define g_roomRecMap (g_data.g_roomRecMap_)
#undef g_roomRecName
#define g_roomRecName ((char *)g_data.g_roomRecName_)
#undef g_roomRecPlayers
#define g_roomRecPlayers (g_data.g_roomRecPlayers_)
#undef g_roomRecTimeLimit
#define g_roomRecTimeLimit (g_data.g_roomRecTimeLimit_)
#undef g_roomRecordPacket
#define g_roomRecordPacket (g_data.g_roomRecordPacket_)
#undef g_roomRefreshing
#define g_roomRefreshing (g_data.g_roomRefreshing_)
#undef g_roomRequestOut
#define g_roomRequestOut (g_data.g_roomRequestOut_)
#undef g_roomSearchAnswerIn
#define g_roomSearchAnswerIn (g_data.g_roomSearchAnswerIn_)
#undef g_roomSearching
#define g_roomSearching (g_data.g_roomSearching_)
#undef g_roomSettingsName
#define g_roomSettingsName ((char *)g_data.g_roomSettingsName_)
#undef g_roomSlideFarX
#define g_roomSlideFarX (g_data.g_roomSlideFarX_)
#undef g_roomSlideFarY
#define g_roomSlideFarY (g_data.g_roomSlideFarY_)
#undef g_roomSlideFarZ
#define g_roomSlideFarZ (g_data.g_roomSlideFarZ_)
#undef g_roomSlideNearX
#define g_roomSlideNearX (g_data.g_roomSlideNearX_)
#undef g_roomSlideNearY
#define g_roomSlideNearY (g_data.g_roomSlideNearY_)
#undef g_roomSlideNearZ
#define g_roomSlideNearZ (g_data.g_roomSlideNearZ_)
#undef g_roomState
#define g_roomState (g_data.g_roomState_)
#undef g_roomTimeLimit
#define g_roomTimeLimit (g_data.g_roomTimeLimit_)
#undef g_roomTunnelDepth
#define g_roomTunnelDepth (*(u32 *)g_roomTunnelDepth_v)
#undef g_savedColourChoices
#define g_savedColourChoices ((u8 *)g_data.g_savedColourChoices_)
#undef g_savedMechArm
#define g_savedMechArm (g_data.g_savedMechArm_)
#undef g_savedMechBooster
#define g_savedMechBooster (g_data.g_savedMechBooster_)
#undef g_savedMechChest
#define g_savedMechChest (g_data.g_savedMechChest_)
#undef g_savedMechItem1
#define g_savedMechItem1 (g_data.g_savedMechItem1_)
#undef g_savedMechItem2
#define g_savedMechItem2 (g_data.g_savedMechItem2_)
#undef g_savedMechItem3
#define g_savedMechItem3 (g_data.g_savedMechItem3_)
#undef g_savedMechItem4
#define g_savedMechItem4 (g_data.g_savedMechItem4_)
#undef g_savedMechItem5
#define g_savedMechItem5 (g_data.g_savedMechItem5_)
#undef g_savedMechLeg
#define g_savedMechLeg (g_data.g_savedMechLeg_)
#undef g_savedMechParts
#define g_savedMechParts (g_data.g_savedMechParts_)
#undef g_savedMechWeapons
#define g_savedMechWeapons (g_data.g_savedMechWeapons_)
#undef g_screenCentreX
#define g_screenCentreX (g_data.g_screenCentreX_)
#undef g_screenCentreY
#define g_screenCentreY (g_data.g_screenCentreY_)
#undef g_searchResult
#define g_searchResult (g_data.g_searchResult_)
#undef g_sensitivitySlider
#define g_sensitivitySlider (g_data.g_sensitivitySlider_)
#undef g_serverAddress
#define g_serverAddress ((char *)g_data.g_serverAddress_)
#undef g_serverAnswerIn
#define g_serverAnswerIn (g_data.g_serverAnswerIn_)
#undef g_serverConnected
#define g_serverConnected (g_data.g_serverConnected_)
#undef g_serverConnectionState
#define g_serverConnectionState (g_data.g_serverConnectionState_)
#undef g_serverListCount
#define g_serverListCount (g_data.g_serverListCount_)
#undef g_serverNames
#define g_serverNames ((u32 *)g_serverNames_v)
#undef g_serverPingCount
#define g_serverPingCount (g_data.g_serverPingCount_)
#undef g_serverPort
#define g_serverPort (*(u16 *)g_serverPort_v)
#undef g_serverReplyKind
#define g_serverReplyKind (*(int *)g_serverReplyKind_v)
#undef g_serverSearching
#define g_serverSearching (g_data.g_serverSearching_)
#undef g_serviceProviderCount
#define g_serviceProviderCount (*(int *)g_serviceProviderCount_v)
#undef g_settingsPage
#define g_settingsPage (g_data.g_settingsPage_)
#undef g_settingsState
#define g_settingsState (g_data.g_settingsState_)
#undef g_setupControlLeft
#define g_setupControlLeft (g_data.g_setupControlLeft_)
#undef g_setupControlRight
#define g_setupControlRight (g_data.g_setupControlRight_)
#undef g_setupControlTop
#define g_setupControlTop (g_data.g_setupControlTop_)
#undef g_setupOptionsTop
#define g_setupOptionsTop (g_data.g_setupOptionsTop_)
#undef g_setupPage
#define g_setupPage (*(int *)g_setupPage_v)
#undef g_setupPanelMoving
#define g_setupPanelMoving (g_data.g_setupPanelMoving_)
#undef g_setupPanelPos
#define g_setupPanelPos (*(float *)g_setupPanelPos_v)
#undef g_setupPressed
#define g_setupPressed (g_data.g_setupPressed_)
#undef g_setupPressedClock
#define g_setupPressedClock (*(float *)g_setupPressedClock_v)
#undef g_setupResolution
#define g_setupResolution (g_data.g_setupResolution_)
#undef g_setupSoundLeft
#define g_setupSoundLeft (g_data.g_setupSoundLeft_)
#undef g_setupSoundRight
#define g_setupSoundRight (g_data.g_setupSoundRight_)
#undef g_setupTunnelAlpha
#define g_setupTunnelAlpha (*(float *)g_setupTunnelAlpha_v)
#undef g_setupTunnelDepth
#define g_setupTunnelDepth (*(float *)g_setupTunnelDepth_v)
#undef g_showCmd
#define g_showCmd (*(int *)g_showCmd_v)
#undef g_sinTable
#define g_sinTable ((float *)g_sinTable_v)
#undef g_skirmishDrawBackground
#define g_skirmishDrawBackground (g_data.g_skirmishDrawBackground_)
#undef g_skirmishInfoCount
#define g_skirmishInfoCount (g_data.g_skirmishInfoCount_)
#undef g_slotTakenFlag
#define g_slotTakenFlag (*(int *)g_slotTakenFlag_v)
#undef g_sound3D
#define g_sound3D (g_data.g_sound3D_)
#undef g_soundBaseVolume
#define g_soundBaseVolume (*(int *)g_soundBaseVolume_v)
#undef g_soundOn
#define g_soundOn (*(int *)g_soundOn_v)
#undef g_soundSwitch1
#define g_soundSwitch1 (g_data.g_soundSwitch1_)
#undef g_soundToggle6
#define g_soundToggle6 (g_data.g_soundToggle6_)
#undef g_soundToggle7
#define g_soundToggle7 (g_data.g_soundToggle7_)
#undef g_soundVolume
#define g_soundVolume (g_data.g_soundVolume_)
#undef g_startTicks
#define g_startTicks (*(u32 *)g_startTicks_v)
#undef g_startedByLauncher
#define g_startedByLauncher (*(int *)g_startedByLauncher_v)
#undef g_startedFromLobby
#define g_startedFromLobby (g_data.g_startedFromLobby_)
#undef g_staticTex128x128
#define g_staticTex128x128 (g_data.g_staticTex128x128_)
#undef g_staticTex128x64
#define g_staticTex128x64 (g_data.g_staticTex128x64_)
#undef g_staticTex256x128
#define g_staticTex256x128 (g_data.g_staticTex256x128_)
#undef g_staticTex256x256
#define g_staticTex256x256 (g_data.g_staticTex256x256_)
#undef g_staticTex256x64
#define g_staticTex256x64 (g_data.g_staticTex256x64_)
#undef g_staticTex64x64
#define g_staticTex64x64 (g_data.g_staticTex64x64_)
#undef g_statusLine
#define g_statusLine (g_data.g_statusLine_)
#undef g_storedConnection
#define g_storedConnection (*(void * *)g_storedConnection_v)
#undef g_tan10Table
#define g_tan10Table ((float *)g_tan10Table_v)
#undef g_tanTable
#define g_tanTable ((float *)g_tanTable_v)
#undef g_textBottom
#define g_textBottom (g_data.g_textBottom_)
#undef g_textColour
#define g_textColour ((Colour *)g_data.g_textColour_)
#undef g_textEndX
#define g_textEndX (*(int *)g_textEndX_v)
#undef g_textEndY
#define g_textEndY (*(int *)g_textEndY_v)
#undef g_textWrapX
#define g_textWrapX (g_data.g_textWrapX_)
#undef g_textureManager
#define g_textureManager (g_data.g_textureManager_)
#undef g_textureSetHeight
#define g_textureSetHeight (g_data.g_textureSetHeight_)
#undef g_textureSetWidth
#define g_textureSetWidth (g_data.g_textureSetWidth_)
#undef g_timeLimit
#define g_timeLimit (g_data.g_timeLimit_)
#undef g_timerFirstCall
#define g_timerFirstCall (*(int *)g_timerFirstCall_v)
#undef g_timerHigh
#define g_timerHigh (g_data.g_timerHigh_)
#undef g_timerRepeatCount
#define g_timerRepeatCount (*(int *)g_timerRepeatCount_v)
#undef g_titleLevel
#define g_titleLevel (g_data.g_titleLevel_)
#undef g_titleLosses
#define g_titleLosses (g_data.g_titleLosses_)
#undef g_titleName
#define g_titleName ((char *)g_data.g_titleName_)
#undef g_titlePoints
#define g_titlePoints (g_data.g_titlePoints_)
#undef g_titleRating
#define g_titleRating (g_data.g_titleRating_)
#undef g_titleScore
#define g_titleScore (g_data.g_titleScore_)
#undef g_titleWins
#define g_titleWins (g_data.g_titleWins_)
#undef g_totalWeight
#define g_totalWeight (g_data.g_totalWeight_)
#undef g_tunnelFlyingIn
#define g_tunnelFlyingIn (g_data.g_tunnelFlyingIn_)
#undef g_tunnelPulseStep
#define g_tunnelPulseStep (g_data.g_tunnelPulseStep_)
#undef g_tunnelRings
#define g_tunnelRings (*(int *)g_tunnelRings_v)
#undef g_typedArenaName
#define g_typedArenaName (g_data.g_typedArenaName_)
#undef g_typedArenaName4
#define g_typedArenaName4 (g_data.g_typedArenaName4_)
#undef g_typedLength
#define g_typedLength (*(int *)g_typedLength_v)
#undef g_typingAccountEmail
#define g_typingAccountEmail (g_data.g_typingAccountEmail_)
#undef g_typingAccountName
#define g_typingAccountName (g_data.g_typingAccountName_)
#undef g_typingAccountPassword
#define g_typingAccountPassword (g_data.g_typingAccountPassword_)
#undef g_typingAccountRepeat
#define g_typingAccountRepeat (g_data.g_typingAccountRepeat_)
#undef g_typingArenaName
#define g_typingArenaName (g_data.g_typingArenaName_)
#undef g_typingArenaPassword
#define g_typingArenaPassword (g_data.g_typingArenaPassword_)
#undef g_typingGameName
#define g_typingGameName (*(int *)g_typingGameName_v)
#undef g_typingGamePassword
#define g_typingGamePassword (g_data.g_typingGamePassword_)
#undef g_typingRoomName
#define g_typingRoomName (g_data.g_typingRoomName_)
#undef g_typingRoomPassword
#define g_typingRoomPassword (g_data.g_typingRoomPassword_)
#undef g_undoDepth
#define g_undoDepth (*(int *)g_undoDepth_v)
#undef g_unlockedLevel
#define g_unlockedLevel (g_data.g_unlockedLevel_)
#undef g_unusedArmcMoveWord
#define g_unusedArmcMoveWord (*(u32 *)g_unusedArmcMoveWord_v)
#undef g_unusedArmcWord1
#define g_unusedArmcWord1 (*(int *)g_unusedArmcWord1_v)
#undef g_unusedArmcWord2
#define g_unusedArmcWord2 (g_data.g_unusedArmcWord2_)
#undef g_unusedArmcWord3
#define g_unusedArmcWord3 (*(int *)g_unusedArmcWord3_v)
#undef g_unusedArmcWord4
#define g_unusedArmcWord4 (g_data.g_unusedArmcWord4_)
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
#define g_unusedLastWParam (g_data.g_unusedLastWParam_)
#undef g_unusedLoginWord
#define g_unusedLoginWord (g_data.g_unusedLoginWord_)
#undef g_unusedMainMenuWord
#define g_unusedMainMenuWord (g_data.g_unusedMainMenuWord_)
#undef g_unusedMechStat
#define g_unusedMechStat (g_data.g_unusedMechStat_)
#undef g_unusedMenuReturnWord
#define g_unusedMenuReturnWord (g_data.g_unusedMenuReturnWord_)
#undef g_unusedMissionSaveWord
#define g_unusedMissionSaveWord (g_data.g_unusedMissionSaveWord_)
#undef g_unusedNetCloseWord
#define g_unusedNetCloseWord (*(int *)g_unusedNetCloseWord_v)
#undef g_unusedPingWord1
#define g_unusedPingWord1 (*(int *)g_unusedPingWord1_v)
#undef g_unusedPingWord2
#define g_unusedPingWord2 (*(int *)g_unusedPingWord2_v)
#undef g_unusedPlayerRecord26
#define g_unusedPlayerRecord26 (g_data.g_unusedPlayerRecord26_)
#undef g_unusedPlayerRecord2a
#define g_unusedPlayerRecord2a (g_data.g_unusedPlayerRecord2a_)
#undef g_unusedPostMatchFlag
#define g_unusedPostMatchFlag (*(int *)g_unusedPostMatchFlag_v)
#undef g_unusedProfileCameraWord
#define g_unusedProfileCameraWord (*(int *)g_unusedProfileCameraWord_v)
#undef g_unusedReplayListWord1
#define g_unusedReplayListWord1 (g_data.g_unusedReplayListWord1_)
#undef g_unusedReplayListWord2
#define g_unusedReplayListWord2 (*(int *)g_unusedReplayListWord2_v)
#undef g_unusedRoomListWord
#define g_unusedRoomListWord (*(int *)g_unusedRoomListWord_v)
#undef g_unusedRoomWord
#define g_unusedRoomWord (g_data.g_unusedRoomWord_)
#undef g_unusedSessionWord
#define g_unusedSessionWord (*(int *)g_unusedSessionWord_v)
#undef g_unusedStartupWord1
#define g_unusedStartupWord1 (*(int *)g_unusedStartupWord1_v)
#undef g_unusedStartupWord2
#define g_unusedStartupWord2 (*(u32 *)g_unusedStartupWord2_v)
#undef g_unusedStartupWord3
#define g_unusedStartupWord3 (*(int *)g_unusedStartupWord3_v)
#undef g_vecOrigin
#define g_vecOrigin (g_data.g_vecOrigin_)
#undef g_vecUnitX
#define g_vecUnitX ((float *)g_data.g_vecUnitX_)
#undef g_vecUnitY
#define g_vecUnitY ((float *)g_data.g_vecUnitY_)
#undef g_vecUnitZ
#define g_vecUnitZ (g_data.g_vecUnitZ_)
#undef g_vecZero
#define g_vecZero (g_data.g_vecZero_)
#undef g_vecZero2
#define g_vecZero2 ((float *)g_data.g_vecZero2_)
#undef g_videoDepth
#define g_videoDepth (g_data.g_videoDepth_)
#undef g_videoMode
#define g_videoMode (g_data.g_videoMode_)
#undef g_viewFar
#define g_viewFar (*(float *)g_viewFar_v)
#undef g_viewFov
#define g_viewFov (*(float *)g_viewFov_v)
#undef g_viewNear
#define g_viewNear (*(float *)g_viewNear_v)
#undef g_viewedPartIndex
#define g_viewedPartIndex (g_data.g_viewedPartIndex_)
#undef g_viewedPartKind
#define g_viewedPartKind (g_data.g_viewedPartKind_)
#undef g_volumeSetting
#define g_volumeSetting (g_data.g_volumeSetting_)
#undef g_watchChatOpen
#define g_watchChatOpen (*(int *)g_watchChatOpen_v)
#undef g_watchedSlot
#define g_watchedSlot (*(u8 *)g_watchedSlot_v)
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
#undef g_errorHook
#define g_errorHook (*(ErrorHook *)IMG(0x4c57cc))
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
#undef g_menuTunnel
#define g_menuTunnel (*(TunnelRing * *)IMG(0x67fb3c))
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
