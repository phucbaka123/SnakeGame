# CS 302 Programming Assignment 2
Lists from Scratch: Building a Snake Game[cite: 5]

## Overview
This project implements a terminal-based Snake game using two custom-built data structures[cite: 5]. I built an array-based list (`ArrayList<T>`) and a singly linked list (`LinkedList<T>`) from scratch, without using any existing C++ containers[cite: 5]. The game logic uses a type alias so it can run interchangeably with either list implementation[cite: 5].

## Game Features
* Terminal-based 2D board with fixed boundaries[cite: 5].
* The snake starts with at least three segments[cite: 5].
* Exactly one food item spawns at a time in an unoccupied location[cite: 5].
* Collision detection ends the game if the snake hits a wall or its own body[cite: 5].
* Displays the current score and the snake's length[cite: 5].
* Option to start a new game or exit after Game Over[cite: 5].

## Controls
The game uses turn-based controls[cite: 5]:
* W = up[cite: 5]
* A = left[cite: 5]
* S = down[cite: 5]
* D = right[cite: 5]
* Q = quit[cite: 5]

## Included Files
This project includes the following 14 files[cite: 5]:
* `ArrayList.h` and `ArrayList.cpp`[cite: 5]
* `LinkedList.h` and `LinkedList.cpp`[cite: 5]
* `Node.h` and `Node.cpp`[cite: 5]
* `Position.h`[cite: 5]
* `SnakeGame.h` and `SnakeGame.cpp`[cite: 5]
* `main.cpp` (Main game driver)[cite: 5]
* `tests.cpp` (Separate test driver for list implementations)[cite: 5]
* `Makefile`[cite: 5]
* `README.md`[cite: 5]
* `Report.pdf`[cite: 5]

## How to Compile and Run
Use the included `Makefile` to compile the project[cite: 5]. 

To compile and run the main game:
1. Type `make` or `make snakegame` in the terminal.
2. Run `./snakegame`.

To compile and run the test cases for the list implementations:
1. Type `make tests` in the terminal.
2. Run `./run_tests`.