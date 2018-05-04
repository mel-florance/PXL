#ifndef _ENTITYRENDERER_H
#define _ENTITYRENDERER_H


class ShaderManager;
class Scene;
class Shader;

class EntityRenderer {
  public:
     EntityRenderer(ShaderManager & shaderManager);

     ~EntityRenderer();

    void render(Scene & scene, double delta);


  private:
    ShaderManager * m_shaderManager;

    Shader * m_basicShader;

};
#endif
