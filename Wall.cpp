#include "Wall.h" 

Wall::Wall(Vector2f pos, Vector2f s) : m_pos(pos), size(s) {
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
	fixtureDef.filter.maskBits = PLAYER | ENEMY;

	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(false);

	FloatRect size = m_sprite.getGlobalBounds(); 
	m_pos.x += 1;
	size.width -= 2;
	m_pos.y+= 1;
	size.height -= 2; 

	lightBlocker = ltbl::LightSystem::GetInstance()->allocateShape();
	lightBlocker->_shape.setPointCount(4u);
	lightBlocker->_shape.setPoint(0u, { 0.f, 0.f });
	lightBlocker->_shape.setPoint(1u, { 0.f, size.height });
	lightBlocker->_shape.setPoint(2u, { size.width, size.height });
	lightBlocker->_shape.setPoint(3u, { size.width, 0.f });
	lightBlocker->_shape.setPosition(Vector2f(m_pos.x, m_pos.y));  
	ltbl::LightSystem::GetInstance()->addShape(lightBlocker);
}
