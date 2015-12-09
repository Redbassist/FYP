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
	std::pair<int, Menu*> currentMenu;
	World* gameWorld;
	GameState state;
	vector<std::pair<int, Menu*>> menus;

public:
	SceneManager(); 
	void CreateMenus();
	void Update();
	void Draw(); 
	void ChangeScene();
};

#endif  
