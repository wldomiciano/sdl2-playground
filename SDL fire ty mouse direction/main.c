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
    double bulletAngle = 0;

    double velocityX = 0;
    double velocityY = 0;
    int angleSpeed = 15;
    int shipSpeed = 3;
    int bulletSpeed = 6;
    Uint32 time = SDL_GetTicks();
    SDL_bool ready = SDL_TRUE;
    float directionX = 0, directionY = 0;
    while(is_running()) {
        handle_input();



        if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_A] ) {
            shipRect.x += -shipSpeed;
        } else if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_D] ) {
            shipRect.x += shipSpeed;
        } else if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_W] ) {
            shipRect.y += -shipSpeed;
        } else if ( SDL_GetKeyboardState(NULL)[SDL_SCANCODE_S] ) {            shipRect.y += shipSpeed;
        }

        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        int delta_x = (shipRect.x + shipRect.w / 2) - mouseX;
        int delta_y = (shipRect.y + shipRect.h / 2) - mouseY;
        double rad  = SDL_atan2(delta_x, delta_y);
        angle = -rad * 180.0 / M_PI;



        if (ready) {
        bulletAngle = angle;
        directionX = SDL_sinf(rad);
        directionY = SDL_cosf(rad);
        ready = SDL_FALSE;
        }
        velocityX = directionX * bulletSpeed ;
        velocityY = directionY * bulletSpeed ;
        bulletRect.x -= velocityX; bulletRect.y -= velocityY;
        if (!SDL_HasIntersection(&bulletRect, &screen)) {
            bulletRect.x = shipRect.x + shipRect.w / 2 - 5;
            bulletRect.y = shipRect.y - 25;
            velocityX  = velocityY  = 0;
            ready = SDL_TRUE;
        }




        render_clear();
        SDL_RenderCopyEx(renderer, ship, NULL, &shipRect, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderCopyEx(renderer, bullet, NULL, &bulletRect, bulletAngle, &bulletCenter, SDL_FLIP_NONE);
        render_present();
    }

    destroy_game();
    return 0;
}
