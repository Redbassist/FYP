#pragma once
#ifndef EFFECT_H
#define EFFECT_H

#include "stdafx.h"
#include "Animation.h"
#include "AnimatedSprite.h" 

class Effect {
public:
	Effect(Texture*, Vector2f, int frames, int columns, int rows, int individualWidth, int individualHeight, int speed);
	void Draw(sf::Time frameTime);
	bool Complete();
private:
	Animation anim;
	AnimatedSprite animSprite;
};

#endif
