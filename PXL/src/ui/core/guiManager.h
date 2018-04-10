#pragma once

#include <map>
#include <set>
#include <vector>
#include <string>
#include <functional>	
#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "../nanovg/nanovg.h"
#include "../../assets/assetManager.h"
#include "../../scene/sceneManager.h"
#include "fontManager.h"
#include "layerManager.h"
#include "../widgets/layout.h"
#include "widget.h"

#include "../../core/display.h"
#include "../../core/quadTree.h"
#include "../../core/manager.h"



class GuiManager : public Manager
{
public:
	GuiManager(Display* window, FontManager* fontManager, AssetManager* assetManager, SceneManager* sceneManager);
	~GuiManager();

	NVGcontext* getContext() { return m_ctx; }

	inline std::vector<class Layout*> getLayouts() { return m_layouts; }
	Layout* createLayout(const std::string& name, const glm::vec2& position = glm::vec2(0.0f, 0.0f), const glm::vec2& size = glm::vec2(0.0f, 0.0f));

	Layout* addLayout(Layout* layout);
	void removeLayout(Layout* layout);

	void handleWidgetEvent(Widget* widget, const SDL_Event& event, const std::string& name);
	void handleEvent(const std::string& name, const SDL_Event& event);

	Widget* getWidgetByName(const std::string& name);

	void onSceneObjectAdded();

	FontManager* getFontManager() { return m_fontManager; }
	SceneManager* getSceneManager() { return m_sceneManager; }
	AssetManager* getAssetManager() { return m_assetManager; }
	LayerManager* getLayerManager() { return m_layerManager; }

private:
	NVGcontext* m_ctx;
	Display* m_window;
	FontManager* m_fontManager;
	SceneManager* m_sceneManager;
	AssetManager* m_assetManager;
	LayerManager* m_layerManager;
	QuadTree* m_quadTree;
	std::vector<class Layout*> m_layouts;
};

