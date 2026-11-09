/* layout_names.h (tools/mkdatasrc.py): in AxisRC.exe (AXIS_DIRECT) the named globals that are members of
   g_rdata / g_data (src/data/layout.h) as those members; the others stay GAME_VAR (src/globals.h), which IMG()
   routes to the same place */
#pragma once
#include "layout.h"
extern struct GameRdata g_rdata;
extern struct GameData g_data;
#ifdef AXIS_64   /* (the 64-bit build: both at their original addresses in the game's address space) */
#define g_rdata (*(struct GameRdata *)(g_arena + 0x4a9000))
#define g_data (*(struct GameData *)(g_arena + 0x4ad000))
#endif
#include "split.h"   /* (the variables split out of g_data) */
#undef g_accountForm
#define g_accountForm ((u8 *)g_accountForm_v)
#undef g_accountOldPassword
#define g_accountOldPassword ((char *)g_data.g_accountOldPassword_)
#undef g_accountPacket
#define g_accountPacket (*(APTR(AccountPacket) *)g_accountPacket_v)
#undef g_accountPanelBottom
#define g_accountPanelBottom (*(int *)g_accountPanelBottom_v)
#undef g_accountPanelLeft
#define g_accountPanelLeft (*(int *)g_accountPanelLeft_v)
#undef g_accountPanelRight
#define g_accountPanelRight (*(int *)g_accountPanelRight_v)
#undef g_accountPanelTop
#define g_accountPanelTop (*(int *)g_accountPanelTop_v)
#undef g_accountRankAwaited
#define g_accountRankAwaited (*(int *)g_accountRankAwaited_v)
#undef g_accountRankDue
#define g_accountRankDue (*(int *)g_accountRankDue_v)
#undef g_accountRects
#define g_accountRects ((int *)g_accountRects_v)
#undef g_arenaBright
#define g_arenaBright ((float *)g_arenaBright_v)
#undef g_arenaCameraMode
#define g_arenaCameraMode (*(int *)g_arenaCameraMode_v)
#undef g_arenaCorporation
#define g_arenaCorporation (*(int *)g_arenaCorporation_v)
#undef g_arenaCustomize
#define g_arenaCustomize (*(int *)g_arenaCustomize_v)
#undef g_arenaDialogBoxRects
#define g_arenaDialogBoxRects ((int *)g_arenaDialogBoxRects_v)
#undef g_arenaDim
#define g_arenaDim ((float *)g_arenaDim_v)
#undef g_arenaFileFragLimit
#define g_arenaFileFragLimit (g_data.g_arenaFileFragLimit_)
#undef g_arenaFileGameType
#define g_arenaFileGameType (g_data.g_arenaFileGameType_)
#undef g_arenaFileMap
#define g_arenaFileMap (g_data.g_arenaFileMap_)
#undef g_arenaFilePassword
#define g_arenaFilePassword (g_data.g_arenaFilePassword_)
#undef g_arenaFilePassword4
#define g_arenaFilePassword4 (g_data.g_arenaFilePassword4_)
#undef g_arenaFilePlayers
#define g_arenaFilePlayers (g_data.g_arenaFilePlayers_)
#undef g_arenaFileSecret
#define g_arenaFileSecret (g_data.g_arenaFileSecret_)
#undef g_arenaFileTimeLimit
#define g_arenaFileTimeLimit (g_data.g_arenaFileTimeLimit_)
#undef g_arenaFragLimit
#define g_arenaFragLimit (*(u8 *)((u8 *)g_arenaName_v + 0x24))
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
#undef g_arenaGameType
#define g_arenaGameType (*(u8 *)((u8 *)g_arenaName_v + 0x23))
#undef g_arenaInfoPacket
#define g_arenaInfoPacket (*(APTR(u8) *)g_arenaInfoPacket_v)
#undef g_arenaJoinNeedsPassword
#define g_arenaJoinNeedsPassword (*(int *)g_arenaJoinNeedsPassword_v)
#undef g_arenaJoinPassword
#define g_arenaJoinPassword (g_data.g_arenaJoinPassword_)
#undef g_arenaJoinPassword4
#define g_arenaJoinPassword4 (g_data.g_arenaJoinPassword4_)
#undef g_arenaKeptCamX
#define g_arenaKeptCamX (*(float *)g_arenaKeptCamX_v)
#undef g_arenaKeptCamY
#define g_arenaKeptCamY (*(float *)g_arenaKeptCamY_v)
#undef g_arenaKeptCamZ
#define g_arenaKeptCamZ (*(float *)g_arenaKeptCamZ_v)
#undef g_arenaKeptLookX
#define g_arenaKeptLookX (*(float *)g_arenaKeptLookX_v)
#undef g_arenaKeptLookY
#define g_arenaKeptLookY (*(float *)g_arenaKeptLookY_v)
#undef g_arenaKeptLookZ
#define g_arenaKeptLookZ (*(float *)g_arenaKeptLookZ_v)
#undef g_arenaLanListBuilt
#define g_arenaLanListBuilt (*(int *)g_arenaLanListBuilt_v)
#undef g_arenaListClickArmed
#define g_arenaListClickArmed (*(int *)g_arenaListClickArmed_v)
#undef g_arenaListClickTimer
#define g_arenaListClickTimer (*(float *)g_arenaListClickTimer_v)
#undef g_arenaListFromServer
#define g_arenaListFromServer (*(int *)g_arenaListFromServer_v)
#undef g_arenaListPlayers
#define g_arenaListPlayers (*(int *)g_arenaListPlayers_v)
#undef g_arenaListRefreshTimer
#define g_arenaListRefreshTimer (*(float *)g_arenaListRefreshTimer_v)
#undef g_arenaListRequest
#define g_arenaListRequest (*(APTR(u32) *)g_arenaListRequest_v)
#undef g_arenaLocked
#define g_arenaLocked (*(u8 *)((u8 *)g_arenaName_v + 0x2e))
#undef g_arenaMap
#define g_arenaMap (*(signed char *)((u8 *)g_arenaName_v + 0x20))
#undef g_arenaMaxPlayers
#define g_arenaMaxPlayers (*(u8 *)((u8 *)g_arenaName_v + 0x21))
#undef g_arenaMenuTextures
#define g_arenaMenuTextures ((int *)g_arenaMenuTextures_v)
#undef g_arenaName
#define g_arenaName ((char *)g_arenaName_v)
#undef g_arenaOnOff
#define g_arenaOnOff ((char *)g_arenaOnOff_v)
#undef g_arenaPacket
#define g_arenaPacket (*(APTR(ArenaRecord) *)g_arenaPacket_v)
#undef g_arenaPassword
#define g_arenaPassword (*(u32 *)((u8 *)g_arenaName_v + 0x26))
#undef g_arenaPassword4
#define g_arenaPassword4 (*(u32 *)((u8 *)g_arenaName_v + 0x2a))
#undef g_arenaPlayerName
#define g_arenaPlayerName ((char *)g_data.g_arenaPlayerName_)
#undef g_arenaRotation
#define g_arenaRotation (*(u8 *)((u8 *)g_arenaName_v + 0x22))
#undef g_arenaTimeLimit
#define g_arenaTimeLimit (*(u8 *)((u8 *)g_arenaName_v + 0x25))
#undef g_arenaTunnelDepth
#define g_arenaTunnelDepth (*(float *)g_arenaTunnelDepth_v)
#undef g_arenaUpdateNotice
#define g_arenaUpdateNotice (*(int *)g_arenaUpdateNotice_v)
#undef g_arenaUpdateNoticeRects
#define g_arenaUpdateNoticeRects ((int *)g_arenaUpdateNoticeRects_v)
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
#undef g_armcBright
#define g_armcBright ((float *)g_armcBright_v)
#undef g_armcCameraBox
#define g_armcCameraBox ((u32 *)g_armcCameraBox_v)
#undef g_armcCameraTravelling
#define g_armcCameraTravelling (*(int *)g_armcCameraTravelling_v)
#undef g_armcColourRects
#define g_armcColourRects ((int *)g_armcColourRects_v)
#undef g_armcColourSlot
#define g_armcColourSlot (*(int *)g_armcColourSlot_v)
#undef g_armcColours
#define g_armcColours ((float *)g_armcColours_v)
#undef g_armcCursor
#define g_armcCursor (*(int *)g_armcCursor_v)
#undef g_armcDim
#define g_armcDim ((float *)g_armcDim_v)
#undef g_armcFrom
#define g_armcFrom (*(int *)g_armcFrom_v)
#undef g_armcHideInterface
#define g_armcHideInterface (*(int *)g_armcHideInterface_v)
#undef g_armcLeaving
#define g_armcLeaving (*(int *)g_armcLeaving_v)
#undef g_armcLevel
#define g_armcLevel (*(int *)g_armcLevel_v)
#undef g_armcMode
#define g_armcMode (*(int *)g_armcMode_v)
#undef g_armcPageBottom
#define g_armcPageBottom (*(int *)g_armcPageBottom_v)
#undef g_armcPageLeft
#define g_armcPageLeft (*(int *)g_armcPageLeft_v)
#undef g_armcPageRight
#define g_armcPageRight (*(int *)g_armcPageRight_v)
#undef g_armcPageTop
#define g_armcPageTop (*(int *)g_armcPageTop_v)
#undef g_armcPanelDepth
#define g_armcPanelDepth (*(float *)((u8 *)g_armcCameraBox_v + 0x88))
#undef g_armcPartSlot
#define g_armcPartSlot (*(int *)g_armcPartSlot_v)
#undef g_armcParts
#define g_armcParts ((int *)g_armcParts_v)
#undef g_armcPartsPageRects
#define g_armcPartsPageRects ((int *)g_armcPartsPageRects_v)
#undef g_armcPreview
#define g_armcPreview (*(int *)g_armcPreview_v)
#undef g_armcSessionDue
#define g_armcSessionDue (*(int *)g_armcSessionDue_v)
#undef g_armcSessionMade
#define g_armcSessionMade (*(int *)g_armcSessionMade_v)
#undef g_armcSlot
#define g_armcSlot (*(int *)g_armcSlot_v)
#undef g_armcSlotChanged
#define g_armcSlotChanged (*(int *)g_armcSlotChanged_v)
#undef g_armcSlotItems
#define g_armcSlotItems ((int *)g_armcSlotItems_v)
#undef g_armcSpin
#define g_armcSpin (*(int *)g_armcSpin_v)
#undef g_armcState
#define g_armcState (*(int *)g_armcState_v)
#undef g_armcUnusedFlag
#define g_armcUnusedFlag (*(int *)g_armcUnusedFlag_v)
#undef g_armcViewPoints
#define g_armcViewPoints ((float *)g_armcViewPoints_v)
#undef g_armcViewedPartTexture
#define g_armcViewedPartTexture (*(int *)((u8 *)g_slotTextures_v + 0x18))
#undef g_armcWeaponsPageRects
#define g_armcWeaponsPageRects ((int *)g_armcWeaponsPageRects_v)
#undef g_armsFcsLevel
#define g_armsFcsLevel (*(int *)((u8 *)g_armsStats_v + 0x0))
#undef g_armsStats
#define g_armsStats ((int *)g_armsStats_v)
#undef g_armsWeight
#define g_armsWeight (*(float *)g_armsWeight_v)
#undef g_asyncKeySeen
#define g_asyncKeySeen ((int *)g_asyncKeySeen_v)
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
#define g_bitStream (*(APTR(const u8) *)g_bitStream_v)
#undef g_boosterActiveTime
#define g_boosterActiveTime (*(float *)((u8 *)g_boosterStats_v + 0x4))
#undef g_boosterCount
#define g_boosterCount (*(int *)g_boosterCount_v)
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
#undef g_briefingClock
#define g_briefingClock (*(float *)g_briefingClock_v)
#undef g_briefingDone
#define g_briefingDone (*(int *)g_briefingDone_v)
#undef g_briefingEnd
#define g_briefingEnd (*(int *)g_briefingEnd_v)
#undef g_briefingPage
#define g_briefingPage (*(int *)g_briefingPage_v)
#undef g_briefingPageStarts
#define g_briefingPageStarts ((int *)g_data.g_briefingPageStarts_)
#undef g_briefingRects
#define g_briefingRects ((int *)g_briefingRects_v)
#undef g_briefingShown
#define g_briefingShown (*(int *)g_briefingShown_v)
#undef g_briefingSource
#define g_briefingSource (*(APTR(u8) *)g_briefingSource_v)
#undef g_briefingStart
#define g_briefingStart (*(int *)g_briefingStart_v)
#undef g_briefingText
#define g_briefingText ((char *)g_briefingText_v)
#undef g_buttonTexture
#define g_buttonTexture (*(int *)g_buttonTexture_v)
#undef g_cageTexture
#define g_cageTexture (*(int *)g_cageTexture_v)
#undef g_camAim0X
#define g_camAim0X (*(float *)((u8 *)g_camAims_v + 0x0))
#undef g_camAim0Y
#define g_camAim0Y (*(float *)((u8 *)g_camAims_v + 0x4))
#undef g_camAim0Z
#define g_camAim0Z (*(float *)((u8 *)g_camAims_v + 0x8))
#undef g_camAim1X
#define g_camAim1X (*(float *)((u8 *)g_camAims_v + 0x10))
#undef g_camAim1Y
#define g_camAim1Y (*(float *)((u8 *)g_camAims_v + 0x14))
#undef g_camAim1Z
#define g_camAim1Z (*(float *)((u8 *)g_camAims_v + 0x18))
#undef g_camAim2X
#define g_camAim2X (*(float *)((u8 *)g_camAims_v + 0x20))
#undef g_camAim2Y
#define g_camAim2Y (*(float *)((u8 *)g_camAims_v + 0x24))
#undef g_camAim2Z
#define g_camAim2Z (*(float *)((u8 *)g_camAims_v + 0x28))
#undef g_camAims
#define g_camAims ((float *)g_camAims_v)
#undef g_camPoint0X
#define g_camPoint0X (*(float *)((u8 *)g_camPoints_v + 0x0))
#undef g_camPoint0Y
#define g_camPoint0Y (*(float *)((u8 *)g_camPoints_v + 0x4))
#undef g_camPoint0Z
#define g_camPoint0Z (*(float *)((u8 *)g_camPoints_v + 0x8))
#undef g_camPoint1X
#define g_camPoint1X (*(float *)((u8 *)g_camPoints_v + 0x10))
#undef g_camPoint1Z
#define g_camPoint1Z (*(float *)((u8 *)g_camPoints_v + 0x18))
#undef g_camPoint2X
#define g_camPoint2X (*(float *)((u8 *)g_camPoints_v + 0x20))
#undef g_camPoint2Y
#define g_camPoint2Y (*(float *)((u8 *)g_camPoints_v + 0x24))
#undef g_camPoint2Z
#define g_camPoint2Z (*(float *)((u8 *)g_camPoints_v + 0x28))
#undef g_camPoints
#define g_camPoints ((float *)g_camPoints_v)
#undef g_catalogueFile
#define g_catalogueFile (*(APTR(const char) *)g_catalogueFile_v)
#undef g_cfgLinearFilter
#define g_cfgLinearFilter (*(u32 *)((u8 *)g_graphicSettings_v + 0xc))
#undef g_cfgMipmaps
#define g_cfgMipmaps (*(u32 *)((u8 *)g_graphicSettings_v + 0x10))
#undef g_cfgPlayerName
#define g_cfgPlayerName ((char *)g_data.g_cfgPlayerName_)
#undef g_cfgSimpleMenu
#define g_cfgSimpleMenu (*(int *)((u8 *)g_graphicSettings_v + 0x18))
#undef g_characterProfiles
#define g_characterProfiles ((CharacterProfile *)g_data.g_characterProfiles_)
#undef g_characterTexture
#define g_characterTexture (*(int *)g_characterTexture_v)
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
#undef g_clearColour
#define g_clearColour ((Colour *)g_clearColour_v)
#undef g_clockCheckQuits
#define g_clockCheckQuits (*(int *)g_clockCheckQuits_v)
#undef g_clockCheckSeconds
#define g_clockCheckSeconds (*(int *)g_clockCheckSeconds_v)
#undef g_clockCheckTick
#define g_clockCheckTick (*(u32 *)g_clockCheckTick_v)
#undef g_clockCheckTickSeconds
#define g_clockCheckTickSeconds (*(u32 *)g_clockCheckTickSeconds_v)
#undef g_clockLastTime
#define g_clockLastTime ((u16 *)g_clockLastTime_v)
#undef g_clockNow
#define g_clockNow (*(double *)((u8 *)g_timerClocks_v + 0x0))
#undef g_clockNowTime
#define g_clockNowTime ((u16 *)g_clockNowTime_v)
#undef g_codeColours
#define g_codeColours ((Colour *)g_data.g_codeColours_)
#undef g_colourDepthTexts
#define g_colourDepthTexts ((char *)g_colourDepthTexts_v)
#undef g_coloursChanged
#define g_coloursChanged (*(int *)g_coloursChanged_v)
#undef g_componentDatPath
#define g_componentDatPath (*(APTR(const char) *)g_componentDatPath_v)
#undef g_connectedServer
#define g_connectedServer (*(int *)g_connectedServer_v)
#undef g_connectionAwaited
#define g_connectionAwaited (*(int *)g_connectionAwaited_v)
#undef g_connectionCopy
#define g_connectionCopy (*(APTR(void) *)g_connectionCopy_v)
#undef g_connectionKind
#define g_connectionKind (*(int *)g_connectionKind_v)
#undef g_controls
#define g_controls ((int *)g_controls_v)
#undef g_controlsEdit
#define g_controlsEdit ((int *)g_controlsEdit_v)
#undef g_convertHangul
#define g_convertHangul (*(int *)g_convertHangul_v)
#undef g_cosTable
#define g_cosTable ((float *)g_cosTable_v)
#undef g_createArenaRects
#define g_createArenaRects ((int *)g_createArenaRects_v)
#undef g_crosshairEdit
#define g_crosshairEdit (*(int *)((u8 *)g_controlsEdit_v + 0x10c))
#undef g_crosshairName
#define g_crosshairName ((char *)g_crosshairName_v)
#undef g_crosshairSetting
#define g_crosshairSetting (*(int *)((u8 *)g_controls_v + 0x10c))
#undef g_crosshairTexture
#define g_crosshairTexture (*(int *)g_crosshairTexture_v)
#undef g_crtErrno
#define g_crtErrno (*(int *)g_crtErrno_v)
#undef g_crtStderr
#define g_crtStderr ((u8 *)g_data.g_crtStderr_)
#undef g_crtTenPowersDown
#define g_crtTenPowersDown ((u8 *)g_data.g_crtTenPowersDown_)
#undef g_crtTenPowersUp
#define g_crtTenPowersUp ((u8 *)g_data.g_crtTenPowersUp_)
#undef g_ctrlMenuTextures
#define g_ctrlMenuTextures ((int *)g_ctrlMenuTextures_v)
#undef g_currentProfile
#define g_currentProfile (*(int *)g_currentProfile_v)
#undef g_cursorBlinkTimer
#define g_cursorBlinkTimer (*(float *)g_cursorBlinkTimer_v)
#undef g_cursorFrame
#define g_cursorFrame (*(int *)g_cursorFrame_v)
#undef g_cursorFrameTime
#define g_cursorFrameTime (*(float *)g_cursorFrameTime_v)
#undef g_cursorPoint
#define g_cursorPoint ((int *)g_cursorPoint_v)
#undef g_cursorPosY
#define g_cursorPosY (*(int *)((u8 *)g_cursorPoint_v + 0x4))
#undef g_cursorTexture
#define g_cursorTexture (*(int *)g_cursorTexture_v)
#undef g_cursorX
#define g_cursorX (*(int *)((u8 *)g_cursorPoint_v + 0x0))
#undef g_dataDir
#define g_dataDir ((char *)g_dataDir_v)
#undef g_defaultColour
#define g_defaultColour (*(int *)g_defaultColour_v)
#undef g_defaultColours
#define g_defaultColours ((u32 *)g_defaultColours_v)
#undef g_deleteDialogBottom
#define g_deleteDialogBottom (*(int *)g_deleteDialogBottom_v)
#undef g_deleteDialogRects
#define g_deleteDialogRects ((int *)g_deleteDialogRects_v)
#undef g_deleteDialogRight
#define g_deleteDialogRight (*(int *)g_deleteDialogRight_v)
#undef g_deleteDialogX
#define g_deleteDialogX (*(int *)g_deleteDialogX_v)
#undef g_deleteDialogY
#define g_deleteDialogY (*(int *)g_deleteDialogY_v)
#undef g_desktopBits
#define g_desktopBits (*(int *)g_desktopBits_v)
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
#undef g_dialogFocus
#define g_dialogFocus (*(int *)g_dialogFocus_v)
#undef g_dialogFrameTexture
#define g_dialogFrameTexture (*(int *)((u8 *)g_menuFrameTextures_v + 0x4))
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
#undef g_dikF1
#define g_dikF1 (*(int *)g_dikF1_v)
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
#define g_directSound (*(APTR(void) *)g_directSound_v)
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
#define g_dplay (*(APTR(void) *)g_dplay_v)
#undef g_dplayLobby
#define g_dplayLobby (*(APTR(void) *)g_dplayLobby_v)
#undef g_dplaySessionCount
#define g_dplaySessionCount (*(int *)g_dplaySessionCount_v)
#undef g_dplaySessionOpen
#define g_dplaySessionOpen (*(int *)g_dplaySessionOpen_v)
#undef g_dplaySlots
#define g_dplaySlots ((int *)g_dplaySlots_v)
#undef g_editFieldLength
#define g_editFieldLength (*(int *)g_editFieldLength_v)
#undef g_editLineDone
#define g_editLineDone (*(int *)g_editLineDone_v)
#undef g_editOldProc
#define g_editOldProc (*(u32 *)g_editOldProc_v)
#undef g_editingAccountPassword
#define g_editingAccountPassword (*(int *)g_editingAccountPassword_v)
#undef g_editingEmail
#define g_editingEmail (*(int *)g_editingEmail_v)
#undef g_editingFragLimit
#define g_editingFragLimit (*(int *)g_editingFragLimit_v)
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
#undef g_editingTimeLimit
#define g_editingTimeLimit (*(int *)g_editingTimeLimit_v)
#undef g_emblemAlpha
#define g_emblemAlpha (*(float *)g_emblemAlpha_v)
#undef g_emblemAlphaStep
#define g_emblemAlphaStep (*(float *)g_emblemAlphaStep_v)
#undef g_emptySlot0Asked
#define g_emptySlot0Asked (*(int *)g_emptySlot0Asked_v)
#undef g_enteringMenus
#define g_enteringMenus (*(int *)g_enteringMenus_v)
#undef g_errorCleanupHook
#define g_errorCleanupHook (*(Cleanup *)g_errorCleanupHook_v)
#undef g_errorHook
#define g_errorHook (*(ErrorHook *)g_errorHook_v)
#undef g_errorLogging
#define g_errorLogging (*(int *)g_errorLogging_v)
#undef g_errorReported
#define g_errorReported (*(int *)g_errorReported_v)
#undef g_exitCode
#define g_exitCode (*(int *)g_exitCode_v)
#undef g_extraCount
#define g_extraCount (*(int *)g_extraCount_v)
#undef g_extraListTable
#define g_extraListTable ((int *)g_extraListTable_v)
#undef g_fatalReported
#define g_fatalReported (*(int *)g_fatalReported_v)
#undef g_fieldStep
#define g_fieldStep (*(int *)g_fieldStep_v)
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
#undef g_fps
#define g_fps (*(float *)g_fps_v)
#undef g_fpsFrameClock
#define g_fpsFrameClock (*(double *)g_fpsFrameClock_v)
#undef g_fpsFrameCount
#define g_fpsFrameCount (*(int *)g_fpsFrameCount_v)
#undef g_fpsSecondSoFar
#define g_fpsSecondSoFar (*(double *)g_fpsSecondSoFar_v)
#undef g_fpsSecondStart
#define g_fpsSecondStart (*(double *)g_fpsSecondStart_v)
#undef g_fragLimit
#define g_fragLimit (*(int *)g_fragLimit_v)
#undef g_frameCounter40
#define g_frameCounter40 (*(int *)g_frameCounter40_v)
#undef g_frameOpening
#define g_frameOpening (*(int *)g_frameOpening_v)
#undef g_frameRate
#define g_frameRate (*(double *)g_frameRate_v)
#undef g_frameTime
#define g_frameTime (*(float *)g_frameTime_v)
#undef g_freeCamLookX
#define g_freeCamLookX (*(float *)g_freeCamLookX_v)
#undef g_freeCamLookY
#define g_freeCamLookY (*(float *)g_freeCamLookY_v)
#undef g_freeCamLookZ
#define g_freeCamLookZ (*(float *)g_freeCamLookZ_v)
#undef g_freeCamMoveEyeX
#define g_freeCamMoveEyeX (*(float *)g_freeCamMoveEyeX_v)
#undef g_freeCamMoveEyeY
#define g_freeCamMoveEyeY (*(float *)g_freeCamMoveEyeY_v)
#undef g_freeCamMoveEyeZ
#define g_freeCamMoveEyeZ (*(float *)g_freeCamMoveEyeZ_v)
#undef g_freeCamMoveStarted
#define g_freeCamMoveStarted (*(int *)g_freeCamMoveStarted_v)
#undef g_freeCamMoveTargetX
#define g_freeCamMoveTargetX (*(float *)g_freeCamMoveTargetX_v)
#undef g_freeCamMoveTargetY
#define g_freeCamMoveTargetY (*(float *)g_freeCamMoveTargetY_v)
#undef g_freeCamMoveTargetZ
#define g_freeCamMoveTargetZ (*(float *)g_freeCamMoveTargetZ_v)
#undef g_freeCamTilt
#define g_freeCamTilt (*(float *)g_freeCamTilt_v)
#undef g_freeCamTurnCos
#define g_freeCamTurnCos (*(float *)g_freeCamTurnCos_v)
#undef g_freeCamTurnSin
#define g_freeCamTurnSin (*(float *)g_freeCamTurnSin_v)
#undef g_freeCamYaw
#define g_freeCamYaw (*(float *)g_freeCamYaw_v)
#undef g_freeCamZoom
#define g_freeCamZoom (*(int *)g_freeCamZoom_v)
#undef g_fxStatusTexts
#define g_fxStatusTexts ((char *)g_fxStatusTexts_v)
#undef g_gameConnectTexture
#define g_gameConnectTexture (*(int *)g_gameConnectTexture_v)
#undef g_gameCount
#define g_gameCount (*(int *)g_gameCount_v)
#undef g_gameListClickArmed
#define g_gameListClickArmed (*(int *)g_gameListClickArmed_v)
#undef g_gameListClickTimer
#define g_gameListClickTimer (*(float *)g_gameListClickTimer_v)
#undef g_gameListJoinBoxRects
#define g_gameListJoinBoxRects ((int *)g_gameListJoinBoxRects_v)
#undef g_gameListLoaded
#define g_gameListLoaded (*(int *)g_gameListLoaded_v)
#undef g_gameListRects
#define g_gameListRects ((int *)g_gameListRects_v)
#undef g_gameListRefreshSent
#define g_gameListRefreshSent (*(int *)g_gameListRefreshSent_v)
#undef g_gameListRow
#define g_gameListRow (*(int *)g_gameListRow_v)
#undef g_gameListTop
#define g_gameListTop (*(int *)g_gameListTop_v)
#undef g_gameRunning
#define g_gameRunning (*(int *)g_gameRunning_v)
#undef g_gameServerAnswer
#define g_gameServerAnswer (*(int *)g_gameServerAnswer_v)
#undef g_gameServerKeepAlive
#define g_gameServerKeepAlive (*(APTR(char) *)g_gameServerKeepAlive_v)
#undef g_gameServerReply
#define g_gameServerReply ((u8 *)g_gameServerReply_v)
#undef g_gameServerReplyCode
#define g_gameServerReplyCode ((int *)g_gameServerReplyCode_v)
#undef g_gameServerReplyKind
#define g_gameServerReplyKind (*(u32 *)((u8 *)g_gameServerReply_v + 0x68))
#undef g_gameServerReportsOff
#define g_gameServerReportsOff (*(int *)g_gameServerReportsOff_v)
#undef g_gameServerSocket
#define g_gameServerSocket (*(int *)g_gameServerSocket_v)
#undef g_gameServerStatus
#define g_gameServerStatus (*(int *)g_gameServerStatus_v)
#undef g_gameTitle
#define g_gameTitle ((char *)g_gameTitle_v)
#undef g_gameTypeNames
#define g_gameTypeNames ((char *)g_gameTypeNames_v)
#undef g_glColourBits
#define g_glColourBits (*(int *)g_glColourBits_v)
#undef g_glContext
#define g_glContext (g_data.g_glContext_)
#undef g_glDepthBits
#define g_glDepthBits (g_data.g_glDepthBits_)
#undef g_glFullScreen
#define g_glFullScreen (*(int *)g_glFullScreen_v)
#undef g_glHeight
#define g_glHeight (*(int *)g_glHeight_v)
#undef g_glTitle
#define g_glTitle ((char *)g_glTitle_v)
#undef g_glWidth
#define g_glWidth (*(int *)g_glWidth_v)
#undef g_glWindow
#define g_glWindow (*(APTR(void) *)g_glWindow_v)
#undef g_glWindowContext
#define g_glWindowContext (*(APTR(void) *)g_glWindowContext_v)
#undef g_glWindowDc
#define g_glWindowDc (*(APTR(void) *)g_glWindowDc_v)
#undef g_glWindowMade
#define g_glWindowMade (*(int *)g_glWindowMade_v)
#undef g_graphicEdited
#define g_graphicEdited ((u32 *)g_graphicEdited_v)
#undef g_graphicSettings
#define g_graphicSettings ((int *)g_graphicSettings_v)
#undef g_hEditField
#define g_hEditField (*(APTR(void) *)g_hEditField_v)
#undef g_hInstance
#define g_hInstance (*(APTR(void) *)g_hInstance_v)
#undef g_hanChoBottom
#define g_hanChoBottom ((float *)g_hanChoBottom_v)
#undef g_hanChoLeft
#define g_hanChoLeft ((float *)g_hanChoLeft_v)
#undef g_hanChoRight
#define g_hanChoRight ((float *)g_hanChoRight_v)
#undef g_hanChoTop
#define g_hanChoTop ((float *)g_hanChoTop_v)
#undef g_hanJongBottom
#define g_hanJongBottom ((float *)g_hanJongBottom_v)
#undef g_hanJongLeft
#define g_hanJongLeft ((float *)g_hanJongLeft_v)
#undef g_hanJongRight
#define g_hanJongRight ((float *)g_hanJongRight_v)
#undef g_hanJongTop
#define g_hanJongTop ((float *)g_hanJongTop_v)
#undef g_hanJungBottom
#define g_hanJungBottom ((float *)g_hanJungBottom_v)
#undef g_hanJungLeft
#define g_hanJungLeft ((float *)g_hanJungLeft_v)
#undef g_hanJungRight
#define g_hanJungRight ((float *)g_hanJungRight_v)
#undef g_hanJungTop
#define g_hanJungTop ((float *)g_hanJungTop_v)
#undef g_hangulLeadGlyph
#define g_hangulLeadGlyph (*(int *)g_hangulLeadGlyph_v)
#undef g_hangulLeadIndex
#define g_hangulLeadIndex ((signed char *)g_hangulLeadIndex_v)
#undef g_hangulLeadSetByVowel
#define g_hangulLeadSetByVowel ((signed char *)g_hangulLeadSetByVowel_v)
#undef g_hangulLeadSetByVowelTail
#define g_hangulLeadSetByVowelTail ((signed char *)g_hangulLeadSetByVowelTail_v)
#undef g_hangulTailGlyph
#define g_hangulTailGlyph (*(int *)g_hangulTailGlyph_v)
#undef g_hangulTailIndex
#define g_hangulTailIndex ((signed char *)g_hangulTailIndex_v)
#undef g_hangulTailSet
#define g_hangulTailSet ((signed char *)g_hangulTailSet_v)
#undef g_hangulVowelGlyph
#define g_hangulVowelGlyph (*(int *)g_hangulVowelGlyph_v)
#undef g_hangulVowelIndex
#define g_hangulVowelIndex ((signed char *)g_hangulVowelIndex_v)
#undef g_hangulVowelSetByLead
#define g_hangulVowelSetByLead ((signed char *)g_hangulVowelSetByLead_v)
#undef g_hangulVowelSetByLeadTail
#define g_hangulVowelSetByLeadTail ((signed char *)g_hangulVowelSetByLeadTail_v)
#undef g_hasItem30mm
#define g_hasItem30mm (g_data.g_hasItem30mm_)
#undef g_hasItem60mm
#define g_hasItem60mm (g_data.g_hasItem60mm_)
#undef g_hasItemBooster
#define g_hasItemBooster (g_data.g_hasItemBooster_)
#undef g_hasItemCapacity
#define g_hasItemCapacity (g_data.g_hasItemCapacity_)
#undef g_hasItemEpak
#define g_hasItemEpak (g_data.g_hasItemEpak_)
#undef g_hasItemMissile
#define g_hasItemMissile (g_data.g_hasItemMissile_)
#undef g_hasItemSensor
#define g_hasItemSensor (g_data.g_hasItemSensor_)
#undef g_hasItemShield
#define g_hasItemShield (g_data.g_hasItemShield_)
#undef g_hasItemWeight
#define g_hasItemWeight (g_data.g_hasItemWeight_)
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
#undef g_hostAddressBlock
#define g_hostAddressBlock (*(APTR(void) *)g_hostAddressBlock_v)
#undef g_hostAnswer
#define g_hostAnswer (*(int *)g_hostAnswer_v)
#undef g_hostErrorBox
#define g_hostErrorBox (*(int *)g_hostErrorBox_v)
#undef g_hostErrorBoxRects
#define g_hostErrorBoxRects ((int *)g_hostErrorBoxRects_v)
#undef g_hostGameSetUp
#define g_hostGameSetUp (*(int *)g_hostGameSetUp_v)
#undef g_hostGoneMessageFlag
#define g_hostGoneMessageFlag (*(int *)((u8 *)g_hostLeavingMsg_v + 0x4))
#undef g_hostLeavingMsg
#define g_hostLeavingMsg ((u32 *)g_hostLeavingMsg_v)
#undef g_hostingState
#define g_hostingState (*(int *)g_hostingState_v)
#undef g_inputFont
#define g_inputFont (*(APTR(void) *)g_inputFont_v)
#undef g_inputHistory
#define g_inputHistory ((char *)g_inputHistory_v)
#undef g_inputLine
#define g_inputLine ((char *)g_inputLine_v)
#undef g_inputLineHidden
#define g_inputLineHidden (*(int *)g_inputLineHidden_v)
#undef g_inputLineLength
#define g_inputLineLength (*(int *)g_inputLineLength_v)
#undef g_inputLineX
#define g_inputLineX (*(int *)g_inputLineX_v)
#undef g_inputLineY
#define g_inputLineY (*(int *)g_inputLineY_v)
#undef g_insertCdMessage
#define g_insertCdMessage (*(APTR(const char) *)g_insertCdMessage_v)
#undef g_introTextures
#define g_introTextures ((int *)g_introTextures_v)
#undef g_ipxProviderGuid
#define g_ipxProviderGuid ((u8 *)g_ipxProviderGuid_v)
#undef g_isHost
#define g_isHost (*(int *)g_isHost_v)
#undef g_itemBonus30mm
#define g_itemBonus30mm (*(float *)g_itemBonus30mm_v)
#undef g_itemBonus60mm
#define g_itemBonus60mm (*(float *)g_itemBonus60mm_v)
#undef g_itemBonusActiveTime
#define g_itemBonusActiveTime (*(float *)g_itemBonusActiveTime_v)
#undef g_itemBonusCapacityPerLevel
#define g_itemBonusCapacityPerLevel (*(float *)g_itemBonusCapacityPerLevel_v)
#undef g_itemBonusDetectionRange
#define g_itemBonusDetectionRange (*(float *)g_itemBonusDetectionRange_v)
#undef g_itemBonusEpak
#define g_itemBonusEpak (*(float *)g_itemBonusEpak_v)
#undef g_itemBonusHacking
#define g_itemBonusHacking (*(float *)g_itemBonusHacking_v)
#undef g_itemBonusLockOn
#define g_itemBonusLockOn (*(float *)g_itemBonusLockOn_v)
#undef g_itemBonusMissile
#define g_itemBonusMissile (*(float *)g_itemBonusMissile_v)
#undef g_itemBonusRechargeTime
#define g_itemBonusRechargeTime (*(float *)g_itemBonusRechargeTime_v)
#undef g_itemBonusShield
#define g_itemBonusShield (*(float *)g_itemBonusShield_v)
#undef g_itemBonusShieldUnread
#define g_itemBonusShieldUnread (*(float *)g_itemBonusShieldUnread_v)
#undef g_itemBonusTargetKeep
#define g_itemBonusTargetKeep (*(float *)g_itemBonusTargetKeep_v)
#undef g_itemBonusWeightLimit
#define g_itemBonusWeightLimit (*(float *)g_itemBonusWeightLimit_v)
#undef g_itemSlot4
#define g_itemSlot4 (*(int *)((u8 *)g_armcSlotItems_v + 0x0))
#undef g_itemSlot5
#define g_itemSlot5 (*(int *)((u8 *)g_armcSlotItems_v + 0x4))
#undef g_joinConnecting
#define g_joinConnecting (*(int *)g_joinConnecting_v)
#undef g_joinPasswordAndRanking
#define g_joinPasswordAndRanking ((u8 *)g_joinPasswordAndRanking_v)
#undef g_joinPollTicks
#define g_joinPollTicks (*(int *)g_joinPollTicks_v)
#undef g_joinRow
#define g_joinRow (*(int *)g_joinRow_v)
#undef g_joinThroughServer
#define g_joinThroughServer (*(int *)g_joinThroughServer_v)
#undef g_joinTimedOut
#define g_joinTimedOut (*(int *)g_joinTimedOut_v)
#undef g_joinTimer
#define g_joinTimer (*(u32 *)g_joinTimer_v)
#undef g_joinedSessionRec
#define g_joinedSessionRec ((SessionEntry *)g_joinedSessionRec_v)
#undef g_keepCameraAsked
#define g_keepCameraAsked (*(int *)g_keepCameraAsked_v)
#undef g_keptChat
#define g_keptChat ((char *)g_keptChat_v)
#undef g_keptChatLine
#define g_keptChatLine (*(char *)((u8 *)g_keptChat_v + 0x0))
#undef g_keyBackward
#define g_keyBackward (*(int *)((u8 *)g_controls_v + 0x8))
#undef g_keyChat
#define g_keyChat (*(int *)((u8 *)g_controls_v + 0xa8))
#undef g_keyForward
#define g_keyForward (*(int *)((u8 *)g_controls_v + 0x0))
#undef g_keyGameMenu
#define g_keyGameMenu (*(int *)((u8 *)g_controls_v + 0xc8))
#undef g_keyGameMenu2
#define g_keyGameMenu2 (*(int *)((u8 *)g_controls_v + 0xcc))
#undef g_keyNames
#define g_keyNames ((u32 *)g_keyNames_v)
#undef g_keySeen
#define g_keySeen ((int *)g_keySeen_v)
#undef g_keyState
#define g_keyState ((u8 *)g_keyState_v)
#undef g_keyStepLeft
#define g_keyStepLeft (*(int *)((u8 *)g_controls_v + 0x10))
#undef g_keyStepRight
#define g_keyStepRight (*(int *)((u8 *)g_controls_v + 0x18))
#undef g_keyboard
#define g_keyboard (g_data.g_keyboard_)
#undef g_keyboardReady
#define g_keyboardReady (*(int *)g_keyboardReady_v)
#undef g_ladderDeaths
#define g_ladderDeaths (*(int *)g_ladderDeaths_v)
#undef g_ladderDns
#define g_ladderDns ((char *)g_ladderDns_v)
#undef g_ladderEmail
#define g_ladderEmail ((char *)g_data.g_ladderEmail_)
#undef g_ladderExp
#define g_ladderExp (*(int *)g_ladderExp_v)
#undef g_ladderGames
#define g_ladderGames (*(int *)g_ladderGames_v)
#undef g_ladderId
#define g_ladderId ((char *)g_ladderId_v)
#undef g_ladderIdCopy
#define g_ladderIdCopy ((char *)g_ladderIdCopy_v)
#undef g_ladderKills
#define g_ladderKills (*(int *)g_ladderKills_v)
#undef g_ladderLevel
#define g_ladderLevel (*(int *)g_ladderLevel_v)
#undef g_ladderMenuTextures
#define g_ladderMenuTextures ((int *)g_ladderMenuTextures_v)
#undef g_ladderName
#define g_ladderName ((char *)g_data.g_ladderName_)
#undef g_ladderPassword
#define g_ladderPassword (*(int *)((u8 *)g_ladderId_v + 0x1e))
#undef g_ladderPassword4
#define g_ladderPassword4 (*(int *)((u8 *)g_ladderId_v + 0x22))
#undef g_ladderPassword8
#define g_ladderPassword8 (*(int *)((u8 *)g_ladderId_v + 0x26))
#undef g_ladderPort
#define g_ladderPort (*(int *)g_ladderPort_v)
#undef g_ladderPower
#define g_ladderPower (*(float *)g_ladderPower_v)
#undef g_lanJoinRequest
#define g_lanJoinRequest (*(int *)g_lanJoinRequest_v)
#undef g_lanSearch
#define g_lanSearch (*(int *)g_lanSearch_v)
#undef g_lanSearchStarted
#define g_lanSearchStarted (*(int *)g_lanSearchStarted_v)
#undef g_language
#define g_language (*(int *)g_language_v)
#undef g_languageId
#define g_languageId (*(u16 *)g_languageId_v)
#undef g_lastChatLine
#define g_lastChatLine (*(APTR(char) *)g_lastChatLine_v)
#undef g_lastChatLineSet
#define g_lastChatLineSet (*(int *)g_lastChatLineSet_v)
#undef g_lastCrosshair
#define g_lastCrosshair (g_data.g_lastCrosshair_)
#undef g_lastFrameClock
#define g_lastFrameClock (*(double *)g_lastFrameClock_v)
#undef g_lastPanel
#define g_lastPanel (*(int *)g_lastPanel_v)
#undef g_lastScreen
#define g_lastScreen (*(int *)g_lastScreen_v)
#undef g_lastTime
#define g_lastTime (*(double *)((u8 *)g_timerClocks_v + 0x8))
#undef g_launchArgs
#define g_launchArgs ((APTR(char) *)g_data.g_launchArgs_)
#undef g_launchMessage
#define g_launchMessage (*(APTR(const char) *)g_launchMessage_v)
#undef g_launchStartStep
#define g_launchStartStep (*(int *)g_launchStartStep_v)
#undef g_launchedAsHost
#define g_launchedAsHost (*(int *)g_launchedAsHost_v)
#undef g_launchedForNetGame
#define g_launchedForNetGame (*(int *)g_launchedForNetGame_v)
#undef g_launcherCheck
#define g_launcherCheck ((u8 *)g_launcherCheck_v)
#undef g_leavingForMatch
#define g_leavingForMatch (*(int *)g_leavingForMatch_v)
#undef g_legCount
#define g_legCount (*(int *)g_legCount_v)
#undef g_legCursor
#define g_legCursor (g_data.g_legCursor_)
#undef g_legList
#define g_legList ((int *)g_legList_v)
#undef g_legPanelName
#define g_legPanelName ((char *)g_legPanelName_v)
#undef g_legsSpeedCorrection
#define g_legsSpeedCorrection (*(float *)((u8 *)g_legsStats_v + 0x8))
#undef g_legsStats
#define g_legsStats ((float *)g_legsStats_v)
#undef g_legsWeight
#define g_legsWeight (*(float *)((u8 *)g_legsStats_v + 0x18))
#undef g_lineMaxLength
#define g_lineMaxLength (*(int *)g_lineMaxLength_v)
#undef g_lineToLoginId
#define g_lineToLoginId (*(int *)g_lineToLoginId_v)
#undef g_lineToLoginPassword
#define g_lineToLoginPassword (*(int *)g_lineToLoginPassword_v)
#undef g_linearFilterTexts
#define g_linearFilterTexts ((char *)g_linearFilterTexts_v)
#undef g_listAnswered
#define g_listAnswered (*(int *)g_listAnswered_v)
#undef g_listBlinkClock
#define g_listBlinkClock (*(float *)g_listBlinkClock_v)
#undef g_listBlinkRate
#define g_listBlinkRate (*(float *)g_listBlinkRate_v)
#undef g_listRefreshPeriod
#define g_listRefreshPeriod (*(int *)g_listRefreshPeriod_v)
#undef g_loadFade
#define g_loadFade (*(float *)g_loadFade_v)
#undef g_loadGame
#define g_loadGame (*(APTR(Scene) *)g_loadGame_v)
#undef g_loadLimit
#define g_loadLimit (*(float *)((u8 *)g_mechSpeeds_v + 0x14))
#undef g_loadScroll
#define g_loadScroll (*(float *)g_loadScroll_v)
#undef g_loadStatusText
#define g_loadStatusText ((char *)g_data.g_loadStatusText_)
#undef g_loadStep
#define g_loadStep (*(int *)g_loadStep_v)
#undef g_loadTexture
#define g_loadTexture (*(int *)g_loadTexture_v)
#undef g_loadTimer
#define g_loadTimer ((u8 *)g_loadTimer_v)
#undef g_lobbyConnectionBlock
#define g_lobbyConnectionBlock (*(APTR(void) *)g_lobbyConnectionBlock_v)
#undef g_lobbyConnectionOpen
#define g_lobbyConnectionOpen (*(int *)g_lobbyConnectionOpen_v)
#undef g_lobbyJoinStarted
#define g_lobbyJoinStarted (*(int *)g_lobbyJoinStarted_v)
#undef g_lobbyKeepAlive
#define g_lobbyKeepAlive (*(APTR(char) *)g_lobbyKeepAlive_v)
#undef g_lobbyLeavePacket
#define g_lobbyLeavePacket (*(APTR(u8) *)g_lobbyLeavePacket_v)
#undef g_lobbyListAnswer
#define g_lobbyListAnswer (*(int *)g_lobbyListAnswer_v)
#undef g_lobbyPanelsSliding
#define g_lobbyPanelsSliding (*(int *)g_lobbyPanelsSliding_v)
#undef g_lobbyRefreshing
#define g_lobbyRefreshing (*(int *)g_lobbyRefreshing_v)
#undef g_lobbyReplyCode
#define g_lobbyReplyCode ((int *)g_lobbyReplyCode_v)
#undef g_lobbyReplyKind
#define g_lobbyReplyKind (*(u32 *)((u8 *)g_lobbyReplyRecord_v + 0x4a))
#undef g_lobbyReplyRecord
#define g_lobbyReplyRecord ((u8 *)g_lobbyReplyRecord_v)
#undef g_lobbyReportsOff
#define g_lobbyReportsOff (*(int *)g_lobbyReportsOff_v)
#undef g_lobbySearching
#define g_lobbySearching (*(int *)g_lobbySearching_v)
#undef g_lobbySlideEase
#define g_lobbySlideEase ((float *)g_lobbySlideEase_v)
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
#undef g_lobbyTopRects
#define g_lobbyTopRects ((int *)g_lobbyTopRects_v)
#undef g_localAddress
#define g_localAddress ((char *)g_localAddress_v)
#undef g_localPlayerData
#define g_localPlayerData (*(u32 *)g_localPlayerData_v)
#undef g_localPlayerId
#define g_localPlayerId (*(u32 *)g_localPlayerId_v)
#undef g_localSlot
#define g_localSlot (*(u8 *)g_localSlot_v)
#undef g_logBMPRGBFile
#define g_logBMPRGBFile ((u32 *)g_logBMPRGBFile_v)
#undef g_logCollisionVolume
#define g_logCollisionVolume ((u32 *)g_logCollisionVolume_v)
#undef g_logConsole
#define g_logConsole ((u32 *)g_logConsole_v)
#undef g_logHook
#define g_logHook (*(APTR(void) *)g_logHook_v)
#undef g_logLight
#define g_logLight ((u32 *)g_logLight_v)
#undef g_logOutDialogBottom
#define g_logOutDialogBottom (*(int *)g_logOutDialogBottom_v)
#undef g_logOutDialogRects
#define g_logOutDialogRects ((int *)g_logOutDialogRects_v)
#undef g_logOutDialogRight
#define g_logOutDialogRight (*(int *)g_logOutDialogRight_v)
#undef g_logOutDialogX
#define g_logOutDialogX (*(int *)g_logOutDialogX_v)
#undef g_logOutDialogY
#define g_logOutDialogY (*(int *)g_logOutDialogY_v)
#undef g_logPackedColor
#define g_logPackedColor ((u32 *)g_logPackedColor_v)
#undef g_logRealColor
#define g_logRealColor ((u32 *)g_logRealColor_v)
#undef g_logScene
#define g_logScene ((u32 *)g_logScene_v)
#undef g_logShape
#define g_logShape ((u32 *)g_logShape_v)
#undef g_logShapeManager
#define g_logShapeManager ((u32 *)g_logShapeManager_v)
#undef g_logSkeleton
#define g_logSkeleton ((u32 *)g_logSkeleton_v)
#undef g_logSkeletonManager
#define g_logSkeletonManager ((u32 *)g_logSkeletonManager_v)
#undef g_logSound
#define g_logSound ((u32 *)g_logSound_v)
#undef g_logStage
#define g_logStage ((u32 *)g_logStage_v)
#undef g_logTexture
#define g_logTexture ((u32 *)g_logTexture_v)
#undef g_logTextureManager
#define g_logTextureManager ((u32 *)g_logTextureManager_v)
#undef g_logTimeSync
#define g_logTimeSync ((u32 *)g_logTimeSync_v)
#undef g_logUnit
#define g_logUnit ((u32 *)g_logUnit_v)
#undef g_logUnitPartInfo
#define g_logUnitPartInfo ((u32 *)g_logUnitPartInfo_v)
#undef g_logUnitPoseInfo
#define g_logUnitPoseInfo ((u32 *)g_logUnitPoseInfo_v)
#undef g_logViewVolume
#define g_logViewVolume ((u32 *)g_logViewVolume_v)
#undef g_loginToSend
#define g_loginToSend (*(int *)g_loginToSend_v)
#undef g_logoFade
#define g_logoFade (*(float *)g_logoFade_v)
#undef g_logoTexture
#define g_logoTexture (*(int *)g_logoTexture_v)
#undef g_mainMenuDepth
#define g_mainMenuDepth (*(float *)g_mainMenuDepth_v)
#undef g_mainMenuFrames
#define g_mainMenuFrames (*(int *)g_mainMenuFrames_v)
#undef g_mainMenuOutlines
#define g_mainMenuOutlines ((int *)g_mainMenuOutlines_v)
#undef g_mainMenuTextures
#define g_mainMenuTextures ((int *)g_mainMenuTextures_v)
#undef g_mainWindow
#define g_mainWindow (*(APTR(void) *)g_mainWindow_v)
#undef g_mapAbouts
#define g_mapAbouts ((char *)g_mapAbouts_v)
#undef g_mapChoiceKeptTable
#define g_mapChoiceKeptTable ((MapChoice *)g_mapChoiceKeptTable_v)
#undef g_mapChoiceTable
#define g_mapChoiceTable ((MapChoice *)g_mapChoiceTable_v)
#undef g_mapCount
#define g_mapCount (*(int *)g_mapCount_v)
#undef g_mapEntry22On
#define g_mapEntry22On (*(int *)((u8 *)g_mapChoiceKeptTable_v + 0xb0))
#undef g_mapEntry23On
#define g_mapEntry23On (*(int *)((u8 *)g_mapChoiceKeptTable_v + 0xb8))
#undef g_mapEntry24On
#define g_mapEntry24On (*(int *)((u8 *)g_mapChoiceKeptTable_v + 0xc0))
#undef g_mapIndex
#define g_mapIndex (*(int *)g_mapIndex_v)
#undef g_mapInfoDir
#define g_mapInfoDir ((char *)g_mapInfoDir_v)
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
#define g_mapNames ((char *)g_mapNames_v)
#undef g_mapPreviewChanged
#define g_mapPreviewChanged (*(int *)g_mapPreviewChanged_v)
#undef g_mapPreviewTexture
#define g_mapPreviewTexture (*(int *)g_mapPreviewTexture_v)
#undef g_mapRotation
#define g_mapRotation (*(int *)g_mapRotation_v)
#undef g_mapTop
#define g_mapTop (*(int *)g_mapTop_v)
#undef g_matchEndedByServer
#define g_matchEndedByServer (*(int *)g_matchEndedByServer_v)
#undef g_matchEndedByUser
#define g_matchEndedByUser (*(int *)g_matchEndedByUser_v)
#undef g_matchLogWritten
#define g_matchLogWritten (*(int *)g_matchLogWritten_v)
#undef g_matchMode
#define g_matchMode (*(int *)g_matchMode_v)
#undef g_matchPlayerName
#define g_matchPlayerName ((char *)g_matchPlayerName_v)
#undef g_matchProjMode
#define g_matchProjMode (*(int *)g_matchProjMode_v)
#undef g_matchRunning
#define g_matchRunning (*(int *)g_matchRunning_v)
#undef g_matchTextFieldX
#define g_matchTextFieldX (*(int *)g_matchTextFieldX_v)
#undef g_matchTextFieldY
#define g_matchTextFieldY (*(int *)g_matchTextFieldY_v)
#undef g_mciCallback
#define g_mciCallback (*(u32 *)g_mciCallback_v)
#undef g_mciDevice
#define g_mciDevice (*(u32 *)g_mciDevice_v)
#undef g_mciFrom
#define g_mciFrom (*(u32 *)g_mciFrom_v)
#undef g_mciTo
#define g_mciTo (*(u32 *)g_mciTo_v)
#undef g_mechBoostTime
#define g_mechBoostTime (*(float *)g_mechBoostTime_v)
#undef g_mechBoosterRecharge
#define g_mechBoosterRecharge (*(float *)g_mechBoosterRecharge_v)
#undef g_mechBoosterRestTime
#define g_mechBoosterRestTime (*(float *)g_mechBoosterRestTime_v)
#undef g_mechChanged
#define g_mechChanged (*(int *)g_mechChanged_v)
#undef g_mechDetectionAngle
#define g_mechDetectionAngle (*(float *)g_mechDetectionAngle_v)
#undef g_mechDetectionRange
#define g_mechDetectionRange (*(float *)g_mechDetectionRange_v)
#undef g_mechHackingLevel
#define g_mechHackingLevel (*(int *)g_mechHackingLevel_v)
#undef g_mechLegsBackBoost
#define g_mechLegsBackBoost (*(float *)g_mechLegsBackBoost_v)
#undef g_mechLegsForwardBoost
#define g_mechLegsForwardBoost (*(float *)g_mechLegsForwardBoost_v)
#undef g_mechLegsInertia
#define g_mechLegsInertia (*(float *)g_mechLegsInertia_v)
#undef g_mechLegsSideBoost
#define g_mechLegsSideBoost (*(float *)g_mechLegsSideBoost_v)
#undef g_mechLegsSpeedCorrection
#define g_mechLegsSpeedCorrection (*(float *)g_mechLegsSpeedCorrection_v)
#undef g_mechLockOnTime
#define g_mechLockOnTime (*(float *)g_mechLockOnTime_v)
#undef g_mechMaxSpeedBwd
#define g_mechMaxSpeedBwd (*(float *)((u8 *)g_mechSpeeds_v + 0x8))
#undef g_mechMaxima
#define g_mechMaxima ((int *)g_mechMaxima_v)
#undef g_mechMobility
#define g_mechMobility (*(float *)g_mechMobility_v)
#undef g_mechNormalSpeed
#define g_mechNormalSpeed (*(float *)((u8 *)g_mechSpeeds_v + 0x0))
#undef g_mechSpeeds
#define g_mechSpeeds ((float *)g_mechSpeeds_v)
#undef g_mechTargetKeepTime
#define g_mechTargetKeepTime (*(float *)g_mechTargetKeepTime_v)
#undef g_mechWeaponSlot0
#define g_mechWeaponSlot0 (*(int *)((u8 *)g_armcSlotItems_v + 0x8))
#undef g_mechWeaponSlot1
#define g_mechWeaponSlot1 (*(int *)((u8 *)g_armcSlotItems_v + 0xc))
#undef g_mechWeaponSlot2
#define g_mechWeaponSlot2 (*(int *)((u8 *)g_armcSlotItems_v + 0x10))
#undef g_mechWeaponSlot3
#define g_mechWeaponSlot3 (*(int *)((u8 *)g_armcSlotItems_v + 0x14))
#undef g_menuCameraLook
#define g_menuCameraLook (*(float *)((u8 *)g_menuLook_v + 0x0))
#undef g_menuCameraLookY
#define g_menuCameraLookY (*(float *)((u8 *)g_menuLook_v + 0x4))
#undef g_menuCameraLookZ
#define g_menuCameraLookZ (*(float *)((u8 *)g_menuLook_v + 0x8))
#undef g_menuCameraMove
#define g_menuCameraMove (*(int *)g_menuCameraMove_v)
#undef g_menuEye
#define g_menuEye ((float *)g_menuEye_v)
#undef g_menuEyeHome
#define g_menuEyeHome ((float *)g_menuEyeHome_v)
#undef g_menuEyeHomeX
#define g_menuEyeHomeX (*(float *)((u8 *)g_menuEyeHome_v + 0x0))
#undef g_menuEyeHomeY
#define g_menuEyeHomeY (*(float *)((u8 *)g_menuEyeHome_v + 0x4))
#undef g_menuEyeHomeZ
#define g_menuEyeHomeZ (*(float *)((u8 *)g_menuEyeHome_v + 0x8))
#undef g_menuEyeKept
#define g_menuEyeKept ((float *)g_menuEyeKept_v)
#undef g_menuEyeKeptX
#define g_menuEyeKeptX (*(float *)((u8 *)g_menuEyeKept_v + 0x0))
#undef g_menuEyeKeptY
#define g_menuEyeKeptY (*(float *)((u8 *)g_menuEyeKept_v + 0x4))
#undef g_menuEyeKeptZ
#define g_menuEyeKeptZ (*(float *)((u8 *)g_menuEyeKept_v + 0x8))
#undef g_menuEyeX
#define g_menuEyeX (*(float *)((u8 *)g_menuEye_v + 0x0))
#undef g_menuEyeY
#define g_menuEyeY (*(float *)((u8 *)g_menuEye_v + 0x4))
#undef g_menuEyeZ
#define g_menuEyeZ (*(float *)((u8 *)g_menuEye_v + 0x8))
#undef g_menuFrameCounter
#define g_menuFrameCounter (*(int *)g_menuFrameCounter_v)
#undef g_menuFramePhase
#define g_menuFramePhase (*(int *)g_menuFramePhase_v)
#undef g_menuFrameTextures
#define g_menuFrameTextures ((int *)g_menuFrameTextures_v)
#undef g_menuHintFade
#define g_menuHintFade (*(float *)g_menuHintFade_v)
#undef g_menuHintStep
#define g_menuHintStep (*(float *)g_menuHintStep_v)
#undef g_menuIdleTime
#define g_menuIdleTime (*(float *)g_menuIdleTime_v)
#undef g_menuKeyGuard
#define g_menuKeyGuard (*(float *)g_menuKeyGuard_v)
#undef g_menuLook
#define g_menuLook ((float *)g_menuLook_v)
#undef g_menuLookHome
#define g_menuLookHome ((float *)g_menuLookHome_v)
#undef g_menuLookHomeX
#define g_menuLookHomeX (*(float *)((u8 *)g_menuLookHome_v + 0x0))
#undef g_menuLookHomeY
#define g_menuLookHomeY (*(float *)((u8 *)g_menuLookHome_v + 0x4))
#undef g_menuLookHomeZ
#define g_menuLookHomeZ (*(float *)((u8 *)g_menuLookHome_v + 0x8))
#undef g_menuLookKept
#define g_menuLookKept ((float *)g_menuLookKept_v)
#undef g_menuLookKeptX
#define g_menuLookKeptX (*(float *)((u8 *)g_menuLookKept_v + 0x0))
#undef g_menuLookKeptY
#define g_menuLookKeptY (*(float *)((u8 *)g_menuLookKept_v + 0x4))
#undef g_menuLookKeptZ
#define g_menuLookKeptZ (*(float *)((u8 *)g_menuLookKept_v + 0x8))
#undef g_menuRepeatClock
#define g_menuRepeatClock (*(float *)g_menuRepeatClock_v)
#undef g_menuScaleX
#define g_menuScaleX (*(float *)g_menuScaleX_v)
#undef g_menuScaleY
#define g_menuScaleY (*(float *)g_menuScaleY_v)
#undef g_menuSoundBuffers
#define g_menuSoundBuffers ((u32 *)g_menuSoundBuffers_v)
#undef g_menuTunnel
#define g_menuTunnel (*(APTR(TunnelRing) *)g_menuTunnel_v)
#undef g_menuTunnelSpeed
#define g_menuTunnelSpeed (*(float *)g_menuTunnelSpeed_v)
#undef g_menuTunnelTexture
#define g_menuTunnelTexture (*(int *)g_menuTunnelTexture_v)
#undef g_menuVolume
#define g_menuVolume (*(int *)g_menuVolume_v)
#undef g_messageBoxArgs
#define g_messageBoxArgs (*(va_list *)g_messageBoxArgs_v)
#undef g_messageBoxLine
#define g_messageBoxLine ((char *)g_messageBoxLine_v)
#undef g_messageBoxText
#define g_messageBoxText ((char *)g_data.g_messageBoxText_)
#undef g_messageColours
#define g_messageColours ((Colour *)g_messageColours_v)
#undef g_messages
#define g_messages ((char *)g_messages_v)
#undef g_mipMapTexts
#define g_mipMapTexts ((char *)g_mipMapTexts_v)
#undef g_misHeader1
#define g_misHeader1 (*(int *)((u8 *)g_missionHeader_v + 0x4))
#undef g_misHeader2
#define g_misHeader2 (*(int *)((u8 *)g_missionHeader_v + 0x8))
#undef g_misHeader3
#define g_misHeader3 (*(int *)((u8 *)g_missionHeader_v + 0xc))
#undef g_missionClearBuffer
#define g_missionClearBuffer ((u8 *)g_missionClearBuffer_v)
#undef g_missionCount
#define g_missionCount (*(int *)((u8 *)g_missionHeader_v + 0x0))
#undef g_missionHeader
#define g_missionHeader ((u32 *)g_missionHeader_v)
#undef g_missionListRects
#define g_missionListRects ((int *)g_missionListRects_v)
#undef g_missionPicked
#define g_missionPicked (*(int *)g_missionPicked_v)
#undef g_missionRow
#define g_missionRow (*(int *)g_missionRow_v)
#undef g_missionTop
#define g_missionTop (*(int *)g_missionTop_v)
#undef g_missions
#define g_missions ((Mission *)g_missions_v)
#undef g_missionsColourDim
#define g_missionsColourDim ((float *)g_missionsColourDim_v)
#undef g_missionsColourLit
#define g_missionsColourLit ((float *)g_missionsColourLit_v)
#undef g_missionsDrawBackground
#define g_missionsDrawBackground (*(int *)g_missionsDrawBackground_v)
#undef g_missionsPage
#define g_missionsPage (*(int *)g_missionsPage_v)
#undef g_missionsState
#define g_missionsState (*(int *)g_missionsState_v)
#undef g_missionsWindowBottom
#define g_missionsWindowBottom (*(int *)g_missionsWindowBottom_v)
#undef g_missionsWindowLeft
#define g_missionsWindowLeft (*(int *)g_missionsWindowLeft_v)
#undef g_missionsWindowRight
#define g_missionsWindowRight (*(int *)g_missionsWindowRight_v)
#undef g_missionsWindowTop
#define g_missionsWindowTop (*(int *)g_missionsWindowTop_v)
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
#undef g_mouseButtonsHeld
#define g_mouseButtonsHeld ((int *)g_mouseButtonsHeld_v)
#undef g_mouseClicked
#define g_mouseClicked ((int *)g_mouseClicked_v)
#undef g_mouseInvert
#define g_mouseInvert (*(int *)((u8 *)g_controls_v + 0x100))
#undef g_mousePos
#define g_mousePos ((int *)g_mousePos_v)
#undef g_mouseReady
#define g_mouseReady (*(int *)g_mouseReady_v)
#undef g_mouseSensitivity
#define g_mouseSensitivity (*(int *)((u8 *)g_controls_v + 0x108))
#undef g_mouseSmooth
#define g_mouseSmooth (*(int *)((u8 *)g_controls_v + 0x104))
#undef g_mouseState
#define g_mouseState ((int *)g_mouseState_v)
#undef g_mouseTaken
#define g_mouseTaken (*(int *)g_mouseTaken_v)
#undef g_mouseWasDown
#define g_mouseWasDown ((int *)g_mouseWasDown_v)
#undef g_mouseWheel
#define g_mouseWheel (*(int *)g_mouseWheel_v)
#undef g_mouseWheelTurned
#define g_mouseWheelTurned (*(int *)g_mouseWheelTurned_v)
#undef g_mouseX
#define g_mouseX (*(int *)((u8 *)g_mousePos_v + 0x0))
#undef g_mouseY
#define g_mouseY (*(int *)((u8 *)g_mousePos_v + 0x4))
#undef g_music
#define g_music (*(APTR(void) *)g_music_v)
#undef g_musicDuration
#define g_musicDuration ((u32 *)g_musicDuration_v)
#undef g_musicFile
#define g_musicFile ((char *)g_musicFile_v)
#undef g_musicLength
#define g_musicLength (*(u32 *)((u8 *)g_musicDuration_v + 0x0))
#undef g_musicLengthHigh
#define g_musicLengthHigh (*(int *)((u8 *)g_musicDuration_v + 0x4))
#undef g_musicVolume
#define g_musicVolume (*(int *)((u8 *)g_soundSettings_v + 0x4))
#undef g_musicVolumeSetting
#define g_musicVolumeSetting (*(int *)g_musicVolumeSetting_v)
#undef g_netAccountBuffer
#define g_netAccountBuffer (*(APTR(char) *)g_netAccountBuffer_v)
#undef g_netAccountRequest
#define g_netAccountRequest (*(APTR(char) *)g_netAccountRequest_v)
#undef g_netBlockSize
#define g_netBlockSize (*(u32 *)g_netBlockSize_v)
#undef g_netByteBuffer
#define g_netByteBuffer (*(APTR(char) *)g_netByteBuffer_v)
#undef g_netChatMessageFrom
#define g_netChatMessageFrom (*(int *)g_netChatMessageFrom_v)
#undef g_netChatMessageKind
#define g_netChatMessageKind (*(int *)g_netChatMessageKind_v)
#undef g_netChatMessageText
#define g_netChatMessageText (*(int *)g_netChatMessageText_v)
#undef g_netChatMessageWord1
#define g_netChatMessageWord1 (*(int *)g_netChatMessageWord1_v)
#undef g_netClaimedSlot
#define g_netClaimedSlot (*(int *)((u8 *)g_netSlotMsg_v + 0x4))
#undef g_netConnected
#define g_netConnected (*(int *)g_netConnected_v)
#undef g_netHostGone
#define g_netHostGone (*(int *)g_netHostGone_v)
#undef g_netHostLeftMessageKind
#define g_netHostLeftMessageKind (*(int *)((u8 *)g_hostLeavingMsg_v + 0x0))
#undef g_netKindBuffer
#define g_netKindBuffer (*(APTR(u32) *)g_netKindBuffer_v)
#undef g_netLastRequest
#define g_netLastRequest (*(int *)g_netLastRequest_v)
#undef g_netLeaveBuffer
#define g_netLeaveBuffer (*(APTR(char) *)g_netLeaveBuffer_v)
#undef g_netListDone
#define g_netListDone (*(int *)g_netListDone_v)
#undef g_netPacketMessageKind
#define g_netPacketMessageKind (*(int *)((u8 *)g_netSendPacket_v + 0x0))
#undef g_netPlayerList
#define g_netPlayerList ((RankedPlayer *)g_netPlayerList_v)
#undef g_netPlayerRecordPacket
#define g_netPlayerRecordPacket (*(APTR(u8) *)g_netPlayerRecordPacket_v)
#undef g_netQueueOnline
#define g_netQueueOnline (*(int *)g_netQueueOnline_v)
#undef g_netRankingBuffer
#define g_netRankingBuffer (*(APTR(int) *)g_netRankingBuffer_v)
#undef g_netRole
#define g_netRole (*(int *)g_netRole_v)
#undef g_netSelectionPacket
#define g_netSelectionPacket (*(APTR(u8) *)g_netSelectionPacket_v)
#undef g_netSendPacket
#define g_netSendPacket ((NetPacketMessage *)g_netSendPacket_v)
#undef g_netSlotMessageKind
#define g_netSlotMessageKind (*(int *)((u8 *)g_netSlotMsg_v + 0x0))
#undef g_netSlotMsg
#define g_netSlotMsg ((u32 *)g_netSlotMsg_v)
#undef g_netSlots
#define g_netSlots ((NetSlot *)g_data.g_netSlots_)
#undef g_netqCursor
#define g_netqCursor (*(int *)g_netqCursor_v)
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
#undef g_newArenaFragLimit
#define g_newArenaFragLimit (*(u8 *)((u8 *)g_newArenaName_v + 0x24))
#undef g_newArenaMap
#define g_newArenaMap (*(signed char *)((u8 *)g_newArenaName_v + 0x20))
#undef g_newArenaMaxPlayers
#define g_newArenaMaxPlayers (*(signed char *)((u8 *)g_newArenaName_v + 0x21))
#undef g_newArenaMode
#define g_newArenaMode (*(signed char *)((u8 *)g_newArenaName_v + 0x23))
#undef g_newArenaName
#define g_newArenaName ((char *)g_newArenaName_v)
#undef g_newArenaPassword
#define g_newArenaPassword (*(int *)((u8 *)g_newArenaName_v + 0x26))
#undef g_newArenaPassword4
#define g_newArenaPassword4 (*(int *)((u8 *)g_newArenaName_v + 0x2a))
#undef g_newArenaRotation
#define g_newArenaRotation (*(signed char *)((u8 *)g_newArenaName_v + 0x22))
#undef g_newArenaTimeLimit
#define g_newArenaTimeLimit (*(u8 *)((u8 *)g_newArenaName_v + 0x25))
#undef g_newIdAnswer
#define g_newIdAnswer (*(int *)g_newIdAnswer_v)
#undef g_newIdAnswerAwaited
#define g_newIdAnswerAwaited (*(int *)g_newIdAnswerAwaited_v)
#undef g_newIdConfirmBox
#define g_newIdConfirmBox ((int *)g_newIdConfirmBox_v)
#undef g_newIdConfirmChoice
#define g_newIdConfirmChoice (*(int *)g_newIdConfirmChoice_v)
#undef g_newIdConfirmRects
#define g_newIdConfirmRects ((int *)g_newIdConfirmRects_v)
#undef g_newIdFormBottom
#define g_newIdFormBottom (*(int *)g_newIdFormBottom_v)
#undef g_newIdFormLeft
#define g_newIdFormLeft (*(int *)g_newIdFormLeft_v)
#undef g_newIdFormOpenName
#define g_newIdFormOpenName (*(int *)g_newIdFormOpenName_v)
#undef g_newIdFormRects
#define g_newIdFormRects ((int *)g_newIdFormRects_v)
#undef g_newIdFormRight
#define g_newIdFormRight (g_data.g_newIdFormRight_)
#undef g_newIdFormTop
#define g_newIdFormTop (*(int *)g_newIdFormTop_v)
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
#undef g_noAddress
#define g_noAddress ((char *)g_noAddress_v)
#undef g_otherModeHeight
#define g_otherModeHeight (*(int *)g_otherModeHeight_v)
#undef g_otherModeWidth
#define g_otherModeWidth (*(int *)g_otherModeWidth_v)
#undef g_outOfRank
#define g_outOfRank (*(u8 *)((u8 *)g_rankReply_v + 0x1))
#undef g_outlinesCopy
#define g_outlinesCopy ((int *)g_outlinesCopy_v)
#undef g_packedBlue
#define g_packedBlue ((u8 *)g_packedBlue_v)
#undef g_packedGreen
#define g_packedGreen ((u8 *)g_packedGreen_v)
#undef g_packedGrey
#define g_packedGrey ((u8 *)g_packedGrey_v)
#undef g_packedRed
#define g_packedRed (*(u32 *)g_packedRed_v)
#undef g_packedWhite
#define g_packedWhite ((u8 *)g_data.g_packedWhite_)
#undef g_packedYellow
#define g_packedYellow ((u8 *)g_packedYellow_v)
#undef g_packetQueue
#define g_packetQueue ((u8 *)g_packetQueue_v)
#undef g_packetsSkipped
#define g_packetsSkipped (*(int *)g_packetsSkipped_v)
#undef g_panel0Speed
#define g_panel0Speed (*(float *)((u8 *)g_spinPanels_v + 0x54))
#undef g_panel1Speed
#define g_panel1Speed (*(float *)((u8 *)g_spinPanels_v + 0xac))
#undef g_panel2Speed
#define g_panel2Speed (*(float *)((u8 *)g_spinPanels_v + 0x104))
#undef g_panel3Speed
#define g_panel3Speed (*(float *)((u8 *)g_spinPanels_v + 0x15c))
#undef g_panel4Speed
#define g_panel4Speed (*(float *)((u8 *)g_spinPanels_v + 0x1b4))
#undef g_panel5Speed
#define g_panel5Speed (*(float *)((u8 *)g_spinPanels_v + 0x20c))
#undef g_panelGlow
#define g_panelGlow (*(float *)g_panelGlow_v)
#undef g_panelGlowStep
#define g_panelGlowStep (*(float *)g_panelGlowStep_v)
#undef g_panelHovered
#define g_panelHovered (*(int *)g_panelHovered_v)
#undef g_partRecords
#define g_partRecords ((u8 *)g_partRecords_v)
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
#undef g_penFontTexture
#define g_penFontTexture (*(int *)g_penFontTexture_v)
#undef g_penInitialized
#define g_penInitialized (*(int *)g_penInitialized_v)
#undef g_penPropBottomLeft
#define g_penPropBottomLeft ((float *)g_penPropBottomLeft_v)
#undef g_penPropBottomRight
#define g_penPropBottomRight ((float *)g_penPropBottomRight_v)
#undef g_penPropTopLeft
#define g_penPropTopLeft ((float *)g_penPropTopLeft_v)
#undef g_penPropTopRight
#define g_penPropTopRight ((float *)g_penPropTopRight_v)
#undef g_penPropWidths
#define g_penPropWidths ((int *)g_penPropWidths_v)
#undef g_perfCounterHigh
#define g_perfCounterHigh (*(u32 *)g_perfCounterHigh_v)
#undef g_perfCounterLow
#define g_perfCounterLow (*(u32 *)g_perfCounterLow_v)
#undef g_pickedGame
#define g_pickedGame (*(int *)g_pickedGame_v)
#undef g_pilotDeaths
#define g_pilotDeaths (*(int *)((u8 *)g_pilotStats_v + 0x18))
#undef g_pilotDeathsKept
#define g_pilotDeathsKept (*(int *)((u8 *)g_pilotStatsKept_v + 0x18))
#undef g_pilotExp
#define g_pilotExp (*(int *)((u8 *)g_pilotStats_v + 0x4))
#undef g_pilotExpKept
#define g_pilotExpKept (*(int *)((u8 *)g_pilotStatsKept_v + 0x4))
#undef g_pilotGames
#define g_pilotGames (*(int *)((u8 *)g_pilotStats_v + 0x10))
#undef g_pilotGamesKept
#define g_pilotGamesKept (*(int *)((u8 *)g_pilotStatsKept_v + 0x10))
#undef g_pilotKillRate
#define g_pilotKillRate (*(float *)((u8 *)g_pilotStats_v + 0x1c))
#undef g_pilotKills
#define g_pilotKills (*(int *)((u8 *)g_pilotStats_v + 0x14))
#undef g_pilotKillsKept
#define g_pilotKillsKept (*(int *)((u8 *)g_pilotStatsKept_v + 0x14))
#undef g_pilotLevel
#define g_pilotLevel (*(int *)((u8 *)g_pilotStats_v + 0x0))
#undef g_pilotLevelKept
#define g_pilotLevelKept (*(int *)((u8 *)g_pilotStatsKept_v + 0x0))
#undef g_pilotNoise
#define g_pilotNoise ((u8 *)g_pilotNoise_v)
#undef g_pilotPower
#define g_pilotPower (*(float *)((u8 *)g_pilotStats_v + 0xc))
#undef g_pilotPowerKept
#define g_pilotPowerKept (*(float *)((u8 *)g_pilotStatsKept_v + 0xc))
#undef g_pilotRank
#define g_pilotRank (*(int *)((u8 *)g_pilotStats_v + 0x8))
#undef g_pilotRankKept
#define g_pilotRankKept (*(int *)((u8 *)g_pilotStatsKept_v + 0x8))
#undef g_pilotSave
#define g_pilotSave ((u8 *)g_pilotSave_v)
#undef g_pilotSelectBottom
#define g_pilotSelectBottom (*(int *)g_pilotSelectBottom_v)
#undef g_pilotSelectCursor
#define g_pilotSelectCursor (*(int *)g_pilotSelectCursor_v)
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
#undef g_pingAddresses
#define g_pingAddresses ((char *)g_pingAddresses_v)
#undef g_pingStartEvent
#define g_pingStartEvent (*(APTR(void) *)g_pingStartEvent_v)
#undef g_pingStopEvent
#define g_pingStopEvent (*(APTR(void) *)g_pingStopEvent_v)
#undef g_pingThread
#define g_pingThread (*(APTR(void) *)g_pingThread_v)
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
#undef g_playerCustomize
#define g_playerCustomize (*(int *)g_playerCustomize_v)
#undef g_playerListCount
#define g_playerListCount (*(int *)g_playerListCount_v)
#undef g_playerListDone
#define g_playerListDone (*(int *)g_playerListDone_v)
#undef g_playerListReply
#define g_playerListReply ((u8 *)g_playerListReply_v)
#undef g_playerListReplyKind
#define g_playerListReplyKind (*(int *)((u8 *)g_playerListReply_v + 0x1e))
#undef g_playerSetupBottom
#define g_playerSetupBottom (*(int *)g_playerSetupBottom_v)
#undef g_playerSetupLeft
#define g_playerSetupLeft (*(int *)g_playerSetupLeft_v)
#undef g_playerSetupRects
#define g_playerSetupRects ((int *)g_playerSetupRects_v)
#undef g_playerSetupRight
#define g_playerSetupRight (*(int *)g_playerSetupRight_v)
#undef g_playerSetupTop
#define g_playerSetupTop (*(int *)g_playerSetupTop_v)
#undef g_playerSlotFlags
#define g_playerSlotFlags ((int *)g_playerSlotFlags_v)
#undef g_pointerGlideTime
#define g_pointerGlideTime (*(float *)g_pointerGlideTime_v)
#undef g_pointerGlideX
#define g_pointerGlideX (*(int *)g_pointerGlideX_v)
#undef g_pointerGlideY
#define g_pointerGlideY (*(int *)g_pointerGlideY_v)
#undef g_pointerGliding
#define g_pointerGliding (*(int *)g_pointerGliding_v)
#undef g_primarySoundBuffer
#define g_primarySoundBuffer (*(APTR(void) *)g_primarySoundBuffer_v)
#undef g_profileChosen
#define g_profileChosen (*(int *)g_profileChosen_v)
#undef g_profileColour
#define g_profileColour ((float *)g_profileColour_v)
#undef g_profileCount
#define g_profileCount (*(int *)g_profileCount_v)
#undef g_profileDim
#define g_profileDim ((float *)g_profileDim_v)
#undef g_profileFrameAlpha
#define g_profileFrameAlpha (*(float *)g_profileFrameAlpha_v)
#undef g_profileFrameStep
#define g_profileFrameStep (*(float *)g_profileFrameStep_v)
#undef g_profileHeader
#define g_profileHeader ((u8 *)g_profileHeader_v)
#undef g_profileListRects
#define g_profileListRects ((int *)g_profileListRects_v)
#undef g_profileListRow
#define g_profileListRow (*(int *)g_profileListRow_v)
#undef g_profileListTop
#define g_profileListTop (*(int *)g_profileListTop_v)
#undef g_profileLogInAsked
#define g_profileLogInAsked (*(int *)g_profileLogInAsked_v)
#undef g_profileMechArm
#define g_profileMechArm (*(int *)((u8 *)g_pilotSave_v + 0x2e8))
#undef g_profileMechBooster
#define g_profileMechBooster (*(int *)((u8 *)g_pilotSave_v + 0x2f0))
#undef g_profileMechChest
#define g_profileMechChest (*(int *)((u8 *)g_pilotSave_v + 0x2e4))
#undef g_profileMechHead
#define g_profileMechHead (*(int *)((u8 *)g_pilotSave_v + 0x2e0))
#undef g_profileMechItemSlot4
#define g_profileMechItemSlot4 (*(int *)((u8 *)g_pilotSave_v + 0x2fc))
#undef g_profileMechItemSlot5
#define g_profileMechItemSlot5 (*(int *)((u8 *)g_pilotSave_v + 0x300))
#undef g_profileMechLeg
#define g_profileMechLeg (*(int *)((u8 *)g_pilotSave_v + 0x2ec))
#undef g_profileMechWeaponSlot0
#define g_profileMechWeaponSlot0 (*(int *)((u8 *)g_pilotSave_v + 0x304))
#undef g_profileMechWeaponSlot1
#define g_profileMechWeaponSlot1 (*(int *)((u8 *)g_pilotSave_v + 0x308))
#undef g_profileMechWeaponSlot2
#define g_profileMechWeaponSlot2 (*(int *)((u8 *)g_pilotSave_v + 0x30c))
#undef g_profileMechWeaponSlot3
#define g_profileMechWeaponSlot3 (*(int *)((u8 *)g_pilotSave_v + 0x310))
#undef g_profileName
#define g_profileName ((char *)g_data.g_profileName_)
#undef g_profileNameTakenClickBox
#define g_profileNameTakenClickBox ((int *)g_profileNameTakenClickBox_v)
#undef g_profileNameTakenShown
#define g_profileNameTakenShown (*(int *)g_profileNameTakenShown_v)
#undef g_profileNoneAtEntry
#define g_profileNoneAtEntry (*(int *)g_profileNoneAtEntry_v)
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
#undef g_profileQuitSkip
#define g_profileQuitSkip (*(int *)g_profileQuitSkip_v)
#undef g_profileQuitting
#define g_profileQuitting (*(int *)g_profileQuitting_v)
#undef g_profileReply
#define g_profileReply ((u8 *)g_profileReply_v)
#undef g_profileReplyResult
#define g_profileReplyResult (*(int *)((u8 *)g_profileReply_v + 0x0))
#undef g_profileReveal
#define g_profileReveal (*(int *)g_profileReveal_v)
#undef g_profileRevealClock
#define g_profileRevealClock (*(float *)g_profileRevealClock_v)
#undef g_profileRowClickTime
#define g_profileRowClickTime (*(float *)g_profileRowClickTime_v)
#undef g_profileRowClicked
#define g_profileRowClicked (*(int *)g_profileRowClicked_v)
#undef g_profiles
#define g_profiles ((u8 *)g_profiles_v)
#undef g_progressSeen
#define g_progressSeen (*(int *)g_progressSeen_v)
#undef g_progressWentUp
#define g_progressWentUp (*(int *)g_progressWentUp_v)
#undef g_projMode
#define g_projMode (*(int *)g_projMode_v)
#undef g_providerGuid
#define g_providerGuid (*(APTR(const void) *)g_providerGuid_v)
#undef g_ptxAcCodes
#define g_ptxAcCodes ((int *)g_ptxAcCodes_v)
#undef g_ptxBitPos
#define g_ptxBitPos (*(int *)g_ptxBitPos_v)
#undef g_ptxCbBlue
#define g_ptxCbBlue ((int *)g_ptxCbBlue_v)
#undef g_ptxCbGreen
#define g_ptxCbGreen ((int *)g_ptxCbGreen_v)
#undef g_ptxClamp
#define g_ptxClamp (*(APTR(const u8) *)g_ptxClamp_v)
#undef g_ptxClampTable
#define g_ptxClampTable ((u8 *)g_ptxClampTable_v)
#undef g_ptxCrGreen
#define g_ptxCrGreen ((int *)g_ptxCrGreen_v)
#undef g_ptxCrRed
#define g_ptxCrRed ((int *)g_ptxCrRed_v)
#undef g_ptxData
#define g_ptxData ((u8 *)g_ptxData_v)
#undef g_ptxDcCodes
#define g_ptxDcCodes ((int *)g_ptxDcCodes_v)
#undef g_ptxDequant
#define g_ptxDequant ((int *)g_ptxDequant_v)
#undef g_ptxFdctBase
#define g_ptxFdctBase ((float *)g_ptxFdctBase_v)
#undef g_ptxFdctDivisors
#define g_ptxFdctDivisors ((float *)g_ptxFdctDivisors_v)
#undef g_ptxHuffSet
#define g_ptxHuffSet (*(int *)g_ptxHuffSet_v)
#undef g_ptxLastDc
#define g_ptxLastDc (*(int *)g_ptxLastDc_v)
#undef g_ptxPixels
#define g_ptxPixels ((u8 *)g_ptxPixels_v)
#undef g_ptxPlanes
#define g_ptxPlanes ((u8 *)g_ptxPlanes_v)
#undef g_ptxQuantBase
#define g_ptxQuantBase ((int *)g_ptxQuantBase_v)
#undef g_ptxTablesReady
#define g_ptxTablesReady (*(int *)g_ptxTablesReady_v)
#undef g_ptxYCbCrTables
#define g_ptxYCbCrTables ((int *)g_ptxYCbCrTables_v)
#undef g_ptxZigzag
#define g_ptxZigzag ((int *)g_ptxZigzag_v)
#undef g_pulse
#define g_pulse (*(float *)g_pulse_v)
#undef g_pulseStep
#define g_pulseStep (*(float *)g_pulseStep_v)
#undef g_randPos
#define g_randPos (*(u32 *)g_randPos_v)
#undef g_randTable
#define g_randTable ((int *)g_randTable_v)
#undef g_rankReply
#define g_rankReply ((u8 *)g_rankReply_v)
#undef g_rankReplyCode
#define g_rankReplyCode (*(u8 *)((u8 *)g_rankReply_v + 0x0))
#undef g_rankReplyIn
#define g_rankReplyIn (*(int *)g_rankReplyIn_v)
#undef g_rankingFirst
#define g_rankingFirst (*(int *)g_rankingFirst_v)
#undef g_rankingHaveList
#define g_rankingHaveList (*(int *)g_rankingHaveList_v)
#undef g_rankingLast
#define g_rankingLast (*(int *)g_rankingLast_v)
#undef g_rankingLastPage
#define g_rankingLastPage (*(int *)g_rankingLastPage_v)
#undef g_rankingListIn
#define g_rankingListIn (*(int *)g_rankingListIn_v)
#undef g_rankingPage
#define g_rankingPage (*(int *)g_rankingPage_v)
#undef g_rankingPrevPage
#define g_rankingPrevPage (*(int *)g_rankingPrevPage_v)
#undef g_rankingPrevRank
#define g_rankingPrevRank (*(int *)g_rankingPrevRank_v)
#undef g_rankingPrevSort
#define g_rankingPrevSort (*(int *)g_rankingPrevSort_v)
#undef g_rankingPrevValue
#define g_rankingPrevValue (*(float *)g_rankingPrevValue_v)
#undef g_rankingRect
#define g_rankingRect ((int *)g_rankingRect_v)
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
#undef g_receivedRank
#define g_receivedRank (*(int *)((u8 *)g_rankReply_v + 0x16))
#undef g_receivedSession
#define g_receivedSession (*(APTR(const u8) *)g_receivedSession_v)
#undef g_rectColour
#define g_rectColour ((Colour *)g_rectColour_v)
#undef g_repeatDown
#define g_repeatDown (*(float *)g_repeatDown_v)
#undef g_repeatUp
#define g_repeatUp (*(float *)g_repeatUp_v)
#undef g_replayFileCount
#define g_replayFileCount (*(int *)g_replayFileCount_v)
#undef g_replayList
#define g_replayList ((FileEntry *)g_replayList_v)
#undef g_replayListCount
#define g_replayListCount (*(int *)g_replayListCount_v)
#undef g_replayRandomOrder
#define g_replayRandomOrder (*(int *)g_replayRandomOrder_v)
#undef g_replayRunning
#define g_replayRunning (*(int *)g_replayRunning_v)
#undef g_replaySelectBottom
#define g_replaySelectBottom (*(int *)g_replaySelectBottom_v)
#undef g_replaySelectDim
#define g_replaySelectDim ((float *)g_replaySelectDim_v)
#undef g_replaySelectDimA
#define g_replaySelectDimA (*(float *)((u8 *)g_replaySelectDim_v + 0xc))
#undef g_replaySelectDimB
#define g_replaySelectDimB (*(float *)((u8 *)g_replaySelectDim_v + 0x8))
#undef g_replaySelectDimG
#define g_replaySelectDimG (*(float *)((u8 *)g_replaySelectDim_v + 0x4))
#undef g_replaySelectDimR
#define g_replaySelectDimR (*(float *)((u8 *)g_replaySelectDim_v + 0x0))
#undef g_replaySelectFirst
#define g_replaySelectFirst (*(int *)g_replaySelectFirst_v)
#undef g_replaySelectLeft
#define g_replaySelectLeft (*(int *)g_replaySelectLeft_v)
#undef g_replaySelectLit
#define g_replaySelectLit ((float *)g_replaySelectLit_v)
#undef g_replaySelectLitA
#define g_replaySelectLitA (*(float *)((u8 *)g_replaySelectLit_v + 0xc))
#undef g_replaySelectLitB
#define g_replaySelectLitB (*(float *)((u8 *)g_replaySelectLit_v + 0x8))
#undef g_replaySelectLitG
#define g_replaySelectLitG (*(float *)((u8 *)g_replaySelectLit_v + 0x4))
#undef g_replaySelectLitR
#define g_replaySelectLitR (*(float *)((u8 *)g_replaySelectLit_v + 0x0))
#undef g_replaySelectOpen
#define g_replaySelectOpen (*(int *)g_replaySelectOpen_v)
#undef g_replaySelectRects
#define g_replaySelectRects ((int *)g_replaySelectRects_v)
#undef g_replaySelectRight
#define g_replaySelectRight (*(int *)g_replaySelectRight_v)
#undef g_replaySelectTop
#define g_replaySelectTop (*(int *)g_replaySelectTop_v)
#undef g_replayShowOn
#define g_replayShowOn (*(int *)g_replayShowOn_v)
#undef g_replayWrap
#define g_replayWrap (*(int *)g_replayWrap_v)
#undef g_replayZoomTime
#define g_replayZoomTime (*(float *)g_replayZoomTime_v)
#undef g_resolutionNames
#define g_resolutionNames ((u32 *)g_resolutionNames_v)
#undef g_resolvedAddress
#define g_resolvedAddress ((char *)g_resolvedAddress_v)
#undef g_retintAllParts
#define g_retintAllParts (*(int *)g_retintAllParts_v)
#undef g_retypePassword
#define g_retypePassword (*(int *)g_retypePassword_v)
#undef g_rightClick
#define g_rightClick (*(int *)((u8 *)g_mouseClicked_v + 0x4))
#undef g_ringBandTexture
#define g_ringBandTexture (*(int *)g_ringBandTexture_v)
#undef g_roomBright
#define g_roomBright ((float *)g_roomBright_v)
#undef g_roomCameraMode
#define g_roomCameraMode (*(int *)g_roomCameraMode_v)
#undef g_roomColours
#define g_roomColours ((float *)g_roomColours_v)
#undef g_roomColoursKept
#define g_roomColoursKept ((float *)g_roomColoursKept_v)
#undef g_roomConnected
#define g_roomConnected (*(int *)g_roomConnected_v)
#undef g_roomDim
#define g_roomDim ((float *)g_roomDim_v)
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
#define g_roomGameMode (*(signed char *)((u8 *)g_roomSettingsName_v + 0x23))
#undef g_roomInfoPacket
#define g_roomInfoPacket (*(APTR(u8) *)g_roomInfoPacket_v)
#undef g_roomJoinNeedsPassword
#define g_roomJoinNeedsPassword (*(int *)g_roomJoinNeedsPassword_v)
#undef g_roomJoinStarted
#define g_roomJoinStarted (*(int *)g_roomJoinStarted_v)
#undef g_roomLeavePacket
#define g_roomLeavePacket (*(APTR(u8) *)g_roomLeavePacket_v)
#undef g_roomList
#define g_roomList ((RoomRecord *)g_roomList_v)
#undef g_roomListAnswer
#define g_roomListAnswer (*(int *)g_roomListAnswer_v)
#undef g_roomListCount
#define g_roomListCount (*(int *)g_roomListCount_v)
#undef g_roomListPlayers
#define g_roomListPlayers (*(int *)g_roomListPlayers_v)
#undef g_roomListRefreshTimer
#define g_roomListRefreshTimer (*(float *)g_roomListRefreshTimer_v)
#undef g_roomListRequest
#define g_roomListRequest (*(APTR(u32) *)g_roomListRequest_v)
#undef g_roomLoginBottom
#define g_roomLoginBottom (*(int *)g_roomLoginBottom_v)
#undef g_roomLoginDue
#define g_roomLoginDue (*(int *)g_roomLoginDue_v)
#undef g_roomLoginLeft
#define g_roomLoginLeft (*(int *)g_roomLoginLeft_v)
#undef g_roomLoginRects
#define g_roomLoginRects ((int *)g_roomLoginRects_v)
#undef g_roomLoginRight
#define g_roomLoginRight (*(int *)g_roomLoginRight_v)
#undef g_roomLoginTop
#define g_roomLoginTop (*(int *)g_roomLoginTop_v)
#undef g_roomMap
#define g_roomMap (*(signed char *)((u8 *)g_roomSettingsName_v + 0x20))
#undef g_roomMaxPlayers
#define g_roomMaxPlayers (*(u8 *)((u8 *)g_roomSettingsName_v + 0x21))
#undef g_roomMech
#define g_roomMech ((u8 *)g_roomMech_v)
#undef g_roomMechKept
#define g_roomMechKept ((u8 *)g_roomMechKept_v)
#undef g_roomOutlines
#define g_roomOutlines ((int *)g_roomOutlines_v)
#undef g_roomPacket
#define g_roomPacket (*(APTR(RoomRecord) *)g_roomPacket_v)
#undef g_roomPanelsSliding
#define g_roomPanelsSliding (*(int *)g_roomPanelsSliding_v)
#undef g_roomRecFragLimit
#define g_roomRecFragLimit (*(u8 *)((u8 *)g_roomRecName_v + 0x24))
#undef g_roomRecGameMode
#define g_roomRecGameMode (*(signed char *)((u8 *)g_roomRecName_v + 0x23))
#undef g_roomRecMap
#define g_roomRecMap (*(signed char *)((u8 *)g_roomRecName_v + 0x20))
#undef g_roomRecMaxPlayers
#define g_roomRecMaxPlayers (*(signed char *)((u8 *)g_roomRecName_v + 0x21))
#undef g_roomRecName
#define g_roomRecName ((char *)g_roomRecName_v)
#undef g_roomRecRotation
#define g_roomRecRotation (*(u8 *)((u8 *)g_roomRecName_v + 0x22))
#undef g_roomRecTimeLimit
#define g_roomRecTimeLimit (*(u8 *)((u8 *)g_roomRecName_v + 0x25))
#undef g_roomRefreshing
#define g_roomRefreshing (*(int *)g_roomRefreshing_v)
#undef g_roomRequestOut
#define g_roomRequestOut (*(int *)g_roomRequestOut_v)
#undef g_roomRotation
#define g_roomRotation (*(u8 *)((u8 *)g_roomSettingsName_v + 0x22))
#undef g_roomSearchAnswerIn
#define g_roomSearchAnswerIn (*(int *)g_roomSearchAnswerIn_v)
#undef g_roomSearching
#define g_roomSearching (*(int *)g_roomSearching_v)
#undef g_roomSettingsName
#define g_roomSettingsName ((char *)g_roomSettingsName_v)
#undef g_roomSettingsRects
#define g_roomSettingsRects ((int *)g_roomSettingsRects_v)
#undef g_roomSlideEase
#define g_roomSlideEase (*(float *)g_roomSlideEase_v)
#undef g_roomState
#define g_roomState (*(int *)g_roomState_v)
#undef g_roomTimeLimit
#define g_roomTimeLimit (*(u8 *)((u8 *)g_roomSettingsName_v + 0x25))
#undef g_roomTunnelDepth
#define g_roomTunnelDepth (*(float *)g_roomTunnelDepth_v)
#undef g_roomUpdateNotice
#define g_roomUpdateNotice (*(int *)g_roomUpdateNotice_v)
#undef g_rotationOnOff
#define g_rotationOnOff ((char *)g_rotationOnOff_v)
#undef g_saveFileNames
#define g_saveFileNames ((char *)g_data.g_saveFileNames_)
#undef g_savedColourChoices
#define g_savedColourChoices ((float *)g_savedColourChoices_v)
#undef g_savedMechArm
#define g_savedMechArm (*(int *)((u8 *)g_savedMechPartIds_v + 0x8))
#undef g_savedMechBooster
#define g_savedMechBooster (*(int *)((u8 *)g_savedMechPartIds_v + 0x10))
#undef g_savedMechChest
#define g_savedMechChest (*(int *)((u8 *)g_savedMechPartIds_v + 0x4))
#undef g_savedMechHead
#define g_savedMechHead (*(int *)((u8 *)g_savedMechPartIds_v + 0x0))
#undef g_savedMechItemSlot4
#define g_savedMechItemSlot4 (*(int *)((u8 *)g_savedMechSlotItems_v + 0x0))
#undef g_savedMechItemSlot5
#define g_savedMechItemSlot5 (*(int *)((u8 *)g_savedMechSlotItems_v + 0x4))
#undef g_savedMechLeg
#define g_savedMechLeg (*(int *)((u8 *)g_savedMechPartIds_v + 0xc))
#undef g_savedMechPartIds
#define g_savedMechPartIds ((int *)g_savedMechPartIds_v)
#undef g_savedMechSlotItems
#define g_savedMechSlotItems ((int *)g_savedMechSlotItems_v)
#undef g_savedMechWeaponSlot0
#define g_savedMechWeaponSlot0 (*(int *)((u8 *)g_savedMechSlotItems_v + 0x8))
#undef g_savedMechWeaponSlot1
#define g_savedMechWeaponSlot1 (*(int *)((u8 *)g_savedMechSlotItems_v + 0xc))
#undef g_savedMechWeaponSlot2
#define g_savedMechWeaponSlot2 (*(int *)((u8 *)g_savedMechSlotItems_v + 0x10))
#undef g_savedMechWeaponSlot3
#define g_savedMechWeaponSlot3 (*(int *)((u8 *)g_savedMechSlotItems_v + 0x14))
#undef g_scanCharTable
#define g_scanCharTable ((int *)g_scanCharTable_v)
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
#undef g_searchResult
#define g_searchResult (*(int *)g_searchResult_v)
#undef g_selectedCharacter
#define g_selectedCharacter (*(int *)((u8 *)g_pilotSave_v + 0x100))
#undef g_sensitivitySlider
#define g_sensitivitySlider (*(int *)((u8 *)g_controlsEdit_v + 0x108))
#undef g_sentChatBlock
#define g_sentChatBlock (*(APTR(char) *)g_sentChatBlock_v)
#undef g_serialProviderGuid
#define g_serialProviderGuid ((u8 *)g_serialProviderGuid_v)
#undef g_serverAddressArg
#define g_serverAddressArg ((char *)g_serverAddressArg_v)
#undef g_serverAnswerIn
#define g_serverAnswerIn (*(int *)g_serverAnswerIn_v)
#undef g_serverHost
#define g_serverHost ((char *)g_data.g_serverHost_)
#undef g_serverList
#define g_serverList ((u8 *)g_serverList_v)
#undef g_serverListCount
#define g_serverListCount (*(int *)g_serverListCount_v)
#undef g_serverPing
#define g_serverPing ((int *)g_serverPing_v)
#undef g_serverPingCount
#define g_serverPingCount (*(int *)g_serverPingCount_v)
#undef g_serverPinged
#define g_serverPinged ((int *)g_serverPinged_v)
#undef g_serverPort
#define g_serverPort (*(u16 *)g_serverPort_v)
#undef g_serverSearching
#define g_serverSearching (*(int *)g_serverSearching_v)
#undef g_serviceProviderCount
#define g_serviceProviderCount (*(int *)g_serviceProviderCount_v)
#undef g_sessionDesc
#define g_sessionDesc ((DPSessionDesc2 *)g_sessionDesc_v)
#undef g_sessionFound
#define g_sessionFound (*(int *)g_sessionFound_v)
#undef g_sessionList
#define g_sessionList ((SessionEntry *)g_sessionList_v)
#undef g_sessionListOpen
#define g_sessionListOpen (*(int *)g_sessionListOpen_v)
#undef g_sessionTable
#define g_sessionTable ((SessionSlot *)g_sessionTable_v)
#undef g_setupArrowPressed
#define g_setupArrowPressed (*(int *)g_setupArrowPressed_v)
#undef g_setupCameraMode
#define g_setupCameraMode (*(int *)g_setupCameraMode_v)
#undef g_setupColourDim
#define g_setupColourDim ((float *)g_setupColourDim_v)
#undef g_setupColourLit
#define g_setupColourLit ((float *)g_setupColourLit_v)
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
#undef g_setupEffectVolume
#define g_setupEffectVolume (*(int *)((u8 *)g_soundEdited_v + 0x0))
#undef g_setupGraphicRect
#define g_setupGraphicRect ((int *)g_setupGraphicRect_v)
#undef g_setupGraphicRects
#define g_setupGraphicRects ((int *)g_setupGraphicRects_v)
#undef g_setupGraphicTop
#define g_setupGraphicTop (*(int *)((u8 *)g_setupGraphicRect_v + 0x4))
#undef g_setupMusicVolume
#define g_setupMusicVolume (*(int *)((u8 *)g_soundEdited_v + 0x4))
#undef g_setupPanelMoving
#define g_setupPanelMoving (*(int *)g_setupPanelMoving_v)
#undef g_setupPanelPos
#define g_setupPanelPos (*(float *)g_setupPanelPos_v)
#undef g_setupPressedClock
#define g_setupPressedClock (*(float *)g_setupPressedClock_v)
#undef g_setupResolution
#define g_setupResolution (*(int *)((u8 *)g_graphicEdited_v + 0x0))
#undef g_setupSliderRects
#define g_setupSliderRects ((int *)g_setupSliderRects_v)
#undef g_setupSound3D
#define g_setupSound3D (*(int *)((u8 *)g_soundEdited_v + 0x8))
#undef g_setupSoundLeft
#define g_setupSoundLeft (*(int *)((u8 *)g_setupSoundRect_v + 0x0))
#undef g_setupSoundRect
#define g_setupSoundRect ((int *)g_setupSoundRect_v)
#undef g_setupSoundRects
#define g_setupSoundRects ((int *)g_setupSoundRects_v)
#undef g_setupSoundRight
#define g_setupSoundRight (*(int *)((u8 *)g_setupSoundRect_v + 0x8))
#undef g_setupStereoReverse
#define g_setupStereoReverse (*(int *)((u8 *)g_soundEdited_v + 0xc))
#undef g_setupTab
#define g_setupTab (*(int *)g_setupTab_v)
#undef g_setupTopOutlines
#define g_setupTopOutlines ((int *)g_setupTopOutlines_v)
#undef g_setupTunnelAlpha
#define g_setupTunnelAlpha (*(float *)g_setupTunnelAlpha_v)
#undef g_setupTunnelDepth
#define g_setupTunnelDepth (*(float *)g_setupTunnelDepth_v)
#undef g_setupWallTurns
#define g_setupWallTurns ((float *)g_setupWallTurns_v)
#undef g_shapeDat
#define g_shapeDat ((u32 *)g_shapeDat_v)
#undef g_showCmd
#define g_showCmd (*(int *)g_showCmd_v)
#undef g_simpleMenu
#define g_simpleMenu (*(int *)g_simpleMenu_v)
#undef g_simpleMenuTexts
#define g_simpleMenuTexts ((char *)g_simpleMenuTexts_v)
#undef g_sinTable
#define g_sinTable ((float *)g_sinTable_v)
#undef g_skelDat
#define g_skelDat ((u32 *)g_skelDat_v)
#undef g_skirmishChosen
#define g_skirmishChosen (*(int *)g_skirmishChosen_v)
#undef g_skirmishColourDim
#define g_skirmishColourDim ((float *)g_skirmishColourDim_v)
#undef g_skirmishColourLit
#define g_skirmishColourLit ((float *)g_skirmishColourLit_v)
#undef g_skirmishInfo
#define g_skirmishInfo ((u8 *)g_skirmishInfo_v)
#undef g_skirmishInfo16Mode
#define g_skirmishInfo16Mode (g_data.g_skirmishInfo16Mode_)
#undef g_skirmishInfoCount
#define g_skirmishInfoCount (*(int *)g_skirmishInfoCount_v)
#undef g_skirmishLeft
#define g_skirmishLeft (*(int *)g_skirmishLeft_v)
#undef g_skirmishNewPartsNotice
#define g_skirmishNewPartsNotice (*(int *)g_skirmishNewPartsNotice_v)
#undef g_skirmishPreviewDue
#define g_skirmishPreviewDue (*(int *)g_skirmishPreviewDue_v)
#undef g_skirmishRect
#define g_skirmishRect ((int *)g_skirmishRect_v)
#undef g_skirmishRectLeft
#define g_skirmishRectLeft (*(int *)((u8 *)g_skirmishRect_v + 0x0))
#undef g_skirmishRectTop
#define g_skirmishRectTop (*(int *)((u8 *)g_skirmishRect_v + 0x4))
#undef g_skirmishRects
#define g_skirmishRects ((int *)g_skirmishRects_v)
#undef g_skirmishRoundShown
#define g_skirmishRoundShown (*(int *)g_skirmishRoundShown_v)
#undef g_skirmishShowBackground
#define g_skirmishShowBackground (*(int *)g_skirmishShowBackground_v)
#undef g_skirmishState
#define g_skirmishState (*(int *)g_skirmishState_v)
#undef g_slotCams
#define g_slotCams ((float *)g_slotCams_v)
#undef g_slotTakenFlag
#define g_slotTakenFlag (*(int *)g_slotTakenFlag_v)
#undef g_slotTextures
#define g_slotTextures ((int *)g_slotTextures_v)
#undef g_sortBounds
#define g_sortBounds ((int *)g_sortBounds_v)
#undef g_sortState
#define g_sortState ((u8 *)g_sortState_v)
#undef g_sound3D
#define g_sound3D (*(int *)((u8 *)g_soundSettings_v + 0x8))
#undef g_soundBaseVolume
#define g_soundBaseVolume (*(int *)g_soundBaseVolume_v)
#undef g_soundEdited
#define g_soundEdited ((int *)g_soundEdited_v)
#undef g_soundOn
#define g_soundOn (*(int *)g_soundOn_v)
#undef g_soundSettings
#define g_soundSettings ((int *)g_soundSettings_v)
#undef g_soundTable
#define g_soundTable ((u32 *)g_soundTable_v)
#undef g_soundVolume
#define g_soundVolume (*(int *)((u8 *)g_soundSettings_v + 0x0))
#undef g_spinPanels
#define g_spinPanels ((u8 *)g_spinPanels_v)
#undef g_spiralTextures
#define g_spiralTextures ((int *)g_spiralTextures_v)
#undef g_stageDir
#define g_stageDir ((char *)g_stageDir_v)
#undef g_startTicks
#define g_startTicks (*(u32 *)g_startTicks_v)
#undef g_statBarTargets
#define g_statBarTargets ((float *)g_statBarTargets_v)
#undef g_statBars
#define g_statBars ((float *)g_statBars_v)
#undef g_statBarsStale
#define g_statBarsStale (*(int *)g_statBarsStale_v)
#undef g_stereoReverse
#define g_stereoReverse (*(int *)((u8 *)g_soundSettings_v + 0xc))
#undef g_storedConnection
#define g_storedConnection (*(APTR(void) *)g_storedConnection_v)
#undef g_tan10Table
#define g_tan10Table ((float *)g_tan10Table_v)
#undef g_tanTable
#define g_tanTable ((float *)g_tanTable_v)
#undef g_tcpDns
#define g_tcpDns ((char *)g_tcpDns_v)
#undef g_tcpProviderGuid
#define g_tcpProviderGuid ((u8 *)g_tcpProviderGuid_v)
#undef g_teamNames
#define g_teamNames ((char *)g_teamNames_v)
#undef g_textBottom
#define g_textBottom (*(int *)g_textBottom_v)
#undef g_textCharWidth
#define g_textCharWidth (*(int *)g_textCharWidth_v)
#undef g_textColour
#define g_textColour ((Colour *)g_textColour_v)
#undef g_textEndX
#define g_textEndX (*(int *)g_textEndX_v)
#undef g_textEndY
#define g_textEndY (*(int *)g_textEndY_v)
#undef g_textFieldOpen
#define g_textFieldOpen (*(int *)g_textFieldOpen_v)
#undef g_textHitBottom
#define g_textHitBottom (*(int *)g_textHitBottom_v)
#undef g_textWrapX
#define g_textWrapX (*(int *)g_textWrapX_v)
#undef g_texture128x128
#define g_texture128x128 ((u8 *)g_texture128x128_v)
#undef g_texture128x128Vtable
#define g_texture128x128Vtable (*(u32 *)((u8 *)g_texture128x128_v + 0x0))
#undef g_texture128x64
#define g_texture128x64 ((u8 *)g_texture128x64_v)
#undef g_texture128x64Vtable
#define g_texture128x64Vtable (*(u32 *)((u8 *)g_texture128x64_v + 0x0))
#undef g_texture256x128
#define g_texture256x128 ((u8 *)g_texture256x128_v)
#undef g_texture256x128Vtable
#define g_texture256x128Vtable (*(u32 *)((u8 *)g_texture256x128_v + 0x0))
#undef g_texture256x256
#define g_texture256x256 ((u8 *)g_texture256x256_v)
#undef g_texture256x256Vtable
#define g_texture256x256Vtable (*(u32 *)((u8 *)g_texture256x256_v + 0x0))
#undef g_texture256x64
#define g_texture256x64 ((u8 *)g_texture256x64_v)
#undef g_texture256x64Vtable
#define g_texture256x64Vtable (*(u32 *)((u8 *)g_texture256x64_v + 0x0))
#undef g_texture64x64
#define g_texture64x64 ((u8 *)g_texture64x64_v)
#undef g_texture64x64Vtable
#define g_texture64x64Vtable (*(u32 *)((u8 *)g_texture64x64_v + 0x0))
#undef g_textureManager
#define g_textureManager (*(u32 *)((u8 *)g_textureManagerObject_v + 0x0))
#undef g_textureManagerObject
#define g_textureManagerObject ((u32 *)g_textureManagerObject_v)
#undef g_textures
#define g_textures (*(APTR(TextureManager) *)g_textures_v)
#undef g_timeLimit
#define g_timeLimit (*(int *)g_timeLimit_v)
#undef g_timerClocks
#define g_timerClocks ((double *)g_timerClocks_v)
#undef g_timerFirstCall
#define g_timerFirstCall (*(int *)g_timerFirstCall_v)
#undef g_timerFrequency
#define g_timerFrequency (*(u64 *)g_timerFrequency_v)
#undef g_timerLastCount
#define g_timerLastCount (*(u32 *)g_timerLastCount_v)
#undef g_timerRepeatCount
#define g_timerRepeatCount (*(int *)g_timerRepeatCount_v)
#undef g_timerShift
#define g_timerShift (*(int *)g_timerShift_v)
#undef g_timerTick
#define g_timerTick (*(double *)g_timerTick_v)
#undef g_titleCloseFrames
#define g_titleCloseFrames (*(int *)g_titleCloseFrames_v)
#undef g_titleClosing
#define g_titleClosing (*(int *)g_titleClosing_v)
#undef g_titleSpread
#define g_titleSpread ((int *)g_titleSpread_v)
#undef g_totalWeight
#define g_totalWeight (*(float *)g_totalWeight_v)
#undef g_tunnelFlyingIn
#define g_tunnelFlyingIn (*(int *)g_tunnelFlyingIn_v)
#undef g_tunnelPulse
#define g_tunnelPulse (*(float *)g_tunnelPulse_v)
#undef g_tunnelPulseStep
#define g_tunnelPulseStep (*(float *)g_tunnelPulseStep_v)
#undef g_tunnelRings
#define g_tunnelRings (*(int *)g_tunnelRings_v)
#undef g_tunnelStep
#define g_tunnelStep (*(int *)g_tunnelStep_v)
#undef g_tunnelStepF
#define g_tunnelStepF (*(float *)g_tunnelStepF_v)
#undef g_tunnelStripeScroll
#define g_tunnelStripeScroll (*(float *)g_tunnelStripeScroll_v)
#undef g_typedArenaAddress
#define g_typedArenaAddress (*(int *)((u8 *)g_typedArenaAddressText_v + 0x0))
#undef g_typedArenaAddress4
#define g_typedArenaAddress4 (*(int *)((u8 *)g_typedArenaAddressText_v + 0x4))
#undef g_typedArenaAddressText
#define g_typedArenaAddressText ((char *)g_typedArenaAddressText_v)
#undef g_typingAccountEmail
#define g_typingAccountEmail (*(int *)g_typingAccountEmail_v)
#undef g_typingAccountName
#define g_typingAccountName (*(int *)g_typingAccountName_v)
#undef g_typingAccountPassword
#define g_typingAccountPassword (*(int *)g_typingAccountPassword_v)
#undef g_typingAccountRepeat
#define g_typingAccountRepeat (*(int *)g_typingAccountRepeat_v)
#undef g_typingArenaAddress
#define g_typingArenaAddress (*(int *)g_typingArenaAddress_v)
#undef g_typingArenaJoinPassword
#define g_typingArenaJoinPassword (*(int *)g_typingArenaJoinPassword_v)
#undef g_typingArenaPassword
#define g_typingArenaPassword (*(int *)g_typingArenaPassword_v)
#undef g_typingArenaPlayerName
#define g_typingArenaPlayerName (*(int *)g_typingArenaPlayerName_v)
#undef g_typingLoginId
#define g_typingLoginId (*(int *)g_typingLoginId_v)
#undef g_typingLoginPassword
#define g_typingLoginPassword (*(int *)g_typingLoginPassword_v)
#undef g_typingRoomJoinPassword
#define g_typingRoomJoinPassword (*(int *)g_typingRoomJoinPassword_v)
#undef g_unlit
#define g_unlit (g_data.g_unlit_)
#undef g_unlockTablesByProgress
#define g_unlockTablesByProgress ((u8 *)g_unlockTablesByProgress_v)
#undef g_unlockTablesLadder
#define g_unlockTablesLadder ((u8 *)g_unlockTablesLadder_v)
#undef g_unlockedLevel
#define g_unlockedLevel (*(int *)g_unlockedLevel_v)
#undef g_unusedAccountWord
#define g_unusedAccountWord (*(int *)g_unusedAccountWord_v)
#undef g_unusedActive
#define g_unusedActive (*(u32 *)g_unusedActive_v)
#undef g_unusedArenaCamWord
#define g_unusedArenaCamWord (*(u32 *)g_unusedArenaCamWord_v)
#undef g_unusedArenaFloat
#define g_unusedArenaFloat (*(float *)g_unusedArenaFloat_v)
#undef g_unusedArenaWord
#define g_unusedArenaWord (*(int *)g_unusedArenaWord_v)
#undef g_unusedArmcPoint0Y
#define g_unusedArmcPoint0Y (*(float *)((u8 *)g_armcViewPoints_v + 0x4))
#undef g_unusedArmcPoint3Y
#define g_unusedArmcPoint3Y (*(float *)((u8 *)g_armcViewPoints_v + 0x34))
#undef g_unusedArmcPoint5Y
#define g_unusedArmcPoint5Y (*(float *)((u8 *)g_armcViewPoints_v + 0x54))
#undef g_unusedArmcViewCountdown
#define g_unusedArmcViewCountdown (*(float *)g_unusedArmcViewCountdown_v)
#undef g_unusedArmcWord1
#define g_unusedArmcWord1 (*(int *)g_unusedArmcWord1_v)
#undef g_unusedArmcWord2
#define g_unusedArmcWord2 (*(int *)g_unusedArmcWord2_v)
#undef g_unusedArmcWord3
#define g_unusedArmcWord3 (*(int *)g_unusedArmcWord3_v)
#undef g_unusedArmcWord4
#define g_unusedArmcWord4 (*(int *)g_unusedArmcWord4_v)
#undef g_unusedBriefingWord
#define g_unusedBriefingWord (*(int *)g_unusedBriefingWord_v)
#undef g_unusedClock1
#define g_unusedClock1 (*(double *)g_unusedClock1_v)
#undef g_unusedClock2
#define g_unusedClock2 (*(double *)g_unusedClock2_v)
#undef g_unusedClock3
#define g_unusedClock3 (*(double *)g_unusedClock3_v)
#undef g_unusedDplayWord1
#define g_unusedDplayWord1 (*(int *)g_unusedDplayWord1_v)
#undef g_unusedDplayWord2
#define g_unusedDplayWord2 (*(int *)g_unusedDplayWord2_v)
#undef g_unusedDplayWord3
#define g_unusedDplayWord3 (*(int *)g_unusedDplayWord3_v)
#undef g_unusedDplayWord4
#define g_unusedDplayWord4 (*(int *)g_unusedDplayWord4_v)
#undef g_unusedFreeCamCounter
#define g_unusedFreeCamCounter (*(int *)g_unusedFreeCamCounter_v)
#undef g_unusedFreeCamMoveWord
#define g_unusedFreeCamMoveWord (*(u32 *)g_unusedFreeCamMoveWord_v)
#undef g_unusedHighlightAlpha
#define g_unusedHighlightAlpha (*(float *)g_unusedHighlightAlpha_v)
#undef g_unusedInitWord
#define g_unusedInitWord (*(int *)g_unusedInitWord_v)
#undef g_unusedKeyTable2
#define g_unusedKeyTable2 ((int *)g_unusedKeyTable2_v)
#undef g_unusedKeyTable2Flags
#define g_unusedKeyTable2Flags (*(u16 *)g_unusedKeyTable2Flags_v)
#undef g_unusedKeyTable2Word0
#define g_unusedKeyTable2Word0 (*(int *)g_unusedKeyTable2Word0_v)
#undef g_unusedKeyTable2Word1
#define g_unusedKeyTable2Word1 (*(int *)g_unusedKeyTable2Word1_v)
#undef g_unusedKeyTable2Word2
#define g_unusedKeyTable2Word2 (*(int *)g_unusedKeyTable2Word2_v)
#undef g_unusedLoginWord
#define g_unusedLoginWord (*(int *)g_unusedLoginWord_v)
#undef g_unusedLogoFade
#define g_unusedLogoFade (*(float *)g_unusedLogoFade_v)
#undef g_unusedMechStat
#define g_unusedMechStat (*(int *)g_unusedMechStat_v)
#undef g_unusedMenuReturnWord
#define g_unusedMenuReturnWord (*(int *)g_unusedMenuReturnWord_v)
#undef g_unusedNetResetWord
#define g_unusedNetResetWord (*(int *)g_unusedNetResetWord_v)
#undef g_unusedPingWord1
#define g_unusedPingWord1 (*(int *)g_unusedPingWord1_v)
#undef g_unusedPingWord2
#define g_unusedPingWord2 (*(int *)g_unusedPingWord2_v)
#undef g_unusedPostMatchFlag
#define g_unusedPostMatchFlag (*(int *)g_unusedPostMatchFlag_v)
#undef g_unusedProfileCameraSpeed
#define g_unusedProfileCameraSpeed (*(float *)g_unusedProfileCameraSpeed_v)
#undef g_unusedProfileCameraTime
#define g_unusedProfileCameraTime (*(int *)g_unusedProfileCameraTime_v)
#undef g_unusedProfileCameraWord
#define g_unusedProfileCameraWord (*(int *)g_unusedProfileCameraWord_v)
#undef g_unusedProfileCameraZoom
#define g_unusedProfileCameraZoom (*(float *)g_unusedProfileCameraZoom_v)
#undef g_unusedReplayListWord1
#define g_unusedReplayListWord1 (*(int *)g_unusedReplayListWord1_v)
#undef g_unusedReplayListWord2
#define g_unusedReplayListWord2 (*(int *)g_unusedReplayListWord2_v)
#undef g_unusedReplaySelectWord
#define g_unusedReplaySelectWord (*(int *)g_unusedReplaySelectWord_v)
#undef g_unusedRoomCamWord
#define g_unusedRoomCamWord (*(u32 *)g_unusedRoomCamWord_v)
#undef g_unusedRoomFloat
#define g_unusedRoomFloat (*(float *)g_unusedRoomFloat_v)
#undef g_unusedRoomListWord
#define g_unusedRoomListWord (*(int *)g_unusedRoomListWord_v)
#undef g_unusedRoomWord
#define g_unusedRoomWord (*(int *)g_unusedRoomWord_v)
#undef g_unusedSessionWord
#define g_unusedSessionWord (*(int *)g_unusedSessionWord_v)
#undef g_unusedStartupTable
#define g_unusedStartupTable ((int *)g_unusedStartupTable_v)
#undef g_unusedStartupWord1
#define g_unusedStartupWord1 (*(int *)g_unusedStartupWord1_v)
#undef g_unusedStartupWord2
#define g_unusedStartupWord2 (*(u32 *)g_unusedStartupWord2_v)
#undef g_unusedStartupWord3
#define g_unusedStartupWord3 (*(int *)g_unusedStartupWord3_v)
#undef g_updateNoticeRects
#define g_updateNoticeRects ((int *)g_updateNoticeRects_v)
#undef g_vecOrigin
#define g_vecOrigin (*(float *)((u8 *)g_vecOriginXyz_v + 0x0))
#undef g_vecOriginXyz
#define g_vecOriginXyz ((float *)g_vecOriginXyz_v)
#undef g_vecUnitX
#define g_vecUnitX ((float *)g_vecUnitX_v)
#undef g_vecUnitY
#define g_vecUnitY ((float *)g_vecUnitY_v)
#undef g_vecUnitZ
#define g_vecUnitZ (*(float *)((u8 *)g_vecUnitZXyz_v + 0x0))
#undef g_vecUnitZXyz
#define g_vecUnitZXyz ((float *)g_vecUnitZXyz_v)
#undef g_vecZero
#define g_vecZero (*(float *)((u8 *)g_vecZeroXyz_v + 0x0))
#undef g_vecZero2
#define g_vecZero2 ((float *)g_vecZero2_v)
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
#undef g_viewFpsTexts
#define g_viewFpsTexts ((char *)g_viewFpsTexts_v)
#undef g_viewNear
#define g_viewNear (*(float *)g_viewNear_v)
#undef g_viewedPartAmmoPerShot
#define g_viewedPartAmmoPerShot (*(int *)((u8 *)g_partRecords_v + 0x348))
#undef g_viewedPartAmmoType
#define g_viewedPartAmmoType (*(int *)((u8 *)g_partRecords_v + 0x344))
#undef g_watchChatOpen
#define g_watchChatOpen (*(int *)g_watchChatOpen_v)
#undef g_weaponCount
#define g_weaponCount (*(int *)g_weaponCount_v)
#undef g_weaponListTable
#define g_weaponListTable ((int *)g_weaponListTable_v)
#undef g_whiteFade
#define g_whiteFade (*(float *)g_whiteFade_v)
#undef g_windowClass
#define g_windowClass ((u8 *)g_windowClass_v)
#undef g_windowDC
#define g_windowDC (*(APTR(void) *)g_windowDC_v)
#undef g_writeMatchLog
#define g_writeMatchLog (*(int *)g_writeMatchLog_v)
#undef k_0_00125f
#define k_0_00125f (g_rdata.k_0_00125f_)
#undef k_0_001f
#define k_0_001f (g_rdata.k_0_001f_)
#undef k_0_00390625f
#define k_0_00390625f (g_rdata.k_0_00390625f_)
#undef k_0_0051f
#define k_0_0051f (g_rdata.k_0_0051f_)
#undef k_0_005f_4aa428
#define k_0_005f_4aa428 (g_rdata.k_0_005f_4aa428_)
#undef k_0_0078125f
#define k_0_0078125f (g_rdata.k_0_0078125f_)
#undef k_0_01f
#define k_0_01f (g_rdata.k_0_01f_)
#undef k_0_025f
#define k_0_025f (g_rdata.k_0_025f_)
#undef k_0_03f
#define k_0_03f (g_rdata.k_0_03f_)
#undef k_0_06666667f
#define k_0_06666667f (g_rdata.k_0_06666667f_)
#undef k_0_07f
#define k_0_07f (g_rdata.k_0_07f_)
#undef k_0_1f
#define k_0_1f (g_rdata.k_0_1f_)
#undef k_0_25f
#define k_0_25f (g_rdata.k_0_25f_)
#undef k_0_28125f
#define k_0_28125f (g_rdata.k_0_28125f_)
#undef k_0_2f_4aa400
#define k_0_2f_4aa400 (g_rdata.k_0_2f_4aa400_)
#undef k_0_3
#define k_0_3 (g_rdata.k_0_3_)
#undef k_0_333f
#define k_0_333f (g_rdata.k_0_333f_)
#undef k_0_7083333f
#define k_0_7083333f (g_rdata.k_0_7083333f_)
#undef k_0_75f
#define k_0_75f (g_rdata.k_0_75f_)
#undef k_0_95f
#define k_0_95f (g_rdata.k_0_95f_)
#undef k_1
#define k_1 (g_rdata.k_1_)
#undef k_100
#define k_100 (g_rdata.k_100_)
#undef k_10000f
#define k_10000f (g_rdata.k_10000f_)
#undef k_100f
#define k_100f (g_rdata.k_100f_)
#undef k_10f
#define k_10f (g_rdata.k_10f_)
#undef k_120f
#define k_120f (g_rdata.k_120f_)
#undef k_128f
#define k_128f (g_rdata.k_128f_)
#undef k_14_0625f
#define k_14_0625f (g_rdata.k_14_0625f_)
#undef k_1500f
#define k_1500f (g_rdata.k_1500f_)
#undef k_1500f_4a9700
#define k_1500f_4a9700 (g_rdata.k_1500f_4a9700_)
#undef k_150f
#define k_150f (g_rdata.k_150f_)
#undef k_16f
#define k_16f (g_rdata.k_16f_)
#undef k_1800f
#define k_1800f (g_rdata.k_1800f_)
#undef k_180f
#define k_180f (g_rdata.k_180f_)
#undef k_1_1f
#define k_1_1f (g_rdata.k_1_1f_)
#undef k_1_4
#define k_1_4 (g_rdata.k_1_4_)
#undef k_1_40625f
#define k_1_40625f (g_rdata.k_1_40625f_)
#undef k_1f
#define k_1f (g_rdata.k_1f_)
#undef k_2000000
#define k_2000000 (g_rdata.k_2000000_)
#undef k_200000f
#define k_200000f (g_rdata.k_200000f_)
#undef k_2000f
#define k_2000f (g_rdata.k_2000f_)
#undef k_200f
#define k_200f (g_rdata.k_200f_)
#undef k_20f
#define k_20f (g_rdata.k_20f_)
#undef k_2200f
#define k_2200f (g_rdata.k_2200f_)
#undef k_23
#define k_23 (g_rdata.k_23_)
#undef k_25
#define k_25 (g_rdata.k_25_)
#undef k_256f
#define k_256f (g_rdata.k_256f_)
#undef k_2_25f
#define k_2_25f (g_rdata.k_2_25f_)
#undef k_30000f
#define k_30000f (g_rdata.k_30000f_)
#undef k_3000f
#define k_3000f (g_rdata.k_3000f_)
#undef k_300f
#define k_300f (g_rdata.k_300f_)
#undef k_38f
#define k_38f (g_rdata.k_38f_)
#undef k_3_6f
#define k_3_6f (g_rdata.k_3_6f_)
#undef k_4000f
#define k_4000f (g_rdata.k_4000f_)
#undef k_400f
#define k_400f (g_rdata.k_400f_)
#undef k_450f
#define k_450f (g_rdata.k_450f_)
#undef k_45f
#define k_45f (g_rdata.k_45f_)
#undef k_49f
#define k_49f (g_rdata.k_49f_)
#undef k_4f
#define k_4f (g_rdata.k_4f_)
#undef k_5000f
#define k_5000f (g_rdata.k_5000f_)
#undef k_500f
#define k_500f (g_rdata.k_500f_)
#undef k_50f
#define k_50f (g_rdata.k_50f_)
#undef k_550f
#define k_550f (g_rdata.k_550f_)
#undef k_60
#define k_60 (g_rdata.k_60_)
#undef k_60f
#define k_60f (g_rdata.k_60f_)
#undef k_69_9
#define k_69_9 (g_rdata.k_69_9_)
#undef k_6_66f
#define k_6_66f (g_rdata.k_6_66f_)
#undef k_75f
#define k_75f (g_rdata.k_75f_)
#undef k_8
#define k_8 (g_rdata.k_8_)
#undef k_890f
#define k_890f (g_rdata.k_890f_)
#undef k_9000000f
#define k_9000000f (g_rdata.k_9000000f_)
#undef k_900f
#define k_900f (g_rdata.k_900f_)
#undef k_90f
#define k_90f (g_rdata.k_90f_)
#undef k_armcDistanceRoom
#define k_armcDistanceRoom (g_rdata.k_armcDistanceRoom_)
#undef k_cameraSnapDistance
#define k_cameraSnapDistance (g_rdata.k_cameraSnapDistance_)
#undef k_m0_001f
#define k_m0_001f (g_rdata.k_m0_001f_)
#undef k_m0_002f
#define k_m0_002f (g_rdata.k_m0_002f_)
#undef k_m0_5f
#define k_m0_5f (g_rdata.k_m0_5f_)
#undef k_m100f
#define k_m100f (g_rdata.k_m100f_)
#undef k_m1100f
#define k_m1100f (g_rdata.k_m1100f_)
#undef k_m1101f
#define k_m1101f (g_rdata.k_m1101f_)
#undef k_m1500f
#define k_m1500f (g_rdata.k_m1500f_)
#undef k_m164f
#define k_m164f (g_rdata.k_m164f_)
#undef k_m168f
#define k_m168f (g_rdata.k_m168f_)
#undef k_m180f
#define k_m180f (g_rdata.k_m180f_)
#undef k_m1f_4a95f4
#define k_m1f_4a95f4 (g_rdata.k_m1f_4a95f4_)
#undef k_m360f
#define k_m360f (g_rdata.k_m360f_)
#undef k_m450f
#define k_m450f (g_rdata.k_m450f_)
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
#undef k_panelSlideTarget
#define k_panelSlideTarget (g_rdata.k_panelSlideTarget_)
#undef k_pi
#define k_pi (g_rdata.k_pi_)
#undef k_tenth
#define k_tenth (g_rdata.k_tenth_)
/* names that are no member of their own type: at IMG()'s place */
#undef k_panelSlideEnd
#define k_panelSlideEnd (*AP(double, IMG(0x4a9440)))
#undef k_degToRad
#define k_degToRad (*AP(double, IMG(0x4aa290)))
#undef k_tenthDegreeRad
#define k_tenthDegreeRad (*AP(double, IMG(0x4aa298)))
#undef k_15f
#define k_15f (*AP(float, IMG(0x4aa498)))
#undef k_oneOver180
#define k_oneOver180 (*AP(double, IMG(0x4a9540)))
#undef g_energyBarWidth
#define g_energyBarWidth (*AP(float, IMG(0xb68ce0)))
#undef g_energyBarHeight
#define g_energyBarHeight (*AP(float, IMG(0xb68ce4)))
#undef k_3600f
#define k_3600f (*AP(float, IMG(0x4a94c8)))
#undef k_0f
#define k_0f (*AP(float, IMG(0x4a93e8)))
#undef k_2f
#define k_2f (*AP(float, IMG(0x4a93fc)))
#undef k_0_5f
#define k_0_5f (*AP(float, IMG(0x4a942c)))
#undef k_360f
#define k_360f (*AP(float, IMG(0x4a9460)))
#undef k_m1f
#define k_m1f (*AP(float, IMG(0x4a9474)))
#undef k_m2f
#define k_m2f (*AP(float, IMG(0x4a94a8)))
#undef k_0_01
#define k_0_01 (*AP(double, IMG(0x4a94c0)))
#undef k_0_9f
#define k_0_9f (*AP(float, IMG(0x4a9508)))
#undef k_m1000f
#define k_m1000f (*AP(float, IMG(0x4a95c0)))
#undef k_27_7778f
#define k_27_7778f (*AP(float, IMG(0x4a9750)))
#undef k_1em8f
#define k_1em8f (*AP(float, IMG(0x4aa268)))
#undef k_1em8
#define k_1em8 (*AP(double, IMG(0x4aa458)))
#undef g_imp_wsprintfA
#define g_imp_wsprintfA (*AP(APTR(void), IMG(0x4a92f0)))
#undef k_5f
#define k_5f (*AP(float, IMG(0x4a93d0)))
#undef k_1000000f
#define k_1000000f (*AP(float, IMG(0x4a94ec)))
#undef k_0_2f
#define k_0_2f (*AP(float, IMG(0x4a94f8)))
#undef k_640f
#define k_640f (*AP(float, IMG(0x4a9510)))
#undef k_3f
#define k_3f (*AP(float, IMG(0x4a9534)))
#undef k_27
#define k_27 (*AP(double, IMG(0x4aa408)))
#undef g_scene
#define g_scene (*AP(APTR(Scene), IMG(0x9087b4)))
#undef g_white
#define g_white (*AP(u32, IMG(0xa1f23c)))
#undef k_1_95f
#define k_1_95f (*AP(float, IMG(0x4a9710)))
#undef k_26f
#define k_26f (*AP(float, IMG(0x4aa27c)))
#undef k_0_002777778f
#define k_0_002777778f (*AP(float, IMG(0x4a9488)))
#undef k_0_2777778f
#define k_0_2777778f (*AP(float, IMG(0x4a9490)))
#undef k_m200f
#define k_m200f (*AP(float, IMG(0x4a94a0)))
#undef k_105f
#define k_105f (*AP(float, IMG(0x4a94b4)))
#undef k_0_001111111f
#define k_0_001111111f (*AP(float, IMG(0x4a971c)))
#undef k_0_0005555556f
#define k_0_0005555556f (*AP(float, IMG(0x4a9724)))
#undef k_572_9578f
#define k_572_9578f (*AP(float, IMG(0x4a9738)))
#undef k_250000f
#define k_250000f (*AP(float, IMG(0x4a9740)))
#undef k_170f
#define k_170f (*AP(float, IMG(0x4a9748)))
#undef k_0_04f
#define k_0_04f (*AP(float, IMG(0x4aa25c)))
#undef k_0_125f
#define k_0_125f (*AP(float, IMG(0x4aa274)))
#undef k_0_01666667f
#define k_0_01666667f (*AP(float, IMG(0x4aa2a8)))
#undef k_0_001745329f
#define k_0_001745329f (*AP(float, IMG(0x4aa44c)))
#undef k_0_85f
#define k_0_85f (*AP(float, IMG(0x4aa478)))
#undef k_14_11765f
#define k_14_11765f (*AP(float, IMG(0x4aa48c)))
