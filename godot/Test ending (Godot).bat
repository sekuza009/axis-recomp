@echo off
rem Plays Axis in Godot and, about 5 seconds after the title screen, starts the ending exactly as winning the
rem campaign's last mission does (the ending movie, then the game closes). Your profiles and progress are not
rem touched. Esc skips the movie.
if not exist "%~dp0project\project.godot" (
	echo The Godot project is missing - switch the repository to the godot branch: git switch godot
	pause
	exit /b 1
)
set AXIS_TEST_ENDING=600
start "" "C:\Users\Alexander\Tools\godot\editor64\Godot_v4.7.2-stable_win64.exe" --path "%~dp0project" res://game.tscn -- --game-dir "C:/Users/Alexander/Desktop/Axis"
