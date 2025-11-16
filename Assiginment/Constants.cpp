#include "Constants.h"


//------------------map---------------------

 //地图尺寸 Map size
const unsigned int mapWidth=1344;
const unsigned int mapHeight=1344;
//每个tile的尺寸 Tile size
const unsigned int tileSize=32;

//-----------------Player------------------
 //player Health
 const int playerHealth=2000;
 const float playerSpeed=300.f;
 const float playerProjSpeed=350.f;
//线性攻击射程（玩家普通攻击）  Linear attack range (player normal attack)
 const int linearAttackRange=300;
//AOE 范围 AOE range
 const int AOEAttackRange=400;
 //AOE攻击几个 NPC Number of AOE attach
 int AOENumber=0;
 //普通攻击间隔时间 Linear attack interval time
 extern float  linearTimeThreshold=2;
//普通攻击伤害 Normal attack damage
 const int linearDamage=1300;
//AOE 攻击伤害 AOE attack damage
 const int AOEDamage=600;
//AOE 冷却时间 AOE cooldown time
const float AOECooldowntimeThreshold =3.f;
//运行时记录冷却累计时间 Runtime accumulated cooldown time of AOE
 float AOECooldowntimeElapsed=0.f;
 //是否正在冷却中 Whether cooldown is active of AOE
 bool ifStartCooldown=false;
//玩家的尺寸Size of player  sprite
const unsigned int playerSpriteSize = 48;
//记录当前玩家击杀数/积分 Record player kill count / score
int scores=0;

//---------------NPC---------------------
 const int NPC0Health = 1000;
 const int NPC1Health = 1700;
 const int NPC2Health = 3000;
 const int NPC3Health = 1700;

 const float NPC0Speed = 400.f;
 const float NPC1Speed = 300.f;
 const float NPC2Speed = 250.f;
 const float NPC3Speed = 0;

//NPC melee damage(per frame)
 const int meleeDamege=10;
//NPC shooting damage
 const int npcShootingDamege=80;

//NPC的尺寸	Size of NPC sprites
 const unsigned int npcSpriteSize = 32;
//NPC 发现玩家的距离范围 NPC detection range for spotting player
 const int aggroRange=450;
//NPC 追玩家时的最小距离：Minimum distance NPC keeps when chasing player
 const int stopAggroDistance=45;
 //-------------NPC and player------------
//被击中后闪烁红色  flicker color when hit 
 const Vec3 FlickerColor= { 255,0,0 };
 const int healthBarHeight = 8;
 //调整血条长度
 // Adjust health bar length
  const int healthBarLongSet = 2;


