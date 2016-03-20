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
	else if (type == 1) {
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
	else if (type == 2) {
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

		fillers.push_back(new FillerObject(m_pos + Vector2f(600, 140), 96, "table"));

		fillers.push_back(new FillerObject(m_pos + Vector2f(80, 40), 30, "palletTruck"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(120, 70), 110, "palletTruck"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(350, 200), 290, "palletTruck"));

		fillers.push_back(new FillerObject(m_pos + Vector2f(150, 200), 290, "box1"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(50, 210), 50, "box2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(270, 100), 41, "box3"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(220, 80), 81, "box1"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(270, 100), 41, "box2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(310, 140), 10, "box1"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(260, 140), 130, "box3"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(410, 200), 290, "box3"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(410, 160), 200, "box1"));
	}

	//cabin facing right
	else if (type == 3) {
		walls.push_back(new Wall(m_pos + Vector2f(150, 0), Vector2f(200, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(150, 0), Vector2f(15, 175)));
		walls.push_back(new Wall(m_pos + Vector2f(335, 0), Vector2f(15, 175)));
		walls.push_back(new Wall(m_pos + Vector2f(150, 235), Vector2f(200, 15)));
		doors.push_back(new Door(m_pos + Vector2f(342.5, 205), 90, 0));
		 
		walls.push_back(new Wall(m_pos + Vector2f(0, 100), Vector2f(150, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 100), Vector2f(15, 150)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 235), Vector2f(165, 15)));
		doors.push_back(new Door(m_pos + Vector2f(157.5, 205), 90, 0));

		containers.push_back(new Container(m_pos + Vector2f(65, 125), 0, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(325, 35), 90, items, 1));

		fillers.push_back(new FillerObject(m_pos + Vector2f(250, 130), 73, "table"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(205, 30), 0, "counter"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(65, 194 ), 17, "bed"));
	}

	//cabin facing right
	else if (type == 4) {
		walls.push_back(new Wall(m_pos + Vector2f(0, 0), Vector2f(200, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 0), Vector2f(15, 175)));
		walls.push_back(new Wall(m_pos + Vector2f(185, 0), Vector2f(15, 175)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 235), Vector2f(200, 15)));
		doors.push_back(new Door(m_pos + Vector2f(7.5, 205), 90, 0));


		walls.push_back(new Wall(m_pos + Vector2f(200, 100), Vector2f(150, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(335, 100), Vector2f(15, 150)));
		walls.push_back(new Wall(m_pos + Vector2f(185, 235), Vector2f(165, 15)));
		doors.push_back(new Door(m_pos + Vector2f(192.5, 205), 90, 0));

		containers.push_back(new Container(m_pos + Vector2f(260, 125), 0, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(25, 36), 270, items, 1)); 

		fillers.push_back(new FillerObject(m_pos + Vector2f(90, 130), 56, "table"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(130, 30), 0, "counter"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(280, 194), 193, "bed"));
	}

	//military base
	else if (type == 5) {
		walls.push_back(new Wall(m_pos + Vector2f(0, 0), Vector2f(2000, 15))); 
		walls.push_back(new Wall(m_pos + Vector2f(0, 0), Vector2f(15, 1600)));
		walls.push_back(new Wall(m_pos + Vector2f(0, 1585), Vector2f(150, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(220, 1585), Vector2f(2080, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(2285, 0), Vector2f(15, 1600)));

		//dorm1
		walls.push_back(new Wall(m_pos + Vector2f(100, 600), Vector2f(200, 15)));
		doors.push_back(new Door(m_pos + Vector2f(345, 607.5), 0, 0));
		walls.push_back(new Wall(m_pos + Vector2f(375, 600), Vector2f(55, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(415, 600), Vector2f(15, 800)));
		walls.push_back(new Wall(m_pos + Vector2f(100, 600), Vector2f(15, 800)));
		walls.push_back(new Wall(m_pos + Vector2f(100, 1385), Vector2f(330, 15)));

		walls.push_back(new Wall(m_pos + Vector2f(300, 600), Vector2f(15, 125)));
		doors.push_back(new Door(m_pos + Vector2f(307.5, 755), 90, 0));
		fillers.push_back(new FillerObject(m_pos + Vector2f(160, 640), 3, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(160, 700), 354, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(160, 760), 9, "bed2"));
		containers.push_back(new Container(m_pos + Vector2f(290, 660), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(240, 635), 5, items, 3));

		walls.push_back(new Wall(m_pos + Vector2f(300, 785), Vector2f(15, 140)));
		doors.push_back(new Door(m_pos + Vector2f(307.5, 955), 90, 0));
		fillers.push_back(new FillerObject(m_pos + Vector2f(160, 840), 353, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(160, 900), 4, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(160, 960), 0, "bed2"));
		containers.push_back(new Container(m_pos + Vector2f(290, 860), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(240, 825), 2, items, 3));

		walls.push_back(new Wall(m_pos + Vector2f(300, 985), Vector2f(15, 140)));
		doors.push_back(new Door(m_pos + Vector2f(307.5, 1155), 90, 0));
		fillers.push_back(new FillerObject(m_pos + Vector2f(160, 1040), 0, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(160, 1100), 352, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(160, 1160), 6, "bed2"));
		containers.push_back(new Container(m_pos + Vector2f(290, 1060), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(240, 1025), 5, items, 3));

		walls.push_back(new Wall(m_pos + Vector2f(300, 1185), Vector2f(15, 140)));
		doors.push_back(new Door(m_pos + Vector2f(307.5, 1355), 90, 0));
		fillers.push_back(new FillerObject(m_pos + Vector2f(160, 1240), 3, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(160, 1300), 357, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(160, 1360), 0, "bed2"));
		containers.push_back(new Container(m_pos + Vector2f(290, 1260), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(240, 1225), 357, items, 3));

		walls.push_back(new Wall(m_pos + Vector2f(100, 785), Vector2f(200, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(100, 985), Vector2f(200, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(100, 1185), Vector2f(200, 15)));

		//dorm2
		walls.push_back(new Wall(m_pos + Vector2f(600, 600), Vector2f(200, 15)));
		doors.push_back(new Door(m_pos + Vector2f(845, 607.5), 0, 0));
		walls.push_back(new Wall(m_pos + Vector2f(875, 600), Vector2f(55, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(915, 600), Vector2f(15, 800)));
		walls.push_back(new Wall(m_pos + Vector2f(600, 600), Vector2f(15, 800)));
		walls.push_back(new Wall(m_pos + Vector2f(600, 1385), Vector2f(330, 15)));

		walls.push_back(new Wall(m_pos + Vector2f(800, 600), Vector2f(15, 125)));
		doors.push_back(new Door(m_pos + Vector2f(807.5, 755), 90, 0));
		fillers.push_back(new FillerObject(m_pos + Vector2f(660, 640), 3, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(660, 700), 354, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(660, 760), 9, "bed2"));
		containers.push_back(new Container(m_pos + Vector2f(790, 660), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(740, 635), 5, items, 3));

		walls.push_back(new Wall(m_pos + Vector2f(800, 785), Vector2f(15, 140)));
		doors.push_back(new Door(m_pos + Vector2f(807.5, 955), 90, 0));
		fillers.push_back(new FillerObject(m_pos + Vector2f(660, 840), 353, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(660, 900), 4, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(660, 960), 0, "bed2"));
		containers.push_back(new Container(m_pos + Vector2f(790, 860), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(740, 825), 2, items, 3));

		walls.push_back(new Wall(m_pos + Vector2f(800, 985), Vector2f(15, 140)));
		doors.push_back(new Door(m_pos + Vector2f(807.5, 1155), 90, 0));
		fillers.push_back(new FillerObject(m_pos + Vector2f(660, 1040), 0, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(660, 1100), 352, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(660, 1160), 6, "bed2"));
		containers.push_back(new Container(m_pos + Vector2f(790, 1060), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(740, 1025), 5, items, 3));

		walls.push_back(new Wall(m_pos + Vector2f(800, 1185), Vector2f(15, 140)));
		doors.push_back(new Door(m_pos + Vector2f(807.5, 1355), 90, 0));
		fillers.push_back(new FillerObject(m_pos + Vector2f(660, 1240), 3, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(660, 1300), 357, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(660, 1360), 0, "bed2"));
		containers.push_back(new Container(m_pos + Vector2f(790, 1260), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(740, 1225), 357, items, 3));

		walls.push_back(new Wall(m_pos + Vector2f(600, 785), Vector2f(200, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(600, 985), Vector2f(200, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(600, 1185), Vector2f(200, 15)));

		//dorm3
		walls.push_back(new Wall(m_pos + Vector2f(1100, 600), Vector2f(200, 15)));
		doors.push_back(new Door(m_pos + Vector2f(1345, 607.5), 0, 0));
		walls.push_back(new Wall(m_pos + Vector2f(1375, 600), Vector2f(55, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(1415, 600), Vector2f(15, 800)));
		walls.push_back(new Wall(m_pos + Vector2f(1100, 600), Vector2f(15, 800)));
		walls.push_back(new Wall(m_pos + Vector2f(1100, 1385), Vector2f(330, 15)));

		walls.push_back(new Wall(m_pos + Vector2f(1300, 600), Vector2f(15, 125)));
		doors.push_back(new Door(m_pos + Vector2f(1307.5, 755), 90, 0));
		fillers.push_back(new FillerObject(m_pos + Vector2f(1160, 640), 3, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(1160, 700), 354, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(1160, 760), 9, "bed2"));
		containers.push_back(new Container(m_pos + Vector2f(1290, 660), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(1240, 635), 5, items, 3));

		walls.push_back(new Wall(m_pos + Vector2f(1300, 785), Vector2f(15, 140)));
		doors.push_back(new Door(m_pos + Vector2f(1307.5, 955), 90, 0));
		fillers.push_back(new FillerObject(m_pos + Vector2f(1160, 840), 353, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(1160, 900), 4, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(1160, 960), 0, "bed2"));
		containers.push_back(new Container(m_pos + Vector2f(1290, 860), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(1240, 825), 2, items, 3));

		walls.push_back(new Wall(m_pos + Vector2f(1300, 985), Vector2f(15, 140)));
		doors.push_back(new Door(m_pos + Vector2f(1307.5, 1155), 90, 0));
		fillers.push_back(new FillerObject(m_pos + Vector2f(1160, 1040), 0, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(1160, 1100), 352, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(1160, 1160), 6, "bed2"));
		containers.push_back(new Container(m_pos + Vector2f(1290, 1060), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(1240, 1025), 5, items, 3));

		walls.push_back(new Wall(m_pos + Vector2f(1300, 1185), Vector2f(15, 140)));
		doors.push_back(new Door(m_pos + Vector2f(1307.5, 1355), 90, 0));
		fillers.push_back(new FillerObject(m_pos + Vector2f(1160, 1240), 3, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(1160, 1300), 357, "bed2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(1160, 1360), 0, "bed2"));
		containers.push_back(new Container(m_pos + Vector2f(1290, 1260), 90, items, 0));
		containers.push_back(new Container(m_pos + Vector2f(1240, 1225), 357, items, 3));

		walls.push_back(new Wall(m_pos + Vector2f(1100, 785), Vector2f(200, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(1100, 985), Vector2f(200, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(1100, 1185), Vector2f(200, 15)));

		//outhouse
		walls.push_back(new Wall(m_pos + Vector2f(100, 100), Vector2f(700, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(100, 100), Vector2f(15, 200)));
		walls.push_back(new Wall(m_pos + Vector2f(100, 285), Vector2f(700, 15)));
		walls.push_back(new Wall(m_pos + Vector2f(785, 100), Vector2f(15, 125)));
		doors.push_back(new Door(m_pos + Vector2f(792.5, 255), 90, 0));
		//toilet cubicles
		fillers.push_back(new FillerObject(m_pos + Vector2f(145, 150), 270, "toilet"));
		walls.push_back(new Wall(m_pos + Vector2f(195, 100), Vector2f(15, 90)));
		fillers.push_back(new FillerObject(m_pos + Vector2f(235, 150), 270, "toilet"));
		walls.push_back(new Wall(m_pos + Vector2f(275, 100), Vector2f(15, 90))); 
		walls.push_back(new Wall(m_pos + Vector2f(355, 100), Vector2f(15, 90)));
		fillers.push_back(new FillerObject(m_pos + Vector2f(395, 150), 270, "toilet"));
		walls.push_back(new Wall(m_pos + Vector2f(435, 100), Vector2f(15, 90)));

		fillers.push_back(new FillerObject(m_pos + Vector2f(155, 270), 180, "counter2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(235, 270), 180, "counter2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(315, 270), 180, "counter2"));
		fillers.push_back(new FillerObject(m_pos + Vector2f(395, 270), 180, "counter2"));

		containers.push_back(new Container(m_pos + Vector2f(465, 275), 180, items, 1));
		containers.push_back(new Container(m_pos + Vector2f(505, 275), 180, items, 1));
		containers.push_back(new Container(m_pos + Vector2f(180, 160), 91, items, 3));
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
