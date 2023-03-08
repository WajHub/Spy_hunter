#include "Player.h"

void Player::add_time_point(double distance) {
    points = (int)distance * 50;
    if (points > points_to_get_car) {
        amount_cars++;
        points_to_get_car = points_to_get_car * 2;
    }
}
void Player::destroy_car(SDL_Texture* scrtex, SDL_Surface* screen, SDL_Renderer* renderer, SDL_Surface* charset,
    Road road, double worldTime, double fps, char text[128], float* scores[], int size) {
    int t_end = 0, t_begin = SDL_GetTicks();
    x_position = SCREEN_WIDTH / 2;
    //przez 2 sekundy samochod stoi w miejscu, punkty nie beda doliczane, i bedzie on migal (znak ze jest respawn)
    do {
        for (int i = 0; i < SCREEN_HEIGHT; i++) {
            DrawRectangle(screen, SCREEN_WIDTH / 2 - (road.road_width[i] / 2), i, road.road_width[i], 1, SZARY, SZARY);
        }
        draw_legend(screen, charset, scrtex, renderer, points,
            worldTime, fps, text, amount_cars, unlimited_cars, points_to_get_car, scores, size);
        t_end = SDL_GetTicks();
        if (t_end % 100 < 90) {
            DrawSurface(screen, car, x_position, y_position);
        }
        SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, scrtex, NULL, NULL);
        SDL_RenderPresent(renderer);
    } while (t_end - t_begin < 2000);
}
//funckja sprawdza czy samochod jest na drodze, zwraca 0 jesli jest poza droga i auto zostaje zniszczone
//zwraca 1 jesli dotyka pobocza (samochod zwalnia, punkty nie sa przyznawane) 2 jesli jest na drodze
int Player::car_on_road(Road road) {
    if (x_position<SCREEN_WIDTH / 2 - road.road_width[y_position] / 2 - 25 || x_position > SCREEN_WIDTH / 2 + road.road_width[y_position] / 2 + 25) {
        return 0;
    }
    else if (x_position<SCREEN_WIDTH / 2 - road.road_width[y_position] / 2 + 25 || x_position > SCREEN_WIDTH / 2 + road.road_width[y_position] / 2 - 25) {
        return 1;
    }
    return 2;
}
//void accelerate(int time,double worldTime) {
//      if(time - time_collision_front>3000 || worldTime<=3.0) y_speed = 2.0;
//      else y_speed = 1.0;
//}
bool Player::no_collision(int time, double worldTime) {
    if (time - time_collision_front > 3000 || worldTime <= 3.0) return true;
    else return false;
}