# Third reviewer: settle the disputed names (read-only)

Repo: C:\Users\Alexander\Desktop\Axis\recomp - a readable-C rebuild of the 1999-2000 game AXIS (AxisGL.exe). Read
src/README.txt ("Records", "Globals", "Calls", "Names") and the rule you judge by: tools/names/NAMING_RULES.txt
(WRONG / CLEARER / UNDECIDABLE).

Each line of your list is one claim: a second reviewer called a name, parameter or comment WRONG ([chunk] tag first;
F functions and D data checked from the original, L locals and R tables / types / files from the C), while the first
reviewer had passed it. A few lines are CLEARER notes on the same names, given for context. Check each WRONG claim
yourself, both ways - the rebuilt C (read the code; grep; `python tools/field_uses.py Struct.field`) and the original
(`python tools/disx.py 0xADDR`, the function's address first in its comment; `python tools/addr_access.py 0xADDR` for
a global; `python tools/names/msgtext.py`; Win32 / OpenGL constants by their documented values). Don't trust the
claim's wording; confirm the fact. Some names may have moved since (line numbers drift). Where several lines make the
same claim (e.g. chat_openTextField / chat_endTyping, armc_buildPartLists' `network` and unlocked_level's), settle
them together and keep the fixes consistent. Note: a name narrower than its use (an "arena" global the game room uses
the same way) is WRONG by the rule only if the narrower name misleads about what it is or where it acts.

Do NOT edit the repo. Write REPORT (path in your task): first line `THIRD <part>: n items; CONFIRMED a, NOT WRONG b,
CLEARER c`, then one line per WRONG item:
- `name | CONFIRMED | the exact fix: new name (grep that it is free in src), or for a comment "<current text, quoted
  exactly as in the file now>" -> "<new text>", with the file | evidence (file:line, original address)`
- `name | NOT WRONG | why the claim fails (evidence)`
- `name | CLEARER | the optional improvement`
Final message: the counts and each confirmed fix in one line. Python can't open /c/... paths: use C:/... paths;
write scripts with the Write tool, not bash heredocs with backslashes.
