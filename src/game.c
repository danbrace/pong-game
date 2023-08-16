// LIBRARIES
#include <stdio.h>
#include "../lib/SDL2/include/SDL2/SDL.h"

// HEADER FILES
#include "../include/structs.h"
#include "../include/constants.h"

// Clears the screen
void clearScreen(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

// Allows user to move paddles using the W+S and UP+DOWN keys
void movePaddles(GameObject *leftPaddle, GameObject *rightPaddle) {
    const Uint8 *kbState = SDL_GetKeyboardState(NULL);
    // W key
    if (kbState[SDL_SCANCODE_W]) {
        leftPaddle->y -= 5;
    }
    // S key
    if (kbState[SDL_SCANCODE_S]) {
        leftPaddle->y += 5;
    }
    // UP key
    if (kbState[SDL_SCANCODE_UP]) {
        rightPaddle->y -= 5;
    }
    // DOWN key
    if (kbState[SDL_SCANCODE_DOWN]) {
        rightPaddle->y += 5;
    }
}

// Moves ball on screen
void moveBall(GameObject *ball) {
    ball->x += ball->velocityX;
    ball->y += ball->velocityY;
}

// Updates ball velocity if ball hits top or bottom walls
void collisionWall(GameObject *ball) {
    // Checks if ball is out of bounds beyond top or bottom wall
    if (ball->y <= 0 || ball->y >= SCREEN_HEIGHT - BALL_SIZE) {
        ball->velocityY = -ball->velocityY;
    }
}

// Updates ball velocity if ball hits either paddle
void collisionPaddle(GameObject *ball, SDL_Rect ballRect, SDL_Rect leftPaddleRect, SDL_Rect rightPaddleRect) {
    // Turns ball around if its rectangle intersect the left or right paddle rectangle
    if (SDL_HasIntersection(&ballRect, &leftPaddleRect) || SDL_HasIntersection(&ballRect, &rightPaddleRect)) {
        ball->velocityX = -ball->velocityX;
    }
}

// Keeps paddle in bounds on screen
void paddleClamp(GameObject *leftPaddle, GameObject *rightPaddle) {
    leftPaddle->y = SDL_clamp(leftPaddle->y, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
    rightPaddle->y = SDL_clamp(rightPaddle->y, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
}

// Draws game state
void drawGame(SDL_Renderer *renderer, SDL_Rect ballRect, SDL_Rect leftPaddleRect, SDL_Rect rightPaddleRect) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &leftPaddleRect);
    SDL_RenderFillRect(renderer, &rightPaddleRect);
    SDL_RenderFillRect(renderer, &ballRect);
}

// Plays the game
void game(SDL_Window *window, SDL_Renderer *renderer) {
    // Creates game object pointers for the ball, left paddle, and right paddle
    GameObject ball = {SCREEN_WIDTH / 2, 1000 / 2, BALL_SPEED, BALL_SPEED};
    GameObject *ballPtr = &ball;
    GameObject leftPaddle = {50, PADDLE_HEIGHT / 2, 0, 0};
    GameObject *leftPaddlePtr = &leftPaddle;
    GameObject rightPaddle = {SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2, 0, 0};
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
        // TODO: Add score keeping
        // TODO: Change window name

        // Keeps paddles on screen
        paddleClamp(leftPaddlePtr, rightPaddlePtr);
        // Draws game
        drawGame(renderer, ballRect, leftPaddleRect, rightPaddleRect);

        SDL_RenderPresent(renderer);
        
        // Delays while loop
        SDL_Delay(16);
    }
}