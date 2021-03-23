#include <SDL.h>

#include "framework.h"
#include "sprite.h"

typedef struct {
  SDL_FPoint points[4];
} Collider;

typedef struct {
  SDL_Rect frame;
  Uint8 count;  // quantidade de colliders
  Collider* colliders;
} Frame;

typedef struct {
  int duration;
  Uint8 count;    // quantidade de frames
  Uint8 current;  // frame atual
  Frame* frames;  // array de frames
} Animation;

typedef struct {
  Uint8 count;            // quantidade total de animações
  Uint8 current;          // animação sendo executada no momento
  Animation* animations;  // array de animações
} Animator;

struct Sprite {
  SDL_Texture* texture;
  Animator animator;

  float x;
  float y;
  double angle;
  SDL_FPoint center;  // centro de renderização
  SDL_FPoint pivot;   // centro de rotação
  SDL_FPoint scale;
  SDL_RendererFlip flip;
};

/**
 *
 */
SDL_FPoint sprite_get_position(Sprite* sprite) {
  return (SDL_FPoint){sprite->x, sprite->y};
}

void sprite_set_position(Sprite* sprite, float x, float y) {
  SDL_FPoint pos = sprite_get_position(sprite);

  pos.x += x;
  pos.y += y;

  sprite_move(sprite, pos.x, pos.y);
}

void sprite_rotate(Sprite* sprite, float deg) {
  sprite->angle = deg;
}

void sprite_set_scale(Sprite* sprite, float x, float y) {
  sprite->scale.x = x;
  sprite->scale.y = y;

  for (int animIndex = 0; animIndex < sprite->animator.count; animIndex++) {
    Animation* animation = &sprite->animator.animations[animIndex];

    for (int frameIndex = 0; frameIndex < animation->count; frameIndex++) {
      Frame* frame = &animation->frames[frameIndex];

      for (int collIndex = 0; collIndex < frame->count; collIndex++) {
        Collider* collider = &frame->colliders[collIndex];

        for (int j = 0; j < 4; j++) {
          collider->points[j].x *= x;
          collider->points[j].y *= y;
        }
      }
    }
  }
}

void sprite_move(Sprite* sprite, float x, float y) {
  sprite->x += x;
  sprite->y += y;

  for (int animIndex = 0; animIndex < sprite->animator.count; animIndex++) {
    Animation* animation = &sprite->animator.animations[animIndex];

    for (int frameIndex = 0; frameIndex < animation->count; frameIndex++) {
      Frame* frame = &animation->frames[frameIndex];

      for (int collIndex = 0; collIndex < frame->count; collIndex++) {
        Collider* collider = &frame->colliders[collIndex];

        for (int j = 0; j < 4; j++) {
          collider->points[j].x += x;
          collider->points[j].y += y;
        }
      }
    }
  }
}

void sprite_update_colliders(Sprite* sprite) {
  Animation* animation = &sprite->animator.animations[sprite->animator.current];
  Frame* frame = &animation->frames[animation->current];

  for (int i = 0; i < frame->count; i++) {
    for (int j = 0; j < 4; j++) {
      frame->colliders[i].points[j].x += sprite->x;
      frame->colliders[i].points[j].y += sprite->y;
    }
  }
}

/**
 *
 */
void sprite_play_animation(Sprite* sprite, Uint16 animationIndex) {
  Animator* animator = &sprite->animator;

  if (animationIndex < animator->count) {
    Animation* anim = &animator->animations[animationIndex];

    int currentFrameIndex = 0;

    if (anim->duration > 0) {
      currentFrameIndex = (SDL_GetTicks() / anim->duration) % anim->count;
    }

    animator->current = animationIndex;
    anim->current = currentFrameIndex;
  }
}

SDL_FPoint sprite_get_size(Sprite* sprite) {
  Animation* anim = &sprite->animator.animations[sprite->animator.current];
  SDL_Rect frame = anim->frames[anim->current].frame;

  float w = frame.w * sprite->scale.x;
  float h = frame.h * sprite->scale.y;
  return (SDL_FPoint){w, h};
}

void sprite_add_collider(Sprite* sprite, Uint16 animationIndex,
                         Uint16 frameIndex, Uint16 colliderIndex, float x,
                         float y, float w, float h) {
  Collider* collider = &sprite->animator.animations[animationIndex]
                            .frames[frameIndex]
                            .colliders[colliderIndex];

  SDL_FPoint pos = sprite_get_position(sprite);

  const SDL_FPoint p1 = {pos.x + x, pos.y + y};
  const SDL_FPoint p2 = {p1.x + w, p1.y};
  const SDL_FPoint p3 = {p2.x, p2.y + h};
  const SDL_FPoint p4 = {p1.x, p1.y + h};

  collider->points[0] = p1;
  collider->points[1] = p2;
  collider->points[2] = p3;
  collider->points[3] = p4;
}

Sprite* sprite_create(const char* filename, Uint16 animationsCount) {
  Sprite* sprite = SDL_calloc(1, sizeof(*sprite));

  sprite->texture = texture_create_from_file(filename);
  sprite->flip = SDL_FLIP_NONE;
  sprite->angle = 0;
  sprite->pivot = (SDL_FPoint){0.5, 0.5};
  sprite->center = (SDL_FPoint){0, 0};
  sprite->scale = (SDL_FPoint){1, 1};

  if (sprite) {
    sprite->animator.count = animationsCount;
    sprite->animator.current = 0;

    sprite->animator.animations =
        SDL_calloc(animationsCount, sizeof(*sprite->animator.animations));
  }

  return sprite;
}

void sprite_destroy(Sprite* sprite) {
  if (sprite) {
    for (int i = 0; i < sprite->animator.count; i++) {
      for (int j = 0; j < sprite->animator.animations[i].count; j++) {
        SDL_free(sprite->animator.animations[i].frames[j].colliders);
      }

      SDL_free(sprite->animator.animations[i].frames);
    }

    SDL_free(sprite->animator.animations);
  }

  SDL_DestroyTexture(sprite->texture);
  SDL_free(sprite);
}

void sprite_add_animation(Sprite* sprite, Uint16 animationIndex,
                          Uint16 framesCount, Uint16 duration) {
  if (sprite && sprite->animator.animations) {
    if (animationIndex < sprite->animator.count) {
      sprite->animator.animations[animationIndex].count = framesCount;
      sprite->animator.animations[animationIndex].current = 0;
      sprite->animator.animations[animationIndex].duration = duration;
      sprite->animator.animations[animationIndex].frames = SDL_calloc(
          framesCount,
          sizeof(*sprite->animator.animations[animationIndex].frames));
    }
  }
}

void sprite_add_frame(Sprite* sprite, Uint16 animationIndex, Uint16 frameIndex,
                      Uint16 collidersCount, Uint32 x, Uint32 y, Uint32 w,
                      Uint32 h) {
  Frame* frame =
      &sprite->animator.animations[animationIndex].frames[frameIndex];

  frame->frame = (SDL_Rect){x, y, w, h};
  frame->count = collidersCount;
  frame->colliders = NULL;
  if (collidersCount > 0) {
    frame->colliders = SDL_calloc(collidersCount, sizeof(*frame->colliders));
  }
}

/**
 *
 */
void sprite_render(Sprite* sprite) {
  Animation* anim = &sprite->animator.animations[sprite->animator.current];
  Frame* frame = &anim->frames[anim->current];

  SDL_FPoint pos = sprite_get_position(sprite);
  SDL_FPoint size = sprite_get_size(sprite);

  SDL_FRect dest = {pos.x, pos.y, size.x, size.y};

  if (SDL_RenderCopyExF(renderer, sprite->texture, &frame->frame, &dest,
                        sprite->angle, &sprite->center, sprite->flip) != 0) {
    LOG("Error in render copy");
  }

  // sprite_update_colliders(sprite);

  for (int i = 0; i < frame->count; i++) {
    SDL_FPoint* p = frame->colliders[i].points;
    SDL_RenderDrawLineF(renderer, p[0].x, p[0].y, p[1].x, p[1].y);
    SDL_RenderDrawLineF(renderer, p[1].x, p[1].y, p[2].x, p[2].y);
    SDL_RenderDrawLineF(renderer, p[2].x, p[2].y, p[3].x, p[3].y);
    SDL_RenderDrawLineF(renderer, p[3].x, p[3].y, p[0].x, p[0].y);
  }
}