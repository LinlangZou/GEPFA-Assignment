#pragma once
#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include "NPC.h"
#include "Gameobject.h"
#include "GamesEngineeringBase.h"
#include "Player.h"
#include "Utils.h"

class NPCmanager {
private:
	//NPC 最大数量
	// Maximum number of NPCs
    static const int maxNPCNum = 100;     
	//NPC 指针数组
	// Array of NPC pointers
    NPC* npc_array[maxNPCNum] = { nullptr };
	//用于按血量排序的辅助数组
	// Auxiliary array for sorting by health
    Vec2 sort_health_array[maxNPCNum];
	//当前 NPC 数量
	// Current number of NPCs
    int currentNum = 0;
   //生成一只 NPC 所需的时间间隔
	//timeElapsed for create each NPC
    float timeElapsed = 0.f;
	//从上一次生成到现在经过的时间
	//from last create
    float timeThreshold = 3.f;
	//生成 NPC 并加入 npc_array
	// Generate NPCs and add them to npc_array
    void createNPC(Camera& camera, float& dt);
	//检查并删除已死亡的 NPC
	// Check and delete dead NPCs
    void checkDeleteNPC(unsigned int i);
	//生成 NPC 出生位置
	// Generate NPC spawn position
    Vec2 generateStartPos(Camera& camera);
public:
    NPCmanager();
    ~NPCmanager();
    
    NPCmanager& operator=(const NPCmanager& other);
	//更新 NPC 位置及状态
	// Update NPC positions and states
    void update(float& dt, Vec2& playerPos, Camera& camera);
	//绘制 NPC 及其血条和受击闪烁效果
	// Draw NPCs along with their health bars and hit flicker effects
    void draw(GamesEngineeringBase::Window& canvas);
	//检查 NPC 与玩家的碰撞
	// Check collision between NPCs and player
    void checkNPCPlayerCollision(Player& player);
	//更新 NPC 的投射物
	// Update NPC projectiles
    void setProjectiles(float dt, Gameobject& obj, Camera& camera);
	//绘制速度为0的 NPC 的子弹
	// Draw projectiles of NPCs with speed 0
    void drawProjectiles(GamesEngineeringBase::Window& canvas);
	//检查是否有 NPC 在玩家的攻击范围内
	// Check if any NPC is within the player's attack range
    bool getIfNPCinPlayerAttackRange();
	//获取距离玩家最近的 NPC 指针
	// Get pointer to the NPC closest to the player
    NPC* const getClosestNPC();
	// 对血量最高的3个 NPC 进行 AOE 攻击
	// Perform AOE attack on the top 3 NPCs with highest health
    void AOE();

	//序列化 NPCmanager 对象
	// Serialize NPCmanager object
    void serialize(std::ofstream& out) const;
	//反序列化 NPCmanager 对象
	// Deserialize NPCmanager object
    void deserialize(std::ifstream& in);
};

#endif
