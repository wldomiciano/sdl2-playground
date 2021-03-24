#include "sprite.h"

#include <SDL.h>
#include <SDL_image.h>

#include "initialization.h"
#include "miscellaneous.h"

struct Sprite {
  SDL_Renderer* renderer;
  SDL_Texture* texture;
  SDL_Rect srcrect;

  float w, h;
  vec2 pos;
  vec2 pivot;
  vec2 origin;

  double angle;
  SDL_FPoint scale;
  SDL_RendererFlip flip;
};

// ACTIONS

void destroySprite(Sprite* const sprite) {
  SDL_free(sprite);
}

Sprite* createSprite(Context* ctx, const char* const filename, const SDL_Rect* const rect) {
  ctx = ctx ? ctx : getDefaultContext();

  SDL_Texture* const texture = loadTexture(ctx->renderer, filename);

  if (texture == NULL) {
    SDL_Log("erro na textura: %s\n", SDL_GetError());
  }

  int w = 0, h = 0;
  if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) < 0) {
    SDL_Log("outro erro na textura: %s\n", SDL_GetError());
  }

  const Sprite temp = {
    .renderer = ctx->renderer,
    .texture = texture,
    .flip = SDL_FLIP_NONE,
    .scale = {0, 0},
    .angle = 0.0,
    .pivot = {0, 0},
    .origin = {0, 0},
    .srcrect = rect ? *rect : (SDL_Rect){0, 0, w, h},
    .pos = {0, 0},
    .w = w,
    .h = h,
  };

  const size_t size = sizeof(temp);

  return SDL_memcpy(SDL_malloc(size), &temp, size);
}

void drawSprite(Sprite* const sprite) {
  SDL_RenderCopyExF(
    sprite->renderer,
    sprite->texture,
    &sprite->srcrect,
    &(SDL_FRect){sprite->pos.x, sprite->pos.y, sprite->w, sprite->h},
    sprite->angle,
    &(SDL_FPoint){sprite->pivot.x, sprite->pivot.y},
    sprite->flip  //
  );
}

vec2 moveSprite(Sprite* const sprite, const vec2 v) {
  return sprite->pos = add(sprite->pos, v);
}

void rotateSprite(Sprite* const sprite, const float deg) {
  sprite->angle += deg;
}

// SETTERS

void setSpriteRotation(Sprite* const sprite, const float deg) {
  sprite->angle = deg;
}

void setSpritePosition(Sprite* const sprite, const vec2 v) {
  sprite->pos = sub(v, sprite->origin);
}

void setSpriteOrigin(Sprite* const sprite, const vec2 v) {
  sprite->origin = v;
}

void setSpritePivot(Sprite* const sprite, const vec2 v) {
  sprite->pivot = add(v, sprite->pos);
}

void setSpriteGlogalPivot(Sprite* const sprite, const vec2 v) {
  sprite->pivot = sub(v, sprite->pos);
}

// GETTERS

float getSpriteAngle(Sprite* const sprite) {
  return sprite->angle;
}

vec2 getSpritePivot(Sprite* const sprite) {
  return VEC2(sprite->pivot.x, sprite->pivot.y);
}

vec2 getSpritePosition(Sprite* const sprite) {
  return add(sprite->pos, sprite->origin);
}
