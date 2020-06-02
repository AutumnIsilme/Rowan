@echo off
call build.bat
echo. 
echo ------------ Finished build ------------
echo.
pushd build
rwc.exe
popd
