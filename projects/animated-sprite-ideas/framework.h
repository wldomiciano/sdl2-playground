#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <SDL.h>

#define LOG(message) SDL_Log("[%s] %s (%s)", __func__, message, SDL_GetError())

extern SDL_Renderer* renderer;

// Lifecycle functions
void create(void);
void update(void);
void destroy(void);

SDL_bool button_is_pressed(const int button);

SDL_Texture* texture_create_from_file(const char* const filename);

SDL_bool key_is_pressed(const SDL_Scancode code);
SDL_bool key_was_pressed(const SDL_Scancode code);

#endif  // !FRAMEWORK_H
