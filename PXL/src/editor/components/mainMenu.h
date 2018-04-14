#pragma once

#include "../../ui/widgets/layout.h"
#include "../../ui/widgets/menu.h"
#include "../EditorComponent.h"

class MainMenu : public EditorComponent
{
public:
	MainMenu(Engine* engine);

	void init();

	inline static void exitApplication(CallbackData data)
	{
		data.sender->getWindow()->setIsClosed(true);
	}

	inline static void setFullscreen(CallbackData data)
	{
		Display* window = data.sender->getWindow();
		bool isFullscreen = window->isFullscreen();

		SDL_SetWindowFullscreen(window->getWindow(), !isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
		window->setIsFullscreen(isFullscreen != true);
	}

	inline Menu* getMenu() { return m_menu; }

	~MainMenu();
private:
	Menu* m_menu;
};

