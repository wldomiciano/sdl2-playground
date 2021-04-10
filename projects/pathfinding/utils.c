#include "utils.h"

static SDL_Window* window;
SDL_Renderer*      renderer;
static SDL_Event   event;
static SDL_bool    isRunning;

SDL_Texture* load_texture_from_file(const char* file) {
  SDL_Surface* temp = SDL_LoadBMP(file);
  SDL_Texture* tex  = SDL_CreateTextureFromSurface(renderer, temp);
  SDL_FreeSurface(temp);
  return tex;
}

double getTicks(void) {
  return SDL_GetTicks() / 1000.0;
}

void draw_rect(const SDL_Rect* rect) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(renderer, rect);
}

void set_viewport_fit(int width, int height) {
  const SDL_Rect rect = {0, 0, width, height};
  int            windowWidth;
  int            windowHeight;

  SDL_GetWindowSize(window, &windowWidth, &windowHeight);

  const float scale = (float) (windowWidth / width);

  SDL_RenderSetScale(renderer, scale, scale);
  SDL_RenderSetViewport(renderer, &rect);
}

void create_game(int width, int height) {
  window    = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  renderer  = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  isRunning = SDL_TRUE;
}

void destroy_game(void) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

SDL_bool is_running(void) {
  return isRunning;
}

void render_clear(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void render_present(void) {
  SDL_RenderPresent(renderer);
}

void handle_input(void) {
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
      isRunning = SDL_FALSE;
  }
}
