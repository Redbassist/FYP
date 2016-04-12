#include "Door.h" 

Door::Door(Vector2f pos, float r, int t) : m_pos(pos), rotation(r), type(t){
	int random = rand() % 2;
	if (random == 1)
		open = true;
	else
		open = false;

	LoadAssets();
	createBox2dBody();
}

void Door::LoadAssets() {
	if (type == 0)
		m_texture.loadFromFile("Sprites/door.png");
	else if (type == 1)
		m_texture.loadFromFile("Sprites/door2.png");

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
		ltbl::LightSystem::GetInstance()->addShape(lightBlocker);
		body->GetFixtureList()->SetSensor(false);
		AudioManager::GetInstance()->playSound("closeDoor", m_sprite.getPosition());
	}
	else {
		open = true;
		ltbl::LightSystem::GetInstance()->removeShape(lightBlocker);
		body->GetFixtureList()->SetSensor(true);
	}
}

void Door::Open()
{
	m_sprite.setPosition(Vector2f(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE));
	if (!open) {
		open = true;
		ltbl::LightSystem::GetInstance()->removeShape(lightBlocker);
		body->GetFixtureList()->SetSensor(true);
	}
}

void Door::Knock()
{
	AudioManager::GetInstance()->playSound("knock", m_sprite.getPosition());
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

	//creating lightblocker	
	FloatRect size = m_sprite.getGlobalBounds();
	m_pos.x -= size.width / 2;
	m_pos.y -= size.height / 2;

	if (size.width > size.height) { 
		size.height /= 2;
		m_pos.y += size.height / 2;
		m_pos.x -= 8;
		size.width += 16;
	}
	else {
		size.width /= 2;
		m_pos.x += size.width / 2;
		m_pos.y -= 8;
		size.height += 16;
	}

	lightBlocker = ltbl::LightSystem::GetInstance()->allocateShape();
	lightBlocker->_shape.setPointCount(4u);
	lightBlocker->_shape.setPoint(0u, { 0.f, 0.f });
	lightBlocker->_shape.setPoint(1u, { 0.f, size.height });
	lightBlocker->_shape.setPoint(2u, { size.width, size.height });
	lightBlocker->_shape.setPoint(3u, { size.width, 0.f });
	lightBlocker->_shape.setPosition(Vector2f(m_pos.x, m_pos.y));

	if (open)
		fixtureDef.isSensor = true;
	else {
		fixtureDef.isSensor = false;
		ltbl::LightSystem::GetInstance()->addShape(lightBlocker);
	}

	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = "Door";
	fixtureDef.restitution = b2MixRestitution(0, 0);

	fixtureDef.filter.categoryBits = DOOR;
	fixtureDef.filter.maskBits = PLAYER | MELEE | PUNCH | ENEMY;

	body->CreateFixture(&fixtureDef);
}

Vector2f Door::GetOrigin()
{
	return m_sprite.getPosition();
}
