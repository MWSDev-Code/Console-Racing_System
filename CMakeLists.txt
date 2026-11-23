cmake_minimum_required(VERSION 3.28)
project(ConsoleRacingSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3 COMPONENTS Graphics Audio QUIET)
if(NOT SFML_FOUND)
  include(FetchContent)
  set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
  set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "" FORCE)
  FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW TRUE
  )
  FetchContent_MakeAvailable(SFML)
endif()

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
