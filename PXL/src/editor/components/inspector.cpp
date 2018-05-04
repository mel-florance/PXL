#include "inspector.h"

Inspector::Inspector(Engine* engine) : EditorComponent(engine)
{

}

void Inspector::init()
{
	m_window = new Window("Inspector", glm::vec2(0.0f, 0.0f), this->getLayout()->getSize(), "segoeui");
	m_window->setDrawingShadow(false);

	m_tabs = new Tabs(glm::vec2(0.0f), glm::vec2(this->getLayout()->getComputedSize().x, 30.0f));
	m_tabs->setExpandModeY(Widget::ExpandMode::FIXED);
	Tabs::Tab* worldTab = m_tabs->addTab("World");

	Accordion* worldAccordion = new Accordion(glm::vec2(0.0f), glm::vec2(this->getLayout()->getComputedSize().x, 30.0f));
	worldAccordion->addSection("Sky");
	worldAccordion->addSection("Fog");
	worldAccordion->setLayout(this->getLayout());
	worldAccordion->setExpandModeY(Widget::ExpandMode::LAYOUT);
	worldAccordion->setExpandModeX(Widget::ExpandMode::LAYOUT);
	worldAccordion->setPositionModeY(Widget::ExpandMode::LAYOUT);
	worldAccordion->setPositionModeX(Widget::ExpandMode::LAYOUT);

	worldTab->m_content->m_widget = worldAccordion;

	Tabs::Tab* sceneTab = m_tabs->addTab("Scene");
	Tabs::Tab* objectTab = m_tabs->addTab("Object");
	Tabs::Tab* particlesTab = m_tabs->addTab("Particles");
	Tabs::Tab* physicsTab = m_tabs->addTab("Physics");

	m_window->addChild(m_tabs);

	this->getLayout()->addWidget(m_window);
}

Inspector::~Inspector()
{
	delete m_tabs;
	delete m_window;
}
