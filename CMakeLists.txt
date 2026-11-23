cmake_minimum_required(VERSION 3.28)
project(ConsoleRacingSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio)

add_executable(game
  src/main.cpp
  src/projectmenu.cpp
  src/CarSelection.cpp
  src/Car.cpp
  src/Game.cpp
  src/checkpoint.cpp
)

target_include_directories(game PRIVATE include)
target_link_libraries(game PRIVATE SFML::Graphics SFML::Audio)

file(COPY assets data DESTINATION "${CMAKE_BINARY_DIR}")
