# Local-variable name audit: brief (read-only review)

Repo: C:\Users\Alexander\Desktop\Axis\recomp - a readable-C rebuild of the 1999-2000 game AXIS (AxisGL.exe).
Read src/README.txt first ("Records", "Names", "Calls" parts). Every function name, parameter, record field, global
and object has been audited against the code and play traces. Local variables never have been. Past audits kept
finding names that were guesses or carried an old wrong idea (e.g. "chat line" for what is any text field, "free
camera" for the mech test mode, "fade" for a plain timer, "HUD projection" for the match's 3D projection). Locals
were named in the same passes, so they can hold the same mistakes - including names copied from a field / global /
function that has since been renamed (tools/names/audit2026-11-07/functions_renames.csv and the data_* edits there
list the renames; e.g. a local `chat` holding g_inputLine, a local `stats` holding g_mechMaxima).

## Your job
For every local in your list (LOCALS file, filtered to your FILES list; columns: file:line, function, name,
declaration line), decide whether its name says what it holds. Read the function: what is assigned to it, how it is
used, what field/global it comes from and what that field/global is called NOW (src/scene.fields, src/globals.h,
src/objects.h). A local named after a field it is loaded from should match that field's current name/meaning.
Generic working names (name, text, size, count, slot, colour, left/right ...) are fine when true - don't rename for
style. Check: a "count" that is really an index, an "angle" that is a distance, "player" holding an actor index or
a Space, "hovered" that is the clicked one, "bright" that is a colour, "timer" that is a fade (or the reverse), a
name about one screen in a function used by several, a name about one use of a general thing.
The function trace (tools/names/audit2026-11-07/function_trace.tsv: screens / match states each function ran in,
its callers) tells you where a function really runs: use it when a local's name claims a context.
For a doubt about the rebuild itself: `python tools/disx.py 0xADDR` (the address starts each function's comment).

## Verdicts
Only write lines for locals that need a change (all others are taken as OK - so check every one):
- `file:line | function | old | RENAME -> new | why (evidence)`
- `file:line | function | old | COMMENT | the comment next to it is wrong -> what it should say`
- `file:line | function | old | UNSURE | what is unclear`
New names: camelCase like the file's other locals, say what it is in the game's terms, must not clash with another
name in that function or a macro/global (grep `\bnew\b` in src/globals.h, src/objects.h, src/game.h, src/data/layout_names.h).
Never invent: if the code doesn't settle it, UNSURE.

## Output
Do NOT edit anything in the repo. Write REPORT (path in your task): first line
`GROUP <id>: <n> locals checked; RENAME a, COMMENT b, UNSURE c`, then the lines in file order. Also EDITS (path in
your task): TSV `file<TAB>function<TAB>old<TAB>new` per RENAME. Final message: the counts and the 10 most
important wrong names with one-line reasons.
