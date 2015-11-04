#pragma once
#include "Item.h"

enum _entityCategory {
	PLAYER = 0x0004,
	ITEM = 0x0008
};

Item::Item(b2World* w, RenderWindow* rw, ItemType t, int s) : world(w), window(rw), type(t), size(s) {
	onGround = false;
	LoadAssets();
}

//debugging constructor
Item::Item(b2World* w, RenderWindow* rw, ItemType t, int s, bool g, Vector2f pos) : world(w), window(rw), type(t), size(s) {
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

int Item::GetSize() {
	return size;
}

void Item::Draw() {
	if (onGround)
		window->draw(m_sprite);
}

void Item::DrawInInventory(Vector2f pos, FloatRect rect, int slotCol, int slotRow) {
	//SetScale(newSize / oldSize) 
	float oldScaleX = m_sprite.getScale().x;
	float oldScaleY = m_sprite.getScale().y;
	m_sprite.setScale(0.6, 0.6);

	float xOffset = -(rect.width / 100 * 1);
	float yOffset = -(rect.height / 100 * 1.2);
	float posX = pos.x + (rect.width / 100 * 30.5) + (m_sprite.getTextureRect().width * (slotCol - 1)) + (xOffset * (slotCol - 1));
	float posY = pos.y + (rect.height / 100 * 52) + m_sprite.getTextureRect().height * (slotRow - 1) + (yOffset * (slotRow - 1));
	m_sprite.setPosition(Vector2f(posX, posY));
	window->draw(m_sprite);
}

void Item::PickedUp() {
	onGround = false;
}

void Item::Dropped(Vector2f pos) {
	onGround = true;
	m_sprite.setScale(Vector2f(0.2, 0.2));
	m_sprite.setPosition(pos);
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
