#pragma once
#ifndef EFFECTMANAGER_H
#define EFFECTMANAGER_H

#include "stdafx.h"
#include "Animation.h"
#include "AnimatedSprite.h" 
#include "Effect.h"
#include "Globals.h"

class EffectManager {
public:
	static EffectManager* GetInstance();
	EffectManager();
	void LoadAssets();
	void Draw(); 
	void PlayEffect(EffectType type);
	void RemoveEffects();
private:
	vector<Effect*> effects;
};

#endif
#pragma once
