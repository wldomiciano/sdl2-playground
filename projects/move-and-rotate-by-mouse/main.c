#include "utils.h"

const double PI = 3.14159265358979323846264338327950288;

int main() {
  create_game(400, 400);

  SDL_Surface* image = SDL_LoadBMP("./assets/images/image.bmp");
  SDL_Texture* quad = SDL_CreateTextureFromSurface(renderer, image);
  SDL_Rect quadRect = {175, 175, 50, 50};

  double angleDeg = 0;
  double angleRad = 0;

  while (is_running()) {
    handle_input();

    int x, y;
    SDL_GetMouseState(&x, &y);
    int delta_x = (quadRect.x + quadRect.w / 2) - x;
    int delta_y = (quadRect.y + quadRect.h / 2) - y;
    angleRad = SDL_atan2(delta_x, delta_y);
    angleDeg = angleRad * 180.0 / PI;

    double easingAmount = 0.03;
    double distance = SDL_sqrt(delta_x * delta_x + delta_y * delta_y);
    if (distance > 1) {
      double tempX = delta_x * easingAmount;
      double tempY = delta_y * easingAmount;

      quadRect.x -= (tempX < 0) ? SDL_floor(tempX) : tempX;
      quadRect.y -= (tempY < 0) ? SDL_floor(tempY) : tempY;
    }

    render_clear();
    SDL_RenderCopyEx(renderer, quad, NULL, &quadRect, -angleDeg, NULL,
                     SDL_FLIP_NONE);
    render_present();
  }

  destroy_game();
  return 0;
}
