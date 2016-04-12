#pragma once
#ifndef BULLETRAYCASTCALLBACK_H
#define BULLETRAYCASTCALLBACK_H

#include "stdafx.h"

class BulletRayCastCallback : public b2RayCastCallback {
public:
	BulletRayCastCallback(RayCastCallBack* rc = NULL)
	{
		if (rc == NULL) {
			distance = 10000;
		}
		else {
			distance = rc->distance;
			m_point = rc->m_point;
			m_normal = rc->m_normal;
			data = rc->data;
			objectName = rc->objectName;
		}
	}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
		void* d = fixture->GetBody()->GetUserData();
		void* userData = fixture->GetUserData();

		if (distance > fraction && (userData != "MeleeWeapon" && userData != "Punch" && userData != "EnemyPunch" && userData != "Enemy")) {
			distance = fraction;
			m_point = point;
			m_normal = normal;
			data = d;
			objectName = userData;
			return 1;
		}
		return 1;
	}

	void Reset() {
		distance = 10000;
		m_point = b2Vec2();
		m_normal = b2Vec2();
		data = NULL;
		objectName = NULL;
	}

	float32 distance;
	b2Vec2 m_point;
	b2Vec2 m_normal;
	void* data;
	void* objectName;
};

#endif
