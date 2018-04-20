#include "guiManager.h"

#include "../nanovg/nanovg.h"
#define NANOVG_GL3_IMPLEMENTATION
#include "../nanovg/nanovg_gl.h"

GuiManager::GuiManager(Display* window, FontManager* fontManager, AssetManager* assetManager, SceneManager* sceneManager) : Manager()
{
	m_window = window;
	m_ctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES);
	m_fontManager = fontManager;
	m_assetManager = assetManager;
	m_sceneManager = sceneManager;
	m_layerManager = new LayerManager();
	m_quadTree = new QuadTree(glm::vec2(2.0f, 2.0f), glm::vec2(8.0f, 8.0f));

	/*Node a(glm::vec2(1, 1), 1);
	Node b(glm::vec2(2, 5), 2);
	Node c(glm::vec2(7, 6), 3);

	m_quadTree->insert(&a);
	m_quadTree->insert(&b);
	m_quadTree->insert(&c);

	Node* node = m_quadTree->search(glm::vec2(2, 5));

	if (node != nullptr)
	{
		std::cout << "Node: " << node->m_data << ". Pos: (" << node->m_position.x << ", " << node->m_position.y << ")" << std::endl;
	}
	else
		std::cout << "Node not found" << std::endl;*/

	if (m_ctx == NULL)
		std::cout << "Could not init nanovg." << std::endl;
	else
	{
		m_fontManager->setContext(m_ctx);
		m_fontManager->loadFonts("./res/fonts/");
		std::cout << "Nanovg initialized." << std::endl;
	}
}

void GuiManager::initLayout(Layout* layout) 
{
	Layout* parent = layout->getParent();

	if (parent != nullptr)
	{
		layout->computeSize();
		layout->computePosition();
	}

	for (const auto& child : layout->getChildren())
		this->initLayout(child);
}

void GuiManager::handleLayoutEvent(const std::string& name, const SDL_Event& event, Layout* layout)
{
	switch (event.window.event) 
	{
		case SDL_WINDOWEVENT_RESIZED:
			layout->onWindowResized(event);
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			layout->onWindowSizeChanged(event);
			break;
	}

	if (layout->getSplitter() != nullptr)
		layout->getSplitter()->handleEvent(name, event);

	std::vector<Widget*> widgets = layout->getWidgets();
	for (unsigned int j = 0; j < widgets.size(); j++)
	{
		this->handleWidgetEvent(widgets[j], event, name);
	}

	for (auto child : layout->getChildren())
		this->handleLayoutEvent(name, event, child);
}

void GuiManager::init()
{
	this->initLayout(m_mainLayout);
}

void GuiManager::handleWidgetEvent(Widget* widget, const SDL_Event& event, const std::string& name)
{
	widget->handleEvent(name, event);

	std::vector<class Widget*> childs = widget->getChildren();

	for (unsigned int i = 0; i < childs.size(); i++)
		this->handleWidgetEvent(childs[i], event, name);
}

void GuiManager::handleEvent(const std::string& name, const SDL_Event& event)
{
	this->handleLayoutEvent(name, event, m_mainLayout);

	std::vector<Widget*> firstLayer = this->getLayerManager()->getLayers()[0];

	if (firstLayer.size() > 0)
	{
		for (unsigned int i = 0; i < firstLayer.size(); i++)
			this->handleWidgetEvent(firstLayer[i], event, name);
	}

}


Widget* GuiManager::getWidgetByName(const std::string& name)
{
	//for (unsigned int i = 0; i < m_layouts.size(); i++)
	//{
	//	std::vector<class Widget*> widgets = m_layouts[i]->getWidgets();

	//	for (unsigned int j = 0; j < widgets.size(); j++) {

	//		//std::cout << "first level: " << widgets[j]->getName() << " str: " << name << std::endl;

	//		std::vector<class Widget*> childs = widgets[j]->getChildren();

	//		for (unsigned int z = 0; z < childs.size(); z++) {

	//			//std::cout << "second level: " << childs[z]->getName() << std::endl;

	//			if (childs[z]->getName() == name)
	//				return childs[z];
	//		}
	//	}
	//}

	return (Widget*)NULL;
}

Layout* GuiManager::findPrevious(Layout* fromLevel, Layout* layout) 
{
	Layout* previous = nullptr;
	auto childs = fromLevel->getChildren();

	for (unsigned int i = 0; i < childs.size(); i++)
	{
		if (childs[i] == layout && i > 0)
			return childs[i - 1];

		this->findPrevious(childs[i], layout);
	}

	return previous;
}

Layout* GuiManager::getPrevious(Layout* layout)
{
	return this->findPrevious(m_mainLayout, layout);
}

void GuiManager::onSceneObjectAdded()
{

}

GuiManager::~GuiManager()
{
	delete m_layerManager;
	delete m_quadTree;
	delete m_mainLayout;
}
