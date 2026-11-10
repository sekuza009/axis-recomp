@echo off
rem As "Play Axis (Godot).bat", writing what the mouse and the sound did to logs\input.txt and logs\audio.txt.
if not exist "%~dp0project\project.godot" (
	echo The Godot project is missing - switch the repository to the godot branch: git switch godot
	pause
	exit /b 1
)
if not exist "%~dp0logs" mkdir "%~dp0logs"
start "" "C:\Users\Alexander\Tools\godot\editor64\Godot_v4.7.2-stable_win64.exe" --path "%~dp0project" res://game.tscn -- --game-dir "C:/Users/Alexander/Desktop/Axis" --input-log "%~dp0logs\input.txt" --audio-log "%~dp0logs\audio.txt"
