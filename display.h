#include <stdbool.h>

#define WIDTH 64
#define HEIGHT 32

extern bool display[HEIGHT][WIDTH];

bool pixelDisplay(int x, int y);
void clearDisplay();
void updateDisplay();
