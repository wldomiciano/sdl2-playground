#include "context.h"
#include "events.h"
#include "initialization.h"
#include "math.h"
#include "miscellaneous.h"
#include "sprite.h"
#include "vector.h"

int main() {
  initializeAllWithContext(0, 0, "Hello", 400, 400, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, SDL_RENDERER_PRESENTVSYNC);

  Sprite* const ship = createSprite(NULL, "/assets/images/image.bmp", NULL);
  Sprite* const bullet = createSprite(NULL, "/assets/images/bullet.bmp", NULL);

  SDL_bool ready = SDL_TRUE;
  const int shipSpeed = 3;
  const int bulletSpeed = 6;

  setSpriteOrigin(bullet, VEC2(5, 20));
  setSpritePosition(bullet, VEC2(200, 120));
  setSpriteGlogalPivot(bullet, VEC2(200, 200));

  setSpriteOrigin(ship, VEC2(25, 25));
  setSpritePosition(ship, VEC2(200, 200));
  setSpriteGlogalPivot(ship, VEC2(200, 200));

  float bulletRot = 0;
  vec2 bulletVel = {0, 0};

  while (wasQuitNotRequested()) {
    handleEvents();

    if (isKeyPressed(SDL_SCANCODE_A)) {
      moveSprite(ship, VEC2(-shipSpeed, 0));
      if (ready) moveSprite(bullet, VEC2(-shipSpeed, 0));
    } else if (isKeyPressed(SDL_SCANCODE_D)) {
      moveSprite(ship, VEC2(shipSpeed, 0));
      if (ready) moveSprite(bullet, VEC2(shipSpeed, 0));
    }

    if (isKeyPressed(SDL_SCANCODE_W)) {
      moveSprite(ship, VEC2(0, -shipSpeed));
      if (ready) moveSprite(bullet, VEC2(0, -shipSpeed));
    } else if (isKeyPressed(SDL_SCANCODE_S)) {
      moveSprite(ship, VEC2(0, shipSpeed));
      if (ready) moveSprite(bullet, VEC2(0, shipSpeed));
    }

    const vec2 delta = sub(getSpritePosition(ship), getMousePosition());
    const double rot = rotation(delta);
    setSpriteRotation(ship, -rot);

    if (ready) {
      bulletRot = rot;
      bulletVel = mul(normal(VEC2(-delta.x, -delta.y)), bulletSpeed);
      setSpriteRotation(bullet, -bulletRot);
      ready = SDL_FALSE;
    }

    moveSprite(bullet, bulletVel);

    const vec2 pos = getSpritePosition(bullet);
    if (pos.x > 450 || pos.x < -50 || pos.y > 450 || pos.y < -50) {
      const vec2 pos = getSpritePosition(ship);
      setSpritePosition(bullet, pos);
      setSpriteGlogalPivot(bullet, pos);
      ready = SDL_TRUE;
    }

    clearRender(NULL, (SDL_Color){0, 0, 0, 255});
    drawSprite(bullet);
    drawSprite(ship);
    presentRender(NULL);
  }

  return 0;
}
