#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
	void bindAttribute(unsigned int attribute, std::string& name);
	void update(const Transform& transform, Camera& camera, std::vector<Light*> lights);

	std::string loadShader(const std::string& filename);
	void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& message);
	GLuint createShader(const std::string& text, GLenum type);

private:
	static const unsigned int NUM_SHADERS = 2;

	enum {
		TRANSFORM_U,
		VIEW_U,
		PROJ_U,
		LIGHT_POSITION_U,
		LIGHT_COLOR_U,
		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

