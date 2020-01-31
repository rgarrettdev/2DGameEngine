#include "./Entity.h"

//In C++ you can have the constructor instantiate members.
Entity::Entity(EntityManager& manager) : manager(manager) {
	this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name) : manager(manager), name(name) {
	this->isActive = true;
}

void Entity::Update(float deltaTime) {
	for (auto& component: components) //Loop vector of component and update all components.
	{
		component->Update(deltaTime);
	}
}

void Entity::Render() {
	for (auto& component : components) { //Loop vector of component and render all components.
		component->Render();
	}
}
void Entity::Destroy() {
	this->isActive = false;
}
bool Entity::IsActive() const {
	return this->isActive;
}

void Entity::ListAllComponents() const {
	for (auto mapElement: componentType)
	{
		std::cout << " Component<" << mapElement.first->name() << ">" << std::endl;
	}
}