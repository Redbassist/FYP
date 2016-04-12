#include "RayCastManager.h"
#include "Stalker.h"

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
	bulletRayCastCallBack = new BulletRayCastCallback();
}

RayCastCallBack* RayCastManager::CastRay(b2Vec2 p1, b2Vec2 p2) { 
	callBack->Reset();
	world->RayCast(callBack, p1, p2);
	//HitReaction();
	return callBack;
}

BulletRayCastCallback * RayCastManager::CastBulletRay(b2Vec2 p1, b2Vec2 p2)
{
	bulletRayCastCallBack->Reset();
	world->RayCast(bulletRayCastCallBack, p1, p2);
	HitReaction();
	return bulletRayCastCallBack;
}

void RayCastManager::HitReaction()
{
	if (bulletRayCastCallBack->objectName != NULL) {
		EffectManager::GetInstance()->PlayEffect(0, Vector2f(bulletRayCastCallBack->m_point.x * 30, bulletRayCastCallBack->m_point.y * 30));
	}
	if (bulletRayCastCallBack->objectName == "EnemyHit") {
		static_cast<Stalker*>(bulletRayCastCallBack->data)->DropHealth(20);
	}
}

