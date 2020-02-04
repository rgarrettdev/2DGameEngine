#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "./TransformComponent.h"
#include "../Animation.h"

class SpriteComponent : public Component 
{

public:

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	TransformComponent* transform; //To keep track of the transform on the enitity.
	SpriteComponent(std::string assetTextureID) {
		isAnimated = false;
		isFixed = false;
		SetTexture(assetTextureID);
	}
	SpriteComponent(std::string id, int numFrames, int animationSpeed, bool hasDirection, bool isFixed) {
		isAnimated = true;
		this->numFrames = numFrames;
		this->animationSpeed = animationSpeed;
		this->isFixed = isFixed;

		if (hasDirection)
		{
			Animation downAnimation = Animation(1, numFrames, animationSpeed);
			Animation upAnimation = Animation(1,  numFrames, animationSpeed);
			Animation leftAnimation = Animation(3,  numFrames, animationSpeed);
			Animation rightAnimation = Animation(2, numFrames, animationSpeed);
			Animation attackAnimation = Animation(0, numFrames, animationSpeed);

			animations.emplace("DownAnimation", downAnimation);
			animations.emplace("UpAnimation", upAnimation);
			animations.emplace("LeftAnimation", leftAnimation);
			animations.emplace("RightAnimation", rightAnimation);
			animations.emplace("AttackAnimation", attackAnimation);

			this->animationIndex = 3;
			this->currentAnimationName = "RightAnimation";
		}
		else
		{
			Animation singleAnimation = Animation(0, numFrames, animationSpeed);
			animations.emplace("SingleAnimation", singleAnimation);
			this->animationIndex = 0;
			this->currentAnimationName = "SingleAnimation";
		}
		Play(this->currentAnimationName);

		SetTexture(id);
	}
	void Play(std::string animationName) {
		numFrames = animations[animationName].numFrames;
		animationIndex = animations[animationName].index;
		animationSpeed = animations[animationName].animationSpeed;
		currentAnimationName = animationName;
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
		if (isAnimated)
		{
			//How often the sourceRect moves to the right in the sprite sheet. Cycles till numFrames has been hit.
			sourceRect.x = (sourceRect.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames)); 
		}
		sourceRect.y = animationIndex * transform->height;
		destinationRect.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Engine::camera.y); // IF statement Prevents UI from moving off screen.
		destinationRect.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Engine::camera.x);
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
	bool isAnimated;
	int numFrames;
	int animationSpeed;
	bool isFixed;	//Used to fix an sprite, not matter what is happening with the camera.
	std::map<std::string, Animation> animations;
	std::string currentAnimationName;
	unsigned int animationIndex = 0;
};


#endif // !SPRITECOMPONENT_H

