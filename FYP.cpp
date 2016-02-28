#include "stdafx.h"
#include "ContactListener.h" 
#include "Globals.h"
#include "SceneManager.h"
#include "SFMLDebugDraw.h"

using namespace std;
using namespace sf;

int main()
{
	srand(time(NULL));
	std::chrono::steady_clock myClock;
	const auto timePerTick = std::chrono::milliseconds(16);
	auto timeOfLastTick = myClock.now();

	/** Prepare the window */
	//int screenWidth = VideoMode::getDesktopMode().width;
	//int screenHeight = VideoMode::getDesktopMode().height;	

	int screenWidth = 1280;
	int screenHeight = 720;
	window = new RenderWindow(VideoMode(screenWidth, screenHeight, 32), "FYP"); 
	View view = View(FloatRect(0, 0, screenWidth, screenHeight));
	window->setView(view);  

	b2Vec2 Gravity(0.f, 0.f);
	world = new b2World(Gravity); 
	world->SetAllowSleeping(false);
	ContactListener contactListener = ContactListener();
	world->SetContactListener(&contactListener);

	SFMLDebugDraw debugDraw(*window);
	world->SetDebugDraw(&debugDraw);
	debugDraw.SetFlags(b2Draw::e_shapeBit);
	//setting up the managers
	InputManager::GetInstance();
	AudioManager::GetInstance(); 
	SceneChanger::GetInstance();
	SettingsManager::GetInstance();
	
	SceneManager* sceneManager = new SceneManager();

	while (window->isOpen())
	{
		while (myClock.now() - timeOfLastTick >= timePerTick) {
			timeOfLastTick = myClock.now();

			float32 timeStep = 1 / 20.0;      //the length of time passed to simulate (seconds)
			int32 velocityIterations = 200;   //how strongly to correct velocity
			int32 positionIterations = 100;   //how strongly to correct position

			world->Step(timeStep, velocityIterations, positionIterations);

			//checking for bodies that need to be destroyed (Using their user data)
			//Consider threading this operation 
			b2Body* bodyList = world->GetBodyList();
			for (; bodyList != NULL; bodyList = bodyList->GetNext()) {
				if (bodyList->GetFixtureList()->GetUserData() == "Destroy") {
					world->DestroyBody(bodyList);
					break;
				}
			}

			InputManager::GetInstance()->Update();
			AudioManager::GetInstance()->update(); 
			sceneManager->Update();
		}
		window->clear();
		sceneManager->Draw();
		//world->DrawDebugData();
		window->display();
	}
}

