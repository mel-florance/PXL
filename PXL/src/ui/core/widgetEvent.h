#ifndef _WIDGETEVENT_H
#define _WIDGETEVENT_H


class WidgetEvent {
  public:
     WidgetEvent();

    typedef void EventFnPtr;

    void handleEvent(const std::string & name, const SDL_Event & event);

    inline virtual void onKeyDown(const SDL_Event & event);

    inline virtual void onTextInput(const SDL_Event & event);

    inline virtual void onKeyUp(const SDL_Event & event);

    inline virtual void onMouseWheel(const SDL_Event & event);

    inline virtual void onMouseMove(const SDL_Event & event);

    inline virtual void onMouseDown(const SDL_Event & event);

    inline virtual void onMouseUp(const SDL_Event & event);

    inline virtual void onWindowResized(const SDL_Event & event);

    inline virtual void onWindowSizeChanged(const SDL_Event & event);

     ~WidgetEvent();


  private:
    EventFnPtr m_events;

};
inline void WidgetEvent::onKeyDown(const SDL_Event & event) {
}

inline void WidgetEvent::onTextInput(const SDL_Event & event) {
}

inline void WidgetEvent::onKeyUp(const SDL_Event & event) {
}

inline void WidgetEvent::onMouseWheel(const SDL_Event & event) {
}

inline void WidgetEvent::onMouseMove(const SDL_Event & event) {
}

inline void WidgetEvent::onMouseDown(const SDL_Event & event) {
}

inline void WidgetEvent::onMouseUp(const SDL_Event & event) {
}

inline void WidgetEvent::onWindowResized(const SDL_Event & event) {
}

inline void WidgetEvent::onWindowSizeChanged(const SDL_Event & event) {
}

#endif
