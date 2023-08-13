// DAN BRACE
// PONG GAME

// LIBRARIES
#include <stdio.h>
#include "../lib\SDL2\include\SDL2\SDL.h"
#include "../include/game.h"

// HEADER FILES
#include "structs.h"
#include "constants.h"

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

int main(int argc, char *argv[]) {
    if (init() != 0) { return 1; }

    SDL_Window *window = init();
    // Checks for null pointer
    if (!window) { return 1; }

    game(window);

    return 0;
}