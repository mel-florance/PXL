#ifndef _CAMERA_H
#define _CAMERA_H


class Display;
class Viewport;

class Camera {
  public:
     Camera(Display & window, float fov, float aspect, float near, float far);

    virtual  ~Camera();

    enum Mode {
      ORTHOGRAPHIC,
      PERSPECTIVE
    };

    enum Direction {
      UP,
      DOWN,
      LEFT,
      RIGHT,
      FORWARD,
      BACKWARD
    };

    inline float getFov();

    inline void setFov(float value);

    inline void setViewport(Viewport & viewport);

    inline Viewport getViewport();

    inline float getAspect();

    inline void setAspect(float value);

    inline float getNear();

    inline void setNear(float value);

    inline float getFar();

    inline void setFar(float value);

    inline Mode getMode();

    inline void setMode(Mode mode);

    inline virtual glm::mat4 getProjectionMatrix();

    inline virtual void setProjectionMatrix(const glm::mat4 & matrix);

    inline virtual glm::mat4 getViewMatrix();

    inline virtual void setViewMatrix(const glm::mat4 & matrix);

    inline virtual glm::vec3 getPosition();

    inline virtual void setPosition(const glm::vec3 & position);

    inline virtual bool isActive();

    inline virtual void setActive(bool value);

    inline virtual void onMouseMove(const glm::vec2 & mouse);

    inline virtual void onMouseDown(const Uint8 & button);

    inline virtual void onMouseUp(const Uint8 & button);

    inline virtual void onKeyDown(const SDL_Keycode & keycode);

    inline virtual void onKeyUp(const SDL_Keycode & keycode);

    inline virtual void onMouseWheel(const SDL_Event & event);

    virtual void onWindowResized(const SDL_Event & event);

    virtual void onWindowSizeChanged(const SDL_Event & event);

    inline virtual Display getWindow();

    inline virtual void update(double delta);


  private:
    bool m_active;

    Display * m_window;

    Viewport * m_viewport;

    glm::vec3 m_position;

    Mode m_mode;

    float m_fov;

    float m_aspect;

    float m_near;

    float m_far;

    glm::mat4 m_projMatrix;

    glm::mat4 m_viewMatrix;

};
inline float Camera::getFov() {
}

inline void Camera::setFov(float value) {
}

inline void Camera::setViewport(Viewport & viewport) {
}

inline Viewport Camera::getViewport() {
}

inline float Camera::getAspect() {
}

inline void Camera::setAspect(float value) {
}

inline float Camera::getNear() {
}

inline void Camera::setNear(float value) {
}

inline float Camera::getFar() {
}

inline void Camera::setFar(float value) {
}

inline Camera::Mode Camera::getMode() {
}

inline void Camera::setMode(Camera::Mode mode) {
}

inline glm::mat4 Camera::getProjectionMatrix() {
}

inline void Camera::setProjectionMatrix(const glm::mat4 & matrix) {
}

inline glm::mat4 Camera::getViewMatrix() {
}

inline void Camera::setViewMatrix(const glm::mat4 & matrix) {
}

inline glm::vec3 Camera::getPosition() {
}

inline void Camera::setPosition(const glm::vec3 & position) {
}

inline bool Camera::isActive() {
}

inline void Camera::setActive(bool value) {
}

inline void Camera::onMouseMove(const glm::vec2 & mouse) {
}

inline void Camera::onMouseDown(const Uint8 & button) {
}

inline void Camera::onMouseUp(const Uint8 & button) {
}

inline void Camera::onKeyDown(const SDL_Keycode & keycode) {
}

inline void Camera::onKeyUp(const SDL_Keycode & keycode) {
}

inline void Camera::onMouseWheel(const SDL_Event & event) {
}

inline Display Camera::getWindow() {
}

inline void Camera::update(double delta) {
}

#endif
