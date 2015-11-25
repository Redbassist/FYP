#include "Player.h"

//For the handling of collision filtering
enum _entityCategory {
	PLAYER = 0x0004,
	ITEM = 0x0008,
	CONTAINER = 0x0016,
	WALL = 0x0020,
	DOOR = 0x0024,
};

Player::Player(b2World* b2world, RenderWindow* w, InputManager* im, Vector2f pos) : world(b2world), window(w), inputManager(im), m_pos(pos)
{
	m_pos = pos;
	inventory = new Inventory(w, im);
	speed = 0.045f;
	touchedContainer = NULL;
	touchedDoor = NULL;

	LoadAssets();
	LoadBinds();
	createBox2dBody();
}

void Player::LoadAssets() {
	//loading the animations for the player
	m_legsMovingTexture.loadFromFile("Sprites/legs.png");
	m_legsMovingTexture.setSmooth(false);

	legsIdle.setSpriteSheet(m_legsMovingTexture);
	legsIdle.addFrames(1, 1, 1, 32, 32);

	legsMoving.setSpriteSheet(m_legsMovingTexture);
	legsMoving.addFrames(12, 4, 3, 32, 32);

	currentAnimation = &legsIdle;

	animatedSprite = AnimatedSprite(sf::seconds(0.08), true, false);
	animatedSprite.setOrigin(16, 16);
	animatedSprite.setPosition(m_pos);
	animatedSprite.setScale(1.8, 1.3);

	//loading the body sprite for the player
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
	inputManager->BindSingleKeyPress(&actions.interact, Keyboard::Key::E);
	inputManager->BindSingleKeyPress(&actions.inventory, Keyboard::Key::G);
	inputManager->BindSingleMousePress(&actions.drop, Mouse::Button::Right);
	inputManager->BindSingleMousePress(&actions.take, Mouse::Button::Left);
}

void Player::Draw() {
	//frame time which is used for updating the animation
	sf::Time frameTime = frameClock.restart();

	//Setting the animation of the player legs depending on if is moving or not
	if (actions.walkUp || actions.walkDown || actions.walkLeft || actions.walkRight) {
		currentAnimation = &legsMoving;
	}
	else {
		currentAnimation = &legsIdle;
	}
	animatedSprite.play(*currentAnimation);
	animatedSprite.update(frameTime);

	window->draw(animatedSprite);
	window->draw(m_bodySprite);
	inventory->Draw();
}

void Player::Update() {
	if (!inventory->CheckOpen()) {
		SetRotation();
	}
	Movement();
	Interaction();

	//setting the position of the sprite to the physics body
	animatedSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	m_bodySprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	m_pos = m_bodySprite.getPosition();

	//setting camera to the player
	CenterCamera();
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
}

void Player::Interaction() {
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
		Vector2i mousePos = Mouse::getPosition(*window);
		//used to convert to view coordinates
		sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);
		Item* item = inventory->DropItem((Vector2f)worldMousePos, m_pos);
		if (item != NULL)
			touchedContainer->AddItem(item);
		actions.drop = false;
	}

	else if (actions.drop && inventory->CheckOpen()) {
		Vector2i mousePos = Mouse::getPosition(*window);
		//used to convert to view coordinates
		sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);
		Item* item = inventory->DropItem((Vector2f)worldMousePos, m_pos);
		if (item != NULL)
			item->Dropped(m_pos);
		actions.drop = false;
	}

	//dropping items from the inventory
	if (actions.take && touchedContainer != NULL && touchedContainer->CheckOpen()) {
		Vector2i mousePos = Mouse::getPosition(*window);
		//used to convert to view coordinates
		sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);
		Item* tempItem = touchedContainer->TakeItem(worldMousePos);
		if (tempItem != NULL)
			inventory->AddItem(tempItem);
		actions.take = false;
	}

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
	m_bodySprite.setRotation(orientation);
	animatedSprite.setRotation(orientation);
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

float Player::getRotationAngle() {
	Vector2i mousePos = Mouse::getPosition(*window);
	//used to convert to view coordinates
	sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);
	float dx = worldMousePos.x - m_pos.x;
	float dy = worldMousePos.y - m_pos.y;
	float radian = atan2f(dy, dx);
	return (radian * 180 / 3.14159265359);
}
