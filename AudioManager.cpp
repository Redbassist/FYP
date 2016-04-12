#include "AudioManager.h"

static bool instanceFlag = false;
static AudioManager* instance = NULL;

AudioManager* AudioManager::GetInstance() {
	if (!instanceFlag) {
		instance = new AudioManager();
		instanceFlag = true;
	}
	return instance;
}

AudioManager::AudioManager() : mUpdated(0)
{
	mCurrentSong = NULL;
}

AudioManager::~AudioManager()
{
	for (auto it = mPlaying.begin(); it != mPlaying.end(); mPlaying.erase(it++))
		delete *it;
	for (auto it = mMusic.begin(); it != mMusic.end(); mMusic.erase(it++))
		delete it->second;
}

void AudioManager::setListener(const sf::Vector2f& pos, float dir)
{
	//convert dir to degrees!  
	sf::Listener::setPosition(pos.x, pos.y, 0);  
	sf::Listener::setDirection(cos(dir), sin(dir), 0);
	sf::Listener::setUpVector(sf::Vector3f(0, 0, 1));
}


void AudioManager::playSound(const std::string& name, const sf::Vector2f& pos)
{
	//checking if there are any buffers for the sound already
	bool loaded = mBuffers.count(name) > 0;
	sf::SoundBuffer& buf = mBuffers[name];
	if (!loaded)
		if (!buf.loadFromFile("Sounds/" + name + ".ogg"))
		{
			mBuffers.erase(name);
			return;
		}

	sf::Sound* snd = new sf::Sound();
	snd->setBuffer(buf);

	if (pos != sf::Vector2f())
	{
		snd->setRelativeToListener(false);
		snd->setPosition(pos.x, pos.y, 0); 
	}

	//use later to set the volume of the music using SETTINGS
	snd->setVolume(SettingsManager::GetInstance()->EffectVolume());
	snd->setMinDistance(500);
	snd->setAttenuation(33);
	snd->play();

	mPlaying.push_back(snd);
}

void AudioManager::playVoice(const sf::Vector2f & pos)
{
	string name = "test";
	//checking if there are any buffers for the sound already
	bool loaded = mBuffers.count(name) > 0;
	sf::SoundBuffer& buf = mBuffers[name];
	if (!loaded)
		if (!buf.loadFromFile("test.wav"))
		{
			mBuffers.erase(name);
			return;
		}

	sf::Sound* snd = new sf::Sound();
	snd->setBuffer(buf);

	if (pos != sf::Vector2f())
	{
		snd->setRelativeToListener(false);
		snd->setPosition(pos.x, pos.y, 0);
	}

	//use later to set the volume of the music using SETTINGS
	snd->setVolume(SettingsManager::GetInstance()->EffectVolume());

	snd->play();

	mPlaying.push_back(snd);
}

void AudioManager::addMusic(const std::string& name)
{
	sf::Music* m;
	if (!mMusic.count(name) > 0) {
		mMusic[name] = new sf::Music();
		m = mMusic[name];

		if (!m->openFromFile("Sounds/" + name + ".ogg"))
		{
			mMusic.erase(name);
			return;
		}
	}
}

void AudioManager::startMusic(const std::string& name)
{
	if (mCurrentSong != NULL && mCurrentSong->getStatus() != sf::Music::Stopped)
		mCurrentSong->stop();

	if (!mMusic.count(name) > 0) {
		std::cout << "Adding music to game: " + name << endl;
		addMusic(name); 
	} 
	mCurrentSong = mMusic[name];
	mCurrentSong->setLoop(true);
	mCurrentSong->play();
}
void AudioManager::stopMusic()
{
	mCurrentSong->stop();
	mCurrentSong = NULL;
}

void AudioManager::update()
{  
	sf::Listener::setGlobalVolume(SettingsManager::GetInstance()->MasterVolume());

	if (mCurrentSong != NULL)
		mCurrentSong->setVolume(SettingsManager::GetInstance()->MusicVolume());

	for (auto it = mPlaying.begin(); it != mPlaying.end();)
	{
		if ((*it)->getStatus() == sf::Sound::Stopped)
		{
			delete *it;
			mPlaying.erase(it++);
		}
		else
			++it;
	} 
}