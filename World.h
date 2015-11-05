#pragma once 
#ifndef WORLD_H
#define WORLD_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Box2D\Box2D.h" 
#include "Player.h"
#include "Container.h"
#include "Item.h"
#include "InputManager.h"  

using namespace sf;

class World {
private:
	Player* player;
	std::vector<Container*> containers;
	std::vector<Item*> items; 
	b2World* world;
	RenderWindow* window;
	InputManager* inputManager;
		
public:
	World(RenderWindow*, b2World*, InputManager*);
	void CreateAssets();
	void CreateLevel();
	void Update();
	void Draw(); 
};

#endif