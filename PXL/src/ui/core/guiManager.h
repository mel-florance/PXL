#ifndef _GUIMANAGER_H
#define _GUIMANAGER_H


#include "manager.h"
#include "nanovg.h"

class Engine;
class Display;
class FontManager;
class AssetManager;
class SceneManager;
class Layout;
class Widget;
class LayerManager;
class QuadTree;

class GuiManager : public Manager {
  public:
     GuiManager(Engine & engine, Display & window, FontManager & fontManager, AssetManager & assetManager, SceneManager & sceneManager);

     ~GuiManager();

    void init();

    void initLayout(Layout & layout);

    inline NVGcontext getContext();

    void handleLayoutEvent(const std::string & name, const SDL_Event & event, Layout & layout);

    void handleWidgetEvent(Widget & widget, const SDL_Event & event, const std::string & name);

    void handleEvent(const std::string & name, const SDL_Event & event);

    void handleLayoutWindowEvent(Layout & layout, const SDL_Event & event, const std::string & name);

    Layout getHoveredLayout(const glm::vec2 & mouse);

    inline Layout getMainLayout();

    inline void setMainLayout(Layout & layout);

    Widget getWidgetByName(const std::string & name);

    Layout getPrevious(Layout & layout);

    void onSceneObjectAdded();

    inline void addLayout(Layout & layout);

    inline std::vector<Layout*> getLayouts();

    Layout getLayoutByName(const std::string & name);

    inline FontManager getFontManager();

    inline SceneManager getSceneManager();

    inline AssetManager getAssetManager();

    inline LayerManager getLayerManager();

    inline Engine getEngine();


  private:
    Layout findPrevious(Layout & fromLevel, Layout & layout);

    Layout * m_activeLayout;

    NVGcontext * m_ctx;

    Display * m_window;

    Layout * m_mainLayout;

    Layout * m_layouts;

    FontManager * m_fontManager;

    SceneManager * m_sceneManager;

    AssetManager * m_assetManager;

    LayerManager * m_layerManager;

    QuadTree * m_quadTree;

    Engine * m_engine;

};
inline NVGcontext GuiManager::getContext() {
}

inline Layout GuiManager::getMainLayout() {
}

inline void GuiManager::setMainLayout(Layout & layout) {
}

inline void GuiManager::addLayout(Layout & layout) {
}

inline std::vector<Layout*> GuiManager::getLayouts() {
}

inline FontManager GuiManager::getFontManager() {
}

inline SceneManager GuiManager::getSceneManager() {
}

inline AssetManager GuiManager::getAssetManager() {
}

inline LayerManager GuiManager::getLayerManager() {
}

inline Engine GuiManager::getEngine() {
}

#endif
