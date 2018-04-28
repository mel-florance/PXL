#pragma once

#include "../../ui/widgets/layout.h"
#include "../../ui/widgets/menu.h"
#include "../../ui/widgets/window.h"
#include "../EditorComponent.h"
#include "../../ui/core/guiManager.h"

class MainMenu : public EditorComponent
{
public:
	MainMenu(Engine* engine);

	void init();
	inline Menu* getMenu() { return m_menu; }

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

	inline static void openPreferencesModal(CallbackData data)
	{
		Layout* layout = data.sender->getLayout()->getParent();

		if (layout != nullptr)
		{
			std::cout << layout->getName() << std::endl;
			glm::vec2 wsize = layout->getWindow()->getSize();

			Window* modal = new Window("Preferences", glm::vec2((wsize.x * 0.5f) - (wsize.x * 0.25f), (wsize.y * 0.5f) - (wsize.y * 0.25f)), glm::vec2(wsize.x * 0.5f, wsize.y * 0.5f), "segoeui");
			modal->setExpandModeX(Widget::ExpandMode::FIXED);
			modal->setExpandModeY(Widget::ExpandMode::FIXED);
			modal->setPositionModeX(Widget::ExpandMode::FIXED);
			modal->setPositionModeY(Widget::ExpandMode::FIXED);

			modal->setState("draggable", true);
			modal->setState("closable", true);

			LayerManager* layerManager = layout->getGuiManager()->getLayerManager();
			layerManager->addWidget(0, modal);
			layout->addWidget(modal);
		}
	}

	~MainMenu();

private:
	Menu* m_menu;
};

