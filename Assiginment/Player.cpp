#include "Player.h"
#include "World.h"
#include "Constants.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace GamesEngineeringBase;
//Constructor
Player::Player(int _x, int _y) {
    Spritefilename =  "Resources/right0.png";
    sprite.load(Spritefilename);
    worldPos.x = _x;
    worldPos.y = _y;
    speed = playerSpeed;
    ProjSpeed = playerProjSpeed; 
    health = playerHealth;
    shootingRange = linearAttackRange; 
    type = "Player";
}
//Copy constructor and assignment operator
Player& Player::operator=(const Player& other) {
    if (this == &other) {
        return *this; 
    }
    Gameobject::operator=(other);
    timeElapsed_anim = other.timeElapsed_anim;
    ifApplyAOE = other.ifApplyAOE;
}
//加载并更新移动动画
// Load and update movement animation
void Player::updateMovementAnim(string name) {
    string fileName1 = "Resources/" + name + "0.png";
    string fileName2 = "Resources/" + name + "1.png";
    if (timeElapsed_anim < timeThreshold_anim) sprite.load(fileName1);
    else if (timeElapsed_anim < 2 * timeThreshold_anim) {
        sprite.load(fileName2);
    }
    else timeElapsed_anim = 0.f;
}
//更新玩家位置及状态
// Update player position and state
void Player::update(float dt, Window& canvas, World& world, Camera& cam) {
    int move = static_cast<int>(speed * dt);
    int moveX = 0;
    int moveY = 0;
    timeElapsed_anim += dt;
	//WASD 控制移动
	// WASD controls movement
    if (canvas.keyPressed('W')) {
        moveY -= move;
    }
    if (canvas.keyPressed('S')) {
        moveY += move;
    }
    
    if (canvas.keyPressed('A')) {
        updateMovementAnim("left");
        moveX -= move;
    }

    if (canvas.keyPressed('D')) {
        updateMovementAnim("right");
        moveX += move;
    }
	//按下 E 键触发 AOE 攻击
	// Press E key to trigger AOE attack
    if (canvas.keyPressed('E') && !ifStartCooldown) {
        ifApplyAOE = true;
    }
	
    int posXNew = worldPos.x + moveX;
    int posYNew = worldPos.y + moveY;
	//检查新位置是否可通行
	// Check if the new position is passable
    if (world.checkTilePassable(posXNew, posYNew)) {
        worldPos.x = posXNew;
        worldPos.y = posYNew;
        if (worldPos.x < 0) worldPos.x = 0;
        if (worldPos.y < 0) worldPos.y = 0;
        if ((worldPos.x + playerSpriteSize) > mapWidth) worldPos.x = mapWidth - playerSpriteSize;
        if ((worldPos.y + playerSpriteSize) > mapHeight) worldPos.y = mapHeight - playerSpriteSize;
    }
	//更新屏幕位置
	// Update screen position
    screenPos = cam.worldToScreen(worldPos);

	//更新闪烁状态
	// Update flicker state
    updateFlickerState(dt);
}

//序列化
// Serialization
void Player::serialize(ofstream& out) const {
       Gameobject::serialize(out);
    out.write(reinterpret_cast<const char*>(&timeElapsed_anim), sizeof(timeElapsed_anim));
    out.write(reinterpret_cast<const char*>(&ifApplyAOE), sizeof(ifApplyAOE));
 }
//反序列化
// Deserialization
void Player::deserialize(ifstream& in) {
       Gameobject::deserialize(in);
    in.read(reinterpret_cast<char*>(&timeElapsed_anim), sizeof(timeElapsed_anim));
    in.read(reinterpret_cast<char*>(&ifApplyAOE), sizeof(ifApplyAOE));
}