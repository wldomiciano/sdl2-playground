#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>

#include "context.h"
#include "vector.h"

typedef struct Sprite Sprite;

// ACTIONS

Sprite* createSprite(Context* ctx, const char* const filename, const SDL_Rect* const rect);

void destroySprite(Sprite* const sprite);

void drawSprite(Sprite* const sprite);

void rotateSprite(Sprite* const sprite, const double deg);

vec2 moveSprite(Sprite* const sprite, const vec2 v);

// SETTERS

void setSpriteRotation(Sprite* const sprite, const double deg);

void setSpritePivot(Sprite* const sprite, const vec2 v);

void setSpriteGlogalPivot(Sprite* const sprite, const vec2 v);

void setSpritePosition(Sprite* const sprite, const vec2 v);

void setSpriteOrigin(Sprite* const sprite, const vec2 v);

// GETTERS

float getSpriteAngle(Sprite* const sprite);

vec2 getSpritePivot(Sprite* const sprite);

vec2 getSpritePosition(Sprite* const sprite);

#endif  // SPRITE_H
