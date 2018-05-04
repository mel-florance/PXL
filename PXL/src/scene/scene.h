#ifndef _SCENE_H
#define _SCENE_H


class Mesh;
class Material;
class Camera;
class Light;
class Widget;
class Layout;

class Scene {
  public:
     Scene(const std::string & name);

     ~Scene();

    inline std::string getName();

    inline void setName(std::string & name);

    inline std::vector<class Mesh*> getMeshes();

    Mesh getMeshByName(const std::string & name);

    Mesh addMesh(Mesh & mesh);

    void removeMesh(Mesh & mesh);

    inline std::vector<class Material*> getMaterials();

    Material addMaterial(Material & material);

    void removeMaterial(Material & material);

    inline std::vector<class Camera*> getCameras();

    void addCamera(Camera & camera);

    void removeCamera(Camera & camera);

    inline std::vector<class Light*> getLights();

    void addLight(Light & light);

    void removeLight(Light & light);

    void addWidget(Widget & widget, Layout & layout);

    void removeWidget(Widget & widget, Layout & layout);

    inline void setActiveCamera(unsigned int index);

    inline Camera getActiveCamera();

    inline glm::vec4 getClearColor();

    inline void setClearColor(glm::vec4 & color);

    inline glm::vec3 getFogColor();

    inline void setFogColor(glm::vec3 & color);

    inline float getFogGradient();

    inline void setFogGradient(float & value);

    inline float getFogDensity();

    inline void setFogDensity(float & value);


  private:
    std::string m_name;

    unsigned int m_activeCamera;

    class Camera* m_cameras;

    class Light* m_lights;

    class Mesh* m_meshes;

    class Material* m_materials;

    glm::vec4 m_clearColor;

    glm::vec3 m_fogColor;

    float m_fogGradient;

    float m_fogDensity;

};
inline std::string Scene::getName() {
}

inline void Scene::setName(std::string & name) {
}

inline std::vector<class Mesh*> Scene::getMeshes() {
}

inline std::vector<class Material*> Scene::getMaterials() {
}

inline std::vector<class Camera*> Scene::getCameras() {
}

inline std::vector<class Light*> Scene::getLights() {
}

inline void Scene::setActiveCamera(unsigned int index) {
}

inline Camera Scene::getActiveCamera() {
}

inline glm::vec4 Scene::getClearColor() {
}

inline void Scene::setClearColor(glm::vec4 & color) {
}

inline glm::vec3 Scene::getFogColor() {
}

inline void Scene::setFogColor(glm::vec3 & color) {
}

inline float Scene::getFogGradient() {
}

inline void Scene::setFogGradient(float & value) {
}

inline float Scene::getFogDensity() {
}

inline void Scene::setFogDensity(float & value) {
}

#endif
