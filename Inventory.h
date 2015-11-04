#pragma once
#ifndef INVENTORY_H
#define INVENTORY_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Box2D\Box2D.h" 
#include "InputManager.h" 
#include "Item.h"

using namespace sf; 

class Inventory {
private:
	std::vector<Item*> inventory;
	Texture m_texture;
	Sprite m_sprite;
	RenderWindow* window;
	InputManager* inputManager;
	Vector2f m_pos;
	Vector2f offset;
	int invCols;
	int invRows;
	bool open;

public:
	Inventory(RenderWindow*, InputManager*);
	void LoadAssets();
	void AddItem(Item*);
	void DropItem(Vector2f);
	Item* RemoveItem(Vector2f);
	void Open();
	void Close();
	bool CheckOpen();
	void Draw();
	void DrawItems();
};

#endif
