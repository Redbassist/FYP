#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <Box2D/Box2D.h>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"

#include "Player.h"  

using namespace std;
using namespace sf;

enum class GameState { MENU, OPTIONS, LOBBY, GAME, EXIT};

int main()
{
	/** Prepare the window */
	//int screenWidth = VideoMode::getDesktopMode().width;
	//int screenHeight = VideoMode::getDesktopMode().height;	
	int screenWidth = 1280;
	int screenHeight = 720;
	RenderWindow window(VideoMode(screenWidth, screenHeight, 32), "FYP");
	window.setFramerateLimit(60);
	View view = View(FloatRect(0, 0, screenWidth, screenHeight));
	view.zoom(1);
	window.setView(view);

	b2Vec2 Gravity(0.f, 0.f);
	b2World World(Gravity);
	 
	Player player = Player(&World, &window, Vector2f(20, 20));

	while (window.isOpen())
	{
		float32 timeStep = 1 / 20.0;      //the length of time passed to simulate (seconds)
		int32 velocityIterations = 8;   //how strongly to correct velocity
		int32 positionIterations = 3;   //how strongly to correct position

		World.Step(timeStep, velocityIterations, positionIterations); 

		player.Update();
		
		window.clear();
		player.Draw();
		window.display();

	}
}

