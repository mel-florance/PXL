#ifndef _FORM_H
#define _FORM_H


#include "widget.h"

class Form : public Widget {
  public:
     Form(const glm::vec2 & position, const glm::vec2 & size);

     ~Form();

};
#endif
