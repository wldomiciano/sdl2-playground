#include "player.h"

#include <SDL.h>

#include "bullet.h"
#include "enimy.h"
#include "framework.h"

static SDL_Texture* mainTexture;
static SDL_Texture* armtexture;
static Game* game;
static SDL_FRect frame = {100, 100, 30, 30};
static SDL_FRect arm = {0, 0, 4, 20};
static const Uint8* keys;
static const float VELOCITY = 4;

void player_create() {
  game = game_instance();

  keys = SDL_GetKeyboardState(NULL);

  enimy_init(&frame);
  bullet_init();

  mainTexture = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_RGBA8888,
                                  SDL_TEXTUREACCESS_TARGET, frame.w, frame.h);

  armtexture = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_TARGET, arm.w, arm.h);

  SDL_SetRenderTarget(game->renderer, mainTexture);
  SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
  SDL_RenderClear(game->renderer);

  SDL_SetRenderTarget(game->renderer, armtexture);
  SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
  SDL_RenderClear(game->renderer);

  SDL_SetRenderTarget(game->renderer, NULL);
}

void player_update() {
  int x, y;

  Uint32 fire = SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT);

  SDL_FPoint delta = {(frame.x + frame.w * 0.5) - x,
                      (frame.y + frame.h * 0.5) - y};
  const float rad = SDL_atan2f(delta.x, delta.y);
  const float deg = -(rad * 180) / PI;

  if (keys[SDL_SCANCODE_W]) {
    frame.y += -VELOCITY;
  } else if (keys[SDL_SCANCODE_S]) {
    frame.y += VELOCITY;
  }

  if (keys[SDL_SCANCODE_D]) {
    frame.x += VELOCITY;
  } else if (keys[SDL_SCANCODE_A]) {
    frame.x += -VELOCITY;
  }

  arm.x = frame.x + frame.w * 0.5 - arm.w * 0.5;
  arm.y = frame.y + frame.h * 0.5 - arm.h;

  if (fire) {
    bullet_create(frame, rad, deg);
  }

  SDL_RenderCopyF(game->renderer, mainTexture, NULL, &frame);

  SDL_RenderCopyExF(game->renderer, armtexture, NULL, &arm, deg,
                    &(SDL_FPoint){arm.w * 0.5, arm.h}, SDL_FLIP_NONE);

  bullet_update();
  enimy_update();
}

void player_destroy() {
}
