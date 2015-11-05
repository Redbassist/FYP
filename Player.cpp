#include "Player.h"

//For the handling of collision filtering
enum _entityCategory {
	PLAYER = 0x0004,
	ITEM = 0x0008,
	CONTAINER = 0x0016
};

Player::Player(b2World* b2world, RenderWindow* w, InputManager* im, Vector2f pos) : world(b2world), window(w), inputManager(im), m_pos(pos)
{
	inventory = new Inventory(w, im);
	speed = 0.045f;
	touchedContainer = NULL;

	LoadAssets();
	LoadBinds();
	createBox2dBody();
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
	inputManager->BindSingleKeyPress(&actions.interact, Keyboard::Key::E);
	inputManager->BindSingleKeyPress(&actions.inventory, Keyboard::Key::G);
	inputManager->BindSingleMousePress(&actions.drop, Mouse::Button::Right);
	inputManager->BindSingleMousePress(&actions.take, Mouse::Button::Right);
}

void Player::Draw() {
	window->draw(m_legSprite);
	window->draw(m_bodySprite);
	inventory->Draw();
}

void Player::Update() {
	if (!inventory->CheckOpen()) {
		SetRotation();
	}
	Movement();
	Interaction();
	m_legSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	m_bodySprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	float poop = body->GetPosition().x;
	m_pos = m_bodySprite.getPosition();
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

	//DEGREE TO RADIAN <--- ADD THIS!!!
	body->SetTransform(position, 0);
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
		else if (!touchedItems.empty()){
			inventory->AddItem(touchedItems[0]);
			touchedItems[0]->PickedUp();
			touchedItems.erase(touchedItems.begin());
			actions.interact = false;
		}
	}

	//dropping items from the inventory
	/*if (actions.drop && touchedContainer != NULL && touchedContainer->CheckOpen()) {
		Vector2i mousePos = Mouse::getPosition(*window);
		//used to convert to view coordinates
		sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);
		inventory->DropItem((Vector2f)worldMousePos, m_pos);
		actions.drop = false;
	}*/

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
}

void Player::TouchingContainer(Container* container) {
	touchedContainer = container;
}

void Player::NotTouchingContainer() {
	touchedContainer = NULL;
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
	m_bodySprite.setRotation(getRotationAngle());
	m_legSprite.setRotation(getRotationAngle());
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
	fixtureDef.filter.maskBits = ITEM | CONTAINER;

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
