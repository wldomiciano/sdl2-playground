#include "tinyframework.h"

static Sprite*   ship        = NULL;
static Sprite*   bullet      = NULL;
static SDL_bool  ready       = SDL_TRUE;
static const int shipSpeed   = 3;
static const int bulletSpeed = 6;
static vec2      bulletVel   = {0, 0};

static void create() {
  bullet = createSprite(NULL, "/assets/images/bullet.bmp", NULL);
  setSpriteOrigin(bullet, VEC2(5, 20));
  setSpritePosition(bullet, VEC2(200, 120));
  setSpriteGlogalPivot(bullet, VEC2(200, 200));

  ship = createSprite(NULL, "/assets/images/image.bmp", NULL);
  setSpriteOrigin(ship, VEC2(25, 25));
  setSpritePosition(ship, VEC2(200, 200));
  setSpriteGlogalPivot(ship, VEC2(200, 200));
}

static void draw() {
  drawSprite(bullet);
  drawSprite(ship);
}

static void destroy() {
  destroySprite(bullet);
  destroySprite(ship);
}

static void update() {
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

  const vec2  delta = sub(getMousePosition(), getSpritePosition(ship));
  const float rot   = rotation(delta) + /* fix sprite rotation */ 90;
  setSpriteRotation(ship, rot);

  if (ready) {
    bulletVel = mul(normal(delta), bulletSpeed);
    setSpriteRotation(bullet, rot);
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
}

int main(int argc, char** argv) {
  initializeAllWithContext(0, 0, "Hello", 400, 400, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, SDL_RENDERER_PRESENTVSYNC);

  create();

  while (wasQuitNotRequested()) {
    handleEvents();

    update();

    clearRender(NULL, 0, 0, 0, 255);

    draw();

    presentRender(NULL);
  }

  destroy();

  return EXIT_SUCCESS;
}
