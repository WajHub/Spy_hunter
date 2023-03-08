#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include "Player.h"
#include "Road.h"
class Car_neutral {
public:
    SDL_Surface* car = SDL_LoadBMP("./car_neutral.bmp");
    int x_position = SCREEN_WIDTH / 2;
    int y_position = 0;
    int x_speed = 0;
    double y_speed = 1.0;
    bool exist = false;
    int time_when_turned = 0;
    //tworzymy samochod w losowym miejscu na drodze
    void spawn_car_neutral(Player player, Road road);
    //samochod czasem skreca, ale tak zeby nie wyjechal za droge
    void turn(Road road, int time);
    void draw_car(SDL_Surface* screen, double speed);
    void collision_front(Player player, int* time);
    void collision_side(Player player);
    void car_on_road(Road road, double* distance);
    void remove();
};