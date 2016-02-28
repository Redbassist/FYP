#pragma once
#ifndef RAYCASTMANAGER_H
#define RAYCASTMANAGER_H

#include "stdafx.h"
#include "RayCastCallback.h"

class RayCastManager {
private:
	RayCastCallBack* callBack; 
public: 
	static RayCastManager* GetInstance();
	RayCastManager();
	void CastRay(b2Vec2 p1, b2Vec2 p2);
	void HitReaction();
};

#endif#pragma once
