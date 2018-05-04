
#include "assetBrowser.h"
#include "engine.h"
#include "treeView.h"
#include "window.h"

 AssetBrowser::AssetBrowser(Engine & engine) {


}

void AssetBrowser::init() {

	m_window = new Window("Asset Browser", glm::vec2(0.0f, 73.0f), this->getLayout()->getSize(), "segoeui");
	m_window->setDrawingShadow(false);

	m_treeView = new TreeView(this->getLayout()->getPosition(), glm::vec2(200.0f, this->getLayout()->getSize().y), "segoeui");
	m_treeView->setExpandModeX(Widget::ExpandMode::FIXED);
	m_window->addChild(m_treeView);

	this->getLayout()->addWidget(m_window);
	m_treeView->init("C:/Users/Mel/Documents/SurvivalAssets");
}

 AssetBrowser::~AssetBrowser() {

	delete m_treeView;
	delete m_window;
}

