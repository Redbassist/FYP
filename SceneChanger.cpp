#include "SceneChanger.h"

static bool instanceFlag = false;
static SceneChanger* instance = NULL;

SceneChanger* SceneChanger::GetInstance() {
	if (!instanceFlag) {
		instance = new SceneChanger();
		instanceFlag = true;
	}
	return instance;
}

void SceneChanger::ChangeScene(GameState sceneChange)
{
	currentState = sceneChange;
}

SceneChanger::SceneChanger()
{
	currentState = GameState::SPLASHSCREEN;
	previousState = GameState::SPLASHSCREEN;
}  

bool SceneChanger::SceneChanging()
{
	if (previousState != currentState) {
		previousState = currentState;
		return true;
	}
	return false;
}

GameState SceneChanger::CurrentScene()
{
	return currentState;
}
