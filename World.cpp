#include "World.h"

World::World(RenderWindow * rw, b2World * w, InputManager* im) : world(w), window(rw), inputManager(im) {
	CreateAssets();
	CreateLevel();
}

void World::CreateAssets() { 
}

void World::CreateLevel() {
	player = new Player(world, window, inputManager, Vector2f(20, 20));
	containers.push_back(new Container(world, window, inputManager, Vector2f(100, 100), 0, &items));  
} 

void World::Update() {
	player->Update();
}

void World::Draw() {
	//drawing the items
	int size = items.size();
	for (int i = 0; i < size; i++) {
		items[i]->Draw();
	}

	player->Draw();

	//drawing the containers
	size = containers.size();
	for (int i = 0; i < size; i++) {
		containers[i]->Draw();
	}
}
