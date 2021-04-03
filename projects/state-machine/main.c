#include "SceneManager.h"
#include "tinyframework.h"

Scene* constructScene1();
Scene* constructScene2();
Scene* constructScene3();

static void create() {
  SceneManagerPushScene(constructScene1());
}

static void update() {
  // if (wasKeyJustPressed(SDL_SCANCODE_A)) {
  //   SceneManagerPushScene(constructScene1());
  // } else if (wasKeyJustPressed(SDL_SCANCODE_S)) {
  //   SceneManagerPushScene(constructScene2());
  // } else if (wasKeyJustPressed(SDL_SCANCODE_D)) {
  //   SceneManagerPushScene(constructScene3());
  // }

  SceneManagerUpdate();
}

static void draw() {
  SceneManagerDraw();
}

static void destroy() {
  SceneManagerDestroy();
}

#include "window.h"

int main() {
  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

  Window* const window = WindowCreate();

  while (WindowIsOpened(window)) {
    SDL_PumpEvents();
    WindowClear(window);
    WindowPresent(window);
  }

  WindowDestroy(window);

  // WindowClose(window);

  // initializeAllWithContext(0, 0, "Hello", 400, 400, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, SDL_RENDERER_PRESENTVSYNC);

  // create();

  // while (wasQuitNotRequested()) {
  //   handleEvents();

  //   update();

  //   clearRender(NULL, 0, 0, 0, 255);

  //   draw();

  //   presentRender(NULL);
  // }

  // destroy();

  return 0;
}
