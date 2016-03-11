#include "House.h"

House::~House()
{

}

House::House(Vector2f pos, std::vector<Item*>* i, int t) : m_pos(pos), items(i), type(t) {
	LoadAssets();
	CreateWalls();
}

void House::LoadAssets() {
	/*m_texture.loadFromFile("Sprites/houseFloor.png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	//m_sprite.setScale(Vector2f(0.45, 0.45));
	m_sprite.setPosition(Vector2f(m_pos.x - 90, m_pos.y));*/
}

void House::CreateWalls() {
	//house facing down
	if (type == 0) {
		walls.push_back(new Wall(m_pos + Vector2f(75, 0), Vector2f(325, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 0), Vector2f(15, 400)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 385), Vector2f(150, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(210, 385), Vector2f(190, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(385, 0), Vector2f(15, 400)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 150), Vector2f(150, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(210, 150), Vector2f(190, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(210, 230), Vector2f(190, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(135, 150), Vector2f(15, 155)));
		walls.push_back(new Wall(m_pos + Vector2f(210, 150), Vector2f(15, 20)));
		walls.push_back(new Wall(m_pos + Vector2f(135, 365), Vector2f(15, 34)));
		walls.push_back(new Wall(m_pos + Vector2f(210, 235), Vector2f(15, 90)));

		doors.push_back(new Door(m_pos + Vector2f(45, 7.5), 0, 0));
		doors.push_back(new Door(m_pos + Vector2f(142.5, 335), 90, 0));
		doors.push_back(new Door(m_pos + Vector2f(217.5, 355), 90, 0));
		doors.push_back(new Door(m_pos + Vector2f(217.5, 200), 90, 0));
		doors.push_back(new Door(m_pos + Vector2f(180, 392.5), 180, 0));

		containers.push_back(new Container(m_pos + Vector2f(26, 103), 270, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(26, 340), 270, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(374, 40), 90, items, 1));
		containers.push_back(new Container(m_pos + Vector2f(374, 84), 90, items, 1));
		containers.push_back(new Container(m_pos + Vector2f(310, 176), 0, items, 1));
		containers.push_back(new Container(m_pos + Vector2f(310, 256), 0, items, 0));

		fillers.push_back(new FillerObject(m_pos + Vector2f(120, 82), 0, "table"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(345, 135), 180, "counter"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(265, 135), 180, "counter"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(360, 200), 0, "toilet"));
	}

	//house facing up
	if (type == 1) {
		walls.push_back(new Wall(m_pos + Vector2f(0, 385), Vector2f(325, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(385, 0), Vector2f(15, 400)));
		walls.push_back(new Wall(m_pos + Vector2f(250, 0), Vector2f(150, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 0), Vector2f(190, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 0), Vector2f(15, 400)));
		walls.push_back(new Wall(m_pos + Vector2f(250, 250), Vector2f(150, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 245), Vector2f(190, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 170), Vector2f(190, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(250, 95), Vector2f(15, 155)));
		walls.push_back(new Wall(m_pos + Vector2f(250, 15), Vector2f(15, 20)));
		walls.push_back(new Wall(m_pos + Vector2f(175, 0), Vector2f(15, 35)));
		walls.push_back(new Wall(m_pos + Vector2f(175, 93), Vector2f(15, 90)));

		doors.push_back(new Door(m_pos + Vector2f(355, 392.5), 0, 0));
		doors.push_back(new Door(m_pos + Vector2f(257.5, 65), 90, 0));
		doors.push_back(new Door(m_pos + Vector2f(182.5, 215), 90, 0));
		doors.push_back(new Door(m_pos + Vector2f(182.5, 65), 90, 0));
		doors.push_back(new Door(m_pos + Vector2f(220, 7.5), 180, 0));

		containers.push_back(new Container(m_pos + Vector2f(374, 310), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(374, 110), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(61, 160), 180, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(26, 310), 270, items, 1));
		containers.push_back(new Container(m_pos + Vector2f(26, 353), 270, items, 1));
		containers.push_back(new Container(m_pos + Vector2f(110, 235), 180, items, 1));

		fillers.push_back(new FillerObject(m_pos + Vector2f(80, 82), 0, "table"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(280, 310), 0, "table"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(65, 275), 0, "counter"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(145, 275), 0, "counter"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(40, 215), 180, "toilet"));
	}

	//shop facing downwards
	if (type == 2) {
		walls.push_back(new Wall(m_pos + Vector2f(0, 0), Vector2f(400, 15)));
		doors.push_back(new Door(m_pos + Vector2f(450, 7.5), 0, 1));
		walls.push_back(new Wall(m_pos + Vector2f(500, 0), Vector2f(400, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(500, 0), Vector2f(15, 250)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 0), Vector2f(15, 700)));
		walls.push_back(new Wall(m_pos + Vector2f(885, 0), Vector2f(15, 700)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 685), Vector2f(150, 15)));
		doors.push_back(new Door(m_pos + Vector2f(200, 692.5), 0, 1));
		walls.push_back(new Wall(m_pos + Vector2f(250, 685), Vector2f(650, 15)));
		doors.push_back(new Door(m_pos + Vector2f(75, 257.5), 0, 0));
		walls.push_back(new Wall(m_pos + Vector2f(0, 250), Vector2f(45, 15)));
		doors.push_back(new Door(m_pos + Vector2f(697.5, 80), 270, 0));
		walls.push_back(new Wall(m_pos + Vector2f(105, 250), Vector2f(600, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(765, 250), Vector2f(135, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(765, 0), Vector2f(15, 50)));
		doors.push_back(new Door(m_pos + Vector2f(772.5, 80), 90, 0));
		walls.push_back(new Wall(m_pos + Vector2f(765, 110), Vector2f(15, 140)));

		walls.push_back(new Wall(m_pos + Vector2f(690, 0), Vector2f(15, 50)));
		//door
		walls.push_back(new Wall(m_pos + Vector2f(690, 110), Vector2f(15, 140)));

		containers.push_back(new Container(m_pos + Vector2f(120, 470), 90, items, 2)); 
		containers.push_back(new Container(m_pos + Vector2f(440, 470), 90, items, 2));
		containers.push_back(new Container(m_pos + Vector2f(520, 470), 90, items, 2));
		containers.push_back(new Container(m_pos + Vector2f(600, 470), 90, items, 2));
		containers.push_back(new Container(m_pos + Vector2f(680, 470), 90, items, 2));
		containers.push_back(new Container(m_pos + Vector2f(760, 470), 90, items, 2));
		containers.push_back(new Container(m_pos + Vector2f(840, 470), 90, items, 2));

		containers.push_back(new Container(m_pos + Vector2f(590, 25), 0, items, 0));
		
		fillers.push_back(new FillerObject(m_pos + Vector2f(300, 380), 0, "checkout"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(300, 460), 0, "checkout"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(300, 540), 0, "checkout"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(300, 620), 0, "checkout"));

		fillers.push_back(new FillerObject(m_pos + Vector2f(850, 40), 0, "toilet"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(850, 100), 0, "toilet"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(850, 160), 0, "toilet"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(850, 220), 0, "toilet"));

		fillers.push_back(new FillerObject(m_pos + Vector2f(600, 140), 90, "table"));
	}

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

	size = fillers.size();
	for (int i = 0; i < size; i++) {
		fillers[i]->Draw();
	}

	//drawing the containers
	size = containers.size();
	for (int i = 0; i < size; i++) {
		containers[i]->Draw();
	}
}
