#ifndef PXL_RENDERING_RENDERER_H
#define PXL_RENDERING_RENDERER_H


class Display;
class Loader;
class ShaderManager;
class AssetManager;
class GuiManager;
class Viewport;
class Scene;
class EntityRenderer;
class SkyboxRenderer;
class GuiRenderer;

namespace PXL {

namespace Rendering {

class Renderer {
  public:
     Renderer(::Display & window, ::Loader & loader, ::ShaderManager & shaderManager, ::AssetManager & assetManager, ::GuiManager & guiManager);

     ~Renderer();

    inline void setViewport(::Viewport & viewport);

    void clear(const glm::vec4 & color);

    void render(::Scene & scene, double delta);


  private:
    ::Display * m_window;

    ::Loader * m_loader;

    ::Viewport * m_viewport;

    ::EntityRenderer * m_entityRenderer;

    ::SkyboxRenderer * m_skyboxRenderer;

    ::GuiRenderer * m_guiRenderer;

    ::GuiManager * m_guiManager;

};
inline void Renderer::setViewport(::Viewport & viewport) {
}


} // namespace PXL::Rendering

} // namespace PXL
#endif
