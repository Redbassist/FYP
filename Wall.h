#pragma once
#ifndef WALL_H
#define WALL_H

#include "stdafx.h"
#include "Globals.h"

using namespace sf;

class Wall {
private:
	const float SCALE = 30.f;
	Texture m_texture;
	Sprite m_sprite; 
	b2Body* body;
	b2FixtureDef fixtureDef;
	RenderWindow* window; 
	Vector2f m_pos; 
	Vector2f size;

public:
	Wall(RenderWindow*, Vector2f, Vector2f); 
	void LoadAssets();  
	void Draw();  
	void createBox2dBody();
};

#endif