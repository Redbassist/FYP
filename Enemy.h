#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "stdafx.h"
#include "Globals.h"
#include "Animation.h"
#include "AnimatedSprite.h" 
#include "Door.h"
#include "Player.h"
 
class Enemy {
protected:
	float SCALE = 30.0f;
	Vector2f movementTarget;

	float health;

	Texture phTexture;
	Sprite phSprite;

	Vector2f m_pos;
	float orientation; 
	float speed;  

	b2Body* body;
	b2FixtureDef fixtureDef; 

public:
	Enemy(Vector2f); 
	~Enemy();
	virtual void LoadAssets();
	void createBox2dBody(); 
	virtual void Update(); 
	virtual void Draw();
	virtual void Movement();   
	float GetRotationAngle();
	Vector2f Normalize(Vector2f);
	float Distance(Vector2f, Vector2f);
};

#endif