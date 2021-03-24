#include "game.h"

int getRandomY() {
  srand(SDL_GetTicks());
  return -(rand() % 500);
}

void check_collision() {
}

Pipes* create_pipes(const Uint16 pipesCount) {
  Pipes* temp = SDL_malloc(sizeof(*temp) * pipesCount);

  int initialPosition = 600;
  int interval = 100 + 300;
  for (int i = 0; i < pipesCount; i++) {
    temp[i].top.w = temp[i].bot.w = 100;
    temp[i].top.h = temp[i].bot.h = 500;

    temp[i].top.x = temp[i].bot.x = initialPosition;
    initialPosition += interval;

    temp[i].top.y = getRandomY();
    SDL_Log("%d", temp[i].top.y);
    temp[i].bot.y = temp[i].top.y + 700;
    SDL_Delay(100);
  }

  return temp;
}

void move_pipes(Pipes* pipes) {
  for (int i = 0; i < 3; i++) {
    pipes[i].top.x -= 5;
    pipes[i].bot.x -= 5;

    if (pipes[i].top.x <= -100) {
      pipes[i].top.x = pipes[i].bot.x = 1100;
      pipes[i].top.y = getRandomY();
      pipes[i].bot.y = pipes[i].top.y + 700;
    }
  }
}

void draw_pipes(SDL_Renderer* renderer, SDL_Texture* texture, Pipes* pipes) {
  SDL_Rect rect = {0, 0, 100, 100};
  for (int i = 0; i < 3; i++) {
    SDL_RenderCopy(renderer, texture, &rect, &pipes[i].top);
    SDL_RenderCopy(renderer, texture, &rect, &pipes[i].bot);
  }
}

void destroy_pipes(Pipes* pipes) {
  SDL_free(pipes);
}
