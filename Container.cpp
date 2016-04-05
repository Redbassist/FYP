#include "Container.h" 

Container::Container(Vector2f pos, float rot, std::vector<Item*>* i, int type) :
	m_pos(pos), rotation(rot), items(i)
{
	open = false;
	invCols = 4;
	invRows = 5;
	invSize = 20;
	LoadAssets(type);
	SetupSlots();
	GenerateItems();
	createBox2dBody();
}

void Container::LoadAssets(int type) {
	m_texture.loadFromFile("Sprites/container.png");
	m_texture.setSmooth(false);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_texture.getSize().x, m_texture.getSize().y));
	m_sprite.setScale(Vector2f(0.45, 0.45));
	//offset for where the container is drawing
	offset.x = 0;

	if (type == 0) {
		m_shapeTexture.loadFromFile("Sprites/cupboard.png");
	}
	else if (type == 1) {
		m_shapeTexture.loadFromFile("Sprites/cupboard2.png"); 
	}
	else if (type == 2) {
		m_shapeTexture.loadFromFile("Sprites/shelf.png");
	}
	else if (type == 3) {
		m_shapeTexture.loadFromFile("Sprites/crate.png");
	}
	m_shapeTexture.setSmooth(false);
	m_shapeSprite.setTexture(m_shapeTexture);
	m_shapeSprite.setTextureRect(sf::IntRect(0, 0, m_shapeTexture.getSize().x, m_shapeTexture.getSize().y));
	m_shapeSprite.setOrigin(m_shapeTexture.getSize().x / 2, m_shapeTexture.getSize().y / 2);
	m_shapeSprite.setScale(Vector2f(0.7, 0.7));
	m_shapeSprite.setRotation(rotation);
}

void Container::SetupSlots() {
	//creates the number of slots desired in the arrangement specified in the constuctor
	int slotNumber = 1;
	int currentCol = 1;
	int currentRow = 1;

	for (int i = 0; i < invSize; i++) {
		ContainerSlot tempSlot;
		tempSlot.number = slotNumber++;
		if (currentCol > invCols) {
			currentCol = 1;
			currentRow++;
		}
		tempSlot.col = currentCol;
		tempSlot.row = currentRow;
		currentCol++;
		tempSlot.item = NULL;
		tempSlot.full = false;
		slots.push_back(tempSlot);
	}
}

void Container::GenerateItems() {
	int size = slots.size();
	Item* temp;

	for (int i = 0; i < size; i++) {
		int item = rand() % 20 + 0;
		int amount;
		if (item == 0) {
			temp = new Item(FOOD1, 1);
			AddItem(temp);
			items->push_back(temp);
			/*slots[i].item = new Item(FOOD1, 1); OLD WAY
			slots[i].full = true;
			slots[i].item->SlotNumber(i);
			items->push_back(slots[i].item);*/
		}
		else if (item == 1) {
			temp = new Item(WATER1, 1);
			AddItem(temp);
			items->push_back(temp);
		}
		else if (item == 2) {
			temp = new Item(WATER2, 1);
			AddItem(temp);
			items->push_back(temp);
		}
		else if (item == 3) {
			temp = new Item(AXE, 2);
			AddItem(temp);
			items->push_back(temp);
		}
		else if (item == 4) {
			temp = new Item(BAT, 2);
			AddItem(temp);
			items->push_back(temp);
		}
		else if (item == 5) {
			amount = rand() % 7 + 0;
			temp = new Item(PISTOL, 1, amount);
			AddItem(temp);
			items->push_back(temp);
		}
		else if (item == 6) {
			amount = rand() % 20 + 0;
			temp = new Item(AMMOPISTOL, 1, amount);
			AddItem(temp);
			items->push_back(temp);
		}
		else if (item == 7) {
			amount = rand() % 30 + 0;
			temp = new Item(RIFLE, 2, amount);
			AddItem(temp);
			items->push_back(temp);
		}
		else if (item == 8) {
			amount = rand() % 100 + 0;
			temp = new Item(AMMORIFLE, 1, amount);
			AddItem(temp);
			items->push_back(temp);
		}
		else if (item == 9) {
			amount = rand() % 6 + 0;
			temp = new Item(SHOTGUN, 2, amount);
			AddItem(temp);
			items->push_back(temp);
		}
		else if (item == 10) {
			amount = rand() % 8 + 0;
			temp = new Item(AMMOSHOTGUN, 1, amount);
			AddItem(temp);
			items->push_back(temp);
		}
	}

}

bool Container::AddItem(Item* item, Vector2f dropPos) {
	//this method will look through the slots in the container and find one that is free for the item

	Vector2f spritePos = m_sprite.getPosition();
	float height = m_sprite.getGlobalBounds().height;
	float width = m_sprite.getGlobalBounds().width;

	//make class method that does this!!! -v
	if ((dropPos.x > spritePos.x && dropPos.x < spritePos.x + width &&
		dropPos.y > spritePos.y && dropPos.y < spritePos.y + height) || dropPos == Vector2f()) {

		int size = slots.size();

		for (int i = 0; i < size; i++) {
			if (item->GetSize() == 1 && !slots[i].full) {
				slots[i].item = item;
				slots[i].item->SlotNumber(i);
				slots[i].full = true;
				break;
			}
			else if (item->GetSize() == 2 && !slots[i].full && !slots[i + 1].full && slots[i].col != invCols) {
				slots[i].item = item;
				slots[i].item->SlotNumber(i);
				slots[i].full = true;
				slots[i + 1].full = true;
				break;
			}
			else if (item->GetSize() == 2) {
				bool loop = true;
				while (loop) {
					if (i >= 0 && i < size - 1) {
						if (!slots[i].full && !slots[i + 1].full && slots[i].col != invCols) {
							slots[i].item = item;
							slots[i].item->SlotNumber(i);
							slots[i].full = true;
							slots[i + 1].full = true;
							loop = false;
						}
					}
					if (i < size - 1)
						i++;
					else
						loop = false;
				}
				break;
			}
		}
		return true;
	}
	return false;
}

bool Container::TakeItem(Item* item, int slot) {
	//will check all slots that are full until a slot is found where the dropping click was made 
	int slotNumber = slot;
	int size = slots.size();

	if (slots[slotNumber].item->GetSize() == 1) {
		slots[slotNumber].full = false;
		slots[slotNumber].item = NULL;
	}
	else {
		slots[slotNumber].full = false;
		slots[slotNumber + 1].full = false;
		slots[slotNumber].item = NULL;
	}
	return false;
}

void Container::Open() {
	open = true;
}

void Container::Close() {
	open = false;
}

bool Container::CheckOpen() {
	return open;
}

Item * Container::DragItem(Vector2f clickPos)
{
	int size = slots.size();
	for (int i = 0; i < size; i++) {
		if (slots[i].full == true && slots[i].item != NULL) {
			if (slots[i].item->CheckSprite(clickPos)) {
				return slots[i].item;
			}
		}
	}
	return NULL;
}

void Container::Draw() {
	//container that is visible on the ground
	m_shapeSprite.setPosition(Vector2f(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE));
	window->draw(m_shapeSprite);

	if (open) {
		if (offset.x < m_sprite.getGlobalBounds().width)
			offset.x += 40;
		//drawing the items in the inventory
	}

	else {
		if (offset.x > 0)
			offset.x -= 40;
	}
}

void Container::DrawUI()
{
	//opening and closing the container onto the screen. SLIDES.
	Vector2f center = window->getView().getCenter();
	Vector2f size = window->getView().getSize();

	m_sprite.setPosition(center.x + size.x / 2 - offset.x, center.y - size.y / 2);
	window->draw(m_sprite);

	if (open) {
		DrawItems();
	}
}

void Container::DrawItems() {
	//drawing the items in the right slots
	int size = slots.size();
	int invSlot = 1;
	int currentRow = 1;
	for (int i = 0; i < size; i++) {
		if (slots[i].item != NULL && slots[i].full == true)
			slots[i].item->DrawInContainer(m_sprite.getPosition(), m_sprite.getGlobalBounds(), slots[i].col, slots[i].row);
	}
}

void Container::createBox2dBody() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(m_pos.x / SCALE, m_pos.y / SCALE);
	bodyDef.userData = this;
	body = world->CreateBody(&bodyDef);
	b2PolygonShape box;
	box.SetAsBox((m_shapeSprite.getGlobalBounds().width / 2.0f) / SCALE, (m_shapeSprite.getGlobalBounds().height / 2.0f) / SCALE);
	fixtureDef.shape = &box;
	fixtureDef.density = 1;
	fixtureDef.isSensor = false;
	fixtureDef.userData = "Container";

	fixtureDef.filter.categoryBits = CONTAINER;
	fixtureDef.filter.maskBits = PLAYER | ENEMY;

	body->CreateFixture(&fixtureDef);
}
