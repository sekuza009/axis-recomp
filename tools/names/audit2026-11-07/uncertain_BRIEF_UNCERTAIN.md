# Uncertain names: independent review (read-only)

Repo: C:\Users\Alexander\Desktop\Axis\recomp - a readable-C rebuild of the 1999-2000 game AXIS (AxisGL.exe).
Read first: src/README.txt (its "Records", "Objects", "Globals", "Calls", "Names" parts) and the rule you judge by,
tools/names/NAMING_RULES.txt (WRONG / CLEARER / UNDECIDABLE).

The names in your list are the uncertain ones: no traced play session ever saw them hold a value or run, or an
earlier reviewer could not decide. Another reviewer judges the same list independently from a different starting
point; a change is made only where you both find the same thing. So:
- Do NOT read tools/names/audit2026-11-07/ (earlier verdicts), the git log, or any file in the scratchpad except
  your list. Judge from the code and the original.
- The name's own comment is a claim to check, not evidence.
- Be exact and conservative: WRONG only when the code contradicts the name / type / comment (NAMING_RULES.txt).
  A true but improvable name is CLEARER. If the code cannot settle it, UNDECIDABLE.

## Your starting point (given in your task)
- C: start from the rebuilt C. Every use: `python tools/field_uses.py Struct.field`, grep for globals / functions,
  read each function that writes or reads it and its callers; data files in C:\Users\Alexander\Desktop\Axis
  (initdata\ ...) where a value comes from a file. Check the original (`python tools/disx.py 0xADDR`) only where
  the C is unclear.
- ORIGINAL: start from the original game. For a global: `python tools/addr_access.py 0xADDR` (every instruction
  touching it; the address is in src/globals.h / src/objects.h), then `python tools/disx.py 0xFUNC` on those
  functions; for a field, the functions using it (find them with grep / field_uses.py) disassembled; for a function,
  `python tools/disx.py 0xADDR` (the address starts its comment in src) and what it calls / who calls it; message
  texts `python tools/names/msgtext.py 0xADDR`. Read the rebuilt C only after forming your view, to map names.
Scene fields over the Stage region (Scene + 0x1f36c8) alias Stage fields: check both views.

## Output
Do NOT edit anything in the repo. Write REPORT (path in your task): first line
`<chunk> <C|ORIGINAL>: <n> names; OK a, WRONG b, CLEARER c, UNDECIDABLE d`, then ONE line per name in list order:
- `name | OK | <the evidence in one line>`
- `name | WRONG -> newName | <what the code contradicts; evidence: function / address>`  (comment-only: `WRONG comment -> <what it should say>`)
- `name | CLEARER -> newName | <why>`
- `name | UNDECIDABLE | <what is unknown>`
Every name gets a line. New names: the scheme of their neighbours (camelCase fields, g_ globals, subsystem_ /
Record_ functions); grep that a new name is free. Final message: the counts and every WRONG with its reason.
Python can't open /c/... paths: use C:/... paths. Write scripts with the Write tool, not bash heredocs with backslashes.
