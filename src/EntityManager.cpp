#include "./EntityManager.h"

void EntityManager::DestroyData() {
	for (auto& entity: entities)
	{
		entity->Destroy();
	}
}
//Loop vector of entity and update all entities.
void EntityManager::Update(float deltaTime) {
	for (auto& entity: entities)
	{
		entity->Update(deltaTime);
	}
}
//Loop vector of entity and render all entities.
void EntityManager::Render() {
	for (auto& entity: entities) {
		entity->Render();
	}
}

bool EntityManager::HasNoEntities() {
	return entities.size() == 0;
}
//Create a new entity, instatinate that entity, then add to vector of entities.
Entity& EntityManager::AddEntity(std::string entityName) {
	Entity* entity = new Entity(*this, entityName);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const{ //used for debugging the data structure.
	return entities;
}

unsigned int EntityManager::GetEntityCount() { //used for debugging the data structure.
	return entities.size();
}