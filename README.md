# Console Racing System

A local two-player racing game built with C++17 and SFML 3. Each player starts with three lives. Pass four checkpoints in order and cross the start line to complete a lap. The first player to finish three laps wins. Leaving the road costs a life and returns the car to its last safe position. The cars cannot pass through the track edge or overlap.

## Requirements

- Windows 10 or 11, 64-bit
- Visual Studio 2022 or newer with **Desktop development with C++**, MSVC, and a Windows SDK
- CMake 3.28 or newer
- Git for Windows
- vcpkg, used to install SFML 3 and its libraries

The first setup needs an internet connection so Git can clone the repositories and vcpkg can download SFML and its source dependencies. The build uses the vcpkg baseline pinned in `vcpkg.json` and installs only SFML's graphics and audio features.

## Windows setup and run

Use **Developer PowerShell for Visual Studio** with Git for Windows available on `PATH`. If `git` or `cmake` is not recognized, the following adds them for the Visual Studio 18 installation used to verify this project (run it before the setup commands):

```powershell
$env:Path = "C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin;C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\TeamFoundation\Team Explorer\Git\cmd;$env:Path"
```

Open PowerShell. These commands work even if PowerShell starts in `C:\Windows\System32`; they create a source folder under your home directory, clone both repositories, install vcpkg, build, and launch the game:

```powershell
$sourceFolder = Join-Path $HOME "source\repos"
$repoFolder = Join-Path $sourceFolder "Console-Racing_System"
$vcpkgRoot = Join-Path $HOME "source\vcpkg"

New-Item -ItemType Directory -Force $sourceFolder | Out-Null
git clone https://github.com/MWSDev-Code/Console-Racing_System.git $repoFolder
git clone https://github.com/microsoft/vcpkg.git $vcpkgRoot
& "$vcpkgRoot\bootstrap-vcpkg.bat" -disableMetrics

Set-Location $repoFolder
cmake -S . -B build `
  -DCMAKE_TOOLCHAIN_FILE="$vcpkgRoot\scripts\buildsystems\vcpkg.cmake" `
  -DVCPKG_TARGET_TRIPLET=x64-windows
cmake --build build --config Release
.\build\Release\game.exe
```

If the repository is already cloned, do not repeat the two `git clone` commands. Set `$repoFolder` to the existing clone's folder, then run the vcpkg bootstrap (if needed), configure, build, and launch commands. If CMake says the current source directory does not contain `CMakeLists.txt`, PowerShell is in the wrong folder; check it with `Get-Location`, then run `Set-Location $repoFolder`.

To rebuild after cloning, run the CMake configure and build commands from the repository folder. Run the game from that folder so its relative `assets` and `data` paths resolve. Race times are saved to `data/scores.txt` in the folder where the game was launched.

## Limitations

- The first vcpkg setup and CMake configure require internet access and can take several minutes while SFML and its dependencies are built.
- The game is local two-player only; it has no online play.
- Launch the executable with the repository folder as the working directory so the game can find its assets and score file.

## macOS

Install CMake and SFML 3 with Homebrew, then run these commands from the repository folder:

```sh
brew install cmake sfml
cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix sfml)"
cmake --build build --config Release
./build/game
```

## Linux

Install CMake 3.28 or newer, a C++17 compiler, and SFML 3 development libraries from your distribution. Then run:

```sh
cmake -S . -B build
cmake --build build --config Release
./build/game
```

## How to play

1. Choose **Select Car** to pick Player 1's car. Player 2 uses the next car in the list.
2. Choose **Start Race** to begin.
3. Pass the four checkpoints in order, then cross the finish line. Complete three laps to win.
4. Stay on the road. Leaving the track costs a life and returns the car to its last safe position.

| Action | Player 1 | Player 2 |
| --- | --- | --- |
| Accelerate | W | Up arrow |
| Brake | S | Down arrow |
| Steer left | A | Left arrow |
| Steer right | D | Right arrow |

## Course concepts

The game logic uses C++ fundamentals from the Programming Fundamentals course outline: variables, arithmetic, conditions, loops, fixed-size arrays, functions, and basic text-file input/output. SFML supplies the window, graphics, keyboard input, and sound.

## Project files

| Path | Purpose |
| --- | --- |
| `CMakeLists.txt` | Configures and builds the game with CMake. |
| `vcpkg.json` | Pins the vcpkg registry and lists SFML as the only project dependency. |
| `src/main.cpp` | Starts the main menu. |
| `src/projectmenu.cpp` | Displays the main menu, sound control, and records. |
| `src/CarSelection.cpp` | Displays and confirms car choices. |
| `src/Car.cpp` | Loads cars and handles movement, track limits, and lives. |
| `src/Game.cpp` | Runs the race, tracks checkpoints and laps, and shows the result. |
| `include/Scores.h` | Reads and writes race times. |
| `assets/` | Contains the track, cars, fonts, menu images, and music. |
| `data/scores.txt` | Stores race times. |
