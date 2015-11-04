#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "Box2D\Box2D.h" 
#include "Player.h"
#include "Item.h"

class ContactListener : public b2ContactListener { 
public: 

	void BeginContact(b2Contact* contact)
	{ 
		void* fixAType = contact->GetFixtureA()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetUserData();

		if (fixAType == "Player" && fixBType == "Item"
			|| fixAType == "Item" && fixBType == "Player") {
			if (fixAType == "Player") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->TouchingItem(static_cast<Item*>(bodyUserData2));
			}
			else if (fixBType == "Player") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->TouchingItem(static_cast<Item*>(bodyUserData2));
			}
		}

	}

	void EndContact(b2Contact* contact) {
		void* fixAType = contact->GetFixtureA()->GetUserData();
		void* fixBType = contact->GetFixtureB()->GetUserData();


		if (fixAType == "Player" && fixBType == "Item"
			|| fixAType == "Item" && fixBType == "Player") {
			if (fixAType == "Player") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->NotTouchingItem();
			}
			else if (fixBType == "Player") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->NotTouchingItem();
			}
		}
	}
};
#endif