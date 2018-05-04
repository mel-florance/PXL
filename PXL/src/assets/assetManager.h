#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H


#include "manager.h"

class Loader;
class ShaderManager;
class SceneManager;
class Mesh;
class Texture;

class AssetManager : public Manager {
  public:
     AssetManager(Loader & loader, ShaderManager & shaderManager, SceneManager & sceneManager);

     ~AssetManager();

    void importMesh(const std::string & filename);

    void processNode(aiNode & node, const aiScene & scene);

    Mesh processMesh(const std::string & name, aiMesh & object, const aiScene & scene);

    inline Loader getLoader();

    inline ShaderManager getShaderManager();


  private:
    Loader * m_loader;

    ShaderManager * m_shaderManager;

    SceneManager * m_sceneManager;

    class Texture* m_textures;

};
inline Loader AssetManager::getLoader() {
}

inline ShaderManager AssetManager::getShaderManager() {
}

#endif
