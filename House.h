#pragma once
#ifndef HOUSE_H
#define HOUSE_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Box2D\Box2D.h" 
#include "Wall.h"
#include "Container.h"

using namespace sf;

class House {
private:
	const float SCALE = 30.f;
	Texture m_texture;
	Sprite m_sprite;
	b2World* world; 
	RenderWindow* window;
	Vector2f m_pos; 
	std::vector<Wall*> walls;
	std::vector<Item*>* items;
	std::vector<Container*> containers;

public:
	House(b2World*, RenderWindow*, Vector2f, std::vector<Item*>*);
	void LoadAssets();
	void CreateWalls();
	void Draw(); 
};

#endif