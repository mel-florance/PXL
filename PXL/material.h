#pragma once

#include <string>
#include <vector>
#include <tuple>

#include <glm/glm.hpp>

#include "texture.h"
#include "shader.h"

class Material
{
public:
	Material() {};
	Material(const std::string& name, Shader* shader);
	~Material();

	inline float getShininess() { return m_shininess; }
	inline float getReflectivity() { return m_reflectivity; }
	inline Texture* getDiffuseTexture() { return m_diffuseTexture; }

	inline void setShininess(float value) { m_shininess = value; }
	inline void setReflectivity(float value) { m_reflectivity = value; }
	inline void setDiffuseTexture(Texture* texture) { m_diffuseTexture = texture; }

	inline const std::string& getName() { return m_name; }
	inline void setName(const std::string& name) { m_name = name; }

	inline Shader* getShader() { return m_shader; }
	inline void setShader(Shader* shader) { m_shader = shader; }

	void preUpdate(Transform* transform, Camera* camera, std::vector<Light*> lights);
	void postUpdate();

	virtual void bindAttributes();

private:
	std::string m_name;
	Shader* m_shader;

	glm::vec3 m_color;
	glm::vec2 m_tiling = glm::vec2(1.0f, 1.0f);

	Texture* m_diffuseTexture;

	float m_shininess = 50.0f;
	float m_reflectivity = 0.5f;
};
