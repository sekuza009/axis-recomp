/* data.h: a piece of the game's initialised data (the .c files of src/data, tools/mkdatasrc.py): its address and bytes */
#pragma once
typedef struct { u32 address; const void *bytes; u32 size; } DataPiece;
extern const DataPiece g_rdataPieces[], g_dataPieces[], g_text_dataPieces[];
