#pragma once 
#include "stdafx.h"

using namespace sf;

class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	static AudioManager* GetInstance();

	void setListener(const sf::Vector2f& pos, float dir); 
	void playSound(const std::string& sound, const sf::Vector2f& pos = sf::Vector2f());
	void playVoice(const sf::Vector2f& pos = sf::Vector2f());

	void addMusic(const std::string& name);
	 
	void startMusic(const std::string&);
	void stopMusic();

	void update();

private: 
	float mUpdated;
	std::unordered_map<std::string, sf::SoundBuffer> mBuffers;
	sf::Music* mCurrentSong;
	std::unordered_map<std::string, sf::Music*> mMusic;
	std::list<sf::Sound*> mPlaying; 
};
