/* batch 138 (lifted/grp84.c): the armour screen's colour editor */
#include "lifted/grp84.c"
/* 0x41a280 armc_41a280(): the colour editor (panels at 0x4dcc98 - 200, 0x4dcc94): two translucent boxes headed
   0x75d3a4 / 0x75d424, each with three lines "<0x75d4a4 label> [<value>]" for the current slot's colours
   (0x4dc4b8, six floats a slot: hue * k, then saturation and value scaled and capped at 99; the second colour's
   offset by one first); the slot list (texture 0x9db0a4, five slots and a sixth box 0x756d24, labels 0x756aa4, the
   current slot 0x4dc4b0 bright) with the parts' names when 0x4dbc68 is set; the hue / saturation / value sliders
   for both colours (hue wrapped by 180 into 0..1) and their knobs; the hovered control (armc_40e4d0) */
LIFT_PLAIN(armc_41a280, 41a280)
