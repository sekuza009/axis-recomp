/* record probes (test only): records the game keeps only briefly - match packets as sent / received, DirectPlay
   session descriptions, particle descriptors, map objects' info, BMP headers - copied when the game fills or reads
   them, so tools/ftrace/probe_decode.py can say which fields were seen with which values. The calls are put into
   copies of the source files by tools/ftrace/build_probes.sh; src/ itself has none.
   Out: Axis\probe_<pid>.txt, one line per kept record: "<type> <hex bytes>", flushed every 2 s and at exit.
   Kept: the first 64 of each type (and packet kind), then one in 64. */
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define NTYPE 64
static struct { char name[24]; unsigned seen; } g_types[NTYPE];
static FILE *g_out;
static CRITICAL_SECTION g_lock;
static volatile LONG g_ready;

static DWORD WINAPI flush_thread(void *unused)
{
	(void)unused;
	for (;;) {
		Sleep(2000);
		EnterCriticalSection(&g_lock);
		if (g_out)
			fflush(g_out);
		LeaveCriticalSection(&g_lock);
	}
}

static void probe_end(void)
{
	EnterCriticalSection(&g_lock);
	if (g_out)
		fclose(g_out), g_out = NULL;
	LeaveCriticalSection(&g_lock);
}

static void probe_start(void)
{
	char path[MAX_PATH];
	InitializeCriticalSection(&g_lock);
	snprintf(path, sizeof path, "probe_%lu.txt", GetCurrentProcessId());
	g_out = fopen(path, "w");
	atexit(probe_end);
	CreateThread(NULL, 0, flush_thread, NULL, 0, NULL);
	g_ready = 1;
}

void probe_record(const char *type, const void *p, int size)
{
	char key[24];
	if (InterlockedCompareExchange(&g_ready, 2, 0) == 0)
		probe_start();
	while (g_ready != 1)
		Sleep(0);
	if (!p || size <= 0 || size > 0x10000)
		return;
	if (!strcmp(type, "pkt"))   /* (match packets: counted per kind, the second byte) */
		snprintf(key, sizeof key, "pkt%u", ((const unsigned char *)p)[1]);
	else
		snprintf(key, sizeof key, "%s", type);
	EnterCriticalSection(&g_lock);
	int k;
	for (k = 0; k < NTYPE && g_types[k].name[0] && strcmp(g_types[k].name, key); k++)
		;
	if (k < NTYPE) {
		if (!g_types[k].name[0])
			strcpy(g_types[k].name, key);
		unsigned n = g_types[k].seen++;
		if (g_out && (n < 64 || n % 64 == 0)) {
			fprintf(g_out, "%s ", type);
			for (int i = 0; i < size; i++)
				fprintf(g_out, "%02x", ((const unsigned char *)p)[i]);
			fputc('\n', g_out);
		}
	}
	LeaveCriticalSection(&g_lock);
}
