#ifndef _MESHFACTORY_H
#define _MESHFACTORY_H


class MeshData;

class MeshFactory {
  public:
    const float pi=  std::atan(1.0f) * 4.0f;

    static inline std::vector<glm::vec2> getQuad();

    static inline std::vector<glm::vec3> getCube(float scale);

    static inline MeshData createSphere(float radius, int resolution);


  private:
    inline  MeshFactory();

};
inline std::vector<glm::vec2> MeshFactory::getQuad()
{
}

inline std::vector<glm::vec3> MeshFactory::getCube(float scale)
{
}

inline MeshData MeshFactory::createSphere(float radius, int resolution)
{
}

inline  MeshFactory::MeshFactory() {
}

#endif
