#include "assetBrowser.h"

AssetBrowser::AssetBrowser(Engine* engine) : EditorComponent(engine)
{

}

void AssetBrowser::init()
{
	m_window = new Window("Asset Browser", glm::vec2(0.0f, 73.0f), this->getLayout()->getSize(), "segoeui");
	m_window->setDrawingShadow(false);

	m_treeView = new TreeView(this->getLayout()->getPosition(), glm::vec2(300.0f, this->getLayout()->getSize().y), "segoeui");
	m_treeView->setPath("C:/Users/Mel/Documents/Visual Studio 2017/Projects/PXL/PXL/src");
	m_treeView->initDirectory();
	m_treeView->setExpandModeX(Widget::ExpandMode::FIXED);

	m_window->addChild(m_treeView);
	this->getLayout()->addWidget(m_window);
}

AssetBrowser::~AssetBrowser()
{
	delete m_treeView;
	delete m_window;
}
