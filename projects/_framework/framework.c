#include <SDL.h>
#include <SDL_ttf.h>

#include "framework.h"

static void default_game_loop();

struct Texture {
  SDL_Texture* sdlTexture;
  SDL_Rect src;
  SDL_FRect dest;
  double angle;
  SDL_FPoint center;
  SDL_FPoint origin;
  SDL_FPoint scale;
  SDL_RendererFlip flip;
};

const double PI = 3.14159265358979323846264338327950288;
static SDL_Window* window;
SDL_Renderer* renderer;
static SDL_bool isRunning;
static const char* windowTitle = "";
static Uint32 windowWidth = 640;
static Uint32 windowHeight = 480;
static Uint32 windowPositionX = SDL_WINDOWPOS_CENTERED;
static Uint32 windowPositionY = SDL_WINDOWPOS_CENTERED;
static Uint32 windowFlags = 0;
static Uint32 rendererFlags = SDL_RENDERER_PRESENTVSYNC;
static void (*game_loop)() = default_game_loop;
static Uint8 customKeyStates[SDL_NUM_SCANCODES];

const float TIMESTEP = 1000.0 / 60;
static float delta = 0;
static Uint32 previeousTicks;

void set_config_window_title(const char* title) {
  if (title != NULL) {
    windowTitle = title;
  }
}

void set_config_window_size(const Uint32 width, const Uint32 height) {
  if (width > 0 && height > 0) {
    windowWidth = width;
    windowHeight = height;
  }
}

void set_config_window_position(const Uint32 x, const Uint32 y) {
  windowPositionX = x;
  windowPositionY = y;
}

void set_config_window_flags(const Uint32 flags) {
  windowFlags = flags;
}

void set_config_renderer_flags(const Uint32 flags) {
  rendererFlags = flags;
}

void set_config_main_loop(void (*loop)()) {
  if (loop != NULL) {
    game_loop = loop;
  }
}

SDL_bool is_running() {
  return isRunning;
}

void stop_game() {
  isRunning = SDL_FALSE;
}

static void (*events_listener)(const SDL_Event* event);
static void (*keyboard_listener)(const SDL_KeyboardEvent* event);
static void (*mouse_motion_listener)(const SDL_MouseMotionEvent* event);
static void (*mouse_button_listener)(const SDL_MouseButtonEvent* event);
static void (*mouse_wheel_listener)(const SDL_MouseWheelEvent* event);

static Uint8 customKeyStates[SDL_NUM_SCANCODES];

void add_events_listener(void (*fn)(const SDL_Event* event)) {
  events_listener = fn;
}

void add_keyboard_listener(void (*fn)(const SDL_KeyboardEvent* event)) {
  keyboard_listener = fn;
}

void add_mouse_motion_listener(void (*fn)(const SDL_MouseMotionEvent* event)) {
  mouse_motion_listener = fn;
}

void add_mouse_button_listener(void (*fn)(const SDL_MouseButtonEvent* event)) {
  mouse_button_listener = fn;
}

void add_mouse_wheel_listener(void (*fn)(const SDL_MouseWheelEvent* event)) {
  mouse_wheel_listener = fn;
}

SDL_Texture* create_texture_from_file(const char* file) {
  SDL_Surface* surface = SDL_LoadBMP(file);

  if (surface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture) {
      return texture;
    } else {
      LOG("Failed to create texture from surface");
    }
  } else {
    LOG("Failed to load file");
  }

  return NULL;
}

SDL_bool was_key_pressed(SDL_Scancode code) {
  return customKeyStates[code];
}

SDL_bool is_key_pressed(SDL_Scancode code) {
  return SDL_GetKeyboardState(NULL)[code];
}

void input_handle() {
  SDL_memset(customKeyStates, 0, SDL_NUM_SCANCODES);

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (events_listener) {
      events_listener(&event);
    }

    switch (event.type) {
      case SDL_QUIT:
        stop_game();
        break;

      case SDL_KEYDOWN:
        if (event.key.keysym.scancode == SDL_SCANCODE_GRAVE) {
          stop_game();
        } else {
          customKeyStates[event.key.keysym.scancode] = event.key.repeat == 0;
        }
        __attribute__((fallthrough));
      case SDL_KEYUP:
        if (keyboard_listener) {
          keyboard_listener(( const SDL_KeyboardEvent* ) &event);
        }
        break;

      case SDL_MOUSEBUTTONUP:
      case SDL_MOUSEBUTTONDOWN:
        if (mouse_button_listener) {
          mouse_button_listener(( const SDL_MouseButtonEvent* ) &event);
        }
        break;

      case SDL_MOUSEMOTION:
        if (mouse_motion_listener) {
          mouse_motion_listener(( const SDL_MouseMotionEvent* ) &event);
        }
        break;

      case SDL_MOUSEWHEEL:
        if (mouse_wheel_listener) {
          mouse_wheel_listener(( const SDL_MouseWheelEvent* ) &event);
        }
        break;
    }
  }
}

static void default_game_loop() {
  Uint32 currentTicks = SDL_GetTicks();
  delta += currentTicks - previeousTicks;
  previeousTicks = currentTicks;

  while (delta >= TIMESTEP) {
    input_handle();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    update();

    delta -= TIMESTEP;

    SDL_RenderPresent(renderer);
  }
}

static SDL_bool init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    window = SDL_CreateWindow(windowTitle, windowPositionX, windowPositionY,
                              windowWidth, windowHeight, windowFlags);
  } else {
    LOG("Initialization error");
  }

  if (window) {
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);
  } else {
    LOG("Window creation error");
  }

  if (renderer) {
    isRunning = SDL_TRUE;
  } else {
    LOG("Renderer creation error");
  }

  previeousTicks = SDL_GetTicks();

  return isRunning;
}

static void quit() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main() {
  config();

  init();

  if (isRunning) {
    create();
  }

  while (isRunning) {
    game_loop();
  }

  destroy();

  quit();

  return 0;
}