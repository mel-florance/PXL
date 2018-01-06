#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "shader.h"

class Material
{
public:
	Material(const std::string& name, Shader* shader) : m_name(name), m_shader(shader) {}
	virtual ~Material() {}

	inline const std::string& getName() { return m_name; }
	inline void setName(const std::string& name) { m_name = name; }

	inline Shader* getShader() { return m_shader; }
	inline void setShader(Shader* shader) { m_shader = shader; }

	virtual void updateTransform(Transform* transform) {}

	virtual void preUpdate(Camera* camera, std::vector<Light*> lights) {}
	virtual void postUpdate() {}

	virtual void bindAttributes() {}

private:
	std::string m_name;
	Shader* m_shader;
};
