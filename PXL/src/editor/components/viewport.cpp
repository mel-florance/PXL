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

	Button* cubeButton = new Button(glm::vec2(10.0f, 10.0f), glm::vec2(168.0f, 30.0f), "segoeui");
	cubeButton->setExpandModeX(Widget::ExpandMode::FIXED);
	cubeButton->setExpandModeY(Widget::ExpandMode::FIXED);
	cubeButton->setPositionModeX(Widget::ExpandMode::LAYOUT);
	cubeButton->setPositionModeY(Widget::ExpandMode::LAYOUT);
	cubeButton->setText("Add cube");
	cubeButton->addEventListener("mouseUp", &Viewport::addCube);

	this->getLayout()->addWidget(cubeButton);

	m_fpsText = new Text("0 fps", nvgRGBA(255, 255, 255, 80), glm::vec2(200.0f, 55.0f), "segoeui");
	m_fpsText->setPositionModeX(Widget::ExpandMode::FIXED);
	m_fpsText->setPositionModeY(Widget::ExpandMode::FIXED);

	m_fpsText->setFontSize(18.0f);
	m_window->addChild(m_fpsText);

	m_frameText = new Text("0 ms", nvgRGBA(255, 255, 255, 80), glm::vec2(200.0f, 75.0f), "segoeui");
	m_frameText->setPositionModeX(Widget::ExpandMode::FIXED);
	m_frameText->setPositionModeY(Widget::ExpandMode::FIXED);
	m_frameText->setFontSize(18.0f);
	m_window->addChild(m_frameText);

	this->getLayout()->addWidget(m_window);
}

void Viewport::addCube(CallbackData data)
{
	Layout* layout = data.sender->getLayout()->getRoot();

	if (layout != nullptr)
	{
		glm::vec2 wsize = layout->getWindow()->getSize();

		glm::vec2 modalPos = glm::vec2((wsize.x * 0.5f) - 125.0f, (wsize.y * 0.5f) - 100.0f);
		glm::vec2 modalSize = glm::vec2(250.0f, 230.0f);

		Window* modal = new Window("Add cube", modalPos, modalSize, "segoeui");
		modal->addEventListener("onClosed", &Viewport::onCreateCubeModalClosed);
		modal->setState("draggable", true);
		modal->setState("closable", true);
		modal->setExpandModeX(Widget::ExpandMode::FIXED);
		modal->setExpandModeY(Widget::ExpandMode::FIXED);
		modal->setPositionModeX(Widget::ExpandMode::FIXED);
		modal->setPositionModeY(Widget::ExpandMode::FIXED);

		LayerManager* layerManager = layout->getGuiManager()->getLayerManager();
		layerManager->addWidget(0, modal);

		Label* labelSize = new Label(glm::vec2(10, 40.0f), glm::vec2(230, 35), "Scale", "segoeui");
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

		labelSize->addChild(inputSize);

		Label* labelBackFace = new Label(glm::vec2(10, 80.0f), glm::vec2(210, 35), "Backface culling", "segoeui");
		labelBackFace->setExpandModeX(Widget::ExpandMode::FIXED);
		labelBackFace->setExpandModeY(Widget::ExpandMode::FIXED);
		labelBackFace->setPositionModeX(Widget::ExpandMode::PARENT);
		labelBackFace->setPositionModeY(Widget::ExpandMode::PARENT);

		Checkbox* checkboxBackFaceCulling = new Checkbox(glm::vec2((250 - 30 - 10), 7.0f), glm::vec2(20, 20));
		checkboxBackFaceCulling->setExpandModeX(Widget::ExpandMode::FIXED);
		checkboxBackFaceCulling->setExpandModeY(Widget::ExpandMode::FIXED);
		checkboxBackFaceCulling->setPositionModeX(Widget::ExpandMode::PARENT);
		checkboxBackFaceCulling->setPositionModeY(Widget::ExpandMode::PARENT);

		labelBackFace->setName("checkboxBackface");
		labelBackFace->addChild(checkboxBackFaceCulling);

		Button* okButton = new Button(glm::vec2((250.0f - 90.0f), 150.0f), glm::vec2(80, 30), "segoeui");
		okButton->setExpandModeX(Widget::ExpandMode::FIXED);
		okButton->setExpandModeY(Widget::ExpandMode::FIXED);
		okButton->setPositionModeX(Widget::ExpandMode::PARENT);
		okButton->setPositionModeY(Widget::ExpandMode::PARENT);
		okButton->setText("Ok");
		okButton->addEventListener("mouseUp", &Viewport::createCube);

		modal->addChild(labelSize);
		modal->addChild(labelBackFace);
		modal->addChild(okButton);

		layout->addWidget(modal);
	}
}

void Viewport::createCube(CallbackData data)
{
	GuiManager* gm = data.sender->getLayout()->getGuiManager();
	gm->getAssetManager()->importMesh("./res/models/cube.obj");

	Mesh* cube = gm->getSceneManager()->getCurrentScene()->getMeshByName("Cube");

	if (cube != nullptr)
	{
		Widget* table = gm->getWidgetByName("outliner_table");
		Widget* inputSize = gm->getWidgetByName("labelSize");
		Widget* checkboxBackface = gm->getWidgetByName("checkboxBackface");

		if (checkboxBackface != nullptr) 
		{
			std::vector<Widget*> childs = checkboxBackface->getChildren();
			cube->getMaterial()->setBackFaceCulling(childs[0]->getState("checked"));
		}

		if (inputSize != nullptr)
		{
			std::vector<Widget*> childs = inputSize->getChildren();
			double value = ::atof(childs[0]->getText().c_str());
			cube->getTransform()->setScale(glm::vec3(value, value, value));
		}

		if (table != nullptr)
		{
			Table::Row* row = (Table::Row*)table->addRow();
			row->addColumn(cube->getName()); // get real cube name
			row->addColumn(std::to_string(cube->getVertexCount()));
			row->addColumn("lol");
		}
	}

	Viewport::onCreateCubeModalClosed(data);
}

void Viewport::onCreateCubeModalClosed(CallbackData data)
{
	LayerManager* layerManager = data.sender->getLayout()->getGuiManager()->getLayerManager();
	layerManager->removeWidget(0, data.sender->getParent());

	data.sender->getLayout()->getRoot()->removeWidget(data.sender->getParent());
}

void Viewport::update(double delta)
{
	if (m_fpsText != nullptr) 
	{
		std::ostringstream streamText;
		streamText << std::fixed << std::setprecision(4) << this->getEngine()->getLoop()->getFps() << " fps";
		m_fpsText->setText(streamText.str());
	}

	if (m_frameText != nullptr)
	{
		std::ostringstream streamFrame;
		streamFrame << std::fixed << std::setprecision(2) << this->getEngine()->getLoop()->getProfiler()->getReport("frame") << " ms";
		m_frameText->setText(streamFrame.str());
	}
}

Viewport::~Viewport()
{
	delete m_window;
	delete m_toolsPanel;
	delete m_fpsText;
}
