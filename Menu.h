#pragma once
#ifndef MENU_H
#define MENU_H

#include "stdafx.h"
#include "Globals.h"
#include "Button.h"
#include "Slider.h"

using namespace sf;
using namespace std;

class Menu {
private:
	Texture m_texture;
	Sprite m_sprite;
	vector<Button*> buttons;
	vector<Slider*> sliders;

public:
	Menu(string&);
	void LoadAssets(string&);
	void AddButton(Button*);
	void AddSlider(Slider*);
	void Update();
	void Draw(); 
	void UpdateTransform();
};

#endif 
