#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>

typedef struct Sprite Sprite;

void sprite_add_frame(const Sprite* const sprite, const Uint16 animationIndex, const Uint16 frameIndex, const Uint8 collidersCount, const int x, const int y, const int w, const int h);

Sprite* sprite_create(const char* const filename, const Uint8 animationsCount);

void sprite_add_animation(const Sprite* const sprite, const Uint16 animationIndex, const Uint8 framesCount, const Uint16 duration);

void sprite_add_collider(Sprite* const sprite, const Uint16 animationIndex, const Uint16 frameIndex, const Uint16 colliderIndex, const float x, const float y, const float w, const float h);

void sprite_move(Sprite* const sprite, const float x, const float y);
void sprite_set_position(Sprite* const sprite, const float x, const float y);
void sprite_rotate(Sprite* const sprite, const double deg);

void sprite_play_animation(Sprite* const sprite, const Uint8 animationIndex);
void sprite_set_scale(Sprite* const sprite, const float x, float y);

SDL_FPoint sprite_get_position(const Sprite* const sprite);
SDL_FPoint sprite_get_size(const Sprite* const sprite);
void       sprite_destroy(Sprite* const sprite);

void sprite_render(Sprite* const sprite);

#endif  // !SPRITE_H
