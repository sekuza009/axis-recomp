/* inject.exe <pid> <dll path>: load a DLL into a running 32-bit process (CreateRemoteThread + LoadLibraryA).
   Built 32-bit so LoadLibraryA's address matches the target's kernel32. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	if (argc != 3) { fprintf(stderr, "usage: inject <pid> <dll>\n"); return 2; }
	DWORD pid = (DWORD)strtoul(argv[1], NULL, 10);
	char full[MAX_PATH];
	GetFullPathNameA(argv[2], MAX_PATH, full, NULL);
	HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (!h) { fprintf(stderr, "OpenProcess failed %lu\n", GetLastError()); return 1; }
	SIZE_T n = strlen(full) + 1;
	void *mem = VirtualAllocEx(h, NULL, n, MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(h, mem, full, n, NULL);
	FARPROC ll = GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	HANDLE t = CreateRemoteThread(h, NULL, 0, (LPTHREAD_START_ROUTINE)ll, mem, 0, NULL);
	if (!t) { fprintf(stderr, "CreateRemoteThread failed %lu\n", GetLastError()); return 1; }
	WaitForSingleObject(t, 10000);
	DWORD mod = 0;
	GetExitCodeThread(t, &mod);
	printf("loaded %s at %08lx\n", full, mod);
	return mod ? 0 : 1;
}
