# Name audit, the kinds never checked: brief (read-only review)

Repo: C:\Users\Alexander\Desktop\Axis\recomp - a readable-C rebuild of the 1999-2000 game AXIS (AxisGL.exe).
Read src/README.txt first ("Records", "Objects", "Globals", "Names" parts). Every function name, parameter, record
FIELD, global (src/globals.h) and object (src/objects.h) has been audited against the code and play traces. Past
audits kept finding names that were guesses or carried an old wrong idea (e.g. "chat line" for what is any text
field, "free camera" for the mech test mode, "fade" for a plain timer, "stats panel" for the ARM CENTER parts
screen). Renames done so far: tools/names/audit2026-11-07/functions_renames.csv and data_*edits*.json - a name
below still built on an old name from those is suspect. The kinds of names below were never checked.

## Your job
Decide for every name in your part whether it (and its comment) says what the thing really is / holds - not more,
not less, not something else. Check every use (grep src), what writes and reads it, and where it runs
(tools/names/audit2026-11-07/function_trace.tsv: screens s<N> / match states m<N> each function ran in, its callers;
data_runtime.txt: values fields were seen holding in play). For the original's code: `python tools/disx.py 0xADDR`,
`python tools/addr_access.py 0xADDR`; message texts `python tools/names/msgtext.py 0xADDR`.
Don't rename for style; never invent: if the code doesn't settle it, UNSURE.

## Verdicts (one line per name - every name gets a line)
- `name | OK | <its uses / what confirms it, one line>`
- `name | RENAME -> new | <why; evidence>`
- `name | COMMENT | <what is wrong -> what it should say>`
- `name | UNSURE | <what is unclear; what would settle it>`
New names: keep the scheme of their neighbours; grep that a new name isn't already used anywhere in src.

## Output
Do NOT edit anything in the repo. Write REPORT (path in your task): first line
`GROUP <id>: <n> names; OK a, RENAME b, COMMENT c, UNSURE d`, then the lines. Also EDITS (path in your task): TSV
`kind<TAB>old<TAB>new<TAB>new comment or empty` per RENAME/COMMENT. Final message: the counts and the most important
wrong names with one-line reasons.
