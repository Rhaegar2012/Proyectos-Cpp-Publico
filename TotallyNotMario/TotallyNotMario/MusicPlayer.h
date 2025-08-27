#pragma once
#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H
#include"ResourceLoader.h"
#include<iostream>
#include<string>
#include<SFML/Audio.hpp>
class MusicPlayer
{
	private:
		string musicFileName;
		sf::Music music;

	public:
			MusicPlayer(string fileName);

};
#endif;

