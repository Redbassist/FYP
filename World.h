#pragma once 
#ifndef WORLD_H
#define WORLD_H

#include "stdafx.h" 
#include "Globals.h"
#include "House.h"
#include "Container.h"
#include "Item.h"
#include "Player.h"
#include "FillerObject.h" 
#include "EnemyManager.h"
#include "Tree.h"

using namespace sf;

class World {
private:
	Player* player;
	EnemyManager enemyManager;
	Texture m_texture;
	Sprite m_sprite;  
	std::vector<House*> houses;
	std::vector<Container*> containers;
	std::vector<Item*> items;
	std::vector<Tree*> trees;
	std::vector<FillerObject*> fillers; 
		
public:
	World();
	void CreateAssets();
	void CreateLevel();
	void Update();
	void Draw(); 
};

#endif