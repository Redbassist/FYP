#include "RayCastManager.h"

static bool instanceFlag = false;
static RayCastManager* instance = NULL;

RayCastManager* RayCastManager::GetInstance() {
	if (!instanceFlag) {
		instance = new RayCastManager();
		instanceFlag = true;
	}
	return instance;
}

RayCastManager::RayCastManager()
{
	callBack = new RayCastCallBack();
}

void RayCastManager::CastRay(b2Vec2 p1, b2Vec2 p2) {
	callBack->Reset();
	world->RayCast(callBack, p1, p2);
	HitReaction();
}

void RayCastManager::HitReaction()
{
	if (callBack->objectName != NULL) {
		int poop = 123;
	}
}

