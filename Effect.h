#pragma once 
#ifndef Effect_H
#define Effect_H

#include "Globals.h"
#include <vector>
#include "Animation.h"
#include "AnimatedSprite.h"

using namespace std;
using namespace sf;

class Effect {
public:
	Effect();
	Effect(Texture* t, Vector2f pos, int frames, int columns, int rows, int individualWidth, int individualHeight, float speed, float scale);
	void DrawEffect(sf::Time frameTime);
	bool IsComplete();
private:
	Animation animation;
	AnimatedSprite animatedSprite;
};

#endif 