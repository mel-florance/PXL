#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H


#include "manager.h"

class Scene;
class GuiManager;

class SceneManager : public Manager {
  public:
     SceneManager();

     ~SceneManager();

    inline std::vector<class Scene*> getScenes();

    inline void setCurrentScene(unsigned int index);

    Scene addScene(const std::string & name);

    void deleteScene(const std::string & name);

    void listScenes();

    Scene getSceneByName(const std::string & name);

    inline Scene getCurrentScene();

    inline void setGuiManager(GuiManager & guiManager);

    inline GuiManager getGuiManager();


  private:
    GuiManager * m_guiManager;

    unsigned int m_sceneCount;

    unsigned int m_currentScene;

    Scene * m_scenes;

};
inline std::vector<class Scene*> SceneManager::getScenes() {
}

inline void SceneManager::setCurrentScene(unsigned int index) {
}

inline Scene SceneManager::getCurrentScene() {
}

inline void SceneManager::setGuiManager(GuiManager & guiManager) {
}

inline GuiManager SceneManager::getGuiManager() {
}

#endif
