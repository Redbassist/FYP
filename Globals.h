#pragma once
#include "stdafx.h"

extern b2World* world; 
extern sf::RenderStates* lightRenderStates;
extern sf::Shader* unshadowShader;
extern sf::Shader* lightOverShapeShader;
extern sf::Shader* normalsShader;
extern sf::RenderWindow* window; 
extern tmx::MapLoader* ml;
extern int playerID;

extern std::string serverIP;
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
	FILLER = 0x0036,
	ENEMY = 0X0040,
	ENEMYPUNCH = 0X0044,
	ENEMYHIT = 0X0048,
};