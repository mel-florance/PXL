#ifndef _TREEVIEW_H
#define _TREEVIEW_H


#include "widget.h"
#include "nanovg.h"

class Icon;
struct CallbackData;
class Scrollbar;

class TreeView : public Widget {
  public:
     TreeView(const glm::vec2 & position, const glm::vec2 & size, const std::string & font);

    struct TreeItem {
        inline  TreeItem(const std::string & name, const std::string & path);

        std::string m_name;

        std::string m_path;

        Icon * m_icon;

        bool m_opened;

        bool m_hovered;

        bool m_selected;

        struct TreeItem* m_children;

        inline void addChild(TreeItem & child);

    };
    
    float getTreeItemHeight(glm::vec2 & position, TreeItem & item, unsigned int index);

    inline TreeItem getRoot();

    inline void deselectAllItems(TreeItem & root);

    inline void loadTreeItem(TreeItem & item, const std::string & path);

    inline void unloadTreeItem(TreeItem & item);

    static void onScrollbarDragged(const CallbackData & data);

    inline void init(const std::string & path);

    void update(double delta);

    void draw(NVGcontext & ctx, double delta);

    void drawTreeItem(NVGcontext & ctx, glm::vec2 & position, glm::vec2 & size, TreeItem & item, unsigned int depth, unsigned int index);

    void onTreeItemMouseMove(const SDL_Event & event, glm::vec2 & position, glm::vec2 & size, TreeItem & item, unsigned int depth, unsigned int index);

    void onTreeItemMouseUp(const SDL_Event & event, glm::vec2 & position, glm::vec2 & size, TreeItem & item, unsigned int depth, unsigned int index);

    void onKeyDown(const SDL_Event & event);

    void onTextInput(const SDL_Event & event);

    void onKeyUp(const SDL_Event & event);

    void onMouseMove(const SDL_Event & event);

    void onMouseWheel(const SDL_Event & event);

    void onMouseDown(const SDL_Event & event);

    void onMouseUp(const SDL_Event & event);

    void onWindowResized(const SDL_Event & event);

    void onWindowSizeChanged(const SDL_Event & event);

    inline void setOffsetScroll(float value);

     ~TreeView();


  private:
    TreeItem * m_root;

    Scrollbar * m_scrollbar;

    float m_offsetScroll;

    glm::vec4 m_margin;

    NVGalign m_align;

    std::string m_font;

    float m_fontSize;

    float m_blur;

    NVGcolor m_color;

    NVGcolor m_textHoverColor;

    NVGcolor m_background;

    NVGcolor m_backgroundHoverColor;

    float m_borderRadius;

    float m_opacity;

};
inline  TreeView::TreeItem::TreeItem(const std::string & name, const std::string & path) {
}

inline void TreeView::TreeItem::addChild(TreeView::TreeItem & child) {
}

inline TreeView::TreeItem TreeView::getRoot() {
}

inline void TreeView::deselectAllItems(TreeView::TreeItem & root) {
}

inline void TreeView::loadTreeItem(TreeView::TreeItem & item, const std::string & path) {
}

inline void TreeView::unloadTreeItem(TreeView::TreeItem & item) {
}

inline void TreeView::init(const std::string & path) {
}

inline void TreeView::setOffsetScroll(float value) {
}

#endif
