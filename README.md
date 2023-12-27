# 2d-game-engine-course
2D Game Engine with C++ and Lua from the pikuma.com course

# Libraries and dependencies

## How to compile cpp file
g++ Main.cpp -o Main

## Compile with c++ 17
g++ -Wall -std=c++17  Main.cpp -o Main

## Execute Main file
./Main

## Link implementation of libraries
g++ -Wall -std=c++17  Main.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -llua -o Main

# Build, run and clean with Makefile
make build
make run
make build