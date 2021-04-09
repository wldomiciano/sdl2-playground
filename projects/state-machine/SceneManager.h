#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

typedef struct SceneManager SceneManager;

typedef struct Scene Scene;

typedef void (*Func)(Scene* const scene);

typedef enum SceneStatus {
  UPDATING = 0x00001,
  DRAWING  = 0x00020,
  ALL      = UPDATING | DRAWING
} SceneStatus;

struct Scene {
  SceneStatus status;
  Func        create;
  Func        update;
  Func        draw;
  Func        destroy;
};

void ScenePause(Scene* const scene);

void SceneHide(Scene* const scene);

void SceneResume(Scene* const scene);

void SceneShow(Scene* const scene);

Scene* SceneManagerGetScene(void);

void SceneManagerPushScene(Scene* const scene);

void SceneManagerPopScene(void);

void SceneManagerChangeScene(Scene* const scene);

void SceneManagerDraw(void);

void SceneManagerUpdate(void);

void SceneManagerDestroy(void);

#endif  // SCENEMANAGER_H
