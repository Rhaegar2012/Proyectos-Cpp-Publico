#pragma once
#ifndef SOUND_PLAYER_H
#define SOUND_PLAYER_H
#include"ResourceLoader.h"
#include"Enums.h"
#include"Entity.h"
#include"Observer.h"
#include<SFML/Audio.hpp>
#include<iostream>
#include<string>
#include<map>

using namespace std;

class SoundPlayer:public Observer<Entity,Events,SoundFXResourceID>
{
	private:

		//Constants
		const map<SoundFXResourceID, string> soundFileMap = { {JUMP,"jumpSoundFx"},{SQUISH,"squishSoundFx"},{DIE,"dieSoundFx"},{COIN,"coinSoundFx"}};


		//Components
		string currentSoundFile;
		unique_ptr<sf::Sound> currentSound;
		ResourceLoader& resourceLoader = ResourceLoader::instance();
		

		//Private methods
		void SetSoundFile(SoundFXResourceID soundType);
		void PlaySound();

	public:
		SoundPlayer();
		void SetSound(unique_ptr<sf::Sound> sound);
		void OnNotify(Entity& entity, Events event, SoundFXResourceID soundType) override;
};
#endif

