#include "game.h"

Game::Game(Engine* engine)
{
	m_engine = engine;

	Display* window = engine->getWindow();

	SceneManager* sceneManager = engine->getSceneManager();
	ShaderManager* shaderManager = engine->getShaderManager();
	AssetManager* assetManager = engine->getAssetManager();
	GuiManager* guiManager = engine->getGuiManager();

	m_scene = sceneManager->addScene("test");

	m_camera = new FPSCamera(window, glm::vec3(0.0f, 10.0f, -30.0f), 70.0f, (float)window->getAspect(), 0.01f, 1000.0f);
	m_scene->addCamera(m_camera);

	m_light = new Light();
	m_light->setType(Light::DIRECTIONAL);
	m_light->setPosition(glm::vec3(10.0f, 20.0f, 20.0f));
	m_light->setColor(glm::vec3(2.0f, 2.0f, 2.0f));
	m_light->setAttenuation(glm::vec3(1.0f, 0.01f, 0.002f));
	m_scene->addLight(m_light);

	assetManager->importMesh("./res/models/plane.obj");
	assetManager->importMesh("./res/models/monkey.obj");

	Mesh* plane = m_scene->getMeshByName("Plane");
	plane->getTransform()->setScale(glm::vec3(50.0f, 50.0f, 50.0f));
	plane->getMaterial()->setTiling(glm::vec2(15.0f, 15.0f));
	plane->getMaterial()->setBackFaceCulling(false);

	Mesh* suzanne = m_scene->getMeshByName("Suzanne");
	suzanne->getTransform()->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));

	glm::vec4 white = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
	m_layout = guiManager->createLayout("main_window");
	Window* profiler = new Window("Profiling", glm::vec2(1.0f, 1.0f), glm::vec2(250.0f, window->getSize().y), "segoeui");
	Window* outliner = new Window("Outliner", glm::vec2(250.0f, 1.0f), glm::vec2(250.0f, window->getSize().y), "segoeui");
	profiler->setDraggable(true);
	outliner->setDraggable(true);


	//Image* image = new Image(guiManager->getContext(), "./res/textures/icon_big.png", glm::vec2(0.0f, 0.0f), glm::vec2(48.0f, 48.0f));

	m_fpsText = new Text("Fps:", white, glm::vec2(20.0f, 65.0f), "segoeui");
	m_profGame = new Text("Game:", white, glm::vec2(20, 85), "segoeui");
	m_profInput = new Text("Input:", white, glm::vec2(20, 105), "segoeui");
	m_profRender = new Text("Render:", white, glm::vec2(20, 125), "segoeui");
	m_profSwapBuffer = new Text("SwapBuffer:", white, glm::vec2(20, 145), "segoeui");
	m_profSleep = new Text("Sleep:", white, glm::vec2(20, 165), "segoeui");



	m_label = new Label(glm::vec2(20, 35.0f), glm::vec2(210, 35), "My super label", "segoeui");
	m_input = new Input(glm::vec2(0, 30), glm::vec2(210, 35), "segoeui");
	m_label->addChild(m_input);

	m_labelName = new Label(glm::vec2(20, 100.0f), glm::vec2(210, 35), "Name", "segoeui");
	m_inputName = new Input(glm::vec2(0, 30), glm::vec2(210, 35), "segoeui");
	m_labelName->addChild(m_inputName);

	m_button = new Button(glm::vec2(20, 190.0f), glm::vec2(210, 35), "segoeui");
	m_button->setText("clickMe");

	//panel->addChild(image);
	profiler->addChild(m_fpsText);
	profiler->addChild(m_profGame);
	profiler->addChild(m_profInput);
	profiler->addChild(m_profRender);
	profiler->addChild(m_profSwapBuffer);
	profiler->addChild(m_profSleep);

	outliner->addChild(m_label);
	outliner->addChild(m_labelName);
	outliner->addChild(m_button);

	m_layout->addWidget(profiler);
	m_layout->addWidget(outliner);

	m_angle = 0.0f;
}

void Game::update(double delta)
{
	m_angle += (float)delta * 0.3f;

	if (m_fpsText != nullptr)
		m_fpsText->setText("Fps: " + std::to_string((int)round(m_engine->getFps())));

	if (m_profGame != nullptr)
		m_profGame->setText("Game: " + std::to_string(m_engine->getProfiler()->getReport("game")));

	if (m_profInput != nullptr)
		m_profInput->setText("Input: " + std::to_string(m_engine->getProfiler()->getReport("input")));

	if (m_profRender != nullptr)
		m_profRender->setText("Render: " + std::to_string(m_engine->getProfiler()->getReport("render")));

	if (m_profSwapBuffer != nullptr)
		m_profSwapBuffer->setText("SwapBuffer: " + std::to_string(m_engine->getProfiler()->getReport("swapBuffer")));

	if (m_profSleep != nullptr)
		m_profSleep->setText("Sleep: " + std::to_string(m_engine->getProfiler()->getReport("sleep")));
}

Game::~Game()
{

}
