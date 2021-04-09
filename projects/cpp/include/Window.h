#pragma once

#include <SDL.h>

class Window {
  SDL_Window* const window;

  SDL_Renderer* const renderer;

  bool isOpen = false;

public:
  const Uint32 id;

  Window(void);

  Window(const Window& window) = delete;

  Window(Window&& window) = delete;

  ~Window(void);

  void draw(const SDL_Rect& rect);

  void clear(void);

  void present(void);

  bool isOpened(void);

  void close(void);
};
