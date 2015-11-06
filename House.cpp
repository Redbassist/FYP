#include "House.h"

House::House(b2World* w, RenderWindow* rw, Vector2f pos, std::vector<Item*>* i) : world(w), window(rw), m_pos(pos), items(i) {
	LoadAssets();
	CreateWalls(); 
} 

void House::LoadAssets() {
	m_texture.loadFromFile("Sprites/houseFloor.png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	//m_sprite.setScale(Vector2f(0.45, 0.45));
	m_sprite.setPosition(Vector2f(m_pos.x - 90, m_pos.y));
}

void House::CreateWalls() { 
	walls.push_back(new Wall(world, window, m_pos + Vector2f(0, 10), Vector2f(10 , 100)));
	walls.push_back(new Wall(world, window, m_pos + Vector2f(90, 10), Vector2f(10, 100)));
	walls.push_back(new Wall(world, window, m_pos + Vector2f(0, 10), Vector2f(20, 10)));
	walls.push_back(new Wall(world, window, m_pos + Vector2f(80, 10), Vector2f(20, 10)));
	walls.push_back(new Wall(world, window, m_pos + Vector2f(-90, 100), Vector2f(100, 10)));
	walls.push_back(new Wall(world, window, m_pos + Vector2f(-90, 100), Vector2f(10, 300)));
	walls.push_back(new Wall(world, window, m_pos + Vector2f(-90, 400), Vector2f(400, 10)));
	walls.push_back(new Wall(world, window, m_pos + Vector2f(90, 100), Vector2f(210, 10)));
	walls.push_back(new Wall(world, window, m_pos + Vector2f(300, 100), Vector2f(10, 300)));	
	walls.push_back(new Wall(world, window, m_pos + Vector2f(-90, 200), Vector2f(100, 10)));
	walls.push_back(new Wall(world, window, m_pos + Vector2f(70, 300), Vector2f(230, 10)));
	walls.push_back(new Wall(world, window, m_pos + Vector2f(-90, 200), Vector2f(100, 10)));
	walls.push_back(new Wall(world, window, m_pos + Vector2f(190, 100), Vector2f(10, 130)));
	walls.push_back(new Wall(world, window, m_pos + Vector2f(0, 270), Vector2f(10, 200)));

	doors.push_back(new Door(world, window, m_pos + Vector2f(50, 15), 0));
	doors.push_back(new Door(world, window, m_pos + Vector2f(6, 240), 90));
	doors.push_back(new Door(world, window, m_pos + Vector2f(195, 270), 90));
	doors.push_back(new Door(world, window, m_pos + Vector2f(40, 305), 0));

	containers.push_back(new Container(world, window, Vector2f(140, 120), 0, items));
	containers.push_back(new Container(world, window, Vector2f(200, 390), 180, items));
	containers.push_back(new Container(world, window, Vector2f(-70, 300), 270, items));
}

void House::Draw() {
	window->draw(m_sprite);

	int size = walls.size();
	for (int i = 0; i < size; i++) {
		walls[i]->Draw();
	}

	size = doors.size();
	for (int i = 0; i < size; i++) {
		doors[i]->Draw();
	}

	//drawing the containers
	size = containers.size();
	for (int i = 0; i < size; i++) {
		containers[i]->Draw();
	}
}
