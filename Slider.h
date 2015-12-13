#pragma once
#ifndef SLIDER_H
#define SLIDER_H

#include "stdafx.h"
#include "Globals.h" 

using namespace sf;
using namespace std;

class Slider {
private:
	Texture m_barTexture;
	Sprite m_barSprite;
	Texture m_slideTexture;
	Sprite m_slideSprite;
	Vector2f m_barPos;
	Vector2f offset;
	float barLength;
	Font font;
	Text text;
	float value;
	Setting setting;
public:
	Slider(Vector2f, int, string&, Setting);
	void LoadAssets(string&);
	void Update();
	void Draw(); 
	void MoveSlide();
	void UpdateTransform();
};

#endif
