#ifndef PROJECTILECOMPONENT_H
#define PROJECTILECOMPONENT_H

#include <glm.hpp>
#include "../EntityManager.h"
#include "./TransformComponent.h"

class ProjectileComponent : public Component
{
public:
	ProjectileComponent(int speed, int angle, int range, bool continousEmission)
	{
		this->speed = speed;
		this->range = range;
		this->angleRad = glm::radians(static_cast<float>(angle)); //Conversion of degrees to radians.
		this->continousEmission = continousEmission;
	}

	void Initialise() override {
		transform = owner->GetComponent<TransformComponent>();
		origin = glm::vec2(transform->position.x, transform->position.y);
		//Get x position through cos of the angle, and y postion from the sin of the angle.
		transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed); 
	}

	void Update(float deltaTime) override {
		if (glm::distance(transform->position, origin) > range)
		{
			if (continousEmission)
			{
				//Allows the projectile to be set back to origin when range is exceeded.
				transform->position.x = origin.x;	
				transform->position.y = origin.y;
			}
			else
			{
				owner->Destroy(); //Destroys the entity when range is exceeded.
			}
		}
	}

private:
	TransformComponent* transform;
	glm::vec2 origin; 
	int speed;
	int range;
	float angleRad; //In randians
	bool continousEmission;
};

#endif // !PROJECTILECOMPONENT_H

