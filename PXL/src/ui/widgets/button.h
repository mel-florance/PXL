#ifndef _BUTTON_H
#define _BUTTON_H


#include "widget.h"
#include "nanovg.h"

class Button : public Widget {
  public:
     Button(glm::vec2 & position, glm::vec2 & size, const std::string & font);

     ~Button();

    inline void setBackground(NVGcolor & color);

    inline NVGcolor getBackground();

    inline void setMargin(const glm::vec4 & margin);

    inline glm::vec4 getMargin();

    inline void setText(const std::string & text);

    inline std::string getText();

    void update(double delta);

    void draw(NVGcontext & ctx, double delta);

    void drawBackground(NVGcontext & ctx, glm::vec2 & position, glm::vec2 & size);

    void drawText(NVGcontext & ctx, glm::vec2 & position, glm::vec2 & size);

    void onKeyDown(const SDL_Event & event);

    void onTextInput(const SDL_Event & event);

    void onKeyUp(const SDL_Event & event);

    void onMouseMove(const SDL_Event & event);

    void onMouseDown(const SDL_Event & event);

    void onMouseUp(const SDL_Event & event);

    void onWindowResized(const SDL_Event & event);

    void onWindowSizeChanged(const SDL_Event & event);


  private:
    NVGcolor m_background;

    NVGcolor m_hightlight;

    float m_borderRadius;

    glm::vec4 m_margin;


  public:
    struct ButtonText {
        std::string text;

        std::string font;

        NVGalign align;

        NVGcolor color;

        NVGcolor shadow;

        float fontSize;

        float blur;

        float width;

    };
    
};
inline void Button::setBackground(NVGcolor & color) {
}

inline NVGcolor Button::getBackground() {
}

inline void Button::setMargin(const glm::vec4 & margin) {
}

inline glm::vec4 Button::getMargin() {
}

inline void Button::setText(const std::string & text) {
}

inline std::string Button::getText() {
}

#endif
