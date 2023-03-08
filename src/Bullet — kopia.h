#pragma once
#include "const.h"
#include "Car_neutral.h"
#include "Car_enemy.h"
class Bullet {
public:
    const int width = 3;
    const int height = 50;
    int x_position = 0;
    int y_position = 0;
    bool exist = false;
    void shot(SDL_Surface* screen, Player* player);
    void kill(Car_neutral* car_neutral_1, Car_neutral* car_neutral_2, Car_enemy* car_enemy, double* distnace);
    void remove();
};
