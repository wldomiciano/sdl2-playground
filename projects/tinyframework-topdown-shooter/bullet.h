#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>

void bullet_create(const SDL_FRect player, const float playerRotationRad, const float playerRotationDeg);
void bullet_init(void);
void bullet_update(void);

#endif
