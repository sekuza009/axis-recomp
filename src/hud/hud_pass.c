/* hud_pass.c: the in-match 2D pass, once per frame after the 3D scene: the screen cleared as needed, the scene's
   transparent and overlay parts drawn, then each HUD element by the match's state. Five of the HUD calls are
   wrapped by the patch DLL (each element anchored for wide screens), so they go through their call sites. */
#include "../game.h"


/* 0x4982f0: the 2D pass (only while scene->matchDrawing) */
void THISCALL (hud_pass)(Scene *scene)
{
	char text[256];
	if (!scene->matchDrawing)
		return;
	tex_clearSetCounters(g_textures);
	ViewVolume_clearDrawCounts(&scene->view);
	if (scene->clearOn == 1) {
		glClearColor_stored(scene->clearColour);
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	} else {
		glClearDepth(1.0);
		glClear(GL_DEPTH_BUFFER_BIT);
	}
	gfx_setProjectionHud(1, 1.0f);

	if (scene->scriptMode != 1) {
		ViewVolume_captureMatrices(&scene->view, scene->projection, scene->modelview);
		ViewVolume_reset(&scene->view);
		/* the player the view shows is marked (the watched one, or the local one in camera mode 2) */
		if (scene->playing == 0) {
			if (scene->cameraSlot == 2 && scene->watchedPlayer >= 0)
				scene->players[scene->watchedPlayer].viewMarked = 1;
		} else if (scene->playing == 1 && scene->cameraMode == 2 && scene->localPlayer >= 0) {
			scene->players[scene->localPlayer].viewMarked = 1;
		}
		sky_draw(STAGE(scene), view_farPlane());
		ground_buildDrawLists(STAGE(scene), &scene->view, view_farPlane());
		stage_drawObjects(STAGE(scene), &scene->view);
		stage_drawActors(STAGE(scene), &scene->view, 0);
		stage_drawBullets(STAGE(scene), &scene->view);
		stage_drawProjectiles(STAGE(scene), &scene->view);
		stage_drawItems(STAGE(scene), &scene->view);
		if (scene->fogOn == 1) {
			stage_setFog(STAGE(scene), &scene->fogColour, scene->fogParams[0], scene->fogParams[1], scene->fogParams[2]);
			glEnable(GL_FOG);
		}
		render_drawObjects(&scene->view, scene->renderMode, scene->clockFraction);
		glDisable(GL_FOG);
	}
	glClear(GL_DEPTH_BUFFER_BIT);
	ViewVolume_reset(&scene->view);
	stage_drawActors(STAGE(scene), &scene->view, 1);
	render_drawObjects(&scene->view, scene->renderMode, scene->clockFraction);
	if (scene->scriptMode != 0) {
		if (scene->scriptMode == 2) {
			glClearDepth(1.0);
			glClear(GL_DEPTH_BUFFER_BIT);
		}
		int height = gfx_getHeight();
		script_notifyObject(STAGE(scene), 0, 0, gfx_getWidth(), height);
	}
	gfx_setProjectionHud(0, 1.0f);

	if (scene->hudHidden == 0) {
		if (scene->scriptMode == 0) {
			int local = scene->localPlayer;
			if (local >= 0 && !scene->matchOver && !scene->matchLeaving)
				PATCHED_THISCALL(0x498580, void, Scene *)(scene);                 /* hud_drawPlayerMarkers */
			if (local >= 0 && scene->players[local].state == 1 && !scene->matchOver && !scene->matchLeaving)
				PATCHED_THISCALL(0x4985c4, void, Scene *)(scene);                 /* hud_drawLockOn */
			if (!scene->escMenuOpen && !scene->helpOpen) {
				/* the main HUD of the player the view follows: the local one while playing, else the watched one */
				if (scene->localPlayer >= 0) {
					int shown = scene->playing == 1 ? scene->players[scene->localPlayer].state == 1
					          : scene->playing == 0 && scene->players[scene->watchedPlayer].state == 1;
					if (shown && !scene->matchOver && !scene->matchLeaving)
						PATCHED_THISCALL(0x498654, void, Scene *)(scene);             /* hud_drawMain */
				}
				if (scene->rankingKey == 1 || scene->rankingShown == 1
				    || (scene->localPlayer >= 0 && scene->players[scene->localPlayer].state == 2)
				    || scene->matchOver == 1 || scene->matchLeaving == 1)
					PATCHED_THISCALL(0x4986a0, void, Scene *)(scene);             /* hud_drawRanking */
				if (scene->localPlayer >= 0 && scene->localTeam >= 0
				    && scene->players[scene->localPlayer].active == 0 && scene->chatMode == 0
				    && !scene->matchOver && !scene->matchLeaving)
					hud_drawPressFire(scene);
			}
			if (scene->messagesHidden == 0 && scene->msgFade > 0.0f)
				replay_drawMessage(scene);
			if (scene->chatMode != 0)
				hud_drawChatInput(scene);
			if (!scene->matchOver && !scene->matchLeaving)
				hud_drawClock(scene);
			if (scene->matchOver == 1 && scene->players[scene->ranking[0]].state == 1)
				hud_drawMatchResult(scene);
			if (scene->playing == 0) {
				replay_drawFollowedName(scene);
				if (scene->playing == 0 && scene->cameraSlot >= 0 && scene->watchedPlayer >= 0) {
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					hud_drawIcon(scene, 0x10, 0x10, 6);
					text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
					int slot = scene->cameraSlot;
					sprintf(text, "%d", slot > 0 ? slot : slot + 10);
					text_drawSized(0x28, 0x10, text, 16);
				}
			}
		}
		if (scene->teamGame == 1)
			hud_drawTeamScores(scene);
		debug_traceStripped(scene);
		if (g_showFps == 1)
			PATCHED_THISCALL(0x498862, void, Scene *)(scene);                     /* hud_drawFps */
		if (scene->helpOpen == 1)
			hud_drawHelp(scene);
		if (scene->escMenuOpen == 1)
			hud_drawEscMenu(scene);
		if (scene->recording == 1)
			hud_drawRecordIndicator(scene);
	}
	if ((scene->readyTimer > 0.0f && !scene->matchOver) || scene->restartTimer > 0.0f)
		hud_drawReadyStart(scene);
}
