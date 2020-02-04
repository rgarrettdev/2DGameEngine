#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include <SDL.h>
#include "../EntityManager.h"
#include "../AssetManager.h"
#include <glm.hpp>

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect sourceRect; //SDL_Rect are for the SDL_RenderCopyEx call.
	SDL_Rect destinationRect;
	glm::vec2 position;

	TileComponent(int sourceRectX, int sourceRectY, int y, int x, int tileSize, int tileScale, std::string assetTextureID) {
		texture = Engine::assetManager->GetTexture(assetTextureID);

		sourceRect.y = sourceRectY;
		sourceRect.x = sourceRectX;
		sourceRect.h = tileSize;
		sourceRect.w = tileSize;

		destinationRect.y = y;
		destinationRect.x = x;
		destinationRect.h = tileSize * tileScale;
		destinationRect.w = tileSize * tileScale;

		position.x = x;
		position.y = y;
	}
	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	void Update(float deltaTime) override {
		//Here is where we will manage tile positions based on camera control.
		destinationRect.x = position.x - Engine::camera.x;
		destinationRect.y = position.y - Engine::camera.y;
	}
	void Render() override {
		TextureManager::Draw(texture, sourceRect, destinationRect, SDL_FLIP_NONE);
	}
private:

};


#endif
