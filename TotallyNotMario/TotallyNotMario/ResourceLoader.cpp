#include "ResourceLoader.h"
//================================
//Behaviors
//================================

void ResourceLoader::LoadCSVResourceMapping(const string & resourceMappingPath , ResourceType resourceType)
{
	char delimiter = ',';
	ifstream file(resourceMappingPath);
	if (!file.is_open()) {
		throw runtime_error("Could not open file: " + resourceMappingPath);
	}

	string line;
	while(getline(file,line))
	{
		stringstream stream(line);
		string key;
		string resourcePath;
		sf::Texture texture;
		sf::SoundBuffer soundBuffer;
		if (!getline(stream, key, delimiter)) continue;
		if (!getline(stream, resourcePath, delimiter)) continue;
		
		switch (resourceType) 
		{
			case TEXTURE:
				if (!texture.loadFromFile(resourcePath))
				{
					throw runtime_error("Resource Loader - Texture failed to load " + resourcePath);
				}
				textureMap[key] = texture;
				break;
			case SOUNDFX:
				if(!soundBuffer.loadFromFile(resourcePath))
				{
					throw runtime_error("Resource Loader - SoundBuffer failed to load " + resourcePath);
				}
				soundFxMap[key] = soundBuffer;
				break;
			case MUSIC:
				//TODO
				break;
		}
	}
}

void ResourceLoader::LoadTileCoordinatesMapping(const string & tileCoordinatesResource)
{
	ifstream inFile(tileCoordinatesResource);

	if(!inFile.is_open())
	{
		throw runtime_error("Unable to open json file");
	}

	json jFile = json::parse(inFile);

	for(auto& coordinateMap :jFile[JSON_LAYER_KEY])
	{
		for(auto & coordinateSet :coordinateMap[JSON_MAP_POSITION_KEY])
		{
			tileCoordinatesMap[coordinateMap[JSON_MAP_NAME_KEY]].push_back(coordinateSet);
		}
	}
}

map<string, sf::Texture>& ResourceLoader:: GetTextureMapPointer()
{
	return textureMap;
}

map<string,sf::SoundBuffer> * ResourceLoader:: GetSoundFXMapPointer()
{
	return &soundFxMap;
}

map<string,unique_ptr<sf::Music>> * ResourceLoader::GetMusicMapPointer()
{
	return &musicMap;
}

map<string,vector<map<string,int>>>* ResourceLoader:: GetTileCoordinatesMapPointer()
{
	return &tileCoordinatesMap;
}

sf::Texture& ResourceLoader::GetAnimationFrame(const string& animationFrameKey)
{
	return textureMap.at(animationFrameKey);
}

sf::SoundBuffer& ResourceLoader::GetSoundBuffer(const string& soundBufferFileKey)
{
	return soundFxMap.at(soundBufferFileKey);
}


