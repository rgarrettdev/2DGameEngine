#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include "./Component.h"
#include "./EntityManager.h"

class EntityManager;
//class Component;

class Entity
{
public:
	Entity(EntityManager& manager); //Constructor.
	Entity(EntityManager& manager, std::string name); //Constructor with a specified name.
	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool IsActive() const; //Getter function.
	std::string name;

	//Generics used to add abritary components.
	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));

		newComponent->owner = this; //Entity.h is owner of the new component.
		components.emplace_back(newComponent);
		newComponent->Initialise();
		return *newComponent;
	}

private:
	EntityManager& manager;
	bool isActive;
	std::vector<Component*> components;
};

#endif
