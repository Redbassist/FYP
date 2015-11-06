#pragma once
#ifndef WALL_H
#define WALL_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Box2D\Box2D.h" 

using namespace sf;

class Wall {
private:
	const float SCALE = 30.f;
	Texture m_texture;
	Sprite m_sprite;
	b2World* world;
	b2Body* body;
	b2FixtureDef fixtureDef;
	RenderWindow* window; 
	Vector2f m_pos; 
	Vector2f size;

public:
	Wall(b2World*, RenderWindow*, Vector2f, Vector2f); 
	void LoadAssets();  
	void Draw();  
	void createBox2dBody();
};

#endif