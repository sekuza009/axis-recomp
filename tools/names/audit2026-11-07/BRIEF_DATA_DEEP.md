# Deep data-name audit: brief (read-only review)

Repo: C:\Users\Alexander\Desktop\Axis\recomp - a readable-C rebuild of the 1999-2000 game AXIS (AxisGL.exe).
Read src/README.txt first ("Records", "Objects", "Globals", "Names"). The user keeps finding data names that turned
out to be guesses, after several passes that leaned on comments, file lists and "(by use)" tags. This pass is the
deep one: a name is OK only if YOU read every use of it and every use agrees with the name, type and comment.

## Your part
The LIST file in your task: `file:line name` for each record field (src/scene.fields, `Struct.field`), global
(src/globals.h) or object (src/objects.h). Every one gets a verdict line - none skipped.

## Evidence, per name (all of it, every time)
1. Every use in src. Fields: `python tools/field_uses.py Struct.field -C 2` (Scene fields over the Stage region,
   Scene + 0x1f36c8, alias Stage fields: it shows both views; read both). Globals / objects: grep -rnw the name in
   src (also its address, e.g. `0x4db718`, and for objects any `name + 0x..` / `OBJ(name)` uses; a member of a
   record in an object, e.g. g_x + 0x1e, may have its own name). A field name shared by several structs: pick out
   the uses that are really this struct's (look at the pointer's type).
   Read each use line in its function: who writes it (with what values), who reads it (and what for). Not the
   comment - the code.
2. The original, when the rebuild's use is unclear or there seem to be no readers: `python tools/addr_access.py
   0xADDR` (every instruction touching a global), `python tools/disx.py 0xADDR`, message texts
   `python tools/names/msgtext.py 0xADDR` (screen labels: use the game's own words). Game data files are in
   C:\Users\Alexander\Desktop\Axis (initdata\ ...).
3. Runtime: RUNTIME file (path in your task): `name | declaration | observed values (range, distinct values, how often
   non-zero, which sessions) | comment`. Names not in it were never seen non-zero: NOTSEEN file. Sessions: skirmish,
   profile, mainmenu, setup, multi, ladder, ladderserver, armc, replay, missions, host matches of each game type,
   mp (host + client), formsB (Ladder forms), formsC (arena create form, player name), itemsD (ARM CENTER shoulder
   items), setupE (setup toggles), sessA (hosted arena: free camera, cheat codes, Esc menu, time limit).
   The values must fit: a "count" holding float bits, a "flag" with values 0..37, a "time" that never changes, a
   "player index" above 7, a "pointer" always a small number - each means the name or type is wrong. A comment
   giving values (0 / 1 / 2 meaning X / Y / Z) must match the values seen. Note: big junk values (e.g. 1499027929)
   in a record array usually mean an unused slot in the sampler's walk - say so, don't rename for it.

## Verdicts (one line per name, in list order)
- `Name | OK | code: <writers: who / what values; readers: who / for what>; run: <values that agree> or NOT SEEN: <how to reach in game>`
- `Name | RENAME -> newName | <why; evidence>`
- `Name | TYPE -> newType | <why; which uses would need BITS() / a cast>`
- `Name | COMMENT | <what is wrong -> the corrected comment text>`
- `Name | UNSURE | <what is unclear; what would settle it (an in-game action, or a disassembly read)>`
The code part must name real writers and readers (function names), not "N uses". New names: camelCase (g_ prefix
for globals, k_ for constants), in the game's own terms; grep that the new name is unused. Keep cleared*/unused*
names only for data the ORIGINAL only writes / never touches (check addr_access before calling something unused).
Never invent a name: if the code doesn't settle it, UNSURE. Don't rename for style alone.
Already being handled elsewhere - don't propose types for these (still check their names / comments):
Manager.tint, MapObject.glowSize, ObjectType.glowSize, Player.unused34, SpawnRecord.unused34, Scene.cameraPos,
Scene.cameraSaved, Scene.clearColour, Scene.fogColour, Scene.fogParams, Space.margin, Stage.clearColour,
Stage.glFogColour, Stage.glFogDensity, Stage.glFogEnd, Stage.glFogStart (all u32 holding float bits -> float).

## Output
Do NOT edit anything in the repo. Write REPORT (path in your task): first line
`PART <id>: <n> names; OK a, RENAME b, TYPE c, COMMENT d, UNSURE e; not seen running f`, then the verdict lines in
list order. EDITS (JSON, path in your task): `{"Struct.field" or "g_name": {"name": new, "type": new, "comment":
full new comment text}}` - only the keys that change. REACH (path in your task): for each NOT SEEN name, one line
`name | in-game action that would make it non-zero` (so a scripted session can be run for it).
Work through the list in order and append to REPORT as you go (so nothing is lost). Final message: the counts and
the most important wrong names (up to 15) with one-line reasons.
