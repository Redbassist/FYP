#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "stdafx.h"
#include "Globals.h"

using namespace sf;

const static float SCALE = 30.f;

enum ItemType { 
	FOOD1, FOOD2, FOOD3,
	WATER1, WATER2, 
	AXE, BAT,
	AMMOPISTOL, AMMOSHOTGUN, AMMORIFLE,
	PISTOL, SHOTGUN, RIFLE,
	MAP
};

static const std::string ItemTypeStrings[] =
{ 
	"FOOD1", "FOOD2", "FOOD3",
	"WATER1", "WATER2",
	"AXE", "BAT",
	"AMMOPISTOL", "AMMOSHOTGUN", "AMMORIFLE",
	"PISTOL", "SHOTGUN", "RIFLE",
	"MAP"
};

class Item {
private:
	Texture m_texture;
	Sprite m_sprite; 
	b2Body* body; 
	b2FixtureDef fixtureDef;
	ItemType type;
	Vector2f m_pos;
	bool onGround;
	bool bodyCreated;
	int size;
	int amountAmmo = 0;
	int maxAmmo = 0;
	bool dragged;
	int slot;
	int hotbarSlot;

public:
	bool inHotBar = false;
	bool destroy = false;
	~Item();
	Item(ItemType, int);
	Item(ItemType, int, int);
	Item(ItemType, int, bool, Vector2f); 
	void LoadAssets(); 
	void LoadSprites(std::string type);
	void SlotNumber(int);
	void SetHotbarSlot(int);
	int GetHotbarSlot();
	void ResetSlot();
	int GetSlot();
	int GetSize();
	pair<bool, int> RemoveAmmo(int);
	int MissingAmmo() {
		return maxAmmo - amountAmmo;
	}
	void AddAmmo(int ammo) {
		amountAmmo += ammo;
	}
	void Draw();
	void DrawInInventory(Vector2f, FloatRect, int, int);
	void DrawInContainer(Vector2f, FloatRect, int, int);
	void DrawInHotbar(Vector2f);
	void DrawDragged();
	void PickedUp();
	bool CheckSprite(Vector2f);
	void Dropped(Vector2f);
	std::string getTextForEnum(int enumVal);
	void createBox2dBody();
	int GetAmmo() { return amountAmmo; }
	ItemType GetType() { return type; }
	string GetTypeString() { return ItemTypeStrings[type]; }
};

#endif