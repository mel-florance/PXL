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
#include "../widgets/splitter.h"
#include "widget.h"

#include "../../core/display.h"
#include "../../core/quadTree.h"
#include "../../core/manager.h"



class GuiManager : public Manager
{
public:
	GuiManager(Display* window, FontManager* fontManager, AssetManager* assetManager, SceneManager* sceneManager);
	~GuiManager();

	void init();
	void initLayout(Layout* layout);
	NVGcontext* getContext() { return m_ctx; }

	void handleLayoutEvent(const std::string& name, const SDL_Event& event, Layout* layout);
	void handleWidgetEvent(Widget* widget, const SDL_Event& event, const std::string& name);
	void handleEvent(const std::string& name, const SDL_Event& event);

	inline Layout* getMainLayout() { return m_mainLayout; }
	inline void setMainLayout(Layout* layout) { m_mainLayout = layout; }

	Widget* getWidgetByName(const std::string& name);

	Layout* getPrevious(Layout* layout);

	void onSceneObjectAdded();

	FontManager* getFontManager() { return m_fontManager; }
	SceneManager* getSceneManager() { return m_sceneManager; }
	AssetManager* getAssetManager() { return m_assetManager; }
	LayerManager* getLayerManager() { return m_layerManager; }

private:
	Layout * findPrevious(Layout* fromLevel, Layout* layout);

	NVGcontext* m_ctx;
	Display* m_window;
	Layout* m_mainLayout;
	FontManager* m_fontManager;
	SceneManager* m_sceneManager;
	AssetManager* m_assetManager;
	LayerManager* m_layerManager;
	QuadTree* m_quadTree;
};

