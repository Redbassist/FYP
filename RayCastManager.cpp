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

RayCastCallBack* RayCastManager::CastRay(b2Vec2 p1, b2Vec2 p2) { 
	callBack->Reset();
	world->RayCast(callBack, p1, p2);
	//HitReaction();
	return callBack;
}

void RayCastManager::HitReaction()
{
	if (callBack->objectName != NULL) {
		EffectManager::GetInstance()->PlayEffect(0, Vector2f(callBack->m_point.x * 30, callBack->m_point.y * 30));
	}
	if (callBack->objectName == "Door") {
		static_cast<Door*>(callBack->data)->OpenClose();
	}
}

