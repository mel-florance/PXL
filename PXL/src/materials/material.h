#ifndef _MATERIAL_H
#define _MATERIAL_H


class Shader;
class Transform;
class Camera;
class Scene;

class Material {
  public:
    inline  Material(const std::string & name, Shader & shader);

    inline virtual  ~Material();

    inline virtual std::string getName();

    inline virtual void setName(const std::string & name);

    inline virtual Shader getShader();

    inline virtual void setShader(Shader & shader);

    inline virtual void updateTransform(Transform & transform);

    inline virtual void updateUniforms(Camera & camera);

    inline virtual void preUpdate(Scene & scene);

    inline virtual void postUpdate();

    inline virtual void setBackFaceCulling(bool value);

    inline virtual bool getBackFaceCulling();

    inline virtual void setTiling(glm::vec2 & tiling);

    inline virtual glm::vec2 getTiling();

    inline virtual void bindAttributes();


  private:
    std::string m_name;

    Shader * m_shader;

    bool m_backFaceCulling;

    glm::vec2 m_tiling;

};
inline  Material::Material(const std::string & name, Shader & shader) {
}

inline  Material::~Material() {
}

inline std::string Material::getName() {
}

inline void Material::setName(const std::string & name) {
}

inline Shader Material::getShader() {
}

inline void Material::setShader(Shader & shader) {
}

inline void Material::updateTransform(Transform & transform) {
}

inline void Material::updateUniforms(Camera & camera) {
}

inline void Material::preUpdate(Scene & scene) {
}

inline void Material::postUpdate() {
}

inline void Material::setBackFaceCulling(bool value) {
}

inline bool Material::getBackFaceCulling() {
}

inline void Material::setTiling(glm::vec2 & tiling) {
}

inline glm::vec2 Material::getTiling() {
}

inline void Material::bindAttributes() {
}

#endif
