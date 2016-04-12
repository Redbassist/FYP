#pragma once
#ifndef STALKER_H
#define STALKER_H

#include "stdafx.h"
#include "Globals.h" 
#include "Enemy.h"
#include "Player.h"

class Stalker : public Enemy {
private:
	float SCALE = 30.0f; 
	float searchOrientation;  

	Texture headTexture;
	Sprite headSprite;

	Texture m_AnimationLegsTexture;
	Animation legsIdle;
	Animation legsMoving;
	Animation* currentLegAnimation;
	AnimatedSprite animatedLegSprite;

	Texture m_AnimationWalkTexture;
	Animation topIdle;
	Animation topMoving;
	Animation* currentTopAnimation;
	AnimatedSprite animatedTopSprite;

	Texture m_PunchLeftTexture;
	Animation punchLeft; 
	AnimatedSprite animatedPunchLeft;

	Texture m_PunchRightTexture;
	Animation punchRight;
	AnimatedSprite animatedPunchRight;

	Texture m_deathTexture;
	Animation death;
	AnimatedSprite animatedDeath;

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
	bool damage = true;
	int punchDirection = 0;
	int punchDistance = 0;
	int maxPunchDistance;
	time_t punchTimer;

	b2Body* hitBody;
	b2FixtureDef hitfixtureDef;

	time_t deathTimer;
	bool collapse;

	time_t chatterTimer;
	int chatterDelay;

public:
	Stalker(Vector2f);
	Stalker(Vector2f, Player* );
	~Stalker();
	void LoadAssets();
	void EasyLoadAssetsAnimation(Texture * t, string file, Animation * anim, int frames, int columns, int rows, int individualWidth, int individualHeight, Animation * current);
	void EasyLoadAssetsAnimation(Texture * t, string file, Animation * anim, int frames, int columns, int rows, int individualWidth, int individualHeight);
	void createBox2dBody();
	void createHitBox2dBody();
	void createPunchBox2dBody();
	void CreateRays();
	void Update();
	void UpdateRays();
	void Draw();
	void Movement();
	void RotateOrientation();
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