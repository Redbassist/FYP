#include "Tree.h"

float Distance(Vector2f pos1, Vector2f pos2) {
	return sqrt(pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2));
}

Tree::~Tree()
{
}

Tree::Tree(Vector2f pos) : m_pos(pos)
{
	LoadAssets();
	createBox2dBody();
}

void Tree::LoadAssets()
{
	m_texture.loadFromFile("Sprites/tree.png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y)); 
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	m_sprite.setPosition(m_pos);
	rotation = rand() % 180;
	m_sprite.setRotation(rotation);

	m_trunktexture.loadFromFile("Sprites/wall.png");
	m_trunktexture.setSmooth(false);
	m_trunksprite.setTexture(m_trunktexture);
	m_trunksprite.setTextureRect(sf::IntRect(0, 0, m_trunktexture.getSize().x, m_trunktexture.getSize().y)); 
	m_trunksprite.setOrigin(m_trunktexture.getSize().x / 2, m_trunktexture.getSize().y / 2);
	m_trunksprite.setPosition(m_pos - Vector2f(20, 20));
	m_trunksprite.setScale(40, 40); 
}

void Tree::Draw()
{
	window->draw(m_trunksprite);
	window->draw(m_sprite);
}

void Tree::FadeOut(Vector2f pos)
{
	float distance = Distance(m_pos, pos);
	if (distance < maxDistance) {
		float alpha = 405 - ((maxDistance - distance) / maxDistance) * 255; 
		if (alpha > 255)
			alpha = 255;
		alpha = 0;
		m_sprite.setColor(sf::Color(255, 255, 255, alpha));
	}
	else {
		m_sprite.setColor(sf::Color(255, 255, 255, 0));
	}
}

void Tree::createBox2dBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set((m_pos.x) / SCALE, (m_pos.y) / SCALE);
	bodyDef.userData = this;
	bodyDef.gravityScale = 1;
	body = world->CreateBody(&bodyDef);
	b2PolygonShape staticBox;
	staticBox.SetAsBox((40 / 2.0f) / SCALE, (40 / 2.0f) / SCALE);
	fixtureDef.shape = &staticBox;

	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = "Filler";
	fixtureDef.restitution = b2MixRestitution(0, 0);

	fixtureDef.filter.categoryBits = FILLER;
	fixtureDef.filter.maskBits = PLAYER | MELEE | PUNCH;

	body->CreateFixture(&fixtureDef);
	body->SetTransform(body->GetPosition(), rotation * DEGTORAD);


	ltbl::LightShape* lightBlocker;

	m_pos.x -= 15;
	m_pos.y -= 15;

	lightBlocker = ltbl::LightSystem::GetInstance()->allocateShape();
	lightBlocker->_shape.setPointCount(4u);
	lightBlocker->_shape.setPoint(0u, { 0.f, 0.f });
	lightBlocker->_shape.setPoint(1u, { 0.f, 30 });
	lightBlocker->_shape.setPoint(2u, { 30, 30 });
	lightBlocker->_shape.setPoint(3u, { 30, 0.f });
	lightBlocker->_shape.setPosition(Vector2f(m_pos.x, m_pos.y));
	ltbl::LightSystem::GetInstance()->addShape(lightBlocker);
}
