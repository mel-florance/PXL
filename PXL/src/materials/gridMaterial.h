#ifndef _GRIDMATERIAL_H
#define _GRIDMATERIAL_H


#include "material.h"

class Shader;
class Scene;
class Transform;

class GridMaterial : public Material {
  public:
     GridMaterial(const std::string & name, Shader & shader);

    void preUpdate(Scene & scene);

    void updateTransform(Transform & transform);

    void bindAttributes();

     ~GridMaterial();

};
#endif
