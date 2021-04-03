#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>

typedef struct Window Window;

typedef struct Size Size;

Window* WindowCreate();

void WindowPresent(Window* const window);

void WindowClear(Window* const window);

SDL_bool WindowIsOpened(Window* const window);

void WindowClose(Window* const window);

void WindowDestroy(Window* const window);

#endif  // WINDOW_H
