#pragma once
#ifndef HOTBAR_H
#define HOTBAR_H

#include "stdafx.h"
#include "Item.h"
#include "Globals.h"

struct HotbarSlot {
	Item* item = NULL; 
	bool selected = false;
};

class Hotbar {
private:
	Texture m_texture;
	Texture m_textureSelected;
	Sprite m_sprite;
	Sprite m_spriteSelected;
	std::vector<HotbarSlot> slots;
	int numberSlots; //number of slots on the hotbar
	float xOffset; //Offset for the drawing of slots
public:
	Hotbar();
	void LoadAssets();
	void CreateSlots();
	void Draw();
	bool AddItem(Vector2f, Item*);
	int CheckSprite(Vector2f);
	void RemoveItem(int slot);
	Item* SelectItem(int i);
};

#endif
