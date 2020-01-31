#include "./AssetManager.h"

//In C++ you can have the constructor instantiate members.
AssetManager::AssetManager(EntityManager* manager) : manager(manager) {

}

AssetManager::~AssetManager() {

}

void AssetManager::DestroyData() {
	textures.clear();
}

void AssetManager::AddTexture(std::string textureID, const char* fileName) {
	//emplace inserts textureID and new texture into the map container.
	textures.emplace(textureID, TextureManager::LoadTexture(fileName));
}

SDL_Texture* AssetManager::GetTexture(std::string textureID) {
	return textures[textureID];
}