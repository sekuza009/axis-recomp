/* layout_names.h (tools/mkdatasrc.py): in AxisRC.exe (AXIS_DIRECT) the named globals that are members of
   g_rdata / g_data (src/data/layout.h) as those members; the others stay GAME_VAR (src/globals.h), which IMG()
   routes to the same place */
#pragma once
#include "layout.h"
extern struct GameRdata g_rdata;
extern struct GameData g_data;
#undef g_accountClan
#define g_accountClan (g_data.g_accountClan_)
#undef g_accountEmail
#define g_accountEmail ((char *)g_data.g_accountEmail_)
#undef g_accountName
#define g_accountName ((char *)g_data.g_accountName_)
#undef g_accountNotice
#define g_accountNotice (g_data.g_accountNotice_)
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
#undef g_arenaConfirming
#define g_arenaConfirming (g_data.g_arenaConfirming_)
#undef g_arenaCorporation
#define g_arenaCorporation (g_data.g_arenaCorporation_)
#undef g_arenaCustomize
#define g_arenaCustomize (g_data.g_arenaCustomize_)
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
#define g_arenaFull (g_data.g_arenaFull_)
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
#define g_arenaJoinPending (g_data.g_arenaJoinPending_)
#undef g_arenaJoinRow
#define g_arenaJoinRow (g_data.g_arenaJoinRow_)
#undef g_arenaJoinTimer
#define g_arenaJoinTimer (g_data.g_arenaJoinTimer_)
#undef g_arenaJoinWaiting
#define g_arenaJoinWaiting (g_data.g_arenaJoinWaiting_)
#undef g_arenaJoining
#define g_arenaJoining (g_data.g_arenaJoining_)
#undef g_arenaKeptCamX
#define g_arenaKeptCamX (g_data.g_arenaKeptCamX_)
#undef g_arenaKeptCamY
#define g_arenaKeptCamY (g_data.g_arenaKeptCamY_)
#undef g_arenaKeptCamZ
#define g_arenaKeptCamZ (g_data.g_arenaKeptCamZ_)
#undef g_arenaKeptLookX
#define g_arenaKeptLookX (g_data.g_arenaKeptLookX_)
#undef g_arenaKeptLookY
#define g_arenaKeptLookY (g_data.g_arenaKeptLookY_)
#undef g_arenaKeptLookZ
#define g_arenaKeptLookZ (g_data.g_arenaKeptLookZ_)
#undef g_arenaLeaving
#define g_arenaLeaving (g_data.g_arenaLeaving_)
#undef g_arenaListClickArmed
#define g_arenaListClickArmed (g_data.g_arenaListClickArmed_)
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
#define g_arenaTunnelDepth (g_data.g_arenaTunnelDepth_)
#undef g_argCount
#define g_argCount (g_data.g_argCount_)
#undef g_armcBuildTexture
#define g_armcBuildTexture (g_data.g_armcBuildTexture_)
#undef g_armcCamDistance
#define g_armcCamDistance (g_data.g_armcCamDistance_)
#undef g_armcCamHeight
#define g_armcCamHeight (g_data.g_armcCamHeight_)
#undef g_armcChanged
#define g_armcChanged (g_data.g_armcChanged_)
#undef g_armcCursor
#define g_armcCursor (g_data.g_armcCursor_)
#undef g_armcEnterStep
#define g_armcEnterStep (g_data.g_armcEnterStep_)
#undef g_armcEnterStepF
#define g_armcEnterStepF (g_data.g_armcEnterStepF_)
#undef g_armcEntered
#define g_armcEntered (g_data.g_armcEntered_)
#undef g_armcFrom
#define g_armcFrom (g_data.g_armcFrom_)
#undef g_armcLastPart
#define g_armcLastPart (g_data.g_armcLastPart_)
#undef g_armcLeaving
#define g_armcLeaving (g_data.g_armcLeaving_)
#undef g_armcLevel
#define g_armcLevel (g_data.g_armcLevel_)
#undef g_armcLookCos
#define g_armcLookCos (g_data.g_armcLookCos_)
#undef g_armcLookSin
#define g_armcLookSin (g_data.g_armcLookSin_)
#undef g_armcLookTilt
#define g_armcLookTilt (g_data.g_armcLookTilt_)
#undef g_armcLookYaw
#define g_armcLookYaw (g_data.g_armcLookYaw_)
#undef g_armcMoveEyeX
#define g_armcMoveEyeX (g_data.g_armcMoveEyeX_)
#undef g_armcMoveEyeY
#define g_armcMoveEyeY (g_data.g_armcMoveEyeY_)
#undef g_armcMoveEyeZ
#define g_armcMoveEyeZ (g_data.g_armcMoveEyeZ_)
#undef g_armcMoveStarted
#define g_armcMoveStarted (g_data.g_armcMoveStarted_)
#undef g_armcMoveTargetX
#define g_armcMoveTargetX (g_data.g_armcMoveTargetX_)
#undef g_armcMoveTargetY
#define g_armcMoveTargetY (g_data.g_armcMoveTargetY_)
#undef g_armcMoveTargetZ
#define g_armcMoveTargetZ (g_data.g_armcMoveTargetZ_)
#undef g_armcPanelDepth
#define g_armcPanelDepth (g_data.g_armcPanelDepth_)
#undef g_armcPreview
#define g_armcPreview (g_data.g_armcPreview_)
#undef g_armcSessionMade
#define g_armcSessionMade (g_data.g_armcSessionMade_)
#undef g_armcSliderLeft
#define g_armcSliderLeft (g_data.g_armcSliderLeft_)
#undef g_armcSlot
#define g_armcSlot (g_data.g_armcSlot_)
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
#define g_armcZoom (g_data.g_armcZoom_)
#undef g_armsFcsLevel
#define g_armsFcsLevel (g_data.g_armsFcsLevel_)
#undef g_armsWeight
#define g_armsWeight (g_data.g_armsWeight_)
#undef g_bestLevelNet
#define g_bestLevelNet (g_data.g_bestLevelNet_)
#undef g_bestProgressSolo
#define g_bestProgressSolo (g_data.g_bestProgressSolo_)
#undef g_bindPage
#define g_bindPage (g_data.g_bindPage_)
#undef g_bindRow
#define g_bindRow (g_data.g_bindRow_)
#undef g_bindWaiting
#define g_bindWaiting (g_data.g_bindWaiting_)
#undef g_bitStream
#define g_bitStream (g_data.g_bitStream_)
#undef g_boosterActiveTime
#define g_boosterActiveTime (g_data.g_boosterActiveTime_)
#undef g_boosterNormalSpeed
#define g_boosterNormalSpeed (g_data.g_boosterNormalSpeed_)
#undef g_boosterRechargeDelay
#define g_boosterRechargeDelay (g_data.g_boosterRechargeDelay_)
#undef g_boosterRechargeTime
#define g_boosterRechargeTime (g_data.g_boosterRechargeTime_)
#undef g_boosterThrustType
#define g_boosterThrustType (g_data.g_boosterThrustType_)
#undef g_boosterWeight
#define g_boosterWeight (g_data.g_boosterWeight_)
#undef g_briefingBottom
#define g_briefingBottom (g_data.g_briefingBottom_)
#undef g_briefingClock
#define g_briefingClock (g_data.g_briefingClock_)
#undef g_briefingDone
#define g_briefingDone (g_data.g_briefingDone_)
#undef g_briefingEnd
#define g_briefingEnd (g_data.g_briefingEnd_)
#undef g_briefingRight
#define g_briefingRight (g_data.g_briefingRight_)
#undef g_briefingShown
#define g_briefingShown (g_data.g_briefingShown_)
#undef g_briefingSkipped
#define g_briefingSkipped (g_data.g_briefingSkipped_)
#undef g_briefingSource
#define g_briefingSource (g_data.g_briefingSource_)
#undef g_briefingStart
#define g_briefingStart (g_data.g_briefingStart_)
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
#define g_catalogueFile (g_data.g_catalogueFile_)
#undef g_cfgPlayerName
#define g_cfgPlayerName ((char *)g_data.g_cfgPlayerName_)
#undef g_cfgSimpleMenu
#define g_cfgSimpleMenu (g_data.g_cfgSimpleMenu_)
#undef g_characterTexture
#define g_characterTexture (g_data.g_characterTexture_)
#undef g_chatEditLength
#define g_chatEditLength (g_data.g_chatEditLength_)
#undef g_chatLine
#define g_chatLine ((char *)g_data.g_chatLine_)
#undef g_chatLineDone
#define g_chatLineDone (g_data.g_chatLineDone_)
#undef g_chatLog
#define g_chatLog (g_data.g_chatLog_)
#undef g_chatLogged
#define g_chatLogged (g_data.g_chatLogged_)
#undef g_chatTyping
#define g_chatTyping (g_data.g_chatTyping_)
#undef g_chestMaxArmor
#define g_chestMaxArmor (g_data.g_chestMaxArmor_)
#undef g_chestMaxShield
#define g_chestMaxShield (g_data.g_chestMaxShield_)
#undef g_chestWeightLimit
#define g_chestWeightLimit (g_data.g_chestWeightLimit_)
#undef g_chosenGameMode
#define g_chosenGameMode (g_data.g_chosenGameMode_)
#undef g_chosenPilot
#define g_chosenPilot (g_data.g_chosenPilot_)
#undef g_clockCheckClosed
#define g_clockCheckClosed (g_data.g_clockCheckClosed_)
#undef g_clockCheckSeconds
#define g_clockCheckSeconds (g_data.g_clockCheckSeconds_)
#undef g_clockCheckTick
#define g_clockCheckTick (g_data.g_clockCheckTick_)
#undef g_clockCheckTickSeconds
#define g_clockCheckTickSeconds (g_data.g_clockCheckTickSeconds_)
#undef g_clockNow
#define g_clockNow (g_data.g_clockNow_)
#undef g_cmdSecret
#define g_cmdSecret (g_data.g_cmdSecret_)
#undef g_cmdTimeLimit
#define g_cmdTimeLimit (g_data.g_cmdTimeLimit_)
#undef g_colourChanged
#define g_colourChanged (g_data.g_colourChanged_)
#undef g_colourMaskRed
#define g_colourMaskRed (g_data.g_colourMaskRed_)
#undef g_coloursChanged
#define g_coloursChanged (g_data.g_coloursChanged_)
#undef g_componentDatPath
#define g_componentDatPath (g_data.g_componentDatPath_)
#undef g_connectStep
#define g_connectStep (g_data.g_connectStep_)
#undef g_connectionAwaited
#define g_connectionAwaited (g_data.g_connectionAwaited_)
#undef g_connectionCopy
#define g_connectionCopy (g_data.g_connectionCopy_)
#undef g_connectionKind
#define g_connectionKind (g_data.g_connectionKind_)
#undef g_convertHangul
#define g_convertHangul (g_data.g_convertHangul_)
#undef g_createQuitDialog
#define g_createQuitDialog (g_data.g_createQuitDialog_)
#undef g_crosshair
#define g_crosshair (g_data.g_crosshair_)
#undef g_crosshairSetting
#define g_crosshairSetting (g_data.g_crosshairSetting_)
#undef g_crosshairTexture
#define g_crosshairTexture (g_data.g_crosshairTexture_)
#undef g_currentProfile
#define g_currentProfile (g_data.g_currentProfile_)
#undef g_currentStageName
#define g_currentStageName (g_data.g_currentStageName_)
#undef g_cursorBlinkTimer
#define g_cursorBlinkTimer (g_data.g_cursorBlinkTimer_)
#undef g_cursorPos
#define g_cursorPos (g_data.g_cursorPos_)
#undef g_cursorPosY
#define g_cursorPosY (g_data.g_cursorPosY_)
#undef g_dataDir
#define g_dataDir ((char *)g_data.g_dataDir_)
#undef g_debugValue
#define g_debugValue (g_data.g_debugValue_)
#undef g_defaultColour
#define g_defaultColour (g_data.g_defaultColour_)
#undef g_desktopDC
#define g_desktopDC (g_data.g_desktopDC_)
#undef g_desktopDepth
#define g_desktopDepth (g_data.g_desktopDepth_)
#undef g_desktopHeight
#define g_desktopHeight (g_data.g_desktopHeight_)
#undef g_desktopWidth
#define g_desktopWidth (g_data.g_desktopWidth_)
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
#define g_dikDown (g_data.g_dikDown_)
#undef g_dikEnter
#define g_dikEnter (g_data.g_dikEnter_)
#undef g_dikEscape
#define g_dikEscape (g_data.g_dikEscape_)
#undef g_dikEscape_2
#define g_dikEscape_2 (g_data.g_dikEscape_2_)
#undef g_dikF11
#define g_dikF11 (g_data.g_dikF11_)
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
#define g_dikLeft (g_data.g_dikLeft_)
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
#define g_dikRCtrl (g_data.g_dikRCtrl_)
#undef g_dikRShift
#define g_dikRShift (g_data.g_dikRShift_)
#undef g_dikRight
#define g_dikRight (g_data.g_dikRight_)
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
#define g_dikWheelDown (g_data.g_dikWheelDown_)
#undef g_dikWheelUp
#define g_dikWheelUp (g_data.g_dikWheelUp_)
#undef g_dikX
#define g_dikX (g_data.g_dikX_)
#undef g_dikZ_2
#define g_dikZ_2 (g_data.g_dikZ_2_)
#undef g_directInputMade
#define g_directInputMade (g_data.g_directInputMade_)
#undef g_directSound
#define g_directSound (g_data.g_directSound_)
#undef g_displayModeChanged
#define g_displayModeChanged (g_data.g_displayModeChanged_)
#undef g_displayModeLeft
#define g_displayModeLeft (g_data.g_displayModeLeft_)
#undef g_dpMaxBufferSize
#define g_dpMaxBufferSize (g_data.g_dpMaxBufferSize_)
#undef g_dpMaxQueueSize
#define g_dpMaxQueueSize (g_data.g_dpMaxQueueSize_)
#undef g_dpTimeout
#define g_dpTimeout (g_data.g_dpTimeout_)
#undef g_dplay
#define g_dplay (g_data.g_dplay_)
#undef g_dplayLobby
#define g_dplayLobby (g_data.g_dplayLobby_)
#undef g_dplaySessionCount
#define g_dplaySessionCount (g_data.g_dplaySessionCount_)
#undef g_dplaySessionList
#define g_dplaySessionList (g_data.g_dplaySessionList_)
#undef g_editOldProc
#define g_editOldProc (g_data.g_editOldProc_)
#undef g_editingAccountPassword
#define g_editingAccountPassword (g_data.g_editingAccountPassword_)
#undef g_editingArenaMessage
#define g_editingArenaMessage (g_data.g_editingArenaMessage_)
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
#define g_enteringMenus (g_data.g_enteringMenus_)
#undef g_errorCleanupHook
#define g_errorCleanupHook (g_data.g_errorCleanupHook_)
#undef g_errorLogging
#define g_errorLogging (g_data.g_errorLogging_)
#undef g_excludedKey
#define g_excludedKey (g_data.g_excludedKey_)
#undef g_fieldTabKey
#define g_fieldTabKey (g_data.g_fieldTabKey_)
#undef g_fovKeys
#define g_fovKeys (g_data.g_fovKeys_)
#undef g_fps
#define g_fps (g_data.g_fps_)
#undef g_fpsFrameClock
#define g_fpsFrameClock (g_data.g_fpsFrameClock_)
#undef g_fpsSecondSoFar
#define g_fpsSecondSoFar (g_data.g_fpsSecondSoFar_)
#undef g_fpsSecondStart
#define g_fpsSecondStart (g_data.g_fpsSecondStart_)
#undef g_fragLimit
#define g_fragLimit (g_data.g_fragLimit_)
#undef g_frameCounter40
#define g_frameCounter40 (g_data.g_frameCounter40_)
#undef g_frameRate
#define g_frameRate (g_data.g_frameRate_)
#undef g_freeCamHeight
#define g_freeCamHeight (g_data.g_freeCamHeight_)
#undef g_fullScreen
#define g_fullScreen (g_data.g_fullScreen_)
#undef g_gameCount
#define g_gameCount (g_data.g_gameCount_)
#undef g_gameListClickArmed
#define g_gameListClickArmed (g_data.g_gameListClickArmed_)
#undef g_gameListClickTimer
#define g_gameListClickTimer (g_data.g_gameListClickTimer_)
#undef g_gameListJoinClicked
#define g_gameListJoinClicked (g_data.g_gameListJoinClicked_)
#undef g_gameListLoaded
#define g_gameListLoaded (g_data.g_gameListLoaded_)
#undef g_gameListTop
#define g_gameListTop (g_data.g_gameListTop_)
#undef g_gameRunning
#define g_gameRunning (g_data.g_gameRunning_)
#undef g_gameServerAnswer
#define g_gameServerAnswer (g_data.g_gameServerAnswer_)
#undef g_gameServerAnswer15
#define g_gameServerAnswer15 (g_data.g_gameServerAnswer15_)
#undef g_gameServerPending
#define g_gameServerPending (g_data.g_gameServerPending_)
#undef g_gameServerReplyKind
#define g_gameServerReplyKind (g_data.g_gameServerReplyKind_)
#undef g_gameServerSocket
#define g_gameServerSocket (g_data.g_gameServerSocket_)
#undef g_gameServerState
#define g_gameServerState (g_data.g_gameServerState_)
#undef g_gameServerStatus
#define g_gameServerStatus (g_data.g_gameServerStatus_)
#undef g_glCachedState
#define g_glCachedState (g_data.g_glCachedState_)
#undef g_glColourBits
#define g_glColourBits (g_data.g_glColourBits_)
#undef g_glDepthBits
#define g_glDepthBits (g_data.g_glDepthBits_)
#undef g_glHeight
#define g_glHeight (g_data.g_glHeight_)
#undef g_glWidth
#define g_glWidth (g_data.g_glWidth_)
#undef g_hInstance
#define g_hInstance (g_data.g_hInstance_)
#undef g_hangulLeadGlyph
#define g_hangulLeadGlyph (g_data.g_hangulLeadGlyph_)
#undef g_hangulTailGlyph
#define g_hangulTailGlyph (g_data.g_hangulTailGlyph_)
#undef g_hangulVowelGlyph
#define g_hangulVowelGlyph (g_data.g_hangulVowelGlyph_)
#undef g_headDetectionAngle
#define g_headDetectionAngle (g_data.g_headDetectionAngle_)
#undef g_headDetectionRange
#define g_headDetectionRange (g_data.g_headDetectionRange_)
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
#define g_inputFont (g_data.g_inputFont_)
#undef g_insertCdMessage
#define g_insertCdMessage (g_data.g_insertCdMessage_)
#undef g_instanceGuid
#define g_instanceGuid (g_data.g_instanceGuid_)
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
#define g_itemBonusShield (g_data.g_itemBonusShield_)
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
#define g_keepCameraAsked (g_data.g_keepCameraAsked_)
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
#define g_lastPanel (g_data.g_lastPanel_)
#undef g_lastTime
#define g_lastTime (g_data.g_lastTime_)
#undef g_launchMessage
#define g_launchMessage (g_data.g_launchMessage_)
#undef g_legsMaxWeight
#define g_legsMaxWeight (g_data.g_legsMaxWeight_)
#undef g_legsSpeedCorrection
#define g_legsSpeedCorrection (g_data.g_legsSpeedCorrection_)
#undef g_legsWeight
#define g_legsWeight (g_data.g_legsWeight_)
#undef g_listRefreshPeriod
#define g_listRefreshPeriod (g_data.g_listRefreshPeriod_)
#undef g_loadStep
#define g_loadStep (g_data.g_loadStep_)
#undef g_lobbyBlinkClock
#define g_lobbyBlinkClock (g_data.g_lobbyBlinkClock_)
#undef g_lobbyConnectStatus
#define g_lobbyConnectStatus (g_data.g_lobbyConnectStatus_)
#undef g_lobbyConnectionBlock
#define g_lobbyConnectionBlock (g_data.g_lobbyConnectionBlock_)
#undef g_lobbyConnectionOpen
#define g_lobbyConnectionOpen (g_data.g_lobbyConnectionOpen_)
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
#define g_lobbyReplyKind (g_data.g_lobbyReplyKind_)
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
#define g_localPlayerData (g_data.g_localPlayerData_)
#undef g_localPlayerId
#define g_localPlayerId (g_data.g_localPlayerId_)
#undef g_logHook
#define g_logHook (g_data.g_logHook_)
#undef g_loginFormBottom
#define g_loginFormBottom (g_data.g_loginFormBottom_)
#undef g_loginFormLeft
#define g_loginFormLeft (g_data.g_loginFormLeft_)
#undef g_loginToSend
#define g_loginToSend (g_data.g_loginToSend_)
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
#define g_mapEntry22On (g_data.g_mapEntry22On_)
#undef g_mapEntry23On
#define g_mapEntry23On (g_data.g_mapEntry23On_)
#undef g_mapEntry24On
#define g_mapEntry24On (g_data.g_mapEntry24On_)
#undef g_mapListFlaggedCount
#define g_mapListFlaggedCount (g_data.g_mapListFlaggedCount_)
#undef g_mapListMade
#define g_mapListMade (g_data.g_mapListMade_)
#undef g_mapListOpen
#define g_mapListOpen (g_data.g_mapListOpen_)
#undef g_mapMissing
#define g_mapMissing (g_data.g_mapMissing_)
#undef g_mapPreviewChanged
#define g_mapPreviewChanged (g_data.g_mapPreviewChanged_)
#undef g_mapPreviewTexture
#define g_mapPreviewTexture (g_data.g_mapPreviewTexture_)
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
#define g_matchChatCaretX (g_data.g_matchChatCaretX_)
#undef g_matchChatCaretY
#define g_matchChatCaretY (g_data.g_matchChatCaretY_)
#undef g_matchEndedByServer
#define g_matchEndedByServer (g_data.g_matchEndedByServer_)
#undef g_matchEndedByUser
#define g_matchEndedByUser (g_data.g_matchEndedByUser_)
#undef g_matchLogWritten
#define g_matchLogWritten (g_data.g_matchLogWritten_)
#undef g_matchMode
#define g_matchMode (g_data.g_matchMode_)
#undef g_matchRunning
#define g_matchRunning (g_data.g_matchRunning_)
#undef g_mciCallback
#define g_mciCallback (g_data.g_mciCallback_)
#undef g_mciDevice
#define g_mciDevice (g_data.g_mciDevice_)
#undef g_mciFrom
#define g_mciFrom (g_data.g_mciFrom_)
#undef g_mciTo
#define g_mciTo (g_data.g_mciTo_)
#undef g_mechBoosterEnergy
#define g_mechBoosterEnergy (g_data.g_mechBoosterEnergy_)
#undef g_mechBoosterRecharge
#define g_mechBoosterRecharge (g_data.g_mechBoosterRecharge_)
#undef g_mechChanged
#define g_mechChanged (g_data.g_mechChanged_)
#undef g_mechDetectionRange
#define g_mechDetectionRange (g_data.g_mechDetectionRange_)
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
#define g_menuCamX (g_data.g_menuCamX_)
#undef g_menuCamZ
#define g_menuCamZ (g_data.g_menuCamZ_)
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
#define g_menuFrameCount (g_data.g_menuFrameCount_)
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
#define g_menuTunnelTexture (g_data.g_menuTunnelTexture_)
#undef g_messageBoxArgs
#define g_messageBoxArgs (g_data.g_messageBoxArgs_)
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
#define g_missionPreviewDue (g_data.g_missionPreviewDue_)
#undef g_missionSelectLeft
#define g_missionSelectLeft (g_data.g_missionSelectLeft_)
#undef g_missionSelectTop
#define g_missionSelectTop (g_data.g_missionSelectTop_)
#undef g_missionShown
#define g_missionShown (g_data.g_missionShown_)
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
#define g_musicVolumeSetting (g_data.g_musicVolumeSetting_)
#undef g_netAccountBuffer
#define g_netAccountBuffer (g_data.g_netAccountBuffer_)
#undef g_netBlockSize
#define g_netBlockSize (g_data.g_netBlockSize_)
#undef g_netChatMessageKind
#define g_netChatMessageKind (g_data.g_netChatMessageKind_)
#undef g_netChatMessageText
#define g_netChatMessageText (g_data.g_netChatMessageText_)
#undef g_netChatMessageWord1
#define g_netChatMessageWord1 (g_data.g_netChatMessageWord1_)
#undef g_netChatMessageWord2
#define g_netChatMessageWord2 (g_data.g_netChatMessageWord2_)
#undef g_netClaimedSlot
#define g_netClaimedSlot (g_data.g_netClaimedSlot_)
#undef g_netConnected
#define g_netConnected (g_data.g_netConnected_)
#undef g_netHostGone
#define g_netHostGone (g_data.g_netHostGone_)
#undef g_netInfoPacket
#define g_netInfoPacket (g_data.g_netInfoPacket_)
#undef g_netJoinMessage
#define g_netJoinMessage (g_data.g_netJoinMessage_)
#undef g_netKindWord
#define g_netKindWord (g_data.g_netKindWord_)
#undef g_netLastRequest
#define g_netLastRequest (g_data.g_netLastRequest_)
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
#define g_openLoginName (g_data.g_openLoginName_)
#undef g_otherModeHeight
#define g_otherModeHeight (g_data.g_otherModeHeight_)
#undef g_otherModeWidth
#define g_otherModeWidth (g_data.g_otherModeWidth_)
#undef g_panelGlow
#define g_panelGlow (g_data.g_panelGlow_)
#undef g_panelGlowStep
#define g_panelGlowStep (g_data.g_panelGlowStep_)
#undef g_panelHovered
#define g_panelHovered (g_data.g_panelHovered_)
#undef g_partBox0Offset
#define g_partBox0Offset (g_data.g_partBox0Offset_)
#undef g_partBox1Offset
#define g_partBox1Offset (g_data.g_partBox1Offset_)
#undef g_partBox2Offset
#define g_partBox2Offset (g_data.g_partBox2Offset_)
#undef g_partBox3Offset
#define g_partBox3Offset (g_data.g_partBox3Offset_)
#undef g_partBox4Offset
#define g_partBox4Offset (g_data.g_partBox4Offset_)
#undef g_partBox5Offset
#define g_partBox5Offset (g_data.g_partBox5Offset_)
#undef g_penFontNeverSet
#define g_penFontNeverSet (g_data.g_penFontNeverSet_)
#undef g_penFontTexture
#define g_penFontTexture (g_data.g_penFontTexture_)
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
#define g_pixelFormatFilled (g_data.g_pixelFormatFilled_)
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
#define g_primarySoundBuffer (g_data.g_primarySoundBuffer_)
#undef g_profileColour
#define g_profileColour ((u32 *)g_data.g_profileColour_)
#undef g_profileCount
#define g_profileCount (g_data.g_profileCount_)
#undef g_profileDialogOpen
#define g_profileDialogOpen (g_data.g_profileDialogOpen_)
#undef g_profileFrameAlpha
#define g_profileFrameAlpha (g_data.g_profileFrameAlpha_)
#undef g_profileFrameStep
#define g_profileFrameStep (g_data.g_profileFrameStep_)
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
#define g_profilePageRight (g_data.g_profilePageRight_)
#undef g_profilePageTop
#define g_profilePageTop (g_data.g_profilePageTop_)
#undef g_profileProgressSaved
#define g_profileProgressSaved (g_data.g_profileProgressSaved_)
#undef g_profileRowClicked
#define g_profileRowClicked (g_data.g_profileRowClicked_)
#undef g_profileScreenReady
#define g_profileScreenReady (g_data.g_profileScreenReady_)
#undef g_progressWentUp
#define g_progressWentUp (g_data.g_progressWentUp_)
#undef g_projMode
#define g_projMode (g_data.g_projMode_)
#undef g_ptxBitPos
#define g_ptxBitPos (g_data.g_ptxBitPos_)
#undef g_ptxLastDc
#define g_ptxLastDc (g_data.g_ptxLastDc_)
#undef g_ptxTable
#define g_ptxTable (g_data.g_ptxTable_)
#undef g_ptxTablesReady
#define g_ptxTablesReady (g_data.g_ptxTablesReady_)
#undef g_quitAsked
#define g_quitAsked (g_data.g_quitAsked_)
#undef g_randPos
#define g_randPos (g_data.g_randPos_)
#undef g_rankingFirst
#define g_rankingFirst (g_data.g_rankingFirst_)
#undef g_rankingHaveList
#define g_rankingHaveList (g_data.g_rankingHaveList_)
#undef g_rankingLast
#define g_rankingLast (g_data.g_rankingLast_)
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
#define g_retypePassword (g_data.g_retypePassword_)
#undef g_roomAnswerAwaited
#define g_roomAnswerAwaited (g_data.g_roomAnswerAwaited_)
#undef g_roomAwaitingServer
#define g_roomAwaitingServer (g_data.g_roomAwaitingServer_)
#undef g_roomBright
#define g_roomBright ((u32 *)g_data.g_roomBright_)
#undef g_roomChatting
#define g_roomChatting (g_data.g_roomChatting_)
#undef g_roomConnected
#define g_roomConnected (g_data.g_roomConnected_)
#undef g_roomCustom
#define g_roomCustom (g_data.g_roomCustom_)
#undef g_roomDialogOpen
#define g_roomDialogOpen (g_data.g_roomDialogOpen_)
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
#undef g_roomListCount
#define g_roomListCount (g_data.g_roomListCount_)
#undef g_roomListDistanceLimit
#define g_roomListDistanceLimit (g_data.g_roomListDistanceLimit_)
#undef g_roomListPage
#define g_roomListPage (g_data.g_roomListPage_)
#undef g_roomListPages
#define g_roomListPages (g_data.g_roomListPages_)
#undef g_roomListPrev
#define g_roomListPrev (g_data.g_roomListPrev_)
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
#define g_roomTunnelDepth (g_data.g_roomTunnelDepth_)
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
#undef g_serverAnswerIn
#define g_serverAnswerIn (g_data.g_serverAnswerIn_)
#undef g_serverConnected
#define g_serverConnected (g_data.g_serverConnected_)
#undef g_serverConnectionState
#define g_serverConnectionState (g_data.g_serverConnectionState_)
#undef g_serverListCount
#define g_serverListCount (g_data.g_serverListCount_)
#undef g_serverPingCount
#define g_serverPingCount (g_data.g_serverPingCount_)
#undef g_serverPort
#define g_serverPort (g_data.g_serverPort_)
#undef g_serverReplyKind
#define g_serverReplyKind (g_data.g_serverReplyKind_)
#undef g_serverSearching
#define g_serverSearching (g_data.g_serverSearching_)
#undef g_serviceProviderCount
#define g_serviceProviderCount (g_data.g_serviceProviderCount_)
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
#define g_setupPage (g_data.g_setupPage_)
#undef g_setupPanelMoving
#define g_setupPanelMoving (g_data.g_setupPanelMoving_)
#undef g_setupPanelPos
#define g_setupPanelPos (g_data.g_setupPanelPos_)
#undef g_setupPressed
#define g_setupPressed (g_data.g_setupPressed_)
#undef g_setupPressedClock
#define g_setupPressedClock (g_data.g_setupPressedClock_)
#undef g_setupResolution
#define g_setupResolution (g_data.g_setupResolution_)
#undef g_setupSoundLeft
#define g_setupSoundLeft (g_data.g_setupSoundLeft_)
#undef g_setupSoundRight
#define g_setupSoundRight (g_data.g_setupSoundRight_)
#undef g_setupTunnelAlpha
#define g_setupTunnelAlpha (g_data.g_setupTunnelAlpha_)
#undef g_setupTunnelDepth
#define g_setupTunnelDepth (g_data.g_setupTunnelDepth_)
#undef g_showCmd
#define g_showCmd (g_data.g_showCmd_)
#undef g_skirmishDrawBackground
#define g_skirmishDrawBackground (g_data.g_skirmishDrawBackground_)
#undef g_skirmishInfoCount
#define g_skirmishInfoCount (g_data.g_skirmishInfoCount_)
#undef g_slotTakenFlag
#define g_slotTakenFlag (g_data.g_slotTakenFlag_)
#undef g_sound3D
#define g_sound3D (g_data.g_sound3D_)
#undef g_soundBaseVolume
#define g_soundBaseVolume (g_data.g_soundBaseVolume_)
#undef g_soundOn
#define g_soundOn (g_data.g_soundOn_)
#undef g_soundSwitch1
#define g_soundSwitch1 (g_data.g_soundSwitch1_)
#undef g_soundToggle6
#define g_soundToggle6 (g_data.g_soundToggle6_)
#undef g_soundToggle7
#define g_soundToggle7 (g_data.g_soundToggle7_)
#undef g_soundVolume
#define g_soundVolume (g_data.g_soundVolume_)
#undef g_startTicks
#define g_startTicks (g_data.g_startTicks_)
#undef g_startedByLauncher
#define g_startedByLauncher (g_data.g_startedByLauncher_)
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
#define g_storedConnection (g_data.g_storedConnection_)
#undef g_textBottom
#define g_textBottom (g_data.g_textBottom_)
#undef g_textColour
#define g_textColour ((Colour *)g_data.g_textColour_)
#undef g_textEndX
#define g_textEndX (g_data.g_textEndX_)
#undef g_textEndY
#define g_textEndY (g_data.g_textEndY_)
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
#define g_timerFirstCall (g_data.g_timerFirstCall_)
#undef g_timerHigh
#define g_timerHigh (g_data.g_timerHigh_)
#undef g_timerRepeatCount
#define g_timerRepeatCount (g_data.g_timerRepeatCount_)
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
#define g_tunnelRings (g_data.g_tunnelRings_)
#undef g_typedArenaName
#define g_typedArenaName (g_data.g_typedArenaName_)
#undef g_typedArenaName4
#define g_typedArenaName4 (g_data.g_typedArenaName4_)
#undef g_typedLength
#define g_typedLength (g_data.g_typedLength_)
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
#define g_typingGameName (g_data.g_typingGameName_)
#undef g_typingGamePassword
#define g_typingGamePassword (g_data.g_typingGamePassword_)
#undef g_typingRoomName
#define g_typingRoomName (g_data.g_typingRoomName_)
#undef g_typingRoomPassword
#define g_typingRoomPassword (g_data.g_typingRoomPassword_)
#undef g_undoDepth
#define g_undoDepth (g_data.g_undoDepth_)
#undef g_unlockedLevel
#define g_unlockedLevel (g_data.g_unlockedLevel_)
#undef g_unusedArmcMoveWord
#define g_unusedArmcMoveWord (g_data.g_unusedArmcMoveWord_)
#undef g_unusedArmcWord1
#define g_unusedArmcWord1 (g_data.g_unusedArmcWord1_)
#undef g_unusedArmcWord2
#define g_unusedArmcWord2 (g_data.g_unusedArmcWord2_)
#undef g_unusedArmcWord3
#define g_unusedArmcWord3 (g_data.g_unusedArmcWord3_)
#undef g_unusedArmcWord4
#define g_unusedArmcWord4 (g_data.g_unusedArmcWord4_)
#undef g_unusedDplayWord1
#define g_unusedDplayWord1 (g_data.g_unusedDplayWord1_)
#undef g_unusedDplayWord2
#define g_unusedDplayWord2 (g_data.g_unusedDplayWord2_)
#undef g_unusedDplayWord3
#define g_unusedDplayWord3 (g_data.g_unusedDplayWord3_)
#undef g_unusedDplayWord4
#define g_unusedDplayWord4 (g_data.g_unusedDplayWord4_)
#undef g_unusedInitWord
#define g_unusedInitWord (g_data.g_unusedInitWord_)
#undef g_unusedKeyTable2Flags
#define g_unusedKeyTable2Flags (g_data.g_unusedKeyTable2Flags_)
#undef g_unusedKeyTable2Word0
#define g_unusedKeyTable2Word0 (g_data.g_unusedKeyTable2Word0_)
#undef g_unusedKeyTable2Word1
#define g_unusedKeyTable2Word1 (g_data.g_unusedKeyTable2Word1_)
#undef g_unusedKeyTable2Word2
#define g_unusedKeyTable2Word2 (g_data.g_unusedKeyTable2Word2_)
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
#define g_unusedNetCloseWord (g_data.g_unusedNetCloseWord_)
#undef g_unusedPingWord1
#define g_unusedPingWord1 (g_data.g_unusedPingWord1_)
#undef g_unusedPingWord2
#define g_unusedPingWord2 (g_data.g_unusedPingWord2_)
#undef g_unusedPlayerRecord26
#define g_unusedPlayerRecord26 (g_data.g_unusedPlayerRecord26_)
#undef g_unusedPlayerRecord2a
#define g_unusedPlayerRecord2a (g_data.g_unusedPlayerRecord2a_)
#undef g_unusedPostMatchFlag
#define g_unusedPostMatchFlag (g_data.g_unusedPostMatchFlag_)
#undef g_unusedProfileCameraWord
#define g_unusedProfileCameraWord (g_data.g_unusedProfileCameraWord_)
#undef g_unusedReplayListWord1
#define g_unusedReplayListWord1 (g_data.g_unusedReplayListWord1_)
#undef g_unusedReplayListWord2
#define g_unusedReplayListWord2 (g_data.g_unusedReplayListWord2_)
#undef g_unusedRoomListWord
#define g_unusedRoomListWord (g_data.g_unusedRoomListWord_)
#undef g_unusedRoomWord
#define g_unusedRoomWord (g_data.g_unusedRoomWord_)
#undef g_unusedSessionWord
#define g_unusedSessionWord (g_data.g_unusedSessionWord_)
#undef g_unusedStartupWord1
#define g_unusedStartupWord1 (g_data.g_unusedStartupWord1_)
#undef g_unusedStartupWord2
#define g_unusedStartupWord2 (g_data.g_unusedStartupWord2_)
#undef g_unusedStartupWord3
#define g_unusedStartupWord3 (g_data.g_unusedStartupWord3_)
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
#define g_viewFar (g_data.g_viewFar_)
#undef g_viewFov
#define g_viewFov (g_data.g_viewFov_)
#undef g_viewNear
#define g_viewNear (g_data.g_viewNear_)
#undef g_viewedPartIndex
#define g_viewedPartIndex (g_data.g_viewedPartIndex_)
#undef g_viewedPartKind
#define g_viewedPartKind (g_data.g_viewedPartKind_)
#undef g_volumeSetting
#define g_volumeSetting (g_data.g_volumeSetting_)
#undef g_watchChatOpen
#define g_watchChatOpen (g_data.g_watchChatOpen_)
#undef g_watchedSlot
#define g_watchedSlot (g_data.g_watchedSlot_)
#undef g_writeMatchLog
#define g_writeMatchLog (g_data.g_writeMatchLog_)
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
