#include "shader.h"

Shader::Shader(const std::string& filename)
{
	m_program = glCreateProgram();
	m_shaders[0] = createShader(loadShader(filename + "_VS.glsl"), GL_VERTEX_SHADER);
	m_shaders[1] = createShader(loadShader(filename + "_FS.glsl"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; ++i)
		glAttachShader(m_program, m_shaders[i]);

	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Shader Error: program linking failed.");

	glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Shader Error: the program is invalid.");
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

void Shader::addUniform(const std::string& name)
{
	m_uniforms[name] = glGetUniformLocation(m_program, name.c_str());
}

void Shader::setUniformMat4fv(const std::string& name, const glm::mat4& mat)
{
	glUniformMatrix4fv(m_uniforms[name], 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniform4fv(const std::string& name, const glm::vec4& vec)
{
	glUniform4fv(m_uniforms[name], 1, &vec[0]);
}

void Shader::setUniform3fv(const std::string& name, const glm::vec3& vec)
{
	glUniform3fv(m_uniforms[name], 1, &vec[0]);
}

void Shader::setUniform2fv(const std::string& name, const glm::vec2& vec)
{
	glUniform2fv(m_uniforms[name], 1, &vec[0]);
}

void Shader::setUniform1f(const std::string& name, float& value)
{
	glUniform1f(m_uniforms[name], value);
}

void Shader::setUniform1i(const std::string& name, int value)
{
	glUniform1i(m_uniforms[name], value);
}

void Shader::bind()
{
	glUseProgram(m_program);
}	
void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::bindAttribute(GLuint location, const std::string& name)
{
	glBindAttribLocation(m_program, location, name.c_str());
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
