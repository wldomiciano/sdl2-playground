#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <SDL.h>

#define LOG(message) SDL_Log("[%s] %s (%s)", __func__, message, SDL_GetError())

extern SDL_Renderer* renderer;

// Lifecycle functions
void create();
void update();
void destroy();

SDL_bool button_is_pressed(int button);

SDL_Texture* texture_create_from_file(const char* filename);

SDL_bool key_is_pressed(SDL_Scancode code);
SDL_bool key_was_pressed(SDL_Scancode code);

#endif  // !FRAMEWORK_H
