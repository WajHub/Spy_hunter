#include "Handling.h"

#ifdef __cplusplus
extern "C"
#endif


int main(int argc, char **argv) {
	int t1, t2,t3_pause,t_pause_begin,t_pause_end, quit, frames, rc;
	double delta, worldTime, fpsTimer, fps, distance;
	bool pause = false;
	char text[128];
	SDL_Event event{};
	SDL_Surface *screen, *charset;
	SDL_Surface *pauza_bmp;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Renderer *renderer;
	Road road;
	Player player;
	Obstacle obstacle;
	Car_neutral car_neutral_1;
	Car_neutral car_neutral_2;
	Car_enemy car_enemy_1;
	Bullet bullet_1;
	Power_up power_up;
	//odczytujemy ilosc wynikow
	int size_scores = 0;
	FILE* file;
	file = fopen("scores_size.txt", "r");
	if (file == NULL) {
		printf("Blad");
	}
	else {
		fscanf(file, "%d", &size_scores);
	}
	fclose(file);
	float **scores = new float* [size_scores];
	for (int i = 0; i < size_scores; i++) {
		scores[i] = new float[2];
	}
	file = fopen("scores.txt", "r");
	if (file == NULL) {
		printf("Blad");
	}
	else {
		for (int i = 0; i < size_scores; i++) {
			fscanf(file, "%f %f", &scores[i][0], &scores[i][1]);
			printf("%.2f    %.2f\n", scores[i][0], scores[i][1]);
		}
	}
	fclose(file);

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
		}
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,&window, &renderer);
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 250);
	SDL_SetWindowTitle(window, "Project Spy Hunter Hubert Wajda 193511");
	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
	                           SCREEN_WIDTH, SCREEN_HEIGHT);
	//wczytania obrazka pauzy
	pauza_bmp = SDL_LoadBMP("./pauza.bmp");
	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};
	SDL_SetColorKey(charset, true, 0x000000);

	if(player.car == NULL) {
		printf("SDL_LoadBMP(car.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};

	start_game(&t1, &t3_pause, &t_pause_begin, &t_pause_end, &frames, &fpsTimer, &fps, &quit, &worldTime,
		&distance, &player, &road,&car_neutral_1,&car_neutral_2,&car_enemy_1, &bullet_1,&power_up,&obstacle);
	while(!quit) {
		//Kiedy nie ma pauzy - Toczy sie gra
		if (!pause) {
			//CZAS, FPS
			time_handling(&t1, &t2, &t3_pause, &t_pause_begin, &t_pause_begin, &delta, &worldTime, &fpsTimer, &fps, &frames);
			//TLO
			SDL_FillRect(screen, NULL, ZIELONY);
			//DROGA
			road_handling(screen, &road, player, t2);
			//PRZESZKODY - kaluze
			obstacle_handling(screen, &obstacle, &player, road);
			//POWER UP
			power_up_handling(screen, &power_up, &player, road);
			//INNE SAMOCHODY
			cars_handling(screen, &car_neutral_1, &car_neutral_2, &car_enemy_1, &player, road, &distance);
			//AMUNUCJA
			bullet_handling(screen, &bullet_1, &player, &car_neutral_1, &car_neutral_2, &car_enemy_1, &t2, &worldTime, &distance);
			//GRACZ
			player_handling(renderer, event, scrtex, screen, charset, &player, road, &quit, &fps, text, &distance, &delta, &worldTime,
				&t_pause_begin, &t_pause_end,scores,size_scores);
			// LEGENDA
			draw_legend(screen, charset, scrtex, renderer, player.points, worldTime, fps, text, player.amount_cars, player.unlimited_cars,player.points_to_get_car,scores,size_scores);
			// OBSLUGA ZDARZEN
			while (SDL_PollEvent(&event)) {
				event_handling(screen,charset,scrtex,renderer,event,&quit,&t1,&t2,&worldTime,&frames,
					&fpsTimer,&fps,&distance,&t3_pause,&t_pause_begin,&t_pause_end,&pause, 
					&player, &road, &car_neutral_1, &car_neutral_2, &car_enemy_1, &bullet_1, 
					&power_up, &obstacle,scores,size_scores);
			};
			frames++;
		}
		//PAUZA
		else {
			event_handling_pause(pauza_bmp, screen, charset, scrtex, renderer, event, &quit, &t1, &t2, &worldTime, &frames,
				&fpsTimer, &fps, &distance, &t3_pause, &t_pause_begin, &t_pause_end, &pause, &player, &road );
		}
		};
	//zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	for (int i = 0; i < size_scores; i++) {
		delete [] scores[i];
	}
	delete[] scores;
	return 0;
	};
