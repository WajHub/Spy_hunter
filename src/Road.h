#pragma once
#include "const.h"

class Road {
public:
    //droga podzielona jest na 600 czesci, w celu rysowania jej po czesciach
    int road_width[SCREEN_HEIGHT];
    void set_road_width(int size);
    void scroll_road(double speed);
    bool can_change_road_width();
    void change_road_width(int random);
};