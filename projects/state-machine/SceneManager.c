#include "SceneManager.h"

#include <stdbool.h>
#include <stdlib.h>

#define SCENE_MANAGER_CAPACITY 10

static Scene* scenes[SCENE_MANAGER_CAPACITY] = {0};
static size_t length                         = 0;

void ScenePause(Scene* const scene) {
  scene->status &= ~UPDATING;
}

void SceneHide(Scene* const scene) {
  scene->status &= ~DRAWING;
}

void SceneResume(Scene* const scene) {
  scene->status |= UPDATING;
}

void SceneShow(Scene* const scene) {
  scene->status |= DRAWING;
}

void SceneManagerPushScene(Scene* const scene) {
  if (length < SCENE_MANAGER_CAPACITY) {
    scenes[length++] = scene;
    scene->create(scene);
  }
}

Scene* SceneManagerGetScene(void) {
  return length > 0 ? scenes[length - 1] : NULL;
}

void SceneManagerPopScene(void) {
  if (length > 0) {
    Scene* const scene = scenes[--length];
    scene->destroy(scene);

    if (length > 0) {
      scenes[length - 1]->status = ALL;
    }
  }
}

void SceneManagerChangeScene(Scene* const scene) {
  SceneManagerPopScene();
  SceneManagerPushScene(scene);
}

void SceneManagerDraw(void) {
  for (size_t i = 0; i < length; i++) {
    if (scenes[i]->status & DRAWING) {
      scenes[i]->draw(scenes[i]);
    }
  }
}

void SceneManagerUpdate(void) {
  for (size_t i = 0; i < length; i++) {
    if (scenes[i]->status & UPDATING) {
      scenes[i]->update(scenes[i]);
    }
  }
}

void SceneManagerDestroy(void) {
  while (length) {
    SceneManagerPopScene();
  }
}
