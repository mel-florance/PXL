#pragma once

#include <vector>

#include "../core/transform.h"
#include "../materials/material.h"

class EntityComponent;

class Entity
{
public:
	Entity() {}
	virtual ~Entity();

	Entity* addEntity(Entity* child);
	Entity* addComponent(EntityComponent* component);

	inline Transform* getTransform() { return &m_transform; }


	inline std::vector<class Entity*> getChildren() { return m_children; }
	inline std::vector<class EntityComponent*> getComponents() { return m_components; }

private:
	std::vector<class Entity*> m_children;
	std::vector<class EntityComponent*> m_components;

	Transform m_transform;


	void update(float delta);

	Entity(const Entity& other) {}
	void operator=(const Entity& other) {}
};

