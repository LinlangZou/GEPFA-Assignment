#include "NPCmanager.h"
#include "Constants.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace GamesEngineeringBase;

NPCmanager::NPCmanager() {}

NPCmanager::~NPCmanager() {
    for (int i = 0; i < currentNum; i++) {
        delete npc_array[i];
    }
}
//深拷贝赋值运算符重载
// Deep copy assignment operator overload
NPCmanager& NPCmanager::operator=(const NPCmanager& other) {
    // 防止自赋值导致删除自身数据
	// Prevent self-assignment leading to deletion of own data
    if (this == &other) return *this; 
    currentNum = other.currentNum;
    timeElapsed = other.timeElapsed;
    for (int i = 0; i < maxNPCNum; ++i) {
        delete npc_array[i];
        npc_array[i] = nullptr;
    }
    for (int i = 0; i < maxNPCNum; ++i) {
        if (other.npc_array[i] != nullptr) {
            npc_array[i] = new NPC(*other.npc_array[i]); 
        }
        else npc_array[i] = nullptr; 
    }
    for (int i = 0; i < maxNPCNum; ++i) {
        sort_health_array[i] = other.sort_health_array[i];
    }
    return *this;
}

//随机生成 NPC 的出生点，必须保证 NPC 出生位置在 地图范围内
// 并且不在摄像机当前视野内
// Randomly generate NPC spawn points, 
// ensuring they are within the map boundaries
// and outside the current camera view
Vec2 NPCmanager::generateStartPos(Camera& camera) {
    Vec2 camPos = camera.getCameraPos();
    int width = camera.getViewWidth();
    int height = camera.getViewHeight();
    bool inMap, inView;
    int x, y;
   
    do {
        x = rand() % mapWidth;
        y = rand() % mapHeight;
        inMap = (x > 0 && x + npcSpriteSize < mapWidth) && (y > 0 && y + npcSpriteSize < mapHeight);
        inView = (x + npcSpriteSize >= camPos.x && x <= camPos.x + width)
            && (y + npcSpriteSize >= camPos.y && y <= camPos.y + height);
        //决定是否退出循环
        // 如果条件不满足 → 再随机生成一次
		// Decide whether to exit the loop
		// If conditions are not met → generate again
        if (inMap == true && inView == false)
            break;
    } while (1);
	//返回生成的出生点
	// Return the generated spawn point
    Vec2 startPos;
    startPos.x = x;
    startPos.y = y;
    return startPos;
}
//生成 NPC 并加入 npc_array
// Generate NPCs and add them to npc_array
void NPCmanager::createNPC(Camera& camera, float& dt) {

    timeElapsed += dt;
    if (currentNum < maxNPCNum) {
        if (timeElapsed > timeThreshold) {
            Vec2 pos = generateStartPos(camera);
			//随机选择 NPC 类型
			// Randomly select NPC type
            int NPCtypeIndex = rand() % 4;
            int health ;
            float speed ;
            string filename = "Resources/npc" + to_string(NPCtypeIndex) + ".png";
            switch (NPCtypeIndex) {
				// Different NPC types with varying health and speed
                
				 //melee fast NPC
            case 0:
                health = NPC0Health;
                speed = NPC0Speed;
                break;
				//melee balanced NPC
            case 1:
                health = NPC1Health;
                speed = NPC1Speed;
                break;
				//melee tank NPC
            case 2:
                health = NPC2Health;
                speed = NPC2Speed;
                break;
                //shooting NPC
            case 3:
                health = NPC3Health;
                speed = NPC3Speed;
                break;
                
            }
          
            NPC* _npc = new NPC(pos, filename, health, speed);
            npc_array[currentNum++] = _npc;
           
            //生成一只 NPC 所需的时间间隔（秒） 
           // Time interval required to spawn an NPC (seconds)
            timeElapsed = 0.f;
            //从上一次生成到现在经过的时间 
            /// Time elapsed since the last spawn
            timeThreshold -= 0.1f;
            //限制生成间隔最短为 0.5秒  
            //Limit the minimum spawn interval to 0.5 seconds
            timeThreshold = max(0.5f, timeThreshold);

        }
    }
}
//检查并删除已死亡的 NPC
// Check and delete dead NPCs
void NPCmanager::checkDeleteNPC(unsigned int i) {
    if (!npc_array[i]->getIsAlive()) { 
        NPC* _npc = npc_array[i];
        //in
        scores += 1000;
        cout << "NPC killed! Current score: " << scores << endl;
        if (linearTimeThreshold >= 0.8f) {
            AOENumber += 1;
            linearTimeThreshold -= 0.2f;
            cout << "Increase AOE count  to " << AOENumber << endl
                  << "Increase linear attack speed" << endl;
        }
        else
            cout << "Maximum AOE count: " << AOENumber<< " reached!" << endl
			<< "Linear attack speed is at maximum!" << endl;
        npc_array[i] = nullptr;
        delete _npc;
        currentNum--;
    }
}
//更新 NPC 位置及状态
// Update NPC positions and states
void NPCmanager::update(float& dt, Vec2& playerPos, Camera& camera) {
   
    createNPC(camera, dt);
    for (int i = 0; i < currentNum; i++) {
        sort_health_array[i].x = i;
        if (npc_array[i] != nullptr) {
            npc_array[i]->update(dt, playerPos, camera);
			//更新 NPC 的血量到辅助排序数组
			// Update NPC health to auxiliary sorting array
            sort_health_array[i].y = npc_array[i]->getHealth();
            
            checkDeleteNPC(i);
        }
		// NPC 已死亡，血量设为0
		// NPC is dead, set health to 0
        else sort_health_array[i].y = 0;

    }
}
//绘制 NPC 及其血条和受击闪烁效果
// Draw NPCs along with their health bars and hit flicker effects
void NPCmanager::draw(Window& canvas) {
    for (int i = 0; i < currentNum; i++) {
        if (npc_array[i] != nullptr) {
            npc_array[i]->draw(canvas); 
            npc_array[i]->drawHealthBar(canvas); 
            npc_array[i]->drawFlicker(canvas, FlickerColor); 
        }
    }
}

//检测 NPC 与玩家的碰撞
// Check collision between NPCs and the player
void NPCmanager::checkNPCPlayerCollision(Player& player) {
    for (int i = 0; i < currentNum; i++) {
        if (npc_array[i] != nullptr) {
            if (npc_array[i]->checkCollision(player.getWorldPos())) {
				//发生碰撞，玩家受到伤害并开始闪烁
				// Collision occurred, player takes damage and starts flickering
                player.setIfStartFlicker(1);
                player.applyDamage(meleeDamege);
            }
        }
    }
}
//速度为0的 NPC 才会发射子弹
// Only NPCs with speed 0 will shoot projectiles
void NPCmanager::setProjectiles(float dt, Gameobject& obj, Camera& camera) {
    for (int i = 0; i < currentNum; i++) {
        if (npc_array[i] != nullptr && npc_array[i]->getSpeed() == 0.f && npc_array[i]->getIsActive()) {
            npc_array[i]->updateProjectiles(dt, obj, camera);
        }
    }
}
//绘制速度为0的 NPC 的子弹
// Draw projectiles of NPCs with speed 0
void NPCmanager::drawProjectiles(Window& canvas) {
    for (int i = 0; i < currentNum; i++) {
		// Only draw projectiles for NPCs with speed 0 and in aggro state
        if (npc_array[i] != nullptr && npc_array[i]->getSpeed() == 0.f && npc_array[i]->getIsActive()) {
            npc_array[i]->drawProjectiles(canvas);
        }
    }
}
//检查是否有 NPC 在玩家的攻击范围内
// Check if any NPC is within the player's attack range
bool NPCmanager::getIfNPCinPlayerAttackRange() {
    for (int i = 0; i < currentNum; i++) {
		//遍历所有 NPC，检查是否有 NPC 在玩家的攻击范围内
		// Iterate through all NPCs to check if any are within the player's attack range
        if (npc_array[i] != nullptr &&
            npc_array[i]->getNPCPlayerDistance() < linearAttackRange) {
            return true;
        }
    }
    return false;
}

//获取距离玩家最近的 NPC 指针
// Get pointer to the NPC closest to the player
NPC* const NPCmanager::getClosestNPC() {
    int min = 1000;
    int index = -1;
	//遍历所有 NPC，找到距离玩家最近且处于激怒状态的 NPC
	// Iterate through all NPCs to find the one closest to the player and in aggro state
    for (int i = 0; i < currentNum; i++) {
        if (npc_array[i] != nullptr && npc_array[i]->getIsActive()) {
            if (min > npc_array[i]->getNPCPlayerDistance()) {
                min = npc_array[i]->getNPCPlayerDistance();
                index = i;
            }
        }
    }
    if (index == -1) {
       
        return nullptr;
    }
    return npc_array[index];
}
// 快速排序 NPC 血量数组，按血量从高到低排序
// Quick sort NPC health array in descending order
void QuickSortByHealth(Vec2* arr, int start, int end)
{
	//交换变量
	// Swap variable
    Vec2 change;
	//递归终止条件
	// Recursion termination condition
    if (start >= end) return;
	//设置左右指针和基准
	// Set left and right pointers and pivot
    int left = start;
    int right = end;
    int key = start; 
    while (start < end)
    {
		// 从右向左找比基准小的值
		// Find a value smaller than the pivot from right to left
        while (arr[end].y <= arr[key].y && start < end) end--;
        while (arr[start].y >= arr[key].y && start < end) start++;
		//交换两个数在数组中的位置
		// Swap the positions of the two numbers in the array
         change=arr[start] ;
         arr[start] = arr[end];
         arr[end] = change;
        }
	//交换基准数与最终位置的数
	// Swap the pivot with the number at its final position
    change = arr[key];
    arr[key] = arr[end];
    arr[end] = change;
    key = end;
	//递归排序基准左右两侧的数组
	// Recursively sort the arrays on both sides of the pivot
    QuickSortByHealth(arr, left, key - 1);
    QuickSortByHealth(arr, key + 1, right);
}

// 对血量最高的N个 NPC 进行 AOE 攻击
// Perform AOE attack on the top n NPCs with highest health
void NPCmanager::AOE() {
      QuickSortByHealth(sort_health_array, 0, 99);

    int AOEGoat = 0;
      for (int i = 0; i < currentNum; i++) {
        int index = sort_health_array[i].x;
        if (AOEGoat < AOENumber && npc_array[index] != nullptr) {
			//检查 NPC 是否在 AOE 攻击范围内
			// Check if NPC is within AOE attack range
            if (npc_array[index]->getNPCPlayerDistance() < AOEAttackRange) {
                npc_array[index]->applyDamage(AOEDamage);
                npc_array[index]->setIfStartFlicker(2);
				//记录已进行 AOE 攻击的 NPC 数量
				// Record the number of NPCs that have undergone AOE attack
                AOEGoat++;
                
            }
        }
    }
}
//序列化 NPCmanager 对象
// Serialize NPCmanager object
void NPCmanager::serialize(ofstream& out) const {

    out.write(reinterpret_cast<const char*>(&currentNum), sizeof(currentNum));
	//保存每个 NPC 是否存在的标志位
	// Save flag indicating whether each NPC exists
    for (int i = 0; i < currentNum; i++) {
        bool hasNPC = (npc_array[i] != nullptr);
        out.write(reinterpret_cast<const char*>(&hasNPC), sizeof(hasNPC));
        if (hasNPC) {
            npc_array[i]->serialize(out);
        }

    }
    out.write(reinterpret_cast<const char*>(&timeElapsed), sizeof(timeElapsed));
    out.write(reinterpret_cast<const char*>(&sort_health_array), sizeof(sort_health_array));

}
//反序列化 NPCmanager 对象
// Deserialize NPCmanager object
void NPCmanager::deserialize(ifstream& in) {

    in.read(reinterpret_cast<char*>(&currentNum), sizeof(currentNum));
	//读取每个 NPC 是否存在的标志位
	// Read flag indicating whether each NPC exists
    for (int i = 0; i < currentNum; i++) {
        bool hasNPC;
        in.read(reinterpret_cast<char*>(&hasNPC), sizeof(hasNPC));
        if (hasNPC) {
            npc_array[i] = new NPC();
            npc_array[i]->deserialize(in);
            npc_array[i]->setSprite();
        }
    }
	//读取 timeElapsed 和 sort_health_array
	// Read timeElapsed and sort_health_array
    in.read(reinterpret_cast<char*>(&timeElapsed), sizeof(timeElapsed));
    in.read(reinterpret_cast<char*>(&sort_health_array), maxNPCNum * sizeof(Vec2));
}
