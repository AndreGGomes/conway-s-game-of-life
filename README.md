# Conway's Game of Life

An implementation of Conway's Game of Life written in C, using [SDL3](https://github.com/libsdl-org/SDL), for learning purposes.

## Getting Started

These instructions will give you a copy of the project up and running on
your local machine.

### Prerequisites

Necessary tools to build the game:
- [Git](https://git-scm.com/downloads)
- [Cmake](https://cmake.org/download/)

### Building

Clone the repository:

    git clone https://github.com/AndreGGomes/conway-s-game-of-life.git

Enter the project directory and create a directory called "build":

    cd conway-s-game-of-life; mkdir build; cd build

Run the following CMake commands inside the "build" directory (with CMake installed):

    cmake ..; cmake --build .
    

Now you will have an executable file called "conway_game_of_life" in your build directory.

## Playing the game

Space: starts/pauses the game.

X: kills every alive cell.

Right_Click: changes the status of the cell.

R: Randomizes the board.

G: Starts a glider in the board.
