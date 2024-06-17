#include "SoundManager.h"

SoundManager::SoundManager() {
	masterVolume = 50;
	effektVolume = 100;
	musikVolume = 20;

	errorSound.sound.stop();
}

bool SoundManager::loadAllSounds()
{
	bool loadingFails = false;

	//if (!link_hurt_SB.loadFromFile("Sounds/Link/Link_Hurt.wav"))
		//loadingFails = true;

	return !loadingFails;
}

void SoundManager::changeBackgroundMusic(std::string musicPath)
{
	if (!backgroundMusic.openFromFile(musicPath))
	{
		return;
	}

	backgroundMusic.setVolume(musikVolume * masterVolume / 100);
	backgroundMusic.setLoop(true);

	backgroundMusic.play();
}

void SoundManager::setBackgroundMusicStatus(sf::Music::Status status)
{
	switch (status)
	{
	case sf::Music::Playing:
		backgroundMusic.play();
		break;
	case sf::Music::Paused:
		backgroundMusic.pause();
		break;
	case sf::Music::Stopped:
		backgroundMusic.stop();
		break;
	}
}

SoundManager::SoundObject* SoundManager::playSound(SoundName effekt, bool loop, bool parallel)
{
	if (soundList.size() > 256)
	{
		return &errorSound;
	}

	if (!parallel) 
		clearAllSounds();

	SoundObject* newSound = new SoundObject();

	newSound->sound.setBuffer(*getSoundBuffer(effekt));
	newSound->sound.setVolume(effektVolume * masterVolume / 100);

	if (loop) 
		newSound->sound.setLoop(true);

	newSound->sound.play();
	soundList.push_back(newSound);

	return newSound;
}

void SoundManager::clearAllSounds()
{
	for (auto cursor : soundList)
	{
		delete cursor;
	}

	soundList.clear();
}

void SoundManager::deleteStoppedSounds()
{
	std::list<SoundObject*>::iterator cursor;

	for (cursor = soundList.begin(); cursor != soundList.end(); ++cursor)
	{
		if ((*cursor)->sound.getStatus() != sf::Sound::Stopped)
		{
			continue;
		}

		try {
			delete* cursor;
			cursor = soundList.erase(cursor);

			if(cursor == soundList.end())
				break;
		} catch (const std::exception& e) {
				
		}
	}

}

void SoundManager::update()
{
	deleteStoppedSounds();
}

void SoundManager::setMasterVolume(int volume)
{
	if (volume >= 0 && volume <= 100) 
		masterVolume = volume;
	
	updateSoundVolume();
}

void SoundManager::setMusikVolume(int volume)
{
	if (volume >= 0 && volume <= 100)
		musikVolume = volume;
	
	updateSoundVolume();
}

void SoundManager::setEffektVolume(int volume)
{
	if (volume >= 0 && volume <= 100) 
		effektVolume = volume;
	
	updateSoundVolume();
}

int SoundManager::getMasterVolume()
{
	return masterVolume;
}

int SoundManager::getMusikVolume()
{
	return musikVolume;
}

int SoundManager::getEffektVolume()
{
	return effektVolume;
}

void SoundManager::updateSoundVolume()
{
	backgroundMusic.setVolume(musikVolume * masterVolume / 100);

	for (auto cursor : soundList)
	{
		cursor->sound.setVolume(effektVolume * masterVolume / 100);
	}
}

sf::SoundBuffer* SoundManager::getSoundBuffer(SoundName name)
{
	switch (name)
	{
	
	};

	return nullptr;
}

SoundManager::~SoundManager(void)
{
	setBackgroundMusicStatus(sf::Music::Stopped);
	clearAllSounds();
}
