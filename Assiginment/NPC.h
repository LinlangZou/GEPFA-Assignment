#pragma once
#ifndef NPC_H
#define NPC_H

#include "Utils.h"   
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include "Gameobject.h"

class NPC : public Gameobject {
private:
	//NPC 与玩家的距离
	//Distance between NPC and player
	int NPCPlayerDistance;
	//NPC 是否处于激怒状态
	//Whether the NPC is in an aggro state
	bool isActive = false;
public:
	NPC() {}
	//构造函数
	// Constructor
	NPC(Vec2 _pos, std::string filename, int _maxHealth, float _speed);
	//拷贝构造函数和赋值运算符
	// Copy constructor and assignment operator
	NPC(const NPC& other);
	NPC& operator=(const NPC& other);
	//获取 NPC 当前血量
	// Get current health of NPC
	int getHealth() const;
	int getNPCPlayerDistance() const;
	int getSpeed()const;
	//更新 NPC 位置及状态
	// Update NPC position and state
	void update(float dt, Vec2& playerPos, Camera& cam);
	//检查与玩家的碰撞
	// Check collision with player
	bool checkCollision(Vec2 playerPos);
	bool getIsActive();
	void serialize(std::ofstream& out) const;
	void deserialize(std::ifstream& in);
};

#endif