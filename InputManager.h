#pragma once
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_h

#include <vector>
#include "SFML\Graphics.hpp"
using namespace sf;

class InputManager {
private: 
	std::vector<std::pair<bool*, Keyboard::Key>> keyboardBinds;
	std::vector<std::pair<bool*, Mouse::Button>> mouseBinds;
	
public:
	InputManager();
	void Bind(bool*, Keyboard::Key);
	void Bind(bool*, Mouse::Button);
	void UpdateKeyStates();
	void UpdateMouseStates();
	void Update();
};

#endif