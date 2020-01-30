#include <SDL.h>
#include "framework.h"

SDL_Window* window;
SDL_Renderer* renderer;

void drawCircle(int xc, int yc, int x, int y) {
  SDL_RenderDrawPoint(renderer, xc + x, yc + y);
  SDL_RenderDrawPoint(renderer, xc - x, yc + y);

  SDL_RenderDrawPoint(renderer, xc + x, yc - y);
  SDL_RenderDrawPoint(renderer, xc - x, yc - y);

  SDL_RenderDrawPoint(renderer, xc + y, yc + x);
  SDL_RenderDrawPoint(renderer, xc - y, yc + x);

  SDL_RenderDrawPoint(renderer, xc + y, yc - x);
  SDL_RenderDrawPoint(renderer, xc - y, yc - x);
}

void fillCircle(int xc, int yc, int x, int y) {
  SDL_RenderDrawLine(renderer, xc + x, yc + y, xc - x, yc + y);
  SDL_RenderDrawLine(renderer, xc + x, yc - y, xc - x, yc - y);
  SDL_RenderDrawLine(renderer, xc + y, yc + x, xc - y, yc + x);
  SDL_RenderDrawLine(renderer, xc + y, yc - x, xc - y, yc - x);
}

void drawCircleBres(int xc, int yc, int r) {
  int x = 0, y = r;
  int d = 3 - 2 * r;
  drawCircle(xc, yc, x, y);

  while (y >= x) {
    x++;
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else
      d = d + 4 * x + 6;
    drawCircle(xc, yc, x, y);
  }
}

void fillCircleBres(int xc, int yc, int r) {
  int x = 0, y = r;
  int d = 3 - 2 * r;
  fillCircle(xc, yc, x, y);

  while (y >= x) {
    x++;
    if (d > 0) {
      y--;
      d = d + 4 * (x - y) + 10;
    } else
      d = d + 4 * x + 6;
    fillCircle(xc, yc, x, y);
  }
}

int main() {
  window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 300, 300, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  while (!SDL_QuitRequested()) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    drawCircleBres(150, 150, 100);
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
    fillCircleBres(150, 200, 100);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyWindow(window);
  return 0;
}