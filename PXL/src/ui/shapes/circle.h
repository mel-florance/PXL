#ifndef _CIRCLE_H
#define _CIRCLE_H


class Circle {
  public:
     Circle(const glm::vec2 & position, float radius);

     ~Circle();

    inline void setPosition(const glm::vec2 & position);

    inline glm::vec2 getPosition();

    inline void setRadius(float radius);

    inline float getRadius();

    bool intersects(const glm::vec2 & point);


  private:
    glm::vec2 m_position;

    float m_radius;

};
inline void Circle::setPosition(const glm::vec2 & position) {
}

inline glm::vec2 Circle::getPosition() {
}

inline void Circle::setRadius(float radius) {
}

inline float Circle::getRadius() {
}

#endif
