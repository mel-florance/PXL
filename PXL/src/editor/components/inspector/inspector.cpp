
#include "inspector.h"
#include "engine.h"
#include "window.h"
#include "tabs.h"

 Inspector::Inspector(Engine & engine) {


}

void Inspector::init() {

	m_window = new Window("Inspector", glm::vec2(0.0f, 0.0f), this->getLayout()->getSize(), "segoeui");
	m_window->setDrawingShadow(false);

	m_tabs = new Tabs(glm::vec2(0.0f), glm::vec2(this->getLayout()->getComputedSize().x, 30.0f));
	m_tabs->setExpandModeY(Widget::ExpandMode::FIXED);
	Tabs::Tab* worldTab = m_tabs->addTab("World");

	Accordion* worldAccordion = new Accordion(glm::vec2(0.0f), glm::vec2(this->getLayout()->getComputedSize().x, 30.0f));
	Accordion::Section* skySection = worldAccordion->addSection("Sky");

	Accordion::Section* fogSection = worldAccordion->addSection("Fog");

	Label* labelSize = new Label(glm::vec2(20.0f, 100.0f), glm::vec2(230, 35), "Scale", "segoeui");
	labelSize->setExpandModeX(Widget::ExpandMode::FIXED);
	labelSize->setExpandModeY(Widget::ExpandMode::FIXED);
	labelSize->setPositionModeX(Widget::ExpandMode::PARENT);
	labelSize->setPositionModeY(Widget::ExpandMode::PARENT);
	labelSize->setName("labelSize");

	Input* inputSize = new Input(glm::vec2(60.0f, 0.0f), glm::vec2(170.0f, 35), "segoeui");
	inputSize->setExpandModeX(Widget::ExpandMode::FIXED);
	inputSize->setExpandModeY(Widget::ExpandMode::FIXED);
	inputSize->setPositionModeX(Widget::ExpandMode::PARENT);
	inputSize->setPositionModeY(Widget::ExpandMode::PARENT);
	inputSize->setText("1.0");

	labelSize->setParent(worldAccordion);
	labelSize->setLayout(this->getLayout());
	labelSize->addChild(inputSize);
	fogSection->addWidget(labelSize);


	worldAccordion->setLayout(this->getLayout());
	worldAccordion->setExpandModeY(Widget::ExpandMode::LAYOUT);
	worldAccordion->setExpandModeX(Widget::ExpandMode::LAYOUT);
	worldAccordion->setPositionModeY(Widget::ExpandMode::LAYOUT);
	worldAccordion->setPositionModeX(Widget::ExpandMode::LAYOUT);
	worldAccordion->setMarginRight(13.0f);

	worldTab->m_content->m_widget = worldAccordion;

	Tabs::Tab* sceneTab = m_tabs->addTab("Scene");
	Tabs::Tab* objectTab = m_tabs->addTab("Object");
	Tabs::Tab* particlesTab = m_tabs->addTab("Particles");
	Tabs::Tab* physicsTab = m_tabs->addTab("Physics");

	m_window->addChild(m_tabs);

	this->getLayout()->addWidget(m_window);
}

 Inspector::~Inspector() {

	delete m_tabs;
	delete m_window;
}

