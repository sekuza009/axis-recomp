// launcher.h: the launcher - AxisPlay.exe rewritten (launcher.cpp), as the Godot build's (godot branch,
// project/launcher.gd), for AxisSDL on Windows, Linux and macOS.
#pragma once
#include <string>

// the launcher shown until Play Game (true: start the game) or Quit (false). gameDir: the game folder, with a '/'
bool launcher_run(const std::string &gameDir);
