#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include "stdafx.h"
#include "Item.h"

using namespace sf; 

struct Slot {
	Item* item;
	int number;
	int row;
	int col;
	bool full;
};

class Inventory {
private:
	std::vector<Item*> inventory;
	Texture m_texture;
	Sprite m_sprite; 
	Vector2f m_pos;
	Vector2f offset;
	int invCols;
	int invRows;
	int invSize;
	bool open;
	std::vector<Slot> slots;

public:
	Inventory();
	void LoadAssets();
	void SetupSlots();
	void AddItem(Item*); 
	Item* DropItem(Vector2f, Vector2f);
	Item* DragItem(Vector2f);
	void Open();
	void Close();
	bool CheckOpen();
	void Draw();
	void DrawItems();
};

#endif
