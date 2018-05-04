#ifndef _MESHRENDERER_H
#define _MESHRENDERER_H


#include "entityComponent.h"
#include "mesh.h"
#include "material.h"

class MeshRenderer : public EntityComponent {
  public:
    inline  MeshRenderer(const Mesh & mesh, const Material & material);

    inline  ~MeshRenderer();


  private:
    Mesh m_mesh;

    Material m_material;

};
inline  MeshRenderer::MeshRenderer(const Mesh & mesh, const Material & material) {
}

inline  MeshRenderer::~MeshRenderer() {
}

#endif
