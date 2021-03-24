#include "utils.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event event;
static SDL_bool isRunning;

float getTicks() {
  return SDL_GetTicks() / 1000.0;
}

void draw_rect(const SDL_Rect* rect) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(renderer, rect);
}

void set_viewport_fit(Uint32 width, Uint32 height) {
  const SDL_Rect rect = {0, 0, width, height};
  int windowWidth;
  int windowHeight;

  SDL_GetWindowSize(window, &windowWidth, &windowHeight);

  float scale = (float) windowWidth / width;

  SDL_RenderSetScale(renderer, scale, scale);
  SDL_RenderSetViewport(renderer, &rect);
}

void create_game(Uint32 width, Uint32 height) {
  window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  isRunning = SDL_TRUE;
}

void destroy_game() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

SDL_bool is_running() {
  return isRunning;
}

void render_clear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void render_present() {
  SDL_RenderPresent(renderer);
}

void handle_input() {
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
      isRunning = SDL_FALSE;
  }
}
