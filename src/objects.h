/* objects.h: the game's arrays, buffers and records by name (tools/name_objects.py): each the original address in
   the harness, its place in AxisRC.exe (IMG; in AxisRC.exe a member of g_rdata / g_data, src/data/layout.h).
   OBJ(name) is its address as a number (src/axis.h). Element type, count: the extent known (see the note) */
#pragma once
#define g_chatLine ((char *)IMG(0x9dc92c))   /* char[1024]; the chat line being typed (memset 0x400) */
#define g_joinedTitleName ((char *)IMG(0x9dd570))   /* char[30]; the joined game's title record: the name (laid out as 0x4de700) */
#define g_titleName ((char *)IMG(0x4de700))   /* char[30]; the title record's name (+0x1e the level: g_titleLevel) */
#define g_accountName ((char *)IMG(0x9dd1d8))   /* char[30]; the login form's name (30 bytes) */
#define g_accountPassword ((char *)IMG(0x9dd1f6))   /* char[12]; (12 bytes) */
#define g_accountPasswordRepeat ((char *)IMG(0x9dd202))   /* char[12]; (12 bytes) */
#define g_accountEmail ((char *)IMG(0x9dd20e))   /* char[40]; (40 bytes) */
#define g_playerName ((char *)IMG(0x4ded20))   /* char[32]; the arena player's record: the name (32 bytes) */
#define g_cfgPlayerName ((char *)IMG(0x4dedb0))   /* char[32]; axis.cfg's player name (default "PLAYER") */
#define g_roomRecName ((char *)IMG(0x5b1b30))   /* char[32]; the room record's name (fields from +0x20: g_roomRec*) */
#define g_roomSettingsName ((char *)IMG(0x4df9c8))   /* char[32]; the room's settings record (GameSettings): its name */
#define g_newArenaName ((char *)IMG(0x4db528))   /* char[32]; the new arena's settings record: its name */
#define g_mapTitle ((char *)IMG(0x67fb44))   /* char[32]; the map's title (TITLE: %s) */
#define g_profileName ((char *)IMG(0x9f8fe8))   /* char[32]; the profile's name (written 0x20 bytes) */
#define g_arenaName ((char *)IMG(0x4db560))   /* char[32]; (0x20 bytes) */
#define g_localAddress ((char *)IMG(0xa0b43c))   /* char[16]; the local IP address text (memset 16) */
#define g_dataDir ((char *)IMG(0x9dae7c))   /* char[1]; the data folder's path (extent unknown) */
#define g_savedColourChoices ((u8 *)IMG(0x4dcfe0))   /* u8[144]; the ARM CENTER's colour choices kept (memcpy 0x90) */
#define g_textColour ((Colour *)IMG(0x76d438))   /* Colour[1]; the menus' text colour */
#define g_rectColour ((Colour *)IMG(0x9da480))   /* Colour[1]; the rectangles' colour */
#define g_roomBright ((u32 *)IMG(0x9dcec0))   /* u32[4]; the room's bright colour (r g b a) */
#define g_roomDim ((u32 *)IMG(0x9dd338))   /* u32[4]; the room's dim colour */
#define g_profileColour ((u32 *)IMG(0x9f8eb0))   /* u32[4] */
#define g_vecZero2 ((float *)IMG(0xa0e7b8))   /* float[3]; a zero vector (vec_initZero) */
#define g_vecUnitY ((float *)IMG(0xa0e7d8))   /* float[3]; (0 1 0: vec_initUp) */
#define g_vecUnitX ((float *)IMG(0xa0e7f8))   /* float[3]; (1 0 0: vec_initAxisX) */
