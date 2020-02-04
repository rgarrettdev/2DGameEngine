#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SDL.h>
#include "../Engine.h"
#include "../EntityManager.h"
#include "./TransformComponent.h"

class ColliderComponent : public Component
{
public:
	std::string colliderTag;
	SDL_Rect collider;
	SDL_Rect sourceRect;
	SDL_Rect destinationRect;
	TransformComponent* transform;

	ColliderComponent(std::string colliderTag, int x, int y, int width, int height) {
		this->colliderTag = colliderTag;
		this->collider = { x,y,width,height }; //Passing in values for the SDL_Rect struct.
	}

	void Initialise() override {
		if (owner->HasComponent<TransformComponent>()) {
			transform = owner->GetComponent<TransformComponent>();
			sourceRect = {0, 0, transform->width, transform->height};
			destinationRect = {collider.x, collider.y, collider.w, collider.h};
		}
	}

	void Update(float deltaTime) override {
		//Set collider x and y to transform x and y
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
		destinationRect.x = collider.x - Engine::camera.x;
		destinationRect.y = collider.y - Engine::camera.y;
	}
private:

};
#endif // !COLLIDERCOMPONENT_H

