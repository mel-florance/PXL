#ifndef _RECT_H
#define _RECT_H


class Rect {
  public:
     Rect(const glm::vec2 & position, const glm::vec2 & size);

     ~Rect();

    inline void setPosition(const glm::vec2 & position);

    inline void incrementPosition(const glm::vec2 & position);

    inline glm::vec2 getPosition();

    inline void setSize(const glm::vec2 & size);

    inline glm::vec2 getSize();

    bool intersects(const glm::vec2 & point);

    bool intersects(Rect & rect);

    inline void print();


  private:
    glm::vec2 m_position;

    glm::vec2 m_size;

};
inline void Rect::setPosition(const glm::vec2 & position) {
}

inline void Rect::incrementPosition(const glm::vec2 & position) {
}

inline glm::vec2 Rect::getPosition() {
}

inline void Rect::setSize(const glm::vec2 & size) {
}

inline glm::vec2 Rect::getSize() {
}

inline void Rect::print() {
}

#endif
