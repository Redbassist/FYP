#include "Button.h"

Button::Button(Vector2f pos, int width, int height, string& buttonText) : m_pos(pos), size(Vector2f(width, height)) {
	LoadAssets(buttonText);
}

void Button::LoadAssets(string& buttonText) {
	if (!m_texture.loadFromFile("Sprites/button.png")) {
		cout << "Could not find the image in location" << endl;
	} 
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
	m_sprite.setOrigin(Vector2f(size.x / 2, size.y / 2));
	m_sprite.setPosition(m_pos);

	//setting the text inside the button
	if (!font.loadFromFile("metro.otf"))
	{
		// error...
	}

	text.setFont(font);	
	text.setString(buttonText);
	text.setCharacterSize(32); 
	text.setColor(sf::Color::Black); 
	text.setStyle(sf::Text::Bold); 
	text.setPosition(m_pos.x - size.x / 2.5, m_pos.y - size.y / 4);
}

void Button::Update() {
	CheckHover();
	CheckClick();
}

void Button::Draw() {
	if (hovering) {
		m_sprite.setScale(Vector2f(1.2, 1.2));
		m_sprite.setColor(Color::Yellow);
		window->draw(m_sprite);
		window->draw(text);
	}
	else {
		m_sprite.setScale(Vector2f(1, 1));
		m_sprite.setColor(Color::White);
		window->draw(m_sprite);
		window->draw(text);
	}
}

void Button::CheckHover() {
	Vector2i mousePos = Mouse::getPosition(*window);
	//used to convert to view coordinates
	sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);

	//checking if mouse is over the button
	float tempX = m_pos.x - size.x / 2;
	float tempY = m_pos.y - size.y / 2;	

	if (worldMousePos.x > tempX && worldMousePos.x < tempX + size.x &&
		worldMousePos.y > tempY && worldMousePos.y < tempY + size.y) {
		hovering = true;
	}
	else
		hovering = false;
}

void Button::CheckClick() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && hovering)
	{
		cout << "Button Clicked" << endl;
	}
}

