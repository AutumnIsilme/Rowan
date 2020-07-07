@echo off
if "%~1"=="-d" call build.bat -d
if "%~1"=="-r" call build.bat -r
echo. 
echo ------------ Finished build ------------
echo.
"build/rwc.exe"
