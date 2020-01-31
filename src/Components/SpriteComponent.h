#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "./TransformComponent.h"

class SpriteComponent: public Component 
{

public:

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	TransformComponent* transform; //To keep track of the transform on the enitity.
	SpriteComponent(const char* fileName) {
		SetTexture(fileName);
	}
	void SetTexture(std::string assetTextureID) {
		texture = Engine::assetManager->GetTexture(assetTextureID);
	}
	void Initialise() override {
		transform = owner->GetComponent<TransformComponent>();
		sourceRect.y = 0;
		sourceRect.x = 0;
		sourceRect.h = transform->height;
		sourceRect.w = transform->width;

	}
	void Update(float deltaTime) override{
		destinationRect.y = (int)transform->position.y;
		destinationRect.x = (int)transform->position.x;
		destinationRect.h = transform->height * transform->scale;
		destinationRect.w = transform->width * transform->scale;
	}
	void Render() override {
		TextureManager::Draw(texture, sourceRect, destinationRect, spriteFlip);
	}
private:
	SDL_Texture* texture;
	SDL_Rect sourceRect;
	SDL_Rect destinationRect;

};


#endif // !SPRITECOMPONENT_H

