#include "Player.h"

Player::Player(b2World* b2world, RenderWindow* w, InputManager* im, Vector2f pos) : world(b2world), window(w), inputManager(im), m_pos(pos)
{
	LoadAssets();
	LoadBinds();
	createBox2dBody();

	speed = 0.045f;
}

void Player::LoadAssets() {
	m_legTexture.loadFromFile("Sprites/legs.png");
	m_legTexture.setSmooth(false);
	m_legSprite.setTexture(m_legTexture);
	m_legSprite.setTextureRect(sf::IntRect(0, 0, m_legTexture.getSize().x, m_legTexture.getSize().y));
	m_legSprite.setOrigin(m_legTexture.getSize().x / 2, m_legTexture.getSize().y / 2);
	m_legSprite.setPosition(m_pos);

	m_bodyTexture.loadFromFile("Sprites/player.png");
	m_bodyTexture.setSmooth(false);
	m_bodySprite.setTexture(m_bodyTexture);
	m_bodySprite.setTextureRect(sf::IntRect(0, 0, m_bodyTexture.getSize().x, m_bodyTexture.getSize().y));
	m_bodySprite.setOrigin(m_bodyTexture.getSize().x / 2, m_bodyTexture.getSize().y / 2);
	m_bodySprite.setPosition(m_pos);
}

void Player::LoadBinds() {
	//binding the keys for the player
	inputManager->Bind(&actions.walkUp, Keyboard::Key::W);
	inputManager->Bind(&actions.walkDown, Keyboard::Key::S);
	inputManager->Bind(&actions.walkLeft, Keyboard::Key::A);
	inputManager->Bind(&actions.walkRight, Keyboard::Key::D);
}

void Player::Draw() {
	window->draw(m_legSprite);
	window->draw(m_bodySprite);
}

void Player::Update() {
	Movement();
	SetRotation();
	m_legSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	m_bodySprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	m_pos = m_bodySprite.getPosition();
}

void Player::Movement() {
	b2Vec2 position = body->GetPosition();

	if (actions.walkUp) {
		position.y -= speed;
		m_legSprite.setRotation(90);
	}
	if (actions.walkDown) {
		position.y += speed;
		m_legSprite.setRotation(270);
	}
	if (actions.walkLeft) {
		position.x -= speed;
		m_legSprite.setRotation(0);
	}
	if (actions.walkRight) {
		position.x += speed;
		m_legSprite.setRotation(0);
	}
	body->SetTransform(position, 0);
}

void Player::SetRotation() {
	m_bodySprite.setRotation(getRotationAngle());
}

void Player::createBox2dBody() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_pos.x / SCALE, m_pos.y / SCALE);
	bodyDef.userData = this;
	bodyDef.gravityScale = 1;
	body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((m_bodySprite.getGlobalBounds().width / 2.0f) / SCALE, (m_bodySprite.getGlobalBounds().height / 2.0f) / SCALE);
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = "Player";
	fixtureDef.restitution = b2MixRestitution(0, 0);

	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(false);
}

b2Vec2 Player::Normalize(b2Vec2 vector) {
	float length = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	if (length != 0) {
		vector.x /= length;
		vector.y /= length;
	}

	return vector;
}

float Player::getRotationAngle() {
	Vector2f mousePos = (Vector2f)Mouse::getPosition(*window);
	float dx = mousePos.x - m_pos.x;
	float dy = mousePos.y - m_pos.y;
	float radian = atan2f(dy, dx);
	return (radian * 180 / 3.14159265359);
}
