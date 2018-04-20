#include "viewport.h"
#include "../../core/engine.h"

Viewport::Viewport(Engine* engine) : EditorComponent(engine)
{

}

void Viewport::init()
{
	LayerManager* layerManager = this->getLayout()->getGuiManager()->getLayerManager();

	m_window = new Window("Viewport", this->getLayout()->getComputedPosition(), this->getLayout()->getComputedSize(), "segoeui");
	m_window->setOpacity(0.0f);
	m_window->setDrawingShadow(false);
	m_window->setHeaderFixedBottom(true);

	m_toolsPanel = new Window("Tools", glm::vec2(0.0f, 0.0f), glm::vec2(180.0f, this->getLayout()->getComputedSize().y), "segoeui");
	m_toolsPanel->setOpacity(0.25f);
	m_toolsPanel->setMarginBottom(30.0f);
	m_toolsPanel->setDrawingShadow(false);
	m_toolsPanel->setExpandModeX(Widget::ExpandMode::FIXED);
	m_toolsPanel->setPositionModeX(Widget::ExpandMode::LAYOUT);
	m_toolsPanel->setPositionModeY(Widget::ExpandMode::LAYOUT);

	m_window->addChild(m_toolsPanel);

	m_fpsText = new Text("0 fps", nvgRGBA(255, 255, 255, 80), glm::vec2(200.0f, 55.0f), "segoeui");
	m_fpsText->setFontSize(18.0f);
	m_window->addChild(m_fpsText);

	m_frameText = new Text("0 ms", nvgRGBA(255, 255, 255, 80), glm::vec2(200.0f, 75.0f), "segoeui");
	m_frameText->setFontSize(18.0f);
	m_window->addChild(m_frameText);



	this->getLayout()->addWidget(m_window);
}

void Viewport::update(double delta)
{
	if (m_fpsText != nullptr) 
	{
		std::ostringstream streamText;
		streamText << std::fixed << std::setprecision(2) << this->getEngine()->getFps() << " fps";
		m_fpsText->setText(streamText.str());
	}

	if (m_frameText != nullptr)
	{
		std::ostringstream streamFrame;
		streamFrame << std::fixed << std::setprecision(2) << this->getEngine()->getProfiler()->getReport("frame") << " ms";
		m_frameText->setText(streamFrame.str());
	}
}

Viewport::~Viewport()
{
	delete m_window;
	delete m_toolsPanel;
	delete m_fpsText;
}
