#pragma once 
#include "stdafx.h"

using namespace sf;

enum class Setting {MASTER, MUSIC, EFFECT};

class SettingsManager
{
public:
	SettingsManager(); 

	static SettingsManager* GetInstance();
	float MasterVolume();
	float MusicVolume();
	float EffectVolume();
	void SetSetting(Setting, float); 

private:
	float masterVolume;
	float effectsVolume;
	float musicVolume;
}; 
