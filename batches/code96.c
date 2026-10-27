/* batch 95 (lifted/grp41.c) */
#include "lifted/grp41.c"
/* 0x419000 armc_snapshot(i): the snapshot texture of the arm-customise catalogue's item i (name 0x4dbe50 + i * 0x80;
   shorter than 2 characters: none): "Actor/item/<name>/snapshot" from the global texture set (tex_getIdByName) into
   0x4dcc70 + i * 4; the "loading" flag 0x4dcc64 cleared */
LIFT_PLAIN(armc_snapshot, 419000)
/* 0x40b420 arena_40b420 / 0x43bcb0 room_43bcb0(): the selected map's preview texture: dir (0x680bc4) + map name
   (0x907b30 + index * 0x20; index byte 0x4db548 / 0x4df9e8) + "/" + the name again, into 0x9da324; 0x680cd0 = 0 */
LIFT_PLAIN(arena_40b420, 40b420)
LIFT_PLAIN(room_43bcb0, 43bcb0)
