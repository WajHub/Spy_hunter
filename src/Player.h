#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include "const.h"
#include "Road.h"
#include "Drawing.h"
class Player {
public:
    SDL_Surface* car = SDL_LoadBMP("./car.bmp");
    int x_position = SCREEN_WIDTH / 2;
    const int y_position = 5 * SCREEN_HEIGHT / 6;
    int points = 0;
    //jesli -1 to skreca w lewo, 0 jedzie prosto, 1 skreca w prawo
    int x_speed = 0;
    double y_speed = 1.0;
    bool unlimited_cars = true;
    int amount_cars = 3;
    int time_collision_front = 0;
    int ammo_power_up = 0;
    int points_to_get_car = 1000;
    void add_time_point(double distance);

    void destroy_car(SDL_Texture* scrtex, SDL_Surface* screen, SDL_Renderer* renderer, SDL_Surface* charset,
        Road road, double worldTime, double fps, char text[128], float* scores[], int size);

    //funckja sprawdza czy samochod jest na drodze, zwraca 0 jesli jest poza droga i auto zostaje zniszczone
    //zwraca 1 jesli dotyka pobocza (samochod zwalnia, punkty nie sa przyznawane) 2 jesli jest na drodze
    int car_on_road(Road road);
    //void accelerate(int time,double worldTime) {
    //      if(time - time_collision_front>3000 || worldTime<=3.0) y_speed = 2.0;
    //      else y_speed = 1.0;
    //}
    bool no_collision(int time, double worldTime);
};
