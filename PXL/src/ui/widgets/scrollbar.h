#ifndef _SCROLLBAR_H
#define _SCROLLBAR_H


#include "widget.h"
#include "nanovg.h"

class Icon;
class Rect;

class Scrollbar : public Widget {
  public:
     Scrollbar(const glm::vec2 & position, const glm::vec2 & size);

    void update(double delta);

    void draw(NVGcontext & ctx, double delta);

    inline void setMarginTop(float margin);

    inline void setMarginRight(float margin);

    inline void setMarginBottom(float margin);

    inline void setMarginLeft(float margin);

    void onKeyDown(const SDL_Event & event);

    void onTextInput(const SDL_Event & event);

    void onKeyUp(const SDL_Event & event);

    void onMouseMove(const SDL_Event & event);

    void onMouseWheel(const SDL_Event & event);

    void onMouseDown(const SDL_Event & event);

    void onMouseUp(const SDL_Event & event);

    void onWindowResized(const SDL_Event & event);

    void onWindowSizeChanged(const SDL_Event & event);

    void computeHandleHeight(float parentHeight, float scrollMax);

    inline float getHandleHeight();

    inline float getHandleDragOffset();

    inline void setHandleDragOffset(float offset);

    inline void setHandleMarginTop(float margin);

    inline void setHandleMarginRight(float margin);

    inline void setHandleMarginBottom(float margin);

    inline void setHandleMarginLeft(float margin);

     ~Scrollbar();


  private:
    NVGcolor m_background;

    NVGcolor m_handleBackground;

    glm::vec4 m_margin;

    float m_handleHeight;

    Icon * m_firstIcon;

    Icon * m_secondIcon;

    Rect * m_handle;

    glm::vec4 m_handleMargin;

    bool m_handleDragged;

    float m_handleDragOffset;

};
inline void Scrollbar::setMarginTop(float margin) {
}

inline void Scrollbar::setMarginRight(float margin) {
}

inline void Scrollbar::setMarginBottom(float margin) {
}

inline void Scrollbar::setMarginLeft(float margin) {
}

inline float Scrollbar::getHandleHeight() {
}

inline float Scrollbar::getHandleDragOffset() {
}

inline void Scrollbar::setHandleDragOffset(float offset) {
}

inline void Scrollbar::setHandleMarginTop(float margin) {
}

inline void Scrollbar::setHandleMarginRight(float margin) {
}

inline void Scrollbar::setHandleMarginBottom(float margin) {
}

inline void Scrollbar::setHandleMarginLeft(float margin) {
}

#endif
