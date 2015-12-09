#include "SceneManager.h" 

SceneManager::SceneManager()
{
	state = GameState::SPLASHSCREEN;
	CreateMenus(); 
}

void SceneManager::CreateMenus()
{
	Menu* tempMenu = new Menu(string("splashMenu"));  
	tempMenu->AddButton(new Button(Vector2f(1050, 640), 200, 80, string("Continue...")));	
	menus.push_back(std::pair<int, Menu*>(0, tempMenu));
	currentMenu = std::pair<int, Menu*>(0, tempMenu);

	tempMenu = new Menu(string("normalMenu"));
	tempMenu->AddButton(new Button(Vector2f(1050, 400), 200, 80, string("Start Game")));
	tempMenu->AddButton(new Button(Vector2f(1050, 520), 200, 80, string("Options")));
	tempMenu->AddButton(new Button(Vector2f(1050, 640), 200, 80, string("Exit")));
	menus.push_back(std::pair<int, Menu*>(1, tempMenu));
}

void SceneManager::Update()
{
	ChangeScene();
	currentMenu.second->Update();
}

void SceneManager::Draw()
{
	currentMenu.second->Draw();
}

void SceneManager::ChangeScene()
{
	int size = menus.size();
	if (SceneChanger::GetInstance()->SceneChanging() == 1) {
		for (int i = 0; i < size; i++) {
			if (currentMenu.first + 1== menus[i].first) {
				currentMenu.second = menus[i].second;
				break;
			}
		}
	}
	if (SceneChanger::GetInstance()->SceneChanging() == 2) {
		for (int i = 0; i < size; i++) {
			if (currentMenu.first -1 == menus[i].first) {
				currentMenu.second = menus[i].second;
				break;
			}
		}
	}
}
