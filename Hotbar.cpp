#include "Hotbar.h"

Hotbar::Hotbar()
{
	numberSlots = 5;
	xOffset = 120;
	LoadAssets();
	CreateSlots();
}

void Hotbar::LoadAssets()
{
	m_texture.loadFromFile("Sprites/hotbarSlot.png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	m_sprite.setScale(0.9, 0.9);
	//offset for where the container is drawing
}

void Hotbar::CreateSlots()
{ 	
	for (int i = 0; i < numberSlots; i++) {
		slots.push_back(HotbarSlot());
	}
}

void Hotbar::Draw()
{
	Vector2f center = window->getView().getCenter();
	Vector2f size = window->getView().getSize();

	Vector2f spritePos = m_sprite.getPosition();
	spritePos.y = center.y + (size.y / 3);

	for (int i = 0; i < numberSlots; i++) {
		spritePos.x = center.x - (size.x / 3) + (xOffset * i);
		m_sprite.setPosition(spritePos);
		window->draw(m_sprite);
	}
}

bool Hotbar::AddItem(Vector2f dropPos, Item* item)
{
	int slot = CheckSprite(dropPos);

	if (slot >= 0 && slots[slot].item == NULL) {
		item->SetHotbarSlot(slot);
		slots[slot].item = item;
		return true;
	}
	return false;
}

int Hotbar::CheckSprite(Vector2f mousePos)
{
	//checking if the mouse position is inside the sprite
	float height = m_sprite.getGlobalBounds().height;
	float width = m_sprite.getGlobalBounds().width;

	Vector2f center = window->getView().getCenter();
	Vector2f size = window->getView().getSize();
	Vector2f spritePos = m_sprite.getPosition();

	for (int i = 0; i < numberSlots; i++) {
		spritePos.x = center.x - (size.x / 3) + (xOffset * i);
		if (mousePos.x > spritePos.x && mousePos.x < spritePos.x + width &&
			mousePos.y > spritePos.y && mousePos.y < spritePos.y + height)
			return i;
	}

	return -1;
}

void Hotbar::RemoveItem(int slot)
{
	if (slot >= 0) {
		slots[slot].item = NULL;
	}
}

Item * Hotbar::SelectItem()
{
	return nullptr;
}
