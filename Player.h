#pragma once
#ifndef Player_H
#define Player_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Box2D\Box2D.h" 
#include "InputManager.h" 
#include "Inventory.h"

using namespace sf;

struct keyActions {
	bool walkLeft = false;
	bool walkRight = false;
	bool walkUp = false;
	bool walkDown = false;
	bool pickup = false;
	bool drop = false;
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
	std::vector<Item*> touchedItems;
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
	void TouchingItem(Item*);
	void NotTouchingItem(Item*);
	void CenterCamera();
	void SetRotation();
	float getRotationAngle();
	void createBox2dBody();
	b2Vec2 Normalize(b2Vec2);
};

#endif
