#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <SDL.h>

typedef void (*stateFn)();

typedef struct Game {
  SDL_Rect windowFrame;

  SDL_Window*   window;
  SDL_Renderer* renderer;
  SDL_bool      isRunning;
  stateFn       create;
  stateFn       update;
  stateFn       destroy;
} Game;

extern const double PI;

int game_run(const char* const title, const Uint16 width, const Uint16 height,
             stateFn create, stateFn update, stateFn destroy);

Game* game_instance();

#endif
