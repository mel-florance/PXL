#ifndef _TOOLTIP_H
#define _TOOLTIP_H


#include "widget.h"

class Tooltip : public Widget {
  public:
     Tooltip(const glm::vec2 & position, const glm::vec2 & size);

     ~Tooltip();

};
#endif
