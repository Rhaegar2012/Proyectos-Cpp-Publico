#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H
#include "Enums.h"
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<iostream>
#include<fstream>
#include<nlohmann/json.hpp>
#include<sstream>
#include<map>
using namespace std;
using json = nlohmann::json;

class ResourceLoader
{
	private:
		

		ResourceLoader(){}
		//Singleton reference
		static ResourceLoader* instance_;
		//Constants
		const string JSON_LAYER_KEY			= "layers";
		const string JSON_MAP_NAME_KEY		= "name";
		const string JSON_MAP_POSITION_KEY  = "positions";
		
		//resource containers
		map<string, sf::Texture> textureMap;
		map<string, sf::SoundBuffer> soundFxMap;
		map<string, unique_ptr<sf::Music>> musicMap;
		map<string, vector<map<string, int>>> tileCoordinatesMap;

	
		
	public:

		static ResourceLoader& instance() 
		{
			static ResourceLoader* instance = new ResourceLoader();
			return *instance;
		}
		void LoadCSVResourceMapping(const string & resourceMappingPath , const ResourceType resourceType);
		void LoadTileCoordinatesMapping(const string& tileCoordinatesResource);
		map<string,sf::Texture>& GetTextureMapPointer();
		map<string, sf::SoundBuffer>* GetSoundFXMapPointer();
		map<string, unique_ptr<sf::Music>>* GetMusicMapPointer();
		map<string, vector<map<string, int>>>* GetTileCoordinatesMapPointer();
		sf::Texture& GetAnimationFrame(const string& animationFrameKey);
		sf::SoundBuffer& GetSoundBuffer(const string& soundBufferFileKey);
		

};
#endif

