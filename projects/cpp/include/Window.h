#pragma once

#include <SDL.h>

class Window {
  SDL_Window* const window;

  SDL_Renderer* const renderer;

  bool isOpen = false;

public:
  const Uint32 id;

  Window();

  Window(const Window& window) = delete;

  Window(Window&& window) = delete;

  ~Window();

  void draw(const SDL_Rect& rect);

  void clear();

  void present();

  bool isOpened();

  void close();
};
