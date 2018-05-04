#ifndef _DISPLAY_H
#define _DISPLAY_H


class Display {
  public:
     Display(glm::vec2 & size, const std::string & title, const std::string & icon);

    virtual  ~Display();

    bool isClosed();

    inline void setIsClosed(bool value);

    inline bool isFullscreen();

    inline void setIsFullscreen(bool state);

    void swapBuffers();

    inline glm::vec2 getSize();

    inline void setSize(const glm::vec2 & size);

    inline double getAspect();

    inline SDL_Window getWindow();

    bool addIcon(const std::string & filename);

    inline void setCurrentCursor(const std::string & name);

    SDL_Cursor getMCursor(const std::string & name);

    inline SDL_Cursor getCurrentMouseCursor();

    glm::vec2 m_size;


  private:
    SDL_Window m_window;

    SDL_GLContext m_glContext;

    std::string, SDL_Cursor* m_cursors;

    SDL_Cursor m_currentCursor;

    bool m_isClosed;

    bool m_isFullscreen;

};
inline void Display::setIsClosed(bool value) {
}

inline bool Display::isFullscreen() {
}

inline void Display::setIsFullscreen(bool state) {
}

inline glm::vec2 Display::getSize() {
}

inline void Display::setSize(const glm::vec2 & size) {
}

inline double Display::getAspect() {
}

inline SDL_Window Display::getWindow() {
}

inline void Display::setCurrentCursor(const std::string & name) {
}

inline SDL_Cursor Display::getCurrentMouseCursor() {
}

#endif
