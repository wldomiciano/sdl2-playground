#ifndef SPRITE_H
#define SPRITE_H

typedef struct Sprite Sprite;

void sprite_add_frame(Sprite* sprite, Uint16 animationIndex, Uint16 frameIndex,
                      Uint16 collidersCount, Uint32 x, Uint32 y, Uint32 w,
                      Uint32 h);

Sprite* sprite_create(const char* filename, Uint16 animationsCount);

void sprite_add_animation(Sprite* sprite, Uint16 animationIndex,
                          Uint16 framesCount, Uint16 duration);

void sprite_add_collider(Sprite* sprite, Uint16 animationIndex,
                         Uint16 frameIndex, Uint16 colliderIndex, float x,
                         float y, float w, float h);

void sprite_move(Sprite* sprite, float x, float y);
void sprite_set_position(Sprite* sprite, float x, float y);
void sprite_rotate(Sprite* sprite, float deg);

void sprite_play_animation(Sprite* sprite, Uint16 animationIndex);
void sprite_set_scale(Sprite* sprite, float x, float y);

SDL_FPoint sprite_get_position(Sprite* sprite);
SDL_FPoint sprite_get_size(Sprite* sprite);
void sprite_destroy(Sprite* sprite);

void sprite_render(Sprite* sprite);

#endif  // !SPRITE_H