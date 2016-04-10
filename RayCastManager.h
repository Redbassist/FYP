#pragma once
#ifndef RAYCASTMANAGER_H
#define RAYCASTMANAGER_H

#include "stdafx.h"
#include "RayCastCallback.h"
#include "BulletRayCastCallback.h"
#include "Door.h"  

class Stalker;

class RayCastManager {
private:
	RayCastCallBack* callBack;
	BulletRayCastCallback* bulletRayCastCallBack;
public: 
	static RayCastManager* GetInstance();
	RayCastManager();
	RayCastCallBack* RayCastManager::CastRay(b2Vec2 p1, b2Vec2 p2);
	BulletRayCastCallback* RayCastManager::CastBulletRay(b2Vec2 p1, b2Vec2 p2);
	void HitReaction(); 
};

#endif
