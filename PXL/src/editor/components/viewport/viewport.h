#ifndef _VIEWPORT_H
#define _VIEWPORT_H


#include "editorComponent.h"

class Engine;
class Window;
struct CallbackData;
class Text;

class Viewport : public EditorComponent {
  public:
     Viewport(Engine & engine);

    enum ViewportMode {
      EDITOR,
      GAME
    };

    void init();

    void update(double delta);

    inline Window getWindow();

    static void addCube(const CallbackData & data);

    static void createCube(const CallbackData & data);

    static void onCreateCubeModalClosed(const CallbackData & data);

    inline Text getFpsText();

    inline Text getFrameText();

    inline ViewportMode getMode();

    inline void setMode(ViewportMode mode);

    void onKeyUp(const SDL_Event & event);

     ~Viewport();


  private:
    ViewportMode m_mode;

    Window * m_window;

    Window * m_toolsPanel;

    Text * m_fpsText;

    Text * m_frameText;

};
inline Window Viewport::getWindow() {
}

inline Text Viewport::getFpsText() {
}

inline Text Viewport::getFrameText() {
}

inline Viewport::ViewportMode Viewport::getMode() {
}

inline void Viewport::setMode(Viewport::ViewportMode mode) {
}

#endif
