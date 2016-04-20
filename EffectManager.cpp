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

	m_bloodEffectTexture = new Texture();
	m_bloodEffectTexture->loadFromFile("Sprites/bloodSplat.png");
	m_bloodEffectTexture->setSmooth(false);

	m_alienBloodEffectTexture = new Texture();
	m_alienBloodEffectTexture->loadFromFile("Sprites/alienBloodSplat.png");
	m_alienBloodEffectTexture->setSmooth(false);

	m_BloodSlashTexture = new Texture();
	m_BloodSlashTexture->loadFromFile("Sprites/bloodSlash.png");
	m_BloodSlashTexture->setSmooth(false);

	m_bloodHitTexture = new Texture();
	m_bloodHitTexture->loadFromFile("Sprites/bloodHit.png");
	m_bloodHitTexture->setSmooth(false);

	m_alienBloodHitTexture = new Texture();
	m_alienBloodHitTexture->loadFromFile("Sprites/alienBloodHit.png");
	m_alienBloodHitTexture->setSmooth(false);
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
	case(1) :
		effects.push_back(new Effect(m_bloodEffectTexture, pos, 5, 5, 1, 50, 50, 0.05, 0.35));
		break;
	case(2) :
		effects.push_back(new Effect(m_alienBloodEffectTexture, pos, 5, 5, 1, 50, 50, 0.05, 0.35));
		break;
	case(3) :
		effects.push_back(new Effect(m_BloodSlashTexture, pos, 5, 5, 1, 50, 50, 0.05, 0.8));
		break;
	case(5) :
		effects.push_back(new Effect(m_bloodHitTexture, pos, 5, 5, 1, 50, 50, 0.05, 1));
		break;
	case(6) :
		effects.push_back(new Effect(m_alienBloodHitTexture, pos, 5, 5, 1, 50, 50, 0.05, 1));
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