#ifndef _MENU_H
#define _MENU_H


#include "widget.h"
#include "eventListener.h"
#include "nanovg.h"

class Icon;

class Menu : public Widget {
  public:
     Menu(const glm::vec2 & position, const glm::vec2 & size, const std::string & font);

    struct MenuItem : public EventListener {
        inline  MenuItem(const std::string & data, const EventListenerFnPtr & callback = NULL, const std::string & shortcut = "", const std::string & icon = "");

        inline  ~MenuItem();

        inline void addIcon();

        inline void setIconPosition(const glm::vec2 & position);

        inline void setIconSize(const glm::vec2 & size);

        inline void setIconSymbol(const std::string & name);

        inline MenuItem addChild(const std::string & data, const EventListenerFnPtr & callback = NULL, const std::string & shortcut = "", const std::string & icon = "");

        inline MenuItem addSeparator();

        inline unsigned int getNbChildIcons();

        inline unsigned int getNbSeparators();

        inline bool hasIcon();

        std::string m_data;

        std::string m_shortcut;

        Icon * m_icon;

        MenuItem * m_children;

        float m_width;

        bool m_hovered;

        bool m_opened;

        bool m_isSeparator;

    };
    
    void onMouseMove(const SDL_Event & event);

    void onMouseDown(const SDL_Event & event);

    void onMouseUp(const SDL_Event & event);

    void onKeyDown(const SDL_Event & event);

    inline void setDrawingShadow(bool state);

    inline bool isDrawingShadow();

    void update(double delta);

    void draw(NVGcontext & ctx, double delta);

    inline MenuItem addMenuItem(const std::string & data, const EventListenerFnPtr & callback = NULL, const std::string & shortcut = "");

     ~Menu();


  private:
    MenuItem * m_items;

    NVGpaint m_shadowPaint;

    bool m_drawingShadow;

    float m_borderRadius;

    float m_minHeight;

    float m_minFontSize;

    glm::vec4 m_margin;

    NVGalign m_align;

    std::string m_font;

    float m_fontSize;

    float m_blur;

    NVGcolor m_color;

    NVGcolor m_background;

};
inline  Menu::MenuItem::MenuItem(const std::string & data, const EventListenerFnPtr & callback, const std::string & shortcut, const std::string & icon) {
}

inline  Menu::MenuItem::~MenuItem() {
}

inline void Menu::MenuItem::addIcon() {
}

inline void Menu::MenuItem::setIconPosition(const glm::vec2 & position) {
}

inline void Menu::MenuItem::setIconSize(const glm::vec2 & size) {
}

inline void Menu::MenuItem::setIconSymbol(const std::string & name) {
}

inline Menu::MenuItem Menu::MenuItem::addChild(const std::string & data, const EventListenerFnPtr & callback, const std::string & shortcut, const std::string & icon) {
}

inline Menu::MenuItem Menu::MenuItem::addSeparator() {
}

inline unsigned int Menu::MenuItem::getNbChildIcons() {
}

inline unsigned int Menu::MenuItem::getNbSeparators() {
}

inline bool Menu::MenuItem::hasIcon() {
}

inline void Menu::setDrawingShadow(bool state) {
}

inline bool Menu::isDrawingShadow() {
}

inline Menu::MenuItem Menu::addMenuItem(const std::string & data, const EventListenerFnPtr & callback, const std::string & shortcut) {
}

#endif
