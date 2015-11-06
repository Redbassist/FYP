#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Box2D\Box2D.h"  
#include "Item.h"
#include <math.h>

using namespace sf;

struct ContainerSlot {
	Item* item;
	int number;
	int row;
	int col;
	bool full;
};

class Container {
private:
	std::vector<Item*> contains;
	Texture m_texture;
	Sprite m_sprite;
	Texture m_shapeTexture;
	Sprite m_shapeSprite;
	RenderWindow* window; 
	b2World* world;
	b2Body* body;
	b2FixtureDef fixtureDef;
	Vector2f m_pos;
	float rotation;
	Vector2f offset;
	int invCols;
	int invRows;
	int invSize;
	bool open;
	std::vector<ContainerSlot> slots; 
	std::vector<Item*>* items;

public:
	Container(b2World*, RenderWindow*, Vector2f, float, std::vector<Item*>*);
	void LoadAssets();
	void SetupSlots();
	void GenerateItems();
	void AddItem(Item*);
	Item* TakeItem(Vector2f);
	void Open();
	void Close();
	bool CheckOpen();
	void Draw();
	void DrawItems();
	void createBox2dBody();
};

#endif
