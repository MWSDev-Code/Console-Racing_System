@echo off
setlocal
cd /d "%~dp0" || exit /b 1

if not defined MSYS2_ROOT set "MSYS2_ROOT=C:\msys64"
set "UCRT=%MSYS2_ROOT%\ucrt64"
set "PATH=%UCRT%\bin;%PATH%"

if not exist "%UCRT%\bin\g++.exe" goto missing
if not exist "%UCRT%\include\SFML\Graphics.hpp" goto missing

if not exist build mkdir build
"%UCRT%\bin\g++.exe" -std=c++17 -Iinclude -I"%UCRT%\include" ^
  src\main.cpp src\projectmenu.cpp src\CarSelection.cpp src\Car.cpp src\Game.cpp src\checkpoint.cpp ^
  -L"%UCRT%\lib" -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system ^
  -o build\game.exe
if errorlevel 1 exit /b 1

if /i "%~1"=="--build-only" exit /b 0
build\game.exe
exit /b %ERRORLEVEL%

:missing
echo Install GCC and SFML from the MSYS2 UCRT64 shell using the commands in README.md.
echo If you installed MSYS2 outside C:\msys64, set MSYS2_ROOT to the install folder.
exit /b 1
