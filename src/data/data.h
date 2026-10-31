/* data.h: a piece of the game's initialised data (src/data/*.c, tools/mkdatasrc.py): its address and bytes */
#pragma once
typedef struct { u32 address; const void *bytes; u32 size; } DataPiece;
extern const DataPiece g_rdataPieces[], g_dataPieces[], g_text_dataPieces[];
