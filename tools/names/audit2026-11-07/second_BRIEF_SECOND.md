# Second independent review of the names (read-only)

Repo: C:\Users\Alexander\Desktop\Axis\recomp - a readable-C rebuild of the 1999-2000 game AXIS (AxisGL.exe).
Read first: src/README.txt (its "Records", "Objects", "Globals", "Calls", "Names" parts) and the rule you judge by,
tools/names/NAMING_RULES.txt (WRONG / CLEARER / UNDECIDABLE).

Every name in your list was judged right by one earlier reviewer. You are the second, independent reviewer: where you
find a name WRONG, a third reviewer will settle it. So:
- Do NOT read tools/names/audit2026-11-07/ (earlier verdicts), the git log, or any scratchpad file except your list.
- A name's own comment is a claim to check, not evidence. Check its type and its comment too.
- Be exact and conservative: WRONG only when the code contradicts the name / type / comment (NAMING_RULES.txt);
  true but improvable is CLEARER; what the code cannot settle is UNDECIDABLE.

## Starting point (given in your task)
- ORIGINAL: start from the original game. A global: `python tools/addr_access.py 0xADDR` (every instruction touching
  it; its address is in src/globals.h / src/objects.h), then `python tools/disx.py 0xFUNC` on those functions. A field:
  find the functions using it (`python tools/field_uses.py Struct.field`, grep) and read their disassembly at its
  offset (Scene fields over the Stage region, Scene + 0x1f36c8, alias Stage fields: check both views). A function:
  `python tools/disx.py 0xADDR` (the address starts its comment in src), what it calls, who calls it; message texts
  `python tools/names/msgtext.py 0xADDR`. Read the rebuilt C after forming your view, to map names. For a function also
  judge its parameters and the comment above it. What the game did in play: tools/names/audit2026-11-07 is off
  limits, but the play traces are allowed: tools/names/audit2026-11-07/function_trace.tsv (screens s<N> / match states
  m<N> each function ran in, its callers) and tools/names/audit2026-11-07/data_runtime.txt (values seen) - use them
  as evidence, not their verdict files.
- C: start from the rebuilt C: read the function the local is in (what is assigned, how it is used, what field /
  global / function it comes from and what that is called now), or for a table / type / file every use and what it
  holds; check the original (`python tools/disx.py`) where the C leaves a doubt.

## Output
Do NOT edit anything in the repo. Write REPORT (path in your task): first line
`<chunk> <ORIGINAL|C>: <n> names checked; WRONG a, CLEARER b, UNDECIDABLE c`, then ONE line for every name that is
not OK (the others are taken as OK - so check every one), in list order:
- `name | WRONG -> newName | <what the code contradicts; evidence: function / address / file:line>`
  (a comment: `name | WRONG comment | "<the current text, quoted exactly>" -> "<new text>" | evidence`;
   a parameter: `name | WRONG param old -> new | evidence`)
- `name | CLEARER -> newName | <why>`
- `name | UNDECIDABLE | <what is unknown>`
New names: the scheme of their neighbours; grep that a new name is free. Final message: the counts and every WRONG
in one line each. Your list may be long: you may split it with forks, then merge their parts into the one report.
Python can't open /c/... paths: use C:/... paths. Write scripts with the Write tool, not bash heredocs with backslashes.
