#pragma once
#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "stdafx.h"
#include "Globals.h"
#include "Stalker.h"

class Player;

using namespace std;
using namespace sf;

class EnemyManager {
private:
	vector<Stalker*> stalkers;
	time_t spawnTimer;
	time_t timer;
	int spawnDelay;
public:
	EnemyManager();
	~EnemyManager();
	void Update(Player* player);
	void Draw();
	void SpawnStalkers(Player*);
	void DespawnStalker(Player*);
	void AddStalker(Stalker*); 
	float Distance(Vector2f v1, Vector2f v2)
	{
		return sqrt(pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2));
	}
};

#endif