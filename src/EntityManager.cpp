#include "./EntityManager.h"
#include <iostream>
#include "./Collision.h"
#include "./Components/ColliderComponent.h"

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
	DestroyInactiveEntities();
}
void EntityManager::DestroyInactiveEntities() {
	for (int i = 0; i < entities.size(); i++)
	{
		if (!entities[i]->IsActive())
		{
			entities.erase(entities.begin() + i); //Erases element in position i.
		}
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

Entity* EntityManager::GetEntityByName(std::string entityName) const {
	for (auto* entity : entities)
	{
		if (entity->name.compare(entityName) == 0)
		{
			return entity;
		}
	}
	return NULL;
}
// worst case is O(n2) complexity. due to looping through outer loop "n" times and inner loop "n-1" operations.
CollisionType EntityManager::CheckCollisions() const {
	for (int i = 0; i < entities.size() - 1; i++) {
		auto& thisEntity = entities[i];
		if (thisEntity->HasComponent<ColliderComponent>()) {
			ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();
			for (int j = i + 1; j < entities.size(); j++) {
				auto& thatEntity = entities[j];
				if (thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>()) {
					ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
					if (Collision::CheckRectCollision(thisCollider->collider, thatCollider->collider)) {
						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("ENEMY") == 0) {
							return PLAYER_ENEMY_COLLISION;
						}
						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("PROJECTILE") == 0) {
							return PLAYER_PROJECTILE_COLLISION;
						}
						if (thisCollider->colliderTag.compare("ENEMY") == 0 && thatCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0) {
							return ENEMY_PROJECTILE_COLLISION;
						}
						if (thisCollider->colliderTag.compare("PLAYER") == 0 && thatCollider->colliderTag.compare("LEVEL_COMPLETE") == 0) {
							return PLAYER_LEVEL_COMPLETE_COLLISION;
						}
					}
				}
			}
		}
	}
	return NO_COLLISION;
}
