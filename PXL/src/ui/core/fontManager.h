#ifndef _FONTMANAGER_H
#define _FONTMANAGER_H


#include "manager.h"
#include "nanovg.h"

class FontManager : public Manager {
  public:
     FontManager();

    inline void setContext(NVGcontext & ctx);

    void loadFonts(char & path);

    virtual  ~FontManager();


  private:
    NVGcontext * m_ctx;

};
inline void FontManager::setContext(NVGcontext & ctx) {
}

#endif
