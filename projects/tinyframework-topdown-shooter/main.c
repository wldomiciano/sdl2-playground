#include "player.h"
#include "tinyframework.h"

int main() {
  initializeAllWithContext(0, 0, "Hello", 400, 400, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, SDL_RENDERER_PRESENTVSYNC);

  player_create();

  while (wasQuitNotRequested()) {
    handleEvents();

    clearRender(NULL, 0, 0, 0, 255);

    player_update();

    presentRender(NULL);
  }

  player_destroy();

  return 0;
}
