#include "shader.h"

Shader::Shader(const std::string& filename)
{
	m_program = glCreateProgram();
	m_shaders[0] = createShader(loadShader(filename + "_VS.glsl"), GL_VERTEX_SHADER);
	m_shaders[1] = createShader(loadShader(filename + "_FS.glsl"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; ++i)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "uvs");
	glBindAttribLocation(m_program, 2, "normal");


	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Shader Error: program linking failed.");

	glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Shader Error: the program is invalid.");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "mTransform");
	m_uniforms[VIEW_U] = glGetUniformLocation(m_program, "mView");
	m_uniforms[PROJ_U] = glGetUniformLocation(m_program, "mProj");
	m_uniforms[LIGHT_POSITION_U] = glGetUniformLocation(m_program, "lightPosition");
	m_uniforms[LIGHT_COLOR_U] = glGetUniformLocation(m_program, "lightColor");
}

GLuint Shader::createShader(const std::string& text, GLenum type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)
		std::cerr << "Shader Error: shader creation failed." << std::endl;

	const GLchar* sourceStrings[1];
	GLint sourceStringLengths[1];
	sourceStrings[0] = text.c_str();
	sourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, sourceStrings, sourceStringLengths);
	glCompileShader(shader);

	checkShaderError(shader, GL_COMPILE_STATUS, false, "Shader Error: shader compilation failed.");

	return shader;
}

void Shader::bind()
{
	glUseProgram(m_program);
}	
void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::update(const Transform& transform, Camera& camera, Light* light)
{ 
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &transform.getModel()[0][0]);
	glUniformMatrix4fv(m_uniforms[VIEW_U], 1, GL_FALSE, &camera.getViewMatrix()[0][0]);
	glUniformMatrix4fv(m_uniforms[PROJ_U], 1, GL_FALSE, &camera.getProjectionMatrix()[0][0]);

	glUniform3fv(m_uniforms[LIGHT_POSITION_U], 1, &light->getPosition()[0]);
	glUniform3fv(m_uniforms[LIGHT_COLOR_U], 1, &light->getColor()[0]);
}

std::string Shader::loadShader(const std::string& filename)
{
	std::ifstream file;
	file.open(filename.c_str());

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else {
		std::cerr << "Unable to load shader: " << filename << std::endl;
	}

	return output;
}

void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& message)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE) {
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << message << ": '" << error << "'" << std::endl;
	}
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; ++i) {
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}
