#pragma once 
#ifndef WORLD_H
#define WORLD_H

#include "stdafx.h" 
#include "Globals.h"
#include "ThreadGlobals.h"
#include "House.h"
#include "Container.h"
#include "Item.h"
#include "Player.h"
#include "EnemyPlayer.h"
#include "FillerObject.h" 
#include "EnemyManager.h"
#include "Tree.h"

#include <sstream>

using namespace sf;
using namespace std;

struct PlayerSaveData {
	float health;
	float hunger;
	float thirst;
	Vector2f position;
	vector<Item*> invItems;
};

class Stalker;
class Inventory;

class World {
private:
	bool loadedCharacrter;

	Player* player;
	vector<EnemyPlayer*> enemyPlayers;
	EnemyManager enemyManager;
	Texture m_texture;
	Sprite m_sprite;  
	std::vector<House*> houses;
	std::vector<Container*> containers;
	std::vector<Item*> items;
	std::vector<Tree*> trees;
	std::vector<FillerObject*> fillers; 
	std::vector<Wall*> boundaries;
	bool multiplayer;
	int poop = 0;
public:
	World(bool, bool);
	void CreateAssets();
	void CreateLevel();
	void Update();
	void Draw(); 
	void SavePlayer();
	void LoadPlayer();
	void DeletePlayerSave();
};

#endif