#include "Projectile.h"
#include<iostream>
using namespace GamesEngineeringBase;
using namespace std;
//构造函数
// Constructor
Projectile::Projectile(Vec2 _worldPos, Vec2 _target, float _speed, int _shootingRange) {
	sprite.load("Resources/fireball0.png");
    worldPos = _worldPos;
    speed = _speed;
    targetPos = _target;
    distanceProjMoved = 0;
    shootingRange = _shootingRange;
	//计算投射物目标距离和停止位置
	// Calculate projectile target distance and stop position
    projTargetDistance = static_cast<int>(sqrt(pow(worldPos.x - targetPos.x, 2) + pow(worldPos.y - targetPos.y, 2)));
    stopPos.x = static_cast<int>(shootingRange * (targetPos.x - worldPos.x) / projTargetDistance) + worldPos.x;
    stopPos.y = static_cast<int>(shootingRange * (targetPos.y - worldPos.y) / projTargetDistance) + worldPos.y;
}

Projectile::~Projectile() {}

//更新投射物位置
// Update projectile position
void Projectile::update(float dt, Camera& cam) {
    int move = static_cast<int>(speed * dt);
    int distance = static_cast<int>(sqrt(pow(worldPos.x - stopPos.x, 2) + pow(worldPos.y - stopPos.y, 2)));
	//投射物未超出射程则继续移动
	// The projectile continues to move if it has not exceeded its range
    if (distanceProjMoved < shootingRange) { 
        float moveX = move * (stopPos.x - worldPos.x) / distance;
        float moveY = move * (stopPos.y - worldPos.y) / distance;
		//更新投射物世界坐标和屏幕坐标
		// Update projectile world coordinates and screen coordinates
        worldPos.x += static_cast<int>(moveX);
        worldPos.y += static_cast<int>(moveY);
        screenPos = cam.worldToScreen(worldPos);
        distanceProjMoved += move;
    }
    else {
        isAlive = false;
    }
}

//绘制带图片的投射物
// Draw projectile with image
void Projectile::draw(Window& canvas)
{
    for (unsigned int i = 0; i < sprite.width; i++) {
        for (unsigned int j = 0; j < sprite.height; j++) {
            if (screenPos.x + i >= 0 && screenPos.x + i < canvas.getWidth() &&
                screenPos.y + j >= 0 && screenPos.y + j < canvas.getHeight()) {
                if (sprite.alphaAt(i, j) > 200) {
                    canvas.draw(i + screenPos.x, j + screenPos.y, sprite.at(i, j));
                }
            }
        }
    }
}

//检查与目标的碰撞
// Check collision with target
bool Projectile::checkCollision(Vec2 pos, int spriteSize) {
       if (worldPos.x > pos.x - spriteSize && worldPos.x < pos.x + spriteSize
        && worldPos.y > pos.y - spriteSize && worldPos.y < pos.y + spriteSize)
    {
        isAlive = false;
        return true;
    }
    return false;
}
//加载 NPC 投射物图片
//  Load NPC projectile image
void Projectile::spriteLoadNPC() {

        Projectile::sprite.load("Resources/waterball0.png");
  
}
//加载玩家投射物图片
//  Load player projectile image
void Projectile::spriteLoadPlayer() {

    Projectile::sprite.load("Resources/fireball0.png");

}

