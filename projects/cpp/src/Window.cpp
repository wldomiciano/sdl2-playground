#include "Window.h"

#include <SDL.h>

static int closeEventWatch(void* const userdata, SDL_Event* const event) {
  Window* const window = static_cast<Window*>(userdata);

  if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE && event->window.windowID == window->id) {
    window->close();
  }

  return 0;
}

static SDL_Window* createWindow(void) {
  if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw "Falhou em criar Window devido à uma falha na inicialização da SDL";
    }
  }

  SDL_Window* const window = SDL_CreateWindow("Hello", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

  if (window) {
    return window;
  }

  throw "Falhou ao criar SDL_Window";
}

static SDL_Renderer* createRenderer(SDL_Window* const window) {
  SDL_Renderer* const renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  if (renderer) {
    return renderer;
  }

  throw "Falhou ao criar SDL_Renderer";
}

Window::Window()
    : window{createWindow()},
      renderer{createRenderer(window)},
      isOpen{true},
      id{SDL_GetWindowID(window)} {
  SDL_AddEventWatch(closeEventWatch, this);
}

Window::~Window(void) {
  close();
}

void Window::close(void) {
  isOpen = false;
  SDL_DelEventWatch(closeEventWatch, this);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Window::draw(const SDL_Rect& rect) {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &rect);
}

void Window::clear(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
}

void Window::present(void) {
  SDL_RenderPresent(renderer);
}

bool Window::isOpened(void) {
  return isOpen;
}
