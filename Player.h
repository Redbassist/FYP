#pragma once
#ifndef Player_H
#define Player_H

#include "stdafx.h"
#include "Globals.h"
#include "Animation.h"
#include "AnimatedSprite.h" 
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
	RenderWindow* window;
	InputManager* inputManager;

	keyActions actions;
	Texture m_AnimationLegsTexture;
	Texture m_AnimationTopTexture;
	Animation legsIdle;
	Animation legsMoving;
	Animation playerTopIdle;
	Animation playerTopMoving;
	Animation* currentLegAnimation;
	Animation* currentTopAnimation;
	AnimatedSprite animatedLegSprite;
	AnimatedSprite animatedTopSprite;
	 
	b2Body* body;
	b2FixtureDef fixtureDef;

	Container* touchedContainer;
	std::vector<Item*> touchedItems;
	Door* touchedDoor;

	Vector2f m_pos;
	float orientation;
	float speed;
	Inventory* inventory;

	sf::Clock frameClock;

public:
	Player(RenderWindow*, InputManager*, Vector2f);
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
