#ifndef _MESH_H
#define _MESH_H


class Transform;
class Material;

class Mesh {
  public:
     Mesh(const std::string & name, GLuint & vao, GLuint & vertexCount);

     ~Mesh();

    inline unsigned long getId();

    inline GLuint getVao();

    inline GLuint getVertexCount();

    inline std::string getName();

    inline void setName(const std::string & name);

    inline Transform getTransform();

    inline void setTransform(Transform & transform);

    inline Material getMaterial();

    inline void setMaterial(Material & material);

    inline bool isVisible();

    inline void setVisible(bool state);

    void draw();

    void toggleAttributes(bool state);

    void addChild(Mesh & child);

    inline std::vector<class Mesh*> getInstances();

    Mesh createInstance(const std::string & name);


  private:
    std::string m_name;

    std::string m_id;

    GLuint m_vao;

    GLuint m_vertexCount;

    bool m_visible;

    class Mesh* m_children;

    class Mesh* m_instances;

    Material * m_material;

    Transform * m_transform;

};
inline unsigned long Mesh::getId() {
}

inline GLuint Mesh::getVao() {
}

inline GLuint Mesh::getVertexCount() {
}

inline std::string Mesh::getName() {
}

inline void Mesh::setName(const std::string & name) {
}

inline Transform Mesh::getTransform() {
}

inline void Mesh::setTransform(Transform & transform) {
}

inline Material Mesh::getMaterial() {
}

inline void Mesh::setMaterial(Material & material) {
}

inline bool Mesh::isVisible() {
}

inline void Mesh::setVisible(bool state) {
}

inline std::vector<class Mesh*> Mesh::getInstances() {
}

#endif
