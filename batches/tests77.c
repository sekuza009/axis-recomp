/* batch 76 */
/* a binary shape (shape_read's test file) or an OBJ file (model_loadObjFormatFrom's), named .shp / .obj in any case,
   or with another, no or a misleading extension; the open sometimes fails */
static void modelfile_setup(void)
{
	static const char *names[] = { "Data\\Shape\\mech.shp", "Data\\Shape\\MECH.SHP", "x.ShP", "Data/arena.obj", "ARENA.OBJ", "y.oBj",
	                               "Data\\Shape\\mech.sh", "Data\\noext", "a.shp\\b", "a.obj/b", "Data\\x.shpx", ".obj", "z.txt", "" };
	int k = irnd(0, 13), obj = strstr(names[k], "ob") || strstr(names[k], "OB") || strstr(names[k], "oB");
	if (obj) obj_setup(); else shaperead_setup();
	strcpy(BUF + 0x300, names[k]);
	g_vfsOpenFail = !irnd(0, 9);
}
ST(model_loadFrom, modelfile_setup();, (TC(void, 0x464bf0, char *, char *, int, int)(BUF + 0x100, BUF + 0x300, g_a[0], g_a[1]), 0),
   (model_loadFrom(BUF + 0x100, (DWORD)(BUF + 0x300), (DWORD)g_a[0], (DWORD)g_a[1]), 0))
