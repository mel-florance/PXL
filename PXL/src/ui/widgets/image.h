#ifndef _IMAGE_H
#define _IMAGE_H


#include "widget.h"
#include "nanovg.h"

class Image : public Widget {
  public:
     Image(NVGcontext & ctx, const std::string & name, glm::vec2 & position, glm::vec2 & size);

     ~Image();

    inline std::string getName();

    inline void setName(const std::string & name);

    void draw(NVGcontext & ctx, double delta);


  private:
    std::string m_name;

    NVGcontext * m_ctx;

    int m_image;

};
inline std::string Image::getName() {
}

inline void Image::setName(const std::string & name) {
}

#endif
