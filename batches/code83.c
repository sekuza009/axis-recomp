/* batch 82 (lifted/grp28.c) */
#include "lifted/grp28.c"
/* 0x4555b0 (thiscall) tex_allocIdBy(name, flags, 6 floats): the texture's index in this manager. The name is
   upper-cased ('/' -> '\'; empty gives -1) and looked up among the count +0xcd128 records: a hit with other flags or
   colours takes them and is recoloured (tex_recolourMaterial); a miss whose file exists adds a record (512 at most,
   else fatal), bound at once while the count is below +0xcd130; no file gives -1 */
static THISCALL DWORD tex_allocIdBy(char *tm, DWORD name, DWORD flags, DWORD a, DWORD b, DWORD c, DWORD d, DWORD e, DWORD f)
{
	DWORD v[8] = { name, flags, a, b, c, d, e, f };
	return run_lifted(lift_4555b0, (DWORD)tm, 8, v);
}
/* 0x456be0 (thiscall) tex_getIdByName(...the same): try the six managers (+4..+0x18, null ones skipped) in turn;
   manager k's index i gives k * 512 + i; none is fatal */
static THISCALL DWORD tex_getIdByName(char *set, DWORD name, DWORD flags, DWORD a, DWORD b, DWORD c, DWORD d, DWORD e, DWORD f)
{
	DWORD v[8] = { name, flags, a, b, c, d, e, f };
	return run_lifted(lift_456be0, (DWORD)set, 8, v);
}
