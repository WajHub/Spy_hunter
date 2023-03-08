#pragma once
#include "Road.h";
#include "Player.h"
#include "Obstacle.h"
#include "Car_neutral.h"
#include "Car_enemy.h"
#include "Obstacle.h"
#include "Bullet.h"
#include "Power_up.h"

void save_score(Player player, double worldTime);
void start_game(int* t1, int* t3_pause, int* t_pause_begin, int* t_pause_end, int* frames,
    double* fpsTimer, double* fps, int* quit, double* worldTime, double* distance, Player* player, Road* road,
    Car_neutral* car_neutral_1, Car_neutral* car_neutral_2, Car_enemy* car_enemy_1, Bullet* bullet_1,
    Power_up* power_up, Obstacle* obstacle);
void end_game(SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Event event,
    Player player, int* quit, double worldTime);
