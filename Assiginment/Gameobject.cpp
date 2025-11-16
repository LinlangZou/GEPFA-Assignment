#include "Gameobject.h"
#include"Projectile.h"
#include <iostream>
#include <fstream>
using namespace GamesEngineeringBase;
//赋值运算符
// Assignment operator
Gameobject& Gameobject::operator=(const Gameobject& other) {
    if (this == &other) {
        return *this; 
    }
    worldPos.x = other.worldPos.x;
    worldPos.y = other.worldPos.y;
    screenPos.x = other.screenPos.x;
    screenPos.y = other.screenPos.y;
    health = other.health;
    speed = other.speed;
    ifStartFlicker = other.ifStartFlicker;
    sprite.load(Spritefilename);

    return *this;
}
//绘制该物体
// Draw the object
void Gameobject::draw(Window& canvas) {
	//遍历精灵图的每个像素，进行绘制
	// Iterate through each pixel of the sprite and draw it
    for (unsigned int i = 0; i < sprite.width; i++) {
        for (unsigned int j = 0; j < sprite.height; j++) {
            if (screenPos.x + i >= 0 && screenPos.x + i < canvas.getWidth() &&
                screenPos.y + j >= 0 && screenPos.y + j < canvas.getHeight()) {
				//只绘制不透明像素#
				//only draw opaque pixels
                if (sprite.alphaAt(i, j) > 200) {
                    canvas.draw(i + screenPos.x, j + screenPos.y, sprite.at(i, j));
                }
            }
        }
    }
}
//绘制受击闪烁效果
// Draw hit flicker effect
void Gameobject::drawFlicker(Window& canvas, Vec3 flickerColor) {
    if (ifStartFlicker != 0) {
        for (unsigned int i = 0; i < sprite.width; i++) {
            for (unsigned int j = 0; j < sprite.height; j++) {
                if (screenPos.x + i >= 0 && screenPos.x + i < canvas.getWidth() &&
                    screenPos.y + j >= 0 && screenPos.y + j < canvas.getHeight()) {
                    if (sprite.alphaAt(i, j) > 200) {
						//NPC闪烁效果为指定颜色
						// NPC flicker effect is the specified color
                        if (ifStartFlicker == 1) canvas.draw(i + screenPos.x, j + screenPos.y, flickerColor.x, flickerColor.y, flickerColor.z);
						//AOE闪烁效果为白色
						//AOE flicker effect is white
                        else if(ifStartFlicker == 2)
                            canvas.draw(i + screenPos.x, j + screenPos.y, 255, 255, 255);
                    }
                }
            }
        }
    }
}
//绘制血条
// Draw health bar
void Gameobject::drawHealthBar(Window& canvas) {
    int barHeight = healthBarHeight;
	//血条起始位置
	// Starting position of the health bar
    int startPosX = screenPos.x;
    int startPosY = screenPos.y -8;
	//绘制血条背景
	// Draw health bar background
    for (unsigned int i = 0; i < healthBarLongSet*maxHealth /80; i++) {
        for (unsigned int j = 0; j < barHeight; j++) {
			//确保血条绘制在画布范围内
			// Ensure the health bar is drawn within the canvas bounds
            if (startPosX + i >= 0 && startPosX + i < canvas.getWidth() &&
                startPosY + j >= 0 && startPosY + j < canvas.getHeight()) {               
                canvas.draw(i + startPosX, j + startPosY, 0, 0, 0);     
				//绘制当前血量
				// Draw current health
                if (i <= healthBarLongSet*health / 80) canvas.draw(i + startPosX, j + startPosY, 255, 0, 0);
               //if type ==player。。。
            }
        }
    }
}
//更新该物体发射的子弹状态
// Update the status of projectiles fired by this object
void Gameobject::updateProjectiles(float dt, Gameobject& obj, Camera& camera) {
	//计算该物体精灵图中心的世界坐标
	// Calculate the world coordinates of the center of the object's sprite
    Vec2 midWorldPos;
    midWorldPos.x = worldPos.x + sprite.width / 2;
    midWorldPos.y = worldPos.y + sprite.height / 2;

	//计算目标物体精灵图中心的世界坐标
	// Calculate the world coordinates of the center of the target object's sprite
    Vec2 midObjWorldPos;
    midObjWorldPos.x = obj.getWorldPos().x + obj.getSpriteSize() / 2;
    midObjWorldPos.y = obj.getWorldPos().y + obj.getSpriteSize() / 2;

	//更新该物体发射的子弹位置
	// Update the position of projectiles fired by this object
    projs.update(dt, midWorldPos, midObjWorldPos, camera, ProjSpeed, shootingRange);

	//检查子弹与目标物体的碰撞
	// Check for collision between projectiles and the target object
    if (projs.checkProjEntityCollision(midObjWorldPos, obj.getSpriteSize())) {
		//目标物体开始闪烁
		// The target object starts flickering
		obj.setIfStartFlicker(1);

		//玩家每次只掉20点血，其它物体掉线性伤害值
		// Players only lose npcShootingDamege each time,
        // other objects lose linear damage value
        if (obj.getType() == "Player") obj.applyDamage(npcShootingDamege);
        else obj.applyDamage(linearDamage);
    }
}
//绘制该物体发射的子弹
// Draw projectiles fired by this object
void Gameobject::drawProjectiles(Window& canvas) {
    
    if (type == "Player") {
        //sprite.load("Resources/fireball0.png");
        projs.drawPlayerProjs(canvas);
    }
    else//NPC
    {
       // Projectile.spriteLoad();
        projs.drawNPCsProjs(canvas);
    }
}
//更新闪烁状态
// Update flicker state
void Gameobject::updateFlickerState(float dt) {
	
    if (ifStartFlicker != 0) {
        if (flickerTimer < flickerDuration) flickerTimer += dt;
        else {
            ifStartFlicker = 0;
            flickerTimer = 0.f;
        }
    }
}
//应用伤害
// Apply damage
void Gameobject::applyDamage(int value) {
    if (health > 0) health -= value;
    else health = 0;
}
//获取是否存活状态
// Get alive status
bool Gameobject::getIsAlive() {
    return(health > 0);
}

//序列化该物体状态
// Serialize the state of this object
void Gameobject::serialize(ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&worldPos), sizeof(worldPos));
    out.write(reinterpret_cast<const char*>(&screenPos), sizeof(screenPos));
  
    out.write(reinterpret_cast<const char*>(&ProjSpeed), sizeof(ProjSpeed));
    out.write(reinterpret_cast<const char*>(&shootingRange), sizeof(shootingRange));
    out.write(reinterpret_cast<const char*>(&health), sizeof(health));
    out.write(reinterpret_cast<const char*>(&maxHealth), sizeof(maxHealth));
    out.write(reinterpret_cast<const char*>(&speed), sizeof(speed));
    out.write(reinterpret_cast<const char*>(&ifStartFlicker), sizeof(ifStartFlicker));
    out.write(reinterpret_cast<const char*>(&flickerDuration), sizeof(flickerDuration));
    out.write(reinterpret_cast<const char*>(&flickerTimer), sizeof(flickerTimer));

    size_t length = Spritefilename.size();
    out.write(reinterpret_cast<const char*>(&length), sizeof(length));
    out.write(Spritefilename.data(), length);
   
}
//反序列化该物体状态
// Deserialize the state of this object
void Gameobject::deserialize(ifstream& in) {
    in.read(reinterpret_cast<char*>(&worldPos), sizeof(worldPos));
    in.read(reinterpret_cast<char*>(&screenPos), sizeof(screenPos));
    in.read(reinterpret_cast<char*>(&ProjSpeed), sizeof(ProjSpeed));
    in.read(reinterpret_cast<char*>(&shootingRange), sizeof(shootingRange));
    in.read(reinterpret_cast<char*>(&health), sizeof(health));
    in.read(reinterpret_cast<char*>(&maxHealth), sizeof(maxHealth));
    in.read(reinterpret_cast<char*>(&speed), sizeof(speed));
    in.read(reinterpret_cast<char*>(&ifStartFlicker), sizeof(ifStartFlicker));
    in.read(reinterpret_cast<char*>(&flickerDuration), sizeof(flickerDuration));
    in.read(reinterpret_cast<char*>(&flickerTimer), sizeof(flickerTimer));
    size_t length;
    in.read(reinterpret_cast<char*>(&length), sizeof(length));
    Spritefilename.resize(length);
    in.read(&Spritefilename[0], length);
}