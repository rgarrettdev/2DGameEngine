#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "./Entity.h"
#include "./Component.h"
#include <vector>
#include <iostream>

class EntityManager
{
public:
	void DestroyData(); //Destroys all entites.
	void Update(float deltaTime);
	void Render();
	bool HasNoEntities(); //Getter to check if there are no entities in the list of entities.
	Entity& AddEntity(std::string entityName); //Adds entities to the system, returns a reference to a entity.
	std::vector<Entity*> GetEntities() const; //Returns a list of all entites.
	unsigned int GetEntityCount(); //Returns the number of entities.
	void ListAllEntities() const;
private:
	std::vector<Entity*> entities;

};
#endif
