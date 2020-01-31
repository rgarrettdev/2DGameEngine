#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <string>
#include "./TextureManager.h"
#include "./EntityManager.h"

class AssetManager
{
public:
	AssetManager(EntityManager* manager);
	~AssetManager();
	void AddTexture(std::string textureID, const char* fileName);
	SDL_Texture* GetTexture(std::string textureID);
	void DestroyData(); //Can clear data stored when swithcing levels.
private:
	EntityManager* manager;

	/*std::map is a sorted associative container than contains key-value pairs. */
	std::map<std::string, SDL_Texture*> textures; //This will contain the texures for the asset manager to use.
};

#endif // !ASSETMANAGER_H

