#include "World.h"
#include "Stalker.h"
#include "Inventory.h"

World::World(bool load) {
	loadedCharacrter = load;
	CreateAssets();
	if (loadedCharacrter) {
		LoadPlayer();
	}
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

	enemyManager = EnemyManager();
}

void World::CreateLevel() {
	View view = View(FloatRect(0, 0, 1280, 720));
	view.zoom(0.7);
	window->setView(view);

	for (auto layer = ml->GetLayers().begin(); layer != ml->GetLayers().end(); ++layer)
	{
		if (!loadedCharacrter) {
			if (layer->name == "Player")
			{
				for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
				{
					player = new Player(Vector2f(object._Ptr->GetPosition()));
					break;
				}
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
				else if (object._Ptr->GetName() == "CabinR") {
					houses.push_back(new House(Vector2f(object._Ptr->GetPosition()), &items, 3));
				}
				else if (object._Ptr->GetName() == "CabinL") {
					houses.push_back(new House(Vector2f(object._Ptr->GetPosition()), &items, 4));
				}
				else if (object._Ptr->GetName() == "Military") {
					houses.push_back(new House(Vector2f(object._Ptr->GetPosition()), &items, 5));
				}
				/*else if (object._Ptr->GetName() == "Enemy") {
					enemyManager.AddStalker(new Stalker(Vector2f(object._Ptr->GetPosition())));
				}*/
			}
		}

		if (layer->name == "Lights")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				fillers.push_back(new FillerObject(object._Ptr->GetPosition(), 0, object._Ptr->GetName(), true, true));
			}
		}

		if (layer->name == "Trees")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				trees.push_back(new Tree(object._Ptr->GetPosition()));
			}
		}
	}
}

void World::Update() {
	player->Update();
	enemyManager.Update(player);

	int size = trees.size();
	for (int i = 0; i < size; i++) {
		trees[i]->FadeOut(player->GetPosition());
	}
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

	enemyManager.Draw();

	player->Draw();

	size = fillers.size();
	for (int i = 0; i < size; i++) {
		fillers[i]->Draw();
	}

	size = trees.size();
	for (int i = 0; i < size; i++) {
		trees[i]->Draw();
	}
}

void World::SavePlayer()
{
	std::ofstream out;
	out.open("saveFile.txt", std::ofstream::out | std::ofstream::trunc);

	PlayerSaveData psd;

	psd.health = player->GetHealth();
	psd.hunger = player->GetHunger();
	psd.thirst = player->GetThirst();
	psd.position = player->GetPosition();
	psd.invItems = player->GetInventory()->GetItems();

	string saveData;
	saveData.append(to_string((int)psd.health) + "/");
	saveData.append(to_string((int)psd.hunger) + "/");
	saveData.append(to_string((int)psd.thirst) + "/");
	saveData.append(to_string((int)psd.position.x) + "/");
	saveData.append(to_string((int)psd.position.y) + "/");

	int size = psd.invItems.size();

	for (int i = 0; i < size; i++) {
		saveData.append(to_string(psd.invItems[i]->GetType()) + "/");
		saveData.append(to_string(psd.invItems[i]->GetSize()) + "/");
		saveData.append(to_string(psd.invItems[i]->GetAmmo()) + "/");
	}

	saveData.append("END");

	out << saveData;
}

void World::LoadPlayer()
{
	PlayerSaveData psd;

	string loadedData;
	ifstream myfile("saveFile.txt");
	if (myfile.is_open())
	{
		getline(myfile, loadedData);
		myfile.close();
	}

	stringstream ss;
	ss.str(loadedData);

	bool gotHealth = false;
	bool gotHunger = false;
	bool gotThirst = false;
	bool gotPosX = false;
	bool gotPosY = false;

	string segment;
	bool breakout = false;

	while (std::getline(ss, segment, '/') && !breakout)
	{
		if (segment == "END")
			breakout = true;
		else if (!gotHealth) {
			psd.health = stoi(segment.c_str());
			gotHealth = true;
		}
		else if (!gotHunger) {
			psd.hunger = stoi(segment.c_str());
			gotHunger = true;
		}
		else if (!gotThirst) {
			psd.thirst = stoi(segment.c_str());
			gotThirst = true;
		}
		else if (!gotPosX) {
			psd.position = Vector2f(stoi(segment.c_str()), 0);
			gotPosX = true;
		}
		else if (!gotPosY) {
			psd.position.y = stoi(segment.c_str());
			gotPosY = true;
		}
		else {
			int type = stoi(segment.c_str());
			std::getline(ss, segment, '/');
			int size = stoi(segment.c_str());
			std::getline(ss, segment, '/');
			int ammo = stoi(segment.c_str());
			psd.invItems.push_back(new Item(ItemType(type), size, ammo));
		}
	}
	ss.clear();

	player = new Player(psd.position, psd.health, psd.hunger, psd.thirst, psd.invItems);
}
