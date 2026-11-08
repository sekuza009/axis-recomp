# In-game evidence check of names (read-only)

Repo: C:\Users\Alexander\Desktop\Axis\recomp - a readable-C rebuild of the 1999-2000 game AXIS (AxisGL.exe).
Read src/README.txt ("Records", "Globals", "Calls", "Names") and the rule: tools/names/NAMING_RULES.txt.

These names were confirmed by the code only, never seen in play. New scripted play sessions (multiplayer host + client,
Ladder server games with accounts, profile creation / deletion, ARM CENTER colour editing, replays, normal exit) have
now reached them. Your job: check each name, its type and its comment against what the game was SEEN doing.

Inputs (same folder as this brief):
- review_new.txt: one line per data name: `name | declaration | observed (values, how often non-zero) | comment`.
- review_fn.txt: one line per function: `name <tab> file <tab> calls <tab> contexts <tab> sessions <tab> callers`;
  contexts: s<N> front-end screen (100 intro, 200 title, 210 profile, 300 main menu, 400 lobby / Ladder, 500 skirmish,
  600 setup, 700 ARM CENTER, 800 game room, 900 missions, 9999 match: see m<N>), m<N> in a match by matchState
  (0 over, 1 loading, 2 playing, 3 mech test, 4 replay); sessions: mp1 / net2 (two copies: arena host + client),
  lad1-4 (Ladder server games; lad4: locked room, new ID registered, seeded account stats), prof1 (profile create /
  delete, ARM CENTER, skirmish round 15), broad1 (skirmish screen, ARM CENTER weapons + colour sliders, Ladder account
  page and create form), quit1 (exit through the profile screen).
Examples of contradictions: a "count" seen holding float bits, a "flag" with values 0..37, an "angle" outside its
range, a "pointer" holding small indices, a comment's value list (0 / 1 / 2 = ..) not matching the values seen, a
"click handler" called thousands of times per frame, a "match_" function seen only on a menu screen, an "init" seen
every frame, a name about one screen whose function ran on others.
Your starting point (in your task): C = read the rebuilt C uses to interpret the values; ORIGINAL = the original's
instructions (`python tools/disx.py`, `python tools/addr_access.py`) to interpret them. Do not read
tools/names/audit2026-11-07 or the git log.

Do NOT edit the repo. Write REPORT (path in your task): first line `EVIDENCE <C|ORIGINAL>: n checked; WRONG a,
CLEARER b`, then one line for each name that is not consistent (others taken as OK, so check every one):
- `name | WRONG -> newName | what the evidence contradicts (values / contexts) and the code that explains it`
  (a comment: `name | WRONG comment | "<current text>" -> "<new text>" | evidence`)
- `name | CLEARER -> ... | why`
Final message: the counts and each WRONG in one line. Python can't open /c/... paths: use C:/... paths.
