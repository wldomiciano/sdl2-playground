#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL.h>

typedef struct Pipes {
  SDL_Rect top;
  SDL_Rect bot;
} Pipes;

Pipes* create_pipes(Uint16 pipesCount);
void   draw_pipes(SDL_Renderer* renderer, SDL_Texture* texture, Pipes* pipes);
void   destroy_pipes(Pipes* pipes);
void   move_pipes(Pipes* pipes);

#endif  // GAME_H_INCLUDED
