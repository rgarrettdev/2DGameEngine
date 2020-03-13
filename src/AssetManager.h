#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "./FontManager.h"
#include "./TextureManager.h"
#include "./EntityManager.h"
#include "./SoundManager.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class AssetManager
{
public:
	AssetManager(EntityManager* manager);
	~AssetManager();
	void AddTexture(std::string textureID, const char* fileName);
	SDL_Texture* GetTexture(std::string textureID);
	void DestroyData(); //Can clear data stored when swithcing levels.
	void AddFont(std::string fontID, const char* fileName, int fontSize);
	TTF_Font* GetFont(std::string fontID);
	void AddMusic(std::string musicID, const char* fileName);
	Mix_Music* GetMusic(std::string musicID);

private:
	EntityManager* manager;

	/*std::map is a sorted associative container than contains key-value pairs. */
	std::map<std::string, SDL_Texture*> textures; //This will contain the texures for the asset manager to use.
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, Mix_Music*> music;
};

#endif // !ASSETMANAGER_H

