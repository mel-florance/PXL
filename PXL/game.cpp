#include "game.h"

Game::Game(Engine* engine)
{
	m_engine = engine;

	Display* window = engine->getWindow();

	SceneManager* sceneManager = engine->getSceneManager();
	ShaderManager* shaderManager = engine->getShaderManager();
	AssetManager* assetManager = engine->getAssetManager();

	m_scene = sceneManager->addScene("test");

	FPSCamera* camera = new FPSCamera(glm::vec3(0.0f, 10.0f, -30.0f), 70.0f, window->getAspect(), 0.01f, 1000.0f);

	m_light = new Light();
	m_light->setPosition(glm::vec4(0.0f, 5.0f, 0.0f, 0.0f));
	m_light->setColor(glm::vec3(1.5f, 1.5f, 1.5f));
	m_light->setAttenuation(glm::vec3(1.0f, 0.01f, 0.002f));

	m_scene->addLight(m_light);

	assetManager->importMesh("./res/models/plane.obj");
	
	Mesh* plane = m_scene->getMeshByName("Plane");
	plane->getTransform()->setScale(glm::vec3(50.0f, 50.0f, 50.0f));
	plane->getMaterial()->setTiling(glm::vec2(15.0f, 15.0f));
	plane->getMaterial()->setBackFaceCulling(false);

	int baseH = m_engine->getWindow()->getHeight();
	int baseW = m_engine->getWindow()->getWidth();

	CBitmapFont font = engine->getFontManager()->getFont("segoe_ui");
	Text* text = new Text("PXL Engine 1.0", glm::vec3(1.0f, 1.0f, 1.0f), 80, 70, font);
	text->setSize(glm::vec2(1.0f, 1.0f));

	m_fpsText = new Text("0 fps", glm::vec3(1.0f, 1.0f, 1.0f), 80, 85, font);
	m_fpsText->setSize(glm::vec2(0.5f, 0.5f));

	Texture* checker = new Texture("./res/textures/icon_big.png");
	m_logo = new Widget("test", shaderManager->getShader("gui"));
	

	glm::vec2 scale = this->setGuiScale(glm::vec2(0.05f, 0.05f));
	
	m_logo->getTransform()->setScale(glm::vec3(scale.x, scale.y, 1.0));
	m_logo->getTransform()->setPosition(glm::vec3(-0.95f, 0.875f, 1.0f));
	m_logo->getMaterial()->setDiffuseTexture(checker);


	scale = this->setGuiScale(glm::vec2(0.3f, 0.3f));
	Widget* menu = new Widget("menu", shaderManager->getShader("gui"));
	menu->getTransform()->setPosition(glm::vec3(-0.85f, 0.55f, 1.0f));
	menu->getTransform()->setScale(glm::vec3(scale.x, scale.y, 1.0));
	menu->getMaterial()->setDiffuseColor(glm::vec3(0.0f, 0.35f, 1.0f));
	menu->getMaterial()->setAlpha(0.4f);


	Text* menuTitle = new Text("Profiling", glm::vec3(1.0f, 1.0f, 1.0f), 40, 140, font);
	menuTitle->setSize(glm::vec2(0.65f, 0.65f));

	m_profGame = new Text("Game", glm::vec3(1.0f, 1.0f, 1.0f), 40, 170, font);
	m_profGame->setSize(glm::vec2(0.5f, 0.5f));

	m_profInput = new Text("Input", glm::vec3(1.0f, 1.0f, 1.0f), 40, 190, font);
	m_profInput->setSize(glm::vec2(0.5f, 0.5f));

	m_profRender = new Text("Render", glm::vec3(1.0f, 1.0f, 1.0f), 40, 210, font);
	m_profRender->setSize(glm::vec2(0.5f, 0.5f));

	m_profSwapBuffer = new Text("SwapBuffer", glm::vec3(1.0f, 1.0f, 1.0f), 40, 230, font);
	m_profSwapBuffer->setSize(glm::vec2(0.5f, 0.5f));

	m_profSleep = new Text("Sleep", glm::vec3(1.0f, 1.0f, 1.0f), 40, 250, font);
	m_profSleep->setSize(glm::vec2(0.5f, 0.5f));


	m_scene->addWidget(m_logo);
	m_scene->addWidget(menu);

	m_scene->addText(text);
	m_scene->addText(menuTitle);
	m_scene->addText(m_fpsText);

	m_scene->addText(m_profGame);
	m_scene->addText(m_profInput);
	m_scene->addText(m_profRender);
	m_scene->addText(m_profSwapBuffer);
	m_scene->addText(m_profSleep);

	m_scene->addCamera(camera);

	m_angle = 0.0f;
}

glm::vec2 Game::setGuiScale(const glm::vec2& scale)
{
	Uint32 offset = m_engine->getWindow()->getWidth() - m_engine->getWindow()->getHeight();
	float scaleX = (scale.x / m_engine->getWindow()->getWidth()) * offset;
	float scaleY = (scale.y / m_engine->getWindow()->getHeight()) * offset;
	return glm::vec2(scaleX, scaleY);
}

void Game::update(double delta)
{
	m_angle += delta * 0.3;

	if (m_fpsText != nullptr) {
		char fps[128];
		sprintf(fps, "%0.f fps", m_engine->getFps());
		m_fpsText->setText(fps);
	}

	if (m_profGame != nullptr) {
		char chars[128];
		sprintf(chars, "Game %0.2f ms", m_engine->getProfiler()->getReport("game"));
		m_profGame->setText(chars);
	}

	if (m_profInput != nullptr) {
		char chars[128];
		sprintf(chars, "Input %0.2f ms", m_engine->getProfiler()->getReport("input"));
		m_profInput->setText(chars);
	}

	if (m_profRender != nullptr) {
		char chars[128];
		sprintf(chars, "Render %0.2f ms", m_engine->getProfiler()->getReport("render"));
		m_profRender->setText(chars);
	}

	if (m_profSwapBuffer != nullptr) {
		char chars[128];
		sprintf(chars, "SwapBuffer %0.2f ms", m_engine->getProfiler()->getReport("swapBuffer"));
		m_profSwapBuffer->setText(chars);
	}

	if (m_profSleep != nullptr) {
		char chars[128];
		sprintf(chars, "Sleep %0.2f ms", m_engine->getProfiler()->getReport("sleep"));
		m_profSleep->setText(chars);
	}

}

Game::~Game()
{

}
