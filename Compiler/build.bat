@echo off
rmdir /S /Q build
mkdir build
mkdir build
pushd build
if "%~1"=="-d" goto :debug
if "%~1"=="-r" goto :release
:debug
echo. 
echo ------------ Building debug ------------
echo. 
cl /Fe"rwc" -Zi /std:c++20 /I../include ../src/main.cpp ../src/Error.cpp ../src/Timer.cpp ../src/Files.cpp ../src/Config.cpp ../src/Frontend/Scanner.cpp ../src/Frontend/Math.cpp ../src/Frontend/Parser.cpp ../src/Frontend/Token.cpp
goto :end
:release
echo. 
echo ------------ Building release ------------
echo. 
cl /O2 /Fe"rwc" /std:c++20 /I../include ../src/main.cpp ../src/Error.cpp ../src/Timer.cpp ../src/Files.cpp ../src/Config.cpp ../src/Frontend/Scanner.cpp ../src/Frontend/Math.cpp ../src/Frontend/Parser.cpp ../src/Frontend/Token.cpp
:end
popd
