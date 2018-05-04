#ifndef _LIGHT_H
#define _LIGHT_H


class Light {
  public:
    inline  Light(const glm::vec3 & position = glm::vec3(), const glm::vec3 & color = glm::vec3(1.0f));

     ~Light();

    enum LightType {
      DIRECTIONAL,
      POINT,
      SPOT
    };

    inline virtual glm::vec3 getPosition();

    inline virtual void setPosition(const glm::vec3 & position);

    inline virtual glm::vec3 getColor();

    inline virtual void setColor(const glm::vec3 & color);

    inline virtual glm::vec3 getAttenuation();

    inline virtual void setAttenuation(const glm::vec3 & attenuation);

    inline virtual LightType getType();

    inline virtual void setType(LightType type);


  private:
    glm::vec3 m_position;

    glm::vec3 m_color;

    glm::vec3 m_attenuation;

    LightType m_type;

    float m_coneAngle;

    float m_coneDirection;

};
inline  Light::Light(const glm::vec3 & position, const glm::vec3 & color) {
}

inline glm::vec3 Light::getPosition() {
}

inline void Light::setPosition(const glm::vec3 & position) {
}

inline glm::vec3 Light::getColor() {
}

inline void Light::setColor(const glm::vec3 & color) {
}

inline glm::vec3 Light::getAttenuation() {
}

inline void Light::setAttenuation(const glm::vec3 & attenuation) {
}

inline Light::LightType Light::getType() {
}

inline void Light::setType(Light::LightType type) {
}

#endif
