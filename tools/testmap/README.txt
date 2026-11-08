AxisGL test map: test.bfd
=========================

Files (this folder)
  bfd.py      decode / encode of a .bfd (the five sections, scrambling, trailing data kept)
  mkmap.py    python mkmap.py [source.bfd] [out.bfd] [--no-tex-trick] [--roundtrip-only]
              reads the source (default ...\Axis\Map\valhalla.bfd; never written), checks that decode -> encode gives
              the same bytes, adds the records below, writes out.bfd (default test.bfd here). It refuses to write
              into the game folder.
  verify.py   python verify.py test.bfd 0   re-runs the loaders' reads and checks without the game (see "Checks").
  survey.py   python survey.py [-v] [maps]  round trip + summary of every shipped map (all 32 round-trip identical).
  test.bfd    the result.

What it stands in for
  test.bfd is valhalla.bfd: map 0 of initdata\mapinfo.dat ("Valhalla", Orbital battle pit), the first single-player
  stage. The 15 single-player stages are the skirmish rounds 0..14 = map indices 0..14 (Valhalla, Catacomb, Midgard,
  jotunheim, Bootcamp, Centropolis, Titanforge, Bloodbath, Gigantic-Core, Hive, Asgard, Abyss, Metropolis, StarField,
  Netsphere): skirmish_startRound sets g_mapIndex = the round shown, the loader opens "map/<g_mapNames[g_mapIndex]>.bfd"
  ("%s.bfd" from Scene.mapName, every loader re-opens the same file and skips to its section). Round 0 needs no
  campaign progress (the arrows only go up to g_progress).
  To use it: back up Map\valhalla.bfd, copy test.bfd over Map\valhalla.bfd, start the single-player (skirmish) screen,
  round 1 VALHALLA, OK; restore the original afterwards. The ground section's mapNumber stays 0, so only the
  Valhalla slot accepts it ("file damaged!" if g_mapIndex != mapNumber). Delete any Map\Temp-valhalla-objectShadingInfo.dat
  if one ever appears (none exists now; mode 0 only reads it, and it would hold shading for the old object list).

.bfd layout (as the loaders read it)
  u32 0x1201 plain, the rest scrambled (read: rol1(b ^ 0x59)). Sections 1-4 each a u32 size + data:
  1 objects (count, ObjectInfo 0xb0), 2 play info (count, 0x24 records), 3 mission (commands 0x30, way points 0x14,
  triggers 0x1c, each a count + records), 4 actors (MapPlayer 0x58, SpawnRecord 0x5c); 5 ground (no size; dir, view
  range, lights, clear, fog, sky / layer / side / floor modes, limits, map number, music, layers 0x20c + 256x256 RGB);
  then ~10.9 MB the loaders never read (kept byte for byte).

Where the player starts / how to reach the approach trigger
  Valhalla has 8 multiplayer starts; local_spawn takes a random free one (spawn_point), so the start is one of these
  (x, y, z; y is up; headings in degrees as the file has them, the game uses x10):
     (-11384, 38992,  -9112) head -181   (this one faces ~43 deg away from the centre: turn LEFT ~43 deg first)
     ( 13968, 38492,  16778) head  -50
     (-16217, 38992,   3736) head -273
     (-11133, 38992,  15345) head -309
     (  1008, 38992,  20779) head    0
     ( 19034, 38492,   3704) head  -89
     ( 13471, 38492,  -9532) head -137
     (   860, 39092, -14541) head -181
  Every start but the first faces the arena centre (within ~6 deg) and is 17000 .. 18700 from it. Heading 0 looks
  along -z, heading +90 along +x (so a larger heading is a turn to the right).
  Approach trigger (22): way point (800.8, 36500, 3447.4), radius 6000 (file value 60 -> 60^2 x 10000), 3D distance.
  On the main floor (y ~ 39000) it fires within ~5400 horizontally of (800, 3447): walk FORWARD ~12000 .. 13500 from
  any start (about 4.5 s at 100 km/h, 2778 units/s). The centre has the dom ring-00 at y 39100 and a lower level
  (y ~ 32700) under it; both are within the radius.

What was added and what it should drive
 Mission section (map_loadMissionInfoFrom; 21 shipped triggers -> 61, 183 way points -> 225, 0 commands -> 365)
  * Shipped triggers 0..20 (the bots' navigation paths; shipped with armed 1, fired 1, no commands): every way point
    now carries command 11 (Actor.scriptFlag = 1), and by position j: j%4==1 command 14 (Actor.invulnerable = 1),
    j%4==3 command 4 (Actor.botWait = 2.0 s), j%8==6 command 12 (wait / invulnerable / look reset). These run with the
    bot as the actor when a wandering bot reaches the point (actor_frame: within 1000 -> script_processCommandBy); at
    frame 1 the shipped "fired 1" runs entry 0 of each with no actor (no-ops). Side effect: bots often become
    invulnerable (the stage cannot really be won).
  * Trigger 21 TIME: flags 1, time 20.0 s of the match clock (clockSeconds, from 0 at load). Way point 0 commands:
    23 (actor 1 = the first bot: path 23, point 0), 26 MESSAGE (text block 0, colour 2, 4th argument 7),
    27 scene path "TestSceneHold" mode 1 (Stage.scriptMode 1, scriptHoldsPlay 1), 24 hold actor 2 (mode 3, value 1 ->
    Actor.outOfPlay 1; only if actor 2 is in play, i.e. the player spawned before 20 s - spawn quickly).
  * Trigger 22 APPROACH: flags 2, radius 6000 (see above). Commands: 26 (text block 1, colour 5, 4th arg 11),
    23 (bot 1 on the bot path again), 24 hold actor 2 (mode 4, value 2; lets the previously held one go first),
    27 "TestSceneApproach" mode 2.
  * Trigger 23 BOT PATH (armed 0, fired only through command 23): 3 way points copied from shipped points near the
    centre (76, 78, 79): [11, 14, 4 = botWait 3 s], [10, 13 = speed 60 km/h], [12, 11]. A bot with a target drops its
    path (actor_frame line "path = -1"), so bot 1 follows it only while it does not see the player.
  * Triggers 24..59 MESSAGE CHAIN: flags 1, times 30, 32, .. 100 s; each one MESSAGE (text blocks 2/3 alternating,
    the last block 4; colour = trigger % 17, so 16 = the "transparent" branch occurs twice; 4th argument 1..36).
    The last one also runs command 25 (held actor let go: Actor.outOfPlay 0, heldActor -1).
    38 MESSAGEs in all: the 32-slot ring overflows at the 33rd (Stage.msgRead moves on: 6 at the end).
  * Trigger 60 TEXT DATA (armed 0, never fired, way point at y 95000 out of every bot's reach): 30 "commands" that are
    really the five message text blocks (see MESSAGE below); every opcode word in them is > 31 (a no-op) anyway.
  Trigger.fired / Stage.triggerFired: set by 21, 22, 24..59 on their own; shipped ones on frame 1.
 Actors section: spawn record 1 pitch 30.0, yaw 450.0, scriptFlag 0x5a; record 2 pitch -20.0, yaw 1350.0,
  scriptFlag 2 (bot_spawns copies the record and only replaces the position).
 Objects section (156 -> 159; copies of "valhalla\addon\Ribet", a small rivet shape, collision on):
  * 156 at (677, 39400, 2813), next to shipped way point 76: flags 8, trigger 15 (radius 1500), animPeriod 1000,
    anim "L-RING-1" (Skeleton.dat STAGE\VALHALLA\L-RING-1): plays forwards when any live actor comes within 1500,
    backwards when all leave (period 1000 gives rate exactly 1.0, the backwards test).
  * 157 at (801, 39600, 4247): flags 0x10, trigger 0, period 1000, "S-RING-1": no wait; forwards, back, again.
  * 158 at (801, 39600, 2647): flags 0x10, trigger 1 (100 s: the wait is trigger x 100 seconds), period 2000,
    "L-RING-1": MapObject.waitTime counts to 100, then plays once and holds at its end.
 Play info section: items 65 and 66 (after the 65 shipped ones), kind 34 = warp zone, linked to each other:
  65 at (3286, 38621, 3150) (over shipped way point 78, ~2500 east of the centre) warpTo 66, warpPitch -10;
  66 at (-8780, 39021, 14149) (over shipped way point 0) warpTo 65, warpPitch 15, angle 45.
  Touching 65 sends the player to 66 with nextPitch 15 x 10 (item_pickup reads the destination's warpPitch).
 Ground section:
  * fog on (Stage.fogOn = Scene.fogOn), colour (0.35, 0.40, 0.55), start 20000, end 60000 (density unchanged 0.35).
  * floor mode 2 (Stage.floorMode; floorFrame / floorClock animate in stage_advanceClocks; its collision plane is the
    level box's bottom, y -100000).
  * 3 ground layers (Stage.groundLayerCount 3, groundLayers, layerParts, pool / poolUsed = 158091 bytes):
    0: kind 0 (floor, collided), 16x16 cells of 300 at (-1599, 50000, 1047) over the centre, height scale 8 with a
       100-grey pyramid (0..800), two red pixels -> 6 cells not drawn (drawnCells 0); texScale 2000.
    1: kind 1 (ceiling, collided, normals flipped), 8x8 of 400 at (4801, 52000, 1847), bump 60 x 10.
    2: kind 2 + water 1 (not collided, water surface around the camera) 10x10 of 20000 from (-100000, 20000, -100000),
       below the whole arena (shipped water layers look like this; it is only seen through openings).

Features that could not be expressed plainly, and what was done
  * Floor mode 1/2 and ground layers need textures "<dir>/FloorAni01".."FloorAni16" and "<dir>/Ground<i>Map"
    (map_loadGroundInfoFrom -> tex_getIdByName: a missing one is a fatal "can't find texture object"). No FloorAni
    texture exists in any Data\Image*.dat, and Valhalla has no Ground<i>Map. Work-around (default; --no-tex-trick
    turns it off and then leaves floor mode 0 and no layers): the ground file's texture directory is set to
    "STAGE/valhalla/SphereFloor*". The game keys the record by the full name but checks and loads only the part before
    '*' (tex_textureFileExist and the image load strtok at "*", the material-variant syntax), so every texture the
    ground file names resolves to STAGE\VALHALLA\SPHEREFLOOR (as 32 separate texture records). Side effect: the sky sphere,
    cloud layer and side walls all show that one image too.
  * Command 26 MESSAGE: Stage.speakers and Stage.texts are never written by the game (no loader, no command), so any
    in-range speaker / text index is a fatal "invalid speaker / text in command MESSAGE". The check is
    *(int*)(stage + 0x2104fe8 + n*0x88) != 0 (and + 0x210850c + n*0x108 for the text) in 32-bit arithmetic, and
    hud_drawMessageBox draws the text from Scene.msgText[n] = the same address + 4. So the commands use u32 indices
    that wrap round to the map's own command table (Stage.commands at stage + 0xdc0f10): speaker 0x169452cf -> the
    first data command's word 0x20202020; text indices -> each block's "TXT " word, followed by four 0x41-byte lines
    (64 characters + NUL each, so the HUD's strcpy into its 256-byte line stays bounded). This relies on the Stage
    layout of scene.fields (static-asserted against the original) and on the i386 build (AxisRC.exe is PE32); verify.py
    re-checks every MESSAGE's targets. MessageSlot.speaker / unusedC / unused10 are written but never read.
    The box (hud_drawMessageBox) is drawn only while Scene.msgFade > 0, i.e. after an event line (a kill, a pickup
    notice...) fades it in; it then shows the ring's msgRead slot, which only moves on when the ring overflows.
  * Command 27: nothing reads the .scp file (ScenePath methods are empty stubs); stage_advanceScenePath runs later in
    the same frame and clears scriptMode at once (the stub answers 0). So scriptMode / scriptHoldsPlay are set for the
    rest of that one update (bullets, particles, items, objects skip it as paused) and match_drawFrame never sees
    Scene.scriptMode != 0. No data can make it last longer.
  * The player's own spawn record (actor 0) is not used by local_spawn (it takes a start point), so pitch / yaw were
    set on the bot records 1 and 2 only. MapItem.pitch is written but never read.
  * Nothing else was left out.

Checks done without the game (verify.py; it reads the file like each loader: own file position, sections skipped
by their scrambled sizes, blocks of 56 objects / 0x71c play records)
  version words of all five readers; ground: light count <= 0x400, map number == 0, layer count <= 4, rows / cols in
  the 256x256 image, layer pool <= 4,000,000, every texture the ground file names exists (after '*'); objects: count
  and type names <= 1000, animation skeletons exist; play info: starts <= 32, items <= 200, warp targets valid;
  mission: commands <= 10000, way points <= 1000, triggers <= 200, both "mismatch between total num of ..." sums,
  every trigger has a way point, trigger / path / actor indices of commands 0, 1, 2, 7, 8, 15..17, 19, 22..24 in
  range, every MESSAGE speaker / text reaching a non-zero dword of the command table with NUL-ended lines, command 27
  names terminated; actors: players <= 16, actors <= 100, player indices valid. Result: "OK: no loader check fails".
  Round trip: decode -> encode of valhalla.bfd (and of all 32 shipped maps) gives identical bytes.
  Not checked: anything at run time (the game was not run).
