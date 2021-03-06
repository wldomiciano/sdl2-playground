#include "player.h"

#include <SDL.h>

#include "bullet.h"
#include "enimy.h"
#include "tinyframework.h"

static Context*     context;
static SDL_Texture* mainTexture;
static SDL_Texture* armtexture;
static SDL_FRect    frame = {100, 100, 30, 30};
static SDL_FRect    arm   = {0, 0, 4, 20};
static const Uint8* keys;
static const float  VELOCITY = 4;

void player_create(void) {
  context = getDefaultContext();
  keys    = SDL_GetKeyboardState(NULL);

  enimy_init(&frame);
  bullet_init();

  mainTexture = SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (int) frame.w, (int) frame.h);

  armtexture = SDL_CreateTexture(context->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (int) arm.w, (int) arm.h);

  SDL_SetRenderTarget(context->renderer, mainTexture);
  SDL_SetRenderDrawColor(context->renderer, 0, 255, 0, 255);
  SDL_RenderClear(context->renderer);

  SDL_SetRenderTarget(context->renderer, armtexture);
  SDL_SetRenderDrawColor(context->renderer, 255, 0, 0, 255);
  SDL_RenderClear(context->renderer);

  SDL_SetRenderTarget(context->renderer, NULL);
}

void player_update(void) {
  const vec2       mousePos = getMousePosition();
  const SDL_FPoint delta    = {(frame.x + frame.w * 0.5f) - mousePos.x, (frame.y + frame.h * 0.5f) - mousePos.y};
  const float      rad      = SDL_atan2f(delta.x, delta.y);
  const float      deg      = -(rad * 180) / (float) M_PI;

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

  arm.x = frame.x + frame.w * 0.5f - arm.w * 0.5f;
  arm.y = frame.y + frame.h * 0.5f - arm.h;

  if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
    bullet_create(frame, rad, deg);
  }

  SDL_RenderCopyF(context->renderer, mainTexture, NULL, &frame);

  SDL_RenderCopyExF(context->renderer, armtexture, NULL, &arm, (double) deg, &(SDL_FPoint){arm.w * 0.5f, arm.h}, SDL_FLIP_NONE);

  bullet_update();
  enimy_update();
}

void player_destroy(void) {
}
