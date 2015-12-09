#pragma once
#ifndef MENU_H
#define MENU_H

#include "stdafx.h"
#include "Globals.h"
#include "Button.h"

using namespace sf;
using namespace std;

class Menu {
private:
	Texture m_texture;
	Sprite m_sprite;
	vector<Button*> buttons; 

public:
	Menu(string&);
	void LoadAssets(string&);
	void AddButton(Button*);
	void Update();
	void Draw(); 
};

#endif 
