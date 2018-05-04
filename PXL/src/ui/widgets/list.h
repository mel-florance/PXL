#ifndef _LIST_H
#define _LIST_H


#include "widget.h"
#include "nanovg.h"

class List : public Widget {
  public:
     List(const glm::vec2 & position, const glm::vec2 & size, const std::string & font);

     ~List();

    void update(double delta);

    void draw(NVGcontext & ctx, double delta);

    void addItem(const std::string & name);

    inline void removeItem(const std::string & item);


  private:
    std::string m_list;

    glm::vec4 m_margin;

    NVGalign m_align;

    std::string m_font;

    float m_fontSize;

    float m_blur;

    glm::vec4 m_color;

    NVGcolor m_background;

};
inline void List::removeItem(const std::string & item) {
}

#endif
