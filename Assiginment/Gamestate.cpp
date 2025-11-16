#include "Gamestate.h"
#include "Constants.h"
#include <iostream>



// Save the current game state to a file
void Gamestate::saveState() {
    ofstream outfile(filename, ios::binary);
    if (outfile.is_open()) {
        hero.serialize(outfile);
        camera.serialize(outfile);
        npcs.serialize(outfile);
        outfile.write(reinterpret_cast<const char*>(&AOECooldowntimeElapsed), sizeof(AOECooldowntimeElapsed));
        outfile.write(reinterpret_cast<const char*>(&ifStartCooldown), sizeof(ifStartCooldown));
        outfile.write(reinterpret_cast<const char*>(&scores), sizeof(scores));
        outfile.close();
        cout << "game saved " << endl;
    }
  
}
// Load the game state from a file
void Gamestate::loadState(Player& _hero, Camera& _camera, World& _world, NPCmanager& _npcs) {
    ifstream infile(filename, ios::binary);
    if (infile.is_open()) {
        hero.deserialize(infile);
        hero.setSprite();
        camera.deserialize(infile);
        npcs.deserialize(infile);
        infile.read(reinterpret_cast<char*>(&AOECooldowntimeElapsed), sizeof(AOECooldowntimeElapsed));
        infile.read(reinterpret_cast<char*>(&ifStartCooldown), sizeof(ifStartCooldown));
        infile.read(reinterpret_cast<char*>(&scores), sizeof(scores));
        infile.close();
        cout << "game loaded " << endl;
        _hero = hero;
        _camera = camera;
        _npcs = npcs;
    }

}
