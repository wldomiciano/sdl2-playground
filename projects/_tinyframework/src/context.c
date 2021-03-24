#include "context.h"

#include <SDL.h>

/**
 * 
 */
Context* createContext(
  const char* title,
  const Uint16 width,
  const Uint16 height,
  const int x,
  const int y,
  const Uint32 windowFlags,
  const Uint32 rendererFlags  //
) {
  SDL_Window* const window = SDL_CreateWindow(title, x, y, width, height, windowFlags);

  if (window) {
    SDL_Renderer* const renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    if (renderer) {
      Context* const temp = SDL_malloc(sizeof(*temp));

      if (temp) {
        return SDL_memcpy(temp, &(Context){window, renderer}, sizeof(*temp));
      } else {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_SetError("Cannot to create a Context");
      }
    } else {
      SDL_DestroyWindow(window);
    }
  } else {
    SDL_DestroyWindow(window);
  }

  return NULL;
}

/**
 * 
 */
void destroyContext(Context* const ctx) {
  SDL_DestroyRenderer(ctx->renderer);
  SDL_DestroyWindow(ctx->window);
  free(ctx);
}
