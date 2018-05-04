#ifndef _TABS_H
#define _TABS_H


#include "widget.h"
#include "nanovg.h"

struct CallbackData;
class Icon;
class Scrollbar;

class Tabs : public Widget {
  public:
     Tabs(const glm::vec2 & position, const glm::vec2 & size);

    enum TabDirection {
      HORIZONTAL,
      VERTICAL
    };

    static void onScrollbarDragged(const CallbackData & data);

    inline void setOffsetScroll(float value);

    struct TabHeader {
        inline  TabHeader(const std::string & name);

        inline  ~TabHeader();

        std::string m_name;

        std::string m_shortcut;

        Icon * m_icon;

        float m_width;

        bool m_hovered=  false;

    };
    
    struct TabContent {
        inline  TabContent(const std::string & name, Widget & widget = nullptr);

        inline  ~TabContent();

        std::string m_name;

        Widget * m_widget;

    };
    
    struct Tab {
        inline  Tab(const std::string & name, TabHeader & header, TabContent & content);

        inline std::string getName();

        inline void setName(const std::string & name);

        std::string m_name;

        TabHeader * m_header;

        TabContent * m_content;

    };
    
    void update(double delta);

    void draw(NVGcontext & ctx, double delta);

    void onMouseMove(const SDL_Event & event);

    void onMouseDown(const SDL_Event & event);

    void onMouseUp(const SDL_Event & event);

    void onWindowResized(const SDL_Event & event);

    void onWindowSizeChanged(const SDL_Event & event);

    Tab addTab(const std::string & name);

    inline bool removeTab(const std::string & name);

     ~Tabs();


  private:
    TabDirection m_direction=  HORIZONTAL;

    Scrollbar * m_scrollbar;

    NVGalign m_align;

    std::string m_font;

    float m_fontSize;

    float m_blur;

    NVGcolor m_color;

    NVGcolor m_background;

    glm::vec4 m_margin;

    unsigned int m_activeTab;

    Tab * m_tabs;

    float m_offsetScroll;

};
inline void Tabs::setOffsetScroll(float value) {
}

inline  Tabs::TabHeader::TabHeader(const std::string & name) {
}

inline  Tabs::TabHeader::~TabHeader() {
}

inline  Tabs::TabContent::TabContent(const std::string & name, Widget & widget) {
}

inline  Tabs::TabContent::~TabContent() {
}

inline  Tabs::Tab::Tab(const std::string & name, Tabs::TabHeader & header, Tabs::TabContent & content) {
}

inline std::string Tabs::Tab::getName() {
}

inline void Tabs::Tab::setName(const std::string & name) {
}

inline bool Tabs::removeTab(const std::string & name) {
}

#endif
