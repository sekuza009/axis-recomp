# Data-name audit: brief (read-only review)

Repo: C:\Users\Alexander\Desktop\Axis\recomp - a readable-C rebuild of the 1999-2000 game AXIS (AxisGL.exe).
Read src/README.txt first (its "Records", "Objects", "Globals", "Names" parts). Earlier passes checked these names
against every use in the code; the user keeps finding names that turned out to be guesses. This pass must leave NO
guessed name: every record field / global / object name must be confirmed BOTH by the code (every use) and by the
values the game was seen holding while it ran.

## Your job
For every name in your part (each struct's fields in src/scene.fields, or each global / object in src/globals.h /
src/objects.h): does the name - and its type and comment - say what the data really is? A tag "(by use)" / "(by use;
seen running)" or an earlier pass is NOT proof: check again.

Evidence you must use:
1. Code: every use. `python tools/field_uses.py Struct.field` (every use of a field in src), grep for globals;
   the original's instructions touching a global: `python tools/addr_access.py 0xADDR`; disassembly
   `python tools/disx.py 0xADDR`; message texts `python tools/names/msgtext.py 0xADDR`. Remember Scene fields over the
   Stage region (Scene + 0x1f36c8) alias Stage fields: check both views. Game data files are in
   C:\Users\Alexander\Desktop\Axis (initdata\ ...) where a field comes from a file.
2. Runtime: RUNTIME file (path in your task), one line per name seen non-zero in play:
   `name | declaration | observed (range, distinct values, how often non-zero, which sessions) | comment`.
   Names absent from it were never seen non-zero (or never reached) in the scripted sessions - see NOTSEEN file.
   Sessions: skirmish, profile, mainmenu, setup, multi, ladder, ladderserver, armc, replay, missions, host
   matches of each game type, mp (host + client), sessA (hosted arena: free camera, cheat codes, Esc menu, time
   limit), sessB (Ladder forms), sessC (arena create form, player name), sessD (ARM CENTER items), sessE (setup
   toggles). Check the values against the name: a "count" that holds float bits, a "flag" with values 0..37, a
   "time" that never changes, a "player index" above 7, an "angle" outside its range, a "pointer" that's always an
   index - all mean the name (or type) is wrong. A name whose comment gives values (0 / 1 / 2 meaning X / Y / Z)
   must match the values seen.

## Verdicts (one line per name, in your report)
- `Name | OK | code: <its uses in a line>; run: <values that agree / NOT SEEN: how to reach>`
- `Name | RENAME -> newName | <why; evidence>`
- `Name | TYPE -> newType | <why>` (e.g. int holding float bits)
- `Name | COMMENT | <what is wrong -> what it should say>`
- `Name | UNSURE | <what is unclear; what would settle it>`
For scene.fields use `Struct.field` as Name. New names: camelCase, say what it is in the game's own terms; keep
cleared*/unused* names only for fields the original only writes / never touches (check the original with
addr_access / disx before calling something unused). Don't rename for style alone; never invent.

## Output
Do NOT edit anything in the repo. Write REPORT (path in your task): first line
`GROUP <id>: <n> names; OK a, RENAME b, TYPE c, COMMENT d, UNSURE e; not seen running f`, then the verdict lines in
file order. Also EDITS (JSON, path in your task): for scene.fields `{"Struct.field": {"name": new, "type": new,
"comment": text}}` (only keys that change); for globals / objects `{"g_old": {"name": "g_new", "type": ..., "comment":
...}}`. Your final message: the counts and the 10 most important wrong names with one-line reasons.
Every name in your part gets a line: list them first so none is skipped.
