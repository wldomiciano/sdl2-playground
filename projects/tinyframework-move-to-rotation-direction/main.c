#include "tinyframework.h"

int main(__attribute__((unused)) int argc, __attribute__((unused)) char** argv) {
  initializeAllWithContext(0, 0, "Hello", 400, 400, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, SDL_RENDERER_PRESENTVSYNC);

  Sprite* const ship = createSprite(NULL, "/assets/images/image.bmp", NULL);

  Uint32 time = SDL_GetTicks();

  const int angleSpeed = 15;

  const int speed = 5;

  vec2 velocity = {0, 0};

  setSpriteOrigin(ship, VEC2(25, 25));
  setSpritePivot(ship, VEC2(25, 25));
  setSpritePosition(ship, VEC2(200, 200));

  while (wasQuitNotRequested()) {
    handleEvents();

    if (isKeyPressed(SDL_SCANCODE_RIGHT) && SDL_GetTicks() > time + 200) {
      rotateSprite(ship, angleSpeed);
      time = SDL_GetTicks();
    } else if (isKeyPressed(SDL_SCANCODE_LEFT) && SDL_GetTicks() > time + 200) {
      rotateSprite(ship, -angleSpeed);
      time = SDL_GetTicks();
    }

    if (isKeyPressed(SDL_SCANCODE_UP)) {
      const float rad = deg2rad(getSpriteAngle(ship));
      const vec2 direction = rad2vec(rad);
      velocity = mul(direction, speed);
    } else if (isKeyPressed(SDL_SCANCODE_DOWN)) {
      setSpritePosition(ship, VEC2(200, 200));
      velocity = VEC2(0, 0);
    }

    moveSprite(ship, velocity);

    clearRender(NULL, 0, 0, 0, 255);
    drawSprite(ship);
    presentRender(NULL);
  }

  return 0;
}
