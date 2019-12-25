#include "framework.h"
#include <SDL.h>

static Game* game;

const double PI = 3.14159265358979323846264338327950288;

SDL_Rect game_window_frame() { return game->windowFrame; }

static void game_init(const char* const title, const Uint16 width,
                      const Uint16 height, stateFn create, stateFn update,
                      stateFn destroy) {
  game = SDL_calloc(1, sizeof(*game));

  game->create = create;
  game->update = update;
  game->destroy = destroy;
  game->windowFrame.w = width;
  game->windowFrame.h = height;
  game->windowFrame.x = SDL_WINDOWPOS_CENTERED;
  game->windowFrame.y = SDL_WINDOWPOS_CENTERED;

  game->window =
      SDL_CreateWindow("Hello", game->windowFrame.x, game->windowFrame.y,
                       game->windowFrame.w, game->windowFrame.h, 0);

  game->renderer =
      SDL_CreateRenderer(game->window, -1, SDL_RENDERER_PRESENTVSYNC);

  game->isRunning = SDL_TRUE;
}

static void game_quit() {
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
  SDL_free(game);
}

static void game_input() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      game->isRunning = SDL_FALSE;
    } else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        game->isRunning = SDL_FALSE;
      } else {
        if (event.key.repeat == 0) {
          SDL_Log("hello %d", event.key.keysym.sym);
        }
      }
    }
  }
}

static void game_update() {
  while (game->isRunning) {
    game_input();

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(game->renderer);

    // SDL_Texture* body =
    //     SDL_CreateTexture(game->renderer, SDL_PIXELFORMAT_RGBA8888,
    //                       SDL_TEXTUREACCESS_TARGET, frame.w, frame.h);
    // SDL_SetRenderTarget(game->renderer, body);
    // SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
    // SDL_RenderClear(game->renderer);
    // // SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
    // // SDL_RenderFillRect(game->renderer, &(SDL_Rect){10, 10, 10, 10});
    // SDL_SetRenderTarget(game->renderer, NULL);
    // SDL_RenderCopy(game->renderer, body, NULL, NULL);

    game->update();

    SDL_RenderPresent(game->renderer);
  }
}

Game* game_instance() { return game; }

int game_run(const char* const title, const Uint16 width, const Uint16 height,
             stateFn create, stateFn update, stateFn destroy) {
  game_init(title, width, height, create, update, destroy);

  game->create();

  game_update();

  game->destroy();

  game_quit();

  return 0;
}