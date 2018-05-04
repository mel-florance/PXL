#ifndef _SHADERMANAGER_H
#define _SHADERMANAGER_H


#include "manager.h"

class Shader;

class ShaderManager : public Manager {
  public:
     ShaderManager();

     ~ShaderManager();

    void loadShaders(const std::string & path);

    inline void addShader(const std::string & name, Shader & shader);

    inline Shader getShader(const std::string & name);


  private:
    Shader * m_shaders;

    std::string m_shadersList;

};
inline void ShaderManager::addShader(const std::string & name, Shader & shader) {
}

inline Shader ShaderManager::getShader(const std::string & name) {
}

#endif
