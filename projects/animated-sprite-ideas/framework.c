#include <SDL.h>
#include <SDL_ttf.h>

#include "framework.h"

#define MAX_LENGTH 1024

const double PI = 3.14159265358979323846264338327950288;

SDL_Window* window;
SDL_Renderer* renderer;

static SDL_Joystick* controller;
static TTF_Font* font;
static SDL_bool isRunning = SDL_FALSE;
static Uint32 sdlInitFlags = SDL_INIT_EVERYTHING;
static Uint32 windowWidth = 640;
static Uint32 windowHeight = 480;
static Uint32 windowFlags = 0;
// static Uint32 rendererFlags = SDL_RENDERER_PRESENTVSYNC;
static Uint8 customKeyStates[SDL_NUM_SCANCODES] = {0};

SDL_bool key_is_pressed(SDL_Scancode code) {
  return SDL_GetKeyboardState(NULL)[code];
}

SDL_bool key_was_pressed(SDL_Scancode code) {
  return customKeyStates[code];
}

SDL_bool button_is_pressed(int button) {
  return SDL_JoystickGetButton(controller, button);
}

SDL_Texture* texture_create_from_file(const char* filename) {
  SDL_Surface* surface = SDL_LoadBMP(filename);

  if (!surface) {
    LOG("Error on surface creation");
    return NULL;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  if (!texture) {
    LOG("Error on texture creation");
  }

  return texture;
}

static SDL_bool sdl_init() {
  if (SDL_Init(sdlInitFlags) != 0) {
    LOG("SDL init failure");
    return SDL_FALSE;
  }

  return SDL_TRUE;
}

static SDL_bool ttf_init() {
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

static void sdl_quit() {
  SDL_JoystickClose(controller);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  font = NULL;
  isRunning = SDL_FALSE;
}

static SDL_bool window_create() {
  if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, windowFlags,
                                  &window, &renderer) != 0) {
    LOG("Window and renderer creation failure");
    return SDL_FALSE;
  }

  return SDL_TRUE;
}

static void input_handle() {
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

int main(int argc, char** argv) {
  // SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
  isRunning = sdl_init() && window_create() && ttf_init();

  if (isRunning) {
    create();

    controller = SDL_JoystickOpen(0);

    if (controller == NULL) {
      LOG("Joystick open error");
    }
  }

  const float TIMESTEP = 1000.0 / 60;
  float delta = 0;
  Uint32 previeousTicks = SDL_GetTicks();

  while (isRunning) {
    Uint32 currentTicks = SDL_GetTicks();
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
