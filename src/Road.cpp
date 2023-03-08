#include "Road.h"

void Road::set_road_width(int size) {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        road_width[i] = size;
    }
}
void Road::scroll_road(double speed) {
    int new_size;
    for (int i = 0; i < SCREEN_HEIGHT - 1; i++) {
        if (road_width[i] != road_width[i + 1]) {
            new_size = road_width[i];
            if (speed > 1.0) {
                for (int j = 0; j < 7 && i + j + 1 < SCREEN_HEIGHT; j++) {
                    road_width[i + j + 1] = new_size;
                }
            }
            else if (speed < 1.0) {
                for (int j = 0; j < 1 && i + j + 1 < SCREEN_HEIGHT; j++) {
                    road_width[i + j + 1] = new_size;
                }
            }
            else {
                for (int j = 0; j < 3 && i + j + 1 < SCREEN_HEIGHT; j++) {
                    road_width[i + j + 1] = new_size;
                }
            }
            break;
        }
    }
}
bool Road::can_change_road_width() {
    for (int i = 0; i < SCREEN_HEIGHT - 1; i++) {
        if (road_width[i] != road_width[i + 1]) {
            return false;
        }
    }
    return true;
}
void Road::change_road_width(int random) {
    if (random % 1000 > 900 && can_change_road_width()) {
        if (random % 2 == 0 && road_width[0] < 600) road_width[0] += 50;
        else if (road_width[0] > 240) road_width[0] -= 50;

    }
}