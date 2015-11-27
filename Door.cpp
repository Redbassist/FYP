#include "Door.h"

//For the handling of collision filtering
enum _entityCategory {
	PLAYER = 0x0004,
	ITEM = 0x0008,
	CONTAINER = 0x0016,
	WALL = 0x0020,
	DOOR = 0x0024,
};

Door::Door(RenderWindow* rw, Vector2f pos, float r) : window(rw), m_pos(pos), rotation(r)  { 
	int random = rand() % 2;
	if (random == 1)
		open = true;
	else
		open = false;

	LoadAssets();
	createBox2dBody();
}

void Door::LoadAssets() {
	m_texture.loadFromFile("Sprites/door.png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	//m_sprite.setScale(size.x, size.y); 
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	m_sprite.setPosition(m_pos);
	m_sprite.setRotation(rotation);
}

void Door::Draw() {
	if (open) {
		m_sprite.setColor(Color(255, 255, 255, 50));
		window->draw(m_sprite);
	}
	else {
		m_sprite.setColor(Color(255, 255, 255, 255));
		window->draw(m_sprite);
	}
}

void Door::OpenClose() {
	m_sprite.setPosition(Vector2f(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE));
	if (open) {
		open = false;
		body->GetFixtureList()->SetSensor(false);
	}
	else {
		open = true;
		body->GetFixtureList()->SetSensor(true);
	}
}

void Door::createBox2dBody() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set((m_pos.x) / SCALE, (m_pos.y) / SCALE);
	bodyDef.userData = this;
	bodyDef.gravityScale = 1;
	body = world->CreateBody(&bodyDef);
	b2PolygonShape staticBox;
	staticBox.SetAsBox((m_sprite.getGlobalBounds().width / 2.0f) / SCALE, (m_sprite.getGlobalBounds().height / 2.0f) / SCALE);
	fixtureDef.shape = &staticBox;

	if (open)
		fixtureDef.isSensor = true;
	else
		fixtureDef.isSensor = false;

	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = "Door";
	fixtureDef.restitution = b2MixRestitution(0, 0);

	fixtureDef.filter.categoryBits = DOOR;
	fixtureDef.filter.maskBits = PLAYER;

	body->CreateFixture(&fixtureDef); 
}
