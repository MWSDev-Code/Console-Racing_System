# Console Racing System

A local two-player 2D racing game written in C++17 with SFML 3. Two cars start side by side. Each driver must pass four checkpoints in order and cross the finish line to complete a lap. The first driver to complete three laps wins.

## Build and run on macOS

The project uses Clang and the SFML headers and libraries installed through Homebrew. If these tools are missing, install the Xcode Command Line Tools with `xcode-select --install` and install SFML with `brew install sfml`.

Open a terminal in the project folder, where `src/`, `include/`, `assets/`, and `data/` are located. Run these commands.

```sh
SFML_PREFIX="$(brew --prefix sfml)"
clang++ -std=c++17 -Iinclude -I"$SFML_PREFIX/include" src/*.cpp \
  -L"$SFML_PREFIX/lib" -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system \
  -o game
./game
```

The compiler builds the C++ files in `src/`, finds the project headers in `include/`, links the SFML libraries, and writes the executable to `game`. Launch it from the project folder so it can find the assets and score file.

In VS Code on Apple Silicon, run **Build Turbo Track** from **Terminal → Run Build Task**. With the Microsoft C/C++ extension installed, select **Debug Turbo Track** in **Run and Debug** and press **F5**. The included VS Code task uses the Apple Silicon Homebrew path `/opt/homebrew/opt/sfml`.

## How to play

1. Click **Select Car** and choose Player 1’s car. Use **Previous**, **Next**, or a car thumbnail to browse, then click **Select Car** to confirm. Player 2 is assigned the next car in the list.
2. Click **Start Race**. Pass all four checkpoints in order, then cross the start/finish line. Repeat for three laps.
3. Use **Show Records** from the main menu to see the saved times. Use **Sound On/Off** to control the menu music.

| Action | Player 1 | Player 2 |
| --- | --- | --- |
| Accelerate | W | ↑ |
| Brake | S | ↓ |
| Steer left | A | ← |
| Steer right | D | → |

## Race records

The winning time is saved in [data/scores.txt](data/scores.txt) after each completed race. The times are in seconds with two decimal places.

| Record | Meaning |
| --- | --- |
| Highest | Slowest winning time |
| Lowest | Fastest winning time |
| Current | Most recent winning time |

The first completed race sets all three values. Later races always update **Current** and update **Highest** when the time is slower or **Lowest** when it is faster. An unfinished race leaves the records as they were.

## C++ concepts used

| Concept | How we used it |
| --- | --- |
| Variables and constants | Store car speed, elapsed time, checkpoint progress, and the number of laps required to win. |
| Arithmetic and comparisons | Calculate movement from speed and elapsed frame time, check whether a car has completed three laps, and compare finish times. |
| `if` and `else` | Handle acceleration, braking, and coasting. Initialize the first race record and check later times against the highest and lowest values. |
| `while` and `for` loops | Keep the menu and race running, process window events, and go through the cars and checkpoints. |
| One-dimensional arrays | Store the three records in one array. The car-selection screen and race also use fixed-size arrays for car choices and checkpoints. |
| Functions and parameters | Split the work into functions for loading cars, updating movement, checking checkpoints, and saving records. |
| Classes and structs | Use `Car` for a car’s sprite and movement, `Checkpoint` for checkpoint bounds, and `CarControls` to group each player’s keys. |
| File handling | Use `ifstream` to read the records and `ofstream` to write them to the text file. |
| Headers and source files | Declare shared types and functions in headers and organize the implementation by feature. |

## What SFML does

- **Graphics** draws the track, cars, menu, and race information. The game reads the track mask image to detect when a car is off the road and limit its speed.
- **Window and input** open the game windows, handle mouse clicks in the menus, and read the two players’ driving keys.
- **System** provides clocks for measuring frame time and the race timer.
- **Audio** plays and pauses the menu music.

## Project files

| Path | Purpose |
| --- | --- |
| [src/main.cpp](src/main.cpp) | Starts the main menu. |
| [src/projectmenu.cpp](src/projectmenu.cpp) | Handles the main menu, sound toggle, and records screen. |
| [src/CarSelection.cpp](src/CarSelection.cpp) | Displays the four car choices and confirms Player 1’s selection. |
| [src/Game.cpp](src/Game.cpp) | Runs the race, sets the starting grid, tracks laps, and determines the winner. |
| [src/Car.cpp](src/Car.cpp) and [include/Car.h](include/Car.h) | Load and position car sprites, define speed settings, and update driving and off-track behavior. |
| [src/checkpoint.cpp](src/checkpoint.cpp) | Checks whether a car has entered a checkpoint area. |
| [include/Scores.h](include/Scores.h) | Reads, updates, and saves the score array. |
| [assets/](assets/) | Contains the car and track artwork, interface images, fonts, and music. |
| [data/scores.txt](data/scores.txt) | Stores the highest, lowest, and most recent winning times. |
| [.vscode/](.vscode/) | Contains the build task and debugger configuration. |
