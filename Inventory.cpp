#include "Inventory.h"

Inventory::Inventory(RenderWindow* w, InputManager* im) : window(w), inputManager(im) {
	open = false;
	invCols = 4;
	invRows = 3;
	LoadAssets();
}

void Inventory::LoadAssets()
{
	m_texture.loadFromFile("Sprites/backpack.png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	m_sprite.setScale(Vector2f(0.45, 0.45));
	offset.x = m_sprite.getTextureRect().width;
}


void Inventory::AddItem(Item* item) {
	inventory.push_back(item);
}

void Inventory::DropItem(Vector2f pos) {

	if (inventory.size() > 0) {
		inventory[0]->Dropped(pos);
		inventory.clear();
	}
}

/*
Item* Inventory::RemoveItem(Vector2f pos) {

}*/

void Inventory::Open() {
	open = true;
}

void Inventory::Close() {
	open = false;
}

bool Inventory::CheckOpen() {
	return open;
}

void Inventory::Draw() {
	Vector2f center = window->getView().getCenter();
	Vector2f size = window->getView().getSize();

	m_sprite.setPosition(center.x - size.x / 2 - offset.x, center.y - size.y / 2);
	window->draw(m_sprite);

	if (open) {
		if (offset.x > 0)
			offset.x -= 40;
		//drawing the items in the inventory
		DrawItems();
	}

	else {
		if (offset.x < m_sprite.getTextureRect().width)
			offset.x += 40;
	}
}

void Inventory::DrawItems() {
	//putting the inventory items in the right slots and then drawing them
	int size = inventory.size();
	int invSlot = 1;
	int currentRow = 1;
	for (int i = 0; i < size; i++) {
		inventory[i]->DrawInInventory(m_sprite.getPosition(), m_sprite.getGlobalBounds(), invSlot, currentRow);
		if (invSlot + inventory[i]->GetSize() > invCols) {
			invSlot = 1;
			currentRow++;
		}
		else {
			invSlot += inventory[i]->GetSize();
		}
	}
}
