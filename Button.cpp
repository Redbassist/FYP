#include "Button.h"

Button::Button(Vector2f pos, int width, int height, string& buttonText, GameState bF) :
	m_pos(pos), size(Vector2f(width, height)), function(bF) {
	offset = m_pos;
	LoadAssets(buttonText);
}

void Button::LoadAssets(string& buttonText) {
	if (!m_texture.loadFromFile("Sprites/button.png")) {
		cout << "Could not find the image in location" << endl;
	} 
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	m_sprite.setOrigin(Vector2f(size.x / 2, size.y / 2));
	scaleX = size.x / m_texture.getSize().x;
	scaleY = size.y / m_texture.getSize().y;
	m_sprite.setScale(scaleX, scaleY);
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
	text.setPosition(m_pos.x - (size.x / 2.5) * scaleX, m_pos.y - (size.y / 4) * scaleY);
}

void Button::Update() {
	CheckHover();
	CheckClick();
}

void Button::Draw() {
	if (hovering) {
		m_sprite.setScale(scaleX * 1.2f, scaleY * 1.2f);
		m_sprite.setColor(Color::Yellow);
		window->draw(m_sprite);
		window->draw(text);
	}
	else {
		m_sprite.setScale(scaleX, scaleY);
		m_sprite.setColor(Color::Blue);
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
		//signaling that the scene is changing
		if (!clicked) { 
			SceneChanger::GetInstance()->ChangeScene(function);
			clicked = true;
		}
	}
}

void Button::UpdateTransform()
{
	View temp = window->getView();
	Vector2f vPos = temp.getCenter();
	Vector2f vSize = temp.getSize();
	vPos.x -= vSize.x / 2;
	vPos.y -= vSize.y / 2;
	m_pos.x = vPos.x + offset.x;
	m_pos.y = vPos.y + offset.y;

	m_sprite.setPosition(m_pos.x, m_pos.y);
	text.setPosition(m_pos.x - size.x / 2.5, m_pos.y - size.y / 4);
}

