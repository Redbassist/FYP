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
	bool searchPlayer = false;
	bool stop = false;
	bool playerSpotted = false;
	bool chasing = false;
	bool lookAround = false;
	bool lookRight = false;
	bool nearDoor = false;
	bool nearLastSpot = false;
	bool lostPlayer = false;

	int searchDirection;
	Player* spottedPlayer;

	sf::Vector2f doorLocation;

public:
	Stalker(Vector2f);
	~Stalker();
	void LoadAssets();
	void createBox2dBody();
	void CreateRays();
	void Update();
	void UpdateRays();
	void Draw();
	void Movement();
	void AI();
	void AIFunction(bool, int);
	void LookAround();
	void SearchDoor(bool onlyFind);
	void SearchPlayer();
	void SpottedAI();
};

#endif