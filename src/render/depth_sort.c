/* depth_sort.c: the two depth sorts of the draw lists (transparent triangles and billboards): an explicit-stack quicksort of 8-byte entries {id, float key}, ascending by key, whose stack, indices, pivot and swap space live in the game's globals (as in the original, so the memory it leaves behind is the same). */
#include "../game.h"

#define GAME_I32(a) GAME_VAR(int, a)
#define GAME_U32(a) GAME_VAR(u32, a)
#define GAME_F32(a) GAME_VAR(float, a)
#define FIELD_I32(p, o) GAME_VAR(int, (u8 *)(p) + (o))

/* where a sort keeps its state: the stack depth, then arrays by depth (lo, hi, i, j, pivot) and two dwords of swap space */
typedef struct { u32 sp, lo, hi, i, j, piv, tmp; } QsGlobals;
#define QA(base, k) GAME_I32((base) + (k) * 4)

/* sort 8-byte entries {id, float key} ascending by key in e[lo..hi]; hi also bounds the forward scan */
static void depth_sort(const QsGlobals *q, u32 *e, int lo, int hi)
{
#define KEY(k) (*(float *)&e[(k) * 2 + 1])
#define PIV(s) GAME_F32(q->piv + (s) * 4)
	if (lo >= hi) return;
	int sp = 1;
	GAME_I32(q->sp) = 1; QA(q->lo, 1) = lo; QA(q->hi, 1) = hi;
	do {
		int bound = QA(q->hi, 1), a = QA(q->lo, sp), b = QA(q->hi, sp);
		if (a < b) {
			QA(q->i, sp) = a; QA(q->j, sp) = b + 1; GAME_U32(q->piv + sp * 4) = e[a * 2 + 1];
			do {
				int i = ++QA(q->i, sp);
				if (i != bound)
					while (!(KEY(i) >= PIV(sp))) { QA(q->i, sp) = ++i; if (i == bound) break; }
				int j;
				do j = --QA(q->j, sp); while (KEY(j) > PIV(sp));
				i = QA(q->i, sp);
				if (i < j) {
					GAME_I32(q->tmp) = e[i * 2]; GAME_I32(q->tmp + 4) = e[i * 2 + 1];
					e[i * 2] = e[j * 2]; e[i * 2 + 1] = e[j * 2 + 1];
					int jj = QA(q->j, GAME_I32(q->sp));
					e[jj * 2] = GAME_I32(q->tmp); e[jj * 2 + 1] = GAME_I32(q->tmp + 4);
					sp = GAME_I32(q->sp);
				}
			} while (QA(q->i, sp) < QA(q->j, sp));
			int l = QA(q->lo, sp);                   /* pivot into place */
			GAME_I32(q->tmp) = e[l * 2]; GAME_I32(q->tmp + 4) = e[l * 2 + 1];
			int jj = QA(q->j, sp);
			e[l * 2] = e[jj * 2]; e[l * 2 + 1] = e[jj * 2 + 1];
			jj = QA(q->j, GAME_I32(q->sp));
			e[jj * 2] = GAME_I32(q->tmp); e[jj * 2 + 1] = GAME_I32(q->tmp + 4);
			sp = GAME_I32(q->sp) + 1; GAME_I32(q->sp) = sp;   /* push the left part */
			QA(q->lo, sp) = QA(q->lo, sp - 1); QA(q->hi, sp) = QA(q->j, sp - 1) - 1;
		} else if (a == QA(q->j, sp - 1)) {      /* left part done: do the parent's right part */
			QA(q->lo, sp) = a + 1; QA(q->hi, sp) = QA(q->hi, sp - 1);
		} else {
			if (b == QA(q->hi, sp - 1)) {           /* right part done: pop finished levels */
				do sp--; while (QA(q->hi, sp) == QA(q->hi, sp - 1));
				GAME_I32(q->sp) = sp;
			}
			QA(q->lo, sp) = QA(q->j, sp - 1) + 1; QA(q->hi, sp) = QA(q->hi, sp - 1);
		}
	} while (sp > 1);
#undef KEY
#undef PIV
}

static const QsGlobals k_sortA = { 0xae5338, 0x4c83c4, 0x4ca3c4, 0xae3338, 0xae7340, 0xaed350, 0xae9340 };

void (render_depthSortA)(u32 *e, int lo, int hi) { depth_sort(&k_sortA, e, lo, hi); }

static const QsGlobals k_sortB = { 0xae533c, 0x4cc3c4, 0x4ce3c4, 0xaeb350, 0xae9350, 0xae5340, 0xae9348 };

void (render_depthSortB)(u32 *e, int lo, int hi) { depth_sort(&k_sortB, e, lo, hi); }
