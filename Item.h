#pragma once
#ifndef ITEM_H
#define ITEM_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Box2D\Box2D.h" 

using namespace sf;
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
	RenderWindow* window;
	ItemType type;
	Vector2f m_pos;
	bool onGround;

public:
	Item(b2World*, RenderWindow*, ItemType);
	void LoadAssets(); 
	void LoadSprites(std::string type);
	void Draw();
	std::string getTextForEnum(int enumVal);
};

#endif