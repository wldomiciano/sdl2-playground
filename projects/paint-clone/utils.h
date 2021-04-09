#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>

extern SDL_Renderer* renderer;

void         handle_input();
void         create_game(Uint32 width, Uint32 height);
void         destroy_game();
void         render_clear();
void         render_present();
SDL_bool     is_running();
float        getTicks();
void         set_viewport_fit(Uint32 width, Uint32 height);
void         draw_rect(const SDL_Rect* rect);
SDL_Texture* load_texture_from_file(const char* file);

#endif  // UTILS_H
