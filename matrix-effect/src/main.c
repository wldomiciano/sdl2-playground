#include <SDL.h>
#include <SDL_ttf.h>

#define MAX_LENGTH 1024
#define FONT_SIZE 24

TTF_Font *font;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_bool isRunning = SDL_FALSE;

const int width = 400;
const int height = 400;
const float colWidth = FONT_SIZE;
int cols = 0;
int* ypos = NULL;

void drawText(int x, int y, const char* fmt, ...) {
    char buffer[MAX_LENGTH] = {0};

    va_list ap;
    va_start (ap, fmt);
    SDL_vsnprintf(buffer, MAX_LENGTH, fmt, ap);
    va_end (ap);

    SDL_Surface* text = TTF_RenderText_Solid(font, buffer, (SDL_Color) { 0, 255, 0, SDL_ALPHA_OPAQUE });
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(renderer, text);
    SDL_Rect dest = { x, y, 0, 0 };

    SDL_QueryTexture(textureText, NULL, NULL, &dest.w, &dest.h);
    SDL_FreeSurface(text);
    SDL_RenderCopy(renderer, textureText, NULL, &dest);
    SDL_DestroyTexture(textureText);
}

void init() {
  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    if (TTF_Init() == 0) {
      window = SDL_CreateWindow("Matrix", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

      if (window) {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

        if (renderer) {
          font = TTF_OpenFont("VT323.ttf", FONT_SIZE);

          if (font) {
            isRunning = SDL_TRUE;
          } else SDL_Log("Open font error: %s\n", TTF_GetError());
        } else SDL_Log("Renderer creation error: %s\n", SDL_GetError());
      } else SDL_Log("Window creation error: %s\n", SDL_GetError());
    } else SDL_Log("TTF init error: %s\n", TTF_GetError());
  } else SDL_Log("SDL init error: %s\n", SDL_GetError());
}

void quit() {
  SDL_free(ypos);
  TTF_CloseFont(font);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
}

void events() {
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      isRunning = SDL_FALSE;
    }
  }
}


void matrix() {
  for (int i = 0; i < cols; i++) {
    const char text = rand() % 128;
    const int x = i * colWidth;

    drawText(x, ypos[i], "%c", text);
    
    if (ypos[i] > 100 + rand() % 5000)
      ypos[i] = 0;
    else
      ypos[i] = ypos[i] + FONT_SIZE;
  }
}

int main() {
  init();

  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  cols = SDL_floor(width / colWidth) + 1;
  ypos = SDL_calloc(cols, sizeof(int));
  SDL_Rect rect = { 0, 0, width, height };

  while (isRunning) {
    events();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 32);
    SDL_RenderFillRect(renderer, &rect);

    matrix();

    SDL_RenderPresent(renderer);
    SDL_Delay(100);
  }

  quit();
  return 0;
}