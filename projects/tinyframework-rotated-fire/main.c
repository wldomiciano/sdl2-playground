#include <SDL.h>
#include <float.h>

#include "tinyframework.h"

int main(__attribute__((unused)) int argc, __attribute__((unused)) char** argv) {
  initializeAllWithContext(0, 0, "Hello", 400, 400, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, SDL_RENDERER_PRESENTVSYNC);

  Sprite* const ship   = createSprite(NULL, "/assets/images/image.bmp", NULL);
  Sprite* const bullet = createSprite(NULL, "/assets/images/bullet.bmp", NULL);

  setSpriteOrigin(bullet, VEC2(5, 20));
  setSpritePosition(bullet, VEC2(200, 120));
  setSpriteGlogalPivot(bullet, VEC2(200, 200));

  setSpriteOrigin(ship, VEC2(25, 25));
  setSpritePivot(ship, VEC2(25, 25));
  setSpritePosition(ship, VEC2(200, 200));

  Uint32 time = SDL_GetTicks();

  const int angleSpeed = 15;

  const int speed = 5;

  vec2 velocity = {0, 0};

  Context* const ctx = getDefaultContext();

  while (wasQuitNotRequested()) {
    handleEvents();

    if (isKeyPressed(SDL_SCANCODE_RIGHT) && SDL_GetTicks() > time + 200) {
      rotateSprite(ship, angleSpeed);
      rotateSprite(bullet, angleSpeed);

      if (SDL_fabsf(getSpriteAngle(ship) - 360.f) < FLT_EPSILON) {
        setSpriteRotation(ship, 0);
      }

      time = SDL_GetTicks();
    } else if (isKeyPressed(SDL_SCANCODE_LEFT) && SDL_GetTicks() > time + 200) {
      rotateSprite(ship, -angleSpeed);
      rotateSprite(bullet, -angleSpeed);

      const float angle = getSpriteAngle(ship);
      if (angle < 0) setSpriteRotation(ship, (double) (360 + angle));

      time = SDL_GetTicks();
    }

    if (wasKeyJustPressed(SDL_SCANCODE_UP)) {
      const float rad       = deg2rad(getSpriteAngle(ship));
      const vec2  direction = rad2vec(rad);
      velocity              = mul(direction, speed);
    } else if (isKeyPressed(SDL_SCANCODE_DOWN)) {
      setSpritePosition(bullet, VEC2(200, 120));
      velocity = VEC2(0, 0);
    }

    moveSprite(bullet, velocity);

    clearRender(NULL, 0, 0, 0, 255);

    SDL_SetRenderDrawColor(ctx->renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(ctx->renderer, 0, 200, 400, 200);
    SDL_RenderDrawLine(ctx->renderer, 200, 0, 200, 400);
    SDL_RenderDrawLine(ctx->renderer, 0, 0, 400, 400);
    SDL_RenderDrawLine(ctx->renderer, 400, 0, 0, 400);

    drawSprite(bullet);
    drawSprite(ship);
    presentRender(NULL);
  }

  return 0;
}
