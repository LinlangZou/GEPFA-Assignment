#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Utils.h"   
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include "Constants.h"
#include "Projsmanager.h"
using namespace std;
//抽象角色类（基类）
// Abstract character class (base class)
class Gameobject { 
protected:
	
	Vec2 worldPos; 
	Vec2 screenPos; 
	GamesEngineeringBase::Image sprite; 
	string Spritefilename;
	//该物体管理自己发射的子弹
	// This object manages its own fired projectiles
	Projsmanager projs; 
	float ProjSpeed; 
	int shootingRange; 
	//NPC or Player
	string type;
	int health = 2000; 
	int maxHealth = 2000; 
	float speed = 0.f;

	//是否开始闪烁
	// Whether to start flickering
	unsigned int ifStartFlicker = 0;
	//闪烁持续时间
	// Duration of flickering
	float flickerDuration = 0.3f;
	//闪烁计时器
	//flicker timer
	float flickerTimer = 0.0f; 
public:
	//赋值运算符
	// Assignment operator
	Gameobject& operator=(const Gameobject& other);
	string getType() const {
		return type;
	}
	Vec2 getWorldPos() const {
		return worldPos;
	}
	int getSpriteSize() const {
		return sprite.width;
	}
	void setIfStartFlicker(int flag) { 
		ifStartFlicker = flag;
	}
	string getSpriteName() {
		return Spritefilename;
	}
	int getMaxHealth() const {
		return maxHealth;
	}
	Vec2 getScreenPos() {
		return screenPos;
	}
	//设置精灵图
	// Set sprite image
	void setSprite() {
		sprite.load(Spritefilename);
	}

	
	virtual void updateProjectiles(float dt, Gameobject& obj, Camera& camera);
	void updateFlickerState(float dt);
	
	//绘制角色
	// Draw character
	void draw(GamesEngineeringBase::Window& canvas);
	//绘制受击闪烁效果
	// Draw hit flicker effect
	void drawFlicker(GamesEngineeringBase::Window& canvas, Vec3 flickerColor);
	//绘制血条
	// Draw health bar
	void drawHealthBar(GamesEngineeringBase::Window& canvas);
	//绘制子弹
	// Draw projectiles
	void drawProjectiles(GamesEngineeringBase::Window& canvas);
	//是否存活
	// Is alive
	bool getIsAlive(); 
	//受到伤害
	// Take damage
	void applyDamage(int value); 

	
	virtual void serialize(ofstream& out) const;
	virtual void deserialize(ifstream& in);
};

#endif

