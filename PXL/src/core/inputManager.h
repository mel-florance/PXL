#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H


#include "manager.h"

class Display;
class GuiManager;
class SceneManager;
class Camera;

class InputManager : public Manager {
  public:
     InputManager(Display & window, GuiManager & guiManager, SceneManager & sceneManager);

     ~InputManager();

    inline glm::vec2 getMouse();

    inline glm::vec2 getMouseRel();

    inline void setMouse(float x, float y);

    inline void setMouseRel(float x, float y);

    inline void setCamera(Camera & camera);

    inline Camera getCamera();

    void update();


  private:
    SceneManager * m_sceneManager;

    GuiManager * m_guiManager;

    Display * m_window;

    Camera * m_camera;

    glm::vec3 m_mouseStates;

    glm::vec2 m_mouse;

    glm::vec2 m_mouseRel;

    std::string, int m_keys;

    std::string, bool m_keys_states;

};
inline glm::vec2 InputManager::getMouse() {
}

inline glm::vec2 InputManager::getMouseRel() {
}

inline void InputManager::setMouse(float x, float y) {
}

inline void InputManager::setMouseRel(float x, float y) {
}

inline void InputManager::setCamera(Camera & camera) {
}

inline Camera InputManager::getCamera() {
}

#endif
