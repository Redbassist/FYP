#pragma once
#ifndef Player_H
#define Player_H

#include "stdafx.h"
#include "Globals.h"
#include "Animation.h"
#include "AnimatedSprite.h" 
#include "Inventory.h"
#include "Container.h" 
#include "Door.h" 

using namespace sf;

struct keyActions {
	bool walkLeft = false;
	bool walkRight = false;
	bool walkUp = false;
	bool walkDown = false;
	bool sprint = false;
	bool interact = false;
	bool drop = false;
	bool take = false;
	bool inventory = false;
	bool drag = false;
	bool swing = false;
	bool punch = false;
	bool fire = false;
};

class Player {
private:
	//player stats
	float fullHealth;
	float health;
	float hunger;
	float thirst;

	keyActions actions;
	Texture m_AnimationLegsTexture;
	Texture m_AnimationTopTexture;
	Texture m_SwingAxeRightTexture;
	Texture m_SwingAxeLeftTexture;
	Texture m_PunchRightTexture;
	Texture m_PunchLeftTexture;
	Texture m_pistolTexture;
	Animation legsIdle;
	Animation legsMoving;
	Animation playerTopIdle;
	Animation playerTopMoving;
	Animation swingAxeRight;
	Animation swingAxeLeft;
	Animation punchLeft;
	Animation punchRight;
	Animation pistolShoot;
	Animation* currentLegAnimation;
	Animation* currentTopAnimation;
	AnimatedSprite animatedLegSprite;
	AnimatedSprite animatedTopSprite;
	AnimatedSprite animatedSwingAxeRight;
	AnimatedSprite animatedSwingAxeLeft;
	AnimatedSprite animatedPunchRight;
	AnimatedSprite animatedPunchLeft;

	//watch variables
	Texture watchTexture;
	Sprite watchSprite;
	Texture watchBGTexture;
	Sprite watchBGSprite;
	Texture heartBeatTexture;
	Sprite heartBeatSprite;
	Font watchFont;
	Text heartRateText;
	Text currentTime;

	float heartRate;
	float heartBeatX;
	int currentHours;
	int currentMinutes;
	int nextMinute;

	b2Body* body;
	b2FixtureDef fixtureDef;
	b2Body* punchbody;
	b2FixtureDef punchfixtureDef;
	b2Body* meleebody;
	b2Joint* meleeJoint;
	b2FixtureDef meleefixtureDef;
	b2RevoluteJointDef meleeJointDef;

	bool punch = false;
	int punchDirection = 0;
	int punchDistance = 0;
	int maxPunchDistance = 40;

	bool melee;
	int swingDirection = 0; //0 is right, 1 is left
	float meleeAngle = 0;
	int swingSpeed;

	bool pistol;
	int shoottime = 0;
	int shootspeed;  

	Container* touchedContainer;
	std::vector<Item*> touchedItems;
	Door* touchedDoor;

	Item* dragInventoryItem;
	Item* dragContainerItem;

	Vector2f m_pos;
	float orientation;
	float speed;
	Inventory* inventory;

	sf::Clock frameClock;
	b2RayCastInput gunRay;

public:
	Player(Vector2f);
	void LoadAssets();
	void EasyLoadAssetsAnimation(Texture* t, string file, Animation* anim, int frames, int columns, int rows, int individualWidth, int individualHeight);
	void EasyLoadAssetsAnimation(Texture* t, string file, Animation* anim,
		int frames, int columns, int rows, int individualWidth, int individualHeight,
		Animation* current);
	void LoadBinds();
	void Draw();
	void Update();
	void Movement();
	void Interaction();
	void TouchingContainer(Container*);
	void NotTouchingContainer();
	void TouchingItem(Item*);
	void NotTouchingItem(Item*);
	void TouchingDoor(Door*);
	void NotTouchingDoor();
	void CenterCamera();
	void SetRotation();
	float getRotationAngle();
	void createBox2dBody();
	void createPunchBox2dBody();
	void createMeleeBox2dBody();
	void createJoint();
	b2Vec2 Normalize(b2Vec2);
	void SetStats();
	void WatchUIPosition();
	void DrawWatch();
};

#endif
