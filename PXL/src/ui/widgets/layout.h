#ifndef _LAYOUT_H
#define _LAYOUT_H


#include "nanovg.h"

class Display;
class Widget;
class GuiManager;
class Splitter;

enum StackDirection {
  HORIZONTAL,
  VERTICAL
};
class Layout {
  public:
     Layout(const std::string & name, Display & window, const glm::vec2 & position, const glm::vec2 & size);

    enum ExpandMode {
      WINDOW,
      PARENT,
      FIXED
    };

    inline ExpandMode getExpandModeX();

    inline void setExpandModeX(ExpandMode mode);

    inline ExpandMode getExpandModeY();

    inline void setExpandModeY(ExpandMode mode);

    inline ExpandMode getPositionModeX();

    inline void setPositionModeX(ExpandMode mode);

    inline ExpandMode getPositionModeY();

    inline void setPositionModeY(ExpandMode mode);

    inline void setMinHeight(float value);

    inline float getMinHeigh();

    inline void setMaxHeight(float value);

    inline float getMaxHeight();

    inline void setMinWidth(float value);

    inline float getMinWidth();

    inline void setMaxWidth(float value);

    inline float getMaxWidth();

    inline std::vector<class Widget*> getWidgets();

    virtual void addWidget(Widget & widget);

    void setWidgetWindow(Widget & widget);

    void setWidgetLayout(Widget & widget);

    virtual void removeWidget(Widget & widget);

    void setGuiManager(GuiManager & guiManager);

    inline GuiManager getGuiManager();

    inline void setDirection(StackDirection direction);

    inline StackDirection getDirection();

    void update(double delta);

    void updateSplitter(double delta, unsigned int index);

    void draw(NVGcontext & ctx);

    void drawSplitter(NVGcontext & ctx, double delta);

    inline void setPosition(const glm::vec2 & position);

    inline glm::vec2 getPosition();

    inline void setBackground(const NVGcolor & color);

    inline NVGcolor getBackground();

    inline void setComputedPosition(const glm::vec2 & position);

    inline glm::vec2 getComputedPosition();

    inline void setSize(const glm::vec2 & size);

    inline glm::vec2 getSize();

    inline void setComputedSize(const glm::vec2 & size);

    inline glm::vec2 getComputedSize();

    void computeStackDirection(Layout & previous, unsigned int index);

    void computePosition();

    void computeSize();

    glm::vec2 getRelativePosition();

    glm::vec2 getRelativeSize();

    inline void setName(const std::string & name);

    inline std::string getName();

    inline Layout getRoot();

    inline void setParent(Layout & layout);

    inline Layout Layout::getParent();

    void addChild(Layout & layout);

    inline std::vector<class Layout*> getChildren();

    void toggleAllWidgets();

    void onWindowResized(const SDL_Event & event);

    void onWindowSizeChanged(const SDL_Event & event);

    inline void setWindow(Display & window);

    inline Display getWindow();

    inline bool needRecomputeStackDirection();

    inline void setNeedRecomputeStackDirection(bool state);

    inline Splitter getSplitter();

    inline void setSplitter(Splitter & splitter);

     ~Layout();


  private:
    glm::vec2 m_position;

    glm::vec2 m_size;

    NVGcolor m_background;

    float m_minWidth;

    float m_minHeight;

    float m_maxWidth;

    float m_maxHeight;

    bool m_needRecomputeStackDirection;

    Splitter * m_splitter;

    ExpandMode m_positionModeX;

    ExpandMode m_positionModeY;

    ExpandMode m_expandModeX;

    ExpandMode m_expandModeY;

    glm::vec2 m_computedPosition;

    glm::vec2 m_computedSize;

    GuiManager * m_guiManager;

    StackDirection m_direction;

    std::string m_name;

    Layout * m_parent;

    Display * m_window;

    Widget * m_widgets;

    Layout * m_children;

};
inline Layout::ExpandMode Layout::getExpandModeX() {
}

inline void Layout::setExpandModeX(Layout::ExpandMode mode) {
}

inline Layout::ExpandMode Layout::getExpandModeY() {
}

inline void Layout::setExpandModeY(Layout::ExpandMode mode) {
}

inline Layout::ExpandMode Layout::getPositionModeX() {
}

inline void Layout::setPositionModeX(Layout::ExpandMode mode) {
}

inline Layout::ExpandMode Layout::getPositionModeY() {
}

inline void Layout::setPositionModeY(Layout::ExpandMode mode) {
}

inline void Layout::setMinHeight(float value) {
}

inline float Layout::getMinHeigh() {
}

inline void Layout::setMaxHeight(float value) {
}

inline float Layout::getMaxHeight() {
}

inline void Layout::setMinWidth(float value) {
}

inline float Layout::getMinWidth() {
}

inline void Layout::setMaxWidth(float value) {
}

inline float Layout::getMaxWidth() {
}

inline std::vector<class Widget*> Layout::getWidgets() {
}

inline GuiManager Layout::getGuiManager() {
}

inline void Layout::setDirection(StackDirection direction) {
}

inline StackDirection Layout::getDirection() {
}

inline void Layout::setPosition(const glm::vec2 & position) {
}

inline glm::vec2 Layout::getPosition() {
}

inline void Layout::setBackground(const NVGcolor & color) {
}

inline NVGcolor Layout::getBackground() {
}

inline void Layout::setComputedPosition(const glm::vec2 & position) {
}

inline glm::vec2 Layout::getComputedPosition() {
}

inline void Layout::setSize(const glm::vec2 & size) {
}

inline glm::vec2 Layout::getSize() {
}

inline void Layout::setComputedSize(const glm::vec2 & size) {
}

inline glm::vec2 Layout::getComputedSize() {
}

inline void Layout::setName(const std::string & name) {
}

inline std::string Layout::getName() {
}

inline Layout Layout::getRoot() {
}

inline void Layout::setParent(Layout & layout) {
}

inline Layout Layout::Layout::getParent() {
}

inline std::vector<class Layout*> Layout::getChildren() {
}

inline void Layout::setWindow(Display & window) {
}

inline Display Layout::getWindow() {
}

inline bool Layout::needRecomputeStackDirection() {
}

inline void Layout::setNeedRecomputeStackDirection(bool state) {
}

inline Splitter Layout::getSplitter() {
}

inline void Layout::setSplitter(Splitter & splitter) {
}

#endif
