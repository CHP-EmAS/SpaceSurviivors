#pragma once
#pragma once

#include "SFML/Audio.hpp"
#include <list>

class SoundManager 
{
public:
	SoundManager();

	struct SoundObject
	{
		sf::Sound sound;
		sf::SoundBuffer buffer;
	};

	enum SoundName
	{
		
	};

	bool loadAllSounds();

	void changeBackgroundMusic(std::string musicPath);
	void setBackgroundMusicStatus(sf::Music::Status status);

	SoundObject* playSound(SoundName effekt, bool loop = false, bool parallel = true);
	void clearAllSounds();

	void deleteStoppedSounds();

	void update();

	void setMasterVolume(int volume);
	void setMusikVolume(int volume);
	void setEffektVolume(int volume);

	int getMasterVolume();
	int getMusikVolume();
	int getEffektVolume();

	void updateSoundVolume();

	sf::SoundBuffer* getSoundBuffer(SoundName name);

	~SoundManager(void);
private:
	std::list<SoundObject*> soundList;
	SoundObject errorSound;

	//sf::SoundBuffer link_hurt_SB;

	sf::Music backgroundMusic;

	int masterVolume;
	int musikVolume;
	int effektVolume;
};


