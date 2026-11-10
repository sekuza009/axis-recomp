"""package.py [windows] [linux]: AxisSDL's zips for sharing - build/sdl/dist/AxisSDL-windows-x64.zip and
AxisSDL-linux-x64.zip, each a folder AxisSDL/ with the program, SDL3, a README and the third-party licences (SDL3: zlib;
dr_mp3: public domain / MIT-0; FFmpeg's indeo3 decoder, built into the program: LGPL 2.1+ - its text, and where the
source is). The programs from host/sdl/build.sh; the Linux ones stripped of their debug data (GNU strip in WSL). No game files: the user's
own copy of Axis is needed."""
import os, subprocess, sys, tarfile, zipfile

R = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..'))
SDL_SRC = os.environ.get('SDL3_SOURCE', 'C:/Users/Alexander/Tools/sdl3/SDL3-3.4.20.tar.gz')
DIST = os.path.join(R, 'build', 'sdl', 'dist')
SOURCE_URL = 'https://github.com/sekuza009/axis-recomp'

README = """AxisSDL - Axis (2000), the original game with its fixes, as a program of its own
=================================================================================

This is the portable build of the Axis recompilation: the original game's code, rebuilt, with fixes (widescreen,
HUD, sharp text, mouse, network) - run without the original program, on {system}.
It needs YOUR OWN COPY OF AXIS: no game files are included.

Installing
----------
Put this AxisSDL folder inside your Axis folder (the one that holds initdata, Data, Map, Sound, Music and
AxisPlay.exe), so that you have e.g.  Axis/AxisSDL/{exe}
(or put the files straight into the Axis folder). Then run {exe}.
Another place: start it with  --game-dir <your Axis folder>

The launcher (AxisPlay's) comes up first - its pictures, sounds and texts are read from your AxisPlay.exe and
Launcher folder. Play Game starts the game.

Options:  --windowed (a window instead of the whole screen)  --novsync  --play (no launcher)
          --game-dir <folder>

Saves and settings
------------------
{saves}

Multiplayer
-----------
The same network as the original game with the axisnet fixes, AxisRC.exe and the other builds: they can play
together (Create Arena to host; others join with DIRECT IP, or SEARCH TCP on a local network).
{notes}
Third-party software
--------------------
- SDL3 (https://libsdl.org) - zlib licence: licenses/SDL3-LICENSE.txt
- dr_mp3 (https://github.com/mackron/dr_libs) - public domain / MIT No Attribution: licenses/dr_mp3-LICENSE.txt
- FFmpeg's Indeo 3 decoder (https://ffmpeg.org), unmodified, built into the program - LGPL 2.1 or later:
  licenses/FFmpeg-COPYING.LGPLv2.1.txt. This program's complete source, the decoder's included, so that it can be
  rebuilt with a changed decoder: {source}
"""

SYSTEMS = {
    'windows': dict(system='Windows (64-bit)', exe='AxisSDL.exe',
                    files=[('build/sdl/windows/AxisSDL.exe', 'AxisSDL.exe'), ('build/sdl/windows/SDL3.dll', 'SDL3.dll')],
                    saves='In the Axis folder, as the original game: Save, initdata\\axis.cfg, ...; settings in the registry\n'
                          '(HKEY_CURRENT_USER\\SOFTWARE\\AxisArena), shared with the original game.',
                    notes='\nThe first time it hosts a game, Windows may ask whether AxisSDL may use the network: allow it for\n'
                          'others to join you.\n',
                    zip='AxisSDL-windows-x64.zip'),
    'linux': dict(system='Linux (x86-64; glibc 2.27 or newer - most distributions since 2018, SteamOS)', exe='AxisSDL',
                  files=[('build/sdl/linux/AxisSDL', 'AxisSDL'), ('build/sdl/linux/libSDL3.so.0', 'libSDL3.so.0')],
                  saves='Your Axis folder is only read. Everything the game writes - saves, axis.cfg, replays - goes to\n'
                        '~/.local/share/axis (or $AXIS_USER_DIR), over the game folder: saves already in the game folder are\n'
                        'read from there until saved again. The settings: ~/.config/axis/registry.txt.',
                  notes='\nNeeds OpenGL (any current graphics driver) and X11 or Wayland. Message boxes look best with zenity\n'
                        'or kdialog installed. Run it from a terminal to see its messages.\n',
                  zip='AxisSDL-linux-x64.zip'),
}


def wsl_path(p):
    p = os.path.abspath(p).replace(os.sep, '/')
    return '/mnt/' + p[0].lower() + p[2:]


def strip(src, dst):
    """a Linux program or library without its debug data - GNU strip, in WSL's Ubuntu (WSL_DISTRO; zig's objcopy cannot
    yet); anything else, or when that fails, copied as it is"""
    import shutil
    shutil.copyfile(src, dst)
    if open(src, 'rb').read(4) != bytes([0x7f]) + b'ELF':
        return False
    r = subprocess.run(['wsl.exe', '-d', os.environ.get('WSL_DISTRO', 'Ubuntu-24.04'), '-u', 'root', '--', 'strip', '--strip-debug',
                        wsl_path(dst)], capture_output=True, env=dict(os.environ, MSYS_NO_PATHCONV='1'))
    return r.returncode == 0 and os.path.getsize(dst) < os.path.getsize(src)


def package(name):
    s = SYSTEMS[name]
    os.makedirs(DIST, exist_ok=True)
    out = os.path.join(DIST, s['zip'])
    tmp = os.path.join(DIST, 'tmp_' + name)
    os.makedirs(tmp, exist_ok=True)
    with tarfile.open(SDL_SRC) as t:
        sdl_licence = t.extractfile('SDL3-3.4.20/LICENSE.txt').read()
    drmp3 = open(os.path.join(R, 'third_party', 'dr_libs', 'dr_mp3.h'), encoding='utf-8').read()
    drmp3_licence = drmp3[drmp3.index('This software is available as a choice'):].strip().rstrip('*/').strip() + '\n'
    lgpl = open(os.path.join(R, 'third_party', 'ffmpeg', 'COPYING.LGPLv2.1'), 'rb').read()
    readme = README.format(system=s['system'], exe=s['exe'], saves=s['saves'], notes=s['notes'], source=SOURCE_URL)
    if name == 'windows':
        readme = readme.replace('\n', '\r\n')
    with zipfile.ZipFile(out, 'w', zipfile.ZIP_DEFLATED, compresslevel=9) as z:
        for src, arc in s['files']:
            p = os.path.join(R, src)
            if not os.path.exists(p):
                sys.exit('%s missing: bash host/sdl/build.sh %s' % (src, name))
            tp = os.path.join(tmp, arc)
            stripped = strip(p, tp)
            info = zipfile.ZipInfo('AxisSDL/' + arc)
            info.compress_type = zipfile.ZIP_DEFLATED
            info.external_attr = (0o100755 << 16) if (name == 'linux' and arc == 'AxisSDL') else (0o100644 << 16)
            info.create_system = 3   # (Unix: the permissions kept by unzip)
            z.writestr(info, open(tp, 'rb').read())
            print('  %-14s %9d bytes%s' % (arc, os.path.getsize(tp), ' (stripped)' if stripped else ''))
        for arc, data in [('README.txt', readme.encode('utf-8')), ('licenses/SDL3-LICENSE.txt', sdl_licence),
                          ('licenses/dr_mp3-LICENSE.txt', drmp3_licence.encode('utf-8')),
                          ('licenses/FFmpeg-COPYING.LGPLv2.1.txt', lgpl)]:
            info = zipfile.ZipInfo('AxisSDL/' + arc)
            info.compress_type = zipfile.ZIP_DEFLATED
            info.external_attr = 0o100644 << 16
            info.create_system = 3
            z.writestr(info, data)
    for f in os.listdir(tmp):
        os.remove(os.path.join(tmp, f))
    os.rmdir(tmp)
    print('%s: %d bytes' % (out, os.path.getsize(out)))


for n in (sys.argv[1:] or ['windows', 'linux']):
    package(n)
