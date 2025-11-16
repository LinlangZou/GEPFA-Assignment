#include <iostream>
#include <fstream>
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include "Player.h"
#include "World.h"
#include "NPCmanager.h"
#include "GameState.h"
#include "Utils.h"

using namespace std;
using namespace GamesEngineeringBase;


int main() {
    Window canvas;
    canvas.create(1024, 768, "MYGAME");
    World world(canvas);
    Camera camera(canvas);
    Player player(500, 500);
    NPCmanager npcs;
    Timer timer;
    Gamestate gamestate(player, camera, world, npcs);

    bool running = true;
    bool playerStartsAttack = false;

    while (running)
    {
		// Handle window events and input
        canvas.checkInput();
        
		// Exit confirmation on ESC key press
        if (canvas.keyPressed(VK_ESCAPE)) {
			
            std::cout << "Are you sure you want to quit? (Y/N)" << std::endl;
            Sleep(3000); 
            running = false;
            cout <<endl<<endl<< "Total number of NPCs defeated:"<< scores/1000<<endl<<"Total scores:" << scores << endl;
        }

      
        canvas.clear();

        // 确保把 GPU 要求的对齐(padded) 区域也清零，避免未初始化数据出现在边缘
		// ensure the padded area required by the GPU is also cleared to avoid uninitialized data appearing at the edges
       // unsigned int dataSize = canvas.getWidth() * canvas.getHeight() * 3;
       // unsigned int paddedDataSize = ((dataSize + 3) / 4) * 4;
       // memset(canvas.getBackBuffer(), 0, paddedDataSize)

        float dt = timer.dt();

        //update
       player.update(dt, canvas, world, camera);
        Vec2 playerPos = player.getWorldPos();
        camera.update(playerPos);
        npcs.update(dt, playerPos, camera);
        npcs.setProjectiles(dt, player, camera);
        npcs.checkNPCPlayerCollision(player);

		//attack 
        if (player.getIfApplyAOE() && !ifStartCooldown) {
            npcs.AOE();
            player.setAOE(false);
            ifStartCooldown = true;
        }
        else {
            playerStartsAttack = npcs.getIfNPCinPlayerAttackRange();
            if (playerStartsAttack) {
                NPC* closestNPC = npcs.getClosestNPC();
                player.updateProjectiles(dt, *closestNPC, camera);
            }
        }
       
        if (ifStartCooldown) {
            AOECooldowntimeElapsed += dt;
            if (AOECooldowntimeElapsed > AOECooldowntimeThreshold) {
                AOECooldowntimeElapsed = 0.f;
                ifStartCooldown = false;
            }
        }

    
        
         //draw      
        Vec2 camPos = camera.getCameraPos();
        world.draw(canvas, camPos);
        player.draw(canvas);
        player.drawHealthBar(canvas);
        player.drawFlicker(canvas, FlickerColor);
        if (playerStartsAttack)player.drawProjectiles(canvas);
        npcs.draw(canvas);
        npcs.drawProjectiles(canvas);

		//draw line to closest NPC
		NPC* closestNPC = npcs.getClosestNPC();
        if (closestNPC) {
         Vec2 drawLineStart = { player.getScreenPos().x+playerSpriteSize/2,player.getScreenPos().y+ playerSpriteSize / 2 };
         Vec2 drawLineEnd = { closestNPC->getScreenPos().x+ npcSpriteSize/2, closestNPC->getScreenPos().y + npcSpriteSize/2 };
        void drawLine(Window & canvas, Vec2 pos1, Vec2 pos2);
		 drawLine1(canvas, drawLineStart, drawLineEnd);
        }

        canvas.present();

        //Output FPS
        if (running!= false) {
            void getFPS(const float& dt);
            getFPS(dt);
        }


		//save and load
        if (canvas.keyPressed('K')) {
            gamestate.saveState();
        }
        if (canvas.keyPressed('L')) {
            gamestate.loadState(player, camera, world, npcs);
        }

    }
    return 0;
}
//计算并输出FPS
// Calculate and output FPS
float timeElapsed = 0.f;
void getFPS(const float& dt) {
    float fps = 1 / dt;
    timeElapsed += dt;
    if (timeElapsed > 1.f) {
        cout << "FPS : " << fps << endl;
        timeElapsed = 0.f;
    }
}
//Bresenham 直线绘制算法
// Bresenham’s Line Algorithm

void drawLine(Window& canvas, Vec2 pos1, Vec2 pos2) {
    int x1 = pos1.x;
    int y1 = pos1.y;
    int x2 = pos2.x;
    int y2 = pos2.y;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    while (true) {
        if (x1 >= 0 && x1 < canvas.getWidth() && y1 >= 0 && y1 < canvas.getHeight()) {
            canvas.draw(x1, y1, 255, 0, 0); // Draw pixel in red color
        }
        if (x1 == x2 && y1 == y2) break;
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
	}

}