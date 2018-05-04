#ifndef _SKYBOXMATERIAL_H
#define _SKYBOXMATERIAL_H


#include "material.h"

class Shader;
class Camera;
class Transform;

class SkyboxMaterial : public Material {
  public:
     SkyboxMaterial(const std::string & name, Shader & shader);

     ~SkyboxMaterial();

    void SkyboxMaterial::updateUniforms(Camera & camera, glm::vec4 & clearColor, double delta);

    void bindAttributes();

    void bindTextures(double delta);

    inline void setLimits(glm::vec2 & limits);

    inline glm::vec2 getLimits();

    inline void setBlendFactor(float value);

    inline float getBlendFactor();

    inline void setRotSpeed(float value);

    inline float getRotSpeed();

    inline void setRotation(float value);

    inline float getRotation();

    inline void setTime(float value);

    inline float getTime();

    inline void setCubemap(const Uint32 & id);

    inline Uint32 getCubemap();

    inline void setCubemap2(const Uint32 & id);

    inline Uint32 getCubemap2();


  private:
    Transform * m_transform;

    glm::vec2 m_limits;

    float m_blendFactor;

    float m_rotSpeed;

    float m_rotation;

    float m_time;

    Uint32 m_cubemap;

    Uint32 m_cubemap2;

};
inline void SkyboxMaterial::setLimits(glm::vec2 & limits) {
}

inline glm::vec2 SkyboxMaterial::getLimits() {
}

inline void SkyboxMaterial::setBlendFactor(float value) {
}

inline float SkyboxMaterial::getBlendFactor() {
}

inline void SkyboxMaterial::setRotSpeed(float value) {
}

inline float SkyboxMaterial::getRotSpeed() {
}

inline void SkyboxMaterial::setRotation(float value) {
}

inline float SkyboxMaterial::getRotation() {
}

inline void SkyboxMaterial::setTime(float value) {
}

inline float SkyboxMaterial::getTime() {
}

inline void SkyboxMaterial::setCubemap(const Uint32 & id) {
}

inline Uint32 SkyboxMaterial::getCubemap() {
}

inline void SkyboxMaterial::setCubemap2(const Uint32 & id) {
}

inline Uint32 SkyboxMaterial::getCubemap2() {
}

#endif
