#!/usr/bin/env bash
# host/sdl/build.sh [windows] [install]: AxisSDL - the game as a program of its own (host/sdl/main.cpp) - linked with the 64-bit
# game library (standalone/build64.sh <target> first) and SDL3, built with zig:
#   windows - build/sdl/windows/AxisSDL.exe and SDL3.dll (SDL3's MinGW development files in SDL3_MINGW, default
#             Tools/sdl3/SDL3-3.4.20/x86_64-w64-mingw32);
#   linux   - build/sdl/linux/AxisSDL (x86-64, glibc 2.28+) and libSDL3.so.0 beside it (found by its rpath $ORIGIN) -
#             SDL3 built for Linux in SDL3_LINUX (default Tools/sdl3/linux-x86_64-glibc228: lib/ and include/);
#   macos   - on a Mac, with Apple's clang (not zig): build/sdl/macos/AxisSDL.app, universal (arm64 + x86_64, macOS
#             11+), SDL3 in its Frameworks, ad-hoc signed, and AxisSDL-macos.zip of it - SDL3 built universal in SDL3_MACOS (a prefix:
#             include/, lib/); the library from standalone/build64.sh macos (both processors' archives joined by lipo)
set -e
cd "$(dirname "$0")/../.."
TARGET=${1:-windows}
if [ "$TARGET" = macos ]; then
	SDL=${SDL3_MACOS:?SDL3_MACOS: SDL3 built universal (a prefix with include/ and lib/)}
	OUT=build/sdl/macos; mkdir -p $OUT/obj
	lipo -create build/libaxis64_macos-arm64.a build/libaxis64_macos-x86_64.a -output $OUT/obj/libaxis64.a
	ARCH="-arch arm64 -arch x86_64 -mmacosx-version-min=11.0"
	FLAGS="$ARCH -O2 -g -Wall -Wno-unused-function -I$SDL/include"
	clang -c $FLAGS -o $OUT/obj/gl_play.o host/sdl/gl_play.c
	clang++ -c -std=c++17 $FLAGS -o $OUT/obj/axis_audio.o host/sdl/axis_audio.cpp
	clang++ -c -std=c++17 $FLAGS -Wno-unused-variable -o $OUT/obj/main.o host/sdl/main.cpp
	clang++ -c -std=c++17 $FLAGS -o $OUT/obj/launcher.o host/sdl/launcher.cpp
	# (the app: AxisSDL.app - the program in Contents/MacOS, SDL3 in Contents/Frameworks, ad-hoc signed; the game folder
	# is the one holding the app, or the one above it)
	APP=$OUT/AxisSDL.app
	rm -rf $APP
	mkdir -p $APP/Contents/MacOS $APP/Contents/Frameworks
	clang++ $ARCH -o $APP/Contents/MacOS/AxisSDL $OUT/obj/main.o $OUT/obj/launcher.o $OUT/obj/gl_play.o $OUT/obj/axis_audio.o $OUT/obj/libaxis64.a -L$SDL/lib -lSDL3 -Wl,-rpath,@executable_path/../Frameworks
	cp -L $SDL/lib/libSDL3.0.dylib $APP/Contents/Frameworks/
	cat > $APP/Contents/Info.plist <<'PLIST'
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>CFBundleExecutable</key><string>AxisSDL</string>
	<key>CFBundleIdentifier</key><string>net.axisport.axissdl</string>
	<key>CFBundleName</key><string>Axis</string>
	<key>CFBundleDisplayName</key><string>Axis</string>
	<key>CFBundlePackageType</key><string>APPL</string>
	<key>CFBundleShortVersionString</key><string>1.0</string>
	<key>CFBundleVersion</key><string>1</string>
	<key>LSMinimumSystemVersion</key><string>11.0</string>
	<key>NSHighResolutionCapable</key><true/>
</dict>
</plist>
PLIST
	codesign --force --sign - $APP/Contents/Frameworks/libSDL3.0.dylib
	codesign --force --sign - $APP
	codesign --verify --verbose $APP
	lipo -info $APP/Contents/MacOS/AxisSDL
	otool -L $APP/Contents/MacOS/AxisSDL
	(cd $OUT && rm -f AxisSDL-macos.zip && ditto -c -k --keepParent AxisSDL.app AxisSDL-macos.zip)
	exit
fi
case "$TARGET" in
windows)
	T=x86_64-windows-gnu
	SDL=${SDL3_MINGW:-C:/Users/Alexander/Tools/sdl3/SDL3-3.4.20/x86_64-w64-mingw32}
	LIB=build/libaxis64_windows.a
	OUT=build/sdl/windows; EXE=AxisSDL.exe; SDLLIB=$SDL/lib/libSDL3.dll.a
	SYSLIBS="-lws2_32 -lwinmm -lole32 -loleaut32 -ladvapi32 -Wl,--subsystem,windows"
	;;
linux)
	T=x86_64-linux-gnu.2.28   # (SDL3 built against glibc 2.28 too: zig in WSL, see README)
	SDL=${SDL3_LINUX:-C:/Users/Alexander/Tools/sdl3/linux-x86_64-glibc228}
	LIB=build/libaxis64_linux-gnu.a
	OUT=build/sdl/linux; EXE=AxisSDL; SDLLIB=$SDL/lib/libSDL3.so.0.4.20
	SYSLIBS="-lm -lpthread -ldl -Wl,-rpath,\$ORIGIN"
	;;
*) echo "unknown target $TARGET"; exit 1 ;;
esac
test -e $LIB || { echo "$LIB missing: bash standalone/build64.sh $TARGET"; exit 1; }
mkdir -p $OUT/obj
CC="python -m ziglang cc -target $T"
CXX="python -m ziglang c++ -target $T"
FLAGS="-O2 -g -Wall -Wno-unused-function -Wno-ignored-attributes -I$SDL/include"
$CC -c $FLAGS -o $OUT/obj/gl_play.o host/sdl/gl_play.c
$CXX -c -std=c++17 $FLAGS -o $OUT/obj/axis_audio.o host/sdl/axis_audio.cpp
$CXX -c -std=c++17 $FLAGS -Wno-unused-variable -o $OUT/obj/main.o host/sdl/main.cpp
$CXX -c -std=c++17 $FLAGS -o $OUT/obj/launcher.o host/sdl/launcher.cpp
$CXX -o $OUT/$EXE $OUT/obj/main.o $OUT/obj/launcher.o $OUT/obj/gl_play.o $OUT/obj/axis_audio.o $LIB $SDLLIB $SYSLIBS
[ "$TARGET" = windows ] && cp $SDL/bin/SDL3.dll $OUT/
[ "$TARGET" = linux ] && cp $SDL/lib/libSDL3.so.0.4.20 $OUT/libSDL3.so.0
ls -la $OUT
# (the replay check: host/sdl/glplay_check.cpp - gl_play against the original's own images)
$CXX -std=c++17 $FLAGS -o $OUT/glplay_check${EXE##AxisSDL} host/sdl/glplay_check.cpp $OUT/obj/gl_play.o $SDLLIB $( [ "$TARGET" = windows ] && echo -Wl,--subsystem,console )
# (install: build/sdl/<target> copied to <Axis>/AxisSDL - the game folder is the one above it)
if [ "$2" = install ] && [ "$TARGET" = windows ]; then
	mkdir -p /c/Users/Alexander/Desktop/Axis/AxisSDL
	cp $OUT/AxisSDL.exe $OUT/SDL3.dll /c/Users/Alexander/Desktop/Axis/AxisSDL/
	echo "installed to /c/Users/Alexander/Desktop/Axis/AxisSDL"
fi
