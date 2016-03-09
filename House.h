#pragma once
#ifndef HOUSE_H
#define HOUSE_H

#include "stdafx.h"
#include "Globals.h"
#include "Wall.h"
#include "Door.h"
#include "Container.h"
#include "FillerObject.h"

using namespace sf;

class House {
private:
	const float SCALE = 30.f;
	Texture m_texture;
	Sprite m_sprite; 
	Vector2f m_pos; 
	std::vector<Wall*> walls;
	std::vector<Item*>* items;
	std::vector<Container*> containers;
	std::vector<Door*> doors;
	std::vector<FillerObject*> fillers;
	int type;

public:
	~House();
	House(Vector2f, std::vector<Item*>*, int);
	void LoadAssets();
	void CreateWalls();
	void Draw();  
};

#endif