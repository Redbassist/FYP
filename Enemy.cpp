#include "Enemy.h"

Enemy::Enemy(Vector2f p) : m_pos(p)
{ 
	LoadAssets();
	createBox2dBody();
	numberRays = 11;
	CreateRays();
	speed = 2;
	orientation = GetRotationAngle(); 
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
	UpdateRays();
	SampleAI();
	Movement(); 
}

void Enemy::CreateRays()
{
	for (int i = 0; i < numberRays; i++) { 
		std::pair<b2RayCastInput, RayCastCallBack*> temp;
		visionRays.push_back(temp);
	}
}

void Enemy::UpdateRays()
{
	b2Vec2 position = body->GetPosition();
	b2Vec2 orientationPoint;
	float rayAngle = 0;
	float angleIncrement = 18;

	for(int i = 0; i < numberRays; i++) {
		rayAngle = angleIncrement * i;
		orientationPoint = b2Vec2((float)cos((orientation - 90) * DEGTORAD + rayAngle * DEGTORAD), (float)sin((orientation - 90) * DEGTORAD + rayAngle * DEGTORAD));
		visionRays[i].first.p1 = position + b2Vec2(orientationPoint.x * 0.4, orientationPoint.y * 0.5);
		visionRays[i].first.p2 = position + b2Vec2(orientationPoint.x * 14.5, orientationPoint.y * 14.5);
		visionRays[i].first.maxFraction = 1;
		visionRays[i].second = RayCastCallBack(RayCastManager::GetInstance()->CastRay(visionRays[i].first.p1, visionRays[i].first.p2));
	}
}

void Enemy::Draw()
{
	phSprite.setPosition(m_pos);
	phSprite.setRotation(orientation);
	window->draw(phSprite);
	for (int i = 0; i < numberRays; i++) {
		sf::VertexArray line(sf::LinesStrip, 2);

		// define the position of the triangle's points
		line[0].position = sf::Vector2f(visionRays[i].first.p1.x * SCALE, visionRays[i].first.p1.y * SCALE);
		if (visionRays[i].second.objectName != NULL)
			line[0].color = sf::Color::Green;
		else 
			line[0].color = sf::Color::Red;
		line[1].position = sf::Vector2f(visionRays[i].first.p2.x * SCALE, visionRays[i].first.p2.y * SCALE);
		if (visionRays[i].second.objectName != NULL)
			line[1].color = sf::Color::Green;
		else
			line[1].color = sf::Color::Red;

		window->draw(line);
	}
}

void Enemy::Movement()
{
	orientation = GetRotationAngle();

	b2Vec2 position = body->GetPosition();

	if (Distance(m_pos, movementTarget) > 40) {
		Vector2f directionVector((float)cos(orientation * DEGTORAD), (float)sin(orientation * DEGTORAD));
		//directionVector = Normalize(directionVector);
		directionVector *= speed;

		position += b2Vec2(directionVector.x / SCALE, directionVector.y / SCALE);
	}
	m_pos = Vector2f(position.x * SCALE, position.y * SCALE);
	body->SetTransform(position, orientation + DEGTORAD);
}

void Enemy::SampleAI()
{
	for (int i = 0; i < numberRays; i++) {
		if (visionRays[i].second.objectName == "Player") {
			movementTarget = Vector2f(visionRays[i].second.m_point.x * SCALE, visionRays[i].second.m_point.y * SCALE);
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
