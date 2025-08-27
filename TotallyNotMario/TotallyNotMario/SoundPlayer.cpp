#include "SoundPlayer.h"

SoundPlayer:: SoundPlayer()
{

}

void SoundPlayer::SetSound(unique_ptr<sf::Sound> sound)
{
	currentSound = move(sound);
}

void SoundPlayer::SetSoundFile(SoundFXResourceID soundType)
{
	currentSoundFile = soundFileMap.at(soundType);
	sf::SoundBuffer& soundBuffer = resourceLoader.GetSoundBuffer(currentSoundFile);
	auto newSound = make_unique<sf::Sound>(soundBuffer);
	SetSound(move(newSound));
}

void SoundPlayer::PlaySound()
{
	currentSound.get()->play();
}

void SoundPlayer::OnNotify(Entity& entity, Events event , SoundFXResourceID soundType)
{
	SetSoundFile(soundType);
	PlaySound();
}
