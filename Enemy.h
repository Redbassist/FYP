#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "stdafx.h"
#include "Globals.h"
#include "Animation.h"
#include "AnimatedSprite.h" 
#include "Door.h"
 
class Enemy {
private:
	float SCALE = 30.0f;

	float health;

	Vector2f m_pos;
	float orientation;
	float speed;
	Vector2f movementTarget;

	Texture phTexture;
	Sprite phSprite;

	b2Body* body;
	b2FixtureDef fixtureDef;

	sf::Clock frameClock;
	time_t timer;

	vector<std::pair<b2RayCastInput, RayCastCallBack>> visionRays;
	int numberRays;

public:
	Enemy(Vector2f);
	~Enemy();
	void LoadAssets();
	void createBox2dBody();
	void Update();
	void CreateRays();
	void UpdateRays();
	void Draw();
	void Movement();
	void SampleAI();
	float GetRotationAngle();
	Vector2f Normalize(Vector2f);
	float Distance(Vector2f, Vector2f);
};

#endif