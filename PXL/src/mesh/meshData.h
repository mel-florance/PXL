#ifndef _MESHDATA_H
#define _MESHDATA_H


class MeshData {
  public:
     MeshData(const std::vector<glm::vec3> & vertices, const std::vector<glm::vec2> & uvs, const std::vector<glm::vec3> & normals, const std::vector<GLuint> & indices, const std::vector<glm::vec3> & tangents);

    inline std::vector<glm::vec3> getVertices();

    inline std::vector<glm::vec2> getUvs();

    inline std::vector<glm::vec3> getNormals();

    inline std::vector<glm::vec3> getTangents();

    inline std::vector<GLuint> getIndices();

     ~MeshData();


  private:
    glm::vec3 m_vertices;

    glm::vec2 m_uvs;

    glm::vec3 m_normals;

    glm::vec3 m_tangents;

    GLuint m_indices;

};
inline std::vector<glm::vec3> MeshData::getVertices() {
}

inline std::vector<glm::vec2> MeshData::getUvs() {
}

inline std::vector<glm::vec3> MeshData::getNormals() {
}

inline std::vector<glm::vec3> MeshData::getTangents() {
}

inline std::vector<GLuint> MeshData::getIndices() {
}

#endif
