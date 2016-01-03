#include "Player.h"

//For the handling of collision filtering
enum _entityCategory {
	PLAYER = 0x0004,
	ITEM = 0x0008,
	CONTAINER = 0x0016,
	WALL = 0x0020,
	DOOR = 0x0024,
};

Player::Player(Vector2f pos) : m_pos(pos)
{
	m_pos = pos;
	inventory = new Inventory();
	speed = 0.06f;
	touchedContainer = NULL;
	touchedDoor = NULL;
	dragItem = NULL;

	fullHealth = 1000;
	health = fullHealth / 100;
	heartBeatX = 0;
	currentHours = 12;
	currentMinutes = 0;
	nextMinute = 0;

	LoadAssets();
	LoadBinds();
	createBox2dBody();
}

void Player::LoadAssets() {
	//loading the animations for the player
	m_AnimationLegsTexture.loadFromFile("Sprites/legs.png");
	m_AnimationLegsTexture.setSmooth(false);
	legsIdle.setSpriteSheet(m_AnimationLegsTexture);
	legsIdle.addFrames(1, 1, 1, 32, 32);
	legsMoving.setSpriteSheet(m_AnimationLegsTexture);
	legsMoving.addFrames(12, 4, 3, 32, 32);
	currentLegAnimation = &legsIdle;

	m_AnimationTopTexture.loadFromFile("Sprites/playerTop.png");
	m_AnimationTopTexture.setSmooth(false);
	playerTopIdle.setSpriteSheet(m_AnimationTopTexture);
	playerTopIdle.addFrames(1, 1, 1, 31, 27);
	playerTopMoving.setSpriteSheet(m_AnimationTopTexture);
	playerTopMoving.addFrames(12, 4, 3, 31, 27);
	currentTopAnimation = &playerTopIdle;

	animatedLegSprite = AnimatedSprite(sf::seconds(0.08), true, false);
	animatedLegSprite.setOrigin(16, 16);
	animatedLegSprite.setPosition(m_pos);
	animatedLegSprite.setScale(1.8, 1.3);

	animatedTopSprite = AnimatedSprite(sf::seconds(0.08), true, false);
	animatedTopSprite.setOrigin(12, 13.5);
	animatedTopSprite.setPosition(m_pos);
	animatedTopSprite.setScale(1, 1);

	//loading the watch sprites for the UI
	watchTexture.loadFromFile("Sprites/watch.png");
	watchTexture.setSmooth(false);
	watchSprite.setTexture(watchTexture);
	watchSprite.setTextureRect(sf::IntRect(0, 0, watchTexture.getSize().x, watchTexture.getSize().y));
	watchSprite.setScale(0.3f, 0.3f);

	watchBGTexture.loadFromFile("Sprites/watchBack.png");
	watchBGTexture.setSmooth(false);
	watchBGSprite.setTexture(watchBGTexture);
	watchBGSprite.setTextureRect(sf::IntRect(0, 0, watchBGTexture.getSize().x, watchBGTexture.getSize().y));
	watchBGSprite.setScale(0.3f, 0.3f);

	heartBeatTexture.loadFromFile("Sprites/HeartBeat.png");
	heartBeatTexture.setSmooth(false);
	heartBeatSprite.setTexture(heartBeatTexture);
	heartBeatSprite.setTextureRect(sf::IntRect(0, 0, heartBeatTexture.getSize().x, heartBeatTexture.getSize().y));
	heartBeatSprite.setScale(0.3f, 0.3f);

	//setting the text inside the button
	watchFont.loadFromFile("digital.ttf");

	heartRateText.setFont(watchFont);
	heartRateText.setCharacterSize(16);
	heartRateText.setColor(sf::Color::Black);

	currentTime.setFont(watchFont);
	currentTime.setCharacterSize(32);
	currentTime.setColor(sf::Color::Black);
}

void Player::LoadBinds() {
	//binding the keys for the player
	InputManager::GetInstance()->Bind(&actions.walkUp, Keyboard::Key::W);
	InputManager::GetInstance()->Bind(&actions.walkDown, Keyboard::Key::S);
	InputManager::GetInstance()->Bind(&actions.walkLeft, Keyboard::Key::A);
	InputManager::GetInstance()->Bind(&actions.walkRight, Keyboard::Key::D);
	InputManager::GetInstance()->BindSingleKeyPress(&actions.interact, Keyboard::Key::E);
	InputManager::GetInstance()->BindSingleKeyPress(&actions.inventory, Keyboard::Key::G);
	InputManager::GetInstance()->BindSingleMousePress(&actions.drop, Mouse::Button::Right);
	InputManager::GetInstance()->BindSingleMousePress(&actions.take, Mouse::Button::Left);
	InputManager::GetInstance()->Bind(&actions.drag, Mouse::Button::Left);
}

void Player::Draw() {
	//frame time which is used for updating the animation
	sf::Time frameTime = frameClock.restart();

	//Setting the animation of the player legs depending on if is moving or not
	if (actions.walkUp || actions.walkDown || actions.walkLeft || actions.walkRight) {
		currentTopAnimation = &playerTopMoving;
		currentLegAnimation = &legsMoving;
	}
	else {
		currentTopAnimation = &playerTopIdle;
		currentLegAnimation = &legsIdle;
	}
	animatedTopSprite.play(*currentTopAnimation);
	animatedTopSprite.update(frameTime);

	animatedLegSprite.play(*currentLegAnimation);
	animatedLegSprite.update(frameTime);

	window->draw(animatedLegSprite);
	window->draw(animatedTopSprite);

	//drawing the inventory and it's contents
	inventory->Draw();

	//if there is an item being drawn, draw it here
	if (dragItem != NULL) {
		dragItem->DrawDragged();
	}

	DrawWatch();
}

void Player::Update() {
	SetRotation();
	Movement();
	Interaction();
	SetStats();

	//setting the position of the sprite to the physics body
	animatedLegSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	animatedTopSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	m_pos = animatedTopSprite.getPosition();

	//setting camera to the player
	CenterCamera();

	//setting the watch position
	WatchUIPosition();

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		SceneChanger::GetInstance()->ChangeScene(GameState::GAMEMENU);
	}
}

void Player::CenterCamera()
{
	View view = window->getView();
	view.setCenter(m_pos);
	window->setView(view);
}

void Player::Movement() {
	b2Vec2 position = body->GetPosition();

	if (actions.walkUp) {
		position.y -= speed;
	}
	if (actions.walkDown) {
		position.y += speed;
	}
	if (actions.walkLeft) {
		position.x -= speed;
	}
	if (actions.walkRight) {
		position.x += speed;
	}

	body->SetTransform(position, 0);
	m_pos = Vector2f(position.x * SCALE, position.y * SCALE);

	//updating the player listener to the position of the player
	float temp = orientation;
	temp += 180;
	AudioManager::GetInstance()->setListener(m_pos, temp);
}

void Player::Interaction() {
	Vector2i mousePos = Mouse::getPosition(*window);
	//used to convert to view coordinates
	sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);

	//opening and closing the inventory
	if (actions.inventory && inventory->CheckOpen()) {
		inventory->Close();
		actions.inventory = false;
	}
	else if (actions.inventory && !inventory->CheckOpen()) {
		inventory->Open();
		actions.inventory = false;
	}

	if (actions.interact) {
		//opening and closing a touched container
		if (touchedContainer != NULL) {
			if (!touchedContainer->CheckOpen()) {
				touchedContainer->Open();
				actions.interact = false;
			}
			else {
				touchedContainer->Close();
				actions.interact = false;
			}
		}
		//picking up a close item
		else if (!touchedItems.empty()) {
			inventory->AddItem(touchedItems[0]);
			touchedItems[0]->PickedUp();
			touchedItems.erase(touchedItems.begin());
			actions.interact = false;
		}
	}

	//dropping items from the inventory
	if (actions.drop && touchedContainer != NULL && touchedContainer->CheckOpen()) { 
		Item* item = inventory->DropItem((Vector2f)worldMousePos, m_pos);
		if (item != NULL)
			touchedContainer->AddItem(item);
		actions.drop = false;
	}

	//dropping items from the inventory
	else if (actions.drop && inventory->CheckOpen()) { 
		Item* item = inventory->DropItem((Vector2f)worldMousePos, m_pos);
		if (item != NULL)
			item->Dropped(m_pos);
		actions.drop = false;
	}

	if (actions.drag && inventory->CheckOpen()) {
		if (dragItem == NULL) {
			dragItem = inventory->DragItem(worldMousePos);
		}	 
	}
	else if (!actions.drag && dragItem != NULL) {
		dragItem = NULL;
		cout << "Dropped dragged item" << endl;
	}

	if (actions.take && touchedContainer != NULL && touchedContainer->CheckOpen()) { 
		Item* tempItem = touchedContainer->TakeItem(worldMousePos);
		if (tempItem != NULL)
			inventory->AddItem(tempItem);
		actions.take = false;
	} 

	//opening a door
	if (actions.interact && touchedDoor != NULL) {
		touchedDoor->OpenClose();
		actions.interact = false;
	}
}

void Player::TouchingContainer(Container* container) {
	touchedContainer = container;
}

void Player::NotTouchingContainer() {
	touchedContainer = NULL;
}

void Player::TouchingDoor(Door* door) {
	touchedDoor = door;
}

void Player::NotTouchingDoor() {
	touchedDoor = NULL;
}

void Player::TouchingItem(Item* item) {
	touchedItems.push_back(item);
}

void Player::NotTouchingItem(Item* item) {
	std::vector<Item*>::iterator iter = touchedItems.begin();
	std::vector<Item*>::iterator end = touchedItems.end();

	for (; iter != end; ++iter) {
		if (item == (*iter)) {
			touchedItems.erase(iter);
			break;
		}
	}
}

void Player::SetRotation() {
	orientation = getRotationAngle();
	animatedLegSprite.setRotation(orientation);
	animatedTopSprite.setRotation(orientation);
}

void Player::createBox2dBody() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_pos.x / SCALE, m_pos.y / SCALE);
	bodyDef.userData = this;
	bodyDef.gravityScale = 1;
	body = world->CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox((31 / 2.0f) / SCALE, (27 / 2.0f) / SCALE);
	fixtureDef.shape = &dynamicBox;

	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = "Player";
	fixtureDef.restitution = b2MixRestitution(0, 0);

	fixtureDef.filter.categoryBits = PLAYER;
	fixtureDef.filter.maskBits = ITEM | CONTAINER | WALL | DOOR;

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

//Setting the stats for the UI depending on the status of the player
void Player::SetStats() {
	//for seting current heart rate on watch using the health of the player
	heartRate = fullHealth / (health * 100);
	int heartRateForText = 85 + (10 * heartRate);
	heartRateText.setString(to_string(heartRateForText));

	//current time on the watch 1 second = 1 minute
	nextMinute++;

	if (nextMinute > 59) {
		nextMinute = 0;
		currentMinutes++;
		if (currentMinutes > 59) {
			currentHours++;
			if (currentHours > 23)
				currentHours = 0;
			currentMinutes = 0;
		}
	}

	String timeText;

	if (currentHours < 10)
		timeText = "0" + to_string(currentHours) + " : ";
	else
		timeText = to_string(currentHours) + " : ";

	if (currentMinutes < 10)
		timeText += "0" + to_string(currentMinutes);
	else
		timeText += to_string(currentMinutes);

	currentTime.setString(timeText);
}

void Player::WatchUIPosition() {
	//placing the watchUI in the correct position on the screen
	Vector2f center = window->getView().getCenter();
	Vector2f size = window->getView().getSize();

	sf::Vector2f watchBGOffset = sf::Vector2f(size.x / 20, size.y / 6);
	sf::Vector2f heartBeatOffset = sf::Vector2f(size.x / 19.5, size.y / 6);
	sf::Vector2f heartRateTextOffset = sf::Vector2f(size.x / 12.2, size.y / 5.8);
	sf::Vector2f timeTextOffset = sf::Vector2f(size.x / 16.6, size.y / 3.2);

	//placing the watch / heart beat monitor / heart rate text / time
	watchBGSprite.setPosition(center.x + size.x / 3.1 + watchBGOffset.x, center.y + watchBGOffset.y);
	heartBeatSprite.setPosition((center.x + size.x / 3.1 + heartBeatOffset.x) + heartBeatX, center.y + heartBeatOffset.y);
	watchSprite.setPosition(center.x + size.x / 3.1, center.y);
	heartRateText.setPosition(center.x + size.x / 3.1 + heartRateTextOffset.x, center.y + heartRateTextOffset.y);
	currentTime.setPosition(center.x + size.x / 3.1 + timeTextOffset.x, center.y + timeTextOffset.y);

	if (heartBeatX < 85) {
		heartBeatX += heartRate;
	}
	else
		heartBeatX = 0;
}

void Player::DrawWatch() {
	window->draw(watchBGSprite);
	window->draw(heartBeatSprite);
	window->draw(watchSprite);
	window->draw(heartRateText);
	window->draw(currentTime);
}

float Player::getRotationAngle() {
	Vector2i mousePos = Mouse::getPosition(*window);
	//used to convert to view coordinates
	sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);
	float dx = worldMousePos.x - m_pos.x;
	float dy = worldMousePos.y - m_pos.y;
	float radian = atan2f(dy, dx);
	return (radian * 180 / 3.14159265359);
}
