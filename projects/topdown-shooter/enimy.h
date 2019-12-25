#ifndef ENIMY_H
#define ENIMY_H

#include <SDL.h>

#define MAX_ENIMIES 10

typedef struct {
  SDL_bool active;
  SDL_FRect frame;
  float rotationRad;
  float rotationDeg;
} Enimy;

extern Enimy enimies[MAX_ENIMIES];

void enimy_create();
void enimy_init(SDL_FRect* player);
void enimy_update();

#endif