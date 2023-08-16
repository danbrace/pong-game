#include "../lib/SDL2/include/SDL2/SDL.h"
#include "../include/structs.h"

void clearScreen(SDL_Renderer *renderer);

void movePaddles(GameObject *leftPaddle, GameObject *rightPaddle); 

void moveBall(GameObject *ball);

void collisionWall(GameObject *ball);

void collisionPaddle(GameObject *ball, SDL_Rect ballRect, SDL_Rect leftPaddleRect, SDL_Rect rightPaddleRect);

void paddleClamp(GameObject *leftPaddle, GameObject *rightPaddle);

void drawGame(SDL_Renderer *renderer, SDL_Rect ballRect, SDL_Rect leftPaddleRect, SDL_Rect rightPaddleRect);

void game(SDL_Window *window);