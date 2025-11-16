#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Utils.h"  
#include "GamesEngineeringBase.h"

class Camera {
private:
    //表示摄像机左上角在世界坐标系中的位置。
    // Represents the position of the camera's top-left corner in the world coordinate system.
    Vec2 position; 
	//摄像机视图的宽度和高度。
	// Width and height of the camera view.
    int width; 
    int height; 
public:
	//构造函数，初始化摄像机视图的宽度和高度。
	// Constructor that initializes the camera view's width and height.
    Camera(GamesEngineeringBase::Window& canvas);

	//获取摄像机视图的宽度和高度。
	// Get the width and height of the camera view.
    int getViewWidth() { return width;  }
    int getViewHeight() { return height; }
	//获取摄像机在世界坐标系中的位置。
	// Get the camera's position in the world coordinate system.
	Vec2 getCameraPos() { return position; }


	//根据玩家位置更新摄像机位置。
	// Update the camera position based on the player's position.
    void update(const Vec2& playerPos);
	//将对象的世界坐标转换为屏幕坐标。
	// Convert an object's world coordinates to screen coordinates.
    Vec2 worldToScreen(const Vec2& objPosition) const; 
	

    
    void serialize(std::ofstream& out) const;
    void deserialize(std::ifstream& in);
};

#endif