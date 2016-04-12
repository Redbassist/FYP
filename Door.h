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
	Vector2f m_pos;
	float rotation;
	bool open;
	ltbl::LightShape* lightBlocker;
	int type;

public:
	Door(Vector2f, float, int);
	void LoadAssets();
	void Draw();
	void OpenClose();
	void Open();
	void Knock();
	void createBox2dBody();
	Vector2f GetOrigin();
};

#endif