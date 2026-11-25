#!/bin/bash
set -e

cd "$(dirname "$0")"

if ! command -v brew >/dev/null 2>&1; then
  export PATH="/opt/homebrew/bin:/usr/local/bin:$PATH"
fi

if ! command -v brew >/dev/null 2>&1; then
  echo "Install Homebrew from https://brew.sh/ and run this launcher again." >&2
  exit 1
fi

if ! xcode-select -p >/dev/null 2>&1; then
  echo "Install the Command Line Tools with xcode-select --install." >&2
  exit 1
fi

sfml_prefix="$(brew --prefix sfml)"
if [ ! -f "$sfml_prefix/include/SFML/Graphics.hpp" ]; then
  echo "Install SFML with brew install sfml." >&2
  exit 1
fi

mkdir -p build
clang++ -std=c++17 -Iinclude -I"$sfml_prefix/include" src/*.cpp \
  -L"$sfml_prefix/lib" -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system \
  -o build/game

if [ "${1:-}" != "--build-only" ]; then
  exec ./build/game
fi
