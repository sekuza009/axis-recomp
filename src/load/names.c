/* names.c: looking resources up by name in the managers' sorted name tables (0x44-byte entries), and file names. */
#include "../game.h"

#define TM ((TextureBank *)tm)   /* the texture bank (tm in each function) by its fields (src/scene.fields) */
#include <string.h>

/* binary search of name in the table at *table (count at *count; the search starts with hi = count); -1 when not
   found */
static int name_search(u32 count, u32 table, const char *name)
{
	int lo = 0, hi = GAME_VAR(int, count);
	if (hi <= 0)
		return -1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		int r = str_order(name, (const char *)(GAME_VAR(u32, table) + mid * 0x44));
		if (r == 0)
			return mid;
		if (r < 0)
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	return -1;
}

/* 0x466ce0: an entry's index in Shape.dat's table by name (binary search, -1 none); skelDat_findByName
   (0x46b0c0): the same in the skeleton archive */
int (shapeDat_findByName)(const char *name) { return name_search(OBJ(g_shapeDat), (OBJ(g_shapeDat) + 0x4), name); }
int (skelDat_findByName)(const char *name) { return name_search(OBJ(g_skelDat), (OBJ(g_skelDat) + 0x4), name); }

/* 0x46cad0: src without its extension (from the last '.') copied to dst */
void (path_stripExtension)(const char *src, char *dst)
{
	char buf[256];
	strcpy(buf, src);
	for (int i = (int)strlen(buf) - 1; i >= 0; i--)
		if (buf[i] == '.') {
			buf[i] = '\0';
			break;
		}
	strcpy(dst, buf);
}

/* 0x4554c0: a texture bank's name, by binary search of its sorted 0x44-byte records (index, count indexCount): the
   index or -1. The upper bound starts at the count, not count - 1, as in the original */
int THISCALL (tex_findByName)(TextureBank *self, const u8 *name)
{
	int hi = self->indexCount, lo = 0;
	if (hi <= 0)
		return -1;
	const u8 *records = self->index;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		const u8 *a = name, *b = records + mid * 0x44;
		while (*a == *b && *a)
			a++, b++;
		int c = *a == *b ? 0 : *a < *b ? -1 : 1;
		if (c == 0)
			return mid;
		if (c < 0)
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	return -1;
}

/* 0x455550 (thiscall on a texture bank): the item named, its file (file) moved to where the item starts (its
   0x44-byte record at index, +0x40); returns the file, or 0 after a fatal message when there is no such item */
void *THISCALL (tex_getItemFileBy)(TextureBank *manager, const char *name)
{
	int i = tex_findByName((u8 *)manager, name);
	if (i < 0) {
		sys_fatalError((char *)OBJ(g_logTexture), (const char *)STR(0x4b3f80, "can't find item(%s) - getItemFileBy()"), (int)name);
		return 0;
	}
	crt_fseek(manager->file, GAME_VAR(long, manager->index + i * 0x44 + 0x40), 0);   /* (the index entry's offset, after its 0x40-byte name) */
	return manager->file;
}

/* 0x456be0 (thiscall on the texture manager): a texture's id by name: each of the six banks (+4 ..) asked in turn
   (tex_allocIdBy, with the flags and the two colours' hue, saturation, value); the first answer k x 512 + its index. None: a fatal message, -1 */
int THISCALL (tex_getIdByName)(TextureManager *manager, const char *name, u32 flags, u32 h1, u32 s1, u32 v1, u32 h2, u32 s2, u32 v2)
{
	for (int k = 0; k < 6; k++) {
		void *bank = manager->banks[k];
		if (!bank)
			continue;
		int i = tex_allocIdBy(bank, (u32)name, flags, h1, s1, v1, h2, s2, v2);
		if (i >= 0)
			return k * 512 + i;
	}
	sys_fatalError((char *)OBJ(g_logTextureManager), (const char *)STR(0x4b42b0, "can't find texture object (%s) - getI..."), (int)name);
	return -1;
}

/* 0x466430 (thiscall on a shape): each of its parts (0x80 bytes from parts, partCount of them) given its texture (texture:
   tex_getIdByName on the game's texture manager, g_textures, by the part's name at +4, with the flags and two colours given);
   with a suffix the name gets 0x4b12f4 and the suffix appended first (too long for the 0x40 bytes: a fatal message
   first). Its callers ignore the eax it leaves */
void THISCALL (shape_bindTextureBy)(u8 *shape, const char *suffix, int flags, int h1, int s1, int v1, int h2, int s2, int v2)
{
	Model *md = (Model *)shape;
	for (int i = 0; i < md->partCount; i++) {
		u8 *part = md->parts + i * 0x80;
		ShapePart *sp = (ShapePart *)part;
		char *name = (char *)part + 4;
		if (*suffix) {
			if (strlen(name) + strlen(suffix) > 0x3f)
				sys_fatalErrorN((char *)OBJ(g_logShape), (const char *)STR(0x4c4c6c, "texture object name is too long (%s+%..."), name, suffix);
			strcat(name, (const char *)STR(0x4b12f4, "*"));
			strcat(name, suffix);
		}
		sp->texture = tex_getIdByName((*(void **)&g_textures), name, flags, h1, s1, v1, h2, s2, v2);
	}
}

/* 0x4566c0 (thiscall on a texture bank): texture i bound, through the cache of GL textures (0x14-byte slots from
   slots: their index, the texture in them, the GL id, next and previous in a ring, oldest the oldest). Not in the
   cache (its slot, records[].slot in its 0x68-byte record, negative): the oldest slot taken and the texture loaded into it
   (tinted when its flags, records[].flags, have 2; clamped at the edges when they have 1, else repeated: tex_upload's mode; mipmaps by the bank's mipmaps; loadCount counts the loads); in it but changed
   (records[].changed 1): loaded again; else just bound. The slot then becomes the newest: when it was the oldest the next one is
   (and that one's texture loses its slot), else it moves to just before the oldest. Its callers ignore the eax it leaves */
void THISCALL (tex_bind)(u8 *tm, int i)
{
	TextureBank *mg = (TextureBank *)tm;
	TexRecord *texture = &mg->records[i];
	TexSlot *slot;
#define OLDEST ((TexSlot *)mg->oldest)
#define SLOT(p) ((TexSlot *)(p))
	if (texture->slot < 0) {
		slot = OLDEST;
		slot->record = i;
		tex_loadImage(tm, i);
		if (*(u8 *)&texture->flags & 2)
			tex_applyTintMask(tm, i);
		tex_upload(tm, slot->glTexture, *(u8 *)&texture->flags & 1 ? 0 : 1);
		mg->loadCount++;
	} else {
		slot = (TexSlot *)mg->slots + texture->slot;
		if (texture->changed == 1) {
			tex_loadImage(tm, i);
			if (*(u8 *)&texture->flags & 2)
				tex_applyTintMask(tm, i);
			tex_upload(tm, slot->glTexture, *(u8 *)&texture->flags & 1 ? 0 : 1);
			mg->loadCount++;
			texture->changed = 0;
		} else
			glBindTexture(0xde1, slot->glTexture);   /* GL_TEXTURE_2D */
	}
	if (slot == OLDEST) {
		mg->oldest = slot->next;
		mg->records[OLDEST->record].slot = -1;
	} else {
		SLOT(slot->next)->prev = slot->prev;
		SLOT(slot->prev)->next = slot->next;
		u8 *oldest = mg->oldest;
		slot->next = oldest;
		slot->prev = OLDEST->prev;
		SLOT(oldest)->prev = (u8 *)slot;
		SLOT(slot->prev)->next = (u8 *)slot;
	}
	slot->record = i;
	texture->slot = slot->index;
#undef OLDEST
#undef SLOT
}

/* 0x4569d0 (thiscall on the texture manager): the six banks kept (+4 .. banks[5]), each (when given) checked for its
   size: 64 x 64, 128 x 64, 256 x 64, 128 x 128, 256 x 128, 256 x 256 (its width / height), a fatal message
   with the size found otherwise. Its caller ignores the eax it leaves */
void THISCALL (TextureManager_setBanks)(TextureManager *manager, u8 *bank64x64, u8 *bank128x64, u8 *bank256x64, u8 *bank128x128, u8 *bank256x128, u8 *bank256x256)
{
	static const u32 sizes[6][3] = { { 64, 64, STR(0x4b4278, "texture image size mismatch (64x64 !=...") }, { 128, 64, STR(0x4b423c, "texture image size mismatch (128x64 !...") }, { 256, 64, STR(0x4b4200, "texture image size mismatch (256x64 !...") },
	                                 { 128, 128, STR(0x4b41c4, "texture image size mismatch (128x128 ...") }, { 256, 128, STR(0x4b4188, "texture image size mismatch (256x128 ...") }, { 256, 256, STR(0x4b414c, "texture image size mismatch (256x256 ...") } };
	u8 *banks[6] = { bank64x64, bank128x64, bank256x64, bank128x128, bank256x128, bank256x256 };
	TextureManager_reset((u8 *)manager);
	for (int k = 0; k < 6; k++) {
		u8 *m = banks[k];
		TextureBank *mg = (TextureBank *)m;
		if (m && (mg->width != sizes[k][0] || mg->height != sizes[k][1]))
			sys_fatalErrorN((char *)OBJ(g_logTextureManager), (const char *)RELOC(sizes[k][2]), mg->width, mg->height);
	}
	for (int k = 0; k < 6; k++)
		manager->banks[k] = banks[k];
}

/* 0x456520 (thiscall on a texture bank): its pixels (image, width x height) uploaded to GL texture id: wrapped
   (mode 1: repeat, else clamp), filtered linearly or not (linear 1), with mipmaps (mipmaps 1: built by
   gluBuild2DMipmaps after the first level) or without. Its callers ignore the eax it leaves */
void THISCALL (tex_upload)(u8 *tm, u32 id, int mode)
{
	glPixelStorei(0xcf5, 1);   /* GL_UNPACK_ALIGNMENT */
	glBindTexture(0xde1, id);
	u32 wrap = mode == 1 ? 0x46240400 : 0x46240000;   /* GL_REPEAT : GL_CLAMP */
	glTexParameterf_bits(0xde1, 0x2802, wrap);
	glTexParameterf_bits(0xde1, 0x2803, wrap);
	int linear = TM->linear == 1;
	int mipmaps = TM->mipmaps == 1;
	glTexParameterf_bits(0xde1, 0x2800, linear ? 0x46180400 : 0x46180000);   /* mag: GL_LINEAR : GL_NEAREST */
	glTexParameterf_bits(0xde1, 0x2801, mipmaps ? (linear ? 0x461c0c00 : 0x461c0000) : (linear ? 0x46180400 : 0x46180000));
	glTexImage2D(0xde1, 0, 4, TM->width, TM->height, 0, 0x1908, 0x1401, TM->image);
	if (mipmaps)
		gluBuild2DMipmaps(0xde1, 4, TM->width, TM->height, 0x1908, 0x1401, TM->image);
}

/* 0x4557e0 (thiscall on a texture bank): is the texture name (up to a '*') there in the manager's format (format,
   under its directory +8 when it has one) at its size (width x height)? 0: in the dat index (tex_findByName); 1: a
   BMP of that size; 2: a RAW whose header (at 6, two shorts in 8-pixel units) gives it; else a fatal message. 1 or
   0, the local image (a BMPRGBFile) closed either way */
int THISCALL (tex_textureFileExist)(u8 *tm, const char *name)
{
	static const u32 formats[3][2] = { { STR(0x4b3fdc, "%s\\%s"), STR(0x4b3fd8, "%s") }, { STR(0x4b3fec, "%s\\%s.BMP"), STR(0x4b3fe4, "%s.BMP") }, { STR(0x4b4000, "%s\\%s.RAW"), STR(0x4b3ff8, "%s.RAW") } };   /* "%s\%s" "%s", .BMP, .RAW */
	BmpFile image;
	image.vtable = VT(BMPRGBFile, 0x4a96f8);   /* (its vtable) */
	BITS(image.file) = 0;          /* (no file yet) */
	char base[0x100], path[0x100];
	strcpy(base, name);
	crt_strtok(base, (const char *)STR(0x4b12f4, "*"));   /* "*" */
	const char *dir = (const char *)tm + 8;
	int format = TM->format, ok = 0;
	if ((unsigned)format > 2)
		sys_fatalError((char *)OBJ(g_logTexture), (const char *)STR(0x4b400c, "invalid file format(%s)-textureFileEx..."), format);
	else {
		if (*dir)
			sprintf(path, (const char *)RELOC(formats[format][0]), dir, base);
		else
			sprintf(path, (const char *)RELOC(formats[format][1]), base);
		if (format == 0)
			ok = tex_findByName(tm, path) >= 0;
		else if (format == 1) {
			if (file_existsf(path)) {
				image_initBy((u8 *)&image, path);
				int w = image.width, h = image.height;
				BMPRGBFile_close((u8 *)&image);
				ok = w == TM->width && h == TM->height;
			}
		} else {
			void *f = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
			if (f) {
				short size[2];
				crt_fseek(f, 6, 0);
				crt_fread(&size[0], 2, 1, f);
				crt_fread(&size[1], 2, 1, f);
				fclose(f);
				ok = size[0] * 8 == TM->width && size[1] * 8 == TM->height;
			}
		}
	}
	BMPRGBFile_dtor((u8 *)&image);   /* (its destructor: vtable 0x4a96f8's deleting destructor calls it) */
	return ok;
}

/* 0x455080 (thiscall on a texture bank): set up (twice is a fatal message): its directory (+8, upper-cased; none or
   0x4b1304 empty), format, size and filtering (format .. linear). The dat format (0) opens its image file for
   the size (Data\Image64.dat ..., by 0x4b3f20 for another size; none a fatal message: kept open at file) and reads
   its index (a count indexCount, then that many 0x44-byte entries at index; no memory a fatal message). Then up to 0x200
   texture slots (slotCount of them, 0x14 bytes at slots: its index, id -1, a GL texture name, previous and next in a
   ring), the oldest oldest, the counts recordCount / loadCount .. cleared; set up (+4 1). Its callers ignore the eax
   it leaves */
void THISCALL (tex_initBy)(u8 *tm, const char *dir, int slots, int format, int w, int h, int linear, int mipmaps)
{
#define fatal(text, ...) sys_fatalErrorN((char *)OBJ(g_logTexture), (const char *)RELOC(text), ##__VA_ARGS__)
	static const u32 names[6][3] = { { 64, 64, STR(0x4b3f54, "Image0") }, { 128, 64, STR(0x4b3f4c, "Image1") }, { 128, 128, STR(0x4b3f3c, "Image3") },
	                                 { 256, 64, STR(0x4b3f44, "Image2") }, { 256, 128, STR(0x4b3f34, "Image4") }, { 256, 256, STR(0x4b3f2c, "Image5") } };
	if (TM->ready == 1)
		fatal(STR(0x4b3f5c, "duplicate initialization - init()"));
	char *own = (char *)tm + 8;
	if (dir && strcmp(dir, (const char *)STR(0x4b1304, ".")) != 0)
		strcpy(own, dir);
	else
		own[0] = 0;
	path_normalize(own);
	TM->linear = linear;
	TM->format = format;
	TM->width = w;
	TM->height = h;
	TM->mipmaps = mipmaps;
	if (format == 0) {
		char name[0x100], path[0x100];
		int k = 0;
		while (k < 6 && !(names[k][0] == (u32)w && names[k][1] == (u32)h))
			k++;
		if (k < 6)
			strcpy(name, (const char *)RELOC(names[k][2]));
		else
			sprintf(name, (const char *)STR(0x4b3f20, "Image%dx%d"), w, h);
		if (*own)
			sprintf(path, (const char *)STR(0x4b3f10, "%s\\Data\\%s.dat"), own, name);
		else
			sprintf(path, (const char *)STR(0x4b3f04, "Data\\%s.dat"), name);
		TM->file = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
		if (!TM->file)
			fatal(STR(0x4b3ee4, "can't open file(%s) - initBy()"), path);
		crt_fread(&TM->indexCount, 4, 1, TM->file);
		(*(void **)&TM->index) = operator_new(((u32)TM->indexCount) * 0x44);
		if (!(*(void **)&TM->index))
			fatal(STR(0x4b3eb4, "insufficient memory for itemBuffer(%d..."), TM->indexCount);
		crt_fread((*(void **)&TM->index), 0x44, ((u32)TM->indexCount), TM->file);
	} else {
		TM->indexCount = 0;
		(*(void **)&TM->index) = NULL;
		TM->file = NULL;
	}
	TM->recordCount = 0;
	TM->slotCount = slots > 0x200 ? 0x200 : slots;
	TM->slots = operator_new(TM->slotCount * 0x14);
	if (!TM->slots)
		fatal(STR(0x4b3e84, "insufficient memory for slotArray(%d)..."), TM->slotCount);
	for (int i = 0; i < TM->slotCount; i++) {
		u32 *slot = (u32 *)(TM->slots + i * 0x14);
		slot[0] = i;
		slot[1] = 0xffffffff;
		glGenTextures(1, &slot[2]);   /* glGenTextures */
		int n = TM->slotCount;
		slot[3] = (u32)(TM->slots + (n + i - 1) % n * 0x14);
		slot[4] = (u32)(TM->slots + (i + 1) % TM->slotCount * 0x14);
	}
	TM->loadCount = 0;
	TM->counterB = 0;
	TM->counterC = 0;
	TM->oldest = TM->slots;
	TM->ready = 1;
#undef fatal
}

/* 0x4555b0 (thiscall on a texture bank): the record for texture name (upper-cased; empty: -1) with flags and two
   colours (h1 s1 v1, h2 s2 v2): among the recordCount records (0x68 bytes from records: the name, flags flags, the
   colours colours ..) a hit keeps it as it is when flags and colours match (a NaN matches anything, as fcom has it),
   else takes them and is recoloured (tex_setMaterialTint). A miss whose file is there (tex_textureFileExist; else
   -1) gets a new record (at most 512: a fatal message), bound at once (tex_bind) while the count is below slotCount.
   Returns the record's index */
int THISCALL (tex_allocIdBy)(u8 *tm, const char *name, u32 flags, u32 h1, u32 s1, u32 v1, u32 h2, u32 s2, u32 v2)
{
	/* the two colours (h1 s1 v1, h2 s2 v2) read where the caller put them, through a volatile pointer: clang would
	   otherwise copy them into the frame. The frame then holds only the name and is as deep as the original's (0x50
	   with the saved registers): tex_textureFileExist reads a short file's size words from stack it never wrote,
	   and a deeper frame gave those reads other values now and then */
	const volatile u32 *colour = &h1;
	(void)s1, (void)v1, (void)h2, (void)s2, (void)v2;
	char key[0x40];
	strcpy(key, name);
	path_normalize(key);
	if (!key[0])
		return -1;
	int i = 0;
	for (; i < TM->recordCount; i++) {
		TexRecord *rec = &TM->records[i];
		if (strcmp((const char *)((u8 *)rec), key))
			continue;
		const float *c = rec->colours;
#define SAME(a, k) (!((a) < fld_m((const float *)&colour[k])) && !((a) > fld_m((const float *)&colour[k])))
		if (rec->flags == flags && SAME(c[0], 0) && SAME(c[2], 2) && SAME(c[1], 1) && SAME(c[3], 3) &&
		    SAME(c[5], 5) && SAME(c[4], 4))
			return i;
#undef SAME
		rec->flags = flags;
		tex_setMaterialTint(tm, i, colour[0], colour[1], colour[2], colour[3], colour[4], colour[5]);
		return i;
	}
	if (!tex_textureFileExist(tm, key))
		return -1;
	if (TM->recordCount < 0x200) {
		i = TM->recordCount;
		texRecord_init((u8 *)&TM->records[i], key, -1, flags, colour[0], colour[1], colour[2], colour[3], colour[4], colour[5]);
		TM->recordCount++;
	} else
		sys_fatalErrorN((char *)OBJ(g_logTexture), (const char *)STR(0x4b3fa8, "[%dx%d] object buffer overflow(%d) - ..."), TM->width, TM->height, 0x200);
	if (TM->recordCount < TM->slotCount)
		tex_bind(tm, i);
	return i;
}

#define W(m) (((TextureBank *)RELOC(m))->width)
#define H(m) (((TextureBank *)RELOC(m))->height)

/* path: the texture name in the given format, under the manager's directory when it has one */
static void tex_path(u8 *m, char *path, u32 with_dir, u32 plain, const char *name)
{
	const TextureBank *tm = (const TextureBank *)m;
	if (tm->dir[0])
		sprintf(path, (const char *)RELOC(with_dir), tm->dir, name);
	else
		sprintf(path, (const char *)RELOC(plain), name);
}

/* a decoded image of another size than the manager's is fatal */
static void size_check(u8 *m, int w, int h)
{
	if (W(m) != w || H(m) != h)
		sys_fatalErrorN((char *)OBJ(g_logTexture), (const char *)STR(0x4b4104, "mismatching image size(%dx%d/%dx%d)-b..."), W(m), H(m), w, h);
}

/* the image's alpha (each pixel's 4th byte): the grey of the ALPHA image, or opaque */
static void alpha_from(u8 *m, int have)
{
	TextureBank *tm = (TextureBank *)m;
	for (int y = 0; y < H(m); y++)
		for (int x = 0; x < W(m); x++) {
			int i = (y * W(m) + x) * 4;
			tm->image[i + 3] = have ? (u8)((tm->alphaImage[i + 2] + tm->alphaImage[i + 1] + tm->alphaImage[i]) / 3) : 0xff;
		}
}

/* no colour mask: every pixel of the mask the colour at g_packedRed */
static void colour_fill(u8 *m)
{
	TextureBank *tm = (TextureBank *)m;
	for (int y = 0; y < H(m); y++)
		for (int x = 0; x < W(m); x++)
			((u32 *)tm->colourMask)[y * W(m) + x] = g_packedRed;
}

/* 0x455aa0 (thiscall on the texture bank): texture i's image (its name records + i * 0x68 cut at '*') loaded at
   image, its alpha (alpha_from) and its colour mask at colourMask (or colour_fill), by the manager's format format:
   0 items of the texture dat (name, name_ALPHA, name_COLOR: tex_findByName / tex_getItemFileBy, the decoder's tables set
   up on first use, g_ptxTablesReady), 1 BMP files (name.BMP must open), 2 PTX files (name.RAW, name_ALPHA.RAW,
   name_COLOR.RAW); a PTX of another size than width x height is fatal. (The original's SEH frame, for its BMP
   objects, is not reproduced.) Its callers ignore the eax it leaves */
void THISCALL (tex_loadImage)(u8 *m, int i)
{
	TextureBank *mg = (TextureBank *)m;
	u32 bmp[3][0x12];   /* BMP reader objects (vtable 0x4a96f8) for the image, the alpha, the mask */
	for (int k = 0; k < 3; k++) {
		bmp[k][0] = VT(BMPRGBFile, 0x4a96f8);
		bmp[k][1] = 0;
	}
	char name[0x100], path[0x190];
	int bpp, w, h;
	strcpy(name, mg->records[i].name);
	crt_strtok(name, (const char *)STR(0x4b12f4, "*"));
	switch (mg->format) {
	case 0:
		if (!g_ptxTablesReady) {
			ptx_initTables();
			g_ptxTablesReady = 1;
		}
		tex_path(m, path, STR(0x4b3fdc, "%s\\%s"), STR(0x4b3fd8, "%s"), name);
		ptx_decode(tex_getItemFileBy(m, path), mg->image, &bpp, &w, &h);
		size_check(m, w, h);
		tex_path(m, path, STR(0x4b405c, "%s\\%s_ALPHA"), STR(0x4b4050, "%s_ALPHA"), name);
		if (tex_findByName(m, path) >= 0) {
			ptx_decode(tex_getItemFileBy(m, path), mg->alphaImage, &bpp, &w, &h);
			size_check(m, w, h);
			alpha_from(m, 1);
		} else
			alpha_from(m, 0);
		tex_path(m, path, STR(0x4b4044, "%s\\%s_COLOR"), STR(0x4b4038, "%s_COLOR"), name);
		if (SITE_THISCALL(0x45636e, tex_findByName, int, void *, const u8 *)(m, (const u8 *)path) >= 0) {   /* tex_findByName (the patch DLL: the KYRIE masks) */
			ptx_decode(tex_getItemFileBy(m, path), mg->colourMask, &bpp, &w, &h);
			size_check(m, w, h);
		} else
			colour_fill(m);
		break;
	case 1:
		tex_path(m, path, STR(0x4b3fec, "%s\\%s.BMP"), STR(0x4b3fe4, "%s.BMP"), name);
		if (!image_initBy(bmp[0], path))
			sys_fatalError((char *)OBJ(g_logTexture), (const char *)STR(0x4b40a8, "can't open file %s-bindBy()"), (int)path);
		image_copyTo(bmp[0], mg->image, W(m), H(m), 4, 0, 0, 0, 0, W(m), H(m), 0);
		tex_path(m, path, STR(0x4b4098, "%s\\%s_ALPHA.BMP"), STR(0x4b4088, "%s_ALPHA.BMP"), name);
		if (image_initBy(bmp[1], path)) {
			image_copyTo(bmp[1], mg->alphaImage, W(m), H(m), 4, 0, 0, 0, 0, W(m), H(m), 0);
			alpha_from(m, 1);
			BMPRGBFile_close(bmp[1]);
		} else
			alpha_from(m, 0);
		tex_path(m, path, STR(0x4b4078, "%s\\%s_COLOR.BMP"), STR(0x4b4068, "%s_COLOR.BMP"), name);
		if (image_initBy(bmp[2], path)) {
			image_copyTo(bmp[2], mg->colourMask, W(m), H(m), 4, 0, 0, 0, 0, W(m), H(m), 0);
			BMPRGBFile_close(bmp[2]);
		} else
			colour_fill(m);
		break;
	case 2: {
		if (!g_ptxTablesReady) {
			ptx_initTables();
			g_ptxTablesReady = 1;
		}
		tex_path(m, path, STR(0x4b4000, "%s\\%s.RAW"), STR(0x4b3ff8, "%s.RAW"), name);
		ptx_open(path, mg->image, &bpp, &w, &h);
		size_check(m, w, h);
		tex_path(m, path, STR(0x4b40f4, "%s\\%s_ALPHA.RAW"), STR(0x4b40e4, "%s_ALPHA.RAW"), name);
		void *f = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
		if (f) {
			ptx_decode(f, mg->alphaImage, &bpp, &w, &h);
			size_check(m, w, h);
			alpha_from(m, 1);
		} else
			alpha_from(m, 0);
		tex_path(m, path, STR(0x4b40d4, "%s\\%s_COLOR.RAW"), STR(0x4b40c4, "%s_COLOR.RAW"), name);
		f = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
		if (f) {
			ptx_decode(f, mg->colourMask, &bpp, &w, &h);
			size_check(m, w, h);
		} else
			colour_fill(m);
		break;
	}
	}
	for (int k = 2; k >= 0; k--)
		BMPRGBFile_dtor(bmp[k]);   /* (the reader's destructor) */
}
#undef W
#undef H
