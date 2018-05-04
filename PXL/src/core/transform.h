#ifndef _TRANSFORM_H
#define _TRANSFORM_H


class Transform {
  private:
    glm::vec3 m_position;

    glm::vec3 m_rotation;

    glm::vec3 m_scale;

    Transform * m_parent;

    mutable glm::mat4 m_parentMatrix;


  public:
    inline  Transform(const glm::vec3 & position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3 & rotation = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3 & scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);

    inline virtual  ~Transform();

    inline glm::mat4 getTransformation();

    inline glm::mat4 getParentMatrix();

    inline void setParent(Transform & parent);

    inline glm::vec3 getPosition();

    inline glm::vec3 getRotation();

    inline glm::vec3 getScale();

    inline void setPosition(glm::vec3 & position);

    inline void setRotation(glm::vec3 & rotation);

    inline void setScale(glm::vec3 & scale);

};
inline  Transform::Transform(const glm::vec3 & position, const glm::vec3 & rotation, const glm::vec3 & scale) {
}

inline  Transform::~Transform() {
}

inline glm::mat4 Transform::getTransformation() {
}

inline glm::mat4 Transform::getParentMatrix() {
}

inline void Transform::setParent(Transform & parent) {
}

inline glm::vec3 Transform::getPosition() {
}

inline glm::vec3 Transform::getRotation() {
}

inline glm::vec3 Transform::getScale() {
}

inline void Transform::setPosition(glm::vec3 & position) {
}

inline void Transform::setRotation(glm::vec3 & rotation) {
}

inline void Transform::setScale(glm::vec3 & scale) {
}

#endif
