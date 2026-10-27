/* batch 66 (lifted/grp13.c) */
#include "lifted/grp13.c"
/* 0x4728e0 load_4728e0(layer): a terrain layer's whole light map from scratch (light_computeLayerLightBy with
   first = 1 over rows 0..+0x1c, columns 0..+0x20, into its own light map +0x48); ecx passes through (the scene) */
static THISCALL DWORD load_4728e0(char *scene, DWORD layer) { DWORD v[1] = { layer }; return run_lifted(lift_4728e0, (DWORD)scene, 1, v); }
/* 0x481ae0 (thiscall) load_481ae0(block, item, depth): put a collision triangle into the space object's block tree:
   nothing if it misses the block's box (load_47fce0 with the space's margin +0x8c) or is already first in its list;
   a leaf (+0x24 == 0) gets a node (item, block, linked in at +0x18, count +0x1c), and once it holds more than +0x90
   items and depth > 0 it splits into 8 child blocks (+0x28.., octants of the box), re-inserts every item into them
   (depth - 1), frees its nodes and the children left empty; an inner block passes the item to each child (made
   when missing), freeing the children left empty. Returns 1 after a split, else 0 */
static THISCALL DWORD load_481ae0(char *sp, DWORD block, DWORD item, DWORD depth)
{
	DWORD v[3] = { block, item, depth };
	return run_lifted(lift_481ae0, (DWORD)sp, 3, v);
}
/* 0x46ab30 (thiscall) skel_applyPose(out, bone, t): a bone's matrix at time t (0..1 of the skeleton's +0x20 frames)
   through the GL modelview matrix (saved and restored): identity, then the position (bone +0x44, or the key
   interpolated: keys of 8 dwords from +0x64, count +0x60, frame / length / base / delta, binary search), then the
   rotation (angle +0x50 about +0x54 if the axis is not zero, or the key's base and delta rotations: keys of 10
   dwords from +0x6c, count +0x68), read back into out. A bone outside 0..+0x10 gets the identity */
static THISCALL DWORD skel_applyPose(char *sk, DWORD out, DWORD bone, DWORD t)
{
	DWORD v[3] = { out, bone, t };
	return run_lifted(lift_46ab30, (DWORD)sk, 3, v);
}
