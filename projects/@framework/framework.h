#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <SDL.h>

#ifdef FRAMEWORK_NO_CONFIG
void config() {
}
#endif

#ifdef FRAMEWORK_NO_UPDATE
void update() {
}
#endif

#ifdef FRAMEWORK_NO_CREATE
void create() {
}
#endif

#ifdef FRAMEWORK_NO_DESTROY
void destroy() {
}
#endif

#define LOG(message) SDL_Log("[%s] %s (%s)", __func__, message, SDL_GetError())

extern const double PI;
extern const float TIMESTEP;

typedef struct Texture Texture;

// Getters
SDL_bool is_running();

// Lifecycle functions
void config();
void create();
void update();
void destroy();

// Config functions
void set_config_window_title(const char* title);
void set_config_window_size(const Uint32 width, const Uint32 height);
void set_config_window_position(const Uint32 x, const Uint32 y);
void set_config_window_flags(const Uint32 flags);
void set_config_renderer_flags(const Uint32 flags);
void set_config_main_loop(void (*loop)());

// Event listener functions
void add_events_listener(void (*fn)(const SDL_Event* event));
void add_keyboard_listener(void (*fn)(const SDL_KeyboardEvent* event));
void add_mouse_motion_listener(void (*fn)(const SDL_MouseMotionEvent* event));
void add_mouse_button_listener(void (*fn)(const SDL_MouseButtonEvent* event));
void add_mouse_wheel_listener(void (*fn)(const SDL_MouseWheelEvent* event));

// Drawing functions
void draw_filled_rect(const SDL_FRect* rect, const Uint32 color);
void draw_filled_rects(const SDL_FRect* rect, const Uint32 count,
                       const Uint32 color);
void draw_rect(const SDL_FRect* rect, const Uint32 color);
void draw_rects(const SDL_FRect* rect, const Uint32 count, const Uint32 color);
void draw_line(const SDL_FPoint* a, const SDL_FPoint* b, const Uint32 color);
void draw_lines(const SDL_FPoint* p, const Uint32 count, const Uint32 color);
void draw_point(const SDL_FPoint* p, const Uint32 color);
void draw_points(const SDL_FPoint* p, const Uint32 count, const Uint32 color);
void draw_texture(const SDL_Texture* texture);

// Text functions
Texture* create_texture_from_text(const char* text, const Uint32 size,
                                  const Uint32 color);

Texture* create_texture_rect(const float x, const float y, const Uint32 w,
                             const Uint32 h, Uint32 fill, Uint32 stroke);

//
SDL_bool is_key_pressed(SDL_Scancode code);
SDL_bool was_key_pressed(SDL_Scancode code);

#endif  // !FRAMEWORK_H