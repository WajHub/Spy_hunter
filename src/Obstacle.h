#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include "const.h"
#include"Player.h"
#include "Road.h"
class Obstacle {
public:
    SDL_Surface* bmp = SDL_LoadBMP("./obstacle.bmp");
    int x_position = SCREEN_WIDTH / 2;
    int y_position = 20;
    bool exist = false;
    void draw_obstacle(SDL_Surface* screen, double speed);
    void spawn_obstacle(Road road);
    int slip(Player player);
    void remove();
};