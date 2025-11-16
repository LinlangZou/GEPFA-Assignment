#include "Projsmanager.h"
#include"Gameobject.h"
#include <iostream>
using namespace std;
using namespace GamesEngineeringBase;

Projsmanager::Projsmanager() {}
//析构函数，释放投射物内存
// Destructor to free projectile memory
Projsmanager::~Projsmanager() {
    for (int i = 0; i < currentNum; i++) {
        delete projs[i];
    }
}
//生成投射物并加入 projs 数组
// Generate projectiles and add them to the projs array
void Projsmanager::generateProjs(float dt, Vec2 worldPos, Vec2 target, float speed, int shootingRange) {
    timeElapsed += dt;
    if (currentNum < maxProjsNum) {
        if (timeElapsed > linearTimeThreshold) {
            Projectile* proj = new Projectile(worldPos, target, speed, shootingRange);
            projs[currentNum++] = proj;
            timeElapsed = 0.f;
        }
    }
}

//检查并删除已碰撞或超出射程的投射物
// Check and delete projectiles that have collided or exceeded their range
void Projsmanager::checkDeleteProj(unsigned int i) {
    if (!projs[i]->getIsAlive()) {
        Projectile* _p = projs[i];
        projs[i] = nullptr;
        delete _p;
    }
}
//更新投射物位置
// Update projectile positions
void Projsmanager::update(float dt, Vec2 worldPos, Vec2 objWorldPos, Camera& camera, float speed, int shootingRange) {
    generateProjs(dt, worldPos, objWorldPos, speed, shootingRange);
    
    for (int i = 0; i < currentNum; i++) {
        if (projs[i] != nullptr) {
            projs[i]->update(dt, camera);
            checkDeleteProj(i);
        }
    }
}

//检查与目标的碰撞
// Check collision with target
bool Projsmanager::checkProjEntityCollision(Vec2 objWorldPos, int sprietSize) {
    for (int i = 0; i < currentNum; i++) {
        if (projs[i] != nullptr) {
            if (projs[i]->checkCollision(objWorldPos, sprietSize)) {
                checkDeleteProj(i);
                return true;
            }
        }
    }
    return false;
}
//绘制NPC投射物
// Draw NPC projectiles
void Projsmanager::drawNPCsProjs(Window& canvas) {
    for (int i = 0; i < currentNum; i++) {
        if (projs[i] != nullptr) {
            projs[i]->spriteLoadNPC();
            projs[i]->draw(canvas);
        }
    }
}
//绘制玩家投射物
// Draw player projectiles
void Projsmanager::drawPlayerProjs(Window& canvas) {
    for (int i = 0; i < currentNum; i++) {
        if (projs[i] != nullptr) {
            projs[i]->spriteLoadPlayer();
            projs[i]->draw(canvas);
        }
    }
}