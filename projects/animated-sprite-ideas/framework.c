#include "framework.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include "tinyframework.h"

#define MAX_LENGTH 1024

static SDL_Window* window;
SDL_Renderer*      renderer;

static SDL_Joystick* controller;
static TTF_Font*     font;
static SDL_bool      isRunning    = SDL_FALSE;
static Uint32        sdlInitFlags = SDL_INIT_EVERYTHING;
static int           windowWidth  = 640;
static int           windowHeight = 480;
static Uint32        windowFlags  = 0;
// static Uint32 rendererFlags = SDL_RENDERER_PRESENTVSYNC;
static Uint8 customKeyStates[SDL_NUM_SCANCODES] = {0};

SDL_bool key_is_pressed(const SDL_Scancode code) {
  return SDL_GetKeyboardState(NULL)[code];
}

SDL_bool key_was_pressed(const SDL_Scancode code) {
  return customKeyStates[code];
}

SDL_bool button_is_pressed(const int button) {
  return SDL_JoystickGetButton(controller, button);
}

SDL_Texture* texture_create_from_file(const char* const filename) {
  SDL_Surface* const surface = SDL_LoadBMP(filename);

  if (!surface) {
    LOG("Error on surface creation");
    return NULL;
  }

  SDL_Texture* const texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (!texture) {
    LOG("Error on texture creation");
  }

  return texture;
}

static SDL_bool sdl_init(void) {
  if (SDL_Init(sdlInitFlags) != 0) {
    LOG("SDL init failure");
    return SDL_FALSE;
  }

  return SDL_TRUE;
}

static SDL_bool ttf_init(void) {
  if (TTF_Init() != 0) {
    SDL_Log("TTF init failure (%s)", TTF_GetError());
    return SDL_FALSE;
  }

  font = TTF_OpenFont("./assets/fonts/VT323.ttf", 24);

  if (font == NULL) {
    SDL_Log("TTF open font failure (%s)", TTF_GetError());
    return SDL_FALSE;
  }

  return SDL_TRUE;
}

static void sdl_quit(void) {
  SDL_JoystickClose(controller);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  font      = NULL;
  isRunning = SDL_FALSE;
}

static SDL_bool window_create(void) {
  if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, windowFlags, &window, &renderer) != 0) {
    LOG("Window and renderer creation failure");
    return SDL_FALSE;
  }

  return SDL_TRUE;
}

static void input_handle(void) {
  SDL_memset(customKeyStates, 0, SDL_NUM_SCANCODES);

  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      isRunning = SDL_FALSE;
    } else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.scancode == SDL_SCANCODE_GRAVE) {
        isRunning = SDL_FALSE;
      } else {
        customKeyStates[event.key.keysym.scancode] = event.key.repeat == 0;
      }
    }
  }
}

int main2(int argc, char** argv) {
  // SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
  isRunning = sdl_init() && window_create() && ttf_init();

  if (isRunning) {
    create();

    controller = SDL_JoystickOpen(0);

    if (controller == NULL) {
      LOG("Joystick open error");
    }
  }

  const float TIMESTEP       = 1000.0 / 60;
  float       delta          = 0;
  Uint32      previeousTicks = SDL_GetTicks();

  while (isRunning) {
    const Uint32 currentTicks = SDL_GetTicks();
    delta += currentTicks - previeousTicks;
    previeousTicks = currentTicks;

    input_handle();

    while (delta >= TIMESTEP) {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      update();

      delta -= TIMESTEP;

      SDL_RenderPresent(renderer);
    }
  }

  destroy();

  sdl_quit();

  return 0;
}

int main(int argc, char** argv) {
  initializeAllWithContext(0, 0, "Hello", 400, 400, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, SDL_RENDERER_PRESENTVSYNC);

  if (wasQuitNotRequested()) {
    create();

    controller = SDL_JoystickOpen(0);

    if (controller == NULL) {
      LOG("Joystick open error");
    }
  }

  const float DT       = 1 / 60.0;
  float       previous = getTicks();
  float       lag      = 0;

  while (wasQuitNotRequested()) {
    const float current = getTicks();
    const float delta   = current - previous;

    lag += delta;
    previous = current;

    handleEvents();

    clearRender(NULL, 0, 0, 0, 255);

    while (lag >= DT) {
      update();
      lag -= DT;
    }

    presentRender(NULL);
  }

  destroy();

  return 0;
}
