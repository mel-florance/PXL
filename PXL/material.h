#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "shader.h"


class Scene;
class Material
{
public:
	Material(const std::string& name, Shader* shader) : m_name(name), m_shader(shader), m_backFaceCulling(true) {}
	virtual ~Material() {}

	inline const std::string& getName() { return m_name; }
	inline void setName(const std::string& name) { m_name = name; }

	inline Shader* getShader() { return m_shader; }
	inline void setShader(Shader* shader) { m_shader = shader; }

	virtual void updateTransform(Transform* transform) {}

	virtual void preUpdate(Scene* scene) {}
	virtual void postUpdate() {}

	inline void setBackFaceCulling(bool value) { m_backFaceCulling = value; }
	inline bool& getBackFaceCulling() { return m_backFaceCulling; }

	virtual void bindAttributes() {}

private:
	std::string m_name;
	Shader* m_shader;

	bool m_backFaceCulling;
};
