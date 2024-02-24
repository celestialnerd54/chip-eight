#include "display.h"
#include <stdio.h>
#include <stdlib.h>

bool display[HEIGHT][WIDTH];

bool pixelDisplay(int x, int y) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        display[y][x] = !display[y][x];
    }
    return display[y][x];
}

void clearDisplay() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            display[y][x] = false;
        }
    }
}

void updateDisplay() {
    system("clear");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf(display[y][x] ? "+ " : "  ");
        }
        printf("\n");
    }
}
