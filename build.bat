@echo off
rem Builds recomp.dll (rebuilt game functions + comparison harness) and inject.exe, 32-bit, with Zig.
cd /d "%~dp0"
python -m ziglang cc -target x86-windows-gnu -shared -O2 -Wno-unused-label -o recomp.dll recomp.c || exit /b 1
python -m ziglang cc -target x86-windows-gnu -O2 -o inject.exe inject.c || exit /b 1
