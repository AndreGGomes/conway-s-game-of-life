all: build run

build:
	gcc ./src/main.c -o ./out/Game_of_Life.exe -lSDL3
	
run:
	./out/Game_of_Life.exe