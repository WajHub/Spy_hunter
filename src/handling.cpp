#include "Handling.h"
void sort_scores(float **tab, int size, int method) {
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size - i; j++) {
				if (tab[j - 1][method] < tab[j][method]) {
					printf("Tak");
					float pom = 0;
					pom = tab[j - 1][0];
					tab[j - 1][0] = tab[j][0];
					tab[j][0] = pom;

					pom = tab[j - 1][1];
					tab[j - 1][1] = tab[j][1];
					tab[j][1] = pom;
				}
		}
	}
}

void event_handling(SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer,
	SDL_Event event, int* quit, int* t1, int* t2, double* worldTime, int* frames,
	double* fpsTimer, double* fps, double* distance, int* t3_pause, int* t_pause_begin,
	int* t_pause_end, bool* pause,
	Player* player, Road* road,
	Car_neutral* car_neutral_1, Car_neutral* car_neutral_2, Car_enemy* car_enemy_1, Bullet* bullet_1,
	Power_up* power_up, Obstacle* obstacle,float *scores[], int size) {
	switch (event.type) {
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;
		else if (event.key.keysym.sym == SDLK_UP) {
			if (player->no_collision(*t2, *worldTime)) player->y_speed = 2.0;
			else player->y_speed = 1.0;
		}
		else if (event.key.keysym.sym == SDLK_DOWN) {
			player->y_speed = 0.3;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT) {
			player->x_speed = 1;
		}
		else if (event.key.keysym.sym == SDLK_LEFT) {
			player->x_speed = -1;
		}
		else if (event.key.keysym.sym == SDLK_SPACE) {
			bullet_1->x_position = player->x_position;
			bullet_1->y_position = player->y_position;
			bullet_1->exist = true;
		}
		else if (event.key.keysym.sym == SDLK_n) {
			start_game(t1, t3_pause, t_pause_begin, t_pause_end, frames, fpsTimer, fps,
				quit, worldTime, distance, player, road, car_neutral_1, car_neutral_2,
				car_enemy_1, bullet_1, power_up, obstacle);
		}
		else if (event.key.keysym.sym == SDLK_p) {
			*pause = true;
			*t_pause_begin = SDL_GetTicks();
		}
		else if (event.key.keysym.sym == SDLK_f) {
			end_game(screen, charset, scrtex, renderer, event, *player, quit, *worldTime);
		}
		else if (event.key.keysym.sym == SDLK_t) {
			sort_scores(scores, size, 1);
		}
		else if (event.key.keysym.sym == SDLK_o) {
			sort_scores(scores, size, 0);
		}
		break;
	case SDL_KEYUP:
		//jesli wcisniety klawisz to:
		//strzalka w gor i dół
		if (!SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP] && !SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])
			player->y_speed = 1.0;
		//strzalka w gore
		if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP] && !SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]) {
			if (player->no_collision(*t2, *worldTime)) player->y_speed = 2.0;
			else player->y_speed = 1.0;
		}
		if (!SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN])
			player->y_speed = 0.3;
		//strzalka w prawo i lewo
		if (!SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && !SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])
			player->x_speed = 0;
		if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && !SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])
			player->x_speed = 1;
		if (!SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT] && SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT])
			player->x_speed = -1;
		break;
	case SDL_QUIT:
		*quit = 1;
		break;
	};
}

void event_handling_pause(SDL_Surface* pauza, SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer,
	SDL_Event event, int* quit, int* t1, int* t2, double* worldTime, int* frames,
	double* fpsTimer, double* fps, double* distance, int* t3_pause, int* t_pause_begin,
	int* t_pause_end, bool* pause,
	Player* player, Road* road) {
	DrawSurface(screen, pauza, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) *quit = 1;
			else if (event.key.keysym.sym == SDLK_p) {
				*pause = false;
				*t_pause_end = SDL_GetTicks();
			}
			break;
		case SDL_KEYUP:
			break;
		case SDL_QUIT:
			*quit = 1;
			break;
		};
	};
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void time_handling(int* t1, int* t2, int* t3_pause, int* t_pause_begin, int* t_pause_end, double* delta, double* worldTime,
	double* fpsTimer, double* fps, int* frames) {
	// w tym momencie t2-t1 to czas w milisekundach,
// jaki uplynał od ostatniego narysowania ekranu
// delta to ten sam czas w sekundach
// t3_pause   ->   zmienna pomocnicza ktora odliczy czas podczas gdy czas nie powinien leciec dalej (pauza, zniszenie samochodu itd)
	*t3_pause = t3_pause + *t_pause_end - t_pause_begin;
	*t_pause_begin = 0;
	*t_pause_end = 0;
	*t2 = SDL_GetTicks() - *t3_pause;
	*delta = (*t2 - *t1) * 0.001;
	*t1 = *t2;
	*worldTime += *delta;
	*fpsTimer += *delta;
	if (*fpsTimer > 0.5) {
		*fps = *frames * 2;
		*frames = 0;
		*fpsTimer -= 0.5;
	};
}

void road_handling(SDL_Surface* screen, Road* road, Player player, int t2) {
	road->change_road_width(t2);
	road->scroll_road(player.y_speed);
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		DrawRectangle(screen, SCREEN_WIDTH / 2 - (road->road_width[i] / 2), i, road->road_width[i], 1, SZARY, SZARY);
	}
}
void obstacle_handling(SDL_Surface* screen, Obstacle* obstacle, Player* player, Road road) {
	if (obstacle->exist) {
		obstacle->draw_obstacle(screen, player->y_speed);
		//Jesli samochod najedzie na kaluze przesuwamy samochod w prawo lub lewo
		player->x_position += obstacle->slip(*player);
	}
	else obstacle->spawn_obstacle(road);
}
void power_up_handling(SDL_Surface* screen, Power_up* power_up, Player* player, Road road) {
	if (power_up->exist) {
		power_up->draw_power_up(screen, player->y_speed);
		power_up->get_power(player);
	}
	else power_up->spawn_power_up(road);
}

void cars_handling(SDL_Surface* screen, Car_neutral* car_neutral_1, Car_neutral* car_neutral_2, Car_enemy* car_enemy_1,
	Player* player, Road road, double* distance) {
	//NEUTRALNY 1
	if (car_neutral_1->exist) {
		car_neutral_1->collision_side(*player);
		car_neutral_1->collision_front(*player, &player->time_collision_front);
		car_neutral_1->car_on_road(road, distance);
		car_neutral_1->turn(road, SDL_GetTicks());
		car_neutral_1->draw_car(screen, player->y_speed);
	}
	//utworz samochod, tylko gdy drugi neutrlany samochod i wrogi nie znajduej sie w tej samej lini
	else if (((!car_neutral_2->exist || car_neutral_2->y_position > 200) &&
		(!car_enemy_1->exist || car_enemy_1->y_position > 200)))car_neutral_1->spawn_car_neutral(*player, road);
	//WROGIE SAMOCHODY
	if (car_enemy_1->exist) {
		car_enemy_1->collision_side2(*player, &player->x_position);
		car_enemy_1->collision_front(*player, &player->time_collision_front);
		car_enemy_1->car_on_road(road, distance);
		car_enemy_1->turn(road, SDL_GetTicks(), *player);
		car_enemy_1->draw_car_neutral(screen, player->y_speed);
	}
	else if (((!car_neutral_1->exist || car_neutral_1->y_position > 200) &&
		(!car_neutral_2->exist || car_neutral_2->y_position > 200))) car_enemy_1->spawn_car_neutral(*player, road);
	//NEUTRALNY 2
	if (car_neutral_2->exist) {
		car_neutral_2->collision_side(*player);
		car_neutral_2->collision_front(*player, &player->time_collision_front);
		car_neutral_2->car_on_road(road, distance);
		car_neutral_2->turn(road, SDL_GetTicks());
		car_neutral_2->draw_car(screen, player->y_speed);
	}
	else if (((!car_neutral_1->exist || car_neutral_1->y_position > 200) &&
		(!car_enemy_1->exist || car_enemy_1->y_position > 200))) car_neutral_2->spawn_car_neutral(*player, road);
}
void bullet_handling(SDL_Surface* screen, Bullet* bullet_1, Player* player, Car_neutral* car_neutral_1, Car_neutral* car_neutral_2,
	Car_enemy* car_enemy_1, int* t2, double* worldTime, double* distance) {
	if (bullet_1->exist && player->no_collision(*t2, *worldTime)) {
		bullet_1->shot(screen, player);
		bullet_1->kill(car_neutral_1, car_neutral_2, car_enemy_1, distance);
	}
}
void player_handling(SDL_Renderer* renderer, SDL_Event event, SDL_Texture* scrtex, SDL_Surface* screen, SDL_Surface* charset,
	Player* player, Road road, int* quit, double* fps, char text[128],
	double* distance, double* delta, double* worldTime, int* t_pause_begin, int* t_pause_end, float* scores[], int size) {
	// zmieniaj dystans, jesli samochod znajduje sie na drodze, jesli dotyka pobocza, zwolnij i nie dodawaj punktow
// jesli wyjechal za droge - respawn
	if (player->car_on_road(road) == 2) {
		*distance += player->y_speed * (*delta);
	}
	else if (player->car_on_road(road) == 1) {
		player->y_speed = 0.3;
	}
	else {
		*t_pause_begin = SDL_GetTicks();
		player->destroy_car(scrtex, screen, renderer, charset, road, *worldTime, *fps, text,scores ,size);
		if (!player->unlimited_cars) player->amount_cars--;
		*t_pause_end = SDL_GetTicks();
	}
	//jesli minie okreslony czas to ilosc samochodow zostaje ograniczona
	if (*worldTime > 10.0) {
		player->unlimited_cars = false;
	}
	//gdy gracz wykorzysta wszystkie mozliwe samochody
	if (player->amount_cars == 0) {
		end_game(screen, charset, scrtex, renderer, event, *player, quit, *worldTime);
	}
	DrawSurface(screen, player->car, player->x_position, player->y_position);
	player->add_time_point(*distance);
	//porszuanie sie samochodu lewo prawo
	if (player->x_speed == -1) {
		player->x_position -= 2;
	}
	else if (player->x_speed == 1) {
		player->x_position += 2;
	}
}