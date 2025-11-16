#pragma once
#ifndef TILESET_H
#define TILESET_H
#include "GamesEngineeringBase.h"

class Tile {
private:
    GamesEngineeringBase::Image image;
	//通过性Passable
    bool isPassable;
public:
    
    Tile() { isPassable = true; }
    //使它无法通过
	//Make it unpassable
    void setUnpassable() { isPassable = false; }
    //获取通过性
	//Get passability
    const bool getIsPassable()const { return isPassable; }
	//加载图片load image
     void load(std::string filename);
	//绘制图片draw image
    void draw(GamesEngineeringBase::Window& canvas, int x, int y);
};

class Tileset {
private:
	//tiles count
    int tileswide;
    int tileshigh;
	//tile size
    int tilewidth;
    int tileheight;
   
    int layer;
	//2D array to store tile indices
    int** arr2D;
public:
    Tileset();
    int getTileswide() const{ return tileswide; }
    int getTileshigh() const{ return tileshigh; }
	//create a 2D array to save tile index
    void load(std::string filename);
	//get tile index at (i,j)
    const int getTileIndex(int i, int j)const;
};

#endif
