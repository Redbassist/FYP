#pragma once
#ifndef SCENECHANGER_H
#define SCENECHANGER_H

#include "stdafx.h"
#include "Globals.h" 

using namespace sf;
using namespace std;

class SceneChanger {
private: 
	bool next;
	bool previous;
public:
	SceneChanger();
	static SceneChanger* GetInstance();
	void NextScene();
	void PreviousScene();
	int SceneChanging();
};

#endif
#pragma once
