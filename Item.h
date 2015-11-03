#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Box2D\Box2D.h" 

using namespace sf;

static const float SCALE = 30.f;

enum ItemType { 
	FOOD1, FOOD2, FOOD3,
	WATER1, WATER2, 
	AMMOPISTOL, AMMOSHOTGUN, AMMORIFLE,
	PISTOL, SHOTGUN, RIFLE,
	MAP
};

static const std::string ItemTypeStrings[] =
{ 
	"FOOD1", "FOOD2", "FOOD3",
	"WATER1", "WATER2",
	"AMMOPISTOL", "AMMOSHOTGUN", "AMMORIFLE",
	"PISTOL", "SHOTGUN", "RIFLE",
	"MAP"
};

class Item {
private:
	Texture m_texture;
	Sprite m_sprite;
	b2World* world;
	b2Body* body; 
	b2FixtureDef fixtureDef;
	RenderWindow* window;
	ItemType type;
	Vector2f m_pos;
	bool onGround;
	bool bodyCreated;
	int size;

public:
	Item(b2World*, RenderWindow*, ItemType, int);
	void LoadAssets(); 
	void LoadSprites(std::string type);
	int GetSize();
	void Draw();
	void DrawInInventory(Vector2f, FloatRect, int, int);
	std::string getTextForEnum(int enumVal);
	void Item::createBox2dBody();
};

#endif