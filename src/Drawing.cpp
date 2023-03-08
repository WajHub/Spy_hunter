extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include "Drawing.h"

// narysowanie napisu txt na powierzchni screen, zaczynajÄ
//c od punktu(x, y)
// charset to bitmapa 128x128 zawierajÄ
//ca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface* screen, int x, int y, const char* text,
    SDL_Surface* charset) {
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = 8;
    d.h = 8;
    while (*text) {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(charset, &s, screen, &d);
        x += 8;
        text++;
    };
};


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt Årodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
    SDL_Rect dest;
    dest.x = x - sprite->w / 2;
    dest.y = y - sprite->h / 2;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_BlitSurface(sprite, NULL, screen, &dest);
};


// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32*)p = color;
};


// rysowanie linii o dÅugoÅci l w pionie (gdy dx = 0, dy = 1) 
// bÄ
//dÅº poziomie(gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
    for (int i = 0; i < l; i++) {
        DrawPixel(screen, x, y, color);
        x += dx;
        y += dy;
    };
};


// rysowanie prostokÄ
//ta o dÅugoÅci bokÃ³w l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
    Uint32 outlineColor, Uint32 fillColor) {
    int i;
    DrawLine(screen, x, y, k, 0, 1, outlineColor);
    DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
    DrawLine(screen, x, y, l, 1, 0, outlineColor);
    DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
    for (i = y + 1; i < y + k - 1; i++)
        DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};
void draw_legend(SDL_Surface* screen, SDL_Surface* charset, SDL_Texture* scrtex, SDL_Renderer* renderer, int player_points,
    double worldTime, double fps, char text[128], int amount_cars, bool unlimited_cars, int points_to_get_car, float* scores[], int size) {
    DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, CZERWONY, NIEBIESKI);
    DrawRectangle(screen, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 175, 200, 175, CZERWONY, NIEBIESKI);
    sprintf(text, "Spy Hunter Hubert Wajda 193511, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
    DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
    if (unlimited_cars) sprintf(text, "Score: %d", player_points);
    else sprintf(text, "Score: %d   Amount cars: %d  Points to get Car:%d", player_points, amount_cars, points_to_get_car);
    DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);
    sprintf(text, "N - nowa gra");
    DrawString(screen, SCREEN_WIDTH - 100 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 10, text, charset);
    sprintf(text, "S - zapisz stan gry");
    DrawString(screen, SCREEN_WIDTH - 100 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 25, text, charset);
    sprintf(text, "L - zaladuj stan gry");
    DrawString(screen, SCREEN_WIDTH - 100 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 40, text, charset);
    sprintf(text, "P - pauza");
    DrawString(screen, SCREEN_WIDTH - 100 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 55, text, charset);
    sprintf(text, "F - zakonczenie gry");
    DrawString(screen, SCREEN_WIDTH - 100 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 70, text, charset);
    sprintf(text, "spacja - strzelanie");
    DrawString(screen, SCREEN_WIDTH - 100 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 85, text, charset);
    sprintf(text, "\030 - przyspieszenie");
    DrawString(screen, SCREEN_WIDTH - 100 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 100, text, charset);
    sprintf(text, "\031 - zwolnienie");
    DrawString(screen, SCREEN_WIDTH - 100 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 115, text, charset);
    sprintf(text, "\032 - lewo");
    DrawString(screen, SCREEN_WIDTH - 100 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 130, text, charset);
    sprintf(text, "\033 - prawo");
    DrawString(screen, SCREEN_WIDTH - 100 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 145, text, charset);
    sprintf(text, "Esc - wyjscie");
    DrawString(screen, SCREEN_WIDTH - 100 - strlen(text) * 8 / 2, SCREEN_HEIGHT - 160, text, charset);
    //WYNIKI
    DrawRectangle(screen, 4, 50, 200, 500, CZERWONY, NIEBIESKI);
    sprintf(text, "The best scores:");
    DrawString(screen, 10, 70, text, charset);
    for (int i = 0; i < size && 70 + ((i + 1) * 20) < SCREEN_HEIGHT - 100; i++) {
        sprintf(text, "%d. %.2f (p) %.2f (s) ", i + 1, scores[i][0], scores[i][1]);
        DrawString(screen, 10, 70 + ((i + 1) * 20), text, charset);
    }
    SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, scrtex, NULL, NULL);
    SDL_RenderPresent(renderer);
};