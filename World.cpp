#include "World.h"

World::World() {
	CreateAssets();
	CreateLevel();
}

void World::CreateAssets() {
	m_texture.loadFromFile("Sprites/background.png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
	m_sprite.setScale(Vector2f(0.4, 0.4));
	m_sprite.setPosition(0, 0);
}

void World::CreateLevel() {
	View view = View(FloatRect(0, 0, 1280, 720));
	view.zoom(0.7);
	window->setView(view);  

	for (auto layer = ml->GetLayers().begin(); layer != ml->GetLayers().end(); ++layer)
	{
		if (layer->name == "Player")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				player = new Player(Vector2f(object._Ptr->GetPosition()));
				break;
			}
		}

		if (layer->name == "Buildings")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				if (object._Ptr->GetName() == "House")
					houses.push_back(new House(Vector2f(object._Ptr->GetPosition()), &items, 0));
				else if (object._Ptr->GetName() == "House2") {
					houses.push_back(new House(Vector2f(object._Ptr->GetPosition()), &items, 1));
				}
				else if (object._Ptr->GetName() == "Shop") {
					houses.push_back(new House(Vector2f(object._Ptr->GetPosition()), &items, 2));
				}
				else if (object._Ptr->GetName() == "Cabin") {
					houses.push_back(new House(Vector2f(object._Ptr->GetPosition()), &items, 3));
				}
			}
		}

		if (layer->name == "Lights")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				fillers.push_back(new FillerObject(object._Ptr->GetPosition(), 0, object._Ptr->GetName(), true, true));
			}
		}
	}

} 

void World::Update() {
	player->Update();
}

void World::Draw() {
	//window->draw(m_sprite);  
	
	int size = houses.size();
	for (int i = 0; i < size; i++) {
		houses[i]->Draw();
	}

	//drawing the items
	size = items.size();
	for (int i = 0; i < size; i++) {
		if (items[i]->destroy) {
			delete items[i];
			items.erase(items.begin() + i);
			size = items.size();
			i--;
		}
		else
			items[i]->Draw();
	}

	player->Draw();

	size = fillers.size();
	for (int i = 0; i < size; i++) {
		fillers[i]->Draw();
	}
}
