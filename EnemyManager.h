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
};

#endif