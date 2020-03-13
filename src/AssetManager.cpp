#include "./AssetManager.h"

//In C++ you can have the constructor instantiate members.
AssetManager::AssetManager(EntityManager* manager) : manager(manager) {

}

AssetManager::~AssetManager() {

}

void AssetManager::DestroyData() {
	fonts.clear();
	textures.clear();
	music.clear();
}

void AssetManager::AddFont(std::string fontID, const char* fileName, int fontSize)
{
	fonts.emplace(fontID, FontManager::LoadFont(fileName, fontSize));
}

TTF_Font* AssetManager::GetFont(std::string fontID)
{
	return fonts[fontID];
}

void AssetManager::AddMusic(std::string musicID, const char* fileName)
{
	music.emplace(musicID, SoundManager::LoadMusic(fileName));
}

Mix_Music* AssetManager::GetMusic(std::string musicID)
{
	return music[musicID];
}

void AssetManager::AddTexture(std::string textureID, const char* fileName) {
	//emplace inserts textureID and new texture into the map container.
	textures.emplace(textureID, TextureManager::LoadTexture(fileName));
}

SDL_Texture* AssetManager::GetTexture(std::string textureID) {
	return textures[textureID];
}