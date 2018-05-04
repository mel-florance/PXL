#ifndef _MATERIALINFO_H
#define _MATERIALINFO_H


struct MaterialInfo {
    std::string name;

    glm::vec3 ambient;

    glm::vec3 diffuse;

    glm::vec3 specular;

    float shininess;

};
#endif
