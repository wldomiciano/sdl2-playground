#include "enimy.h"
#include <SDL.h>
#include "framework.h"

Enimy enimies[MAX_ENIMIES];
static Game* game;
static SDL_Texture* texture;
static SDL_FRect* playerFrame;

Uint32 spawn(Uint32 interval, void* param) {
  SDL_Log("spawn");

  int active = -1;
  for (int i = 0; i < MAX_ENIMIES; i++) {
    if (!enimies[i].active) {
      active = i;
      break;
    }
  }

  if (active > -1) {
    enimies[active].active = SDL_TRUE;
    enimies[active].frame.x = 0;
    enimies[active].frame.y = 0;
  }

  return interval;
}

void enimy_init(SDL_FRect* player) {
  game = game_instance();

  playerFrame = player;

  texture = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_TARGET, 30, 30);

  SDL_SetRenderTarget(game->renderer, texture);
  SDL_SetRenderDrawColor(game->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(game->renderer);
  SDL_SetRenderTarget(game->renderer, NULL);

  for (int i = 0; i < MAX_ENIMIES; i++) {
    enimies[i].active = SDL_FALSE;
    enimies[i].frame.w = 30;
    enimies[i].frame.h = 30;
  }

  SDL_AddTimer(3000, spawn, NULL);
}

void enimy_create() {}

void enimy_update() {
  for (int i = 0; i < MAX_ENIMIES; i++) {
    if (enimies[i].active) {
      const SDL_FPoint delta = {
          (enimies[i].frame.x + enimies[i].frame.w * 0.5) - playerFrame->x,
          (enimies[i].frame.y + enimies[i].frame.h * 0.5) - playerFrame->y};

      const float rad = SDL_atan2f(delta.x, delta.y);
      const float deg = -(rad * 180) / PI;

      enimies[i].rotationRad = rad;
      enimies[i].rotationDeg = deg;

      enimies[i].frame.x -= SDL_sinf(enimies[i].rotationRad) * 1;
      enimies[i].frame.y -= SDL_cosf(enimies[i].rotationRad) * 1;

      // if (enimies[i].frame.x < 0 || enimies[i].frame.y < 0 ||
      //     enimies[i].frame.x > 400 || enimies[i].frame.y > 400) {
      //   enimies[i].active = SDL_FALSE;
      // }

      SDL_RenderCopyExF(game->renderer, texture, NULL, &enimies[i].frame,
                        /* enimies[i].rotationDeg */ 0, NULL, SDL_FLIP_NONE);
    }
  }
}
