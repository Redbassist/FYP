#pragma once
#ifndef RAYCASTMANAGER_H
#define RAYCASTMANAGER_H

#include "stdafx.h"
#include "RayCastCallback.h"
#include "BulletRayCastCallback.h"
#include "BadBulletRayCastCallback.h"
#include "Door.h"  

class Stalker;
class Player;

class RayCastManager {
private:
	RayCastCallBack* callBack;
	BulletRayCastCallback* bulletRayCastCallBack;
	BadBulletRayCastCallback* badbulletRayCastCallBack;
public: 
	static RayCastManager* GetInstance();
	RayCastManager();
	RayCastCallBack* CastRay(b2Vec2 p1, b2Vec2 p2);
	BulletRayCastCallback* CastBulletRay(b2Vec2 p1, b2Vec2 p2);
	BadBulletRayCastCallback* CastBadBulletRay(b2Vec2 p1, b2Vec2 p2);
	void HitReaction(); 
};

#endif
