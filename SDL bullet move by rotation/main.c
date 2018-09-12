#include "utils.h"

int main(int argc, char** argv) {
    create_game(400, 400);
    SDL_Rect screen = {-10, -10, 420, 420 };
    SDL_Texture* ship   = load_texture_from_file("image.bmp");
    SDL_Texture* bullet = load_texture_from_file("bullet.bmp");

    SDL_Rect shipRect   = { 175 , 175, 50, 50};
    SDL_Rect bulletRect = { shipRect.x + shipRect.w / 2 - 5 , shipRect.y - 25, 10, 20};
    SDL_Point bulletCenter = { bulletRect.w / 2, shipRect.h };
    double angle = 0;

    double velocityX = 0;
    double velocityY = 0;
    int angleSpeed = 15;
    int speed = 5;
    Uint32 time = SDL_GetTicks();
    while(is_running()) {
        handle_input();


        if( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && SDL_GetTicks() > time + 200) {
            angle += angleSpeed;
            //if (angle >= 360) angle = 0;
            time = SDL_GetTicks();
        } else if( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT] && SDL_GetTicks() > time + 200 ) {
            angle -= angleSpeed;
            //if (angle <   0) angle = 360 + angle;
            time = SDL_GetTicks();
        }

        if( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP] ) {
            float rad = angle * M_PI / 180;
            float directionX = -SDL_sinf(rad);
            float directionY = SDL_cosf(rad);
            //directionX = (directionX > 0) ? SDL_ceil(directionX) : SDL_floor(directionX);
            //directionY = (directionY > 0) ? SDL_ceil(directionY) : SDL_floor(directionY);

            velocityX = directionX * speed ;
            velocityY = directionY * speed ;
            SDL_Log("\nDeg: %f\nRad: %f\nDir: %f   |   %f\nVel: %f   |   %f", angle, rad, directionX, directionY, velocityX, velocityY);
        }
        else if( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN] ) {
            bulletRect.x = shipRect.x + shipRect.w / 2 - 5;
            bulletRect.y = shipRect.y - 25;
            velocityX  = velocityY  = 0;
        }

        if (!SDL_HasIntersection(&bulletRect, &screen)) {
            bulletRect.x = shipRect.x + shipRect.w / 2 - 5;
            bulletRect.y = shipRect.y - 25;
            velocityX  = velocityY  = 0;
        }

        bulletRect.x -= velocityX;
        bulletRect.y -= velocityY;

        render_clear();
        SDL_RenderCopyEx(renderer, ship, NULL, &shipRect, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, bullet, NULL, &bulletRect, angle, &bulletCenter, SDL_FLIP_NONE);
        render_present();
    }

    destroy_game();
    return 0;
}
