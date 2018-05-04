#ifndef _ASSETBROWSER_H
#define _ASSETBROWSER_H


#include "editorComponent.h"

class Engine;
class TreeView;
class Window;

class AssetBrowser : public EditorComponent {
  public:
     AssetBrowser(Engine & engine);

    void init();

    inline TreeView getTreeView();

     ~AssetBrowser();


  private:
    TreeView * m_treeView;

    Window * m_window;

};
inline TreeView AssetBrowser::getTreeView() {
}

#endif
