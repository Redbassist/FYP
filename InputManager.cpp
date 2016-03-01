#include "InputManager.h"

static bool instanceFlag = false;
static InputManager* instance = NULL;

InputManager* InputManager::GetInstance() {
	if (!instanceFlag) {
		instance = new InputManager();
		instanceFlag = true;
	}
	return instance;
}

InputManager::InputManager() {
}

void InputManager::Bind(bool* action, Keyboard::Key key)
//storing the bind for keyboard inputs
{
	keyboardBinds.push_back(std::pair<bool*, Keyboard::Key>(action, key));
}

void InputManager::Bind(bool* action, Mouse::Button button)
//storing the bind for mouse inputs
{
	mouseBinds.push_back(std::pair<bool*, Mouse::Button>(action, button));
}

void InputManager::BindSingleKeyPress(bool* action, Keyboard::Key key)
//storing key press for key presses that are only checked once
{
	singlePressKeyboardBinds.push_back(std::pair<bool*, Keyboard::Key>(action, key));
}

void InputManager::BindSingleMousePress(bool* action, Mouse::Button button)
//storing key press for key presses that are only checked once
{
	singlePressMouseBinds.push_back(std::pair<bool*, Mouse::Button>(action, button));
}

void InputManager::Update() {
	UpdateKeyStates();
	UpdateMouseStates();
	UpdateSinglePress();
}

void InputManager::UpdateKeyStates() {
	//updating states of the keyboard bound bools
	int size = keyboardBinds.size();

	for (int i = 0; i < size; i++) {
		//setting the bool to false before checking what it's state is (RESET)
		*keyboardBinds[i].first = false;
		if (Keyboard::isKeyPressed(keyboardBinds[i].second)) {
			*keyboardBinds[i].first = true;
		}
	}
}

void InputManager::UpdateMouseStates() {
	//updating states of the mouse bound bools
	int size = mouseBinds.size();

	for (int i = 0; i < size; i++) {
		//setting the bool to false before checking what it's state is (RESET)
		*mouseBinds[i].first = false;
		if (Mouse::isButtonPressed(mouseBinds[i].second)) {
			*mouseBinds[i].first = true;
		}
	}
}

void InputManager::UpdateSinglePress() {
	int size;
	std::vector<std::pair<bool*, Keyboard::Key>>::iterator it;
	std::vector<std::pair<bool*, Keyboard::Key>>::iterator end;

	std::vector<std::pair<bool*, Mouse::Button>>::iterator it2;
	std::vector<std::pair<bool*, Mouse::Button>>::iterator end2;
	sf::Event event;
	// while there are pending events...
	while (window->pollEvent(event))
	{
		// check the type of the event...
		switch (event.type)
		{
			// key pressed
		case sf::Event::KeyPressed:
			it = singlePressKeyboardBinds.begin();
			end = singlePressKeyboardBinds.end();
			for (; it != end;) {
				if (event.key.code == it->second) {
					*it->first = true;
					pressedSinglePressKeyboardBinds.push_back(*it);
					it = singlePressKeyboardBinds.erase(it);
					end = singlePressKeyboardBinds.end(); 
				}
				else {
					it++;
				}
			}
			break;
			// key released
		case sf::Event::KeyReleased:
			it = pressedSinglePressKeyboardBinds.begin();
			end = pressedSinglePressKeyboardBinds.end();
			for (; it != end;) {
				if (event.key.code == it->second) {
					*it->first = false;
					singlePressKeyboardBinds.push_back(*it);
					it = pressedSinglePressKeyboardBinds.erase(it);
					end = pressedSinglePressKeyboardBinds.end();
				}
				else {
					it++;
				}
			}
			break;
			// mouse pressed
		case sf::Event::MouseButtonPressed:
			it2 = singlePressMouseBinds.begin();
			end2 = singlePressMouseBinds.end();
			for (; it2 != end2;) {
				if (event.key.code == it2->second) {
					*it2->first = true;
					pressedSinglePressMouseBinds.push_back(*it2);
					it2 = singlePressMouseBinds.erase(it2);
					end2 = singlePressMouseBinds.end();
				}
				else {
					it2++;
				}
			}
			break;
			// mouse released
		case sf::Event::MouseButtonReleased:
			it2 = pressedSinglePressMouseBinds.begin();
			end2 = pressedSinglePressMouseBinds.end();
			for (; it2 != end2;) {
				//*it2->first = false;
				if (event.key.code == it2->second) {
					singlePressMouseBinds.push_back(*it2);
					it2 = pressedSinglePressMouseBinds.erase(it2);
					end2 = pressedSinglePressMouseBinds.end();
				}
				else {
					it2++;
				}
			}
			break;
		}
	}
} 