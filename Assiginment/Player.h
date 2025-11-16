#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Utils.h"   
#include "World.h"
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include "GameObject.h"

class Player : public Gameobject {
private:

	// Animation related
    float timeElapsed_anim = 0.f; 
    float timeThreshold_anim = 0.3f; 
	//If AOE attack is applied
    bool ifApplyAOE = false; 
public:
	//Constructor
    Player(int _x, int _y);
	//Copy constructor and assignment operator
    Player& operator=(const Player& other);
    bool getIfApplyAOE() {
        return ifApplyAOE;
    }
  
    void setAOE(bool flag) {
        ifApplyAOE = flag;
    }
	//Update movement animation based on direction
    void updateMovementAnim(std::string name);
    void update(float dt, GamesEngineeringBase::Window& canvas, World& world, Camera& cam);

    
    void serialize(ofstream& out) const;
    void deserialize(ifstream& in);
};

#endif 