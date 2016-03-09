#pragma once
#ifndef FILLEROBJECT_H
#define FILLEROBJECT_H

#include "stdafx.h"
#include "Globals.h"

using namespace sf;

class FillerObject {
private:
	const float SCALE = 30.f;
	Texture m_texture;
	Sprite m_sprite;
	b2Body* body;
	b2FixtureDef fixtureDef;
	Vector2f m_pos;
	float rotation;  
	std::string type;

public:
	~FillerObject();
	FillerObject(Vector2f, float, std::string);
	void LoadAssets();
	void Draw(); 
	void createBox2dBody();
};

#endif#pragma once
