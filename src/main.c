// DAN BRACE
// PONG GAME

// LIBRARIES
#include <stdio.h>
#include <windows.h>
#include "../lib/SDL2/include/SDL2/SDL.h"
#include "../include/game.h"

#define SDL_MAIN_HANDLED

// HEADER FILES
#include "../include/structs.h"
#include "../include/constants.h"

/*
// Window initialization
SDL_Window *init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Window *window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    return window;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//int main(int argc, char *argv[]) {
    SDL_Window *window = init();
    // Checks for null pointer
    if (!window) { return 1; }

    game(window);

    return 0;
}
*/

//int main(int argc, char* argv[]) {

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL initialization error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "SDL GUI Window",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        fprintf(stderr, "Window creation error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Creates game object pointers for the ball, left paddle, and right paddle
    GameObject ball = {SCREEN_WIDTH / 2, 1000 / 2, BALL_SPEED, BALL_SPEED};
    GameObject *ballPtr = &ball;
    GameObject leftPaddle = {50, PADDLE_HEIGHT / 2, 0, 0};
    GameObject *leftPaddlePtr = &leftPaddle;
    GameObject rightPaddle = {PADDLE_WIDTH - 50, PADDLE_HEIGHT / 2, 0, 0};
    GameObject *rightPaddlePtr = &rightPaddle;


    // Main loop and event handling
    int quit = 0;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
        
        // Render graphics and handle game logic here
        clearScreen(renderer);
        movePaddles(leftPaddlePtr, rightPaddlePtr);
        moveBall(ballPtr);

        // Rectangles for game objects
        SDL_Rect ballRect = {ballPtr->x, ballPtr->y, BALL_SIZE, BALL_SIZE};
        SDL_Rect leftPaddleRect = {leftPaddlePtr->x, leftPaddlePtr->y, PADDLE_WIDTH, PADDLE_HEIGHT};
        SDL_Rect rightPaddleRect = {rightPaddlePtr->x, rightPaddlePtr->y, PADDLE_WIDTH, PADDLE_HEIGHT};

        // Updates ball data if there is a collision
        collisionWall(ballPtr);
        collisionPaddle(ballPtr, ballRect, leftPaddleRect, rightPaddleRect);

        // TODO: End game if doesn't hit paddle

        paddleClamp(leftPaddlePtr, rightPaddlePtr);
        drawGame(renderer, ballRect, leftPaddleRect, rightPaddleRect);

        SDL_RenderPresent(renderer);
        
        // You can use SDL_RenderClear and SDL_RenderPresent for rendering
    }

    // Clean up and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
