#include "Car_neutral.h"

void Car_neutral::spawn_car_neutral(Player player, Road road) {
    if (SDL_GetTicks() % 1000 < 20 && player.y_speed > 1.0) {
        exist = true;
        x_position = SCREEN_WIDTH / 2 - road.road_width[0] / 2 + SDL_GetTicks() % road.road_width[0];
    }
}

void Car_neutral::turn(Road road, int time) {
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
        int random = SDL_GetTicks();
        if (random % 7 == 2) x_speed = 1;
        else if (random % 7 == 1) x_speed = -1;
        else x_speed = 0;
        time_when_turned = time;
    }
}
void Car_neutral::draw_car(SDL_Surface* screen, double speed) {
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
    }
}
void Car_neutral::collision_front(Player player, int* time) {
    if (player.x_position - 25 < x_position && player.x_position + 25 > x_position && y_position + 102 > player.y_position) {
        y_position -= 100;
        *time = SDL_GetTicks();
    }
}
void Car_neutral::collision_side(Player player) {
    //uderzenie z lewej strony
    if (y_position > player.y_position - 50 && x_position > player.x_position + 44 && x_position < player.x_position + 48) {
        x_position += 100;
    }
    if (y_position > player.y_position - 50 && x_position < player.x_position - 44 && x_position > player.x_position - 48) {
        x_position -= 100;
    }
}

void Car_neutral::car_on_road(Road road, double* distance) {
    if (x_position<SCREEN_WIDTH / 2 - road.road_width[y_position] / 2 - 25 || x_position > SCREEN_WIDTH / 2 + road.road_width[y_position] / 2 + 25) {
        exist = false;
        *distance -= 10;
    }
}
void Car_neutral::remove() {
    y_position = 20;
    exist = false;
}