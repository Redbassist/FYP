#include "Enemy.h"

Enemy::Enemy(Vector2f p) : m_pos(p)
{
	LoadAssets();
	createBox2dBody();
	numberRays = 11;
	CreateRays();
	speed = 2;
	orientation = GetRotationAngle();
	doorSearchTimer = time(&timer);
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
	SearchPlayer();
	UpdateRays();
	SampleAI();
	Movement();

	if (door) {
		doorSearchTimer = time(&timer);
	}

	else if (difftime(time(&timer), doorSearchTimer) > 5) {
		searchDoor = true;
	}
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
	float angleIncrement = 180 / (numberRays - 1);

	spottedRay.first.p1 = position;
	if (playerSpotted && spottedPlayer != NULL) {
		spottedRay.first.p2 = b2Vec2(spottedPlayer->GetPosition().x / SCALE, spottedPlayer->GetPosition().y / SCALE);
	}
	spottedRay.second = RayCastCallBack(RayCastManager::GetInstance()->CastRay(spottedRay.first.p1, spottedRay.first.p2));

	for (int i = 0; i < numberRays; i++) {
		rayAngle = angleIncrement * i;
		orientationPoint = b2Vec2((float)cos((orientation - 90) * DEGTORAD + rayAngle * DEGTORAD), (float)sin((orientation - 90) * DEGTORAD + rayAngle * DEGTORAD));
		visionRays[i].first.p1 = position + b2Vec2(orientationPoint.x * 0.1, orientationPoint.y * 0.1);
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
	b2Vec2 position = body->GetPosition();
	int centre = numberRays / 2;

	if (stop) {
		if (searchDirection == 0)
			orientation += 0.5;
		else
			orientation -= 0.5;

		for (int i = 0; i < numberRays; i++) {
			if (Distance(m_pos, Vector2f(visionRays[i].second.m_point.x * SCALE, visionRays[i].second.m_point.y * SCALE)) > 80) {
				movementTarget = Vector2f(visionRays[i].second.m_point.x * SCALE, visionRays[i].second.m_point.y * SCALE);
				orientation = GetRotationAngle();
				stop = false;
			}
		}
	}

	else if (Distance(m_pos, movementTarget) > 40 && !stop) {
		orientation = GetRotationAngle();

		Vector2f directionVector((float)cos(orientation * DEGTORAD), (float)sin(orientation * DEGTORAD));
		//directionVector = Normalize(directionVector);
		directionVector *= speed;

		position += b2Vec2(directionVector.x / SCALE, directionVector.y / SCALE);
	}
	/*if (visionRays[centre].second.objectName == NULL
		&& search && Distance(m_pos, Vector2f(visionRays[centre + 1].second.m_point.x * SCALE, visionRays[centre + 1].second.m_point.y * SCALE)) > 50
		&& search && Distance(m_pos, Vector2f(visionRays[centre - 1].second.m_point.x * SCALE, visionRays[centre - 1].second.m_point.y * SCALE)) > 50)
		movementTarget = Vector2f(visionRays[centre].first.p2.x * SCALE, visionRays[centre].first.p2.y * SCALE);*/

	else {
		int centre = numberRays / 2;
		movementTarget = Vector2f(visionRays[centre].first.p2.x * SCALE, visionRays[centre].first.p2.y * SCALE);
	}

	m_pos = Vector2f(position.x * SCALE, position.y * SCALE);
	body->SetTransform(position, orientation + DEGTORAD);
}

void Enemy::SampleAI()
{
	/*for (int i = 0; i < numberRays; i++) {
		if (visionRays[i].second.objectName == "Player") {
			movementTarget = Vector2f(visionRays[i].second.m_point.x * SCALE, visionRays[i].second.m_point.y * SCALE);
		}
	}*/

	int centre = numberRays / 2;

	if (chasing) {
		SpottedAI();
	}
	else if (door) {
		movementTarget = Vector2f(visionRays[centre].first.p2.x * SCALE, visionRays[centre].first.p2.y * SCALE);
		bool foundDoor = false;
		for (int i = 4; i < 7; i++) {
			if (visionRays[i].second.objectName == "Door") {
				foundDoor = true;
			}
		}
		if (!foundDoor)
			door = false;
	}
	else {
		if (visionRays[centre].second.objectName != NULL) {
			int direction = rand() % 2;
			SampleAIFunction(false, direction);
		}

		if (search && Distance(m_pos, Vector2f(visionRays[centre].second.m_point.x * SCALE, visionRays[centre].second.m_point.y * SCALE)) < 50) {
			int direction = rand() % 2;
			SampleAIFunction(true, direction);
		}
	}
	if (searchDoor && !chasing) {
		SearchDoor();
	}
}

void Enemy::SampleAIFunction(bool close, int direction)
{
	int centre = numberRays / 2;
	int above = 1;
	int below = 1;
	bool breakOut = false;
	if (direction == 0) {
		if (close) {
			int distance = 50;
			while ((below < centre && above < centre) && !breakOut) {
				if (Distance(m_pos, Vector2f(visionRays[centre + above].second.m_point.x * SCALE, visionRays[centre + above].second.m_point.y * SCALE)) > distance) {
					movementTarget = Vector2f(visionRays[centre + above].first.p2.x * SCALE, visionRays[centre + above].first.p2.y * SCALE);
					breakOut = true;
				}
				else if (Distance(m_pos, Vector2f(visionRays[centre - below].second.m_point.x * SCALE, visionRays[centre - below].second.m_point.y * SCALE)) > distance) {
					movementTarget = Vector2f(visionRays[centre - below].first.p2.x * SCALE, visionRays[centre - below].first.p2.y * SCALE);
					breakOut = true;
				}
				else {
					above++;
					below++;
				}
			}

			if (!breakOut && !stop) {
				searchDirection = rand() % 2;
				stop = true;
			}
		}
		else {
			while ((below < centre && above < centre) && !breakOut) {
				if (visionRays[centre + above].second.objectName == NULL) {
					movementTarget = Vector2f(visionRays[centre + above].first.p2.x * SCALE, visionRays[centre + above].first.p2.y * SCALE);
					breakOut = true;
					search = false;
				}
				else if (visionRays[centre - below].second.objectName == NULL) {
					movementTarget = Vector2f(visionRays[centre - below].first.p2.x * SCALE, visionRays[centre - below].first.p2.y * SCALE);
					breakOut = true;
					search = false;
				}
				else {
					above++;
					below++;
				}
			}
			if (!breakOut) {
				search = true;
			}
		}
	}
	else {
		if (close) {
			int distance = 50;
			while ((below < centre && above < centre) && !breakOut) {
				if (Distance(m_pos, Vector2f(visionRays[centre - below].second.m_point.x * SCALE, visionRays[centre - below].second.m_point.y * SCALE)) > distance) {
					movementTarget = Vector2f(visionRays[centre - below].first.p2.x * SCALE, visionRays[centre - below].first.p2.y * SCALE);
					breakOut = true;
				}
				else if (Distance(m_pos, Vector2f(visionRays[centre + above].second.m_point.x * SCALE, visionRays[centre + above].second.m_point.y * SCALE)) > distance) {
					movementTarget = Vector2f(visionRays[centre + above].first.p2.x * SCALE, visionRays[centre + above].first.p2.y * SCALE);
					breakOut = true;
				}
				else {
					above++;
					below++;
				}
			}

			if (!breakOut && !stop) {
				searchDirection = rand() % 2;
				stop = true;
			}
		}
		else {
			while ((below < centre && above < centre) && !breakOut) {
				if (visionRays[centre - below].second.objectName == NULL) {
					movementTarget = Vector2f(visionRays[centre - below].first.p2.x * SCALE, visionRays[centre - below].first.p2.y * SCALE);
					breakOut = true;
					search = false;
				}
				else if (visionRays[centre + above].second.objectName == NULL) {
					movementTarget = Vector2f(visionRays[centre + above].first.p2.x * SCALE, visionRays[centre + above].first.p2.y * SCALE);
					breakOut = true;
					search = false;
				}
				else {
					above++;
					below++;
				}
			}
			if (!breakOut)
				search = true;
		}
	}
}

void Enemy::SearchDoor()
{
	int centre = numberRays / 2;
	int above = 1;
	int below = 1;
	bool breakOut = false;

	if (visionRays[centre].second.objectName == "Door") {
		movementTarget = static_cast<Door*>(visionRays[centre].second.data)->GetOrigin();
		breakOut = true;
		searchDoor = false;
		door = true;
	}

	while ((below < centre && above < centre) && !breakOut) {
		if (visionRays[centre + above].second.objectName == "Door") {
			movementTarget = static_cast<Door*>(visionRays[centre + above].second.data)->GetOrigin();
			breakOut = true;
			searchDoor = false;
			door = true;
		}
		else if (visionRays[centre - below].second.objectName == "Door") {
			movementTarget = static_cast<Door*>(visionRays[centre - below].second.data)->GetOrigin();
			breakOut = true;
			searchDoor = false;
			door = true;
		}
		else {
			above++;
			below++;
		}
	}
}

void Enemy::SearchPlayer()
{
	int centre = numberRays / 2;
	int above = 1;
	int below = 1;
	bool breakOut = false;

	if (visionRays[centre].second.objectName == "Player") {
		//movementTarget = Vector2f(visionRays[centre].first.p2.x * SCALE, visionRays[centre].first.p2.y * SCALE);
		playerSpotted = true;
		spottedPlayer = static_cast<Player*>(visionRays[centre].second.data);
		breakOut = true;
	}

	while ((below < centre && above < centre) && !breakOut) {
		if (visionRays[centre + above].second.objectName == "Player") {
			//movementTarget = Vector2f(visionRays[centre + above].first.p2.x * SCALE, visionRays[centre + above].first.p2.y * SCALE); 
			playerSpotted = true;
			chasing = true;
			spottedPlayer = static_cast<Player*>(visionRays[centre + above].second.data);
			breakOut = true;
		}
		else if (visionRays[centre - below].second.objectName == "Player") {
			//movementTarget = Vector2f(visionRays[centre - below].first.p2.x * SCALE, visionRays[centre - below].first.p2.y * SCALE);
			playerSpotted = true;
			chasing = true;
			spottedPlayer = static_cast<Player*>(visionRays[centre - below].second.data);
			breakOut = true;
		}
		else {
			above++;
			below++;
		}
	}
}

void Enemy::SpottedAI()
{ 
	int distance = 40;

	if (spottedRay.second.objectName != "Player") {
		spottedPlayer = false;
		if (Distance(m_pos, Vector2f(spottedRay.first.p2.x * SCALE, spottedRay.first.p2.y * SCALE)) < distance) {
			chasing = false;
			searchDoor = true;
		}
		else {
			movementTarget = Vector2f(spottedRay.first.p2.x * SCALE, spottedRay.first.p2.y * SCALE);
		}
	}

	else if (spottedRay.second.objectName == "Player") {
		if (Distance(m_pos, Vector2f(spottedRay.second.m_point.x * SCALE, spottedRay.second.m_point.y * SCALE)) < distance) {
			cout << "Hitting Player" << endl;
		}
		else {
			movementTarget = Vector2f(spottedRay.second.m_point.x * SCALE, spottedRay.second.m_point.y * SCALE);
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
