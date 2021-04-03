#include "SceneManager.h"
#include "tinyframework.h"

Scene* constructScene1();
Scene* constructScene2();
Scene* constructScene3();

typedef struct {
  Scene base;

  Uint8 r, g, b;

  SDL_Rect rect;
} Scene1;

static SDL_Renderer* renderer;

static void create(Scene* const scene) {
  SDL_Log("creating Scene 1");
  renderer = getDefaultContext()->renderer;
}

static void update(Scene* const scene) {
  // Scene1* s = (Scene1*) scene;
  if (wasKeyJustPressed(SDL_SCANCODE_A)) {
    SceneHide(scene);
    SceneManagerPushScene(constructScene2());
  } else if (wasKeyJustPressed(SDL_SCANCODE_D)) {
    ScenePause(scene);
    SceneManagerPushScene(constructScene3());
  }
}

static void draw(Scene* const scene) {
  Scene1* const s = (Scene1*) scene;
  SDL_SetRenderDrawColor(renderer, s->r, s->g, s->b, 255);
  SDL_RenderFillRect(renderer, &s->rect);
}

static void destroy(Scene* const scene) {
  SDL_Log("destroying Scene 1");
}

Scene* constructScene1() {
  Scene1* const scene = SDL_malloc(sizeof(*scene));

  scene->base = (Scene){ALL, create, update, draw, destroy};
  scene->r    = 255;
  scene->g    = 0;
  scene->b    = 0;
  scene->rect = (SDL_Rect){0, 0, 50, 50};

  return &scene->base;
}
