#include "viewport.h"
#include "../../core/engine.h"

Viewport::Viewport(Engine* engine) : EditorComponent(engine)
{

}

void Viewport::init()
{
	LayerManager* layerManager = this->getLayout()->getGuiManager()->getLayerManager();

	const std::string font = "segoeui";
	NVGcolor white = nvgRGBA(255, 255, 255, 120);

	m_fpsText = new Text("0 fps", white, glm::vec2(20.0f, 60.0f), font);
	m_fpsText->setFontSize(20.0f);

	m_frameText = new Text("0 ms", white, glm::vec2(20.0f, 90.0f), font);
	m_frameText->setFontSize(20.0f);

	m_window = new Window("viewport", this->getLayout()->getPosition(), this->getLayout()->getSize(), "segoeui");
	m_window->setOpacity(0.0f);
	m_window->setDrawingShadow(false);
	m_window->setHeaderFixedBottom(true);
	m_window->addChild(m_frameText);
	m_window->addChild(m_fpsText);

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
	delete m_fpsText;
}
