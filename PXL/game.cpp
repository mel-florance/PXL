#include "game.h"

Game::Game(Engine* engine)
{
	m_engine = engine;

	Display* window = engine->getWindow();

	SceneManager* sceneManager = engine->getSceneManager();
	ShaderManager* shaderManager = engine->getShaderManager();
	AssetManager* assetManager = engine->getAssetManager();

	m_scene = sceneManager->addScene("test");

	Camera* camera = new Camera(glm::vec3(0.0f, 10.0f, -30.0f), 70.0f, window->getAspect(), 0.01f, 1000.0f);

	m_light = new PointLight();
	m_light->setPosition(glm::vec3(0.0f, 10.0f, 2.0f));
	m_light->setColor(glm::vec3(0.0f, 10.0f, 0.0f));
	m_light->setAttenuation(glm::vec3(1.0f, 0.01f, 0.002f));


	m_lightS = new PointLight();
	m_lightS->setPosition(glm::vec3(0.0f, 10.0f, 2.0f));
	m_lightS->setColor(glm::vec3(0.0f, 0.0f, 10.0f));
	m_lightS->setAttenuation(glm::vec3(1.0f, 0.01f, 0.002f));

	m_lightR = new PointLight();
	m_lightR->setPosition(glm::vec3(0.0f, 10.0f, 2.0f));
	m_lightR->setColor(glm::vec3(10.0f, 0.0f, 0.0f));
	m_lightR->setAttenuation(glm::vec3(1.0f, 0.01f, 0.002f));


	assetManager->importMesh("./res/models/plane.obj");
	assetManager->importMesh("./res/models/monkey.obj");
	assetManager->importMesh("./res/models/MetalWarhammer01.obj");
	//assetManager->importMesh("./res/models/SM_Pine01.obj");

	m_ak = m_scene->getMeshByName("Suzanne");
	m_ak->getTransform()->setPosition(glm::vec3(4.0f, 1.0f, -2.0f));

	//Mesh* tree = m_scene->getMeshByName("SM_Pine01");
	//tree->getMaterial()->setBackFaceCulling(false);

	Mesh* plane = m_scene->getMeshByName("Plane");
	plane->getTransform()->setScale(glm::vec3(50.0f, 50.0f, 50.0f));
	plane->getMaterial()->setTiling(glm::vec2(15.0f, 15.0f));
	plane->getMaterial()->setBackFaceCulling(false);

	CBitmapFont font = engine->getFontManager()->getFont("segoe_ui");
	Text* text = new Text("PXL Engine 1.0", glm::vec3(1.0f, 1.0f, 1.0f), 80, 960, font);
	m_fpsText = new Text("0 fps", glm::vec3(1.0f, 1.0f, 1.0f), 80, 940, font);
	m_fpsText->setSize(glm::vec2(0.5f, 0.5f));

	Texture* checker = new Texture("./res/textures/icon_big.png");
	m_logo = new Widget("test", shaderManager->getShader("gui"));
	
	glm::vec3 scale = glm::vec3(0.05f, 0.05f, 1.0f);
	Uint32 offset = engine->getWindow()->getWidth() - engine->getWindow()->getHeight();
	float scaleX = (scale.x / engine->getWindow()->getWidth()) * offset;
	float scaleY = (scale.y / engine->getWindow()->getHeight()) * offset;

	m_logo->getTransform()->setScale(glm::vec3(scaleX, scaleY, 1.0));
	m_logo->getTransform()->setPosition(glm::vec3(-0.95f, 0.875f, 1.0f));
	m_logo->getMaterial()->setDiffuseTexture(checker);

	scale = glm::vec3(0.3f, 0.3f, 1.0f);
	offset = engine->getWindow()->getWidth() - engine->getWindow()->getHeight();
	scaleX = (scale.x / engine->getWindow()->getWidth()) * offset;
	scaleY = (scale.y / engine->getWindow()->getHeight()) * offset;

	Widget* menu = new Widget("menu", shaderManager->getShader("gui"));
	menu->getTransform()->setPosition(glm::vec3(-0.85f, 0.55f, 1.0f));
	menu->getTransform()->setScale(glm::vec3(scaleX, scaleY, 1.0));
	menu->getMaterial()->setDiffuseColor(glm::vec3(0.0f, 0.35f, 1.0f));
	menu->getMaterial()->setAlpha(0.4f);

	Text* menuTitle = new Text("Profiling", glm::vec3(1.0f, 1.0f, 1.0f), 40, 880, font);
	menuTitle->setSize(glm::vec2(0.7f, 0.7f));

	m_profGame = new Text("Game", glm::vec3(1.0f, 1.0f, 1.0f), 40, 840, font);
	m_profGame->setSize(glm::vec2(0.5f, 0.5f));

	m_profInput = new Text("Input", glm::vec3(1.0f, 1.0f, 1.0f), 40, 820, font);
	m_profInput->setSize(glm::vec2(0.5f, 0.5f));

	m_profRender = new Text("Render", glm::vec3(1.0f, 1.0f, 1.0f), 40, 800, font);
	m_profRender->setSize(glm::vec2(0.5f, 0.5f));

	m_profSwapBuffer = new Text("SwapBuffer", glm::vec3(1.0f, 1.0f, 1.0f), 40, 780, font);
	m_profSwapBuffer->setSize(glm::vec2(0.5f, 0.5f));

	m_profSleep = new Text("Sleep", glm::vec3(1.0f, 1.0f, 1.0f), 40, 760, font);
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
	m_scene->addLight(m_light);
	m_scene->addLight(m_lightS);
	m_scene->addLight(m_lightR);

	m_angle = 0.0f;
}

void Game::update(double delta)
{
	m_angle += delta * 0.5;

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

	if (m_ak != nullptr && m_light != nullptr) 
	{
		glm::vec3 p = glm::vec3(10 * sinf(m_angle), 1.0f, -10 * cosf(m_angle));
		m_light->setPosition(glm::vec3(p.x, p.y + 10.0f, p.z));

		glm::vec3 p2 = glm::vec3(10 * sinf(m_angle + M_PI), 1.0f, -10 * cosf(m_angle + M_PI));
		m_lightS->setPosition(glm::vec3(p2.x, p2.y + 10.0f, p2.z));

		glm::vec3 p3 = glm::vec3(10 * sinf(m_angle - M_PI/2), 1.0f, -10 * cosf(m_angle - M_PI/2));
		m_lightR->setPosition(glm::vec3(p3.x, p3.y + 10.0f, p3.z));
	}
}

Game::~Game()
{

}
