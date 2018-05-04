#ifndef _GUIRENDERER_H
#define _GUIRENDERER_H


class GuiManager;
class Display;
class Widget;
class Scene;
class Layout;

class GuiRenderer {
  public:
     GuiRenderer(GuiManager & guiManager, Display & window);

     ~GuiRenderer();

    void updateWidget(Widget & widget, double delta);

    void render(Scene & scene, double delta);

    void renderLayout(Layout & layout, Layout & previous, unsigned int index, unsigned int depth, double delta);

    void renderLayoutSplitter(Layout & layout, unsigned int index, double delta);


  private:
    bool m_drawLayouts;

    Display * m_window;

    GuiManager * m_guiManager;

};
#endif
