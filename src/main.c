#define SDL_MAIN_USE_CALLBACKS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

int WINDOW_WIDHT = 1280;
int WINDOW_HEIGHT = 960;
int CELL_SIZE = 5;
int GRID_THICKNESS = 1;

int GAME_STATE = 0;
int counter = 0;

int **board;

Uint32 COLOR_WHITE = 0xffffffff;
Uint32 COLOR_GREY = 0x2f2f2f2f;
Uint32 COLOR_BLACK = 0x00000000;
Uint32 COLOR_GREEN = 0xff00ff00;

SDL_Window* window;
SDL_Surface* surface;

int mod(int a, int b)
{
    int result = a%b;

    if(a<0)
    {
        result+=b;
    }
    return result;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    free(board);
}

void InitializeBoard()
{
    int cols = WINDOW_WIDHT/CELL_SIZE;
    int rows = WINDOW_HEIGHT/CELL_SIZE;

    board = (int**)calloc(rows, sizeof(int*)); 

    for (int i=0; i<rows; i++) 
    {
        board[i] = (int*)calloc(cols, sizeof(int));
    }
}

void DrawGrid()
{
    int cols = WINDOW_WIDHT/CELL_SIZE;
    int rows = WINDOW_HEIGHT/CELL_SIZE;

    for(int i=0; i<rows+1; i++)
    {
        SDL_Rect lineRect = (SDL_Rect) {0, i*CELL_SIZE, WINDOW_WIDHT+GRID_THICKNESS, GRID_THICKNESS};
        SDL_FillSurfaceRect(surface, &lineRect, COLOR_GREY);
    }
    SDL_UpdateWindowSurface(window);

    for(int i=0; i<cols+1; i++)
    {
        SDL_Rect ColumnRect = (SDL_Rect) {i*CELL_SIZE, 0, GRID_THICKNESS, WINDOW_HEIGHT+GRID_THICKNESS};
        SDL_FillSurfaceRect(surface, &ColumnRect, COLOR_GREY);
    }
    SDL_UpdateWindowSurface(window);
}

void DrawCell(int x, int y, int cell_value)
{
    Uint32 color = cell_value == 0 ? COLOR_BLACK : COLOR_WHITE;

    SDL_Rect CellRect = (SDL_Rect) {(x*CELL_SIZE)+GRID_THICKNESS, (y*CELL_SIZE)+GRID_THICKNESS, CELL_SIZE-GRID_THICKNESS, CELL_SIZE-GRID_THICKNESS};
    SDL_FillSurfaceRect(surface, &CellRect, color);
}

void DrawBoard()
{
    int cols = WINDOW_WIDHT/CELL_SIZE;
    int rows = WINDOW_HEIGHT/CELL_SIZE;

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            DrawCell(j, i, board[i][j]); //i and j are switch, bcause j tells how much to the right the cell is, and i tells how much down.
        }
    }

    SDL_UpdateWindowSurface(window);
}

void CleanBoard()
{
    int cols = WINDOW_WIDHT/CELL_SIZE;
    int rows = WINDOW_HEIGHT/CELL_SIZE;

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            board[i][j]=0; 
        }
    }
}

void AdvanceGameLogic()
{   
    int cols = WINDOW_WIDHT/CELL_SIZE;
    int rows = WINDOW_HEIGHT/CELL_SIZE;

    //This creates an temporary copy of the board
    int **temp = (int**)calloc(rows, sizeof(int*)); 

    for (int i=0; i<rows; i++) 
    {
        temp[i] = (int*)calloc(cols, sizeof(int)); 
    }

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            temp[i][j]=board[i][j];
        }
    }

    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            //counting the alive cells around the cell ij, to apply the game rules
            int sumNeighbors = temp[mod((i-1),rows)][mod((j-1),cols)]+temp[mod((i-1),rows)][j]+
            temp[mod((i-1),rows)][mod((j+1),cols)]+temp[i][mod((j-1),cols)]+temp[i][mod((j+1),cols)]+
            temp[mod((i+1),rows)][mod((j-1),cols)]+temp[mod((i+1),rows)][j]+temp[mod((i+1),rows)][mod((j+1),cols)];

            //game rules:
            if(board[i][j]!=0) //ifgate to avoid turn 0s into 0s, which is useless
            {
                if(sumNeighbors<2||sumNeighbors>3) //death by isolation || death by overcrowding
                {
                    board[i][j]=0; 
                }
            }
            else if(sumNeighbors==3)
            {
                board[i][j]=1;
            }
        }
    }
    free(temp);
}

void DrawGlider()
{
    board[2][3] = 1;
    board[3][1] = 1;
    board[3][3] = 1;
    board[4][2] = 1;
    board[4][3] = 1;

    DrawBoard();

    SDL_UpdateWindowSurface(window);

}
void RandomizeBoard()
{
    srand(time(NULL));

    int cols = WINDOW_WIDHT/CELL_SIZE;
    int rows = WINDOW_HEIGHT/CELL_SIZE;
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            int random = 0;
            if(rand()%10<3)
            {   
                random = 1;
            }
            board[i][j] = random;
        }
    }

}

void SetCell(Sint32 mouse_x, Sint32 mouse_y)
{
    int cols = WINDOW_WIDHT/CELL_SIZE;
    int rows = WINDOW_HEIGHT/CELL_SIZE;
    int i, j;
    for(i=0;i<rows;i++)
    {
        if(mouse_y<i*CELL_SIZE)
        {
            i--;
            break;
        }
    }
    for(j=0;j<cols;j++)
    {
        if(mouse_x<j*CELL_SIZE)
        {
            j--;
            break;
        }
    }
    board[i][j] = mod(board[i][j]+1,2);

}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    int cols = WINDOW_WIDHT/CELL_SIZE;
    int rows = WINDOW_HEIGHT/CELL_SIZE;
    

    if(event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;
    }
    if(event->type == SDL_EVENT_KEY_DOWN)
    {
        if(event->key.key == SDLK_SPACE) //PAUSES THE GAME
        {
            GAME_STATE = mod(GAME_STATE+1,2);
        }
        else if(event->key.key == SDLK_X) //ERASES EVERY ALIVE CELL
        {
            CleanBoard();
        }
        else if(event->key.key == SDLK_G) //GENERATES A GLIDER
        {
            DrawGlider();
        }
        else if(event->key.key == SDLK_R) // RANDOMIZES THE BOARD
        {
            RandomizeBoard();
        }
    }
    else if(event->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        Sint32 mouse_x = event->button.x;
        Sint32 mouse_y = event->button.y;
        SetCell(mouse_x, mouse_y);
    }

   return SDL_APP_CONTINUE;
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    DrawBoard();

    if(GAME_STATE)
    {

        AdvanceGameLogic();

        SDL_Delay(50); 
    }

    DrawBoard();

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

    window = SDL_CreateWindow("Game of life, i supose...", WINDOW_WIDHT+GRID_THICKNESS, WINDOW_HEIGHT+GRID_THICKNESS, 0);

    if(!window)
    {
        printf("Error initializing window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    surface = SDL_GetWindowSurface(window);

    InitializeBoard();

    DrawGrid();

    return SDL_APP_CONTINUE;
}

