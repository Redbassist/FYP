#include "SceneManager.h" 

SceneManager::SceneManager()
{
	state = GameState::SPLASHSCREEN;
	gameWorld = NULL;
	AudioManager::GetInstance()->startMusic("menuMusic");
	CreateMenus();
}

void SceneManager::CreateMenus()
{
	//creating the splash screen
	Menu* tempMenu = new Menu(string("splashMenu"));
	tempMenu->AddButton(new Button(Vector2f(650, 640), 200, 80, string("Continue..."), GameState::MENU));
	menusMap[GameState::SPLASHSCREEN] = tempMenu;
	currentMenu = tempMenu;

	//creating the main menu
	tempMenu = new Menu(string("normalMenu"));
	tempMenu->AddButton(new Button(Vector2f(1050, 160), 200, 80, string("Multiplayer"), GameState::MULTIPLAYERMENU));
	tempMenu->AddButton(new Button(Vector2f(1050, 280), 200, 80, string("Continue"), GameState::CONTINUEGAME));
	tempMenu->AddButton(new Button(Vector2f(1050, 400), 200, 80, string("New Game"), GameState::NEWGAME));
	tempMenu->AddButton(new Button(Vector2f(1050, 520), 200, 80, string("Options"), GameState::OPTIONS));
	tempMenu->AddButton(new Button(Vector2f(150, 150), 200, 80, string("CONTROLS"), GameState::CONTROLS));
	tempMenu->AddButton(new Button(Vector2f(1050, 640), 200, 80, string("Exit"), GameState::EXIT));
	menusMap[GameState::MENU] = tempMenu;

	//creating the CONTROLS menu
	tempMenu = new Menu(string("controlMenu")); 
	tempMenu->AddButton(new Button(Vector2f(150, 660), 200, 80, string("Back"), GameState::MENU));
	menusMap[GameState::CONTROLS] = tempMenu;

	//creating the options menu
	tempMenu = new Menu(string("normalMenu"));
	tempMenu->AddSlider(new Slider(Vector2f(700, 200), 500, string("Master Volume"), Setting::MASTER));
	tempMenu->AddSlider(new Slider(Vector2f(700, 400), 500, string("Music Volume"), Setting::MUSIC));
	tempMenu->AddSlider(new Slider(Vector2f(700, 600), 500, string("Effects Volume"), Setting::SHORT));
	tempMenu->AddButton(new Button(Vector2f(150, 650), 200, 80, string("Back"), GameState::MENU));
	menusMap[GameState::OPTIONS] = tempMenu;

	//creating the connect menu
	tempMenu = new Menu(string("normalMenu"));
	tempMenu->AddButton(new Button(Vector2f(640, 280), 200, 80, string("Connect"), GameState::CONNECT));
	tempMenu->AddButton(new Button(Vector2f(640, 520), 200, 80, string("Back"), GameState::MENU));
	menusMap[GameState::MULTIPLAYERMENU] = tempMenu;

	//creating the connect menu
	tempMenu = new Menu(string("waitMenu"));
	tempMenu->AddButton(new Button(Vector2f(640, 520), 200, 80, string("Cancel"), GameState::MENU));
	menusMap[GameState::CONNECT] = tempMenu;

	//creating the menu for in game
	tempMenu = NULL;
	menusMap[GameState::GAME] = tempMenu;

	//creating the game menu
	tempMenu = new Menu(string("ingameMenu"));
	tempMenu->AddButton(new Button(Vector2f(430, 150), 180, 55, string("Resume"), GameState::CONTINUEGAME));
	tempMenu->AddButton(new Button(Vector2f(430, 245), 180, 55, string("Options"), GameState::GAMEOPTIONS));
	tempMenu->AddButton(new Button(Vector2f(430, 340), 180, 55, string("Exit"), GameState::SAVEEXIT));
	menusMap[GameState::GAMEMENU] = tempMenu;

	//creating the game options menu
	tempMenu = new Menu(string("ingameMenu"));
	tempMenu->AddSlider(new Slider(Vector2f(250, 150), 400, string("Master Volume"), Setting::MASTER));
	tempMenu->AddSlider(new Slider(Vector2f(250, 245), 400, string("Music Volume"), Setting::MUSIC));
	tempMenu->AddSlider(new Slider(Vector2f(250, 340), 400, string("Effects Volume"), Setting::SHORT));
	tempMenu->AddButton(new Button(Vector2f(330, 420), 180, 55, string("Back"), GameState::GAMEMENU));
	menusMap[GameState::GAMEOPTIONS] = tempMenu;

	//creating the MULTI game menu
	tempMenu = new Menu(string("ingameMenu"));
	tempMenu->AddButton(new Button(Vector2f(430, 150), 180, 55, string("Resume"), GameState::MULTIPLAYER));
	tempMenu->AddButton(new Button(Vector2f(430, 245), 180, 55, string("Options"), GameState::MULTIGAMEOPTIONS));
	tempMenu->AddButton(new Button(Vector2f(430, 340), 180, 55, string("Exit"), GameState::EXIT));
	menusMap[GameState::MULTIGAMEMENU] = tempMenu;

	//creating the MULTI game options menu
	tempMenu = new Menu(string("ingameMenu"));
	tempMenu->AddSlider(new Slider(Vector2f(250, 150), 400, string("Master Volume"), Setting::MASTER));
	tempMenu->AddSlider(new Slider(Vector2f(250, 245), 400, string("Music Volume"), Setting::MUSIC));
	tempMenu->AddSlider(new Slider(Vector2f(250, 340), 400, string("Effects Volume"), Setting::SHORT));
	tempMenu->AddButton(new Button(Vector2f(330, 420), 180, 55, string("Back"), GameState::MULTIGAMEMENU));
	menusMap[GameState::MULTIGAMEOPTIONS] = tempMenu;

	//creating the dead menu
	tempMenu = new Menu(string("deadMenu"));
	tempMenu->AddButton(new Button(Vector2f(640, 400), 200, 80, string("Main Menu"), GameState::MENU));
	tempMenu->AddButton(new Button(Vector2f(640, 520), 200, 80, string("Exit Game"), GameState::EXIT));
	menusMap[GameState::DEAD] = tempMenu;

	//creating the dead menu
	tempMenu = new Menu(string("winMenu"));
	tempMenu->AddButton(new Button(Vector2f(300, 600), 200, 80, string("Main Menu"), GameState::MENU));
	tempMenu->AddButton(new Button(Vector2f(600, 600), 200, 80, string("Exit Game"), GameState::EXIT));
	menusMap[GameState::WIN] = tempMenu;
}

void SceneManager::Update()
{
	ChangeScene();

	if (currentMenu != NULL)
		currentMenu->Update();

	//updating the gameWorld
	if ((SceneChanger::GetInstance()->CurrentScene() == GameState::NEWGAME
		|| SceneChanger::GetInstance()->CurrentScene() == GameState::MULTIPLAYER
		|| SceneChanger::GetInstance()->CurrentScene() == GameState::CONTINUEGAME ||
		SceneChanger::GetInstance()->CurrentScene() == GameState::MULTIGAMEOPTIONS ||
		SceneChanger::GetInstance()->CurrentScene() == GameState::MULTIGAMEMENU)
		&& gameWorld != NULL)
		gameWorld->Update();

	if (SceneChanger::GetInstance()->CurrentScene() == GameState::CONNECT) {
		if (Network::GetInstance()->startGame) {
			SceneChanger::GetInstance()->ChangeScene(GameState::MULTIPLAYER);
			Network::GetInstance()->startGame = false;
		}
	}
}

void SceneManager::Draw()
{
	//updating the gameWorld
	if ((SceneChanger::GetInstance()->CurrentScene() == GameState::NEWGAME ||
		SceneChanger::GetInstance()->CurrentScene() == GameState::MULTIPLAYER ||
		SceneChanger::GetInstance()->CurrentScene() == GameState::GAMEOPTIONS ||
		SceneChanger::GetInstance()->CurrentScene() == GameState::CONTINUEGAME ||
		SceneChanger::GetInstance()->CurrentScene() == GameState::GAMEMENU ||
		SceneChanger::GetInstance()->CurrentScene() == GameState::MULTIGAMEOPTIONS || 
		SceneChanger::GetInstance()->CurrentScene() == GameState::MULTIGAMEMENU
		)
		&& gameWorld != NULL) {
		gameWorld->Draw();
		EffectManager::GetInstance()->Draw();
	}
	if (currentMenu != NULL)
		currentMenu->Draw();
}

void SceneManager::ChangeScene()
{
	b2Body* bodyList;
	if (SceneChanger::GetInstance()->SceneChanging()) {
		switch (SceneChanger::GetInstance()->CurrentScene()) {
		case(GameState::SPLASHSCREEN) :
			currentMenu = menusMap[GameState::SPLASHSCREEN];
			currentMenu->UpdateTransform();
			break;
		case(GameState::MENU) : 
			bodyList = world->GetBodyList();
			for (; bodyList != NULL; bodyList = bodyList->GetNext()) {
				bodyList->GetFixtureList()->SetUserData("Destroy"); 
			}

			if (gameWorld != NULL) {
				delete gameWorld;
				gameWorld = NULL;
			}
			if (connect) {
				NetworkPacket* np = new NetworkPacket();
				np->type = "Disconnect";
				np->playerID = playerID;
				Network::GetInstance()->SendPacket(serverIP, np);
				connect = true;
				connect = false;
			}
			currentMenu = menusMap[GameState::MENU];
			currentMenu->UpdateTransform();
			break;
		case(GameState::CONTINUEGAME) :
			currentMenu = menusMap[GameState::GAME];
			if (gameWorld == NULL) {
				gameWorld = new World(true, false);
				AudioManager::GetInstance()->startMusic("backgroundMusic");
			}
			break;
		case(GameState::NEWGAME) : 
			currentMenu = menusMap[GameState::GAME];
			if (gameWorld == NULL) {
				gameWorld = new World(false, false);
				AudioManager::GetInstance()->startMusic("backgroundMusic");
			}
			break;
		case(GameState::CONTROLS) :
			currentMenu = menusMap[GameState::CONTROLS]; 
			break;
		case(GameState::OPTIONS) :
			currentMenu = menusMap[GameState::OPTIONS];
			currentMenu->UpdateTransform();
			break;
		case(GameState::MULTIPLAYERMENU) :
			currentMenu = menusMap[GameState::MULTIPLAYERMENU];
			currentMenu->UpdateTransform();
			break;
		case(GameState::CONNECT) :
			currentMenu = menusMap[GameState::CONNECT];
			if (!connect) {
				NetworkPacket* np = new NetworkPacket();
				np->type = "Connection";
				np->playerID = playerID;
				Network::GetInstance()->SendPacket(serverIP, np);
				connect = true;
			}
			break;
		case(GameState::MULTIPLAYER) :
			currentMenu = menusMap[GameState::GAME];
			if (gameWorld == NULL) { 
				gameWorld = new World(true, true); 
				AudioManager::GetInstance()->startMusic("backgroundMusic");
			}
			break;
		case(GameState::GAMEMENU) :
			currentMenu = menusMap[GameState::GAMEMENU];
			currentMenu->UpdateTransform();
			break;
		case(GameState::GAMEOPTIONS) :
			currentMenu = menusMap[GameState::GAMEOPTIONS];
			currentMenu->UpdateTransform();
			break;
		case(GameState::MULTIGAMEMENU) :
			currentMenu = menusMap[GameState::MULTIGAMEMENU];
			currentMenu->UpdateTransform();
			break;
		case(GameState::MULTIGAMEOPTIONS) :
			currentMenu = menusMap[GameState::MULTIGAMEOPTIONS];
			currentMenu->UpdateTransform();
			break;
		case(GameState::DEAD) :
			gameWorld->DeletePlayerSave();
			currentMenu = menusMap[GameState::DEAD];
			currentMenu->UpdateTransform();
			break;
		case(GameState::WIN) : 
			currentMenu = menusMap[GameState::WIN];
			currentMenu->UpdateTransform();
			break;
		case(GameState::SAVEEXIT) :
			if (gameWorld != NULL) {
				gameWorld->SavePlayer();
			}
			window->close();
			break;
		case(GameState::EXIT) : 
			window->close();
			break;
		}
	}
}
