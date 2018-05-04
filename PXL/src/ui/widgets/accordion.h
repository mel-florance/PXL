#ifndef _ACCORDION_H
#define _ACCORDION_H


#include "widget.h"
#include "nanovg.h"

class Icon;

class Accordion : public Widget {
  public:
     Accordion(const glm::vec2 & position, const glm::vec2 & size);

    void update(double delta);

    void draw(NVGcontext & ctx, double delta);

    struct Section {
        inline  Section(const std::string & title);

        inline  ~Section();

        enum StackDirection {
          HORIZONTAL,
          VERTICAL
        };

        inline void addWidget(Widget & widget);

        inline bool removeWidget(Widget & widget);

        inline float getWidgetHeight(Widget & widget, float & height);

        inline float getWidgetsHeight();

        bool m_opened;

        bool m_hovered;

        std::string m_title;

        Icon * m_icon;

        StackDirection m_direction;

        Widget * m_widgets;

    };
    
    void drawSectionWidget(NVGcontext & ctx, double delta, Widget & widget);

    inline Section addSection(const std::string & title);

    inline bool removeSection(const std::string & name);

    void onMouseMove(const SDL_Event & event);

    void onMouseDown(const SDL_Event & event);

    void onMouseUp(const SDL_Event & event);

    void onWindowResized(const SDL_Event & event);

    void onWindowSizeChanged(const SDL_Event & event);

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

     ~Accordion();


  private:
    glm::vec4 m_margin;

    Section * m_sections;

};
inline  Accordion::Section::Section(const std::string & title) {
}

inline  Accordion::Section::~Section() {
}

inline void Accordion::Section::addWidget(Widget & widget) {
}

inline bool Accordion::Section::removeWidget(Widget & widget) {
}

inline float Accordion::Section::getWidgetHeight(Widget & widget, float & height) {
}

inline float Accordion::Section::getWidgetsHeight() {
}

inline Accordion::Section Accordion::addSection(const std::string & title) {
}

inline bool Accordion::removeSection(const std::string & name) {
}

inline void Accordion::setMargin(const glm::vec4 & margin) {
}

inline glm::vec4 Accordion::getMargin() {
}

inline void Accordion::setMarginTop(float value) {
}

inline float Accordion::getMarginTop() {
}

inline void Accordion::setMarginRight(float value) {
}

inline float Accordion::getMarginRight() {
}

inline void Accordion::setMarginBottom(float value) {
}

inline float Accordion::getMarginBottom() {
}

inline void Accordion::setMarginLeft(float value) {
}

inline float Accordion::getMarginLeft() {
}

#endif
