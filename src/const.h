#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#define SCREEN_WIDTH    1100
#define SCREEN_HEIGHT   600
#define BEGIN_ROAD_WIDTH 500
#define OBSTACLE_SIZE 40
#define CZERWONY SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00)
#define CZARNY SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)
#define SZARY SDL_MapRGB(screen->format, 0x3F, 0x3F, 0x3F)
#define BIALY SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF)
#define ZIELONY SDL_MapRGB(screen->format, 0x00, 0x80, 0x00)
#define NIEBIESKI SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC)