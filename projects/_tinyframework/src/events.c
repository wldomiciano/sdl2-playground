#include "events.h"

#include <SDL.h>
#include <stdbool.h>

static Sint8 keys[SDL_NUM_SCANCODES] = {0};

static bool shouldQuit = false;

vec2 getMousePosition() {
  int x, y;
  SDL_GetMouseState(&x, &y);
  return VEC2(x, y);
}

bool wasQuitNotRequested() {
  return shouldQuit == false;
}

void requestQuit() {
  shouldQuit = true;
}

bool wasKeyJustPressed(const SDL_Scancode scancode) {
  return keys[scancode] == 2;
}

bool isKeyPressed(const SDL_Scancode scancode) {
  return keys[scancode] > 1;
}

bool isKeyReleased(const SDL_Scancode scancode) {
  return keys[scancode] == 1;
}

void handleEvents() {
  SDL_Event event;

  // SDL_memset(keys, 0, SDL_NUM_SCANCODES);

  for (int i = 0; i < SDL_NUM_SCANCODES; i++)
    if (keys[i] == 1) keys[i] = 0;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      shouldQuit = true;
    } else if (event.type == SDL_KEYUP) {
      keys[event.key.keysym.scancode] = 1;
    } else if (event.type == SDL_KEYDOWN) {
      keys[event.key.keysym.scancode] = event.key.repeat ? 3 : 2;

      if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        requestQuit();
      }
    }
  }
}
