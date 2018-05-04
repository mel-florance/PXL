#ifndef _TEXT_H
#define _TEXT_H


#include "widget.h"
#include "nanovg.h"

class Text : public Widget {
  public:
     Text(const std::string & text, NVGcolor & color, glm::vec2 & position, const std::string & font);

     ~Text();

    inline void setText(const std::string & text);

    inline std::string getText();

    inline void setFontSize(float size);

    inline float getFontsize();

    void draw(NVGcontext & ctx, double delta);

    inline void onKeyDown(const SDL_Event & event);

    inline void onTextInput(const SDL_Event & event);

    inline void onKeyUp(const SDL_Event & event);

    inline void onMouseMove(const SDL_Event & event);

    inline void onMouseDown(const SDL_Event & event);

    inline void onMouseUp(const SDL_Event & event);


  private:
    NVGcolor m_color;

    std::string m_text;

    std::string m_font;

    float m_fontSize;

    float m_blur;

    Uint32 m_align;

};
inline void Text::setText(const std::string & text) {
}

inline std::string Text::getText() {
}

inline void Text::setFontSize(float size) {
}

inline float Text::getFontsize() {
}

inline void Text::onKeyDown(const SDL_Event & event) {
}

inline void Text::onTextInput(const SDL_Event & event) {
}

inline void Text::onKeyUp(const SDL_Event & event) {
}

inline void Text::onMouseMove(const SDL_Event & event) {
}

inline void Text::onMouseDown(const SDL_Event & event) {
}

inline void Text::onMouseUp(const SDL_Event & event) {
}

#endif
