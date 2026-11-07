# Function-name audit: brief (read-only review)

Repo: C:\Users\Alexander\Desktop\Axis\recomp - a readable-C rebuild of the 1999-2000 game AXIS (AxisGL.exe).
src/ holds every game function rebuilt in C (conventions: src/README.txt, read its "Records", "Names", "Calls" parts).
Earlier naming passes checked names against the code; the user keeps finding names that turned out to be guesses.
This pass must leave NO guessed name: every function name must be confirmed BOTH by the code and by what the game
was seen doing when it ran.

## Your job
For EVERY function defined in your files (exported ones `void (name)(...)` and file-local `static` helpers), and
its parameter names, decide whether the name says what the function really does - not more, not less, not
something else. Also the description comment above it: if the comment claims something the code doesn't do, flag it.

Evidence you must use:
1. Code: read the body, what it reads / writes (fields in src/scene.fields, globals in src/globals.h /
   src/objects.h), what it calls and who calls it (grep the name in src). For a doubt about the rebuild itself,
   the original: `python tools/disx.py 0xADDR` (disassembly; the address is the first thing in each function's
   comment), `python tools/addr_access.py 0xADDR` (every instruction touching a global), message texts:
   `python tools/names/msgtext.py 0xADDR`.
2. Runtime (what the game did in play): EVIDENCE file (path given in your task) - one line per function:
   `name <tab> file <tab> calls <tab> contexts <tab> sessions <tab> callers (name xN, ...)`
   or `name <tab> file <tab> NOT RUN`.
   - contexts: s<N> = front-end screen g_screen (100 intro, 200 title, 210 profile list, 300 main menu, 400 lobby /
     Ladder, 500 skirmish, 600 setup, 700 ARM CENTER, 800 game room, 900 mission list); m<N> = in a match by
     matchState (0 over, 1 loading, 2 playing, 3 free camera, 4 replay); s0 = start-up before any screen.
   - sessions: which scripted run reached it: skirmish (a skirmish match), profile, mainmenu, setup, multi
     (multiplayer menus), ladder / ladderserver (Ladder screens with a local server), armc (ARM CENTER), replay,
     missions (the unused mission list), host-h2_1..4 (hosted DEATH MATCH / TEAM DEATH MATCH / KING ON THE HILL /
     PLATOON MODE arenas), mp (two copies, host + client), sessA (hosted arena: free camera keys, chat cheat codes,
     Esc menu, time running out), sessB (Ladder forms: new ID, account page, ranking sorts, create-room form),
     sessC (arena create form, player name, ARM CENTER from the player page), sessD (every ARM CENTER shoulder
     item), sessE (setup: key rebound, mouse tab, sound / graphics toggles), quit (the game quit from the profile
     screen's log-out question).
   - callers: which functions called it and how often ('+off' dropped; an inlined helper reports its outer function).
   Use it as a check on the name: a "click" handler that ran 50 000 times per session from a frame function is not a
   click handler; a "match_" function seen only on s700 is not a match function; "init" seen every frame is not an
   init; "loadX" whose callers are draw functions is suspicious; a name claiming ranked/Ladder use but run in a
   skirmish is wrong; call counts tell per-frame vs per-event vs once.
   NOT RUN: say what in-game action should reach it (from its callers' chain) - it's then code-confirmed only.

## Verdicts (one line per function, in your report)
- `name | OK | code: <what it does, 1 line>; run: <contexts/callers that agree>`
- `name | RENAME -> newName | <why the old name is wrong or a guess; evidence>`
- `name | COMMENT | <what in the comment is wrong -> what it should say>` (name right, comment wrong)
- `name | PARAMS | <param old -> new, why>`
- `name | UNSURE | <what is unclear; what would settle it>` - only if the code really doesn't settle it.
- add ` (NOT RUN: <how to reach>)` to any verdict for a function the trace didn't see.

Rules for new names: keep the file's prefix scheme (subsystem_ or Record_ for thiscall on a record; menuStateN_ for
screen states), camelCase after the prefix, say what it does in the game's own terms (screen titles / labels from
MSG texts, the record it works on). Don't rename for style alone. Never invent: if you can't confirm a better name,
say UNSURE. A rename must be checked: grep that the new name isn't already used.

## Output
Do NOT edit anything under the repo. Write your report to the REPORT path given in your task:
first line `GROUP <id>: <n> functions; OK a, RENAME b, COMMENT c, PARAMS d, UNSURE e; NOT RUN f`, then the verdict
lines grouped by file. Also write RENAMES path (CSV `old,new` one per line, only RENAME verdicts). Your final message:
the counts and the 10 most important wrong names with one-line reasons.
Be thorough: every function in your files gets a line (list them with grep first so none is skipped).
