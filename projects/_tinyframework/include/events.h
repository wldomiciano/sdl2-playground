#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>
#include <stdbool.h>

#include "vector.h"

void handleEvents();

bool wasKeyJustPressed(const SDL_Scancode scancode);

bool isKeyPressed(const SDL_Scancode scancode);

bool isKeyReleased(const SDL_Scancode scancode);

bool wasQuitNotRequested();

void requestQuit();

vec2 getMousePosition();

#endif  // EVENTS_H
