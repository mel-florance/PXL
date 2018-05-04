#ifndef _SKYBOXRENDERER_H
#define _SKYBOXRENDERER_H


class Loader;
class ShaderManager;
class Scene;
class Mesh;
class SkyboxMaterial;
class Shader;

class SkyboxRenderer {
  public:
     SkyboxRenderer(Loader & loader, ShaderManager & shaderManager);

     ~SkyboxRenderer();

    void render(Scene & scene, double delta);


  private:
    float m_time;

    Loader * m_loader;

    Mesh * m_mesh;

    SkyboxMaterial * m_material;

    ShaderManager * m_shaderManager;

    Shader * m_skyboxShader;

};
#endif
