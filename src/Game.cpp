#include "Game.h"

void save_score(Player player, double worldTime) {
    int size = 0;
    //Odczytujemy rozmiar
    FILE* file_size;
    file_size = fopen("scores_size.txt", "r");
    if (file_size == NULL) {
        printf("Blad");
    }
    else {
        fscanf(file_size, "%d\n", &size);
    }
    size++;
    fclose(file_size);
    //zwiekszamy rozmiar
    file_size = fopen("scores_size.txt", "w+");
    if (file_size == NULL) {
        printf("Blad");
    }
    else {
        fprintf(file_size, "%d", size);
    }
    fclose(file_size);
    //zapisujemy wynik
    FILE* file_score;
    file_score = fopen("scores.txt", "a");
    if (file_score == NULL) {
        printf("Blad");
    }
    else {
        fprintf(file_score, "%d %.2f\n", player.points, worldTime);
    }
    fclose(file_score);
}


void start_game(int* t1, int* t3_pause, int* t_pause_begin, int* t_pause_end, int* frames,
    double* fpsTimer, double* fps, int* quit, double* worldTime, double* distance, Player* player, Road* road,
    Car_neutral* car_neutral_1, Car_neutral* car_neutral_2, Car_enemy* car_enemy_1, Bullet* bullet_1,
    Power_up* power_up, Obstacle* obstacle) {
    *t1 = SDL_GetTicks();
    *frames = 0;
    *fpsTimer = 0;
    *fps = 0;
    *quit = 0;
    *worldTime = 0;
    *distance = 0;
    player->y_speed = 1;
    player->amount_cars = 3;
    player->unlimited_cars = true;
    *t3_pause = 0;
    *t_pause_begin = 0;
    *t_pause_end = 0;
    road->set_road_width(380);
    player->x_position = SCREEN_WIDTH / 2;
    car_enemy_1->remove();
    car_neutral_1->remove();
    car_neutral_2->remove();
    bullet_1->remove();
    power_up->remove();
    obstacle->remove();
}

void end_game(SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Event event,
    Player player, int* quit, double worldTime) {
    save_score(player, worldTime);
    char text[128];
    DrawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 100, 400, 200, CZERWONY, NIEBIESKI);
    sprintf(text, "Koniec Gry");
    DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) / 2 * 8, SCREEN_HEIGHT / 2 - 80, text, charset);
    sprintf(text, "Twoj wynik: %d", player.points);
    DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) / 2 * 8, SCREEN_HEIGHT / 2 - 40, text, charset);
    sprintf(text, "Twoj czas: %.1lf s", worldTime);
    DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) / 2 * 8, SCREEN_HEIGHT / 2 - 20, text, charset);
    sprintf(text, "Wcisnij esc aby zakonczyc");
    DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) / 2 * 8, SCREEN_HEIGHT / 2 + 40, text, charset);
    SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, scrtex, NULL, NULL);
    SDL_RenderPresent(renderer);
    while (*quit == 0) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;
            }
            else if (event.type == SDL_QUIT) *quit = 1;
        }
    }
    *quit = 1;
}