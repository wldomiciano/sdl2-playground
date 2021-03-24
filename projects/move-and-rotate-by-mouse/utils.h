#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <SDL2/SDL.h>

extern SDL_Renderer* renderer;

void handle_input();
void create_game(Uint32 width, Uint32 height);
void destroy_game();
void render_clear();
void render_present();
SDL_bool is_running();
float getTicks();
void set_viewport_fit(Uint32 width, Uint32 height);
void draw_rect(const SDL_Rect* rect);

#endif  // UTILS_H_INCLUDED
