#define SDL_MAIN_USE_CALLBACKS
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int WINDOW_WIDHT = 900;
int WINDOW_HEIGHT = 800;
int CELL_SIZE = 10;

int **board;

Uint32 COLOR_WHITE = 0xffffffff;
Uint32 COLOR_GREY = 0x0f0f0f0f;
Uint32 COLOR_BLACK = 0x00000000;

SDL_Window* window;
SDL_Surface* surface;

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    free(board);
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
   if(event->type == SDL_EVENT_QUIT)
   {
        return SDL_APP_SUCCESS;
   }
   return SDL_APP_CONTINUE;
}

void InitializeBoard()
{
    board = (int**)calloc(WINDOW_WIDHT/CELL_SIZE, sizeof(int*)); //lines

    for (int i=0; i<WINDOW_WIDHT/CELL_SIZE; i++) 
    {
        board[i] = (int*)calloc(WINDOW_HEIGHT/CELL_SIZE, sizeof(int)); //columns
    }
}

void DrawGrid()
{
    for(int i=0; i<WINDOW_HEIGHT/CELL_SIZE; i++)
    {
        SDL_Rect lineRect = (SDL_Rect) {0, i*CELL_SIZE, WINDOW_WIDHT, 1};
        SDL_FillSurfaceRect(surface, &lineRect, COLOR_GREY);
    }
    SDL_UpdateWindowSurface(window);

    for(int i=0; i<WINDOW_WIDHT/CELL_SIZE; i++)
    {
        SDL_Rect ColumnRect = (SDL_Rect) {i*CELL_SIZE, 0, 1, WINDOW_HEIGHT};
        SDL_FillSurfaceRect(surface, &ColumnRect, COLOR_GREY);
    }
    SDL_UpdateWindowSurface(window);

}

void DrawCell(int x, int y, int cell_value)
{
    Uint32 color = cell_value == 0 ? COLOR_BLACK : COLOR_WHITE;

    SDL_Rect CellRect = (SDL_Rect) {x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE};
    SDL_FillSurfaceRect(surface, &CellRect, color);
}

void DrawBoard()
{
    for(int i=0; i<WINDOW_WIDHT/CELL_SIZE; i++)
    {
        for(int j=0; j<WINDOW_HEIGHT/CELL_SIZE; j++)
        {
            DrawCell(i, j, board[i][j]);
        }
        printf("\n");
    }
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{

    DrawBoard();

    DrawGrid();

    return SDL_APP_CONTINUE;
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

    surface = SDL_GetWindowSurface(window);

    InitializeBoard();

    board[10][11] = 1;
    board[23][15] = 1;

    return SDL_APP_CONTINUE;
}

