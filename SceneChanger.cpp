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

SceneChanger::SceneChanger()
{
	next = false;
	previous = false;
}

void SceneChanger::NextScene()
{
	next = true;
}

void SceneChanger::PreviousScene()
{
	previous = true;
}

int SceneChanger::SceneChanging()
{
	if (next) {
		next = false;
		return 1;
	}
	else if (previous) {
		previous = false;
		return 2;
	}
	else
		return 0;
}
