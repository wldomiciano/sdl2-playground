#include <SDL.h>

const int WINDOW_WIDTH  = 500;
const int WINDOW_HEIGHT = 300;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Rect rect = {0, 0, 5, 20};
SDL_Rect box = {100, 0, 50, 50};
float x, y, lastX, lastY;
int vel = 10;
int velX = 300;
int velY = 300;
SDL_bool running = SDL_TRUE;

void move(int pos) {
    rect.y = pos;
    rect.x += rect.w;
    if ((rect.x + rect.w) >= WINDOW_WIDTH ) {
        rect.x = 0;
        rect.y *= 2;
    }
}

void moveBox(double delta) {
    lastX = x;
    lastY = y;

    x += velX * delta;
    y += velY * delta;

    if ( x + box.w >= WINDOW_WIDTH || x < 0 ) velX = -velX;
    if ( y + box.h >= WINDOW_HEIGHT || y < 0 ) velY = -velY;

    // printf("x: %f  y: %f\n", x, y);
}

void update(double delta) {    
    // move(0);
    moveBox(delta);
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderFillRect(renderer, &rect);
    // SDL_Delay(1);
}

void render(double interpolation) {
    // printf("%f\n", interpolation);

    SDL_Delay(1000 / 30);
    // move(rect.h);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    
    x = lastX + (x - lastX) * interpolation; y = lastY + (y - lastY) * interpolation;

    box.x = x;
    box.y = y;
    SDL_RenderFillRect(renderer, &box);
    SDL_RenderPresent(renderer);
}

void quit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Teste", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    atexit(quit);
}


void input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) running = SDL_FALSE;
    }
}

SDL_bool isRunning() { return running; }

int main() {
    init();

    Uint32 prevTime = SDL_GetTicks();
    double accumulator = 0;
    const double TIME_STEP = 1.0 / 60.0;

    while(isRunning()) {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 timeout = currentTime + 1;

        while (!SDL_TICKS_PASSED(currentTime, timeout))
            currentTime = SDL_GetTicks();

        double deltaTime = (currentTime - prevTime) / (double) 1000.0;

        accumulator += deltaTime;
        prevTime = currentTime;

        input();

        while ( accumulator >= TIME_STEP ) {
            update(TIME_STEP);
            accumulator -= TIME_STEP;
        }

        render(accumulator / TIME_STEP);
    }

    return 0;
}
