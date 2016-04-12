#pragma once
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "stdafx.h"
#include "Globals.h"
#include "Button.h"
#include "Menu.h"
#include "World.h"   

using namespace sf;
using namespace std;
//map for holding the menus
typedef std::map<GameState, Menu*> MenuMap;

class SceneManager {
private:
	Menu* currentMenu;
	World* gameWorld;
	GameState state; 
	MenuMap menusMap;
	bool loadGame = false;

public:
	SceneManager(); 
	void CreateMenus();
	void Update();
	void Draw(); 
	void ChangeScene();
};

#endif  
