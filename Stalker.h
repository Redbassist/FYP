#pragma once
#ifndef STALKER_H
#define STALKER_H

#include "stdafx.h"
#include "Globals.h" 
#include "Enemy.h"

class Stalker : public Enemy {
private:
	float SCALE = 30.0f; 
	float searchOrientation;  

	Texture m_AnimationLegsTexture;
	Animation legsIdle;
	Animation legsMoving;
	Animation* currentLegAnimation;
	AnimatedSprite animatedLegSprite;


	sf::Clock frameClock;
	time_t timer;
	time_t doorSearchTimer;
	time_t playerChaseTimer;

	vector<std::pair<b2RayCastInput, RayCastCallBack>> visionRays;
	vector<std::pair<b2RayCastInput, RayCastCallBack>> avoidanceRays;
	int numberRays;
	std::pair<b2RayCastInput, RayCastCallBack> spottedRay;

	bool search = false;
	bool walk = true;
	bool door = false;
	bool searchDoor = true;
	bool searchPlayer = false;
	bool stop = false;
	bool playerSpotted = false;
	bool chasing = false;
	bool lookAround = false;
	bool lookRight = false;
	bool nearDoor = false;
	bool nearLastSpot = false;
	bool lostPlayer = false;
	bool avoid = false;

	bool moving;

	int searchDirection;
	Player* spottedPlayer;

	int avoidDistance;
	Vector2f avoidPoint;

	sf::Vector2f doorLocation;

	b2Body* punchbody;
	b2FixtureDef punchfixtureDef;
	bool punch = false;
	int punchDirection = 0;
	int punchDistance = 0;
	int maxPunchDistance = 55;

public:
	Stalker(Vector2f);
	~Stalker();
	void LoadAssets();
	void EasyLoadAssetsAnimation(Texture * t, string file, Animation * anim, int frames, int columns, int rows, int individualWidth, int individualHeight, Animation * current);
	void EasyLoadAssetsAnimation(Texture * t, string file, Animation * anim, int frames, int columns, int rows, int individualWidth, int individualHeight);
	void createBox2dBody();
	void createPunchBox2dBody();
	void CreateRays();
	void Update();
	void UpdateRays();
	void Draw();
	void Movement();
	void AI();
	void AIFunction(bool, int);
	void AvoidObstacles();
	void LookAround();
	void SearchDoor(bool onlyFind);
	void SearchPlayer();
	void SpottedAI();
	void HittingPlayer();
	bool HitPlayer();
	float VectorToAngle(b2Vec2 vec);
};

#endif