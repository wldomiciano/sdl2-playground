#include "utils.h"

int main(int argc, char** argv) {
    create_game(500, 300);

    SDL_Rect rect = {0, 0, 50, 50};
    float velocity = 1000;

    const float DT = 1/60.0;
    float previous = getTicks();
    float current = 0;
    float delta = 0;
    float lag = 0;
    while(is_running()) {
        current = getTicks();
        delta = current - previous;
        lag += delta;
        previous = current;

        handle_input();


        while(lag >= DT) {
            rect.x += velocity * DT;
            if (rect.x + rect.w >= 500 || rect.x <= 0) velocity = -velocity;
            lag -= DT;
        }

        render_clear();
        draw_rect(&rect);
        render_present();
    }

    destroy_game();
    return 0;
}
