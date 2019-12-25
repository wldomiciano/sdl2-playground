#include "game.h"
#include <SDL.h>
#include "framework.h"
#include "player.h"

Game* game;

void create() {
  game = game_instance();

  player_create();
  SDL_Log("create");
}

void update() {
  player_update();

    // SDL_Log("update");
}

void destroy() {
  player_destroy();
  SDL_Log("destroy");
}