#include <SDL.h>

static void drawCircle(SDL_Renderer* const renderer, int xc, int yc, int x, int y) {
  SDL_RenderDrawPoint(renderer, xc + x, yc + y);
  SDL_RenderDrawPoint(renderer, xc - x, yc + y);

  SDL_RenderDrawPoint(renderer, xc + x, yc - y);
  SDL_RenderDrawPoint(renderer, xc - x, yc - y);

  SDL_RenderDrawPoint(renderer, xc + y, yc + x);
  SDL_RenderDrawPoint(renderer, xc - y, yc + x);

  SDL_RenderDrawPoint(renderer, xc + y, yc - x);
  SDL_RenderDrawPoint(renderer, xc - y, yc - x);
}

static void fillCircle(SDL_Renderer* const renderer, int xc, int yc, int x, int y) {
  SDL_RenderDrawLine(renderer, xc + x, yc + y, xc - x, yc + y);
  SDL_RenderDrawLine(renderer, xc + x, yc - y, xc - x, yc - y);
  SDL_RenderDrawLine(renderer, xc + y, yc + x, xc - y, yc + x);
  SDL_RenderDrawLine(renderer, xc + y, yc - x, xc - y, yc - x);
}

static void drawCircleBres(SDL_Renderer* const renderer, int xc, int yc, int r) {
  int x = 0, y = r;
  int d = 3 - 2 * r;
  drawCircle(renderer, xc, yc, x, y);

  while (y >= x) {
    x++;
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else
      d = d + 4 * x + 6;
    drawCircle(renderer, xc, yc, x, y);
  }
}

static void fillCircleBres(SDL_Renderer* const renderer, int xc, int yc, int r) {
  int x = 0, y = r;
  int d = 3 - 2 * r;
  fillCircle(renderer, xc, yc, x, y);

  while (y >= x) {
    x++;
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else
      d = d + 4 * x + 6;
    fillCircle(renderer, xc, yc, x, y);
  }
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char** argv) {
  SDL_Window*   window   = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 300, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  while (!SDL_QuitRequested()) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    drawCircleBres(renderer, 150, 150, 100);
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
    fillCircleBres(renderer, 150, 200, 100);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyWindow(window);
  return 0;
}
