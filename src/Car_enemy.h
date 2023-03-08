#pragma once
#include "const.h"
#include "Car_neutral.h"
class Car_enemy : public Car_neutral {
public:
    SDL_Surface* car = SDL_LoadBMP("./car_enemy.bmp");
    int health = 5;
    void draw_car_neutral(SDL_Surface* screen, double speed);
    void car_on_road(Road road, double* distance);
    void turn(Road road, int time, Player player);
    void collision_side2(Player player, int* x_position_player);
    void remove();
};