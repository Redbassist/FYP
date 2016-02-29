#include "SettingsManager.h"

static bool instanceFlag = false;
static SettingsManager* instance = NULL;

SettingsManager::SettingsManager()
{
	masterVolume = 100;
	musicVolume = 100;
	effectsVolume = 100;
}

SettingsManager * SettingsManager::GetInstance()
{
	if (!instanceFlag) {
		instance = new SettingsManager();
		instanceFlag = true;
	}
	return instance;
}

float SettingsManager::MasterVolume()
{
	return masterVolume;
}

float SettingsManager::MusicVolume()
{
	return musicVolume;
}

float SettingsManager::EffectVolume()
{
	return effectsVolume;
}

void SettingsManager::SetSetting(Setting changingSetting, float value)
{
	switch (changingSetting) {
	case (Setting::MASTER) :
		masterVolume = value;
		break;
	case (Setting::MUSIC) :
		musicVolume = value;
		break;
	case (Setting::SHORT) :
		effectsVolume = value;
		break;
	}
} 
