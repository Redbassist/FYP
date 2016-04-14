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
	tempMenu->AddButton(new Button(Vector2f(1050, 160), 200, 80, string("Multiplayer"), GameState::MULTIPLAYER));
	tempMenu->AddButton(new Button(Vector2f(1050, 280), 200, 80, string("Continue"), GameState::CONTINUEGAME));
	tempMenu->AddButton(new Button(Vector2f(1050, 400), 200, 80, string("New Game"), GameState::NEWGAME));
	tempMenu->AddButton(new Button(Vector2f(1050, 520), 200, 80, string("Options"), GameState::OPTIONS));
	tempMenu->AddButton(new Button(Vector2f(1050, 640), 200, 80, string("Exit"), GameState::EXIT));
	menusMap[GameState::MENU] = tempMenu;

	//creating the options menu
	tempMenu = new Menu(string("normalMenu"));
	tempMenu->AddSlider(new Slider(Vector2f(700, 200), 500, string("Master Volume"), Setting::MASTER));
	tempMenu->AddSlider(new Slider(Vector2f(700, 400), 500, string("Music Volume"), Setting::MUSIC));
	tempMenu->AddSlider(new Slider(Vector2f(700, 600), 500, string("Effects Volume"), Setting::SHORT));
	tempMenu->AddButton(new Button(Vector2f(150, 650), 200, 80, string("Back"), GameState::MENU));
	menusMap[GameState::OPTIONS] = tempMenu;

	//creating the options menu
	tempMenu = new Menu(string("normalMenu"));
	tempMenu->AddButton(new Button(Vector2f(1050, 280), 200, 80, string("Connect"), GameState::CONNECT));
	tempMenu->AddButton(new Button(Vector2f(1050, 520), 200, 80, string("Back"), GameState::MENU));
	menusMap[GameState::MULTIPLAYER] = tempMenu;

	//creating the menu for in game
	tempMenu = NULL;
	menusMap[GameState::GAME] = tempMenu;

	//creating the game menu
	tempMenu = new Menu(string("ingameMenu"));
	tempMenu->AddButton(new Button(Vector2f(430, 150), 180, 55, string("Resume"), GameState::GAME));
	tempMenu->AddButton(new Button(Vector2f(430, 245), 180, 55, string("Options"), GameState::GAMEOPTIONS));
	tempMenu->AddButton(new Button(Vector2f(430, 340), 180, 55, string("Exit"), GameState::EXIT));
	menusMap[GameState::GAMEMENU] = tempMenu;

	//creating the game options menu
	tempMenu = new Menu(string("ingameMenu"));
	tempMenu->AddSlider(new Slider(Vector2f(250, 150), 400, string("Master Volume"), Setting::MASTER));
	tempMenu->AddSlider(new Slider(Vector2f(250, 245), 400, string("Music Volume"), Setting::MUSIC));
	tempMenu->AddSlider(new Slider(Vector2f(250, 340), 400, string("Effects Volume"), Setting::SHORT));
	tempMenu->AddButton(new Button(Vector2f(330, 420), 180, 55, string("Back"), GameState::GAMEMENU));
	menusMap[GameState::GAMEOPTIONS] = tempMenu;
}

void SceneManager::Update()
{
	ChangeScene();
	if (currentMenu != NULL)
		currentMenu->Update();

	//updating the gameWorld
	if (SceneChanger::GetInstance()->CurrentScene() == GameState::GAME && gameWorld != NULL)
		gameWorld->Update();
}

void SceneManager::Draw()
{
	//updating the gameWorld
	if ((SceneChanger::GetInstance()->CurrentScene() == GameState::GAME ||
		SceneChanger::GetInstance()->CurrentScene() == GameState::GAMEOPTIONS ||
		SceneChanger::GetInstance()->CurrentScene() == GameState::GAMEMENU
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
	if (SceneChanger::GetInstance()->SceneChanging()) {
		switch (SceneChanger::GetInstance()->CurrentScene()) {
		case(GameState::SPLASHSCREEN) :
			currentMenu = menusMap[GameState::SPLASHSCREEN];
			currentMenu->UpdateTransform();
			break;
		case(GameState::MENU) :
			currentMenu = menusMap[GameState::MENU];
			currentMenu->UpdateTransform();
			break;
		case(GameState::CONTINUEGAME) : 
			loadGame = true;
			SceneChanger::GetInstance()->ChangeScene(GameState::GAME);
			break;
		case(GameState::NEWGAME) : 
			loadGame = false;
			SceneChanger::GetInstance()->ChangeScene(GameState::GAME);
			break;
		case(GameState::GAME) : 
			currentMenu = menusMap[GameState::GAME];
			if (gameWorld == NULL) {
				if (loadGame)
					gameWorld = new World(true);
				else {
					gameWorld = new World(false);
				}
				AudioManager::GetInstance()->startMusic("backgroundMusic");
			}
			break;
		case(GameState::OPTIONS) :
			currentMenu = menusMap[GameState::OPTIONS];
			currentMenu->UpdateTransform();
			break;
		case(GameState::MULTIPLAYER) :
			currentMenu = menusMap[GameState::MULTIPLAYER];
			currentMenu->UpdateTransform();
			break;
		case(GameState::CONNECT) : 
			if (!connect) {
				NetworkPacket np;
				np.type = "Connection";
				Network::GetInstance()->SendPacket("149.153.102.56", np);
				connect = true;
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
		case(GameState::EXIT) :
			if (gameWorld != NULL) {
				gameWorld->SavePlayer();
			}
			window->close();
			break;
		}
	}
}
