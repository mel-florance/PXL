#ifndef _EDITORLAYOUT_H
#define _EDITORLAYOUT_H


class EditorLayout {
  public:
     EditorLayout();

     ~EditorLayout();

    void loadLayout();

    void addComponent(const std::string & name);

    void removeComponent(const std::string & name);

};
#endif
