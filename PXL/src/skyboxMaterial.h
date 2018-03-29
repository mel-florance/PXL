#pragma once

#include "material.h"

class SkyboxMaterial : public Material
{
public:
	SkyboxMaterial(const std::string& name, Shader* shader);
	~SkyboxMaterial();

	void SkyboxMaterial::updateUniforms(Camera* camera, glm::vec4& clearColor, double delta);
	void bindAttributes();
	void bindTextures(double delta);

	inline void setLimits(glm::vec2& limits) { m_limits = limits; }
	inline glm::vec2& getLimits() { return m_limits; }

	inline void setBlendFactor(float value) { m_blendFactor = value; }
	inline float& getBlendFactor() { return m_blendFactor; }

	inline void setRotSpeed(float value) { m_rotSpeed = value; }
	inline float& getRotSpeed() { return m_rotSpeed; }

	inline void setRotation(float value) { m_rotation = value; }
	inline float& getRotation() { return m_rotation; }

	inline void setTime(float value) { m_time = value; }
	inline float& getTime() { return m_time; }

	inline void setCubemap(Uint32 id) { m_cubemap = id; }
	inline Uint32& getCubemap() { return m_cubemap; }

	inline void setCubemap2(Uint32 id) { m_cubemap2 = id; }
	inline Uint32& getCubemap2() { return m_cubemap2; }

private:
	Transform* m_transform;
	glm::vec2 m_limits;
	float m_blendFactor;
	float m_rotSpeed;
	float m_rotation;
	float m_time;

	Uint32 m_cubemap;
	Uint32 m_cubemap2;
};

