#ifndef _ENTITYCOMPONENT_H
#define _ENTITYCOMPONENT_H


class Transform;
class Entity;

class EntityComponent {
  public:
    inline  EntityComponent();

    inline virtual  ~EntityComponent();

    inline virtual void update(float delta);

    inline Transform getTransform();

    inline Transform getTransform() const;

    inline virtual void setParent(Entity & parent);


  private:
    Entity * m_parent;

    inline  EntityComponent(const EntityComponent & other);

    inline void operator =(const EntityComponent & other);

};
inline  EntityComponent::EntityComponent() {
}

inline  EntityComponent::~EntityComponent() {
}

inline void EntityComponent::update(float delta) {
}

inline Transform EntityComponent::getTransform() {
}

inline Transform EntityComponent::getTransform() const {
}

inline void EntityComponent::setParent(Entity & parent) {
}

inline  EntityComponent::EntityComponent(const EntityComponent & other) {
}

inline void EntityComponent::operator =(const EntityComponent & other) {
}

#endif
