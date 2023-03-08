#include "Obstacle.h"

void Obstacle::draw_obstacle(SDL_Surface* screen, double speed) {
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
void Obstacle::spawn_obstacle(Road road) {
    if (!exist) {
        int random = SDL_GetTicks();
        if (random % 221 == 5) {
            exist = true;
            x_position = SCREEN_WIDTH / 2 - road.road_width[0] / 2 + SDL_GetTicks() % road.road_width[0];
        }
    }
}
int Obstacle::slip(Player player) {
    //Jesli kaluza znajduje sie w poblizu auta
    if (y_position - 30 < player.y_position && y_position + 30 > player.y_position) {
        if (x_position - 30 < player.x_position && x_position + 30 > player.x_position) {
            //zaleznie z ktorej strony auta jest kaluza, w ta strone poslizgnie sie samochod
            exist = false;
            y_position = 20;
            if (x_position < player.x_position) {
                return 70;
            }
            else {
                return -70;
            }

        }
    }
    return 0;
}
void Obstacle::remove() {
    y_position = 20;
    exist = false;
}