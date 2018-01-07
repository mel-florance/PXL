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
	window->setCamera(camera);

	PointLight* light = new PointLight();
	light->setPosition(glm::vec3(-10.0f, 10.0f, 10.0f));
	light->setColor(glm::vec3(8.0f, 7.0f, 6.0f));
	light->setAttenuation(glm::vec3(0.0f, 0.01f, 0.02f));

	assetManager->importMesh("./res/models/plane.obj");
	assetManager->importMesh("./res/models/test.obj");
	assetManager->importMesh("./res/models/ak47.obj");

	Mesh* cube = m_scene->getMeshByName("Cube_001_Cube.002");
	cube->getTransform()->setPosition(glm::vec3(4.0f, 1.0f, -2.0f));

	m_ak = m_scene->getMeshByName("ak47");
	m_ak->getTransform()->setPosition(glm::vec3(-4.0f, 1.0f, -2.0f));

	Mesh* plane = m_scene->getMeshByName("Plane");
	plane->getTransform()->setScale(glm::vec3(50.0f, 50.0f, 50.0f));
	plane->getMaterial()->setTiling(glm::vec2(15.0f, 15.0f));
	plane->getMaterial()->setBackFaceCulling(false);

	CBitmapFont font = engine->getFontManager()->getFont("segoe_ui");
	Text* text = new Text("PXL Engine 1.0", glm::vec3(1.0f, 1.0f, 1.0f), 40, 960, font);
	m_fpsText = new Text("0 fps", glm::vec3(1.0f, 1.0f, 1.0f), 40, 940, font);
	m_fpsText->setSize(glm::vec2(0.5f, 0.5f));

	m_scene->addText(text);
	m_scene->addText(m_fpsText);

	m_scene->addCamera(camera);
	m_scene->addLight(light);

	m_angle = 0.0f;
}

void Game::update(double delta)
{
	m_angle += 0.003f;

	if (m_ak != nullptr)
	{
		m_ak->getTransform()->setRotation(glm::vec3(0.0f, m_angle, 0.0f));
	}

	char fps[128];
	int d = (int)(1.0 / delta);
	sprintf(fps, "%d fps", d);

	if(m_fpsText != nullptr)
		m_fpsText->setText(fps);
}

Game::~Game()
{

}
