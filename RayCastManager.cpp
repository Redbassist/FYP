#include "RayCastManager.h"
#include "Stalker.h"
#include "Player.h"

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
	badbulletRayCastCallBack = new BadBulletRayCastCallback();
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

BadBulletRayCastCallback * RayCastManager::CastBadBulletRay(b2Vec2 p1, b2Vec2 p2)
{
	badbulletRayCastCallBack->Reset();
	world->RayCast(badbulletRayCastCallBack, p1, p2);
	HitReaction();
	return badbulletRayCastCallBack;
}

void RayCastManager::HitReaction()
{
	if (bulletRayCastCallBack->objectName == "EnemyHit") {
		EffectManager::GetInstance()->PlayEffect(2, Vector2f(bulletRayCastCallBack->m_point.x * 30, bulletRayCastCallBack->m_point.y * 30));
		static_cast<Stalker*>(bulletRayCastCallBack->data)->DropHealth(0);
	}
	else if (bulletRayCastCallBack->objectName != NULL) {
		EffectManager::GetInstance()->PlayEffect(0, Vector2f(bulletRayCastCallBack->m_point.x * 30, bulletRayCastCallBack->m_point.y * 30));
	}

	if (badbulletRayCastCallBack->objectName == "Player") {
		EffectManager::GetInstance()->PlayEffect(1, Vector2f(badbulletRayCastCallBack->m_point.x * 30, badbulletRayCastCallBack->m_point.y * 30));
		static_cast<Player*>(badbulletRayCastCallBack->data)->TakeDamage(3);
	}

	else if (badbulletRayCastCallBack->objectName != NULL) {
		EffectManager::GetInstance()->PlayEffect(0, Vector2f(badbulletRayCastCallBack->m_point.x * 30, badbulletRayCastCallBack->m_point.y * 30));
	}

	bulletRayCastCallBack->Reset();
	badbulletRayCastCallBack->Reset();
}

