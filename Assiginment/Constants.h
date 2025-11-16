#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include"Utils.h"
//------------------map---------------------

 //地图尺寸 Map size
extern const unsigned int mapWidth;
extern const unsigned int mapHeight;
//每个tile的尺寸 Tile size
extern const unsigned int tileSize;

//-----------------Player------------------
//玩家生命值player Health
extern const int playerHealth;
extern const float playerSpeed;
extern const float playerProjSpeed;


//线性攻击射程（玩家普通攻击）  Linear attack range (player normal attack)
extern const int linearAttackRange;
//AOE 范围 AOE range
extern const int AOEAttackRange;
//AOE攻击几个npc Number of AOE attach 
extern  int AOENumber;
//普通攻击间隔时间 Linear attack interval time
extern float  linearTimeThreshold;
//普通攻击伤害 Normal attack damage
extern const int linearDamage;
//AOE 攻击伤害 AOE attack damage
extern const int AOEDamage;
//AOE 冷却时间 AOE cooldown time
extern const float AOECooldowntimeThreshold;
//运行时记录冷却累计时间 Runtime accumulated cooldown time
extern float AOECooldowntimeElapsed;
//是否正在冷却中 Whether cooldown is active
extern bool ifStartCooldown;
//玩家的尺寸Size of player  sprites
extern const unsigned int playerSpriteSize;
//记录当前玩家击杀数/积分 Record player kill count / score
extern int scores;

//---------------NPC---------------------
extern const int NPC0Health;
extern const int NPC1Health;
extern const int NPC2Health;
extern const int NPC3Health;

extern const float NPC0Speed;
extern const float NPC1Speed;
extern const float NPC2Speed;
extern const float NPC3Speed;

//npc近战伤害 NPC melee damage
extern const int meleeDamege;
//NPC远程伤害 NPC shooting damage
extern const int npcShootingDamege;
//NPC的尺寸	Size of NPC sprites
extern const unsigned int npcSpriteSize;
//NPC 发现玩家的距离范围 NPC detection range for spotting player
extern const int aggroRange;
//NPC 追玩家时的最小距离：Minimum distance NPC keeps when chasing player
extern const int stopAggroDistance;

//-------------NPC and player------------
//被击中后闪烁红色  flicker color when hit 
extern const Vec3 FlickerColor;
extern const int healthBarHeight ;
extern const int healthBarLongSet;








#endif 
