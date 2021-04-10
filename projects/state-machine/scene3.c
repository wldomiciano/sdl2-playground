#include "SceneManager.h"
#include "tinyframework.h"

Scene* constructScene1(void);
Scene* constructScene2(void);
Scene* constructScene3(void);

typedef struct {
  Scene base;

  Uint8 r, g, b;

  SDL_Rect rect;
} Scene3;

static SDL_Renderer* renderer;

static void create(__attribute__((unused)) Scene* const scene) {
  SDL_Log("creating Scene 3");
  renderer = getDefaultContext()->renderer;
}

static void update(__attribute__((unused)) Scene* const scene) {
}

static void draw(Scene* const scene) {
  Scene3* const s = (Scene3*) scene;
  SDL_SetRenderDrawColor(renderer, s->r, s->g, s->b, 255);
  SDL_RenderFillRect(renderer, &s->rect);
}

static void destroy(__attribute__((unused)) Scene* const scene) {
  SDL_Log("destroying Scene 3");
}

Scene* constructScene3(void) {
  Scene3* const scene = SDL_malloc(sizeof(*scene));

  scene->base = (Scene){ALL, create, update, draw, destroy};
  scene->r    = 0;
  scene->g    = 0;
  scene->b    = 255;
  scene->rect = (SDL_Rect){200, 200, 50, 50};

  return &scene->base;
}
