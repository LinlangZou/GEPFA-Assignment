#pragma once
#ifndef WORLD_H
#define WORLD_H

#include "Tileset.h"
#include "Constants.h"
#include "GamesEngineeringBase.h"
#include "Utils.h"  

class World {
private:
    int tileNumX ; 
    int tileNumY ;  
    Tileset tileset;
	//tile共有多少种类型
	// Total number of tile types
    static const int tileType = 27;
	//所有类型的tile数组
	// Array of all tile types
    Tile tiles[tileType]; 

public:
	//构造函数 Constructor
     World(GamesEngineeringBase::Window& canvas);
	//绘制地图 Draw map
    void draw(GamesEngineeringBase::Window& canvas, Vec2& camPos);
	//检测tile是否可通过 Check if tile is passable
    bool checkTilePassable(int x, int y);
};
// static保持值在整个程序生命周期内有效
// static keeps the value valid throughout the program's lifecycle
#endif
