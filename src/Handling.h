#pragma once
#include "Road.h";
#include "Player.h"
#include "Drawing.h"
#include "Obstacle.h"
#include "Car_neutral.h"
#include "Car_enemy.h"
#include "Obstacle.h"
#include "Bullet.h"
#include "Power_up.h"
#include "Game.h"
void event_handling(SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer,
    SDL_Event event, int* quit, int* t1, int* t2, double* worldTime, int* frames,
    double* fpsTimer, double* fps, double* distance, int* t3_pause, int* t_pause_begin,
    int* t_pause_end, bool* pause,
    Player* player, Road* road,
    Car_neutral* car_neutral_1, Car_neutral* car_neutral_2, Car_enemy* car_enemy_1, Bullet* bullet_1,
    Power_up* power_up, Obstacle* obstacle, float* scores[], int size);

void event_handling_pause(SDL_Surface* pauza, SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer,
    SDL_Event event, int* quit, int* t1, int* t2, double* worldTime, int* frames,
    double* fpsTimer, double* fps, double* distance, int* t3_pause, int* t_pause_begin,
    int* t_pause_end, bool* pause,
    Player* player, Road* road);

void time_handling(int* t1, int* t2, int* t3_pause, int* t_pause_begin, int* t_pause_end, double* delta, double* worldTime,
    double* fpsTimer, double* fps, int* frames);

void road_handling(SDL_Surface* screen, Road* road, Player player, int t2);
void obstacle_handling(SDL_Surface* screen, Obstacle* obstacle, Player* player, Road road);
void obstacle_handling(SDL_Surface* screen, Obstacle* obstacle, Player* player, Road road);
void power_up_handling(SDL_Surface* screen, Power_up* power_up, Player* player, Road road);

void cars_handling(SDL_Surface* screen, Car_neutral* car_neutral_1, Car_neutral* car_neutral_2, Car_enemy* car_enemy_1,
    Player* player, Road road, double* distance);
void bullet_handling(SDL_Surface* screen, Bullet* bullet_1, Player* player, Car_neutral* car_neutral_1, Car_neutral* car_neutral_2,
    Car_enemy* car_enemy_1, int* t2, double* worldTime, double* distance);
void player_handling(SDL_Renderer* renderer, SDL_Event event, SDL_Texture* scrtex, SDL_Surface* screen, SDL_Surface* charset,
    Player* player, Road road, int* quit, double* fps, char text[128],
    double* distance, double* delta, double* worldTime, int* t_pause_begin, int* t_pause_end, float* scores[], int size);