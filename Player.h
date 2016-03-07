#pragma once
#ifndef Player_H
#define Player_H

#include "stdafx.h"
#include "Globals.h"
#include "Animation.h"
#include "AnimatedSprite.h" 
#include "Inventory.h"
#include "Hotbar.h"
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
	bool autoFire = false;
	bool reload = false;
	bool hotbar1 = false;
	bool hotbar2 = false;
	bool hotbar3 = false;
	bool hotbar4 = false;
	bool hotbar5 = false;
};

class Player {
private:
	//player stats
	float fullHealth;
	float health;
	float hunger;
	float thirst;
	bool bleeding = false;

	keyActions actions;
	Texture m_AnimationLegsTexture;
	Texture m_AnimationTopTexture;
	Texture m_SwingAxeRightTexture;
	Texture m_SwingAxeLeftTexture;
	Texture m_SwingBatRightTexture;
	Texture m_SwingBatLeftTexture;
	Texture m_PunchRightTexture;
	Texture m_PunchLeftTexture;
	Texture m_pistolTexture;
	Texture m_rifleTexture;
	Texture m_shotgunTexture;
	Animation legsIdle;
	Animation legsMoving;
	Animation playerTopIdle;
	Animation playerTopMoving;
	Animation swingAxeRight;
	Animation swingAxeLeft;
	Animation swingBatRight;
	Animation swingBatLeft;
	Animation punchLeft;
	Animation punchRight;
	Animation pistolShoot;
	Animation rifleShoot;
	Animation shotgunShoot;
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

	sf::Texture pointLightTexture;
	shared_ptr<ltbl::LightPointEmission> light;
	float lightSize = 20;

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

	bool meleeAxe;
	bool meleeBat;
	int swingDirection = 0; //0 is right, 1 is left
	float meleeAngle = 0;
	int swingSpeed;

	bool pistol;
	bool shotgun;
	bool rifle;
	int shoottime = 0;
	float rifleShootSpeed; 
	float shotgunShootSpeed;
	typedef std::chrono::high_resolution_clock Clock;
	typedef std::chrono::milliseconds milliseconds;
	Clock::time_point lastShot;
	time_t reloadTimer; 
	int reloadTime;
	bool reloading;

	Container* touchedContainer;
	std::vector<Item*> touchedItems;
	Door* touchedDoor;

	Item* dragInventoryItem;
	Item* dragContainerItem;
	Item* hotbarItem = NULL;

	Vector2f m_pos;
	float orientation;
	float speed;

	Inventory* inventory;
	Hotbar* hotbar;

	sf::Clock frameClock;
	b2RayCastInput gunRay;
	time_t timer;

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
