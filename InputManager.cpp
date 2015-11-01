#include "InputManager.h"

InputManager::InputManager()
{
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

void InputManager::Update() {
	UpdateKeyStates();
	UpdateMouseStates();
}

void InputManager::UpdateKeyStates() {
	//updating states of the keyboard bound bools
	int size = keyboardBinds.size();
	
	for (int i = 0; i < size; i++) {
		//setting the bool to false before checking what it's state is (RESET)
		*keyboardBinds[i].first = false;
		if ( Keyboard::isKeyPressed(keyboardBinds[i].second)) {
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
