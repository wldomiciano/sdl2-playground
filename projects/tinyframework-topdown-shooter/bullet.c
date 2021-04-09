#include "bullet.h"

#include "enimy.h"
#include "tinyframework.h"

typedef struct {
  SDL_bool  active;
  SDL_FRect frame;
  float     rotationRad;
  float     rotationDeg;
} Bullet;

#define MAX_BULLETS 100
static SDL_FRect    rect = {0, 0, 2, 20};
static Bullet       bullets[MAX_BULLETS];
static Uint32       lastTimeCreated = 0;
static Uint32       timeout         = 0;
static SDL_Texture* texture;
static Context*     context;

void bullet_init(void) {
  context = getDefaultContext();

  texture = SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.w);

  SDL_SetRenderTarget(context->renderer, texture);
  SDL_SetRenderDrawColor(context->renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(context->renderer);
  SDL_SetRenderTarget(context->renderer, NULL);

  for (int i = 0; i < MAX_BULLETS; i++) {
    bullets[i].active  = SDL_FALSE;
    bullets[i].frame.w = 5;
    bullets[i].frame.h = 5;
  }
}

static SDL_bool SDL_HasIntersectionF(const SDL_FRect* A, const SDL_FRect* B) {
  /* Horizontal intersection */
  const float hAmin = A->x;
  const float hAmax = hAmin + A->w;
  const float hBmin = B->x;
  const float hBmax = hBmin + B->w;
  const float hMin  = hBmin > hAmin ? hBmin : hAmin;
  const float hMax  = hBmax < hAmax ? hBmax : hAmax;
  if (hMax <= hMin) return SDL_FALSE;

  /* Vertical intersection */
  const float vAmin = A->y;
  const float vAmax = vAmin + A->h;
  const float vBmin = B->y;
  const float vBmax = vBmin + B->h;
  const float vMin  = vBmin > vAmin ? vBmin : vAmin;
  const float vMax  = vBmax < vAmax ? vBmax : vAmax;
  if (vMax <= vMin) return SDL_FALSE;

  return SDL_TRUE;
}

void bullet_create(SDL_FRect player, float playerRotationRad, float playerRotationDeg) {
  const Uint32 ticks = SDL_GetTicks();

  if (SDL_TICKS_PASSED(ticks, timeout)) {
    timeout         = ticks + 200;
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

    bullets[active].active      = SDL_TRUE;
    bullets[active].frame.x     = player.x + 15 - rect.w * 0.5;
    bullets[active].frame.y     = player.y + 15 - rect.h * 0.5;
    bullets[active].rotationDeg = playerRotationDeg;
    bullets[active].rotationRad = playerRotationRad;
  }
}

void bullet_update(void) {
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

      if (!SDL_HasIntersectionF(&bullets[i].frame, &(SDL_FRect){0, 0, 400, 400})) {
        bullets[i].active = SDL_FALSE;
      }

      SDL_RenderCopyExF(context->renderer, texture, NULL, &bullets[i].frame, /* bullets[i].rotationDeg */ 0, NULL, SDL_FLIP_NONE);
    }
  }
}
