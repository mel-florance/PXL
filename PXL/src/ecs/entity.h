#ifndef _ENTITY_H
#define _ENTITY_H


#include "transform.h"

class EntityComponent;

class Entity {
  public:
    inline  Entity();

    virtual  ~Entity();

    Entity addEntity(Entity & child);

    Entity addComponent(EntityComponent & component);

    inline Transform getTransform();

    inline std::vector<class Entity*> getChildren();

    inline std::vector<class EntityComponent*> getComponents();


  private:
    class Entity* m_children;

    class EntityComponent* m_components;

    Transform m_transform;

    void update(float delta);

    inline  Entity(const Entity & other);

    inline void operator =(const Entity & other);

};
inline  Entity::Entity() {
}

inline Transform Entity::getTransform() {
}

inline std::vector<class Entity*> Entity::getChildren() {
}

inline std::vector<class EntityComponent*> Entity::getComponents() {
}

inline  Entity::Entity(const Entity & other) {
}

inline void Entity::operator =(const Entity & other) {
}

#endif
