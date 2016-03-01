#pragma once 
#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H

#include "stdafx.h" 
#include "Globals.h"

using namespace std;
using namespace sf; 

class Effect;

class EffectManager {
public:
	EffectManager();
	static EffectManager* GetInstance();
	void LoadAssets();
	void Draw(); 
	void PlayEffect(int type, Vector2f pos);
	void RemoveEffects();
private:
	vector<Effect*> effects;
	Texture* m_smokeEffectTexture;
	Clock frameClock;
}; 

#endif