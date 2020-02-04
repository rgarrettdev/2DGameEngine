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

	for (int i = 0; i < NUM_LAYERS; i++)
	{
		for (auto& entity: GetEntitiesByLayer(static_cast<LayerType>(i)))
		{
			entity->Render();
		}
	}
}

bool EntityManager::HasNoEntities() {
	return entities.size() == 0;
}
//Create a new entity, instatinate that entity, then add to vector of entities.
Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
	Entity* entity = new Entity(*this, entityName, layer);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const { //used for debugging the data structure.
	return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
	std::vector<Entity*> selectedEntities;
	for (auto& entity: entities)
	{
		if (entity->layer == layer) {	//if layer matches add entity to vector.
			selectedEntities.emplace_back(entity); 
		}
	}
	return selectedEntities;
}
unsigned int EntityManager::GetEntityCount() { //used for debugging the data structure.
	return entities.size();
}

void EntityManager::ListAllEntities() const {
	unsigned int i = 0;
	for (auto& entity: entities)
	{
		std::cout << "Entity[" << i << "];" << entity->name << std::endl;
		entity->ListAllComponents();
		i++;
	}
}