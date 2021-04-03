#include "window.h"

#include <SDL.h>

struct Window {
  SDL_bool      opened;
  Uint32 const  id;
  SDL_Window*   window;
  SDL_Renderer* renderer;
};

static int closeEventWatch(void* const userdata, SDL_Event* const event) {
  Window* const window = (Window*) userdata;

  if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE && event->window.windowID == window->id) {
    WindowClose(window);
  }

  return 0;
}

Window* WindowCreate() {
  if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      return NULL;
    }
  }

  SDL_Window* const window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

  SDL_Renderer* const renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  const Window base = {
    .opened   = SDL_TRUE,
    .id       = SDL_GetWindowID(window),
    .renderer = renderer,
    .window   = window,
  };

  const size_t size = sizeof(base);

  Window* const temp = SDL_malloc(size);

  SDL_AddEventWatch(closeEventWatch, temp);

  return SDL_memcpy(temp, &base, size);
}

SDL_bool WindowIsOpened(Window* const window) {
  return window->opened;
}

void WindowPresent(Window* const window) {
  if (window->opened) {
    SDL_RenderPresent(window->renderer);
  }
}

void WindowClear(Window* const window) {
  if (window->opened) {
    SDL_SetRenderDrawColor(window->renderer, 200, 0, 0, 255);
    SDL_RenderClear(window->renderer);
  }
}

void WindowDestroy(Window* const window) {
  if (window->opened) {
    WindowClose(window);
  }

  SDL_free(window);
}

void WindowClose(Window* const window) {
  SDL_DelEventWatch(closeEventWatch, window);
  SDL_DestroyRenderer(window->renderer);
  SDL_DestroyWindow(window->window);
  window->opened   = SDL_FALSE;
  window->window   = NULL;
  window->renderer = NULL;
}
