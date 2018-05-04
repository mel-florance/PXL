#ifndef _WIDGETSTATE_H
#define _WIDGETSTATE_H


class WidgetState {
  public:
     WidgetState();

    inline void addState(const std::string & name, bool state = false);

    inline bool getState(const std::string & name);

    inline void setState(const std::string & name, bool value);

    virtual  ~WidgetState();


  private:
    std::string, bool m_states;

};
inline void WidgetState::addState(const std::string & name, bool state) {
}

inline bool WidgetState::getState(const std::string & name) {
}

inline void WidgetState::setState(const std::string & name, bool value) {
}

#endif
