#ifndef _OUTLINER_H
#define _OUTLINER_H


#include "editorComponent.h"

class Engine;
class Window;
class Table;

class Outliner : public EditorComponent {
  public:
     Outliner(Engine & engine);

    void init();

    inline Window getWindow();

     ~Outliner();


  private:
    Window * m_window;

    Table * m_table;

};
inline Window Outliner::getWindow() {
}

#endif
