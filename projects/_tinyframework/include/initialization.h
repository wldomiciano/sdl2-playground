#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdint.h>

#include "context.h"

enum {
  SDL_LOG_CATEGORY_UTILS = SDL_LOG_CATEGORY_CUSTOM
};

const char* getAppBasePath(void);

size_t getAppBasePathLength(void);

TTF_Font* getDefaultFont(void);

Context* getDefaultContext(void);

bool initializeSdl(const uint32_t flags);

bool initializeImg(const int flags);

bool initializeTtf(void);

bool initializeAll(const uint32_t sdlFlags, const int imgFlags);

bool initializeAllWithContext(
  const uint32_t sdlFlags,
  const int      imgFlags,
  const char*    title,
  const Uint16   width,
  const Uint16   height,
  const int      x,
  const int      y,
  const Uint32   windowFlags,
  const Uint32   rendererFlags  //
);

#endif  // INITIALIZATION_H
