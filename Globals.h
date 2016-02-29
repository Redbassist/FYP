#pragma once
#include "stdafx.h"

extern b2World* world;
extern sf::RenderWindow* window; 
#define RADTODEG (180.0 / b2_pi)
#define DEGTORAD (b2_pi / 180)

enum _entityCategory {
	PLAYER = 0x0004,
	ITEM = 0x0008,
	CONTAINER = 0x0016,
	WALL = 0x0020,
	DOOR = 0x0024,
	MELEE = 0x0028,
	PUNCH = 0x0032,
};