#include "framework.h"
#include "player.h"

static void create() {
  player_create();
  SDL_Log("create");
}

static void update() {
  player_update();
}

static void destroy() {
  player_destroy();
  SDL_Log("destroy");
}

int main(int argc, char** argv) {
  return game_run("Hello", 400, 400, create, update, destroy);
}
