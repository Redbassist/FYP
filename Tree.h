#pragma once 
#ifndef TREE_H
#define TREE_H

#include "stdafx.h"
#include "Globals.h"

using namespace sf;

class Tree {
private:
	const float SCALE = 30.f;
	Texture m_texture;
	Sprite m_sprite;
	Texture m_trunktexture;
	Sprite m_trunksprite;
	b2Body* body;
	b2FixtureDef fixtureDef;
	Vector2f m_pos;
	float rotation; 
	float maxDistance = 500;

public:
	~Tree();
	Tree(Vector2f);
	void LoadAssets();
	void Draw();
	void FadeOut(Vector2f pos);
	void createBox2dBody();
};

#endif
