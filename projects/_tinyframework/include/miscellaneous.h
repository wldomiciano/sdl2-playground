#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include <SDL.h>
#include <SDL_ttf.h>

#include "context.h"

float getTicks();

void presentRender(Context* ctx);

void clearRender(Context* ctx, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);

char* makePath(const char* path);

TTF_Font* openFont(const char* const filename, const Uint16 size);

SDL_Texture* loadTexture(SDL_Renderer* const renderer, const char* const filename);

SDL_Color hexToColor(const Uint32 color);

#endif  // MISCELLANEOUS_H
