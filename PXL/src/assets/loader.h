#ifndef _LOADER_H
#define _LOADER_H


class Mesh;

class Loader {
  public:
     Loader();

     ~Loader();

    Mesh loadToVAO(const std::string & name, const std::vector<glm::vec3> & vertices);

    Mesh loadToVAO(const std::string & name, const std::vector<glm::vec2> & vertices);

    Mesh loadToVAO(const std::string & name, const std::vector<glm::vec3> & vertices, const std::vector<GLuint> & indices, const std::vector<glm::vec2> & uvs, const std::vector<glm::vec3> & normals, const std::vector<glm::vec3> & tangents);

    Uint32 loadCubeMap(const std::vector<std::string> & textures);

    inline void unbindVAO();


  private:
    void storeDataInAttributeList(const GLuint & location, int size, void data, int dataSize);

    void bindIndicesBuffer(GLuint & indices, GLuint & count);

    GLuint createVAO();

    GLuint m_vaos;

    GLuint m_vbos;

};
inline void Loader::unbindVAO() {
}

#endif
