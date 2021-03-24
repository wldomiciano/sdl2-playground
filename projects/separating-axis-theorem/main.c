#include "framework.h"

void print(SDL_FPoint* p) {
  for (int i = 0; i < 4; i++) {
    const float len = SDL_sqrtf(p[i].x * p[i].x + p[i].y * p[i].y);
    SDL_Log("%3.2f, %3.2f (%3.2f)", p[i].x, p[i].y, len);
  }
}

int main() {
  init();

  Rect* a = create_rect(200, 200, 50, 50, 0x0000FFFF, 0xFF00FFFF);
  Rect* b = create_rect(120, 120, 50, 50, 0x0000FFFF, 0xFF00FFFF);

  const float w = 100;
  const float c = 60;
  const float d = 60;
  SDL_FPoint points2[5] = {
    {c, d},
    {c + w, d},
    {c + w, d + w},
    {c, d + w},
    {c, d},
  };

  print(points2);

  float rad = (45 * PI) / 180;
  const float cos = SDL_cosf(rad);
  const float sin = SDL_sinf(rad);
  for (int i = 0; i < 5; i++) {
    const float cx = (c + w * 0.5);
    const float cy = (d + w * 0.5);
    const float x = points2[i].x - cx;
    const float y = points2[i].y - cy;

    points2[i] =
      (SDL_FPoint){(x * cos - y * sin) + cx, (x * sin + y * cos) + cy};
  }

  print(points2);

  while (isRunning) {
    input();

    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_Q]) {
      a->angle -= 3;
    } else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_E]) {
      a->angle += 3;
    }

    const float vel = 2;
    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W]) {
      a->dest.y -= vel;
    } else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S]) {
      a->dest.y += vel;
    }

    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A]) {
      a->dest.x -= vel;
    } else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D]) {
      a->dest.x += vel;
    }

    if (checkCollision(&a->dest, a->angle, &b->dest, b->angle)) {
      SDL_SetWindowTitle(window, "OK");
    } else {
      SDL_SetWindowTitle(window, "");
    }

    draw_rect(a);
    draw_rect(b);

    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderDrawLinesF(renderer, points2, 5);
    // SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    // SDL_RenderDrawLinesF(renderer, points3, 5);
    // SDL_RenderDrawPoint(renderer, 200, 200);
    present();
  }

  destroy_rect(a);
  destroy_rect(b);

  quit();
}
