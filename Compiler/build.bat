@echo off
rmdir /S /Q build
mkdir build
mkdir build
pushd build
if "%~1"=="-d" goto :debug
if "%~1"=="-r" goto :release
:debug
cl  /Fe"rwc" -Zi ../src/main.cpp
goto :end
:release
cl  /Fe"rwc" ../src/main.cpp
:end
popd
