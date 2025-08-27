#include "MusicPlayer.h"
MusicPlayer::MusicPlayer(string fileName)
{
	musicFileName = fileName;
	if(!music.openFromFile(musicFileName))
	{
		cout<<"Music file can't be played"<<endl;
	}
	else
	{
		music.play();
	}
	
}
