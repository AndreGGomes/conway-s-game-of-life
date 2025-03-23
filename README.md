# Conway's Game of Life

An implementation of Conway's Game of Life written in C, using [SDL3](https://github.com/libsdl-org/SDL), for learning purposes.

## Getting Started

These instructions will give you a copy of the project up and running on
your local machine for development and testing purposes. See deployment
for notes on deploying the project on a live system.

### Prerequisites

Necessary tools to build the game
- [Git](https://git-scm.com/downloads)
- [Cmake](https://cmake.org/download/)

### Building

Clone the repo with:

    git clone https://github.com/AndreGGomes/conway-s-game-of-life.git

Inside the repo's directory run:

    mkdir build; cd build

With Cmake installed run:

    cmake ..; cmake --build .

## Playing the game

Space: starts/pauses the game

X: kills every alive cell

Right_Click: changes the status of the cell

R: Randomizes the board

G: Starts a glider in the board
