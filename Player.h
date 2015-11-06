#pragma once
#ifndef Player_H
#define Player_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Box2D\Box2D.h" 
#include "InputManager.h" 
#include "Inventory.h"
#include "Container.h"
#include "Door.h"

using namespace sf;

struct keyActions {
	bool walkLeft = false;
	bool walkRight = false;
	bool walkUp = false;
	bool walkDown = false;
	bool interact = false;
	bool drop = false;
	bool take = false;
	bool inventory = false;
};

class Player {
private:
	keyActions actions;
	Texture m_legTexture;
	Sprite m_legSprite;
	Texture m_bodyTexture;
	Sprite m_bodySprite;
	b2World* world; 
	b2Body* body;
	b2FixtureDef fixtureDef;
	Container* touchedContainer;
	std::vector<Item*> touchedItems;
	Door* touchedDoor;
	RenderWindow* window; 
	InputManager* inputManager;
	Vector2f m_pos;
	float orientation;
	float speed;
	Inventory* inventory;

public:
	Player(b2World*, RenderWindow*, InputManager*, Vector2f);
	void LoadAssets();
	void LoadBinds();
	void Draw();
	void Update();
	void Movement();
	void Interaction();
	void TouchingContainer(Container*);
	void NotTouchingContainer();
	void TouchingItem(Item*);
	void NotTouchingItem(Item*);
	void TouchingDoor(Door*);
	void NotTouchingDoor();
	void CenterCamera();
	void SetRotation();
	float getRotationAngle();
	void createBox2dBody();
	b2Vec2 Normalize(b2Vec2);
};

#endif
