#ifndef CONTROLCOMPONENT_H
#define CONTROLCOMPONENT_H

#include "../Engine.h"
#include "../EntityManager.h"
#include "./TransformComponent.h"
#include "./SpriteComponent.h"

class ControlComponent : public Component
{
public:
	std::string UpKey;
	std::string DownKey;
	std::string LeftKey;
	std::string RightKey;
	std::string ShootKey;
	TransformComponent *transform;
	SpriteComponent* sprite;

	ControlComponent() {

	}
	ControlComponent(std::string upKey, std::string downKey, std::string leftKey, std::string rightKey, std::string shootKey) {
		this->UpKey = GetSDLKeyStringCode(upKey);
		this->DownKey = GetSDLKeyStringCode(downKey);
		this->LeftKey = GetSDLKeyStringCode(leftKey);
		this->RightKey = GetSDLKeyStringCode(rightKey);
		this->ShootKey = GetSDLKeyStringCode(shootKey);
	}

	std::string GetSDLKeyStringCode(std::string key) {
		if (key.compare("up") == 0) return "1073741906"; //Returns string code from SDL.
		if (key.compare("down") == 0) return "1073741905"; //Returns string code from SDL.
		if (key.compare("left") == 0) return "1073741904"; //Returns string code from SDL.
		if (key.compare("right") == 0) return "1073741903"; //Returns string code from SDL.
		if (key.compare("space") == 0) return "32"; //Returns string code from SDL.
		return std::to_string(static_cast<int>(key[0]));
	}

	void Initialise() override {
		transform = owner->GetComponent<TransformComponent>();
		sprite = owner->GetComponent<SpriteComponent>();
	}

	void Update(float deltaTime) override {
		if (Engine::event.type == SDL_KEYDOWN)	//Allows control of sprites depending on key pressed.
		{
			std::string keyCode = std::to_string(Engine::event.key.keysym.sym);
			if (keyCode.compare(UpKey) == 0)
			{
				transform->velocity.y = -10;
				transform->velocity.x = 0;
				sprite->Play("UpAnimation");
			}
			if (keyCode.compare(DownKey) == 0)
			{
				transform->velocity.y = 10;
				transform->velocity.x = 0;
				sprite->Play("DownAnimation");
			}
			if (keyCode.compare(LeftKey) == 0)
			{
				transform->velocity.y = 0;
				transform->velocity.x = -10;
				sprite->Play("LeftAnimation");
			}
			if (keyCode.compare(RightKey) == 0)
			{
				transform->velocity.y = 0;
				transform->velocity.x = 10;
				sprite->Play("RightAnimation");
			}
			if (keyCode.compare(ShootKey) == 0)
			{
				sprite->Play("AttackAnimation");
				//TODO.. Shoot projectiles when shoot is pressed.
			}
		}
		if (Engine::event.type == SDL_KEYUP)
		{
			std::string keyCode = std::to_string(Engine::event.key.keysym.sym);
			if (keyCode.compare(UpKey) == 0)
			{
				transform->velocity.y = 0;
			}
			if (keyCode.compare(DownKey) == 0)
			{
				transform->velocity.y = 0;
			}
			if (keyCode.compare(LeftKey) == 0)
			{
				transform->velocity.x = 0;
			}
			if (keyCode.compare(RightKey) == 0)
			{
				transform->velocity.x = 0;
			}
			if (keyCode.compare(ShootKey) == 0)
			{
				//TODO..
			}
		}
	}
private:

};


#endif // !CONTROLCOMPONENT_H

