#ifndef _SPLITTER_H
#define _SPLITTER_H


#include "widget.h"
#include "nanovg.h"

class Splitter : public Widget {
  public:
     Splitter(const glm::vec2 & position, const glm::vec2 & size);

    void update(double delta);

    void draw(NVGcontext & ctx, double delta);

    void onMouseMove(const SDL_Event & event);

    void onMouseDown(const SDL_Event & event);

    void onMouseUp(const SDL_Event & event);

    void onWindowResized(const SDL_Event & event);

    void onWindowSizeChanged(const SDL_Event & event);

    inline glm::vec2 getOffset();

    inline void setOffset(const glm::vec2 & offset);

     ~Splitter();


  private:
    NVGcolor m_background;

    glm::vec2 m_offset;

};
inline glm::vec2 Splitter::getOffset() {
}

inline void Splitter::setOffset(const glm::vec2 & offset) {
}

#endif
