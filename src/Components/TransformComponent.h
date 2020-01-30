#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../EntityManager.h"
#include <glm.hpp>
#include <SDL.h>
#include "../Engine.h"

class TransformComponent : public Component
{
public:
	glm::vec2 position;
	glm::vec2 velocity;
	int height;
	int width;
	int scale;

	TransformComponent(int posY, int posX, int velY, int velX, int EntityHeight, int EntityWidth, int EntityScale) {
		position = glm::vec2(posY, posX);
		velocity = glm::vec2(velY, velX);
		height = EntityHeight;
		width = EntityWidth;
		scale = EntityScale;
	}

	void Initialise() override{

	}
	void Update(float deltaTime) override {
		//TODO: Update the pos + vel * deltaTime
		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;
	}
	void Render() override {
		SDL_Rect transformRectangle
		{
			(int)position.x,
			(int)position.y,
			height,
			width
		};
		SDL_SetRenderDrawColor(Engine::renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(Engine::renderer, &transformRectangle);
	}
private:

};

#endif