#include "Slider.h"

Slider::Slider(Vector2f pos, int length, string & sliderName, Setting s)
{
	setting = s;
	barLength = length;
	m_barPos = pos;
	offset = m_barPos;
	value = 100;
	LoadAssets(sliderName);
}

void Slider::LoadAssets(string & sliderName)
{
	if (!m_barTexture.loadFromFile("Sprites/sliderBar.png")) {
		cout << "Could not find the image in location" << endl;
	}

	m_barTexture.setSmooth(false);
	m_barSprite.setTexture(m_barTexture);
	m_barSprite.setTextureRect(sf::IntRect(0, 0, m_barTexture.getSize().x, m_barTexture.getSize().y));
	float scaleX = barLength / m_barTexture.getSize().x;
	m_barSprite.setScale(scaleX, 1);
	m_barSprite.setPosition(m_barPos); 

	if (!m_slideTexture.loadFromFile("Sprites/sliderSlide.png")) {
		cout << "Could not find the image in location" << endl;
	}

	m_slideTexture.setSmooth(false);
	m_slideSprite.setTexture(m_slideTexture);
	m_slideSprite.setTextureRect(sf::IntRect(0, 0, m_slideTexture.getSize().x, m_slideTexture.getSize().y));
	m_slideSprite.setPosition(m_barPos.x + barLength - (barLength / 10), m_barPos.y); 

	//setting the text inside the button
	if (!font.loadFromFile("metro.otf"))
	{
		// error...
	}

	text.setFont(font);
	text.setString(sliderName);
	text.setCharacterSize(32);
	text.setColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(m_barPos.x, m_barPos.y - 40);
}

void Slider::Update()
{
	MoveSlide(); 
}

void Slider::Draw()
{
	window->draw(m_barSprite);
	window->draw(m_slideSprite);
	window->draw(text);
}

void Slider::MoveSlide()
{
	Vector2i mousePos = Mouse::getPosition(*window);
	//used to convert to view coordinates
	sf::Vector2f worldMousePos = window->mapPixelToCoords(mousePos);

	//checking if mouse is over the button
	float tempX = m_slideSprite.getPosition().x;
	float tempY = m_slideSprite.getPosition().y;
	Vector2f size = Vector2f(50, 50);

	//limited by the bar size and position
	if (worldMousePos.x > tempX && worldMousePos.x < tempX + size.x &&
		worldMousePos.y > tempY && worldMousePos.y < tempY + size.y &&
		Mouse::isButtonPressed(Mouse::Left)) {
		if (worldMousePos.x > (m_barPos.x + size.x / 2) && worldMousePos.x < (m_barPos.x + barLength - size.x / 2))
			m_slideSprite.setPosition(Vector2f(worldMousePos.x - 25, m_slideSprite.getPosition().y));
	} 

	value = ((m_slideSprite.getPosition().x - m_barPos.x) / barLength) * 100;
	SettingsManager::GetInstance()->SetSetting(setting, value);
}

void Slider::UpdateTransform()
{
	View temp = window->getView();
	Vector2f vPos = temp.getCenter();
	Vector2f vSize = temp.getSize();
	vPos.x -= vSize.x / 2;
	vPos.y -= vSize.y / 2;
	m_barPos.x = vPos.x + offset.x;
	m_barPos.y = vPos.y + offset.y;

	m_barSprite.setPosition(m_barPos.x, m_barPos.y);
	text.setPosition(m_barPos.x, m_barPos.y - 40);
	m_slideSprite.setPosition(m_barPos.x + barLength - (barLength / 10), m_barPos.y); 
}
