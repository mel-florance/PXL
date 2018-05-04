#ifndef _GROUP_H
#define _GROUP_H


#include "widget.h"

class Group : public Widget {
  public:
     Group(const glm::vec2 & position, const glm::vec2 & size);

     ~Group();

};
#endif
