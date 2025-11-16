#pragma once
#ifndef PROJSMANAGER_H
#define PROJSMANAGER_H
#include "Projectile.h"
#include "Utils.h"
#include "GamesEngineeringBase.h"
class Projsmanager {
private:
	//最大投射物数量
	// Maximum number of projectiles
	static const int maxProjsNum = 9999;
	//投射物指针数组
	// Array of projectile pointers
	Projectile* projs[maxProjsNum] = { nullptr };
	//当前投射物数量
	// Current number of projectiles
	int currentNum = 0;
	//时间控制变量
	// Time control variables
	float timeElapsed = 0.f;
	float timeThreshold = 0.8f; 
public:
	Projsmanager();
	~Projsmanager();
	//生成投射物并加入 projs 数组
	// Generate projectiles and add them to the projs array
	void generateProjs(float dt, Vec2 worldPos, Vec2 target, float speed, int shootingRange);
	//检查并删除已碰撞或超出射程的投射物
	// Check and delete projectiles that have collided or exceeded their range
	void checkDeleteProj(unsigned int i);
	//更新投射物位置
	// Update projectile positions
	void update(float dt, Vec2 worldPos, Vec2 objWorldPos, Camera& camera, float speed, int shootingRange);
	//检查与目标的碰撞
	// Check collision with target
	bool checkProjEntityCollision(Vec2 objWorldPos, int sprietSize);
	//绘制投射物
	// Draw projectiles
	void drawNPCsProjs(GamesEngineeringBase::Window& canvas);
	void drawPlayerProjs(GamesEngineeringBase::Window& canvas);


};

#endif