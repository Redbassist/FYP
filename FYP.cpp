#include "stdafx.h"
#include <iostream>
#include <stdlib.h>     
#include <time.h>       
#include <math.h>
#include <Box2D/Box2D.h>
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "ContactListener.h"

enum class GameState { MENU, OPTIONS, LOBBY, GAME, EXIT };

#include "InputManager.h"
#include "World.h"
#include "Player.h" 
#include "Item.h" 

using namespace std;
using namespace sf;

int main()
{
	srand(time(NULL));

	/** Prepare the window */
	//int screenWidth = VideoMode::getDesktopMode().width;
	//int screenHeight = VideoMode::getDesktopMode().height;	
	int screenWidth = 1280;
	int screenHeight = 720;
	RenderWindow window(VideoMode(screenWidth, screenHeight, 32), "FYP");
	window.setFramerateLimit(60);
	View view = View(FloatRect(0, 0, screenWidth, screenHeight));
	view.zoom(0.7);
	window.setView(view);

	b2Vec2 Gravity(0.f, 0.f);
	b2World world(Gravity); 
	world.SetAllowSleeping(false);
	ContactListener contactListener = ContactListener();
	world.SetContactListener(&contactListener);

	InputManager inputManager = InputManager(&window);

	World* gameWorld = new World(&window, &world, &inputManager);

	while (window.isOpen())
	{
		float32 timeStep = 1 / 20.0;      //the length of time passed to simulate (seconds)
		int32 velocityIterations = 8;   //how strongly to correct velocity
		int32 positionIterations = 3;   //how strongly to correct position

		world.Step(timeStep, velocityIterations, positionIterations);

		//checking for bodies that need to be destroyed (Using their user data)
		//Consider threading this operation 
		b2Body* bodyList = world.GetBodyList();

		for (; bodyList != NULL; bodyList = bodyList->GetNext()) {
			if (bodyList->GetFixtureList()->GetUserData() == "Destroy") {
				world.DestroyBody(bodyList);
				break;
			}
		}

		inputManager.Update(); 
		gameWorld->Update();
		
		window.clear(); 
		gameWorld->Draw();
		window.display();
	}
}

