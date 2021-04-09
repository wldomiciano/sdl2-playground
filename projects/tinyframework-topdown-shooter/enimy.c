#include "enimy.h"

#include <SDL.h>

#include "tinyframework.h"

Enimy                   enimies[MAX_ENIMIES];
static Context*         context;
static SDL_Texture*     texture;
static const SDL_FRect* playerFrame;

Uint32 spawn(Uint32 interval, void* const param) {
  SDL_Log("spawn");

  (void) param;

  int active = -1;
  for (int i = 0; i < MAX_ENIMIES; i++) {
    if (!enimies[i].active) {
      active = i;
      break;
    }
  }

  if (active > -1) {
    enimies[active].active  = SDL_TRUE;
    enimies[active].frame.x = 0;
    enimies[active].frame.y = 0;
  }

  return interval;
}

void enimy_init(const SDL_FRect* const player) {
  context = getDefaultContext();

  playerFrame = player;

  texture = SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 30, 30);

  SDL_SetRenderTarget(context->renderer, texture);
  SDL_SetRenderDrawColor(context->renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(context->renderer);
  SDL_SetRenderTarget(context->renderer, NULL);

  for (int i = 0; i < MAX_ENIMIES; i++) {
    enimies[i].active  = SDL_FALSE;
    enimies[i].frame.w = 30;
    enimies[i].frame.h = 30;
  }

  SDL_AddTimer(3000, spawn, NULL);
}

void enimy_create(void) {
}

void enimy_update(void) {
  for (int i = 0; i < MAX_ENIMIES; i++) {
    if (enimies[i].active) {
      const SDL_FPoint delta = {
        (enimies[i].frame.x + enimies[i].frame.w * 0.5) - playerFrame->x,
        (enimies[i].frame.y + enimies[i].frame.h * 0.5) - playerFrame->y,
      };

      const float rad = SDL_atan2f(delta.x, delta.y);
      const float deg = -(rad * 180) / M_PI;

      enimies[i].rotationRad = rad;
      enimies[i].rotationDeg = deg;

      enimies[i].frame.x -= SDL_sinf(enimies[i].rotationRad) * 1;
      enimies[i].frame.y -= SDL_cosf(enimies[i].rotationRad) * 1;

      // if (enimies[i].frame.x < 0 || enimies[i].frame.y < 0 ||
      //     enimies[i].frame.x > 400 || enimies[i].frame.y > 400) {
      //   enimies[i].active = SDL_FALSE;
      // }

      SDL_RenderCopyExF(context->renderer, texture, NULL, &enimies[i].frame, /* enimies[i].rotationDeg */ 0, NULL, SDL_FLIP_NONE);
    }
  }
}
