#ifndef _PARTICLE_H
#define _PARTICLE_H


class Particle {
  public:
     Particle(const glm::vec3 & position, const glm::vec3 & velocity, float gravity, float life, float rotation, float scale);

    inline glm::vec3 getPosition();

    inline void setPosition(const glm::vec3 & position);

    inline glm::vec3 getVelocity();

    inline void setVelocity(const glm::vec3 & velocity);

    inline float getScale();

    inline void setScale(float scale);

    bool update(double delta);

     ~Particle();


  private:
    glm::vec3 m_position;

    glm::vec3 m_velocity;

    float m_gravity;

    float m_life;

    float m_rotation;

    float m_scale;

    float m_elapsedTime;

};
inline glm::vec3 Particle::getPosition() {
}

inline void Particle::setPosition(const glm::vec3 & position) {
}

inline glm::vec3 Particle::getVelocity() {
}

inline void Particle::setVelocity(const glm::vec3 & velocity) {
}

inline float Particle::getScale() {
}

inline void Particle::setScale(float scale) {
}

#endif
