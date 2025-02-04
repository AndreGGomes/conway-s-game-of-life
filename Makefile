all: build run

build:
	gcc ./src/main.c -o ./out/sdl_project.exe -lSDL3
	
run:
	./out/sdl_project.exe