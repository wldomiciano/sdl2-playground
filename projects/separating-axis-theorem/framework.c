#include "framework.h"

#include <float.h>

SDL_Window*   window;
SDL_Renderer* renderer;
SDL_bool      isRunning;

void init(void) {
  SDL_Init(SDL_INIT_VIDEO);
  window   = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  isRunning = SDL_TRUE;
}

void quit(void) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void input(void) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      isRunning = SDL_FALSE;
    } else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        isRunning = SDL_FALSE;
      }
    }
  }

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
}

void present(void) {
  SDL_RenderPresent(renderer);
}

Rect* create_rect(float x, float y, float w, float h, Uint32 fill,
                  Uint32 border) {
  SDL_FRect    rect    = {x, y, w, h};
  SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, (int) rect.w, (int) rect.h);

  SDL_SetRenderTarget(renderer, texture);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_ADD);

  if (fill > 0) {
    const Uint8 r = (fill >> 24) & 0xFF;
    const Uint8 g = (fill >> 16) & 0xFF;
    const Uint8 b = (fill >> 8) & 0xFF;
    const Uint8 a = fill & 0xFF;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, NULL);
  }

  if (border > 0) {
    SDL_FPoint points[8] = {
      {0, 0},
      {rect.w - 1, 0},
      {rect.w - 1, rect.h - 1},
      {0, rect.h - 1},
      {0, 0},
    };

    const Uint8 r = (border >> 24) & 0xFF;
    const Uint8 g = (border >> 16) & 0xFF;
    const Uint8 b = (border >> 8) & 0xFF;
    const Uint8 a = border & 0xFF;

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawLinesF(renderer, points, 5);
  }

  SDL_SetRenderTarget(renderer, NULL);

  Rect* myRect    = SDL_malloc(sizeof(*myRect));
  myRect->angle   = 0;
  myRect->center  = (SDL_FPoint){rect.w * 0.5f, rect.h * 0.5f};
  myRect->dest    = rect;
  myRect->flip    = SDL_FLIP_NONE;
  myRect->texture = texture;
  return myRect;
}

void destroy_rect(Rect* rect) {
  SDL_DestroyTexture(rect->texture);
  SDL_free(rect);
}

typedef struct {
  SDL_FPoint points[5];
} Vertices;

static Vertices rect_get_vertices(const SDL_FRect* rect, double angle) {
  const float startX = rect->x;
  const float startY = rect->y;
  const float rad    = (float) ((angle * M_PI) / 180);
  const float cos    = SDL_cosf(rad);
  const float sin    = SDL_sinf(rad);
  const float w      = rect->w - 1;
  const float h      = rect->h - 1;

  const SDL_FPoint UL       = {rect->x, rect->y};
  const SDL_FPoint UR       = {rect->x + w, rect->y};
  const SDL_FPoint LL       = {rect->x, rect->y + h};
  const SDL_FPoint LR       = {rect->x + w, rect->y + h};
  Vertices         vertices = {{UL, UR, LR, LL, UL}};

  for (int i = 0; i < 5; i++) {
    const float cx = (startX + w * 0.5f);
    const float cy = (startY + w * 0.5f);
    const float x  = vertices.points[i].x - cx;
    const float y  = vertices.points[i].y - cy;

    vertices.points[i] = (SDL_FPoint){(x * cos - y * sin) + cx, (x * sin + y * cos) + cy};
  }

  return vertices;
}

static Vertices rect_get_normals(const Vertices* vert) {
  Vertices normals = {0};

  for (int i = 0; i < 5; i++) {
    SDL_FPoint a = vert->points[i];
    SDL_FPoint b = vert->points[i + 1 == 5 ? 0 : i + 1];
    SDL_FPoint c = {a.x - b.x, a.y - b.y};

    float const x       = c.x;
    float const y       = c.y;
    float const length  = SDL_sqrtf(x * x + y * y);
    normals.points[i].x = (y / length);
    normals.points[i].y = -(x / length);
  }

  return normals;
}

static SDL_FPoint projection(const SDL_FPoint axis, const Vertices* vert) {
  // dot product
  float min = axis.x * vert->points[0].x + axis.y * vert->points[0].y;
  float max = min;

  for (int i = 1; i < 4; i++) {
    const float p = axis.x * vert->points[i].x + axis.y * vert->points[i].y;
    if (p < min) {
      min = p;
    } else if (p > max) {
      max = p;
    }
  }

  return (SDL_FPoint){min, max};
}

static SDL_bool checkOverlap(const SDL_FPoint* a, const SDL_FPoint* b) {
  return a->y > b->x || a->x > b->y;
}

SDL_bool checkCollision(SDL_FRect* a, double angleA, const SDL_FRect* b,
                        double angleB) {
  //   const axisAll = [... a.normalizedAxis, ... b.normalizedAxis ];
  const Vertices va    = rect_get_vertices(a, angleA);
  const Vertices vb    = rect_get_vertices(b, angleB);
  const Vertices axisA = rect_get_normals(&va);
  const Vertices axisB = rect_get_normals(&vb);

  //   let overlap : number = Infinity;
  //   let smallest : Vector2;

  float      overlap  = FLT_MAX;
  SDL_FPoint smallest = {0, 0};

  for (int i = 0; i < 4; i++) {
    const SDL_FPoint p1 = projection(axisA.points[i], &va);
    const SDL_FPoint p2 = projection(axisA.points[i], &vb);

    if (!checkOverlap(&p1, &p2)) {
      return SDL_FALSE;
    } else {
      float o = FLT_MAX;

      if (p1.y > p2.x) {
        o = p1.y - p2.x;
      }

      if (o < overlap) {
        overlap  = o;
        smallest = axisA.points[i];
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    const SDL_FPoint p1 = projection(axisB.points[i], &va);
    const SDL_FPoint p2 = projection(axisB.points[i], &vb);

    if (!checkOverlap(&p1, &p2)) {
      return SDL_FALSE;
    } else {
      float o = FLT_MAX;

      if (p1.y > p2.x) {
        o = p1.y - p2.x;
      }

      if (o < overlap) {
        overlap  = o;
        smallest = axisB.points[i];
      }
    }
  }

  SDL_FPoint dist = {smallest.x * overlap, smallest.y * overlap};
  a->x -= dist.x;
  a->y -= dist.y;

  return SDL_TRUE;
}

void draw_rect(Rect* rect) {
  SDL_RenderCopyExF(renderer, rect->texture, NULL, &rect->dest, rect->angle, &rect->center, rect->flip);

  // Vertices v = rect_get_vertices(&rect->dest, rect->angle);
  // SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
  // SDL_RenderDrawLinesF(renderer, v.points, 5);

  // Vertices n = rect_get_normals(&v);
  // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  // SDL_RenderDrawLinesF(renderer, n.points, 5);
}
