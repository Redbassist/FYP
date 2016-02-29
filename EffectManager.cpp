#include "EffectManager.h"
#include "Effect.h"

static bool instanceFlag = false;
static EffectManager* instance = NULL;

EffectManager::EffectManager()
{
	LoadAssets();
}

EffectManager * EffectManager::GetInstance()
{

	if (!instanceFlag) {
		instance = new EffectManager();
		instanceFlag = true;
	}
	return instance;
}

void EffectManager::LoadAssets()
{
	m_smokeEffectTexture = new Texture();
	m_smokeEffectTexture->loadFromFile("Sprites/smokeEffect.png"); 
	m_smokeEffectTexture->setSmooth(false);
}

void EffectManager::Draw()
{
	sf::Time frameTime = frameClock.restart();
	int size = effects.size();
	for (int i = 0; i < size; i++) {
		effects[i]->DrawEffect(frameTime);
	}
	RemoveEffects();
}

void EffectManager::PlayEffect(int type, Vector2f pos)
{
	int temp = 0;
	switch (type) {
	case(0) :
		effects.push_back(new Effect(m_smokeEffectTexture, pos, 10, 10, 1, 128, 128, 0.1, 0.1));
		break;
	}
}

void EffectManager::RemoveEffects()
{
	int size = effects.size();
	for (int i = 0; i < size; i++) {
		if (effects[i]->IsComplete()) {
			delete effects[i];
			effects.erase(effects.begin() + i);
			size = effects.size();
			i--;
		}
	}
}