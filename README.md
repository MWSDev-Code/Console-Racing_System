# Console Racing System

A two-player racing game built with C++17 and SFML 3. Drive around the track, pass each checkpoint in order, and cross the start line to finish a lap. The first player to complete three laps wins. Each player starts with three lives. Leaving the road costs one life and returns the car to the last safe position. The race ends when a player runs out of lives.

## Build with CMake

The project needs CMake 3.28 or newer and Git. CMake uses an installed SFML 3 when available. Otherwise, it downloads and builds SFML 3.0.2 automatically.

### Windows

Open a Developer PowerShell in this folder and run:

```powershell
cmake -S . -B build
cmake --build build --config Release
build\Release\game.exe
```

### macOS with Homebrew

```sh
brew install cmake sfml
cmake -S . -B build -DCMAKE_PREFIX_PATH="$(brew --prefix sfml)"
cmake --build build --config Release
./build/game
```

### Linux

Install CMake and SFML 3 development packages from your distribution, then run:

```sh
cmake -S . -B build
cmake --build build --config Release
./build/game
```

Run the game from the build folder so it can find the copied `assets` and `data` folders. Race records are saved in `build/data/scores.txt`.

## How to play

1. Choose **Select Car** to pick Player 1's car. Player 2 uses the next car in the list.
2. Choose **Start Race** to begin.
3. Pass the four checkpoints in order, then cross the finish line. Complete three laps to win.
4. Stay on the road. Each player has three lives; leaving the track costs a life and puts the car back at its last safe position.

| Action | Player 1 | Player 2 |
| --- | --- | --- |
| Accelerate | W | Up arrow |
| Brake | S | Down arrow |
| Steer left | A | Left arrow |
| Steer right | D | Right arrow |

The cars stop before crossing the track boundary and are moved back if their paths would overlap. A separate results window announces the winner.

## Course concepts

The code uses the C++ fundamentals in the Programming Fundamentals course outline: variables, arithmetic, conditions, loops, fixed-size arrays, functions, and basic text-file input/output. SFML provides the window, graphics, keyboard input, and sound used by the game.

## Project files

| Path | Purpose |
| --- | --- |
| `CMakeLists.txt` | Builds the game with CMake and links SFML. |
| `vcpkg.json` | Lists SFML for Windows dependency setup. |
| `src/main.cpp` | Starts the main menu. |
| `src/projectmenu.cpp` | Displays the main menu, music control, and race records. |
| `src/CarSelection.cpp` | Displays and confirms car choices. |
| `src/Car.cpp` | Loads cars and handles movement, track limits, and lives. |
| `src/Game.cpp` | Runs the race, tracks checkpoints and laps, and shows the result. |
| `include/Scores.h` | Reads and writes race times. |
| `assets/` | Holds the track, cars, fonts, menu images, and music. |
| `data/scores.txt` | Stores race times. |
