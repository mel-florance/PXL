
#include "console.h"
#include "engine.h"
#include "window.h"

 Console::Console(Engine & engine) {


}

void Console::init() {

	glm::vec2 wsize = this->getLayout()->getWindow()->getSize();
	glm::vec2 modalPos = glm::vec2((wsize.x * 0.5f) - (wsize.x * 0.25f), (wsize.y * 0.5f) - (wsize.y * 0.25f));
	glm::vec2 modalSize = glm::vec2(wsize.x * 0.5f, wsize.y * 0.5f);

	m_window = new Window("Console", modalPos, modalSize, "segoeui");
	m_window->setExpandModeX(Widget::ExpandMode::FIXED);
	m_window->setExpandModeY(Widget::ExpandMode::FIXED);
	m_window->setPositionModeX(Widget::ExpandMode::FIXED);
	m_window->setPositionModeY(Widget::ExpandMode::FIXED);

	m_window->setName("console");
	m_window->setState("draggable", true);

	//m_window->setState("closable", true);

	Input* cmdInput = new Input(glm::vec2(0.0f, modalSize.y - 35.0f), glm::vec2(modalSize.x, 35), "segoeui");
	cmdInput->setExpandModeX(Widget::ExpandMode::PARENT);
	cmdInput->setExpandModeY(Widget::ExpandMode::FIXED);
	cmdInput->setPositionModeX(Widget::ExpandMode::PARENT);
	cmdInput->setPositionModeY(Widget::ExpandMode::PARENT);
	cmdInput->setName("cmdInput");
	cmdInput->setPlaceholder("Enter a command...");

	m_window->addChild(cmdInput);

	LayerManager* layerManager = this->getLayout()->getGuiManager()->getLayerManager();
	layerManager->addWidget(0, m_window);

	this->getLayout()->addWidget(m_window);
	m_window->setState("visible", false);
}

void Console::Console::onKeyUp(const SDL_Event & event) {
}

 Console::~Console() {

	delete m_window;
}

