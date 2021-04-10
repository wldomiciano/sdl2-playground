// #include "game.h"
#include "utils.h"

static void draw(float radius, float x, float y) {
  const float sections   = 360.f;
  const float secAngles  = 2 * (float) M_PI / sections;
  float       radiusTemp = radius;
  float       a, b;

  while (radiusTemp-- <= 0) {
    for (float i = 0; i < sections; i++) {
      float cos = SDL_cosf(i * secAngles);
      float sin = SDL_sinf(i * secAngles);
      a         = radiusTemp * cos + x;
      b         = radiusTemp * sin + y;
      SDL_RenderDrawPointF(renderer, a, b);
    }
  }
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char** argv) {
  create_game(800, 800);
  Uint8    red    = 255;
  float    radius = 10;
  int      x      = 0;
  int      y      = 0;
  SDL_bool grab   = SDL_FALSE;

  while (is_running()) {
    handle_input();

    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LEFT) {
      grab = SDL_TRUE;
    }

    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]) {
      radius += 0.2f;
    } else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]) {
      radius -= 0.2f;
      if (radius < 1) radius = 1;
    } else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]) {
      red = 255;
    } else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]) {
      red = 0;
    }

    SDL_SetRenderDrawColor(renderer, red, 0, 0, 255);
    if (grab) {
      SDL_GetMouseState(&x, &y);
      draw(radius, (float) x, (float) y);
      grab = SDL_FALSE;
    }
    render_present();
  }

  destroy_game();
  return 0;
}
