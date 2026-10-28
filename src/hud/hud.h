/* hud.h: helpers shared by the HUD files (hud_overlay.c). The HUD is laid out in 640 x 480 units and scaled to
   the screen. */
#ifndef HUD_H
#define HUD_H

/* a length in HUD units to screen pixels, as the original computes it: divided by the units per pixel (640 /
   width, 480 / height), the screen size asked for each time */
int hud_scaleX(float units);
int hud_scaleY(float units);
/* a whole HUD coordinate to screen pixels (converted to a float first) */
#define hud_toScreenX(x) hud_scaleX((float)(x))
#define hud_toScreenY(y) hud_scaleY((float)(y))

#endif
