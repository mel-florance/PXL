#ifndef _WINDOW_H
#define _WINDOW_H


#include "widget.h"
#include "nanovg.h"

struct CallbackData;
class Rect;

class Window : public Widget {
  public:
     Window(const std::string & text, const glm::vec2 & position, const glm::vec2 & size, const std::string & font);

     ~Window();

    void onKeyDown(const SDL_Event & event);

    void onTextInput(const SDL_Event & event);

    void onKeyUp(const SDL_Event & event);

    void onMouseMove(const SDL_Event & event);

    void onMouseDown(const SDL_Event & event);

    void onMouseUp(const SDL_Event & event);

    void onWindowResized(const SDL_Event & event);

    void onWindowSizeChanged(const SDL_Event & event);

    static void onClosed(const CallbackData & data);

    void drawBackground(NVGcontext & ctx, glm::vec2 & position);

    void drawShadow(NVGcontext & ctx, glm::vec2 & position);

    void drawHeader(NVGcontext & ctx, glm::vec2 & position);

    void drawHeaderText(NVGcontext & ctx, glm::vec2 & position);

    void drawIcon(NVGcontext & ctx, glm::vec2 & position);

    void draw(NVGcontext & ctx, double delta);

    void update(double delta);

    inline void setDrawingShadow(bool state);

    inline bool isDrawingShadow();

    inline void setOpacity(float value);

    inline float getOpacity();

    inline void setHeaderFixedBottom(bool state);

    inline bool getHeaderFixedBottom();

    inline void setMargin(const glm::vec4 & margin);

    inline glm::vec4 getMargin();

    inline void setMarginTop(float value);

    inline float getMarginTop();

    inline void setMarginRight(float value);

    inline float getMarginRight();

    inline void setMarginBottom(float value);

    inline float getMarginBottom();

    inline void setMarginLeft(float value);

    inline float getMarginLeft();


  private:
    NVGpaint m_shadowPaint;

    NVGpaint m_headerPaint;

    bool m_drawingShadow;

    float m_opacity;

    glm::vec4 m_margin;

    glm::vec2 m_windowDragOffset;


  public:
    struct WindowHeader {
        Rect * rect;

        std::string text;

        NVGalign align;

        std::string font;

        float fontSize;

        float blur;

        NVGcolor color;

        bool isFixedBottom;

    };
    

  private:
    NVGcolor m_background;

    float m_borderRadius;

};
inline void Window::setDrawingShadow(bool state) {
}

inline bool Window::isDrawingShadow() {
}

inline void Window::setOpacity(float value) {
}

inline float Window::getOpacity() {
}

inline void Window::setHeaderFixedBottom(bool state) {
}

inline bool Window::getHeaderFixedBottom() {
}

inline void Window::setMargin(const glm::vec4 & margin) {
}

inline glm::vec4 Window::getMargin() {
}

inline void Window::setMarginTop(float value) {
}

inline float Window::getMarginTop() {
}

inline void Window::setMarginRight(float value) {
}

inline float Window::getMarginRight() {
}

inline void Window::setMarginBottom(float value) {
}

inline float Window::getMarginBottom() {
}

inline void Window::setMarginLeft(float value) {
}

inline float Window::getMarginLeft() {
}

#endif
