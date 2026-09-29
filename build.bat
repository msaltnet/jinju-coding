@echo off
cd /d "%~dp0"
.\claat-windows-amd64.exe export .\_article\01_intro\01_intro.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\02_semiconductor\02_semiconductor.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\03_LED\03_LED.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\04_button\04_button.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\05_play_button\05_play_button.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\99_game\99_game.md
if errorlevel 1 exit /b 1
.\claat-windows-amd64.exe export .\_article\00_preparation\preparation.md
if errorlevel 1 exit /b 1
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0scripts\localize-assets.ps1"
exit /b %errorlevel%
