#include "Utils.h"
#include <iostream>
#include "GamesEngineeringBase.h"
//swap two integers
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
//clamp value between min and max
int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
//clamp float value between min and max and convert to int
int clampFloatToInt(float value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return static_cast<int>(value);
}
//Bresenham’s Line Algorithm
void drawLine1(GamesEngineeringBase::Window& canvas, Vec2 pos1, Vec2 pos2) {
    int x1 = pos1.x;
    int y1 = pos1.y;
    int x2 = pos2.x;
    int y2 = pos2.y;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    while (true) {
        if (x1 >= 0 && x1 < canvas.getWidth() && y1 >= 0 && y1 < canvas.getHeight()) {
            canvas.draw(x1, y1, 255, 0, 0); // Draw pixel in red color
        }
        if (x1 == x2 && y1 == y2) break;
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

