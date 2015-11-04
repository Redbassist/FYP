#include "World.h"

World::World(RenderWindow * rw, b2World * w, InputManager* im) : world(w), window(rw), inputManager(im) {
	CreateAssets();
	CreateLevel();
}

void World::CreateAssets() { 
}

void World::CreateLevel() {
	player = new Player(world, window, inputManager, Vector2f(20, 20));
	items.push_back(new Item(world, window, WATER2, 1, true, Vector2f(100, 100)));
} 

void World::Update() {
	player->Update();
}

void World::Draw() {
	int size = items.size();
	for (int i = 0; i < size; i++) {
		items[i]->Draw();
	}
	player->Draw();
}
