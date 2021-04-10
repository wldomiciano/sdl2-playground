#include "miscellaneous.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "context.h"
#include "initialization.h"

double getTicks(void) {
  return SDL_GetTicks() / 1000.0;
}

void clearRender(Context* ctx, const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
  ctx = ctx ? ctx : getDefaultContext();
  SDL_SetRenderDrawColor(ctx->renderer, r, g, b, a);
  SDL_RenderClear(ctx->renderer);
}

void presentRender(Context* ctx) {
  ctx = ctx ? ctx : getDefaultContext();
  SDL_RenderPresent(ctx->renderer);
}

char* makePath(const char* path) {
  const char*  basePath       = getAppBasePath();
  const size_t basePathLength = getAppBasePathLength();
  const size_t pathLength     = SDL_strlen(path);
  char*        result         = SDL_calloc(basePathLength + pathLength, sizeof(char));

  SDL_strlcpy(result, basePath, basePathLength);

  strncat(result, path, pathLength);

  return result;
}

TTF_Font* openFont(const char* const filename, const Uint16 size) {
  char*           path = makePath(filename);
  TTF_Font* const font = TTF_OpenFont(path, size);
  SDL_free(path);
  return font;
}

SDL_Texture* loadTexture(SDL_Renderer* const renderer, const char* const filename) {
  char*              path    = makePath(filename);
  SDL_Texture* const texture = IMG_LoadTexture(renderer, path);
  SDL_free(path);
  return texture;
}

SDL_Color hexToColor(const Uint32 color) {
  return (SDL_Color){
    .r = (color >> 24) & 0xFF,
    .g = (color >> 16) & 0xFF,
    .b = (color >> 8) & 0xFF,
    .a = (color) &0xFF,
  };
}
