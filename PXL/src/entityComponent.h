#pragma once

#include "transform.h"
#include "entity.h"

class EntityComponent
{
public:
	EntityComponent() : m_parent(0) {}
	virtual ~EntityComponent() {}

	virtual void update(float delta) {}

	inline Transform* getTransform() { return m_parent->getTransform(); }
	inline const Transform& getTransform() const { return *m_parent->getTransform(); }

	virtual void setParent(Entity* parent) { m_parent = parent; }

private:
	Entity* m_parent;

	EntityComponent(const EntityComponent& other) {}
	void operator=(const EntityComponent& other) {}
};

