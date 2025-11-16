#include "Camera.h"
#include "Constants.h"
#include "Utils.h"  
#include "GamesEngineeringBase.h"
#include <fstream>

using namespace std;
using namespace GamesEngineeringBase;

Camera::Camera(Window& canvas) {
    width = canvas.getWidth();
    height = canvas.getHeight();
}
void Camera::update(const Vec2& playerPos) {
    //把相机中心对齐玩家
	// Center the camera on the player
    position.x = playerPos.x - getViewWidth() / 2+32;
    position.y = playerPos.y - getViewHeight() / 2+32;
    // 左上角边界限制
	//boundary limit for top-left corner
    if (position.x < 0)position.x = 0;
    if (position.y < 0)position.y = 0;
    // 右下角边界限制
	//boundary limit for bottom-right corner
    if (position.x + getViewWidth() > mapWidth) position.x = mapWidth - getViewWidth();
    if (position.y + getViewHeight() > mapHeight) position.y = mapHeight - getViewHeight();
}
Vec2 Camera::worldToScreen(const Vec2& objPosition) const {
	//世界坐标转换为屏幕坐标
	// Convert world coordinates to screen coordinates
    Vec2 vector;
    vector.x = objPosition.x - position.x;
    vector.y = objPosition.y - position.y;
    return vector;
}

//序列化摄像机位置
// Serialize camera position
void Camera::serialize(ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&position), sizeof(position));
}
//反序列化摄像机位置
// Deserialize camera position
void Camera::deserialize(ifstream& in) {
    in.read(reinterpret_cast<char*>(&position), sizeof(position));
}