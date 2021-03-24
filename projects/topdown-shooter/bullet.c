#include "bullet.h"

#include <SDL.h>

#include "enimy.h"
#include "framework.h"

typedef struct {
  SDL_bool active;
  SDL_FRect frame;
  float rotationRad;
  float rotationDeg;
} Bullet;

#define MAX_BULLETS 100
static SDL_FRect rect = {0, 0, 2, 20};
static Bullet bullets[MAX_BULLETS];
static Uint32 lastTimeCreated = 0;
static Uint32 timeout = 0;
static SDL_Texture* texture;
static Game* game;

void bullet_init() {
  game = game_instance();

  texture = SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_RGBA8888,
                              SDL_TEXTUREACCESS_TARGET, rect.w, rect.w);

  SDL_SetRenderTarget(game->renderer, texture);
  SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(game->renderer);
  SDL_SetRenderTarget(game->renderer, NULL);

  for (int i = 0; i < MAX_BULLETS; i++) {
    bullets[i].active = SDL_FALSE;
    bullets[i].frame.w = 5;
    bullets[i].frame.h = 5;
  }
}

static SDL_bool SDL_HasIntersectionF(const SDL_FRect* A, const SDL_FRect* B) {
  float Amin, Amax, Bmin, Bmax;

  /* Horizontal intersection */
  Amin = A->x;
  Amax = Amin + A->w;
  Bmin = B->x;
  Bmax = Bmin + B->w;
  if (Bmin > Amin) Amin = Bmin;
  if (Bmax < Amax) Amax = Bmax;
  if (Amax <= Amin) return SDL_FALSE;

  /* Vertical intersection */
  Amin = A->y;
  Amax = Amin + A->h;
  Bmin = B->y;
  Bmax = Bmin + B->h;
  if (Bmin > Amin) Amin = Bmin;
  if (Bmax < Amax) Amax = Bmax;
  if (Amax <= Amin) return SDL_FALSE;

  return SDL_TRUE;
}

void bullet_create(SDL_FRect player, float playerRotationRad,
                   float playerRotationDeg) {
  const Uint32 ticks = SDL_GetTicks();

  // SDL_Log("ok %d", count);
  if (SDL_TICKS_PASSED(ticks, timeout)) {
    // if (1) {
    timeout = ticks + 200;
    lastTimeCreated = ticks;

    int active = -1;

    for (int i = 0; i < MAX_BULLETS; i++) {
      if (!bullets[i].active) {
        active = i;
        break;
      }
    }

    SDL_Log("> %d", active);

    if (active < 0) return;

    rect.x = player.x * 0.5 + rect.w * 0.5;
    rect.y = player.y * 0.5 + rect.h * 0.5;

    bullets[active].active = SDL_TRUE;
    bullets[active].frame.x = player.x + 15 - rect.w * 0.5;
    bullets[active].frame.y = player.y + 15 - rect.h * 0.5;
    bullets[active].rotationDeg = playerRotationDeg;
    bullets[active].rotationRad = playerRotationRad;
  }
}

void bullet_update() {
  for (int i = 0; i < MAX_BULLETS; i++) {
    if (bullets[i].active) {
      bullets[i].frame.x -= SDL_sinf(bullets[i].rotationRad) * 3;
      bullets[i].frame.y -= SDL_cosf(bullets[i].rotationRad) * 3;

      for (int j = 0; j < MAX_ENIMIES; j++) {
        if (enimies[j].active) {
          if (SDL_HasIntersectionF(&bullets[i].frame, &enimies[j].frame)) {
            bullets[i].active = SDL_FALSE;
            enimies[j].active = SDL_FALSE;
          }
        }
      }

      if (bullets[i].frame.x < 0 || bullets[i].frame.y < 0 ||
          bullets[i].frame.x > 400 || bullets[i].frame.y > 400) {
        bullets[i].active = SDL_FALSE;
      }

      SDL_RenderCopyExF(game->renderer, texture, NULL, &bullets[i].frame,
                        /* bullets[i].rotationDeg */ 0, NULL, SDL_FLIP_NONE);
    }
  }
}
