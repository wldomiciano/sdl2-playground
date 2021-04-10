#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>

extern SDL_Renderer* renderer;

void         handle_input(void);
void         create_game(int width, int height);
void         destroy_game(void);
void         render_clear(void);
void         render_present(void);
SDL_bool     is_running(void);
double       getTicks(void);
void         set_viewport_fit(int width, int height);
void         draw_rect(const SDL_Rect* rect);
SDL_Texture* load_texture_from_file(const char* file);

#endif  // UTILS_H
