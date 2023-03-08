#include "Power_up.h"

void Power_up::draw_power_up(SDL_Surface* screen, double speed) {
    if (speed > 1.0 && exist) {
        y_position += 7;
    }
    else if (speed < 1.0 && exist) {
        y_position += 1;
    }
    else if (exist) {
        y_position += 3;
    }
    if (y_position < SCREEN_HEIGHT - 20 && exist) {
        DrawSurface(screen, bmp, x_position, y_position);
    }
    else {
        y_position = 20;
        exist = false;
    }
}
void Power_up::spawn_power_up(Road road) {
    if (!exist) {
        int random = SDL_GetTicks();
        if (random % 421 == 7) {
            exist = true;
            x_position = SCREEN_WIDTH / 2 - road.road_width[0] / 2 + SDL_GetTicks() % road.road_width[0];
        }
    }
}
void Power_up::get_power(Player* player) {
    if (y_position - 30 < player->y_position && y_position + 30 > player->y_position) {
        if (x_position - 30 < player->x_position && x_position + 30 > player->x_position) {
            player->ammo_power_up += 10;
            exist = false;
            y_position = 20;
        }
    }
}

void Power_up::remove()
{
    y_position = 0;
    exist = false;
}