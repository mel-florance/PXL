#ifndef _INPUT_H
#define _INPUT_H


#include "widget.h"
#include "nanovg.h"

class Input : public Widget {
  public:
     Input(glm::vec2 & position, glm::vec2 & size, const std::string & font);

     ~Input();

    struct InputText {
        std::string text;

        NVGalign align;

        std::string font;

        NVGcolor color;

        float fontSize;

        float blur;

        float width;

        std::string placeholder;

        bool drawPlaceholder;

    };
    
    struct InputCaret {
        glm::vec2 position;

        glm::vec2 size;

        NVGcolor background;

        Uint32 blinkStart;

        Uint32 blinkSpeed;

        bool blinking;

    };
    
    inline void setPlaceholder(const std::string & placeholder);

    inline std::string getPlaceholder();

    inline void setBackground(const NVGcolor & color);

    inline NVGcolor getBackground();

    inline void setMargin(const glm::vec4 & margin);

    inline glm::vec4 getMargin();

    inline std::string getText();

    inline void setText(const std::string & text);

    inline void clearText();

    inline void setCaretPosition(glm::vec2 & position);

    inline glm::vec2 getCaretPosition();

    inline void setCaretSize(glm::vec2 & size);

    inline glm::vec2 getCaretSize();

    inline void setCaretBackground(const NVGcolor & background);

    inline NVGcolor getCaretBackground();

    void update(double delta);

    void draw(NVGcontext & ctx, double delta);

    void drawBackground(NVGcontext & ctx, glm::vec2 & position, glm::vec2 & size);

    void drawText(NVGcontext & ctx, glm::vec2 & position, glm::vec2 & size);

    void drawCaret(NVGcontext & ctx, glm::vec2 & position, glm::vec2 & size);

    void drawIcon(NVGcontext & ctx, glm::vec2 & position, glm::vec2 & size);

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

    glm::vec4 m_margin;

    InputCaret * m_caret;

    InputText m_text;

};
inline void Input::setPlaceholder(const std::string & placeholder) {
}

inline std::string Input::getPlaceholder() {
}

inline void Input::setBackground(const NVGcolor & color) {
}

inline NVGcolor Input::getBackground() {
}

inline void Input::setMargin(const glm::vec4 & margin) {
}

inline glm::vec4 Input::getMargin() {
}

inline std::string Input::getText() {
}

inline void Input::setText(const std::string & text) {
}

inline void Input::clearText() {
}

inline void Input::setCaretPosition(glm::vec2 & position) {
}

inline glm::vec2 Input::getCaretPosition() {
}

inline void Input::setCaretSize(glm::vec2 & size) {
}

inline glm::vec2 Input::getCaretSize() {
}

inline void Input::setCaretBackground(const NVGcolor & background) {
}

inline NVGcolor Input::getCaretBackground() {
}

#endif
