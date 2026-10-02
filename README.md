# CS 302 Programming Assignment 2: Lists from Scratch (Snake Game)

**Name:** YOUR NAME HERE
**Course/Section:** CS 302, SECTION HERE

## Overview

This project implements two list data structures from scratch and uses one of
them to store the snake in a terminal-based Snake game:

- `ArrayList<T>`: an array-based list backed by a dynamically allocated array
  that doubles in capacity when full.
- `LinkedList<T>`: a singly linked list built from dynamically allocated `Node<T>`
  objects, with a pointer to the first node.

No C++ containers (`std::vector`, `std::list`, etc.) are used to store the snake or
to implement either list.

## Files

| File | Purpose |
|------|---------|
| `ArrayList.h`, `ArrayList.cpp` | Array-based list (template) |
| `LinkedList.h`, `LinkedList.cpp` | Singly linked list (template) |
| `Node.h`, `Node.cpp` | Node used by `LinkedList` |
| `Position.h` | `Position` struct (row, column) for one board cell |
| `SnakeGame.h`, `SnakeGame.cpp` | Snake game logic and rendering |
| `main.cpp` | Game driver (play again / exit loop) |
| `tests.cpp` | Test driver for both list implementations |
| `Makefile` | Build instructions |
| `Report.pdf` | Design reflection answers |
| `README.md` | This file |

Because `ArrayList`, `LinkedList` and `Node` are templates, each header
`#include`s its matching `.cpp` file at the bottom. These `.cpp` files are not
compiled on their own; they are compiled as part of any file that includes the
header.

## List API

Both lists provide the same interface, so they are interchangeable.

| Operation | Description |
|-----------|-------------|
| `void insert(int index, T value)` | Insert at `index` (valid range `0` to `length`) |
| `remove(int index)` | Remove the element at `index` (valid range `0` to `length - 1`) |
| `T get(int index)` | Return the element at `index` |
| `int getLength()` | Number of elements |
| `void clear()` | Remove all elements; the list can be reused afterward |

- An invalid index in `get`, `insert` or `remove` throws `std::out_of_range`.
- Both classes implement a destructor, a copy constructor and a copy-assignment
  operator that perform **deep copies**. Self-assignment is safe.
- `ArrayList` starts with a capacity of 10 (or a given initial capacity, at least 1)
  and doubles its capacity whenever it is full. It does not shrink.

## How to Build and Run

Requires a C++17 compiler (g++) and `make`.

```
make              # builds both the game and the tests
make snakegame    # builds only the game
make tests        # builds only the tests
make clean        # removes build output
```

On Windows with MinGW, use `mingw32-make` in place of `make`.

Run the game:

```
./snakegame
```

Run the list tests:

```
./run_tests
```

## Game Controls

The game is turn-based: type a letter and press **Enter** to take one step.

| Key | Action |
|-----|--------|
| `W` | Move up |
| `A` | Move left |
| `S` | Move down |
| `D` | Move right |
| `Q` | Quit |

Upper- and lower-case letters both work. Reversing directly into the snake's own
neck is ignored, so it does not count as a move.

## Game Rules and Display

The board is 20 columns by 10 rows with fixed walls.

| Symbol | Meaning |
|--------|---------|
| `#` | Wall |
| `O` | Snake head |
| `o` | Snake body |
| `*` | Food |
| (space) | Empty cell |

- The snake starts with 3 segments.
- Exactly one food item is on the board at a time, and it is never placed on the snake.
- Eating food adds 10 to the score and grows the snake by one segment.
  A new food item then appears in an unoccupied cell.
- The current score and snake length are displayed each turn.
- The game ends when the snake hits a wall, hits its own body, or the player quits.
  A game-over message and the final score are then shown.
- After a game ends, the player may start a new game (`Y`) or exit (`N`).
  Each new game starts with a freshly initialized snake.

## How the Snake Is Stored

The snake is an ordered sequence of `Position` values stored in one of the custom
lists. Index `0` is the head and the last index is the tail.

- **Normal step:** insert the new head at index 0, then remove the last element.
- **Eating food:** insert the new head at index 0 and do not remove the tail.
- **Collision detection:** loops over the list with `get(i)` to compare the next
  head position against every body segment.

The board array in `render()` is only used for drawing; it never stores the snake.

### Switching the Implementation

The list used for the snake is chosen by one type alias in `SnakeGame.h`:

```cpp
using SnakeBody = LinkedList<Position>;
// using SnakeBody = ArrayList<Position>;
```

Comment out one line and uncomment the other, then rebuild with `make`. No other
game code needs to change.

## Testing

`tests.cpp` runs the same 19 test cases on both `ArrayList<int>` and
`LinkedList<int>`:

1. Construct an empty list
2. Insert at the beginning
3. Insert in the middle
4. Insert at the end
5. Remove the first element
6. Remove a middle element
7. Remove the last element
8. Access every valid index
9. Access an invalid index (expects `std::out_of_range`)
10. Clear an empty list
11. Clear a nonempty list
12. Reuse a list after `clear()`
13. Trigger multiple array resizes
14. Copy an empty list
15. Copy a nonempty list
16. Modify the original after copying
17. Modify the copy without affecting the original
18. Assign one list to another (including chained and self-assignment)
19. Destroy a nonempty list

The program prints PASS/FAIL for every case and a final summary, and exits with a
nonzero status if any test fails.

To also check for memory errors and leaks (g++ or clang on Linux/macOS):

```
g++ -std=c++17 -g -fsanitize=address,undefined tests.cpp -o tests_asan
./tests_asan
```

## Notes

- Report answers to the design-reflection questions are in `Report.pdf`.
