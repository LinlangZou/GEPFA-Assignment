#include "NPC.h"
#include "Constants.h"
#include "math.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace GamesEngineeringBase;
//构造函数
// Constructor
NPC::NPC(Vec2 _pos, string filename, int _maxHealth, float _speed) {
    Spritefilename = filename;
    sprite.load(Spritefilename);
    worldPos.x = _pos.x;
    worldPos.y = _pos.y;
    maxHealth = _maxHealth;
    health = _maxHealth;
    speed = _speed;
	type = "NPC";
    ProjSpeed = 280.f; 
    shootingRange = aggroRange + 80; 
}
//拷贝构造函数
// Copy constructor
NPC::NPC(const NPC& other) {
    NPCPlayerDistance = other.NPCPlayerDistance;
    isActive = other.isActive;
    sprite.load(Spritefilename); 
}
//赋值运算符
// Assignment operator
NPC& NPC::operator=(const NPC& other) {
    if (this == &other) {
        return *this; 
    }
    Gameobject::operator=(other); 
    NPCPlayerDistance = other.NPCPlayerDistance;
    isActive = other.isActive;
}

int NPC::getNPCPlayerDistance() const {
    return NPCPlayerDistance;
}

int NPC::getSpeed() const {
    return speed;
}

int NPC::getHealth() const {
    return health;
}
//更新 NPC 位置及状态
// Update NPC position and state
void NPC::update(float dt, Vec2& playerPos, Camera& cam) {
	// Calculate movement towards player
    int move = static_cast<int>(speed * dt);
	// Calculate distance to player
    NPCPlayerDistance = static_cast<int>(sqrt(pow(worldPos.x - playerPos.x, 2) 
        + pow(worldPos.y - playerPos.y, 2)));
    if (NPCPlayerDistance == 0) NPCPlayerDistance = 1;
    float moveX = move * (playerPos.x - worldPos.x) / NPCPlayerDistance;
    float moveY = move * (playerPos.y - worldPos.y) / NPCPlayerDistance;
	//使用 static_cast<int>将移动量转换为整数，以确保位置更新的准确性
	// Use static_cast<int> to convert movement amount to integer to ensure accurate position updates
    int newPosX = worldPos.x + static_cast<int>(moveX);
    int newPosY = worldPos.y + static_cast<int>(moveY);
    bool inMap = (newPosX > 0 && newPosX + npcSpriteSize < mapWidth)
        && (newPosY > 0 && newPosY + npcSpriteSize < mapHeight);
    //当玩家进入 aggro 范围（450）时，NPC 启动攻击/追踪模式
	// When the player enters the aggro range , the NPC activates attack/tracking mode
    if (NPCPlayerDistance < aggroRange) isActive = true;
	//当玩家超出停止追踪距离（30）时，NPC 停止攻击/追踪模式
	// When the player exceeds the stop tracking distance , the NPC stops attack/tracking mode
    else isActive = false;
	// NPC 仅在地图边界内且在激怒范围内但超出停止距离时移动
	// Only move NPC if within map boundaries and within aggro range but outside stop distance
    if (inMap && NPCPlayerDistance > stopAggroDistance && NPCPlayerDistance < aggroRange) {
        worldPos.x = newPosX;
        worldPos.y = newPosY;
    }
    screenPos = cam.worldToScreen(worldPos); 

    
    updateFlickerState(dt);
}
// Check collision with player
bool NPC::checkCollision(Vec2 playerPos) {
    int x2 = (worldPos.x - playerPos.x) * (worldPos.x - playerPos.x);
    int y2 = (worldPos.y - playerPos.y) * (worldPos.y - playerPos.y);
    float r = sqrtf(x2 + y2);
    float hitBox = static_cast<float>(3 * npcSpriteSize / 4);
    return(r < hitBox);
}
//获取 NPC 是否处于激怒状态
// Get whether the NPC is in an aggro state
bool NPC::getIsActive() {
    return isActive;
}

//序列化 NPC 对象状态到文件
// Serialize NPC object state to file
void NPC::serialize(ofstream& out) const {
    
    Gameobject::serialize(out);

    
    out.write(reinterpret_cast<const char*>(&NPCPlayerDistance), sizeof(NPCPlayerDistance));
    out.write(reinterpret_cast<const char*>(&isActive), sizeof(isActive));

   
}
//反序列化 NPC 对象状态从文件
// Deserialize NPC object state from file
void NPC::deserialize(ifstream& in) {
     Gameobject::deserialize(in);
    in.read(reinterpret_cast<char*>(&NPCPlayerDistance), sizeof(NPCPlayerDistance));
    in.read(reinterpret_cast<char*>(&isActive), sizeof(isActive));
}

