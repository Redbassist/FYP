#pragma once
#ifndef DOOR_H
#define DOOR_H

#include "stdafx.h"
#include "Globals.h"

using namespace sf;

class Door {
private:
	const float SCALE = 30.f;
	Texture m_texture;
	Sprite m_sprite; 
	b2Body* body;
	b2FixtureDef fixtureDef;
	RenderWindow* window;
	Vector2f m_pos;
	float rotation;
	bool open;

public:
	Door(RenderWindow*, Vector2f, float);
	void LoadAssets();
	void Draw();
	void OpenClose();
	void createBox2dBody();
};

#endif