#pragma once
#ifndef RAYCASTCALLBACK_H
#define RAYCASTCALLBACK_H

#include "stdafx.h"

class RayCastCallBack : public b2RayCastCallback {
public:
	RayCastCallBack()
	{
		distance = 10000;
	}

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) {
		void* d = fixture->GetBody()->GetUserData();
		void* userData = fixture->GetUserData();

		if (distance > fraction) {
			distance = fraction;
			m_point = point;
			m_normal = normal;
			data = d;
			objectName = userData;
			return 1;
		}
		return 0;
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