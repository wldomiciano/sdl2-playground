#include <stdarg.h>

typedef struct {} Game;
typedef struct {} Scene;
typedef struct {} Config;

int defineScene(Scene);
Game createGame(Config);
Scene createScene();

DEFINE_SCENE(forest, update, create)

#define DEFINE_SCENE(NAME, ...)

int main() {
    Game* game = createGame((Config) {
        .windowTitle    = "teste",
        .windowPosition = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED },
        .rendererFlags  = SDL_RENDER_SYNC
    });


    setWindowTitle("teste");
    setWindowPosition(0, 0);
    setRenderFlags(RENDER_SYNC);
    int game = createGame();

    return runGame(game);

    setSceneUpdate(forest_update);
    setSceneCreate(forest_create);
    int scene = createScene();

    int forest = defineScene((Scene) {

    });

    Scene forest = {
        .update = forest_update,
        .create = forest_create
    }

    addScene(game, forest);


    return 0;
}