#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Utils.h"
#include "Camera.h"
#include "GamesEngineeringBase.h"
#include "Constants.h"

class Projectile {
private:
	//投射物精灵图
	// Projectile sprite image
	GamesEngineeringBase::Image sprite;
	Vec2 worldPos; 
	Vec2 screenPos; 
	Vec2 targetPos; 
	Vec2 stopPos;
	float speed;
	//投射物移动的距离
	// Distance moved by the projectile
	int distanceProjMoved;
	//投射物目标距离
	// Projectile target distance
	int projTargetDistance;
	//投射物射程
	// Projectile shooting range
	int shootingRange;
	//投射物是否碰撞
	// Whether the projectile has collided
	bool isCollided = false; 
	//投射物是否存活
	// Whether the projectile is alive
	bool isAlive = true;
public:
	Projectile(Vec2 _worldPos, Vec2 _target, float _speed, int _shootingRange);
	~Projectile();
	//更新投射物位置
	// Update projectile position
	void update(float dt, Camera& cam);
	//绘制投射物
	// Draw projectile
	void draw(GamesEngineeringBase::Window& canvas, int projSize, Vec3 color);
	void draw(GamesEngineeringBase::Window& canvas);
	void spriteLoadNPC();
	void spriteLoadPlayer();
	//检查与目标的碰撞
	// Check collision with target
	bool checkCollision(Vec2 pos, int spriteSize);
	bool getIsAlive() { return isAlive; }
	bool getIsCollided() { return isCollided; }

};

#endif
