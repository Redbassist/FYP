#pragma once
#ifndef DOOR_H
#define DOOR_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Box2D\Box2D.h" 

using namespace sf;

class Door {
private:
	const float SCALE = 30.f;
	Texture m_texture;
	Sprite m_sprite;
	b2World* world;
	b2Body* body;
	b2FixtureDef fixtureDef;
	RenderWindow* window;
	Vector2f m_pos;
	float rotation;
	bool open;

public:
	Door(b2World*, RenderWindow*, Vector2f, float);
	void LoadAssets();
	void Draw();
	void OpenClose();
	void createBox2dBody();
};

#endif