#include "SceneManager.h" 

SceneManager::SceneManager()
{
	state = GameState::SPLASHSCREEN;
	CreateMenus(); 
}

void SceneManager::CreateMenus()
{
	Menu* tempMenu = new Menu(string("splashMenu"));  
	tempMenu->AddButton(new Button(Vector2f(400, 100), 200, 80, string("Temp Button")));
	
	menus.push_back(tempMenu);
	currentMenu = tempMenu;
}

void SceneManager::Update()
{
	currentMenu->Update();
}

void SceneManager::Draw()
{
	currentMenu->Draw();
}

void SceneManager::LastMenu()
{
}

void SceneManager::NextMenu()
{
	cout << "Button Test" << endl;
}
