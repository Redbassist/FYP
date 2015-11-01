#pragma once
#include "Item.h"

Item::Item(b2World* w, RenderWindow* rw, ItemType t) : world(w), window(rw), type(t) {
	onGround = false;
	LoadAssets();
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

void Item::Draw()
{
	if (onGround)
		window->draw(m_sprite);
}

std::string Item::getTextForEnum(int enumVal)
{
	return ItemTypeStrings[enumVal];
}
