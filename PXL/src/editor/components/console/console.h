#ifndef _CONSOLE_H
#define _CONSOLE_H


#include "editorComponent.h"

class Engine;
class Window;

class Console : public EditorComponent {
  public:
     Console(Engine & engine);

    void init();

    inline Window getWindow();

    void Console::onKeyUp(const SDL_Event & event);

     ~Console();


  private:
    Window * m_window;

};
inline Window Console::getWindow() {
}

#endif
