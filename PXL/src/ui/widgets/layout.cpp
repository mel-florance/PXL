#include "layout.h"
#include "../../assets/assetManager.h"


Layout::Layout(const std::string& name, Display* window, const glm::vec2& position, const glm::vec2& size)
{
	m_name = name;
	m_window = window;
	m_direction = HORIZONTAL;
	m_position = m_computedPosition = position;
	m_size = m_computedSize = size;
}

void Layout::addWidget(Widget* widget)
{
	this->setWidgetLayout(widget);
	this->setWidgetWindow(widget);
	widget->setState("visible", true);
	m_widgets.emplace_back(widget);
}

void Layout::draw(NVGcontext* ctx, double delta)
{
	/*nvgSave(ctx);
	glm::vec2 position = this->getRelativePosition();

	nvgBeginPath(ctx);
	nvgRect(ctx,
		position.x,
		position.y,
		this->getSize().x,
		this->getSize().y
	);

	nvgFillColor(ctx, nvgRGBA(255, 0, 0, 127));
	nvgFill(ctx);

	nvgRestore(ctx);*/
}

void Layout::toggleAllWidgets()
{
	for (unsigned int i = 0; i < m_widgets.size(); i++)
		m_widgets[i]->setState("visible", m_widgets[i]->getState("visible") != false);
}

void Layout::onWindowResized(const SDL_Event& event)
{

}

void Layout::onWindowSizeChanged(const SDL_Event& event)
{
	Layout* root = this->getRoot();

	if (root == this) {
		std::cout << "ROOT SIZE CHANGED: " << this->getName() << " . " << this->getRoot()->m_name << ": " << m_window->getSize().x << std::endl;
		this->setSize(m_window->getSize());
	}
	else if (root != nullptr)
	{
		std::cout << "CHILD SIZE CHANGED: " << this->getName() << " . " << this->getRoot()->m_name << ": " << m_window->getSize().x << std::endl;

		glm::vec2 parentSize = this->getParent()->getSize();
		glm::vec2 size = (parentSize * this->getSize()) / 100.0f;
		this->setComputedSize(size);

		glm::vec2 pos = this->getPosition();
		glm::vec2 position = (pos * parentSize) / 100.0f;
		this->setComputedPosition(position);

		std::cout << position.x << ", " << position.y << std::endl;
	}
}

void Layout::setWidgetWindow(Widget* widget) 
{
	if (m_window != nullptr) 
	{
 		widget->setWindow(m_window);

		std::vector<class Widget*> childs = widget->getChildren();

		for (unsigned int i = 0; i < childs.size(); i++)
			this->setWidgetWindow(childs[i]);
	}
}

void Layout::setWidgetLayout(Widget* widget)
{
	widget->setLayout(this);

	std::vector<class Widget*> childs = widget->getChildren();

	for (unsigned int i = 0; i < childs.size(); i++)
		this->setWidgetLayout(childs[i]);
}

void Layout::removeWidget(Widget* widget)
{
	m_widgets.erase(std::remove(m_widgets.begin(), m_widgets.end(), widget), m_widgets.end());
}

Layout::~Layout()
{

}
