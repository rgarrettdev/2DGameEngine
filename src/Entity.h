#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include "./Definitions.h"
#include "./Component.h"
#include "./EntityManager.h"
#include <typeinfo>

class EntityManager;
//class Component;

class Entity
{
public:
	Entity(EntityManager& manager); //Constructor.
	Entity(EntityManager& manager, std::string name, LayerType layer); //Constructor with a specified name.
	LayerType layer;
	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool IsActive() const; //Getter function.
	std::string name;

	void ListAllComponents() const;

	//Generics used to add abritary components.
	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));

		newComponent->owner = this; //Entity.h is owner of the new component.
		components.emplace_back(newComponent);
		//typeid() returns type indentication infromation at run time.
		componentType[&typeid(*newComponent)] = newComponent; //Keeps a map of all that are added components based on type.
		newComponent->Initialise();
		return *newComponent;
	}

	//Template used as generic way to get component types.
	template <typename T>
	T* GetComponent() {
		return static_cast<T*>(componentType[&typeid(T)]); //static cast to convert to a type pointer.
	}

	template <typename T>
	bool HasComponent() const {
		return componentType.count(&typeid(T)); //Returns a 1 if element with &typeid(T) is present in the map container. Returns 0 if not present.
	}
private:
	EntityManager& manager;
	bool isActive;
	std::vector<Component*> components;
	std::map<const std::type_info*, Component*> componentType; //This map keep track of type of components and points to the components.
};

#endif
