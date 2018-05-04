#ifndef _ENGINE_H
#define _ENGINE_H


class GameLoop;
class Display;
namespace PXL { namespace Rendering { class Renderer; }  } 
class Loader;
class Database;
class Editor;
class SceneManager;
class ShaderManager;
class AssetManager;
class GuiManager;
class FontManager;
class InputManager;
class SoundManager;

class Engine {
  public:
     Engine(glm::vec2 & windowSize);

     ~Engine();

    void start();

    static void update(GameLoop & loop, Engine & self);

    static void render(GameLoop & loop, Engine & self);

    void stop();

    inline Display getWindow();

    inline PXL::Rendering::Renderer getRenderer();

    inline Loader getLoader();

    inline GameLoop getLoop();

    inline Database getDatabase();

    inline Editor getEditor();

    inline SceneManager getSceneManager();

    inline ShaderManager getShaderManager();

    inline AssetManager getAssetManager();

    inline GuiManager getGuiManager();

    inline FontManager getFontManager();

    inline InputManager getInputManager();

    inline SoundManager getSoundManager();


  private:
    Database * m_database;

    GameLoop * m_gameLoop;

    Loader * m_loader;

    Display * m_window;

    PXL::Rendering::Renderer * m_renderer;

    Editor * m_editor;

    InputManager * m_inputManager;

    SceneManager * m_sceneManager;

    ShaderManager * m_shaderManager;

    AssetManager * m_assetManager;

    GuiManager * m_guiManager;

    FontManager * m_fontManager;

    SoundManager * m_soundManager;

    glm::vec2 m_windowSize;

};
inline Display Engine::getWindow() {
}

inline PXL::Rendering::Renderer Engine::getRenderer() {
}

inline Loader Engine::getLoader() {
}

inline GameLoop Engine::getLoop() {
}

inline Database Engine::getDatabase() {
}

inline Editor Engine::getEditor() {
}

inline SceneManager Engine::getSceneManager() {
}

inline ShaderManager Engine::getShaderManager() {
}

inline AssetManager Engine::getAssetManager() {
}

inline GuiManager Engine::getGuiManager() {
}

inline FontManager Engine::getFontManager() {
}

inline InputManager Engine::getInputManager() {
}

inline SoundManager Engine::getSoundManager() {
}

#endif
