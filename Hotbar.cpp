#include "Hotbar.h"

Hotbar::Hotbar()
{
	numberSlots = 5;
	xOffset = 60;
	LoadAssets();
	CreateSlots();
}

void Hotbar::LoadAssets()
{
	m_texture.loadFromFile("Sprites/hotbarSlot.png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	m_sprite.setScale(0.45, 0.45);

	m_textureSelected.loadFromFile("Sprites/hotbarSlotSelected.png");
	m_textureSelected.setSmooth(false);
	m_spriteSelected.setTexture(m_textureSelected);
	m_spriteSelected.setTextureRect(sf::IntRect(0, 0, m_textureSelected.getSize().x, m_textureSelected.getSize().y));
	m_spriteSelected.setScale(0.45, 0.45);
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
	spritePos.y = center.y + (size.y / 2.65);

	for (int i = 0; i < numberSlots; i++) {
		spritePos.x = center.x - (size.x / 2.3) + (xOffset * i);
		m_sprite.setPosition(spritePos);
		m_spriteSelected.setPosition(spritePos);
		if (slots[i].item != NULL) { slots[i].item->DrawInHotbar(spritePos); }
		if (slots[i].selected)
			window->draw(m_spriteSelected);
		else
			window->draw(m_sprite);
	}
}

bool Hotbar::AddItem(Vector2f dropPos, Item* item)
{
	int slot = CheckSprite(dropPos);

	if (slot < 0) {
		return false;
	}
	else if (item->GetType() == AMMOPISTOL || item->GetType() == AMMORIFLE || item->GetType() == AMMOSHOTGUN) {
		return false;
	}
	else if (item->inHotBar == false) {
		if (slots[slot].item != NULL) {
			slots[slot].item->SetHotbarSlot(-1);
			slots[slot].item->inHotBar = false;
		}
		item->SetHotbarSlot(slot);
		slots[slot].item = item;
		item->inHotBar = true;
		return true;
	}
	else if (item->inHotBar == true) {
		return true;
	}
	else if (slots[slot].item == item) {
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
		spritePos.x = center.x - (size.x / 2.3) + (xOffset * i);
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

Item * Hotbar::SelectItem(int i)
{
	int size = slots.size();
	for (int j = 0; j < size; j++) {
		slots[j].selected = false;
	}
	slots[i].selected = true;
	return slots[i].item;
}
