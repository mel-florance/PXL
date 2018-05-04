#ifndef _WIDGET_H
#define _WIDGET_H


#include "rect.h"
#include "eventListener.h"
#include "widgetEvent.h"
#include "widgetState.h"
#include "nanovg.h"

class Display;
class Layout;
struct CallbackData;
class Icon;

class Widget : public Rect, public EventListener, public WidgetEvent, public WidgetState {
  public:
     Widget(const glm::vec2 & position, const glm::vec2 & size);

     ~Widget();

    enum ExpandMode {
      LAYOUT,
      PARENT,
      FIXED
    };

    enum Alignment {
      TOP_LEFT,
      TOP,
      TOP_RIGHT,
      RIGHT,
      BOTTOM_RIGHT,
      BOTTOM,
      BOTTOM_LEFT,
      LEFT
    };

    inline ExpandMode getExpandModeX();

    inline void setExpandModeX(ExpandMode mode);

    inline ExpandMode getExpandModeY();

    inline void setExpandModeY(ExpandMode mode);

    inline ExpandMode getPositionModeX();

    inline void setPositionModeX(ExpandMode mode);

    inline ExpandMode getPositionModeY();

    inline void setPositionModeY(ExpandMode mode);

    inline Alignment getAlignement();

    inline void setAlignment(Alignment alignment);

    inline std::string getName();

    inline void setName(const std::string & name);

    inline void setWindow(Display & window);

    inline Display getWindow();

    inline virtual void setScreen(const glm::vec2 & screen);

    inline virtual glm::vec2 getScreen();

    inline void setParent(Widget & parent);

    inline Widget getParent();

    glm::vec2 getRelativePosition();

    glm::vec2 getRelativeSize();

    virtual void setCentered();

    bool intersects(const glm::vec2 & point);

    inline void setLayout(Layout & layout);

    inline Layout getLayout();

    void addChild(Widget & child);

    inline std::vector<Widget*> getChildren();

    inline virtual void draw(NVGcontext & ctx, double delta);

    inline virtual void update(double delta);

    static void onClosed(const CallbackData & data);

    void setIcon(Icon & icon);

    Icon getIcon();

    inline bool hasIcon();

    inline virtual void addRow();

    inline virtual void addItem(const std::string & item);

    inline virtual MenuItem addMenuItem(std::string & item);

    inline virtual std::string getText();

    inline void setUnits(const std::string & units);

    inline std::string getUnits();

    inline void setMinHeight(float value);

    inline float getMinHeigh();

    inline void setMaxHeight(float value);

    inline float getMaxHeight();

    inline void setMinWidth(float value);

    inline float getMinWidth();

    inline void setMaxWidth(float value);

    inline float getMaxWidth();

    void computePosition();

    void computeSize();

    inline void setComputedPosition(const glm::vec2 & position);

    inline glm::vec2 getComputedPosition();

    inline void setComputedSize(const glm::vec2 & size);

    inline glm::vec2 getComputedSize();

    glm::vec2 m_dragStart;

    glm::vec2 m_dragEnd;

    glm::vec2 m_dragDelta;

    glm::vec2 m_mouseDelta;

    glm::vec3 m_mouseStates;

    glm::vec2 m_mouse;

    glm::vec2 m_mouseRel;


  private:
    Alignment m_alignment;

    ExpandMode m_positionModeX;

    ExpandMode m_positionModeY;

    ExpandMode m_expandModeX;

    ExpandMode m_expandModeY;

    glm::vec2 m_computedPosition;

    glm::vec2 m_computedSize;

    float m_minWidth;

    float m_minHeight;

    float m_maxWidth;

    float m_maxHeight;

    bool m_visible;

    std::string m_name;

    Icon * m_icon;

    Display * m_window;

    Layout * m_layout;

    Widget * m_parent;

    std::string m_units;

    glm::vec2 m_screen;

    class Widget* m_children;

};
inline Widget::ExpandMode Widget::getExpandModeX() {
}

inline void Widget::setExpandModeX(Widget::ExpandMode mode) {
}

inline Widget::ExpandMode Widget::getExpandModeY() {
}

inline void Widget::setExpandModeY(Widget::ExpandMode mode) {
}

inline Widget::ExpandMode Widget::getPositionModeX() {
}

inline void Widget::setPositionModeX(Widget::ExpandMode mode) {
}

inline Widget::ExpandMode Widget::getPositionModeY() {
}

inline void Widget::setPositionModeY(Widget::ExpandMode mode) {
}

inline Widget::Alignment Widget::getAlignement() {
}

inline void Widget::setAlignment(Widget::Alignment alignment) {
}

inline std::string Widget::getName() {
}

inline void Widget::setName(const std::string & name) {
}

inline void Widget::setWindow(Display & window) {
}

inline Display Widget::getWindow() {
}

inline void Widget::setScreen(const glm::vec2 & screen) {
}

inline glm::vec2 Widget::getScreen() {
}

inline void Widget::setParent(Widget & parent) {
}

inline Widget Widget::getParent() {
}

inline void Widget::setLayout(Layout & layout) {
}

inline Layout Widget::getLayout() {
}

inline std::vector<Widget*> Widget::getChildren() {
}

inline void Widget::draw(NVGcontext & ctx, double delta) {
}

inline void Widget::update(double delta) {
}

inline bool Widget::hasIcon() {
}

inline void Widget::addRow() {
}

inline void Widget::addItem(const std::string & item) {
}

inline MenuItem Widget::addMenuItem(std::string & item) {
}

inline std::string Widget::getText() {
}

inline void Widget::setUnits(const std::string & units) {
}

inline std::string Widget::getUnits() {
}

inline void Widget::setMinHeight(float value) {
}

inline float Widget::getMinHeigh() {
}

inline void Widget::setMaxHeight(float value) {
}

inline float Widget::getMaxHeight() {
}

inline void Widget::setMinWidth(float value) {
}

inline float Widget::getMinWidth() {
}

inline void Widget::setMaxWidth(float value) {
}

inline float Widget::getMaxWidth() {
}

inline void Widget::setComputedPosition(const glm::vec2 & position) {
}

inline glm::vec2 Widget::getComputedPosition() {
}

inline void Widget::setComputedSize(const glm::vec2 & size) {
}

inline glm::vec2 Widget::getComputedSize() {
}

#endif
