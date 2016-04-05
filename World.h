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
#include "Stalker.h"
#include "Tree.h"

using namespace sf;

class World {
private:
	Player* player;
	Texture m_texture;
	Sprite m_sprite;  
	std::vector<House*> houses;
	std::vector<Container*> containers;
	std::vector<Item*> items;
	std::vector<Tree*> trees;
	std::vector<FillerObject*> fillers;
	std::vector<Stalker*> stalkers;
		
public:
	World();
	void CreateAssets();
	void CreateLevel();
	void Update();
	void Draw(); 
};

#endif