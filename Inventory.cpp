#include "Inventory.h"

Inventory::Inventory(RenderWindow* w, InputManager* im) : window(w), inputManager(im) {
	open = false;
	invCols = 4;
	invRows = 3;
	invSize = 12;
	LoadAssets();
	SetupSlots();
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

void Inventory::SetupSlots() {
	//creates the number of slots desired in the arrangement specified in the constuctor
	int slotNumber = 1;
	int currentCol = 1;
	int currentRow = 1;

	for (int i = 0; i < invSize; i++) {
		Slot tempSlot;
		tempSlot.number = slotNumber++;
		if (currentCol > invCols) {
			currentCol = 1;
			currentRow++;
		}
		tempSlot.col = currentCol;
		tempSlot.row = currentRow;
		currentCol++;
		tempSlot.item = NULL;
		tempSlot.full = false;
		slots.push_back(tempSlot);
	}
}

void Inventory::AddItem(Item* item) {
	//this method will look through the slots in the inventory and find one that is free for the item
	int size = slots.size();

	for (int i = 0; i < size; i++) {
		if (item->GetSize() == 1 && !slots[i].full) {
			slots[i].item = item;
			slots[i].full = true;
			break;
		}
		else if (item->GetSize() == 2 && !slots[i].full && !slots[i + 1].full && slots[i].col != invCols) {
			slots[i].item = item;
			slots[i].full = true;
			slots[i + 1].full = true;
			break;
		}
		else if (item->GetSize() == 2) {
			bool loop = true;
			while (loop) {
				if (!slots[i].full && !slots[i + 1].full && slots[i].col != invCols) {
					slots[i].item = item;
					slots[i].full = true;
					slots[i + 1].full = true;
					loop = false;
				}
				i++;
			}
			break;
		}
	}
}

Item* Inventory::DropItem(Vector2f clickPos, Vector2f playerPos) {
	int size = slots.size();

	for (int i = 0; i < size; i++) {
		if (slots[i].full == true && slots[i].item != NULL) {
			if (slots[i].item->CheckSprite(clickPos)) {
				Item* tempItem = slots[i].item;
				if (slots[i].item->GetSize() == 1) { 
					slots[i].full = false;
					slots[i].item = NULL;
				}
				else { 
					slots[i].full = false;
					slots[i + 1].full = false;
					slots[i].item = NULL;
				}
				return tempItem;
			}
		}
	}

	return NULL;
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
	//opening and closing the inventory onto the screen. SLIDES.
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
	int size = slots.size();
	int invSlot = 1;
	int currentRow = 1;
	for (int i = 0; i < size; i++) {
		if (slots[i].item != NULL && slots[i].full == true)
			slots[i].item->DrawInInventory(m_sprite.getPosition(), m_sprite.getGlobalBounds(), slots[i].col, slots[i].row); 
	}
}
