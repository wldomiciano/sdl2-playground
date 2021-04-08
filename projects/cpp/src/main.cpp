#include "Window.h"

class Scene {
public:
  virtual void create()             = 0;
  virtual void update()             = 0;
  virtual void draw(Window& window) = 0;
  virtual void destroy()            = 0;
};

class Stage1 : public Scene {
  const SDL_Rect rect = {0, 0, 100, 100};

public:
  void create() override {
    SDL_Log("create Stage1");
  }

  void update() override {
  }

  void draw(Window& window) override {
    window.draw(rect);
  }

  void destroy() override {
    SDL_Log("destroy Stage1");
  }
};

class Stage2 : public Scene {
  const SDL_Rect rect = {100, 100, 100, 100};

public:
  void create() override {
    SDL_Log("create Stage2");
  }

  void update() override {
  }

  void draw(Window& window) override {
    window.draw(rect);
  }

  void destroy() override {
    SDL_Log("destroy Stage2");
  }
};

class Stage3 : public Scene {
  const SDL_Rect rect = {200, 200, 100, 100};

public:
  void create() override {
    SDL_Log("create Stage3");
  }

  void update() override {
  }

  void draw(Window& window) override {
    window.draw(rect);
  }

  void destroy() override {
    SDL_Log("destroy Stage3");
  }
};

class Game {
  static Game* game;

  static Game& instance() {
    if (game == nullptr) {
      game = new Game();
    }

    return *game;
  }

  void handleEventsInternal() {
    SDL_Log("eee lasquera");
  }

public:
  static void handleEvents() {
    instance().handleEventsInternal();
  }
};

Game* Game::game = nullptr;

int main(__attribute__((unused)) int argc, __attribute__((unused)) char** argv) {
  Window a;

  Stage1 s1;
  Stage2 s2;
  Stage3 s3;

  Scene* curr = &s1;

  curr->create();

  Game::handleEvents();

  while (a.isOpened()) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        a.close();
      } else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
          a.close();
        } else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
          curr->destroy();
          curr = &s2;
          curr->create();
        }
      }
    }

    a.clear();

    // a.draw(rect);

    curr->draw(a);

    a.present();
  }

  curr->destroy();

  return 0;
}
