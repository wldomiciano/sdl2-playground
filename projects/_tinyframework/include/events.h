#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>
#include <stdbool.h>

#include "vector.h"

void handleEvents(void);

bool wasKeyJustPressed(const SDL_Scancode scancode);

bool isKeyPressed(const SDL_Scancode scancode);

bool isKeyReleased(const SDL_Scancode scancode);

bool wasQuitNotRequested(void);

void requestQuit(void);

vec2 getMousePosition(void);

#endif  // EVENTS_H
