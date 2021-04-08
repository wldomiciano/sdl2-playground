#include <SDL.h>

typedef struct Drawable {
  SDL_Texture* texture;
  SDL_Rect     src;
  SDL_Rect     dst;
  double       angle;
  struct {
    float x;
    float y;
  } scale;
  SDL_Point        center;
  SDL_RendererFlip flip;
} Drawable;

typedef struct SpriteSheet {
  SDL_Texture* texture;
  SDL_Rect*    sprites;
  Uint32       count;
} SpriteSheet;

typedef struct Sprite {
  SpriteSheet* sheet;
  SDL_Rect     frame;
} Sprite;

typedef struct Animation {
  float speed;
  int   current;
  int   count;
  int*  frames;
} Animation;

typedef struct AnimatedSprite {
  Sprite*    sprite;
  int        lastAnimation;
  Animation* animations;
} AnimatedSprite;

SDL_Texture* createTexture(SDL_Renderer* const renderer, const char* file) {
  SDL_Surface* surface = SDL_LoadBMP(file);

  if (surface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (texture) {
      return texture;
    }
  }

  return NULL;
}

SpriteSheet* createSpriteSheet(SDL_Renderer* const renderer, const char* file, int cols, int rows, int count) {
  SDL_Texture* texture = createTexture(renderer, file);

  if (texture) {
    int width, height, spriteWidth, spriteHeight;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    spriteWidth  = width / cols;
    spriteHeight = height / rows;

    SpriteSheet* sheet = SDL_malloc(sizeof(*sheet));

    if (sheet) {
      sheet->texture = texture;
      sheet->sprites = SDL_malloc(sizeof(*sheet->sprites) * count);
      sheet->count   = count;

      for (int i = 0, x = 0, y = 0; i < count; i++) {
        sheet->sprites[i].w = spriteWidth;
        sheet->sprites[i].h = spriteHeight;
        sheet->sprites[i].x = x++ * spriteWidth;
        sheet->sprites[i].y = y * spriteHeight;

        SDL_Log("%4d, %4d, %4d, %4d", sheet->sprites[i].x, sheet->sprites[i].y,
                sheet->sprites[i].w, sheet->sprites[i].h);

        if (x == cols) {
          x = 0;
          y++;
        }
      }

      return sheet;
    }
  }

  return NULL;
}

Sprite* createSprite(SpriteSheet* sheet, int frame) {
  Sprite* sprite = malloc(sizeof(*sprite));

  if (sprite) {
    sprite->sheet = sheet;
    sprite->frame = sheet->sprites[frame];
    return sprite;
  }

  return NULL;
}

AnimatedSprite* createAnimatedSprite(SpriteSheet* sheet, int frame, int count) {
  AnimatedSprite* sprite = SDL_malloc(sizeof(*sprite));

  if (sprite) {
    sprite->sprite        = createSprite(sheet, frame);
    sprite->animations    = SDL_malloc(sizeof(*sprite->animations) * count);
    sprite->lastAnimation = -1;
    return sprite;
  }

  return NULL;
}

void addAnimation(AnimatedSprite* sprite, int index, int frames, float speed, ...) {
  sprite->animations[index].count   = frames;
  sprite->animations[index].speed   = speed;
  sprite->animations[index].current = 0;
  sprite->animations[index].frames  = SDL_malloc(sizeof(*sprite->animations[index].frames) * frames);

  va_list args;
  va_start(args, speed);

  for (int i = 0; i < frames; i++) {
    sprite->animations[index].frames[i] = va_arg(args, int);
  }

  va_end(args);
}

void playAnimation(AnimatedSprite* sprite, int index) {
  if (sprite->lastAnimation != index) {
    sprite->lastAnimation             = index;
    sprite->animations[index].current = 0;
  }

  int c                 = sprite->animations[index].count;
  sprite->sprite->frame = sprite->sprite->sheet->sprites[sprite->animations[index].frames[(int) (sprite->animations[index].current * sprite->animations[index].speed)]];
  sprite->animations[index].current++;

  if ((int) (sprite->animations[index].current * sprite->animations[index].speed) == c)
    sprite->animations[index].current = 0;
}

int main(int argc, char** argv) {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* const     window   = SDL_CreateWindow("Teste", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
  SDL_Renderer* const   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  SpriteSheet* const    sheet    = createSpriteSheet(renderer, "./assets/images/link.bmp", 10, 4, 40);
  AnimatedSprite* const sprite   = createAnimatedSprite(sheet, 0, 5);

  addAnimation(sprite, 0, 1, 1, 0);
  addAnimation(sprite, 1, 10, 0.5, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19);
  addAnimation(sprite, 2, 10, 0.2, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39);
  addAnimation(sprite, 3, 10, 0.2, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29);
  addAnimation(sprite, 4, 10, 0.2, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);

  while (!SDL_QuitRequested()) {
    SDL_PumpEvents();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A])
      playAnimation(sprite, 1);
    else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D])
      playAnimation(sprite, 2);
    else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W])
      playAnimation(sprite, 3);
    else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S])
      playAnimation(sprite, 4);
    else
      playAnimation(sprite, 0);

    SDL_RenderCopy(renderer, sprite->sprite->sheet->texture, &sprite->sprite->frame, NULL);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
