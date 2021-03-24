#ifndef CONTEXT_H
#define CONTEXT_H

#include <SDL.h>
#include <SDL_ttf.h>

typedef struct Context {
  SDL_Window* const window;
  SDL_Renderer* const renderer;
} Context;

Context* createContext(
  const char* title,
  const Uint16 width,
  const Uint16 height,
  const int x,
  const int y,
  const Uint32 windowFlags,
  const Uint32 rendererFlags  //
);

void destroyContext(Context* const ctx);

#endif  // CONTEXT_H
