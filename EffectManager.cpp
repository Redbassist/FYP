#include "EffectManager.h"

static bool instanceFlag = false;
static EffectManager* instance = NULL;

EffectManager* EffectManager::GetInstance() {
	if (!instanceFlag) {
		instance = new EffectManager();
		instanceFlag = true;
	}
	return instance;
}
EffectManager::EffectManager()
{
	LoadAssets();
}

void EffectManager::LoadAssets()
{
}

void EffectManager::Draw()
{
}

void EffectManager::PlayEffect(EffectType type)
{
	switch (type) {
	case(EffectType::SPARK) :
		//effects.push_back(new Effect()
		break;
	}
}

void EffectManager::RemoveEffects()
{
}
