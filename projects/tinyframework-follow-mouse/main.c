#include "tinyframework.h"

int main() {
  initializeAllWithContext(0, 0, "Hello", 400, 400, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, SDL_RENDERER_PRESENTVSYNC);

  Sprite* const ship = createSprite(NULL, "/assets/images/image.bmp", NULL);

  setSpriteOrigin(ship, VEC2(25, 25));
  setSpritePosition(ship, VEC2(200, 200));

  const float easingAmount = 0.03;

  while (wasQuitNotRequested()) {
    handleEvents();

    const vec2 delta = sub(getSpritePosition(ship), getMousePosition());
    setSpriteRotation(ship, -rotation(delta));

    if (len(delta) > 1) {
      const vec2 temp = mul(delta, easingAmount);

      const vec2 pos = {
        .x = -(temp.x < 0 ? SDL_floorf(temp.x) : temp.x),
        .y = -(temp.y < 0 ? SDL_floorf(temp.y) : temp.y),
      };

      moveSprite(ship, pos);
    }

    clearRender(NULL, (SDL_Color){0, 0, 0, 255});
    drawSprite(ship);
    presentRender(NULL);
  }

  return 0;
}