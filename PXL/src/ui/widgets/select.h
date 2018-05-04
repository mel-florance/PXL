#ifndef _SELECT_H
#define _SELECT_H


#include "widget.h"

class Select : public Widget {
  public:
     Select(const glm::vec2 & position, const glm::vec2 & size);

     ~Select();

};
#endif
