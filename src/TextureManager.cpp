#include "./TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
	SDL_Surface* surface = IMG_Load(fileName);
	printf(IMG_GetError()); //Prints if an error occured during image loading.

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destinationRect, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Engine::renderer, texture, &sourceRect, &destinationRect, 0.0, NULL, flip); //Draws texture to the target renderer.
}