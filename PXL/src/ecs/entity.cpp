
#include "entity.h"
#include "entityComponent.h"

 Entity::~Entity() {

	for (unsigned int i = 0; i < m_components.size(); i++)
		if (m_components[i])
			delete m_components[i];

	for (unsigned int i = 0; i < m_children.size(); i++)
		if (m_children[i])
			delete m_children[i];
}

Entity Entity::addEntity(Entity & child) {

	m_children.push_back(child);
	return this;
}

Entity Entity::addComponent(EntityComponent & component) {

	m_components.push_back(component);
	return this;
}

void Entity::update(float delta) {

	for (unsigned int i = 0; i < m_components.size(); i++)
		m_components[i]->update(delta);
}

