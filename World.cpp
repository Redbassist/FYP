#include "World.h"

World::World(RenderWindow * rw, b2World * w, InputManager* im) : world(w), window(rw), inputManager(im) {
	CreateAssets();
	CreateLevel();
}

void World::CreateAssets() {
	m_texture.loadFromFile("Sprites/background.png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	m_sprite.setScale(Vector2f(0.4, 0.4));
	m_sprite.setPosition(0, 0);
}

void World::CreateLevel() {
	player = new Player(world, window, inputManager, Vector2f(0, 0));
	houses.push_back(new House(world, window, Vector2f(0, 0), &items));
} 

void World::Update() {
	player->Update();
}

void World::Draw() {
	window->draw(m_sprite);  
	
	int size = houses.size();
	for (int i = 0; i < size; i++) {
		houses[i]->Draw();
	}

	//drawing the items
	size = items.size();
	for (int i = 0; i < size; i++) {
		items[i]->Draw();
	}

	player->Draw();

}
