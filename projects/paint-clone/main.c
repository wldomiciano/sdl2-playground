#include "game.h"
#include "utils.h"

const double PI = 3.14159265358979323846264338327950288;

void draw(int radius, int x, int y) {
  int sections = 360;
  float secAngles = 2 * PI / sections;
  int radiusTemp = radius;
  int a, b;

  while (radiusTemp--) {
    for (int i = 0; i < sections; i++) {
      float cos = SDL_cos(i * secAngles);
      float sin = SDL_sin(i * secAngles);
      a = radiusTemp * cos + x;
      b = radiusTemp * sin + y;
      SDL_RenderDrawPoint(renderer, a, b);
    }
  }
}

int main(int argc, char** argv) {
  create_game(800, 800);
  int red = 255;
  float radius = 10;
  int x = 0;
  int y = 0;
  SDL_bool grab;
  while (is_running()) {
    handle_input();

    if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON_LEFT) {
      grab = SDL_TRUE;
    }

    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]) {
      radius += 0.2;
    } else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]) {
      radius -= 0.2;
      if (radius < 1) radius = 1;
    } else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]) {
      red = 255;
    } else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]) {
      red = 0;
    }

    SDL_SetRenderDrawColor(renderer, red, 0, 0, 255);
    if (grab) {
      SDL_GetMouseState(&x, &y);
      draw(radius, x, y);
      grab = SDL_FALSE;
    }
    render_present();
  }

  destroy_game();
  return 0;
}
