@echo off
rem Plays Axis in Godot (the godot branch). Add --windowed after --game-dir ... for a window instead of full screen.
rem The repository must be on the godot branch (the project files are only there).
if not exist "%~dp0project\project.godot" (
	echo The Godot project is missing - switch the repository to the godot branch: git switch godot
	pause
	exit /b 1
)
start "" "C:\Users\Alexander\Tools\godot\editor64\Godot_v4.7.2-stable_win64.exe" --path "%~dp0project" res://game.tscn -- --game-dir "C:/Users/Alexander/Desktop/Axis"
