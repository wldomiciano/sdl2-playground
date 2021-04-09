#ifndef ENIMY_H
#define ENIMY_H

#include <SDL.h>

#define MAX_ENIMIES 10

typedef struct {
  SDL_bool  active;
  SDL_FRect frame;
  float     rotationRad;
  float     rotationDeg;
} Enimy;

extern Enimy enimies[MAX_ENIMIES];

void enimy_create(void);
void enimy_init(const SDL_FRect* const player);
void enimy_update(void);

#endif
