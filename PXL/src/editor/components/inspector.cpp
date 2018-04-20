#include "inspector.h"

Inspector::Inspector(Engine* engine) : EditorComponent(engine)
{

}

void Inspector::init()
{
	m_window = new Window("Inspector", glm::vec2(0.0f, 0.0f), this->getLayout()->getSize(), "segoeui");
	m_window->setDrawingShadow(false);
	this->getLayout()->addWidget(m_window);
}

Inspector::~Inspector()
{
	delete m_window;
}
