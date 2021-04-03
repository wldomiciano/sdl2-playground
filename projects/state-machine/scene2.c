#include "SceneManager.h"
#include "tinyframework.h"

Scene* constructScene1();
Scene* constructScene2();
Scene* constructScene3();

typedef struct {
  Scene base;

  Uint8 r, g, b;

  SDL_Rect rect;
} Scene2;

static SDL_Renderer* renderer;

static void create(Scene* const scene) {
  SDL_Log("creating Scene 2");
  renderer = getDefaultContext()->renderer;
}

static void update(Scene* const scene) {
  if (wasKeyJustPressed(SDL_SCANCODE_Z)) {
    SceneManagerPopScene();
  }
}

static void draw(Scene* const scene) {
  Scene2* const s = (Scene2*) scene;
  SDL_SetRenderDrawColor(renderer, s->r, s->g, s->b, 255);
  SDL_RenderFillRect(renderer, &s->rect);
}

static void destroy(Scene* const scene) {
  SDL_Log("destroying Scene 2");
}

Scene* constructScene2() {
  Scene2* const scene = SDL_malloc(sizeof(*scene));

  scene->base = (Scene){ALL, create, update, draw, destroy};
  scene->r    = 0;
  scene->g    = 255;
  scene->b    = 0;
  scene->rect = (SDL_Rect){100, 100, 50, 50};

  return &scene->base;
}
