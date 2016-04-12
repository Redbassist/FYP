#include "Inventory.h"

Inventory::Inventory() {
	open = false;
	invCols = 4;
	invRows = 4;
	invSize = 16;
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

bool Inventory::AddItem(Item* item, Vector2f dropPos) {
	//this method will look through the slots in the inventory and find one that is free for the item
	Vector2f spritePos = m_sprite.getPosition();
	float height = m_sprite.getGlobalBounds().height;
	float width = m_sprite.getGlobalBounds().width;

	//checks if the item is dropped on the inventory (from container)
	if ((dropPos.x > spritePos.x && dropPos.x < spritePos.x + width &&
		dropPos.y > spritePos.y && dropPos.y < spritePos.y + height) || dropPos == Vector2f()) {

		int size = slots.size();

		for (int i = 0; i < size; i++) {
			if (item->GetSize() == 1 && !slots[i].full) {
				slots[i].item = item;
				slots[i].item->SlotNumber(i);
				slots[i].full = true;
				return true;
			}
			else if (item->GetSize() == 2 && !slots[i].full && !slots[i + 1].full && slots[i].col != invCols) {
				slots[i].item = item;
				slots[i].full = true;
				slots[i].item->SlotNumber(i);
				slots[i + 1].full = true;
				return true;
			}
			else if (item->GetSize() == 2) {
				bool loop = true;
				while (loop) {
					if (!slots[i].full && !slots[i + 1].full && slots[i].col != invCols) {
						slots[i].item = item;
						slots[i].full = true;
						slots[i].item->SlotNumber(i);
						slots[i + 1].full = true;
						loop = false;
					}
					i++;
				}
				return true;
			}
		}
	}
	return false;
}

Item* Inventory::DropItem(Item* item, Vector2f dropPos) {

	Vector2f spritePos = m_sprite.getPosition();
	float height = m_sprite.getGlobalBounds().height;
	float width = m_sprite.getGlobalBounds().width;

	if (dropPos.x < spritePos.x || dropPos.x > spritePos.x + width ||
		dropPos.y < spritePos.y || dropPos.y > spritePos.y + height) {

		int slot = item->GetSlot();

		if (item->GetSize() == 1) {
			slots[slot].full = false;
			slots[slot].item->ResetSlot();
			slots[slot].item = NULL;
		}
		else {
			slots[slot].full = false;
			slots[slot + 1].full = false;
			slots[slot].item->ResetSlot();
			slots[slot].item = NULL;
		}
		return item;
	}
	return NULL;
} 

int Inventory::SearchAmmo(ItemType t, int searchAmmo)
{ 
	int ammoFound = 0;
	ItemType searchType;

	switch (t) {
	case (ItemType::PISTOL) : 
		searchType = AMMOPISTOL;
		break;
	case (ItemType::RIFLE) : 
		searchType = AMMORIFLE;
		break;
	case (ItemType::SHOTGUN) : 
		searchType = AMMOSHOTGUN;
	}

	int size = slots.size();

	for (int i = 0; i < size; i++) {
		if (slots[i].item != NULL) {
			if (slots[i].item->GetType() == searchType) {
				pair<bool, int> temp = slots[i].item->RemoveAmmo(searchAmmo - ammoFound); 
 				ammoFound += temp.second;
				if (!temp.first) {
					slots[i].item->destroy = true;
					slots[i].item = NULL;
					slots[i].full = false;
				}
				if (ammoFound >= searchAmmo)
					break;
			}
		}
	}
	return ammoFound;
}

Item * Inventory::DropItem(Item * item, int slot)
{
	int slotNumber = slot;
	int size = slots.size();

	if (slots[slotNumber].item->GetSize() == 1) {
		slots[slotNumber].full = false;
		slots[slotNumber].item->SetHotbarSlot(-1);
		slots[slotNumber].item = NULL;
	}
	else {
		slots[slotNumber].full = false;
		slots[slotNumber + 1].full = false;
		slots[slotNumber].item = NULL;
	}

	return item;
}

Item * Inventory::DragItem(Vector2f clickPos)
{
	int size = slots.size();
	for (int i = 0; i < size; i++) {
		if (slots[i].full == true && slots[i].item != NULL) {
			if (slots[i].item->CheckSprite(clickPos)) {
				return slots[i].item;
			}
		}
	}
	return NULL;
}

void Inventory::UseItem(int slot)
{
	slots[slot].item->destroy = true;
	slots[slot].item = NULL;
	slots[slot].full = false;
}

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

std::vector<Item*> Inventory::GetItems()
{
	std::vector<Item*> items;

	int size = slots.size(); 
	for (int i = 0; i < size; i++) {
		if (slots[i].item != NULL && slots[i].full == true) {
			items.push_back(slots[i].item);
		}
			
	}

	return items;
}
