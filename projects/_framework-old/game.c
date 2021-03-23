#include "framework.h"
#include "sprite.h"

SDL_FRect rect = {0, 0, 50, 50};
float velocity = 1;

SDL_FPoint p1[5] = {{270, 0}, {370, 0}, {370, 100}, {270, 100}, {270, 0}};
SDL_FPoint p2[5] = {{270, 100}, {370, 100}, {370, 200}, {270, 200}, {270, 100}};

Sprite* link;

void rotate(SDL_FPoint* p, float deg, float centerX, float centerY) {
  const float rad = (deg * PI) / 180;
  const float cos = SDL_cosf(rad);
  const float sin = SDL_sinf(rad);

  for (int i = 0; i < 5; i++) {
    const float x = p[i].x - centerX;
    const float y = p[i].y - centerY;

    p[i].x = (x * cos - y * sin) + centerX;
    p[i].y = (x * sin + y * cos) + centerY;
  }
}

void create() {
  // link = sprite_create("assets/images/link.bmp", 1, 0, 0, 102, 108);
  link = sprite_create("assets/images/link.bmp", 5);

  sprite_add_animation(link, 0, 1, 100);
  sprite_add_frame(link, 0, 0, 1, 0, 0, 102, 108);
  sprite_add_collider(link, 0, 0, 0, 20, 20, 52, 70);
  // sprite_add_frame(link, 0, 1, 0, 102, 0, 102, 108);

  sprite_add_animation(link, 1, 10, 100);
  sprite_add_frame(link, 1, 0, 1, 0, 0, 102, 108);
  sprite_add_collider(link, 1, 0, 0, 20, 20, 52, 70);
  sprite_add_frame(link, 1, 1, 0, 102, 0, 102, 108);
  sprite_add_frame(link, 1, 2, 0, 204, 0, 102, 108);
  sprite_add_frame(link, 1, 3, 0, 306, 0, 102, 108);
  sprite_add_frame(link, 1, 4, 0, 408, 0, 102, 108);
  sprite_add_frame(link, 1, 5, 0, 510, 0, 102, 108);
  sprite_add_frame(link, 1, 6, 0, 612, 0, 102, 108);
  sprite_add_frame(link, 1, 7, 0, 714, 0, 102, 108);
  sprite_add_frame(link, 1, 8, 0, 816, 0, 102, 108);
  sprite_add_frame(link, 1, 9, 0, 918, 0, 102, 108);

  sprite_add_animation(link, 2, 10, 100);
  sprite_add_frame(link, 2, 0, 0, 0, 108, 102, 108);
  sprite_add_frame(link, 2, 1, 0, 102, 108, 102, 108);
  sprite_add_frame(link, 2, 2, 0, 204, 108, 102, 108);
  sprite_add_frame(link, 2, 3, 0, 306, 108, 102, 108);
  sprite_add_frame(link, 2, 4, 0, 408, 108, 102, 108);
  sprite_add_frame(link, 2, 5, 0, 510, 108, 102, 108);
  sprite_add_frame(link, 2, 6, 0, 612, 108, 102, 108);
  sprite_add_frame(link, 2, 7, 0, 714, 108, 102, 108);
  sprite_add_frame(link, 2, 8, 0, 816, 108, 102, 108);
  sprite_add_frame(link, 2, 9, 0, 918, 108, 102, 108);

  sprite_add_animation(link, 3, 10, 100);
  sprite_add_frame(link, 3, 0, 0, 0, 216, 102, 108);
  sprite_add_frame(link, 3, 1, 0, 102, 216, 102, 108);
  sprite_add_frame(link, 3, 2, 0, 204, 216, 102, 108);
  sprite_add_frame(link, 3, 3, 0, 306, 216, 102, 108);
  sprite_add_frame(link, 3, 4, 0, 408, 216, 102, 108);
  sprite_add_frame(link, 3, 5, 0, 510, 216, 102, 108);
  sprite_add_frame(link, 3, 6, 0, 612, 216, 102, 108);
  sprite_add_frame(link, 3, 7, 0, 714, 216, 102, 108);
  sprite_add_frame(link, 3, 8, 0, 816, 216, 102, 108);
  sprite_add_frame(link, 3, 9, 0, 918, 216, 102, 108);

  sprite_add_animation(link, 4, 10, 100);
  sprite_add_frame(link, 4, 0, 0, 0, 324, 102, 108);
  sprite_add_frame(link, 4, 1, 0, 102, 324, 102, 108);
  sprite_add_frame(link, 4, 2, 0, 204, 324, 102, 108);
  sprite_add_frame(link, 4, 3, 0, 306, 324, 102, 108);
  sprite_add_frame(link, 4, 4, 0, 408, 324, 102, 108);
  sprite_add_frame(link, 4, 5, 0, 510, 324, 102, 108);
  sprite_add_frame(link, 4, 6, 0, 612, 324, 102, 108);
  sprite_add_frame(link, 4, 7, 0, 714, 324, 102, 108);
  sprite_add_frame(link, 4, 8, 0, 816, 324, 102, 108);
  sprite_add_frame(link, 4, 9, 0, 918, 324, 102, 108);

  sprite_set_scale(link, 0.5, 0.5);
}

void update() {
  rotate(p1, 1, 320, 240);
  rotate(p2, 1, 320, 240);

  float minX = p1[0].x;
  float minY = p1[0].y;
  float maxX = p1[0].x;
  float maxY = p1[0].y;
  for (int i = 1; i < 4; i++) {
    if (p1[i].x < minX) {
      minX = p1[i].x;
    } else if (p1[i].x > maxX) {
      maxX = p1[i].x;
    }

    if (p1[i].y < minY) {
      minY = p1[i].y;
    } else if (p1[i].y > maxY) {
      maxY = p1[i].y;
    }
  }
  const float centerX = (maxX - minX) * 0.5 + minX;
  const float centerY = (maxY - minY) * 0.5 + minY;
  rotate(p1, 1, centerX, centerY);

  int mouseX, mouseY;
  SDL_GetMouseState(&mouseX, &mouseY);
  SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
  SDL_RenderDrawLineF(renderer, centerX, centerY, mouseX, mouseY);

  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderDrawLineF(renderer, minX, minY, maxX, maxY);

  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_RenderDrawLinesF(renderer, p1, 5);

  SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  SDL_RenderDrawLinesF(renderer, p2, 5);

  // if (button_is_pressed(2)) {
  //   sprite_move(link, 0, velocity);
  //   sprite_play_animation(link, 1);
  //   //
  // } else if (button_is_pressed(3)) {
  //   sprite_move(link, -velocity, 0);
  //   sprite_play_animation(link, 2);
  //   //
  // } else if (button_is_pressed(0)) {
  //   sprite_move(link, 0, -velocity);
  //   sprite_play_animation(link, 3);
  //   //
  // } else if (button_is_pressed(1)) {
  //   sprite_move(link, velocity, 0);
  //   sprite_play_animation(link, 4);
  //   //
  // } else {
  //   sprite_play_animation(link, 0);
  // }
  if (key_is_pressed(SDL_SCANCODE_S)) {
    sprite_move(link, 0, velocity);
    sprite_play_animation(link, 1);
  } else if (key_is_pressed(SDL_SCANCODE_A)) {
    sprite_move(link, -velocity, 0);
    sprite_play_animation(link, 2);
  } else if (key_is_pressed(SDL_SCANCODE_W)) {
    sprite_move(link, 0, -velocity);
    sprite_play_animation(link, 3);
  } else if (key_is_pressed(SDL_SCANCODE_D)) {
    sprite_move(link, velocity, 0);
    sprite_play_animation(link, 4);
  } else {
    sprite_play_animation(link, 0);
  }

  sprite_render(link);

  // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  // SDL_RenderFillRectF(renderer, &rect);
}

void destroy() {
  sprite_destroy(link);
}