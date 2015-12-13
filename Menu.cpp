#include "Menu.h"

Menu::Menu(string& imageName)
{
	LoadAssets(imageName);
}

void Menu::LoadAssets(string& textureName)
{
	if (!m_texture.loadFromFile("Sprites/" + textureName + ".png")) {
		cout << "Could not find the image in location" << endl;
	}
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	float scaleX = 1280.0f / m_texture.getSize().x;
	float scaleY = 720.0f / m_texture.getSize().y;
	m_sprite.setScale(scaleX, scaleY);
}

void Menu::AddButton(Button * button)
{
	buttons.push_back(button);
}

void Menu::AddSlider(Slider * slider)
{
	sliders.push_back(slider);
}

void Menu::Update()
{
	int size = buttons.size();
	for (int i = 0; i < size; i++) {
		buttons[i]->Update();
	}
	size = sliders.size();
	for (int i = 0; i < size; i++) {
		sliders[i]->Update();
	}
}

void Menu::Draw()
{
	window->draw(m_sprite);
	
	int size = buttons.size();
	for (int i = 0; i < size; i++) {
		buttons[i]->Draw();
	}
	size = sliders.size();
	for (int i = 0; i < size; i++) {
		sliders[i]->Draw();
	}
}

void Menu::UpdateTransform()
{
	float scaleX = window->getView().getSize().x / m_texture.getSize().x;
	float scaleY = window->getView().getSize().y / m_texture.getSize().y;
	m_sprite.setScale(scaleX, scaleY);

	View temp = window->getView();
	Vector2f vPos = temp.getCenter();
	Vector2f vSize = temp.getSize();
	m_sprite.setPosition(vPos.x - vSize.x / 2, vPos.y - vSize.y / 2); 

	int size = buttons.size();
	for (int i = 0; i < size; i++) {
		buttons[i]->UpdateTransform();
	}
	size = sliders.size();
	for (int i = 0; i < size; i++) {
		sliders[i]->UpdateTransform();
	}
}
