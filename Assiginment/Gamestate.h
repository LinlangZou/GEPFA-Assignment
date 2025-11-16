#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <fstream>
#include "GamesEngineeringBase.h"
#include "Camera.h"
#include "Player.h"
#include "World.h"
#include "NPCmanager.h"
#include "NPC.h"
using namespace GamesEngineeringBase;
using namespace std;

class Gamestate {
private:
	// Savegame file path
    string filename = "Resources/savegame.dat";
	// References to game components
    Player& hero;
    Camera& camera;
    World& world;
    NPCmanager& npcs;
public:
	// Constructor
    Gamestate(Player& _hero, Camera& _camera, World& _world, NPCmanager& _npcs) :
        hero(_hero), camera(_camera), world(_world), npcs(_npcs) {
    };
	// Save the current game state to a file
    void saveState();
	// Load the game state from a file
    void loadState(Player& _hero, Camera& _camera, World& _world, NPCmanager& _npcs);
	
    Player& getPlayer() { return hero; }
    Camera& getCamera() { return camera; }
    World& getWorld() { return world; }
    NPCmanager& getNPCmanager() { return npcs; }
};

#endif
