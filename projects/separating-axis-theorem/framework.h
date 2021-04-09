#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <SDL.h>

typedef struct {
  SDL_Texture*     texture;
  SDL_FRect        dest;
  double           angle;
  SDL_FPoint       center;
  SDL_RendererFlip flip;
} Rect;

void  init(void);
void  quit(void);
void  input(void);
void  present(void);
void  draw_rect(Rect* rect);
Rect* create_rect(float x, float y, float w, float h, Uint32 color,
                  Uint32 backColor);
void  destroy_rect(Rect* rect);

SDL_bool checkCollision(SDL_FRect* a, double angleA, const SDL_FRect* b,
                        double angleB);

extern SDL_bool      isRunning;
extern SDL_Window*   window;
extern SDL_Renderer* renderer;

#endif  // !FRAMEWORK_H
