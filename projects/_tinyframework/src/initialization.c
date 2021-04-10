#include "initialization.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdint.h>

#include "context.h"
#include "miscellaneous.h"

#define ANSI_COLOR_RED    "\x1b[31m"
#define ANSI_COLOR_GREEN  "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE   "\x1b[34m"
#define ANSI_COLOR_RESET  "\x1b[0m"
// #define ANSI_COLOR_MAGENTA "\x1b[35m"
// #define ANSI_COLOR_CYAN    "\x1b[36m"

static char*     appBasePath       = NULL;
static size_t    appBasePathLength = 0;
static TTF_Font* font              = NULL;
static Context*  context           = NULL;

Context* getDefaultContext(void) {
  return context;
}

const char* getAppBasePath(void) {
  return appBasePath;
}

size_t getAppBasePathLength(void) {
  return appBasePathLength;
}

TTF_Font* getDefaultFont(void) {
  return font;
}

static void deinitializeAllOnExit(void) {
  SDL_LogDebug(SDL_LOG_CATEGORY_UTILS, ANSI_COLOR_BLUE "All systems was deinitializeds." ANSI_COLOR_RESET);

  destroyContext(context);

  SDL_free(appBasePath);
  appBasePath = NULL;
  appBasePath = 0;

  TTF_CloseFont(font);
  font = NULL;

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
}

bool initializeSdl(const uint32_t flags) {
  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

  SDL_LogDebug(SDL_LOG_CATEGORY_UTILS, ANSI_COLOR_YELLOW "Initializing SDL..." ANSI_COLOR_RESET);

  if (SDL_Init(flags | SDL_INIT_VIDEO) == 0) {
    SDL_LogDebug(SDL_LOG_CATEGORY_UTILS, ANSI_COLOR_GREEN "SDL initialized." ANSI_COLOR_RESET);

    atexit(deinitializeAllOnExit);

    appBasePath = SDL_GetBasePath();

    if (appBasePath == NULL) {
      appBasePath = SDL_strdup(".");
    }

    appBasePathLength = SDL_strlen(appBasePath);

    SDL_LogDebug(SDL_LOG_CATEGORY_UTILS, ANSI_COLOR_GREEN "Application base path setted to %s" ANSI_COLOR_RESET, appBasePath);

    return true;
  }

  SDL_Log(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, SDL_GetError());

  return false;
}

bool initializeImg(const int flags) {
  SDL_LogDebug(SDL_LOG_CATEGORY_UTILS, ANSI_COLOR_YELLOW "Initializing SDL_image..." ANSI_COLOR_RESET);

  if (SDL_WasInit(SDL_INIT_EVERYTHING) == 0) {
    SDL_Log(ANSI_COLOR_RED "SDL was not initialized." ANSI_COLOR_RESET);

    return false;
  }

  if ((IMG_Init(flags) & flags) == flags) {
    SDL_LogDebug(SDL_LOG_CATEGORY_UTILS, ANSI_COLOR_GREEN "SDL_image initialized." ANSI_COLOR_RESET);

    return true;
  }

  SDL_Log(ANSI_COLOR_RED "SDL_image initialization error: %s" ANSI_COLOR_RESET, IMG_GetError());

  return false;
}

bool initializeTtf(void) {
  SDL_LogDebug(SDL_LOG_CATEGORY_UTILS, ANSI_COLOR_YELLOW "Initializing SDL_ttf..." ANSI_COLOR_RESET);

  if (SDL_WasInit(SDL_INIT_EVERYTHING) == 0) {
    SDL_Log(ANSI_COLOR_RED "SDL was not initialized." ANSI_COLOR_RESET);

    return false;
  }

  if (TTF_Init() == 0) {
    SDL_LogDebug(SDL_LOG_CATEGORY_UTILS, ANSI_COLOR_GREEN "SDL_ttf initialized." ANSI_COLOR_RESET);

    font = openFont("/assets/fonts/VT323.ttf", 24);

    return true;
  }

  SDL_Log(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, TTF_GetError());

  return false;
}

bool initializeAll(const uint32_t sdlFlags, const int imgFlags) {
  return initializeSdl(sdlFlags) && initializeImg(imgFlags) && initializeTtf();
}

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
) {
  const bool isInitialized = initializeSdl(sdlFlags);

  if (isInitialized) {
    context = createContext(title, width, height, x, y, windowFlags, rendererFlags);
  }

  return isInitialized && initializeImg(imgFlags) && initializeTtf();
}
