#include <SDL2/SDL.h>

static const int WINDOW_WIDTH = 600;
static const int WINDOW_HEIGHT = 700;
static const int PIPES_COUNT = 3;

struct Pipes {
    SDL_Rect top;
    SDL_Rect bot;
};

int getRandom(int max) {
    srand(SDL_GetTicks());
    return -(rand() % max);
}

int main(int argc, char** argv) {
    SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_bool isRunning = SDL_TRUE;
    SDL_Rect bird = { WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2, 40, 30};

    const int JUMP_SPEED = -10;
    const int FALLING_CONSTANT = -1;
    int vertSpeed = 0;

    const int PIPE_WIDTH = WINDOW_WIDTH / 6;
    const int PIPES_GAP = PIPE_WIDTH * 2;
    const int PIPE_HEIGHT = PIPE_WIDTH * 7 - PIPES_GAP;
    const int PIPES_VELOCITY = 5;
    const int PIPES_INTERVAL = PIPE_WIDTH * 2.5;
    const int PIPES_SPAWN = (PIPE_WIDTH + PIPES_INTERVAL) * 3;
    struct Pipes pipes[PIPES_COUNT];

    int POS_X = WINDOW_WIDTH;

    for(int i = 0; i < PIPES_COUNT; i++) {
        pipes[i].top.w = pipes[i].bot.w = PIPE_WIDTH;
        pipes[i].top.h = pipes[i].bot.h = PIPE_HEIGHT;
        pipes[i].top.x = pipes[i].bot.x = POS_X;

        pipes[i].top.y = getRandom(PIPE_HEIGHT);
        pipes[i].bot.y = pipes[i].top.y + PIPE_HEIGHT + PIPES_GAP;

        POS_X += PIPES_INTERVAL + PIPE_WIDTH;
    }

    SDL_Event event;
    SDL_bool tap;
        const Uint8* states = SDL_GetKeyboardState(NULL);
    while(isRunning) {
        SDL_PumpEvents(); if (SDL_HasEvent(SDL_QUIT)) isRunning = SDL_FALSE;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = SDL_FALSE;
            else if (event.type == SDL_MOUSEBUTTONDOWN) vertSpeed = JUMP_SPEED;
        }


        for(int i = 0; i < PIPES_COUNT; i++) {
            pipes[i].top.x -= PIPES_VELOCITY;
            pipes[i].bot.x -= PIPES_VELOCITY;

            if (pipes[i].top.x <= -PIPE_WIDTH) {
                pipes[i].top.x += PIPES_SPAWN;
                pipes[i].bot.x += PIPES_SPAWN;

                pipes[i].top.y = getRandom(PIPE_HEIGHT);
                pipes[i].bot.y = pipes[i].top.y + PIPE_HEIGHT + PIPES_GAP;
            }

            if ( SDL_HasIntersection(&bird, &pipes[i].top) || SDL_HasIntersection(&bird, &pipes[i].bot) ) {
                SDL_SetWindowTitle(window, "bateu");
            }
        }



        bird.y += vertSpeed;
        vertSpeed -= FALLING_CONSTANT;





        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for(int i = 0; i < PIPES_COUNT; i++) {
            SDL_RenderFillRect(renderer, &pipes[i].top);
            SDL_RenderFillRect(renderer, &pipes[i].bot);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &bird);


        SDL_RenderPresent(renderer);
    }

    return 0;
}
