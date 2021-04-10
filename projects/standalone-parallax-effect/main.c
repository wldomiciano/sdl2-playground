#include <SDL.h>

typedef struct Texture {
  int          w;
  int          h;
  float        x;
  int          y;
  float        vel;
  SDL_Texture *texture;
} Texture;

static Texture createTexture(SDL_Renderer *const renderer, const char *const path, const float vel) {
  Texture texture;

  SDL_Surface *bitmap = SDL_LoadBMP(path);

  SDL_SetColorKey(bitmap, SDL_TRUE, SDL_MapRGB(bitmap->format, 0, 255, 255));

  texture.texture = SDL_CreateTextureFromSurface(renderer, bitmap);
  texture.w       = bitmap->w;
  texture.h       = bitmap->h;
  texture.x       = 0;
  texture.y       = 0;
  texture.vel     = vel;

  SDL_FreeSurface(bitmap);

  return texture;
}

static void drawTexture(SDL_Renderer *const renderer, Texture *const texture) {
  SDL_Rect rect = {(int) texture->x, texture->y, texture->w, texture->h};

  SDL_RenderCopy(renderer, texture->texture, NULL, &rect);

  rect.x += texture->w;

  SDL_RenderCopy(renderer, texture->texture, NULL, &rect);
}

static void moveTexture(Texture *const texture) {
  texture->x -= texture->vel;

  if (texture->x < (float) -texture->w) texture->x = 0;
}

static void movePlayer(SDL_Renderer *const renderer, Texture *const texture) {
  static float          frame    = 0;
  static const SDL_Rect position = {300, 350, 48, 37};
  static const SDL_Rect parts[5] = {
    {0, 0, 48, 37},
    {48, 0, 48, 37},
    {96, 0, 48, 37},
    {144, 0, 48, 37},
    {152, 0, 48, 37},
  };

  // frame = (frame / 4 > 4) ? 0 : ++frame;

  if (frame / 4 > 4)
    frame = 0;
  else
    frame++;

  SDL_RenderCopy(renderer, texture->texture, &parts[(int) frame / 5], &position);
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char **argv) {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *const   window   = SDL_CreateWindow("Test", 50, 50, 640, 480, 0);
  SDL_Renderer *const renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  SDL_bool            running  = SDL_TRUE;

  Texture chao       = createTexture(renderer, "./assets/images/chao.bmp", 15);
  Texture montanhas  = createTexture(renderer, "./assets/images/montanhas.bmp", 8);
  Texture montanhas2 = createTexture(renderer, "./assets/images/montanhas2.bmp", 5);
  Texture nuvens     = createTexture(renderer, "./assets/images/nuvens.bmp", 1);
  Texture sol        = createTexture(renderer, "./assets/images/sol.bmp", 0.5f);
  Texture player     = createTexture(renderer, "./assets/images/player.bmp", 0);

  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event))
      if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
        running = SDL_FALSE;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    drawTexture(renderer, &sol);
    drawTexture(renderer, &nuvens);
    drawTexture(renderer, &montanhas2);
    drawTexture(renderer, &montanhas);
    drawTexture(renderer, &chao);

    moveTexture(&sol);
    moveTexture(&nuvens);
    moveTexture(&montanhas2);
    moveTexture(&montanhas);
    moveTexture(&chao);

    movePlayer(renderer, &player);

    SDL_RenderPresent(renderer);
  }

  return 0;
}
