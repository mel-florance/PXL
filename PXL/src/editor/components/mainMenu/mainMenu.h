#ifndef _MAINMENU_H
#define _MAINMENU_H


#include "editorComponent.h"

class Engine;
class Menu;
struct CallbackData;

class MainMenu : public EditorComponent {
  public:
     MainMenu(Engine & engine);

    void init();

    inline Menu getMenu();

    static inline void exitApplication(const CallbackData & data);

    static inline void setFullscreen(const CallbackData & data);

    static inline void openPreferencesModal(const CallbackData & data);

     ~MainMenu();


  private:
    Menu * m_menu;

};
inline Menu MainMenu::getMenu() {
}

inline void MainMenu::exitApplication(const CallbackData & data)
{
}

inline void MainMenu::setFullscreen(const CallbackData & data)
{
}

inline void MainMenu::openPreferencesModal(const CallbackData & data)
{
}

#endif
