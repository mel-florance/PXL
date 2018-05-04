#ifndef _SHADER_H
#define _SHADER_H


class Shader {
  public:
     Shader(const std::string & filename);

    virtual  ~Shader();

    void bind();

    void unbind();

    void bindAttribute(const GLuint & location, const std::string & name);

    std::string loadShader(const std::string & filename);

    void checkShaderError(const GLuint & shader, const GLuint & flag, bool isProgram, const std::string & message);

    GLuint createShader(const std::string & text, const GLenum & type);

    void addUniform(const std::string & name);

    void setUniformMat4fv(const std::string & name, const glm::mat4 & mat);

    void setUniform4fv(const std::string & name, const glm::vec4 & vec);

    void setUniform3fv(const std::string & name, const glm::vec3 & vec);

    void setUniform2fv(const std::string & name, const glm::vec2 & vec);

    void setUniform1f(const std::string & name, float & value);

    void setUniform1i(const std::string & name, int value);

    inline GLuint getProgram();


  private:
    static const unsigned int NUM_SHADERS;

    GLuint m_program;

    GLuint m_shaders[NUM_SHADERS];

    std::string, GLuint m_uniforms;

};
inline GLuint Shader::getProgram() {
}

#endif
