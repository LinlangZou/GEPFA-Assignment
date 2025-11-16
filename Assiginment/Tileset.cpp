#include "Tileset.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace GamesEngineeringBase;
// ------Tile class methods
void Tile::load(string filename) {
    image.load(filename);
}
void Tile::draw(Window& canvas, int x, int y){ 
    for (unsigned int i = 0; i < image.width; i++) {
        if (x + i >= 0 && x + i < canvas.getWidth()) {
            for (unsigned int j = 0; j < image.height; j++) {
                if (y + j >= 0 && y + j < canvas.getHeight()) {
                    if (image.alphaAt(i, j) > 200)
                        canvas.draw(x + i, y + j, image.at(i, j));
                }
            }
        }
    }
}
//------ Tileset class methods
Tileset::Tileset() {}
// 打开 txt 文件,str 用来读单词（如 tileswide）,num 用来读数字
//open txt,str for words,num for tilesindex
void Tileset::load(string filename) {
    ifstream infile(filename);
    string str;
    string num;
    //逐条读取文件头信息
	//Read file header information one by one
    while (infile >> str) {
        if (str == "tileswide") {
            infile >> num;
            tileswide = stoi(num);
        }
        else if (str == "tileshigh") {
            infile >> num;
            tileshigh = stoi(num);
        }
        else if (str == "tilewidth") {
            infile >> num;
            tilewidth = stoi(num);
        }
        else if (str == "tileheight") {
            infile >> num;
            tileheight = stoi(num);
        }
        else if (str == "layer") {
            infile >> num;
            layer = stoi(num);
            break;
        }
    } 
    //分配二维数组 arr2D
	// Allocate 2D array arr2D
    arr2D = new int* [tileshigh];
	//为每一行分配列
	// Allocate columns for each row
    for (int i = 0; i < tileshigh; i++) {
        arr2D[i] = new int[tileswide];
    }
	//读取地图 tile ID 信息到 arr2D
	// Read map tile ID information into arr2D
   	for (int j = 0; j < tileshigh; j++)
	{
		for (int i = 0; i < tileswide; i++)
		{
            if (getline(infile, str, ',')) { 
                arr2D[i][j] = stoi(str);
            }
        }
    }
}
//World.cpp 绘制 tile 用这个函数来决定画哪一种 tile（草地、石头、道路等）。
// In World.cpp, this function is used to determine which type of tile to draw (grass, stone, road, etc.).
const int Tileset::getTileIndex(int i, int j)const {
	//边界检查
	// Boundary check
    if (i < 0 || i >= tileshigh || j < 0 || j >= tileswide) { 
        return -1; 
    }
    return arr2D[i][j];
}

