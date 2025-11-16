#pragma once
#ifndef UTILS_H
#define UTILS_H
#include "GamesEngineeringBase.h"
//swap two integers
void swap(int& a, int& b);
//clamp value between min and max
int clamp(int value, int min, int max);
//clamp float value between min and max and convert to int
int clampFloatToInt(float value, int min, int max);

//2D and 3D vector structs
struct Vec2 {
    int x, y;
};
struct Vec3 {
    int x, y, z;
};
//Bresenham’s Line Algorithm
void drawLine1(GamesEngineeringBase::Window& canvas, Vec2 pos1, Vec2 pos2);



#endif 