#ifndef _INSPECTOR_H
#define _INSPECTOR_H


#include "editorComponent.h"

class Engine;
class Window;
class Tabs;

class Inspector : public EditorComponent {
  public:
     Inspector(Engine & engine);

    void init();

    inline Window getWindow();

     ~Inspector();


  private:
    Tabs * m_tabs;

    Window * m_window;

};
inline Window Inspector::getWindow() {
}

#endif
