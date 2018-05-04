#ifndef _BOXLAYOUT_H
#define _BOXLAYOUT_H


#include "layout.h"

class Display;

class BoxLayout : public Layout {
  public:
     BoxLayout(const std::string & name, Display & window, const glm::vec2 & position, const glm::vec2 & size);

     ~BoxLayout();

};
#endif
