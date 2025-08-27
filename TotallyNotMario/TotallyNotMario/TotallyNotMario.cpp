// TotallyNotMario.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Enums.h"
#include "ResourceLoader.h"
#include "InputSystem.h"
#include "RenderSystem.h"
#include "EntityPhysics.h"
#include "SoundPlayer.h"
#include "MusicPlayer.h"
#include "GameManager.h"


using namespace std;

//Constants
const string  TEXTURE_RESOURCE_MAPPING      = "Assets/Mappings/TextureAssetMapping.csv";
const string  TILE_RESOURCE_MAPPING         = "Assets/Mappings/LevelTiles_JSON/LevelTiles_JSON.txt";
const string  SOUND_FX_RESOURCE_MAPPING     = "Assets/Mappings/SoundFXAssetMapping.csv";
const string  MUSIC_FILE_PATH               = "Assets/Music/background-music.mp3";

int main()
{

    ResourceLoader& resourceLoader = ResourceLoader::instance();
    RenderSystem renderSystem;
    EntityPhysics entityPhysics;
    SoundPlayer soundPlayer;
    InputSystem  inputSystem(&entityPhysics,&soundPlayer);   
    MusicPlayer  musicPlayer(MUSIC_FILE_PATH);
    GameManager gameManager(TEXTURE_RESOURCE_MAPPING, TILE_RESOURCE_MAPPING,SOUND_FX_RESOURCE_MAPPING,renderSystem,inputSystem,entityPhysics,soundPlayer);

    //Main game lop call 
    gameManager.RunGame();
}


