#include "Car_enemy.h"

void Car_enemy::draw_car_neutral(SDL_Surface* screen, double speed) {
    if (speed > 1.0 && exist) {
        y_position += 2;
    }
    else if (speed < 1.0 && exist) {
        y_position -= 1;
    }
    if (y_position < SCREEN_HEIGHT - 20 && exist && y_position > 50) {
        DrawSurface(screen, car, x_position, y_position);
    }
    else {
        y_position = 50;
        exist = false;
        health = 5;
    }
}
void Car_enemy::car_on_road(Road road, double* distance) {
    if (x_position<SCREEN_WIDTH / 2 - road.road_width[y_position] / 2 - 25 || x_position > SCREEN_WIDTH / 2 + road.road_width[y_position] / 2 + 25) {
        exist = false;
        *distance += 5;
    }
}
void Car_enemy::turn(Road road, int time, Player player) {
    if (x_speed == 1) x_position += 1;
    else if (x_speed == -1) x_position -= 1;
    //gdy znajduje sie blisko lewej krawedzi
    if (SCREEN_WIDTH / 2 - road.road_width[0] / 2 + 10 > x_position) {
        x_speed = 1;
        time_when_turned = time;
    }
    //gdy znajduje sie blisko prawej krawedzi
    else if (SCREEN_WIDTH / 2 + road.road_width[0] / 2 - 10 < x_position) {
        x_speed = -1;
        time_when_turned = time;
    }
    //samochod moze zmienic kierunek tylko gdy minie 0,5 sekundy
    if (time - time_when_turned > 500) {
        if (player.x_position > x_position) x_speed = 1;
        else if (player.x_position < x_position) x_speed = -1;
        else x_speed = 0;
        time_when_turned = time;
    }
}
void Car_enemy::collision_side2(Player player, int* x_position_player) {
    //uderzenie z prawej strony
    if (y_position > player.y_position - 50 && x_position > player.x_position + 44 && x_position < player.x_position + 48) {
        //jesli gracz uderza wroga
        if (player.x_speed == 1) {
            *x_position_player -= 20;
            x_position += 100;
        }
        else *x_position_player -= 100;
    }
    if (y_position > player.y_position - 50 && x_position < player.x_position - 44 && x_position > player.x_position - 48) {
        if (player.x_speed == -1) {
            *x_position_player += 20;
            x_position -= 100;
        }
        else *x_position_player += 100;
    }
}

void Car_enemy::remove() {
    y_position = 0;
    exist = false;
}