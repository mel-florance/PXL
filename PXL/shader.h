#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include <GL/glew.h>

#include "transform.h"
#include "camera.h"
#include "Light.h"

class Shader
{
public:
	Shader(const std::string& filename);
	virtual ~Shader();

	void bind();
	void unbind();
	void bindAttribute(GLuint location, const std::string& name);

	std::string loadShader(const std::string& filename);
	void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& message);
	GLuint createShader(const std::string& text, GLenum type);

	void addUniform(const std::string& name);

	void setUniformMat4fv(const std::string& name, const glm::mat4& mat);
	void setUniform3fv(const std::string& name, const glm::vec3& vec);
	void setUniform1f(const std::string& name, float& value);
	void setUniform1i(const std::string& name, int value);

private:
	static const unsigned int NUM_SHADERS = 2;

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];

	std::map<std::string, GLuint> m_uniforms;
};

