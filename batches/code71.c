/* batch 70 (lifted/grp17.c) */
#include "lifted/grp17.c"
/* 0x463b80 shape_getShadingColorBufferBy(out, first, part, factors, matrix): a shape part's vertex colours (RGBA
   bytes, count +0x4c) lit by the factor pool (count +0xb004, 0x2c-byte records from +4; colour +0xc): type 0 an
   ambient colour, 1 a directional light (normals +0x54 . direction, times the base colours +0x58), 2 / 3 point lights
   (position +0x10, through the matrix if one is given; radius +0x28; vertices +0x50) skipped when the part's box
   (+0x68..+0x7c) is out of reach. first = 1 writes the first factor, the rest are added and clamped to 255; parts
   flagged 2 and empty pools take the base colours; an unknown type is fatal (sys_errorTerminate) */
LIFT_PLAIN8(shape_getShadingColorBufferBy, 463b80)
/* 0x466910 FUN_00466910(out, first, shape, factors, matrix): shape_getShadingColorBufferBy for every part (0x80 apart,
   count +0x10), each into out + its colour offset (+0x48) * 4 */
LIFT_PLAIN8(FUN_00466910, 466910)
