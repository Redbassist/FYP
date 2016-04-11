#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	spawnTimer = time(&timer);
	spawnDelay = 0;
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update(Player* player)
{
	SpawnStalkers(player);
	DespawnStalker(player);

	int size = stalkers.size();
	for (int i = 0; i < size; i++) {
		stalkers[i]->Update();
	}
}

void EnemyManager::Draw()
{
	int size = stalkers.size();
	for (int i = 0; i < size; i++) {
		if (stalkers[i]->destroy) {
			delete stalkers[i];
			stalkers.erase(stalkers.begin() + i);
			size = stalkers.size();
			i--;
		}
		else
			stalkers[i]->Draw();
	}
}

void EnemyManager::SpawnStalkers(Player * player)
{
	//spawns an enemy just off the screen from the player every certain amount of time
	if (difftime(time(&timer), spawnTimer) > spawnDelay) {
		float width = 1280 * 0.7;
		float height = 720 * 0.7;

		Vector2f playerPos = player->GetPosition();
		Vector2f p2 = Vector2f(playerPos.x - width / 2, playerPos.y - height / 2);
		Vector2f p3 = Vector2f(p2.x - 200, p2.y - 200);
		Vector2f size2 = Vector2f(width + 200, height + 200);
		Vector2f p4 = Vector2f(p2.x + size2.x, p2.y + size2.y);

		bool spawned = false;

		while (!spawned) {
			float randX = rand() % (int)(p4.x - p3.x + 1) + (int)p3.x;
			float randY = rand() % (int)(p4.y - p3.y + 1) + (int)p3.y;

			if (randX > p2.x && randX < p2.x + width && randY > p2.y && randY < p2.y + height) {

			}
			else {
				stalkers.push_back(new Stalker(Vector2f(randX, randY), player));
				spawned = true;
			} 
		}

		spawnDelay = rand() % 20 + 10;
		spawnTimer = time(&timer);
	}
}

void EnemyManager::DespawnStalker(Player *)
{
}

void EnemyManager::AddStalker(Stalker * s)
{
	stalkers.push_back(s);
}
