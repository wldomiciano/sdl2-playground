// #define FRAMEWORK_NO_CONFIG
// #define FRAMEWORK_NO_CREATE
// #define FRAMEWORK_NO_UPDATE
// #define FRAMEWORK_NO_DESTROY

#include "framework.h"

void config() {
  // set_window_size(300, 300);
  // set_window_position(100, 100);
  // set_window_flags(0);
  // set_renderer_flags(0);
}

void mouse(__attribute__((unused)) const SDL_MouseButtonEvent* event) {
  SDL_Log("Clique");
}

void create() {
  add_mouse_button_listener(mouse);
}

void update() {
  if (is_key_pressed(SDL_SCANCODE_A)) {
    SDL_Log("A");
  }

  if (was_key_pressed(SDL_SCANCODE_S)) {
    SDL_Log("S");
  }
}

void destroy() {
}
