/* crash_report.c: a crash in the process reported with its place (debug builds of the extension): the exception,
   the function and source line it happened in, and the calls that led there - read from the DLLs' debug symbols
   (PDB) with Windows' own dbghelp - written to stderr and to axis_crash.txt in the current folder. The crash then
   goes on as before. */
#include <windows.h>
#include <dbghelp.h>
#include <stdio.h>

static volatile LONG g_busy;

static void line_for(FILE *f, HANDLE p, DWORD64 a)
{
	char buf[sizeof(SYMBOL_INFO) + 256];
	SYMBOL_INFO *s = (SYMBOL_INFO *)buf;
	memset(buf, 0, sizeof buf);
	s->SizeOfStruct = sizeof(SYMBOL_INFO);
	s->MaxNameLen = 255;
	char module[MAX_PATH] = "?";
	HMODULE m = NULL;
	if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)(UINT_PTR)a, &m))
		GetModuleFileNameA(m, module, sizeof module);
	const char *base = strrchr(module, '\\');
	DWORD64 off = 0;
	IMAGEHLP_LINE64 line = { sizeof line };
	DWORD loff = 0;
	fprintf(f, "  %08llx %s+%llx", (unsigned long long)a, base ? base + 1 : module, (unsigned long long)(a - (DWORD64)(UINT_PTR)m));
	if (SymFromAddr(p, a, &off, s))
		fprintf(f, " %s+%llu", s->Name, (unsigned long long)off);
	if (SymGetLineFromAddr64(p, a, &loff, &line))
		fprintf(f, " (%s:%lu)", line.FileName, line.LineNumber);
	fprintf(f, "\n");
}

static void report(FILE *f, EXCEPTION_POINTERS *e)
{
	HANDLE p = GetCurrentProcess();
	fprintf(f, "crash: exception %08lx at %p\n", e->ExceptionRecord->ExceptionCode, e->ExceptionRecord->ExceptionAddress);
	CONTEXT c = *e->ContextRecord;
	STACKFRAME64 s;
	memset(&s, 0, sizeof s);
	s.AddrPC.Offset = c.Eip;
	s.AddrPC.Mode = AddrModeFlat;
	s.AddrFrame.Offset = c.Ebp;
	s.AddrFrame.Mode = AddrModeFlat;
	s.AddrStack.Offset = c.Esp;
	s.AddrStack.Mode = AddrModeFlat;
	for (int i = 0; i < 40; i++) {
		if (!StackWalk64(IMAGE_FILE_MACHINE_I386, p, GetCurrentThread(), &s, &c, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL))
			break;
		if (!s.AddrPC.Offset)
			break;
		line_for(f, p, s.AddrPC.Offset);
	}
	fflush(f);
}

static LONG CALLBACK on_crash(EXCEPTION_POINTERS *e)
{
	DWORD code = e->ExceptionRecord->ExceptionCode;
	if (code != EXCEPTION_ILLEGAL_INSTRUCTION && code != EXCEPTION_ACCESS_VIOLATION && code != EXCEPTION_INT_DIVIDE_BY_ZERO &&
	    code != EXCEPTION_STACK_OVERFLOW && code != EXCEPTION_PRIV_INSTRUCTION)
		return EXCEPTION_CONTINUE_SEARCH;
	/* (only crashes in this DLL: other modules' access violations may be handled by them) */
	HMODULE here = NULL, at = NULL;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)on_crash, &here);
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)e->ExceptionRecord->ExceptionAddress, &at);
	if (at != here && code != EXCEPTION_ILLEGAL_INSTRUCTION)
		return EXCEPTION_CONTINUE_SEARCH;
	if (InterlockedExchange(&g_busy, 1))
		return EXCEPTION_CONTINUE_SEARCH;
	SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME);
	SymInitialize(GetCurrentProcess(), NULL, TRUE);
	report(stderr, e);
	FILE *f = fopen("axis_crash.txt", "w");
	if (f) {
		report(f, e);
		fclose(f);
	}
	g_busy = 0;
	return EXCEPTION_CONTINUE_SEARCH;
}

void axis_crash_report_install(void)
{
	AddVectoredExceptionHandler(1, on_crash);
}
