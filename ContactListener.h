#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "stdafx.h"
#include "Player.h"
#include "Item.h"
#include "Container.h"
#include "Stalker.h"
#include "Door.h"

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

		else if (fixAType == "Player" && fixBType == "Container"
			|| fixAType == "Container" && fixBType == "Player") {
			if (fixAType == "Player") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->TouchingContainer(static_cast<Container*>(bodyUserData2));
			}
			else if (fixBType == "Player") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->TouchingContainer(static_cast<Container*>(bodyUserData2));
			}
		}

		else if (fixAType == "Player" && fixBType == "Door"
			|| fixAType == "Door" && fixBType == "Player") {
			if (fixAType == "Player") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->TouchingDoor(static_cast<Door*>(bodyUserData2));
			}
			else if (fixBType == "Player") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->TouchingDoor(static_cast<Door*>(bodyUserData2));
			}
		} 
		else if (fixAType == "Player" && fixBType == "EnemyPunch"
			|| fixAType == "EnemyPunch" && fixBType == "Player") {
			if (fixAType == "Player") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				if (static_cast<Stalker*>(bodyUserData2)->HitPlayer()) {
					static_cast<Player*>(bodyUserData1)->TakeDamage(0);
				}
			}
			else if (fixBType == "Player") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				if (static_cast<Stalker*>(bodyUserData2)->HitPlayer()) {
					static_cast<Player*>(bodyUserData1)->TakeDamage(0);
				}
			}
		}
		else if (fixAType == "EnemyHit" && fixBType == "Punch"
			|| fixAType == "Punch" && fixBType == "EnemyHit") {
			if (fixAType == "EnemyHit") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				if (static_cast<Player*>(bodyUserData2)->doingPunchDamage) {
					static_cast<Player*>(bodyUserData2)->doingPunchDamage = false;
					static_cast<Enemy*>(bodyUserData1)->DropHealth(10);
				}
			}
			else if (fixBType == "EnemyHit") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				if (static_cast<Player*>(bodyUserData2)->doingPunchDamage) {
					static_cast<Player*>(bodyUserData2)->doingPunchDamage = false;
					static_cast<Enemy*>(bodyUserData1)->DropHealth(10);
				}
			}
		}
		else if (fixAType == "EnemyHit" && fixBType == "MeleeWeapon"
			|| fixAType == "MeleeWeapon" && fixBType == "EnemyHit") {
			if (fixAType == "EnemyHit") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				if (static_cast<Player*>(bodyUserData2)->doingMeleeDamage) {
					static_cast<Player*>(bodyUserData2)->doingMeleeDamage = false;
					static_cast<Enemy*>(bodyUserData1)->DropHealth(40);
				}
			}
			else if (fixBType == "EnemyHit") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				if (static_cast<Player*>(bodyUserData2)->doingMeleeDamage) {
					static_cast<Player*>(bodyUserData2)->doingMeleeDamage = false;
					static_cast<Enemy*>(bodyUserData1)->DropHealth(40);
				}
			}
		}
		else if (fixAType == "EnemyHit" && fixBType == "Door"
			|| fixAType == "Door" && fixBType == "EnemyHit") {
			if (fixAType == "Door") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Door*>(bodyUserData1)->Open();
			}
			else if (fixBType == "Door") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Door*>(bodyUserData1)->Open();
			}
		}
		else if (fixAType == "Punch" && fixBType == "Door"
			|| fixAType == "Door" && fixBType == "Punch") {
			if (fixAType == "Door") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				if (static_cast<Player*>(bodyUserData2)->doingPunchDamage) 
				static_cast<Door*>(bodyUserData1)->Knock();
			}
			else if (fixBType == "Door") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				if (static_cast<Player*>(bodyUserData2)->doingPunchDamage) 
					static_cast<Door*>(bodyUserData1)->Knock();
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
				static_cast<Player*>(bodyUserData1)->NotTouchingItem(static_cast<Item*>(bodyUserData2));
			}
			else if (fixBType == "Player") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->NotTouchingItem(static_cast<Item*>(bodyUserData2));
			}
		}

		else if (fixAType == "Player" && fixBType == "Container"
			|| fixAType == "Container" && fixBType == "Player") {
			if (fixAType == "Player") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->NotTouchingContainer();
				static_cast<Container*>(bodyUserData2)->Close();
			}
			else if (fixBType == "Player") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->NotTouchingContainer();
				static_cast<Container*>(bodyUserData2)->Close();
			}
		}

		else if (fixAType == "Player" && fixBType == "Door"
			|| fixAType == "Door" && fixBType == "Player") {
			if (fixAType == "Player") {
				void* bodyUserData1 = contact->GetFixtureA()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->NotTouchingDoor(); 
			}
			else if (fixBType == "Player") {
				void* bodyUserData1 = contact->GetFixtureB()->GetBody()->GetUserData();
				void* bodyUserData2 = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Player*>(bodyUserData1)->NotTouchingDoor(); 
			}
		}  
	}
};
#endif