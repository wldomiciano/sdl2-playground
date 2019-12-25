#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>

void bullet_create(SDL_FRect player, float playerRotationRad,
                   float playerRotationDeg);
void bullet_init();
void bullet_update();

#endif