#ifndef _TPSCAMERA_H
#define _TPSCAMERA_H


#include "camera.h"

class Display;
class Mesh;

class TPSCamera : public Camera {
  public:
     TPSCamera(Display & window, Mesh & target, const glm::vec3 & position, const glm::vec3 & rotation, float fov, float aspect, float near, float far);

     ~TPSCamera();

    void onMouseMove(const glm::vec2 & mouse);

    void onMouseDown(const glm::vec3 & state);

    void onMouseUp(const glm::vec3 & state);

    void onKeyDown(const SDL_Keycode & keycode);

    void onKeyUp(const SDL_Keycode & keycode);

    void update(double delta);

    inline glm::vec3 getPosition();

    inline void setPosition(const glm::vec3 & position);

    inline glm::vec3 getRotation();

    inline void setRotation(const glm::vec3 & rotation);


  private:
    Mesh * m_target;

    glm::vec3 m_position;

    glm::vec3 m_rotation;

    glm::vec2 m_mouse;

    glm::vec2 m_oldMouse;

    double m_sensitivity;

    double m_delta;

    std::string, int m_keys;

    std::string, bool m_keys_states;

};
inline glm::vec3 TPSCamera::getPosition() {
}

inline void TPSCamera::setPosition(const glm::vec3 & position) {
}

inline glm::vec3 TPSCamera::getRotation() {
}

inline void TPSCamera::setRotation(const glm::vec3 & rotation) {
}

#endif
