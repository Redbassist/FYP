#pragma once
#ifndef SCENECHANGER_H
#define SCENECHANGER_H

#include "stdafx.h"
#include "Globals.h" 

using namespace sf;
using namespace std; 

enum class GameState { SPLASHSCREEN, MENU, OPTIONS, GAME, NEWGAME, CONTINUEGAME, GAMEMENU, GAMEOPTIONS, EXIT };

class SceneChanger {
private: 
	GameState currentState;
	GameState previousState;
public:
	SceneChanger();
	static SceneChanger* GetInstance();
	void ChangeScene(GameState);
	bool SceneChanging();
	GameState CurrentScene();
};

#endif
#pragma once
