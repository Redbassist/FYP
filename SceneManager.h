#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "stdafx.h"
#include "Globals.h"
#include "Button.h"
#include "Menu.h"
#include "World.h"

enum class GameState { SPLASHSCREEN, MENU, OPTIONS, GAME, GAMEOPTIONS, EXIT };

using namespace sf;
using namespace std;

class SceneManager {
private:
	Menu* currentMenu;
	World* gameWorld;
	GameState state;
	vector<Menu*> menus;

public:
	SceneManager(); 
	void CreateMenus();
	void Update();
	void Draw();
	void LastMenu();
	void NextMenu();
};

#endif  
