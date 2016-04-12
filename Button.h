#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "stdafx.h"
#include "Globals.h" 

using namespace sf;
using namespace std;

class Button {
private:
	Texture m_texture;
	Sprite m_sprite;
	Vector2f m_pos;
	Vector2f offset;
	Vector2f size;
	bool hovering;
	float scaleX;
	float scaleY;
	Font font;
	Text text;
	GameState function;
	bool clicked = false;
public:
	Button(Vector2f, int, int, string&, GameState);
	void LoadAssets(string&);
	void Update();
	void Draw(); 
	void CheckHover();
	void CheckClick(); 
	void UpdateTransform();
};

#endif
