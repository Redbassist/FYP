#pragma once
#include "Item.h" 

Item::~Item()
{
	if (onGround)
		body->GetFixtureList()->SetUserData("Destroy");
}

Item::Item(ItemType t, int s) : type(t), size(s) {
	onGround = false;
	LoadAssets();
}

Item::Item(ItemType t, int s, int amount) : type(t), size(s), amountAmmo(amount) {
	onGround = false;
	LoadAssets();

	switch (t) {
	case (ItemType::AMMOPISTOL) :
		maxAmmo = 20;
		break;
	case (ItemType::AMMORIFLE) :
		maxAmmo = 100;
		break;
	case (ItemType::AMMOSHOTGUN) :
		maxAmmo = 8;
		break;
	case (ItemType::PISTOL) :
		maxAmmo = 7;
		break;
	case (ItemType::RIFLE) :
		maxAmmo = 30;
		break;
	case (ItemType::SHOTGUN) :
		maxAmmo = 6;
		break;
	}
}

//debugging constructor
Item::Item(ItemType t, int s, bool g, Vector2f pos) : type(t), size(s) {
	onGround = g;
	m_pos = pos;
	LoadAssets();
	createBox2dBody();
} 

void Item::LoadAssets()
{
	LoadSprites(getTextForEnum(type));
}

void Item::LoadSprites(std::string type)
{
	m_texture.loadFromFile("Sprites/" + type + ".png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	m_sprite.setScale(Vector2f(0.2, 0.2));
	m_sprite.setPosition(m_pos);
}

void Item::SlotNumber(int sentSlot)
{
	slot = sentSlot;
}

void Item::SetHotbarSlot(int hbslot)
{
	hotbarSlot = hbslot;
}

int Item::GetHotbarSlot()
{
	return hotbarSlot;
}

void Item::ResetSlot()
{
	slot = 0;
}

int Item::GetSlot()
{
	return slot;
}

int Item::GetSize() {
	return size;
}

pair<bool, int> Item::RemoveAmmo(int amount)
{
	amountAmmo -= amount;
	int returnAmount = amount;
	if (amountAmmo < 0) {
		int returnAmount = amount + amountAmmo;
		amountAmmo = 0;
		return pair<bool, int>(false, (returnAmount));
	}
	return pair<bool, int>(true, (returnAmount));
}

void Item::Draw() {
	if (onGround)
		window->draw(m_sprite);
}

void Item::DrawInInventory(Vector2f pos, FloatRect rect, int slotCol, int slotRow) {
	/*SetScale(newSize / oldSize)
	float oldScaleX = m_sprite.getScale().x;
	float oldScaleY = m_sprite.getScale().y;*/
	m_sprite.setScale(0.5, 0.5);
	float startX = 24;
	float startY = 40;

	float xOffset = -(rect.width / 100 * 8);
	float yOffset = -(rect.height / 100 * 3.7);
	float posX;
	if (m_sprite.getTextureRect().width == 128)
		posX = pos.x + (rect.width / 100 * startX) + 64 * (slotCol - 1) + (xOffset * (slotCol - 1)) + 20;
	else
		posX = pos.x + (rect.width / 100 * startX) + 64 * (slotCol - 1) + (xOffset * (slotCol - 1));
	float posY = pos.y + (rect.height / 100 * startY) + 64 * (slotRow - 1) + (yOffset * (slotRow - 1));
	m_sprite.setPosition(Vector2f(posX, posY));
	window->draw(m_sprite);
}

void Item::DrawInContainer(Vector2f pos, FloatRect rect, int slotCol, int slotRow) {
	/*SetScale(newSize / oldSize)
	float oldScaleX = m_sprite.getScale().x;
	float oldScaleY = m_sprite.getScale().y;*/
	m_sprite.setScale(0.6, 0.6);
	float startX = 24;
	float startY = 16;

	float xOffset = (rect.width / 100 * 1.5);
	float yOffset = (rect.height / 100 * 1);
	float posX;
	if (m_sprite.getTextureRect().width == 128)
		posX = pos.x + (rect.width / 100 * startX) + 64 * (slotCol - 1) + (xOffset * (slotCol - 1)) + 40;
	else
		posX = pos.x + (rect.width / 100 * startX) + 64 * (slotCol - 1) + (xOffset * (slotCol - 1));
	float posY = pos.y + (rect.height / 100 * startY) + (m_sprite.getTextureRect().height * (slotRow - 1)) + (yOffset * (slotRow - 1));
	m_sprite.setPosition(Vector2f(posX, posY));
	window->draw(m_sprite);
}

void Item::DrawInHotbar(Vector2f pos)
{
	pos.x += 18;
	pos.y += 18;
	Vector2f tempPos = m_sprite.getPosition();
	m_sprite.setScale(0.45, 0.45);
	m_sprite.setPosition(pos);
	window->draw(m_sprite);
	m_sprite.setPosition(tempPos);
}

void Item::DrawDragged()
{
	Vector2i mousePos = Mouse::getPosition(*window);
	//used to convert to view coordinates
	sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);

	Sprite temp = m_sprite;
	temp.setPosition(worldMousePos);
	window->draw(temp);
}

void Item::PickedUp() {
	onGround = false;
	body->GetFixtureList()->SetUserData("Destroy");
}

bool Item::CheckSprite(Vector2f mouseClick) {
	//checking if the mouse position is inside the sprite
	float height = m_sprite.getGlobalBounds().height;
	float width = m_sprite.getGlobalBounds().width;
	Vector2f spritePos = Vector2f(m_sprite.getPosition().x - width / 2, m_sprite.getPosition().y - height / 2);

	if (mouseClick.x > spritePos.x && mouseClick.x < spritePos.x + width &&
		mouseClick.y > spritePos.y && mouseClick.y < spritePos.y + height)
		return true;

	return false;
}

void Item::Dropped(Vector2f pos) {
	onGround = true;
	inHotBar = false;
	hotbarSlot = -1;
	m_sprite.setScale(Vector2f(0.2, 0.2));
	m_sprite.setPosition(pos);
	createBox2dBody();
	body->SetTransform(b2Vec2(m_sprite.getPosition().x / SCALE, m_sprite.getPosition().y / SCALE), 0);
}

std::string Item::getTextForEnum(int enumVal) {
	return ItemTypeStrings[enumVal];
}

void Item::createBox2dBody() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(m_pos.x / SCALE, m_pos.y / SCALE);
	bodyDef.userData = this;
	body = world->CreateBody(&bodyDef);
	b2PolygonShape box;
	box.SetAsBox((m_sprite.getGlobalBounds().width / 2.0f) / SCALE, (m_sprite.getGlobalBounds().height / 2.0f) / SCALE);
	fixtureDef.shape = &box;
	fixtureDef.isSensor = true;
	fixtureDef.density = 1;
	fixtureDef.userData = "Item";

	fixtureDef.filter.categoryBits = ITEM;
	fixtureDef.filter.maskBits = PLAYER;

	body->CreateFixture(&fixtureDef);
}
