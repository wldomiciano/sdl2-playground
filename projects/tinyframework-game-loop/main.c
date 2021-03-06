#include "tinyframework.h"

int main(__attribute__((unused)) int argc, __attribute__((unused)) char** argv) {
  initializeAllWithContext(0, 0, "Hello", 400, 400, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, SDL_RENDERER_PRESENTVSYNC);

  Sprite* const ship     = createSprite(NULL, "/assets/images/image.bmp", NULL);
  float         velocity = 900;

  const double DT       = 1 / 60.0;
  double       previous = getTicks();
  double       lag      = 0;

  while (wasQuitNotRequested()) {
    const double current = getTicks();
    const double delta   = current - previous;

    lag += delta;
    previous = current;

    handleEvents();

    while (lag >= DT) {
      const vec2 pos = moveSprite(ship, VEC2(velocity * (float) DT, 0));
      if (pos.x + 50 >= 500 || pos.x <= 0) velocity = -velocity;
      lag -= DT;
    }

    clearRender(NULL, 0, 0, 0, 255);
    drawSprite(ship);
    presentRender(NULL);
  }

  // create_game(500, 300);

  // SDL_Rect rect = {0, 0, 50, 50};
  // float velocity = 1000;

  // const float DT = 1 / 60.0;
  // float previous = getTicks();
  // float current = 0;
  // float delta = 0;
  // float lag = 0;

  // while (is_running()) {
  //   current = getTicks();
  //   delta = current - previous;
  //   lag += delta;
  //   previous = current;

  //   handle_input();

  //   while (lag >= DT) {
  //     rect.x += velocity * DT;
  //     if (rect.x + rect.w >= 500 || rect.x <= 0) velocity = -velocity;
  //     lag -= DT;
  //   }

  //   render_clear();
  //   draw_rect(&rect);
  //   render_present();
  // }

  // destroy_game();

  return 0;
}
