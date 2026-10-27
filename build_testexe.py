"""Build recomp\\build\\AxisGL.exe: the normal AxisGL patch chain (patches\\build_exes.py), but embedding
axisnet_recomp.dll (= axisnet.c + "load recomp.dll from the game folder if present").
The installed game files are not touched."""
import os, shutil, subprocess, sys, tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
GAME = os.path.dirname(HERE)
PATCHES = os.path.join(GAME, "patches")
STEPS = ["cursorfix.py", "hudfix.py", "mousefix.py", "unlockfix.py", "dinputfix.py"]

def run(script, *args):
    r = subprocess.run([sys.executable, os.path.join(PATCHES, script), *args], capture_output=True, text=True)
    if r.returncode:
        sys.exit(f"{script} failed:\n{r.stdout}{r.stderr}")
    print("  %s: %s" % (script, (r.stdout.strip().splitlines() or [""])[-1]))

os.makedirs(os.path.join(HERE, "build"), exist_ok=True)
with tempfile.TemporaryDirectory() as tmp:
    cur = os.path.join(tmp, "0.exe")
    run("embed_axisnet.py", os.path.join(GAME, "AxisGL.exe.nocd-wide"), os.path.join(HERE, "axisnet_recomp.dll"), cur)
    for i, step in enumerate(STEPS, 1):
        nxt = os.path.join(tmp, "%d.exe" % i)
        run(step, cur, nxt)
        cur = nxt
    shutil.copyfile(cur, os.path.join(HERE, "build", "AxisGL.exe"))
print("built recomp\\build\\AxisGL.exe")
