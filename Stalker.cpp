#include "Stalker.h"

Stalker::Stalker(Vector2f pos) : Enemy(pos)
{
	LoadAssets();
	createBox2dBody();
	createPunchBox2dBody();
	createHitBox2dBody();
	numberRays = 11;
	CreateRays();
	speed = 2;
	searchOrientation = 0;
	avoidDistance = 15;
	orientation = 50;
	movementTarget = m_pos + Vector2f((float)cos(orientation * DEGTORAD), (float)sin(orientation * DEGTORAD));
	//orientation = GetRotationAngle();
	doorSearchTimer = time(&timer);
	playerChaseTimer = time(&timer);
	punchTimer = time(&timer);
	maxPunchDistance = 80;
	spottedPlayer = NULL;
	nearDoor = false;
	collapse = false;
	chatterTimer = time(&timer);
	chatterDelay = 0;
}

Stalker::Stalker(Vector2f pos, Player* p) : Enemy(pos)
{
	LoadAssets();
	createBox2dBody();
	createPunchBox2dBody();
	createHitBox2dBody();
	numberRays = 11;
	CreateRays();
	speed = 2;
	searchOrientation = 0;
	avoidDistance = 15;
	orientation = atan2(p->GetPosition().y - m_pos.y, p->GetPosition().x - m_pos.x) * RADTODEG;
	movementTarget = m_pos + Vector2f((float)cos(orientation * DEGTORAD), (float)sin(orientation * DEGTORAD));
	//orientation = GetRotationAngle();
	doorSearchTimer = time(&timer);
	playerChaseTimer = time(&timer);
	punchTimer = time(&timer);
	maxPunchDistance = 80;
	spottedPlayer = NULL;
	nearDoor = false;
	collapse = false;
}

Stalker::~Stalker()
{
}

void Stalker::LoadAssets()
{
	EasyLoadAssetsAnimation(&m_AnimationLegsTexture, "stalkerLegs", &legsIdle, 1, 1, 1, 36, 35, currentLegAnimation);
	EasyLoadAssetsAnimation(&m_AnimationLegsTexture, "stalkerLegs", &legsMoving, 12, 12, 1, 36, 35);

	animatedLegSprite = AnimatedSprite(sf::seconds(0.08), true, false);
	animatedLegSprite.setOrigin(9, 17);
	animatedLegSprite.setPosition(m_pos);
	animatedLegSprite.setScale(1.6, 1.0);

	EasyLoadAssetsAnimation(&m_AnimationWalkTexture, "stalkerWalk", &topIdle, 1, 1, 1, 36, 35, currentTopAnimation);
	EasyLoadAssetsAnimation(&m_AnimationWalkTexture, "stalkerWalk", &topMoving, 12, 4, 3, 36, 35);

	animatedTopSprite = AnimatedSprite(sf::seconds(0.08), true, false);
	animatedTopSprite.setOrigin(9, 17);
	animatedTopSprite.setPosition(m_pos);
	animatedTopSprite.setScale(1.8, 1.3);

	EasyLoadAssetsAnimation(&m_PunchRightTexture, "stalkerRightPunch", &punchRight, 5, 5, 1, 36, 35);
	EasyLoadAssetsAnimation(&m_PunchLeftTexture, "stalkerLeftPunch", &punchLeft, 5, 5, 1, 36, 35);

	animatedPunchRight = AnimatedSprite(sf::seconds(0.03), true, false);
	animatedPunchRight.setOrigin(9, 17);
	animatedPunchRight.setPosition(m_pos);
	animatedPunchRight.setScale(1.8, 1.3);
	animatedPunchRight.play(punchRight);

	animatedPunchLeft = AnimatedSprite(sf::seconds(0.03), true, false);
	animatedPunchLeft.setOrigin(9, 17);
	animatedPunchLeft.setPosition(m_pos);
	animatedPunchLeft.setScale(1.8, 1.3);
	animatedPunchLeft.play(punchLeft);

	animatedPunchLeft = AnimatedSprite(sf::seconds(0.03), true, false);
	animatedPunchLeft.setOrigin(9, 17);
	animatedPunchLeft.setPosition(m_pos);
	animatedPunchLeft.setScale(1.8, 1.3);
	animatedPunchLeft.play(punchLeft);

	EasyLoadAssetsAnimation(&m_deathTexture, "stalkerDeath", &death, 3, 3, 1, 45, 35);

	animatedDeath = AnimatedSprite(sf::seconds(0.5), true, true);
	animatedDeath.setOrigin(9, 17);
	animatedDeath.setPosition(m_pos);
	animatedDeath.setScale(1.8, 1.3);
	animatedDeath.play(death);

	headTexture.loadFromFile("Sprites/stalkerHead.png");
	headTexture.setSmooth(false);
	headSprite.setTexture(headTexture);
	headSprite.setTextureRect(sf::IntRect(0, 0, headTexture.getSize().x, headTexture.getSize().y));
	headSprite.setOrigin(13, 17);
	headSprite.setScale(1.8, 1.3);
}

void Stalker::EasyLoadAssetsAnimation(Texture* t, string file, Animation* anim, int frames, int columns, int rows, int individualWidth, int individualHeight, Animation * current)
{
	t->loadFromFile("Sprites/" + file + ".png");
	t->setSmooth(false);
	anim->setSpriteSheet(*t);
	anim->addFrames(frames, columns, rows, individualWidth, individualHeight);
	current = anim;
}

void Stalker::EasyLoadAssetsAnimation(Texture*t, string file, Animation* anim, int frames, int columns, int rows, int individualWidth, int individualHeight)
{
	t->loadFromFile("Sprites/" + file + ".png");
	t->setSmooth(false);
	anim->setSpriteSheet(*t);
	anim->addFrames(frames, columns, rows, individualWidth, individualHeight);
}

void Stalker::createBox2dBody()
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

void Stalker::createHitBox2dBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_pos.x / SCALE, m_pos.y / SCALE);
	bodyDef.userData = this;
	bodyDef.gravityScale = 1;
	hitBody = world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 15 / SCALE;
	hitfixtureDef.shape = &circle;

	hitfixtureDef.isSensor = true;
	hitfixtureDef.density = 1;
	hitfixtureDef.friction = 0.3f;
	hitfixtureDef.userData = "EnemyHit";
	hitfixtureDef.restitution = b2MixRestitution(0, 0);

	hitfixtureDef.filter.categoryBits = ENEMYHIT;
	hitfixtureDef.filter.maskBits = DOOR | PUNCH | MELEE;

	hitBody->CreateFixture(&hitfixtureDef);
	hitBody->SetFixedRotation(false);
}

void Stalker::createPunchBox2dBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(m_pos.x / SCALE, m_pos.y / SCALE);
	bodyDef.userData = this;
	bodyDef.gravityScale = 1;
	punchbody = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(7.5 / SCALE, 7.5 / SCALE, b2Vec2(0 / SCALE, 0), 0);
	punchfixtureDef.shape = &dynamicBox;

	punchfixtureDef.isSensor = true;
	punchfixtureDef.density = 1;
	punchfixtureDef.friction = 0.3f;
	punchfixtureDef.userData = "EnemyPunch";
	punchfixtureDef.restitution = b2MixRestitution(0, 0);

	punchfixtureDef.filter.categoryBits = ENEMYPUNCH;
	punchfixtureDef.filter.maskBits = PLAYER;

	punchbody->CreateFixture(&punchfixtureDef);
	punchbody->SetFixedRotation(false);
}

void Stalker::CreateRays()
{
	for (int i = 0; i < numberRays; i++) {
		std::pair<b2RayCastInput, RayCastCallBack*> temp;
		visionRays.push_back(temp);
	}
}

void Stalker::Update()
{
	if (alive) {
		SearchPlayer();
		UpdateRays();
		AI();
		Movement();
		RotateOrientation();

		if (door) {
			doorSearchTimer = time(&timer);
		}

		else if (difftime(time(&timer), doorSearchTimer) > 5) {
			searchDoor = true;
		}

		//playing chatter noise of alien
		if (difftime(time(&timer), chatterTimer) > chatterDelay) {
			int sound = rand() % 4;
			if (sound == 0)
				AudioManager::GetInstance()->playSound("stalkerChatter1", m_pos);
			else if (sound == 1)
				AudioManager::GetInstance()->playSound("stalkerChatter2", m_pos);
			else if (sound == 2)
				AudioManager::GetInstance()->playSound("stalkerChatter3", m_pos);

			chatterDelay = sound + 1;
			chatterTimer = time(&timer);
		}

		//turn into method
		headSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
		headSprite.setRotation(orientation + searchOrientation);
		animatedLegSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
		animatedLegSprite.setRotation(orientation);
		animatedTopSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
		animatedTopSprite.setRotation(orientation);
		animatedPunchLeft.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
		animatedPunchLeft.setRotation(orientation);
		animatedPunchRight.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
		animatedPunchRight.setRotation(orientation);
		animatedDeath.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
		animatedDeath.setRotation(orientation);
	}
}

void Stalker::UpdateRays()
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
		orientationPoint = b2Vec2((float)cos((orientation + searchOrientation - 90) * DEGTORAD + rayAngle * DEGTORAD), (float)sin((orientation + searchOrientation - 90) * DEGTORAD + rayAngle * DEGTORAD));
		visionRays[i].first.p1 = position + b2Vec2(orientationPoint.x * 0.1, orientationPoint.y * 0.1);
		visionRays[i].first.p2 = position + b2Vec2(orientationPoint.x * 14.5, orientationPoint.y * 14.5);
		visionRays[i].first.maxFraction = 1;
		visionRays[i].second = RayCastCallBack(RayCastManager::GetInstance()->CastRay(visionRays[i].first.p1, visionRays[i].first.p2));
	}
}

void Stalker::Draw()
{
	sf::Time frameTime = frameClock.restart();

	if (alive) {
		if (moving) {
			if (punch) {
				currentTopAnimation = (punchDirection == 0) ? &punchRight : &punchLeft;
			}
			else {
				currentTopAnimation = &topMoving;
			}
			currentLegAnimation = &legsMoving;
		}
		else {
			if (punch) {
				currentTopAnimation = (punchDirection == 0) ? &punchRight : &punchLeft;
			}
			else {
				currentTopAnimation = &topIdle;
			}
			currentLegAnimation = &legsIdle;
		}

		animatedLegSprite.play(*currentLegAnimation);
		animatedLegSprite.update(frameTime);
		window->draw(animatedLegSprite);

		if (punch) {
			if (punchDirection == 0) {
				window->draw(animatedPunchRight);
				animatedPunchRight.update(frameTime);
			}
			else {
				window->draw(animatedPunchLeft);
				animatedPunchLeft.update(frameTime);
			}
		}
		else {
			animatedTopSprite.play(*currentTopAnimation);
			animatedTopSprite.update(frameTime);
			window->draw(animatedTopSprite);
		}

		window->draw(headSprite);
	}
	else {
		if (!collapse) { 
			collapse = true; 
			body->GetFixtureList()->SetUserData("Destroy");
			punchbody->GetFixtureList()->SetUserData("Destroy");
			hitBody->GetFixtureList()->SetUserData("Destroy");
		}
		else {
			animatedDeath.update(frameTime);
		}
		window->draw(animatedDeath);
	}
	/*
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
	}*/
}

void Stalker::Movement()
{
	moving = false;
	b2Vec2 position = body->GetPosition();
	int centre = numberRays / 2;

	if (stop) {
		LookAround();

		for (int i = 0; i < numberRays; i++) {
			if (i == 0) {
				if (Distance(m_pos, Vector2f(visionRays[i].second.m_point.x * SCALE, visionRays[i].second.m_point.y * SCALE)) > 80
					&& Distance(m_pos, Vector2f(visionRays[i + 1].second.m_point.x * SCALE, visionRays[i + 1].second.m_point.y * SCALE)) > 60
					&& Distance(m_pos, Vector2f(visionRays[i + 2].second.m_point.x * SCALE, visionRays[i + 2].second.m_point.y * SCALE)) > 60) {
					movementTarget = Vector2f(visionRays[i].second.m_point.x * SCALE, visionRays[i].second.m_point.y * SCALE);
					desiredOrientation = GetRotationAngle();
					stop = false;
					lookAround = false;
					lookRight = false;
					searchOrientation = 0;
				}
			}
			else if (i == numberRays - 1) {
				if (Distance(m_pos, Vector2f(visionRays[i].second.m_point.x * SCALE, visionRays[i].second.m_point.y * SCALE)) > 80
					&& Distance(m_pos, Vector2f(visionRays[i - 1].second.m_point.x * SCALE, visionRays[i - 1].second.m_point.y * SCALE)) > 60
					&& Distance(m_pos, Vector2f(visionRays[i - 2].second.m_point.x * SCALE, visionRays[i - 2].second.m_point.y * SCALE)) > 60) {
					movementTarget = Vector2f(visionRays[i].second.m_point.x * SCALE, visionRays[i].second.m_point.y * SCALE);
					desiredOrientation = GetRotationAngle();
					stop = false;
					lookAround = false;
					lookRight = false;
					searchOrientation = 0;
				}
			}
			else {
				if (Distance(m_pos, Vector2f(visionRays[i].second.m_point.x * SCALE, visionRays[i].second.m_point.y * SCALE)) > 80
					&& (Distance(m_pos, Vector2f(visionRays[i - 1].second.m_point.x * SCALE, visionRays[i - 1].second.m_point.y * SCALE)) > 50
						|| Distance(m_pos, Vector2f(visionRays[i + 1].second.m_point.x * SCALE, visionRays[i + 1].second.m_point.y * SCALE)) > 50)) {
					movementTarget = Vector2f(visionRays[i].second.m_point.x * SCALE, visionRays[i].second.m_point.y * SCALE);
					desiredOrientation = GetRotationAngle();
					stop = false;
					lookAround = false;
					lookRight = false;
					searchOrientation = 0;
				}
			}
		}
	}
	else if (avoid) {
		Vector2f directionVector((float)cos(orientation * DEGTORAD), (float)sin(orientation * DEGTORAD));
		//directionVector = Normalize(directionVector);
		directionVector *= speed;

		moving = true;
		position += b2Vec2(directionVector.x / SCALE, directionVector.y / SCALE);
	}

	else if (lookAround) {
		LookAround();
	}

	else if (Distance(m_pos, movementTarget) > 40 || door || chasing) {

		if (!nearDoor && !punch)
			desiredOrientation = GetRotationAngle();

		Vector2f directionVector((float)cos(orientation * DEGTORAD), (float)sin(orientation * DEGTORAD));
		//directionVector = Normalize(directionVector);
		directionVector *= speed;

		if (speed > 0)
			moving = true;
		position += b2Vec2(directionVector.x / SCALE, directionVector.y / SCALE);
	}

	else if (!door) {
		int centre = numberRays / 2;
		movementTarget = Vector2f(visionRays[centre].first.p2.x * SCALE, visionRays[centre].first.p2.y * SCALE);
	}

	b2Vec2 orientationPoint = b2Vec2((float)cos(orientation * DEGTORAD), (float)sin(orientation * DEGTORAD));
	b2Vec2 punchTemp = orientationPoint;
	punchTemp.x /= 100;
	punchTemp.y /= 100;
	punchTemp.x *= punchDistance;
	punchTemp.y *= punchDistance;

	body->SetTransform(position, orientation * DEGTORAD);
	punchbody->SetTransform(body->GetPosition() + punchTemp, orientation * DEGTORAD);
	hitBody->SetTransform(body->GetPosition(), orientation * DEGTORAD);

	m_pos = Vector2f(position.x * SCALE, position.y * SCALE);
}

void Stalker::RotateOrientation()
{
	float facingMinusTarget = orientation - desiredOrientation;
	float angleDiff = facingMinusTarget;
	
	if (abs(facingMinusTarget) > 180)
	{
		if (orientation > desiredOrientation)
		{
			angleDiff = -1 * ((360 - orientation) + desiredOrientation);
		}
		else
		{
			angleDiff = (360 - orientation) + desiredOrientation;
		}
	}

	if (angleDiff < 0)
	{
		if (angleDiff < -10)
			orientation += 10;
		else if (angleDiff < -5)
			orientation += 5;
		else if (angleDiff < -2)
			orientation += 2;
		else if (angleDiff < -1)
			orientation += 1;
		else
			orientation += 0.5;

	}
	else if (angleDiff > 0)
	{
		if (angleDiff > 10)
			orientation -= 10;
		else if (angleDiff > 5)
			orientation -= 5;
		else if (angleDiff > 2)
			orientation -= 2;
		else if (angleDiff > 1)
			orientation -= 1;
		else
			orientation -= 0.5;
	}

	if (orientation < 0) 
		orientation = 360 + orientation;
	
	else if (orientation > 360)
		orientation = 0 + orientation;

}

void Stalker::AI()
{
	int centre = numberRays / 2;

	if (chasing) {
		SpottedAI();
	}

	else if (lookAround) {
		if (searchDoor && !chasing) {
			if (searchPlayer)
				SearchDoor(true);
			else
				SearchDoor(false);
		}
	}

	else if (door) {
		int d = Distance(m_pos, movementTarget);
		if (d < 25 && !nearDoor) {
			nearDoor = true;
		}
		else if (d > 30 && nearDoor) {
			door = false;
			nearDoor = false;
			lookAround = true;
			movementTarget = Vector2f(visionRays[centre].first.p2.x * SCALE, visionRays[centre].first.p2.y * SCALE);
			doorSearchTimer = time(&timer);
		}
	}
	else {
		if (visionRays[centre].second.objectName != NULL) {
			int direction = rand() % 2;
			AIFunction(false, direction);
		}

		if (search && (Distance(m_pos, Vector2f(visionRays[centre].second.m_point.x * SCALE, visionRays[centre].second.m_point.y * SCALE)) < 50)
			|| (Distance(m_pos, Vector2f(visionRays[centre + 1].second.m_point.x * SCALE, visionRays[centre + 1].second.m_point.y * SCALE)) < 50)
			|| (Distance(m_pos, Vector2f(visionRays[centre - 1].second.m_point.x * SCALE, visionRays[centre - 1].second.m_point.y * SCALE)) < 50)) {
			int direction = rand() % 2;
			AIFunction(true, direction);
		}

		if (searchDoor && !chasing) {
			if (searchPlayer)
				SearchDoor(true);
			else
				SearchDoor(false);
		}
	}

	if (punch) {
		HittingPlayer();
	}

	//AvoidObstacles();
}

void Stalker::AIFunction(bool close, int direction)
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
				lookAround = true;
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
				lookAround = true;
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

void Stalker::AvoidObstacles()
{
	//avoid = false; 

	avoidanceRays.clear();
	avoidanceRays.push_back(visionRays[0]);
	avoidanceRays.push_back(visionRays[5]);
	avoidanceRays.push_back(visionRays[10]);

	if (!avoid) {
		for (int i = 0; i < 3; i++) {
			float d = Distance(m_pos, Vector2f(avoidanceRays[i].second.m_point.x * SCALE, avoidanceRays[i].second.m_point.y * SCALE));
			if (d < avoidDistance) {
				if (i == 0)
					desiredOrientation = VectorToAngle(avoidanceRays[i].second.m_normal);
				else
					desiredOrientation = VectorToAngle(avoidanceRays[i].second.m_normal) + 180;
				avoidPoint = Vector2f(avoidanceRays[i].second.m_point.x * SCALE, avoidanceRays[i].second.m_point.y * SCALE);
				avoid = true;
				break;
			}
		}
	}
	else {
		if (Distance(m_pos, avoidPoint) > 20) {
			avoid = false;
		}
	}
}

void Stalker::LookAround()
{
	if (!lookRight) {
		searchOrientation -= 2;
		if (searchOrientation <= -90)
			lookRight = true;
	}
	else {
		searchOrientation += 2;
		if (searchOrientation >= 90) {
			lookRight = false;
			lookAround = false;
			searchOrientation = 0;
			if (searchPlayer) {
				movementTarget = doorLocation;
				searchDoor = true;
				searchPlayer = false;
			}
		}
	}
}

void Stalker::SearchDoor(bool onlyFind)
{
	int centre = numberRays / 2;
	int above = 1;
	int below = 1;
	bool breakOut = false;

	if (visionRays[centre].second.objectName == "Door") {
		if (!onlyFind) {
			movementTarget = static_cast<Door*>(visionRays[centre].second.data)->GetOrigin();
			door = true;
		}
		else {
			doorLocation = static_cast<Door*>(visionRays[centre].second.data)->GetOrigin();
		}
		breakOut = true;
		searchDoor = false;
	}

	while ((below < centre && above < centre) && !breakOut) {
		if (visionRays[centre + above].second.objectName == "Door") {
			if (!onlyFind) {
				movementTarget = static_cast<Door*>(visionRays[centre + above].second.data)->GetOrigin();
				door = true;
			}
			else {
				doorLocation = static_cast<Door*>(visionRays[centre + above].second.data)->GetOrigin();
			}
			breakOut = true;
			searchDoor = false;
		}
		else if (visionRays[centre - below].second.objectName == "Door") {
			if (!onlyFind) {
				movementTarget = static_cast<Door*>(visionRays[centre - below].second.data)->GetOrigin();
				door = true;
			}
			else {
				doorLocation = static_cast<Door*>(visionRays[centre - below].second.data)->GetOrigin();
			}
			breakOut = true;
			searchDoor = false;
		}
		else {
			above++;
			below++;
		}
	}
}

void Stalker::SearchPlayer()
{
	int centre = numberRays / 2;
	int above = 1;
	int below = 1;
	bool breakOut = false;

	if (visionRays[centre].second.objectName == "Player") {
		spottedPlayer = static_cast<Player*>(visionRays[centre].second.data);
		breakOut = true;
	}

	while ((below <= centre && above <= centre) && !breakOut) {
		if (visionRays[centre + above].second.objectName == "Player") {
			spottedPlayer = static_cast<Player*>(visionRays[centre + above].second.data);
			breakOut = true;
		}
		else if (visionRays[centre - below].second.objectName == "Player") {
			spottedPlayer = static_cast<Player*>(visionRays[centre - below].second.data);
			breakOut = true;
		}
		else {
			above++;
			below++;
		}
	}

	if (breakOut) {
		playerSpotted = true;
		lookAround = false;
		chasing = true;
		searchOrientation = 0;
		breakOut = true;
	}
}

void Stalker::SpottedAI()
{
	int distance = 30;
	int pDistance = 55;

	if (spottedRay.second.objectName == "Player" || difftime(time(&timer), playerChaseTimer) < 1) {
		nearDoor = false;
		if (Distance(m_pos, Vector2f(spottedRay.first.p2.x * SCALE, spottedRay.first.p2.y * SCALE)) < pDistance) {
			if (!punch && difftime(time(&timer), punchTimer) > 1) {
				punch = true;
				cout << "Hitting Player" << endl;
			}
		}
		if (Distance(m_pos, Vector2f(spottedRay.first.p2.x * SCALE, spottedRay.first.p2.y * SCALE)) < distance) {
			speed = 0.0;
		}
		else {
			speed = 2;
			movementTarget = Vector2f(spottedRay.first.p2.x * SCALE, spottedRay.first.p2.y * SCALE);
		}
	}

	else if (spottedRay.second.objectName != "Player") {
		if (difftime(time(&timer), playerChaseTimer) > 2)
			playerChaseTimer = time(&timer);

		//if (Distance(m_pos, Vector2f(spottedRay.first.p2.x * SCALE, spottedRay.first.p2.y * SCALE)) < distance) {
		if (difftime(time(&timer), playerChaseTimer) > 1) {
			speed = 2;
			spottedPlayer = NULL;
			chasing = false;
			//lookAround = true;
			searchPlayer = false;
			searchDoor = true;
			door = false;
			doorSearchTimer = time(&timer);
			playerSpotted = false;
		}
		else {
			movementTarget = Vector2f(spottedRay.first.p2.x * SCALE, spottedRay.first.p2.y * SCALE);
		}
	}

}

void Stalker::HittingPlayer()
{
	if (punchDistance < maxPunchDistance) {
		punchDistance += 5;
	}
	else {
		punchTimer = time(&timer);
		punchDirection = (punchDirection == 0) ? 1 : 0;
		if (punchDirection == 0) {
			animatedPunchLeft.stop();
			animatedPunchRight.play(punchRight);
		}
		else {
			animatedPunchRight.stop();
			animatedPunchLeft.play(punchLeft);
		}
		punchDistance = 0;
		punch = false;
		damage = true;
	}
}

bool Stalker::HitPlayer()
{
	if (damage) {
		damage = false;
		return true;
	}
	return false;
}

float Stalker::VectorToAngle(b2Vec2 vec)
{
	return atan2(vec.x, vec.y) * RADTODEG;
}
