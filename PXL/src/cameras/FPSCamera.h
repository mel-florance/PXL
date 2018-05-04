#ifndef _FPSCAMERA_H
#define _FPSCAMERA_H


#include "camera.h"

class Display;

class FPSCamera : public Camera {
  public:
     FPSCamera(Display & window, glm::vec3 & position, float fov, float aspect, float near, float far);

     ~FPSCamera();

    inline glm::vec3 getPosition();

    inline void setPosition(const glm::vec3 & position);

    inline glm::vec3 getRotation();

    inline void setRotation(const glm::vec3 & rotation);

    inline glm::vec3 getDirection();

    inline void setDirection(const glm::vec3 & direction);

    void setPitch(float degrees);

    void setYaw(float degrees);

    void move(const Direction & dir);

    void onKeyDown(const SDL_Keycode & keycode);

    void onKeyUp(const SDL_Keycode & keycode);

    void onMouseMove(const glm::vec2 & mouse);

    void onMouseDown(const Uint8 & button);

    void onMouseUp(const Uint8 & button);

    void onMouseWheel(const SDL_Event & event);

    void lockCursor(bool value);

    void update(double delta);


  private:
    glm::vec3 m_up;

    glm::vec3 m_position;

    glm::vec3 m_positionDelta;

    glm::vec3 m_direction;

    glm::vec3 m_target;

    glm::vec3 m_rotation;

    float m_velocity;

    float m_viewFriction;

    float m_moveFriction;

    float m_pitch;

    float m_yaw;

    float m_sensitivity;

    float m_moveSpeed;

    float m_maxSpeed;

    double m_delta;

    bool m_cursorLocked;

    std::string, int m_keys;

    std::string, bool m_keys_states;

};
inline glm::vec3 FPSCamera::getPosition() {
}

inline void FPSCamera::setPosition(const glm::vec3 & position) {
}

inline glm::vec3 FPSCamera::getRotation() {
}

inline void FPSCamera::setRotation(const glm::vec3 & rotation) {
}

inline glm::vec3 FPSCamera::getDirection() {
}

inline void FPSCamera::setDirection(const glm::vec3 & direction) {
}

#endif
