#include "Wall.h"

//For the handling of collision filtering
enum _entityCategory {
	PLAYER = 0x0004,
	ITEM = 0x0008,
	CONTAINER = 0x0016,
	WALL = 0x0020,
	DOOR = 0x0024,
};

Wall::Wall(b2World* w, RenderWindow* rw, Vector2f pos, Vector2f s) : world(w), window(rw), m_pos(pos), size(s) {
	LoadAssets();
	createBox2dBody();
}

void Wall::LoadAssets() {
	m_texture.loadFromFile("Sprites/wall.png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	m_sprite.setScale(size.x, size.y);
	m_sprite.setPosition(m_pos);
}

void Wall::Draw() { 
	window->draw(m_sprite);
}

void Wall::createBox2dBody() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set((m_pos.x + m_sprite.getGlobalBounds().width / 2.0f) / SCALE, (m_pos.y + m_sprite.getGlobalBounds().height / 2) / SCALE);
	bodyDef.userData = this;
	bodyDef.gravityScale = 1;
	body = world->CreateBody(&bodyDef);
	b2PolygonShape staticBox;
	staticBox.SetAsBox((m_sprite.getGlobalBounds().width / 2.0f) / SCALE, (m_sprite.getGlobalBounds().height / 2.0f) / SCALE);
	fixtureDef.shape = &staticBox;

	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = "Wall";
	fixtureDef.restitution = b2MixRestitution(0, 0);

	fixtureDef.filter.categoryBits = WALL;
	fixtureDef.filter.maskBits = PLAYER;

	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(false);
}