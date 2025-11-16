#include "World.h"
#include "Constants.h"
#include <iostream>
using namespace std;
using namespace GamesEngineeringBase;

World::World(Window& canvas) {
    tileset.load("Resources/tiles.txt");

	//calculate how many tiles needed to draw on screen
    tileNumX = canvas.getWidth() / tileSize + 1;
    tileNumY = canvas.getHeight() / tileSize + 1;
    

	//设置不可穿过的地形类型
    // load all tile images & set unpassable tiles
    for (int i = 0; i < tileType; i++) {
        if ((i >= 14 && i <= 22) || i == 24 || i == 25) tiles[i].setUnpassable();
        string tilename = "Resources/" + to_string(i) + ".png";
        tiles[i].load(tilename);
    }
}

void World::draw(Window& canvas, Vec2& camPos) {
    //通过 camera 计算当前绘制的是哪块 tile
	// Calculate which tile to draw based on camera position
    int tileIndexX = camPos.x / tileSize;
    int tileIndexY = camPos.y / tileSize;
    //决定 tile 在屏幕的初始像素位置
	// Determine the initial pixel position of the tile on the screen
    int tileDrawStartX = 0;
    int tileDrawStartY = 0;
	//获取 地图 的宽高信息
	// Get map width and height information
    int tileswide = tileset.getTileswide();
    int tileshigh = tileset.getTileshigh();
    //计算屏幕起始偏移
	// Calculate screen starting offset
    int tileDrawStartOffsetY = tileSize - camPos.y % tileSize;
    int tileDrawStartOffsetX = tileSize - camPos.x % tileSize;
   // 双层 for 循环，遍历可见区域的 tile
	// Double for loop to traverse visible area tiles
    for (int i = tileIndexX; i < min((tileIndexX + tileNumX), tileswide); i++) {
        for (int j = tileIndexY; j < min((tileIndexY + tileNumY), tileshigh); j++) {
            int tileNameIndex = tileset.getTileIndex(i, j);
            //如果这个 tile 是石块（或透明），先画草地，铺底纹理
			// If this tile is a stone (or transparent), draw grass first as the base texture
            if (tileNameIndex == 24 || tileNameIndex == 25) {
                tiles[0].draw(canvas, tileDrawStartX, tileDrawStartY);
            }
            tiles[tileNameIndex].draw(canvas, tileDrawStartX, tileDrawStartY);
            //更新 Y 轴的绘制位置（进入下一行）
			// Update the Y-axis drawing position (move to the next row)
            if (tileDrawStartY == 0) tileDrawStartY += tileDrawStartOffsetY; 
            else tileDrawStartY += tileSize;
		}
        //每次完成 j 循环后，重置 Y 并更新 X 位置
		// Reset Y after each j loop and update X position
        tileDrawStartY = 0;
        // 更新 tileDrawStartX
		// Update tileDrawStartX
        if (tileDrawStartX == 0) tileDrawStartX += tileDrawStartOffsetX;
        else tileDrawStartX += tileSize;
    }
}

//基于玩家即将移动到的坐标 (x,y)，检查玩家 hitbox 的多个点是否处于可通行的 tile 上，
// 如果碰到不可通过的 tile，就禁止移动。
// Based on the coordinates (x,y) where the player is about to move,
// check multiple points of the player's hitbox to see if they are on passable tiles.
bool World::checkTilePassable(int x, int y) {
    //计算玩家碰撞边界（四个顶点）
	// Calculate the player's collision boundaries (four corners)
    int leftX = x;
    int topY = y;
    int rightX = x + playerSpriteSize;
    int bottomY = y + playerSpriteSize;
    ///遍历玩家 hitbox 的多个检测点
	// Check multiple detection points of the player's hitbox
    for (int i = leftX; i <= rightX; i = i + playerSpriteSize / 2)
        for (int j = topY; j <= bottomY; j = j + playerSpriteSize / 2) {
            int tileIndex = tileset.getTileIndex(i / tileSize, j / tileSize);
            if (!tiles[tileIndex].getIsPassable()) return false;
        }
    return true;

}
