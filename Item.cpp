#pragma once
#include "Item.h"

//For the handling of collision filtering
enum _entityCategory {
	PLAYER = 0x0004,
	ITEM = 0x0008,
	CONTAINER = 0x0016,
	WALL = 0x0020,
	DOOR = 0x0024,
};

Item::Item( ItemType t, int s) : type(t), size(s) {
	onGround = false;
	LoadAssets();
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
	float posX = pos.x + (rect.width / 100 * startX) + (m_sprite.getTextureRect().width * (slotCol - 1)) + (xOffset * (slotCol - 1));
	float posY = pos.y + (rect.height / 100 * startY) + m_sprite.getTextureRect().height * (slotRow - 1) + (yOffset * (slotRow - 1));
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
	float posX = pos.x + (rect.width / 100 * startX) + (m_sprite.getTextureRect().width * (slotCol - 1)) + (xOffset * (slotCol - 1));
	float posY = pos.y + (rect.height / 100 * startY) + (m_sprite.getTextureRect().height * (slotRow - 1)) + (yOffset * (slotRow - 1));
	m_sprite.setPosition(Vector2f(posX, posY));
	window->draw(m_sprite);
}

void Item::DrawInHotbar(Vector2f pos)
{
	pos.x += 35;
	pos.y += 36;
	m_sprite.setScale(0.9, 0.9);
	m_sprite.setPosition(pos);
	window->draw(m_sprite);
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
