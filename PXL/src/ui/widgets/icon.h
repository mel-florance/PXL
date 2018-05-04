#ifndef _ICON_H
#define _ICON_H


#include "widget.h"

class Icon : public Widget {
  public:
    typedef std::map<std::string, int> SymbolsMap;

     Icon(const std::string & name, const glm::vec2 & position, const glm::vec2 & size);

    void onMouseMove(const SDL_Event & event);

    inline void setSymbol(const std::string & name);

    virtual char get();

    inline int getSymbol();

     ~Icon();


  private:
    int m_symbol;

    char m_str[8];

    SymbolsMap m_icons;

};
inline void Icon::setSymbol(const std::string & name) {
}

inline int Icon::getSymbol() {
}

#endif
