#include "Bullet.h"

void Bullet::shot(SDL_Surface* screen, Player* player) {
    x_position = player->x_position;
    const int bialy = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
    if (player->ammo_power_up > 0) {
        if (y_position - 150 >= 0) {
            y_position -= 25;
        }
        else {
            player->ammo_power_up--;
            exist = false;
        }
    }
    else {
        if (y_position - 150 >= 200) {
            y_position -= 25;
        }
        else {
            player->ammo_power_up--;
            exist = false;
        }
    }
    DrawRectangle(screen, x_position, y_position, width, height, bialy, bialy);
}
void Bullet::kill(Car_neutral* car_neutral_1, Car_neutral* car_neutral_2, Car_enemy* car_enemy, double* distnace) {
    //jesli pocisk znajduej sie w podobnej pozycji x co samochod, a takze w podobnej pozycji y
    if (car_neutral_1->exist && (x_position > car_neutral_1->x_position - 25 && x_position < car_neutral_1->x_position + 25)) {
        if (y_position - car_neutral_1->y_position < 50) {
            car_neutral_1->exist = false;
            car_neutral_1->y_position = 0;
            *distnace -= 10;
            exist = false;
        }
    }
    if (car_neutral_2->exist && (x_position > car_neutral_2->x_position - 25 && x_position < car_neutral_2->x_position + 25)) {
        if (y_position - car_neutral_2->y_position < 50) {
            car_neutral_2->exist = false;
            car_neutral_2->y_position = 0;
            *distnace -= 10;
            exist = false;
        }
    }
    if (car_enemy->exist && (x_position > car_enemy->x_position - 25 && x_position < car_enemy->x_position + 25)) {
        if (y_position - car_enemy->y_position < 50) {
            car_enemy->health--;
            exist = false;
            if (car_enemy->health == 0) {
                car_enemy->exist = false;
                car_enemy->y_position = 0;
                car_enemy->health = 5;
                *distnace += 10;

            }
        }
    }
}

void Bullet::remove()
{
    y_position = 0;
    exist = false;
}