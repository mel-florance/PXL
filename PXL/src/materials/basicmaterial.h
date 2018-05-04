#ifndef _BASICMATERIAL_H
#define _BASICMATERIAL_H


#include "material.h"

class Shader;
class Scene;
class Transform;
class Texture;

class BasicMaterial : public Material {
  public:
     BasicMaterial(const std::string & name, Shader & shader);

     ~BasicMaterial();

    virtual void preUpdate(Scene & scene);

    virtual void updateTransform(Transform & transform);

    virtual void postUpdate();

    inline void setShininess(float value);

    inline float getShininess();

    inline void setExponent(float value);

    inline float getExponent();

    inline void setReflectivity(float value);

    inline float getReflectivity();

    inline void setAlpha(float value);

    inline float getAlpha();

    inline void setDiffuseTexture(Texture & texture);

    inline Texture getDiffuseTexture();

    inline void setSpecularTexture(Texture & texture);

    inline Texture getSpecularTexture();

    inline void setNormalTexture(Texture & texture);

    inline Texture getNormalTexture();

    inline void setKa(glm::vec3 & value);

    inline glm::vec3 getKa();

    inline void setKd(glm::vec3 & value);

    inline glm::vec3 getKd();

    inline void setKs(glm::vec3 & value);

    inline glm::vec3 getKs();

    inline void setKe(glm::vec3 & value);

    inline glm::vec3 getKe();

    inline void setBackFaceCulling(bool value);

    inline bool getBackFaceCulling();

    inline void setTiling(glm::vec2 & tiling);

    inline glm::vec2 getTiling();

    inline unsigned int hasDiffuseTexture();

    inline unsigned int hasSpecularTexture();

    inline unsigned int hasNormalTexture();

    virtual void bindAttributes();


  private:
    float m_shininess;

    float m_exponent;

    float m_alpha;

    float m_reflectivity;

    // Ambient
    glm::vec3 m_Ka;

    // Diffuse
    glm::vec3 m_Kd;

    // Specular
    glm::vec3 m_Ks;

    // Emission
    glm::vec3 m_Ke;

    Texture * m_diffuseTexture;

    Texture * m_specularTexture;

    Texture * m_normalTexture;

    glm::vec2 m_tiling;

    bool m_backFaceCulling;

};
inline void BasicMaterial::setShininess(float value) {
}

inline float BasicMaterial::getShininess() {
}

inline void BasicMaterial::setExponent(float value) {
}

inline float BasicMaterial::getExponent() {
}

inline void BasicMaterial::setReflectivity(float value) {
}

inline float BasicMaterial::getReflectivity() {
}

inline void BasicMaterial::setAlpha(float value) {
}

inline float BasicMaterial::getAlpha() {
}

inline void BasicMaterial::setDiffuseTexture(Texture & texture) {
}

inline Texture BasicMaterial::getDiffuseTexture() {
}

inline void BasicMaterial::setSpecularTexture(Texture & texture) {
}

inline Texture BasicMaterial::getSpecularTexture() {
}

inline void BasicMaterial::setNormalTexture(Texture & texture) {
}

inline Texture BasicMaterial::getNormalTexture() {
}

inline void BasicMaterial::setKa(glm::vec3 & value) {
}

inline glm::vec3 BasicMaterial::getKa() {
}

inline void BasicMaterial::setKd(glm::vec3 & value) {
}

inline glm::vec3 BasicMaterial::getKd() {
}

inline void BasicMaterial::setKs(glm::vec3 & value) {
}

inline glm::vec3 BasicMaterial::getKs() {
}

inline void BasicMaterial::setKe(glm::vec3 & value) {
}

inline glm::vec3 BasicMaterial::getKe() {
}

inline void BasicMaterial::setBackFaceCulling(bool value) {
}

inline bool BasicMaterial::getBackFaceCulling() {
}

inline void BasicMaterial::setTiling(glm::vec2 & tiling) {
}

inline glm::vec2 BasicMaterial::getTiling() {
}

inline unsigned int BasicMaterial::hasDiffuseTexture() {
}

inline unsigned int BasicMaterial::hasSpecularTexture() {
}

inline unsigned int BasicMaterial::hasNormalTexture() {
}

#endif
