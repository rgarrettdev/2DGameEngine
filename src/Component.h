#ifndef COMPONENT_H
#define COMPONENT_H

#include "./Entity.h"

class Entity;

class Component
{
public:
	virtual ~Component() {}
	Entity* owner;
	virtual void Initialise() {};
	virtual void Update(float deltaTime) {}
	virtual void Render() {}

};
#endif
