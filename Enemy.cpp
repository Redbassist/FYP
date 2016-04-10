#include "Enemy.h"

Enemy::Enemy(Vector2f p) : m_pos(p)
{
	health = 100;
}

Enemy::~Enemy()
{
}

void Enemy::LoadAssets()
{
	phTexture.loadFromFile("Sprites/phEnemy.png");
	phTexture.setSmooth(false);
	phSprite.setTexture(phTexture);
	phSprite.setTextureRect(sf::IntRect(0, 0, phTexture.getSize().x, phTexture.getSize().y));
	phSprite.setOrigin(phTexture.getSize().x / 2, phTexture.getSize().y / 2);
}

void Enemy::createBox2dBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_pos.x / SCALE, m_pos.y / SCALE);
	bodyDef.userData = this;
	bodyDef.gravityScale = 1;
	body = world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 7 / SCALE;
	fixtureDef.shape = &circle;

	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = "Enemy";
	fixtureDef.restitution = b2MixRestitution(0, 0);

	fixtureDef.filter.categoryBits = ENEMY;
	fixtureDef.filter.maskBits = PLAYER | ITEM | CONTAINER | WALL | DOOR | FILLER;

	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(false);
}

void Enemy::Update()
{

}

void Enemy::Draw()
{
	phSprite.setPosition(m_pos);
	phSprite.setRotation(orientation);
	window->draw(phSprite);
}

void Enemy::Movement()
{
	b2Vec2 position = body->GetPosition();
	orientation = GetRotationAngle();
	m_pos = Vector2f(position.x * SCALE, position.y * SCALE);
	body->SetTransform(position, orientation + DEGTORAD);
}

void Enemy::DropHealth(int amount)
{
	health -= amount;
	if (health < 0) {
		alive = false;
		health = 0;
	}
	if (alive) {
		int randomNoise = rand() % 2;
		if (randomNoise == 0) {
			AudioManager::GetInstance()->playSound("alienHit1", m_pos);
		}
		else {
			AudioManager::GetInstance()->playSound("alienHit2", m_pos);
		}
	}
}
  
float Enemy::GetRotationAngle() {
	float dx = movementTarget.x - m_pos.x;
	float dy = movementTarget.y - m_pos.y;
	float radian = atan2f(dy, dx);
	return (radian * RADTODEG);
}

Vector2f Enemy::Normalize(Vector2f vector)
{
	float length = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	if (length != 0) {
		vector.x /= length;
		vector.y /= length;
	}
	return vector;
}

float Enemy::Distance(Vector2f v1, Vector2f v2)
{
	return sqrt(pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2));
}
