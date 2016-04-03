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
private:
	float SCALE = 30.0f;

	float health;

	Vector2f m_pos;
	float orientation;
	float searchOrientation;
	float speed;
	Vector2f movementTarget;

	Texture phTexture;
	Sprite phSprite;

	b2Body* body;
	b2FixtureDef fixtureDef;

	sf::Clock frameClock;
	time_t timer;
	time_t doorSearchTimer;

	vector<std::pair<b2RayCastInput, RayCastCallBack>> visionRays;
	int numberRays;
	std::pair<b2RayCastInput, RayCastCallBack> spottedRay;

	bool search = false;
	bool walk = true;
	bool door = false;
	bool searchDoor = true;
	bool stop = false;
	bool playerSpotted = false;
	bool chasing = false;

	int searchDirection;
	Player* spottedPlayer;

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
	void SampleAIFunction(bool, int);
	void SearchDoor();
	void SearchPlayer();
	void SpottedAI();
	float GetRotationAngle();
	Vector2f Normalize(Vector2f);
	float Distance(Vector2f, Vector2f);
};

#endif