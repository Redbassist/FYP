#pragma once
#ifndef Player_H
#define Player_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Box2D\Box2D.h" 
#include "InputManager.h"

using namespace sf;

static const float SCALE = 30.f;

struct keyActions {
	bool walkLeft = false;
	bool walkRight = false;
	bool walkUp = false;
	bool walkDown = false;
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
	RenderWindow* window; 
	InputManager* inputManager;
	Vector2f m_pos;
	float orientation;
	float speed;

public:
	Player(b2World*, RenderWindow*, InputManager*, Vector2f);
	void LoadAssets();
	void LoadBinds();
	void Draw();
	void Update();
	void Movement();
	void SetRotation();
	float getRotationAngle();
	void createBox2dBody();
	b2Vec2 Normalize(b2Vec2);
};

#endif
