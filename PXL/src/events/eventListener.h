#ifndef _EVENTLISTENER_H
#define _EVENTLISTENER_H


class Widget;

struct CallbackData {
    Widget * sender;

};
class EventListener {
  public:
     EventListener();

     ~EventListener();

    typedef void EventListenerFnPtr;

    inline void addEventListener(const std::string & name, const EventListenerFnPtr & callback);

    inline bool hasListener(const std::string & name);

    inline void handleEventListener(const std::string & name, const CallbackData & data);


  private:
    EventListenerFnPtr m_listeners;

};
inline void EventListener::addEventListener(const std::string & name, const EventListener::EventListenerFnPtr & callback) {
}

inline bool EventListener::hasListener(const std::string & name) {
}

inline void EventListener::handleEventListener(const std::string & name, const CallbackData & data) {
}

#endif
