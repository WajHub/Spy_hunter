#pragma once
#include "const.h"
#include "Drawing.h"
#include "Road.h"
#include "Player.h"
class Power_up {
public:
    SDL_Surface* bmp = SDL_LoadBMP("./gun.bmp");
    int x_position = SCREEN_WIDTH / 2;
    int y_position = 0;
    bool exist = false;
    void draw_power_up(SDL_Surface* screen, double speed);
    void spawn_power_up(Road road);
    void get_power(Player* player);
    void remove();
};
