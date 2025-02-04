#define SDL_MAIN_USE_CALLBACKS
#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#define WINDOW_WIDHT 900
#define WINDOW_HEIGHT 800
#define CELL_SIZE 10

Uint32 COLOR_WHITE = 0xffffffff;

SDL_Window* window;
SDL_Renderer* renderer;

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
   if(event->type == SDL_EVENT_QUIT)
   {
        return SDL_APP_SUCCESS;
   }
   return SDL_APP_CONTINUE;
}

void update()
{

}

void drawGrid(SDL_Surface* surface, SDL_Window* window)
{
    for(int i=0; i<WINDOW_HEIGHT/CELL_SIZE; i++)
    {
        SDL_Rect lineRect = (SDL_Rect) {0, i*CELL_SIZE, WINDOW_WIDHT, 1};
        SDL_FillSurfaceRect(surface, &lineRect, COLOR_WHITE);
    }
    SDL_UpdateWindowSurface(window);

    for(int i=0; i<WINDOW_WIDHT/CELL_SIZE; i++)
    {
        SDL_Rect ColumnRect = (SDL_Rect) {i*CELL_SIZE, 0, 1, WINDOW_HEIGHT};
        Uint32 color_white = COLOR_WHITE;
        SDL_FillSurfaceRect(surface, &ColumnRect, color_white);
    }
    SDL_UpdateWindowSurface(window);

}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{

}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
    //initializing video
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Error initializing video: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow("Game of life, i supose...", WINDOW_WIDHT, WINDOW_HEIGHT, 0);

    if(!window)
    {
        printf("Error initializing window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, NULL);

    if(!renderer)
    {
        printf("Error initializing renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    drawGrid(surface, window);

    return SDL_APP_CONTINUE;
}

