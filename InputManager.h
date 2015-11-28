#pragma once
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_h

#include "stdafx.h"
#include "Globals.h"

using namespace sf;

class InputManager {
private:
	std::vector<std::pair<bool*, Keyboard::Key>> keyboardBinds;
	std::vector<std::pair<bool*, Keyboard::Key>> singlePressKeyboardBinds;
	std::vector<std::pair<bool*, Keyboard::Key>> pressedSinglePressKeyboardBinds;
	std::vector<std::pair<bool*, Mouse::Button>> mouseBinds;
	std::vector<std::pair<bool*, Mouse::Button>> singlePressMouseBinds;
	std::vector<std::pair<bool*, Mouse::Button>> pressedSinglePressMouseBinds;
	
public:
	InputManager();
	static InputManager* GetInstance();
	void Bind(bool*, Keyboard::Key);
	void Bind(bool*, Mouse::Button);
	void BindSingleKeyPress(bool*, Keyboard::Key);
	void BindSingleMousePress(bool*, Mouse::Button);
	void UpdateKeyStates();
	void UpdateMouseStates();
	void UpdateSinglePress();
	void Update();
};

#endif