/* posix_files_test.c: plat/posix/files.c checked on Linux (a static 32- and 64-bit program; run in WSL by
   tools/plat_tests/run_posix.sh). A game-like tree in /tmp with names whose case differs from the game's. */
#define AXIS_PORTABLE 1
#include "../../src/plat/posix/files.c"
#include <stdio.h>

static int fails;
static void check(int ok, const char *what)
{
	printf("%s  %s\n", ok ? "PASS" : "FAIL", what);
	if (!ok)
		fails++;
}
static void put(const char *path, const char *text)
{
	FILE *f = fopen(path, "w");
	fputs(text, f);
	fclose(f);
}

int main(void)
{
	system("rm -rf /tmp/axt && mkdir -p /tmp/axt/Iftex /tmp/axt/Save /tmp/axt/initdata");
	put("/tmp/axt/Iftex/Cylinder.PTX", "cylinder");
	put("/tmp/axt/Save/Alex.axs", "alex");
	put("/tmp/axt/Save/bob.AXS", "bob");
	put("/tmp/axt/Save/notes.txt", "n");
	put("/tmp/axt/initdata/battle.sra", "movie");
	if (chdir("/tmp/axt") != 0)
		return 2;
	char p[1024];
	int f;

	f = plat_path("iftex\\cylinder.ptx", p, sizeof p);
	check(f == 1 && !strcmp(p, "Iftex/Cylinder.PTX"), "iftex\\cylinder.ptx -> Iftex/Cylinder.PTX");
	f = plat_path("SAVE\\newguy.axs", p, sizeof p);
	check(f == 0 && !strcmp(p, "Save/newguy.axs"), "SAVE\\newguy.axs (a new file) -> Save/newguy.axs, not found");
	f = plat_path(".\\initdata\\\\BATTLE.SRA", p, sizeof p);
	check(f == 1 && !strcmp(p, "./initdata/battle.sra"), ".\\initdata\\\\BATTLE.SRA -> ./initdata/battle.sra");
	f = plat_path("/tmp/AXT/save/ALEX.axs", p, sizeof p);
	check(f == 1 && !strcmp(p, "/tmp/axt/Save/Alex.axs"), "/tmp/AXT/save/ALEX.axs -> /tmp/axt/Save/Alex.axs");

	char buf[64] = { 0 };
	FILE *fp = plat_fopen("save\\ALEX.AXS", "rb");
	check(fp && fread(buf, 1, sizeof buf, fp) == 4 && !strcmp(buf, "alex"), "fopen(save\\ALEX.AXS, rb) reads alex");
	if (fp) fclose(fp);
	fp = plat_fopen("Save\\newguy.axs", "wt");
	check(fp != NULL, "fopen(Save\\newguy.axs, wt) makes a new file");
	if (fp) { fputs("new", fp); fclose(fp); }
	check(access("/tmp/axt/Save/newguy.axs", F_OK) == 0, "  ... at Save/newguy.axs");

	void *h = plat_fileOpenRead("IFTEX\\cylinder.ptx");
	uint32_t done = 0;
	memset(buf, 0, sizeof buf);
	check(h != (void *)(intptr_t)-1 && plat_fileRead(h, buf, 100, &done) && done == 8 && !strcmp(buf, "cylinder"),
	      "fileOpenRead + fileRead(100) on IFTEX\\cylinder.ptx: 8 bytes");
	if (h != (void *)(intptr_t)-1) plat_fileClose(h);
	check(plat_fileOpenRead("iftex\\missing.ptx") == (void *)(intptr_t)-1, "fileOpenRead of a missing file: -1");

	FindData d;
	char got[512] = "";
	intptr_t fh = plat_findfirst("save\\*.axs", &d);
	for (int r = fh == -1 ? -1 : 0; r == 0; r = plat_findnext(fh, &d)) { strcat(got, d.name); strcat(got, " "); }
	plat_findclose(fh);
	check(!strcmp(got, "Alex.axs bob.AXS newguy.axs "), "findfirst(save\\*.axs): Alex.axs bob.AXS newguy.axs");
	printf("      got: %s\n", got);
	got[0] = 0;
	fh = plat_findfirst("SAVE\\*.*", &d);
	int dirs = 0;
	for (int r = fh == -1 ? -1 : 0; r == 0; r = plat_findnext(fh, &d)) { strcat(got, d.name); strcat(got, " "); dirs += (d.attrib & 0x10) != 0; }
	plat_findclose(fh);
	check(!strcmp(got, ". .. Alex.axs bob.AXS newguy.axs notes.txt ") && dirs == 2, "findfirst(SAVE\\*.*): . .. and every file");
	printf("      got: %s\n", got);
	check(plat_findfirst("nosuch\\*.axs", &d) == -1, "findfirst in a missing folder: -1");
	fh = plat_findfirst("save\\b?b.axs", &d);
	check(fh != -1 && !strcmp(d.name, "bob.AXS") && d.size == 3, "findfirst(save\\b?b.axs): bob.AXS, 3 bytes");
	plat_findclose(fh);

	check(plat_fileDelete("save\\BOB.axs") == 1 && access("/tmp/axt/Save/bob.AXS", F_OK) != 0, "fileDelete(save\\BOB.axs) removes Save/bob.AXS");
	check(plat_fileDelete("save\\BOB.axs") == 0, "fileDelete again: 0");
	check(plat_mkdir("SAVE\\Replays") == 0 && access("/tmp/axt/Save/Replays", F_OK) == 0, "mkdir(SAVE\\Replays) -> Save/Replays");
	check(plat_chdir("save") == 0 && plat_currentDirectory(sizeof p, p) && !strcmp(p, "/tmp/axt/Save"), "chdir(save) -> /tmp/axt/Save");
	fp = plat_fopen("ALEX.axs", "r");
	check(fp != NULL, "fopen(ALEX.axs) from there");
	if (fp) fclose(fp);

	printf("%s: %d failed\n", fails ? "FAILED" : "ALL PASSED", fails);
	return fails != 0;
}
