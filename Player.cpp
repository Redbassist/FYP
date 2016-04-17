#include "Player.h"

//For the handling of collision filtering

Player::Player(Vector2f pos, bool multi) : m_pos(pos)
{
	multiplayer = multi;
	m_pos = pos;
	inventory = new Inventory();
	hotbar = new Hotbar();
	speed = 0.06f;
	touchedContainer = NULL;
	touchedDoor = NULL;
	dragInventoryItem = NULL;
	dragContainerItem = NULL;

	fullHealth = 1000;
	health = fullHealth / 100;
	heartBeatX = 0;

	hunger = 50;
	thirst = 50;
	hungerTick = time(&timer);
	thirstTick = time(&timer);
	hungerRate = 1;
	thirstRate = 0.5;

	currentHours = 12;
	currentMinutes = 0;
	nextMinute = 0;

	LoadAssets();
	LoadBinds();
	createBox2dBody();
	createPunchBox2dBody();

	createMeleeBox2dBody();
	createJoint();

	shot = false;
	swingSpeed = 10;
	punch = false;
	meleeAxe = false;
	meleeBat = false;
	pistol = false;
	rifle = false;
	shotgun = false;

	reloadTime = 1;
	reloadTimer = time(&timer);
	lastShot = Clock::now();
	rifleShootSpeed = 100;
	shotgunShootSpeed = 1100;
}

Player::Player(Vector2f pos, int hth, int hgr, int thst, vector<Item*> items)
{
	multiplayer = false;

	m_pos = pos;

	inventory = new Inventory();

	int size = items.size();
	for (int i = 0; i < size; i++) {
		inventory->AddItem(items[i], sf::Vector2f());
	}

	hotbar = new Hotbar();
	speed = 0.06f;
	touchedContainer = NULL;
	touchedDoor = NULL;
	dragInventoryItem = NULL;
	dragContainerItem = NULL;

	fullHealth = 1000;
	health = hth;
	heartBeatX = 0;

	hunger = hgr;
	thirst = thst;
	hungerTick = time(&timer);
	thirstTick = time(&timer);
	hungerRate = 1;
	thirstRate = 0.5;

	currentHours = 12;
	currentMinutes = 0;
	nextMinute = 0;

	LoadAssets();
	LoadBinds();
	createBox2dBody();
	createPunchBox2dBody();

	createMeleeBox2dBody();
	createJoint();

	shot = false;
	swingSpeed = 10;
	punch = false;
	meleeAxe = false;
	meleeBat = false;
	pistol = false;
	rifle = false;
	shotgun = false;

	reloadTime = 1;
	reloadTimer = time(&timer);
	lastShot = Clock::now();
	rifleShootSpeed = 100;
	shotgunShootSpeed = 1100;
}

void Player::LoadAssets() {
	//loading the animations for the player
	EasyLoadAssetsAnimation(&m_AnimationLegsTexture, "legs", &legsIdle, 1, 1, 1, 32, 32, currentLegAnimation);
	EasyLoadAssetsAnimation(&m_AnimationLegsTexture, "legs", &legsMoving, 12, 4, 3, 32, 32);

	EasyLoadAssetsAnimation(&m_AnimationTopTexture, "playerTop", &playerTopIdle, 1, 1, 1, 31, 27, currentTopAnimation);
	EasyLoadAssetsAnimation(&m_AnimationTopTexture, "playerTop", &playerTopMoving, 12, 4, 3, 31, 27);

	EasyLoadAssetsAnimation(&m_SwingAxeRightTexture, "swingAnimationAxeRight", &swingAxeRight, 5, 5, 1, 60, 60);
	EasyLoadAssetsAnimation(&m_SwingAxeLeftTexture, "swingAnimationAxeLeft", &swingAxeLeft, 5, 5, 1, 60, 60);

	EasyLoadAssetsAnimation(&m_SwingBatRightTexture, "swingAnimationBatRight", &swingBatRight, 5, 5, 1, 60, 60);
	EasyLoadAssetsAnimation(&m_SwingBatLeftTexture, "swingAnimationBatLeft", &swingBatLeft, 5, 5, 1, 60, 60);

	EasyLoadAssetsAnimation(&m_PunchRightTexture, "rightPunch", &punchRight, 4, 4, 1, 31, 27);
	EasyLoadAssetsAnimation(&m_PunchLeftTexture, "leftPunch", &punchLeft, 4, 4, 1, 31, 27);

	EasyLoadAssetsAnimation(&m_pistolTexture, "playerPistol", &pistolShoot, 1, 1, 1, 31, 27);

	EasyLoadAssetsAnimation(&m_rifleTexture, "playerRifle", &rifleShoot, 1, 1, 1, 36, 27);

	EasyLoadAssetsAnimation(&m_shotgunTexture, "playerShotgun", &shotgunShoot, 1, 1, 1, 36, 27);

	animatedLegSprite = AnimatedSprite(sf::seconds(0.08), true, false);
	animatedLegSprite.setOrigin(16, 16);
	animatedLegSprite.setPosition(m_pos);
	animatedLegSprite.setScale(1.8, 1.3);

	animatedTopSprite = AnimatedSprite(sf::seconds(0.08), true, false);
	animatedTopSprite.setOrigin(12, 13.5);
	animatedTopSprite.setPosition(m_pos);
	animatedTopSprite.setScale(1, 1);

	animatedSwingAxeRight = AnimatedSprite(sf::seconds(0.055), true, false);
	animatedSwingAxeRight.setOrigin(12, 28);
	animatedSwingAxeRight.setPosition(m_pos);
	animatedSwingAxeRight.setScale(1, 1);
	animatedSwingAxeRight.play(swingAxeRight);

	animatedSwingAxeLeft = AnimatedSprite(sf::seconds(0.055), true, false);
	animatedSwingAxeLeft.setOrigin(12, 28);
	animatedSwingAxeLeft.setPosition(m_pos);
	animatedSwingAxeLeft.setScale(1, 1);
	animatedSwingAxeLeft.play(swingAxeLeft);

	animatedPunchRight = AnimatedSprite(sf::seconds(0.04), true, false);
	animatedPunchRight.setOrigin(12, 13.5);
	animatedPunchRight.setPosition(m_pos);
	animatedPunchRight.setScale(1, 1);
	animatedPunchRight.play(punchRight);

	animatedPunchLeft = AnimatedSprite(sf::seconds(0.04), true, false);
	animatedPunchLeft.setOrigin(12, 13.5);
	animatedPunchLeft.setPosition(m_pos);
	animatedPunchLeft.setScale(1, 1);
	animatedPunchLeft.play(punchLeft);

	//loading the watch sprites for the UI
	watchTexture.loadFromFile("Sprites/watch.png");
	watchTexture.setSmooth(false);
	watchSprite.setTexture(watchTexture);
	watchSprite.setTextureRect(sf::IntRect(0, 0, watchTexture.getSize().x, watchTexture.getSize().y));
	watchSprite.setScale(0.3f, 0.3f);

	watchBGTexture.loadFromFile("Sprites/watchBack.png");
	watchBGTexture.setSmooth(false);
	watchBGSprite.setTexture(watchBGTexture);
	watchBGSprite.setTextureRect(sf::IntRect(0, 0, watchBGTexture.getSize().x, watchBGTexture.getSize().y));
	watchBGSprite.setScale(0.3f, 0.3f);

	heartBeatTexture.loadFromFile("Sprites/HeartBeat.png");
	heartBeatTexture.setSmooth(false);
	heartBeatSprite.setTexture(heartBeatTexture);
	heartBeatSprite.setTextureRect(sf::IntRect(0, 0, heartBeatTexture.getSize().x, heartBeatTexture.getSize().y));
	heartBeatSprite.setScale(0.3f, 0.3f);

	statusBarTexture.loadFromFile("Sprites/statusBar.png");
	statusBarTexture.setSmooth(false);
	foodBarSprite.setTexture(statusBarTexture);
	foodBarSprite.setTextureRect(sf::IntRect(0, 0, statusBarTexture.getSize().x, statusBarTexture.getSize().y));
	foodBarSprite.setScale(0.3f, 0.3f);
	drinkBarSprite.setTexture(statusBarTexture);
	drinkBarSprite.setTextureRect(sf::IntRect(0, 0, statusBarTexture.getSize().x, statusBarTexture.getSize().y));
	drinkBarSprite.setScale(0.3f, 0.3f);

	bloodScreenTexture.loadFromFile("Sprites/bloodScreen.png");
	bloodScreenTexture.setSmooth(true);
	bloodScreenSprite.setTexture(bloodScreenTexture);
	bloodScreenSprite.setTextureRect(sf::IntRect(0, 0, bloodScreenTexture.getSize().x, bloodScreenTexture.getSize().y));
	bloodScreenSprite.setColor(sf::Color(255, 255, 255, 0));
	bloodScreenSprite.setScale(0.7, 0.7);

	//setting the text inside the button
	watchFont.loadFromFile("digital.ttf");

	pointLightTexture.loadFromFile("assets/pointLightTexture.png");
	pointLightTexture.setSmooth(true);

	light = std::make_shared<ltbl::LightPointEmission>();
	light->_emissionSprite.setOrigin(pointLightTexture.getSize().x * 0.5f, pointLightTexture.getSize().y * 0.5f);
	light->_emissionSprite.setTexture(pointLightTexture);
	lightSize = 10;
	light->_emissionSprite.setScale(lightSize, lightSize);
	light->_emissionSprite.setColor({ 255u, 255u, 255u });
	light->_emissionSprite.setPosition(100.0f, 100.0f);
	ltbl::LightSystem::GetInstance()->addLight(light);

	heartRateText.setFont(watchFont);
	heartRateText.setCharacterSize(16);
	heartRateText.setColor(sf::Color::Black);

	currentTime.setFont(watchFont);
	currentTime.setCharacterSize(32);
	currentTime.setColor(sf::Color::Black);
}
void Player::EasyLoadAssetsAnimation(Texture* t, string file, Animation* anim, int frames, int columns, int rows, int individualWidth, int individualHeight, Animation * current)
{
	t->loadFromFile("Sprites/" + file + ".png");
	t->setSmooth(false);
	anim->setSpriteSheet(*t);
	anim->addFrames(frames, columns, rows, individualWidth, individualHeight);
	current = anim;
}

void Player::EasyLoadAssetsAnimation(Texture*t, string file, Animation* anim, int frames, int columns, int rows, int individualWidth, int individualHeight)
{
	t->loadFromFile("Sprites/" + file + ".png");
	t->setSmooth(false);
	anim->setSpriteSheet(*t);
	anim->addFrames(frames, columns, rows, individualWidth, individualHeight);
}

void Player::LoadBinds() {
	//binding the keys for the player
	InputManager::GetInstance()->Bind(&actions.walkUp, Keyboard::Key::W);
	InputManager::GetInstance()->Bind(&actions.walkDown, Keyboard::Key::S);
	InputManager::GetInstance()->Bind(&actions.walkLeft, Keyboard::Key::A);
	InputManager::GetInstance()->Bind(&actions.walkRight, Keyboard::Key::D);
	InputManager::GetInstance()->Bind(&actions.sprint, Keyboard::Key::LShift);
	InputManager::GetInstance()->BindSingleKeyPress(&actions.interact, Keyboard::Key::E);
	InputManager::GetInstance()->BindSingleKeyPress(&actions.inventory, Keyboard::Key::G);
	InputManager::GetInstance()->BindSingleMousePress(&actions.drop, Mouse::Button::Right);
	InputManager::GetInstance()->BindSingleMousePress(&actions.take, Mouse::Button::Left);
	InputManager::GetInstance()->Bind(&actions.drag, Mouse::Button::Left);
	InputManager::GetInstance()->BindSingleMousePress(&actions.swing, Mouse::Button::Left);
	InputManager::GetInstance()->BindSingleMousePress(&actions.punch, Mouse::Button::Left);
	InputManager::GetInstance()->BindSingleMousePress(&actions.fire, Mouse::Button::Left);
	InputManager::GetInstance()->BindSingleMousePress(&actions.use, Mouse::Button::Left);
	InputManager::GetInstance()->Bind(&actions.autoFire, Mouse::Button::Left);
	InputManager::GetInstance()->BindSingleKeyPress(&actions.hotbar1, Keyboard::Key::Num1);
	InputManager::GetInstance()->BindSingleKeyPress(&actions.hotbar2, Keyboard::Key::Num2);
	InputManager::GetInstance()->BindSingleKeyPress(&actions.hotbar3, Keyboard::Key::Num3);
	InputManager::GetInstance()->BindSingleKeyPress(&actions.hotbar4, Keyboard::Key::Num4);
	InputManager::GetInstance()->BindSingleKeyPress(&actions.hotbar5, Keyboard::Key::Num5);
	InputManager::GetInstance()->BindSingleKeyPress(&actions.reload, Keyboard::Key::R);
	InputManager::GetInstance()->BindSingleKeyPress(&actions.testNet, Keyboard::Key::Return);
}

void Player::Draw() {
	if (shot) {
		sf::VertexArray line(sf::LinesStrip, 2);

		// define the position of the triangle's points
		line[0].position = sf::Vector2f(gunRay.p1.x * SCALE, gunRay.p1.y * SCALE);
		line[0].color = sf::Color(255, 255, 255, 50);

		line[1].position = sf::Vector2f(gunRay.p2.x * SCALE, gunRay.p2.y * SCALE);
		line[1].color = sf::Color(255, 255, 255, 50);

		window->draw(line);
	}

	//frame time which is used for updating the animation
	sf::Time frameTime = frameClock.restart();

	//Setting the animation of the player legs depending on if is moving or not
	if ((actions.walkUp || actions.walkDown || actions.walkLeft || actions.walkRight)) {

		if (punch) {
			currentTopAnimation = (punchDirection == 0) ? &punchRight : &punchLeft;
		}
		else if (meleeAxe) {
			currentTopAnimation = (swingDirection == 0) ? &swingAxeRight : &swingAxeLeft;
		}
		else if (meleeBat) {
			currentTopAnimation = (swingDirection == 0) ? &swingBatRight : &swingBatLeft;
		}
		else if (pistol) {
			currentTopAnimation = &pistolShoot;
		}
		else if (rifle) {
			currentTopAnimation = &rifleShoot;
		}
		else if (shotgun) {
			currentTopAnimation = &shotgunShoot;
		}
		else
			currentTopAnimation = &playerTopMoving;
		currentLegAnimation = &legsMoving;
	}
	else {
		if (punch) {
			currentTopAnimation = (punchDirection == 0) ? &punchRight : &punchLeft;
		}
		else if (meleeAxe) {
			currentTopAnimation = (swingDirection == 0) ? &swingAxeRight : &swingAxeLeft;
		}
		else if (meleeBat) {
			currentTopAnimation = (swingDirection == 0) ? &swingBatRight : &swingBatLeft;
		}
		else if (pistol) {
			currentTopAnimation = &pistolShoot;
		}
		else if (rifle) {
			currentTopAnimation = &rifleShoot;
		}
		else if (shotgun) {
			currentTopAnimation = &shotgunShoot;
		}
		else
			currentTopAnimation = &playerTopIdle;
		currentLegAnimation = &legsIdle;
	}

	animatedLegSprite.play(*currentLegAnimation);
	animatedLegSprite.update(frameTime);

	window->draw(animatedLegSprite);

	if (punch) {
		if (punchDirection == 0) {
			window->draw(animatedPunchRight);
		}
		else {
			window->draw(animatedPunchLeft);
		}
		if (actions.punch) {
			if (punchDirection == 0)
				animatedPunchRight.update(frameTime);
			else
				animatedPunchLeft.update(frameTime);
		}
	}
	else if (meleeAxe || meleeBat) {
		if (swingDirection == 0) {
			//animatedSwingAxeRight.play(*currentTopAnimation);
			window->draw(animatedSwingAxeRight);
		}
		else {
			//animatedSwingAxeLeft.play(*currentTopAnimation);
			window->draw(animatedSwingAxeLeft);
		}
		if (actions.swing) {
			if (swingDirection == 0)
				animatedSwingAxeRight.update(frameTime);
			else
				animatedSwingAxeLeft.update(frameTime);
		}
	}
	else {
		animatedTopSprite.play(*currentTopAnimation);
		animatedTopSprite.update(frameTime);
		window->draw(animatedTopSprite);
	}

	/*View view1 = window->getView();
	ltbl::LightSystem::GetInstance()->render();
	sf::Sprite sprite(ltbl::LightSystem::GetInstance()->getLightingTexture());
	sprite.setPosition(view1.getCenter());
	sprite.setOrigin(640, 360);
	window->draw(sprite, *lightRenderStates);*/

	//drawing the inventory and its contents
	inventory->Draw();

	//drawing the hotbar and its contents
	hotbar->Draw();

	//if there is an item being dragged, draw it here
	if (dragInventoryItem != NULL) {
		dragInventoryItem->DrawDragged();
	}
	if (dragContainerItem != NULL) {
		dragContainerItem->DrawDragged();
	}

	DrawWatch();

	if (touchedContainer != NULL) {
		touchedContainer->DrawUI();
	}

	window->draw(bloodScreenSprite);
}

void Player::Update() {
	SetRotation();
	if (multiplayer) {
		SendPlayerData();
	}
	Movement();
	Interaction();
	SetStats();
	UpdateBloodMask();

	//setting the position of the sprite to the physics body
	animatedLegSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	animatedTopSprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	animatedSwingAxeRight.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	animatedSwingAxeLeft.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	animatedPunchRight.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
	animatedPunchLeft.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);

	m_pos = animatedTopSprite.getPosition();

	//setting camera to the player
	CenterCamera();

	//setting the watch position
	WatchUIPosition();

	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		SceneChanger::GetInstance()->ChangeScene(GameState::GAMEMENU);
	}
}

void Player::CenterCamera()
{
	View view = window->getView();
	view.setCenter(m_pos);
	window->setView(view);
}

void Player::Movement() {
	b2Vec2 position = body->GetPosition();

	float moveSpeed = speed;
	if (actions.sprint) { moveSpeed *= 1.5; }

	if (actions.walkUp) {
		position.y -= moveSpeed;
	}
	if (actions.walkDown) {
		position.y += moveSpeed;
	}
	if (actions.walkLeft) {
		position.x -= moveSpeed;
	}
	if (actions.walkRight) {
		position.x += moveSpeed;
	}

	//getting the punch to move out from players body using current orientation
	b2Vec2 orientationPoint = b2Vec2((float)cos(orientation * DEGTORAD), (float)sin(orientation * DEGTORAD));
	b2Vec2 punchTemp = orientationPoint;
	punchTemp.x /= 100;
	punchTemp.y /= 100;
	punchTemp.x *= punchDistance;
	punchTemp.y *= punchDistance;

	body->SetTransform(position, orientation * DEGTORAD);
	punchbody->SetTransform(body->GetPosition() + punchTemp, orientation * DEGTORAD);
	meleebody->SetTransform(meleebody->GetPosition(), (orientation - (80 - meleeAngle)) * DEGTORAD);

	m_pos = Vector2f(position.x * SCALE, position.y * SCALE);

	//updating the ray for the gun
	gunRay.p1 = position + b2Vec2(orientationPoint.x * 0.4, orientationPoint.y * 0.5);
	gunRay.p2 = position + b2Vec2(orientationPoint.x * 14.5, orientationPoint.y * 14.5);
	gunRay.maxFraction = 1;

	//updating the player listener to the position of the player
	float tempRot = orientation;
	//tempRot += 180;
	tempRot = 90;
	AudioManager::GetInstance()->setListener(m_pos, tempRot);

	light->_emissionSprite.setPosition(m_pos);
}

void Player::Interaction() {
	shot = false;

	Vector2i mousePos = Mouse::getPosition(*window);
	//used to convert to view coordinates
	sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);

	//opening and closing the inventory
	if (actions.inventory && inventory->CheckOpen()) {
		inventory->Close();
		dragInventoryItem = NULL;
		dragContainerItem = NULL;
		actions.inventory = false;
	}
	else if (actions.inventory && !inventory->CheckOpen()) {
		inventory->Open();
		actions.inventory = false;
	}

	if (actions.interact) {
		//opening and closing a touched container
		if (touchedContainer != NULL) {
			if (!touchedContainer->CheckOpen()) {
				touchedContainer->Open();
				actions.interact = false;
			}
			else {
				touchedContainer->Close();
				actions.interact = false;
			}
		}
		//picking up a close item
		else if (!touchedItems.empty()) {
			inventory->AddItem(touchedItems[0], Vector2f());
			touchedItems[0]->PickedUp();
			touchedItems.erase(touchedItems.begin());
			actions.interact = false;
		}
	}

	if (actions.drag && inventory->CheckOpen() && dragContainerItem == NULL) {
		if (dragInventoryItem == NULL) {
			dragInventoryItem = inventory->DragItem(worldMousePos);
		}
	}

	if (actions.drag && touchedContainer != NULL && touchedContainer->CheckOpen() && dragInventoryItem == NULL) {
		if (dragContainerItem == NULL) {
			dragContainerItem = touchedContainer->DragItem(worldMousePos);
		}
	}

	//when you are dropping the item (be it inventory / container)
	else if (!actions.drag && (dragInventoryItem != NULL || dragContainerItem != NULL)) {

		if (touchedContainer != NULL) {
			//dropping from inventory to the container
			if (dragInventoryItem != NULL && touchedContainer->CheckOpen()) {
				int itemSlot = dragInventoryItem->GetSlot();
				if (touchedContainer->AddItem(dragInventoryItem, worldMousePos)) {
					inventory->DropItem(dragInventoryItem, itemSlot);
					dragInventoryItem = NULL;
				}
			}
			//dropping from container to the inventory
			else if (dragContainerItem != NULL && inventory->CheckOpen()) {
				int itemSlot = dragContainerItem->GetSlot();
				if (inventory->AddItem(dragContainerItem, worldMousePos)) {
					touchedContainer->TakeItem(dragContainerItem, itemSlot);
					dragContainerItem = NULL;
				}
			}
		}

		//try drop item in the hotbar <- THINK OF WAY TO MAKE MORE EFFICIENT
		bool addedToHotbar = false;
		if (dragInventoryItem != NULL) {
			addedToHotbar = hotbar->AddItem(worldMousePos, dragInventoryItem);
		}

		//dropping the item from the inventory 
		if (dragInventoryItem != NULL && addedToHotbar == false) {
			Item* item = inventory->DropItem(dragInventoryItem, worldMousePos);
			if (item != NULL) {
				hotbar->RemoveItem(item->GetHotbarSlot());
				if (item == hotbarItem) {
					hotbarItem = NULL;
					punch = false;
					pistol = false;
					meleeAxe = false;
					meleeBat = false;
					rifle = false;
					shotgun = false;
				}
				item->Dropped(m_pos);
				cout << "Dropped inventory item on ground" << endl;
			}
		}

		dragInventoryItem = NULL;
		dragContainerItem = NULL;
	}

	//opening a door
	if (actions.interact && touchedDoor != NULL) {
		touchedDoor->OpenClose();
		actions.interact = false;
	}

	if (actions.swing && (meleeAxe || meleeBat)) {
		if (!doDamage) {
			doDamage = true;
			doingMeleeDamage = true;
		}
		if (swingDirection == 0) {
			meleeAngle += swingSpeed;
		}
		else {
			meleeAngle -= swingSpeed;
		}
		if (meleeAngle >= 160) {
			doDamage = false;
			doingMeleeDamage = false;
			swingDirection = 1;
			animatedSwingAxeRight.stop();
			if (meleeAxe)
				animatedSwingAxeLeft.play(swingAxeLeft);
			else if (meleeBat)
				animatedSwingAxeLeft.play(swingBatLeft);
			actions.swing = false;
		}
		else if (meleeAngle <= 0) {
			swingDirection = 0;
			animatedSwingAxeLeft.stop();
			if (meleeAxe)
				animatedSwingAxeRight.play(swingAxeRight);
			else if (meleeBat)
				animatedSwingAxeRight.play(swingBatRight);
			actions.swing = false;
		}
	}

	if (actions.punch && punch) {
		if (!doDamage) {
			doDamage = true;
			doingPunchDamage = true;
		}

		if (punchDistance < maxPunchDistance) {
			punchDistance += 5;
		}
		else {
			doDamage = false;
			doingPunchDamage = false;
			punchDirection = (punchDirection == 0) ? 1 : 0;
			if (punchDirection == 0) {
				animatedPunchLeft.stop();
				animatedPunchRight.play(punchRight);
			}
			else {
				animatedPunchRight.stop();
				animatedPunchLeft.play(punchLeft);
			}
			punchDistance = 0;
			actions.punch = false;
		}
	}

	if (!inventory->CheckOpen()) {
		if (actions.autoFire && rifle && !reloading) {
			if (std::chrono::duration_cast<milliseconds>(Clock::now() - lastShot).count() > rifleShootSpeed) {
				if (hotbarItem->RemoveAmmo(1).first) {
					AudioManager::GetInstance()->playSound("rifleshot", m_pos);
					RayCastManager::GetInstance()->CastBulletRay(gunRay.p1, gunRay.p2);
					shot = true;
				}
				else {
					AudioManager::GetInstance()->playSound("pistoldry", m_pos);
				}
				lastShot = Clock::now();
			}
		}

		else if (actions.fire) {
			if (!reloading && (pistol || shotgun)) {
				if (hotbarItem->RemoveAmmo(1).first) {
					if (pistol) {
						AudioManager::GetInstance()->playSound("pistolshot", m_pos);
						RayCastManager::GetInstance()->CastBulletRay(gunRay.p1, gunRay.p2);
						shot = true;
					}
					else if (shotgun && std::chrono::duration_cast<milliseconds>(Clock::now() - lastShot).count() > shotgunShootSpeed) {
						AudioManager::GetInstance()->playSound("shotgunshot", m_pos);
						RayCastManager::GetInstance()->CastBulletRay(gunRay.p1, gunRay.p2);
						shot = true;
						lastShot = Clock::now();
					}
				}
				else {
					if (pistol)
						AudioManager::GetInstance()->playSound("pistoldry", m_pos);
					else if (shotgun)
						AudioManager::GetInstance()->playSound("pistoldry", m_pos);
				}
			}
		}
	}

	if (actions.hotbar1 || actions.hotbar2 || actions.hotbar3 || actions.hotbar4 || actions.hotbar5) {
		if (actions.hotbar1) hotbarItem = hotbar->SelectItem(0);
		else if (actions.hotbar2) hotbarItem = hotbar->SelectItem(1);
		else if (actions.hotbar3) hotbarItem = hotbar->SelectItem(2);
		else if (actions.hotbar4) hotbarItem = hotbar->SelectItem(3);
		else if (actions.hotbar5) hotbarItem = hotbar->SelectItem(4);

		if (hotbarItem != NULL) {

			punch = false;
			meleeAxe = false;
			meleeBat = false;
			pistol = false;
			shotgun = false;
			rifle = false;
			actions.swing = false;

			switch (hotbarItem->GetType()) {
			case(ItemType::AXE) :
				meleeAxe = true;
				animatedSwingAxeRight.play(swingAxeRight);
				animatedSwingAxeLeft.play(swingAxeLeft);
				break;
			case(ItemType::BAT) :
				meleeBat = true;
				animatedSwingAxeRight.play(swingBatRight);
				animatedSwingAxeLeft.play(swingBatLeft);
				break;
			case(ItemType::PISTOL) :
				pistol = true;
				break;
			case(ItemType::RIFLE) :
				rifle = true;
				break;
			case(ItemType::SHOTGUN) :
				shotgun = true;
				break;
			}

		}
		else {
			punch = true;
			meleeAxe = false;
			meleeBat = false;
			pistol = false;
			shotgun = false;
			rifle = false;
		}

		actions.hotbar1 = false;
		actions.hotbar2 = false;
		actions.hotbar3 = false;
		actions.hotbar4 = false;
		actions.hotbar5 = false;
	}

	//reloading the current weapon
	if (actions.reload && hotbarItem != NULL && (pistol || rifle || shotgun) && !reloading) {
		hotbarItem->AddAmmo(inventory->SearchAmmo(hotbarItem->GetType(), hotbarItem->MissingAmmo()));
		reloadTimer = time(&timer);
		if (hotbarItem->GetType() == PISTOL) {
			AudioManager::GetInstance()->playSound("loadPistol", m_pos);
			reloadTime = 1;
		}
		else if (hotbarItem->GetType() == RIFLE) {
			AudioManager::GetInstance()->playSound("loadRifle", m_pos);
			reloadTime = 1;
		}
		else if (hotbarItem->GetType() == SHOTGUN) {
			AudioManager::GetInstance()->playSound("loadShotgun", m_pos);
			reloadTime = 2;
		}
		reloading = true;
		actions.reload = false;

		if (hotbarItem->GetAmmo() > 0)
			ammoEmpty = false;
	}

	if (actions.use && hotbarItem != NULL) {
		if (hotbarItem->GetType() == FOOD1 || hotbarItem->GetType() == FOOD2 || hotbarItem->GetType() == FOOD3) {
			hunger -= 30;
			hunger = (hunger < 0) ? 0 : hunger;
			hotbar->RemoveItem(hotbarItem->GetHotbarSlot());
			inventory->UseItem(hotbarItem->GetSlot());
			hotbarItem = NULL;
		}
		else if (hotbarItem->GetType() == WATER1 || hotbarItem->GetType() == WATER2) {
			thirst -= 70;
			thirst = (thirst < 0) ? 0 : thirst;
			hotbar->RemoveItem(hotbarItem->GetHotbarSlot());
			inventory->UseItem(hotbarItem->GetSlot());
			hotbarItem = NULL;
		}
		actions.use = false;
	}
	else {
		actions.use = false;
	}

	if (difftime(time(&timer), reloadTimer) > reloadTime && reloading) {
		reloading = false;
	}

	if (hotbarItem == NULL) {
		meleeAxe = false;
		meleeBat = false;
		pistol = false;
	}
	else {
		if (hotbarItem->GetType() == PISTOL || hotbarItem->GetType() == RIFLE || hotbarItem->GetType() == SHOTGUN) {
			if (hotbarItem->GetAmmo() == 0)
				ammoEmpty = true;
			else
				ammoEmpty = false;
		}
	}

	invOpen = inventory->CheckOpen();

	//making sure if fire didnt happen, that it doesnt try again next frame
	actions.fire = false;
}

void Player::TouchingContainer(Container* container) {
	touchedContainer = container;
}

void Player::NotTouchingContainer() {
	touchedContainer = NULL;
	dragContainerItem - NULL;
}

void Player::TouchingDoor(Door* door) {
	touchedDoor = door;
}

void Player::NotTouchingDoor() {
	touchedDoor = NULL;
}

void Player::TouchingItem(Item* item) {
	touchedItems.push_back(item);
}

void Player::NotTouchingItem(Item* item) {
	std::vector<Item*>::iterator iter = touchedItems.begin();
	std::vector<Item*>::iterator end = touchedItems.end();

	for (; iter != end; ++iter) {
		if (item == (*iter)) {
			touchedItems.erase(iter);
			break;
		}
	}
}

void Player::SetRotation() {
	orientation = getRotationAngle();
	animatedLegSprite.setRotation(orientation);
	animatedTopSprite.setRotation(orientation);
	animatedSwingAxeRight.setRotation(orientation);
	animatedSwingAxeLeft.setRotation(orientation);
	animatedPunchRight.setRotation(orientation);
	animatedPunchLeft.setRotation(orientation);
}

void Player::createBox2dBody() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(m_pos.x / SCALE, m_pos.y / SCALE);
	bodyDef.userData = this;
	bodyDef.gravityScale = 1;
	body = world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 7 / SCALE;
	fixtureDef.shape = &circle;

	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	fixtureDef.userData = "Player";
	fixtureDef.restitution = b2MixRestitution(0, 0);

	fixtureDef.filter.categoryBits = PLAYER;
	fixtureDef.filter.maskBits = ENEMY | ENEMYPUNCH | ITEM | CONTAINER | WALL | DOOR | FILLER;

	body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(false);
}

void Player::createPunchBox2dBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(m_pos.x / SCALE, m_pos.y / SCALE);
	bodyDef.userData = this;
	bodyDef.gravityScale = 1;
	punchbody = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(7.5 / SCALE, 7.5 / SCALE, b2Vec2(0 / SCALE, 0), 0);
	punchfixtureDef.shape = &dynamicBox;

	punchfixtureDef.isSensor = true;
	punchfixtureDef.density = 1;
	punchfixtureDef.friction = 0.3f;
	punchfixtureDef.userData = "Punch";
	punchfixtureDef.restitution = b2MixRestitution(0, 0);

	punchfixtureDef.filter.categoryBits = PUNCH;
	punchfixtureDef.filter.maskBits = ITEM | CONTAINER | WALL | DOOR | PLAYER | ENEMYHIT;

	punchbody->CreateFixture(&punchfixtureDef);
	punchbody->SetFixedRotation(false);
}

void Player::createMeleeBox2dBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = this;
	bodyDef.gravityScale = 1;
	meleebody = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(15 / SCALE, 1 / SCALE, b2Vec2(15 / SCALE, 0), 0);
	meleefixtureDef.shape = &dynamicBox;

	meleefixtureDef.isSensor = true;
	meleefixtureDef.density = 0.000000001;
	meleefixtureDef.friction = 0.0f;
	meleefixtureDef.userData = "MeleeWeapon";
	meleefixtureDef.restitution = b2MixRestitution(0, 0);

	meleefixtureDef.filter.categoryBits = MELEE;
	meleefixtureDef.filter.maskBits = CONTAINER | WALL | DOOR | PLAYER | ENEMYHIT;

	meleebody->CreateFixture(&meleefixtureDef);
	meleebody->SetFixedRotation(false);
}

void Player::createJoint()
{
	meleeJointDef;
	meleeJointDef.bodyA = body;
	meleeJointDef.bodyB = meleebody;
	meleeJointDef.collideConnected = false;
	meleeJointDef.localAnchorA.Set(0, 0);
	meleeJointDef.localAnchorB.Set(0, 0);
	meleeJoint = world->CreateJoint(&meleeJointDef);
}

b2Vec2 Player::Normalize(b2Vec2 vector) {
	float length = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	if (length != 0) {
		vector.x /= length;
		vector.y /= length;
	}
	return vector;
}

//Setting the stats for the UI depending on the status of the player
void Player::SetStats() {
	//for seting current heart rate on watch using the health of the player
	heartRate = fullHealth / (health * 100);
	int heartRateForText = 85 + (10 * heartRate);
	heartRateText.setString(to_string(heartRateForText));

	//Handling the hunger and thirst of the player
	if (difftime(time(&timer), hungerTick) / 60 > hungerRate) {
		hunger += 5;
		hunger = (hunger > 100) ? 100 : hunger;
		hungerTick = time(&timer);
	}

	if (difftime(time(&timer), thirstTick) / 60 > thirstRate) {
		thirst += 5;
		thirst = (thirst > 100) ? 100 : thirst;
		thirstTick = time(&timer);
	}

	float foodBarLength = (100 - hunger) / 100;
	float drinkBarLength = (100 - thirst) / 100;

	foodBarSprite.setScale(0.3 * foodBarLength, 0.3);
	drinkBarSprite.setScale(0.3 * drinkBarLength, 0.3);

	//current time on the watch 1 second = 1 minute
	nextMinute++;

	if (nextMinute > 59) {
		nextMinute = 0;
		currentMinutes++;
		if (currentMinutes > 59) {
			currentHours++;
			if (currentHours > 23)
				currentHours = 0;
			currentMinutes = 0;
		}
	}

	String timeText;

	if (currentHours < 10)
		timeText = "0" + to_string(currentHours) + " : ";
	else
		timeText = to_string(currentHours) + " : ";

	if (currentMinutes < 10)
		timeText += "0" + to_string(currentMinutes);
	else
		timeText += to_string(currentMinutes);

	currentTime.setString(timeText);
}

void Player::WatchUIPosition() {
	//placing the watchUI in the correct position on the screen
	Vector2f center = window->getView().getCenter();
	Vector2f size = window->getView().getSize();

	sf::Vector2f watchBGOffset = sf::Vector2f(size.x / 20, size.y / 6);
	sf::Vector2f heartBeatOffset = sf::Vector2f(size.x / 19.5, size.y / 6);
	sf::Vector2f heartRateTextOffset = sf::Vector2f(size.x / 12.2, size.y / 5.8);
	sf::Vector2f timeTextOffset = sf::Vector2f(size.x / 16.6, size.y / 3.2);

	//placing the watch / heart beat monitor / heart rate text / time
	watchBGSprite.setPosition(center.x + size.x / 3.1 + watchBGOffset.x, center.y + watchBGOffset.y);
	heartBeatSprite.setPosition((center.x + size.x / 3.1 + heartBeatOffset.x) + heartBeatX, center.y + heartBeatOffset.y);
	watchSprite.setPosition(center.x + size.x / 3.1, center.y);
	foodBarSprite.setPosition(center.x + size.x / 3.1 + timeTextOffset.x + 15, center.y + timeTextOffset.y - 9);
	drinkBarSprite.setPosition(center.x + size.x / 3.1 + timeTextOffset.x + 54, center.y + timeTextOffset.y - 9);
	heartRateText.setPosition(center.x + size.x / 3.1 + heartRateTextOffset.x, center.y + heartRateTextOffset.y);
	currentTime.setPosition(center.x + size.x / 3.1 + timeTextOffset.x, center.y + timeTextOffset.y);

	if (heartBeatX < 85) {
		heartBeatX += heartRate;
	}
	else
		heartBeatX = 0;

	//drawing the blood mask in the right place
	bloodScreenSprite.setPosition(center - Vector2f(size.x / 2, size.y / 2));
}

void Player::DrawWatch() {
	window->draw(watchBGSprite);
	window->draw(heartBeatSprite);
	window->draw(watchSprite);
	window->draw(foodBarSprite);
	window->draw(drinkBarSprite);
	window->draw(heartRateText);
	window->draw(currentTime);
}

void Player::TakeDamage(int type)
{
	//punched
	if (type == 0) {
		health -= 1.5f;
		AudioManager::GetInstance()->playSound("groan", m_pos);
		BloodMask();
	}
}

void Player::BloodMask()
{
	bloodScreenAlpha = 255;
	bloodScreenSprite.setColor((sf::Color(255, 255, 255, bloodScreenAlpha)));
}

void Player::UpdateBloodMask()
{
	//fading out the blood mask
	float alpha = bloodScreenSprite.getColor().a;
	float desiredAlpha = 150 - (150 * (health / 10));

	if (alpha > desiredAlpha)
		alpha -= 1;

	bloodScreenSprite.setColor((sf::Color(255, 255, 255, alpha)));
}

void Player::SendPlayerData()
{
	NetworkPacket* np = new NetworkPacket();
	np->type = "PlayerData";
	np->playerID = playerID;

	//adding player data to packet for server to use
	np->data.push_back(m_pos.x);
	np->data.push_back(m_pos.y);
	np->data.push_back(orientation);

	AddActionsToPacket(np->data);
	np->dataSize = np->data.size();

	Network::GetInstance()->SendPacket("192.168.1.18", np);
}

void Player::AddActionsToPacket(vector<float>& data)
{
	data.push_back(actions.walkLeft);
	data.push_back(actions.walkRight);
	data.push_back(actions.walkUp);
	data.push_back(actions.sprint);
	data.push_back(invOpen);
	data.push_back(actions.swing);
	data.push_back(actions.punch);
	data.push_back(actions.fire);
	data.push_back(actions.autoFire);
	data.push_back(actions.reload);
	data.push_back(punch);
	data.push_back(meleeAxe);
	data.push_back(meleeBat);
	data.push_back(pistol);
	data.push_back(shotgun);
	data.push_back(rifle);
	data.push_back(reloading);
	data.push_back(ammoEmpty);
}

float Player::getRotationAngle() {
	Vector2i mousePos = Mouse::getPosition(*window);
	//used to convert to view coordinates
	sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);
	float dx = worldMousePos.x - m_pos.x;
	float dy = worldMousePos.y - m_pos.y;
	float radian = atan2f(dy, dx);
	return (radian * RADTODEG);
}
