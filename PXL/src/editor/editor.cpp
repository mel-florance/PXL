
#include "editor.h"
#include "engine.h"
#include "layout.h"
#include "mesh.h"
#include "light.h"
#include "editorLayout.h"

 Editor::Editor(Engine & engine) {

	this->init();
}

void Editor::init() {

	Scene* scene = m_engine->getSceneManager()->addScene("Scene 1");

	Camera* camera = new FPSCamera(
		m_engine->getWindow(),
		glm::vec3(0.0f, 1.0f, -3.0f),
		70.0f, 
		(float)m_engine->getWindow()->getAspect(), 
		0.01f, 
		1000.0f
	);

	scene->addCamera(camera);

	Light* m_light = new Light();
	m_light->setType(Light::POINT);
	m_light->setPosition(glm::vec3(50.0f, 100.0f, 100.0f));
	m_light->setColor(glm::vec3(100.0f, 100.0f, 100.0f));
	m_light->setAttenuation(glm::vec3(1.0f, 0.05f, 0.005f));
	scene->addLight(m_light);

	m_engine->getAssetManager()->importMesh("./res/models/suzanne.blend");

	MeshData meshData(MeshFactory::createSphere(2.0f, 64));

	Mesh* sphere = m_engine->getAssetManager()->getLoader()->loadToVAO("sphere", 
		meshData.getVertices(),
		meshData.getIndices(),
		meshData.getUvs(),
		meshData.getNormals(), 
		meshData.getTangents()
	);
	sphere->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	//sphere->getTransform()->setScale(glm::vec3(50.0f, 50.0f, 50.0f));

	Material* mat = new BasicMaterial("sphere", m_engine->getShaderManager()->getShader("basic"));
	sphere->setMaterial(mat);

	scene->addMesh(sphere);


	//m_engine->getAssetManager()->importMesh("./res/models/plane.obj");

	//GridMaterial* gridMat = new GridMaterial("grid", m_engine->getShaderManager()->getShader("grid"));
	//gridMat->setBackFaceCulling(false);

	//Mesh* plane = scene->getMeshByName("Plane");
	//plane->getTransform()->setScale(glm::vec3(5.0f, 5.0f, 5.0f));
	//plane->setMaterial(gridMat);


	//m_engine->getAssetManager()->importMesh("./res/models/bushhouse.obj");
	//m_cube->getTransform()->setPosition(glm::vec3(0.0f, 0.05f, 0.0f));
	//m_cube->getTransform()->setScale(glm::vec3(0.1f, 0.1f, 0.1f));

	//Mesh* lightMesh = m_cube->createInstance("lightMesh");
	//lightMesh->getTransform()->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
	//lightMesh->getTransform()->setPosition(m_light->getPosition());

	//cube->setVisible(false);

	//for (float x = 0; x < 10; x += 0.08f) {
	//	for (float y = 0; y < 10; y += 0.08f) {
	//		Mesh* instance = cube->createInstance("instance_" + std::to_string(x+y));
	//		instance->setVisible(true);
	//		instance->getTransform()->setPosition(glm::vec3(x * 0.3f, sinf(y) * 0.5f * cosf(x) * 0.5f, y * 0.3f));
	//		instance->getTransform()->setScale(glm::vec3(0.02f, 0.02f, 0.02f));
	//	}
	//}


	m_register["1_viewport"] = &registerComponent<Viewport>;
	m_register["2_outliner"] = &registerComponent<Outliner>;
	m_register["3_main_menu"] = &registerComponent<MainMenu>;
	m_register["4_asset_browser"] = &registerComponent<AssetBrowser>;
	m_register["5_inspector"] = &registerComponent<Inspector>;
	m_register["6_console"] = &registerComponent<Console>;

	m_mainLayout = new Layout("editor_window", m_engine->getWindow(), glm::vec2(0.0f), m_engine->getWindow()->getSize());
	m_mainLayout->setGuiManager(m_engine->getGuiManager());


	m_mainLayout->setPositionModeX(Layout::ExpandMode::WINDOW);
	m_mainLayout->setPositionModeY(Layout::ExpandMode::WINDOW);
	m_mainLayout->setExpandModeY(Layout::ExpandMode::WINDOW);
	m_mainLayout->setExpandModeX(Layout::ExpandMode::WINDOW);


	// Main menu
	Layout* layoutA = new Layout("layoutA", m_engine->getWindow(), glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 3.0f));
	layoutA->setMinHeight(30.0f);
	layoutA->setGuiManager(m_engine->getGuiManager());
	layoutA->setBackground(nvgRGBA(0, 0, 255, 100));
	m_mainLayout->addChild(layoutA);

	MainMenu* mainMenu = this->createComponent<MainMenu>("mainMenu", "3_main_menu");
	mainMenu->setLayout(layoutA);
	mainMenu->init();
	layoutA->addWidget(mainMenu->getMenu());


	Layout* layoutB = new Layout("layoutB", m_engine->getWindow(), glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 97.0f));
	layoutB->setGuiManager(m_engine->getGuiManager());
	layoutB->setBackground(nvgRGBA(0, 255, 0, 255));
	m_mainLayout->addChild(layoutB);





	Layout* layoutC = new Layout("layoutC", m_engine->getWindow(), glm::vec2(0.0f, 0.0f), glm::vec2(82.0f, 100.0f));
	layoutC->setGuiManager(m_engine->getGuiManager());
	layoutC->setBackground(nvgRGB(255, 0, 0));
	layoutC->setDirection(StackDirection::HORIZONTAL);


	layoutB->addChild(layoutC);





	Layout* layoutE = new Layout("layoutE", m_engine->getWindow(), glm::vec2(0.0f, 0.0f), glm::vec2(18.0f, 100.0f));
	layoutE->setMinWidth(200.0f);
	layoutE->setGuiManager(m_engine->getGuiManager());
	layoutE->setBackground(nvgRGB(255, 255, 255));
	layoutE->setDirection(StackDirection::HORIZONTAL);

	Layout* layoutH = new Layout("layoutH", m_engine->getWindow(), glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 27.0f));
	layoutH->setGuiManager(m_engine->getGuiManager());
	layoutH->setBackground(nvgRGB(255, 0, 255));



	Layout* layoutI= new Layout("layoutI", m_engine->getWindow(), glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 73.0f));
	layoutI->setGuiManager(m_engine->getGuiManager());
	layoutI->setBackground(nvgRGB(0, 255, 100));

	layoutB->addChild(layoutE);
	layoutE->addChild(layoutH);
	layoutE->addChild(layoutI);

	//Viewport
	Layout* layoutF = new Layout("layoutF", m_engine->getWindow(), glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 73.0f));
	layoutF->setGuiManager(m_engine->getGuiManager());
	layoutF->setBackground(nvgRGB(0, 255, 255));

	//layoutF->setPositionModeX(Layout::ExpandMode::FIXED);
	//layoutF->setPositionModeY(Layout::ExpandMode::FIXED);
	//layoutF->setExpandModeX(Layout::ExpandMode::WINDOW);
	//layoutF->setExpandModeY(Layout::ExpandMode::WINDOW);

	layoutC->addChild(layoutF);

	// AssetManager
	Layout* layoutG = new Layout("layoutG", m_engine->getWindow(), glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 27.0f));
	layoutG->setGuiManager(m_engine->getGuiManager());
	layoutG->setBackground(nvgRGBA(255, 255, 128, 128));

	layoutC->addChild(layoutG);

	m_engine->getGuiManager()->setMainLayout(m_mainLayout);


	Viewport* viewport = this->createComponent<Viewport>("viewport", "1_viewport");
	viewport->setLayout(layoutF);
	viewport->init();
	camera->setViewport(viewport);
	layoutF->addWidget(viewport->getWindow());

	AssetBrowser* assetBrowser = this->createComponent<AssetBrowser>("assetBrowser", "4_asset_browser");
	assetBrowser->setLayout(layoutG);
	assetBrowser->init();
	layoutG->addWidget(assetBrowser->getTreeView());

	Outliner* outliner = this->createComponent<Outliner>("outliner", "2_outliner");
	outliner->setLayout(layoutH);
	outliner->init();
	layoutH->addWidget(outliner->getWindow());


	Inspector* inspector = this->createComponent<Inspector>("inspector", "5_inspector");
	inspector->setLayout(layoutI);
	inspector->init();
	layoutI->addWidget(inspector->getWindow());

	Console* console = this->createComponent<Console>("console", "6_console");
	console->setLayout(m_mainLayout);
	console->init();


	//m_mainLayout->addWidget(console->getWindow());

	SoundManager* soundManager = m_engine->getSoundManager();
	//soundManager->loadSound("hope", "./res/sounds/hope.ogg");
	//soundManager->loadSound("aze", "./res/sounds/groove_drums.wav");
	//soundManager->loadSound("hope", "./res/sounds/hope.ogg");
	//soundManager->play();
	//soundManager->playSound("hope", -1, -1);

	//SDL_Delay(2000);
	//soundManager->playSound("aze", -1, -1);
	

	m_engine->getGuiManager()->init();
}

void Editor::update(double delta) {

	ComponentList::iterator it;

	for (it = m_components.begin(); it != m_components.end(); it++) 
		it->second->update(delta);

	if (m_cube != nullptr && m_light != nullptr) {
		std::vector<Mesh*> instances = m_cube->getInstances();
		if (instances.size() > 0) {
			instances[0]->getTransform()->setPosition(m_light->getPosition());
			std::cout << "ok" << std::endl;
		}
	}

	/*Scene* scene = m_engine->getSceneManager()->getCurrentScene();

	if (scene != nullptr) {
		Mesh* m = scene->getMeshByName("Cube");

		std::vector<Mesh*> instances = m->getInstances();

		m_angle += 0.001f;

		unsigned int i = 0;
		for (const auto& instance : m->getInstances()) {
			i++;
			float r = cosf(instance->getTransform()->getPosition().x / i) * sinf(instance->getTransform()->getPosition().y / i) * m_angle;

			instance->getTransform()->setPosition(glm::vec3(
				instance->getTransform()->getPosition().x, 
				 r,
				instance->getTransform()->getPosition().z)
			);
		}
	}*/
}

 Editor::~Editor() {

	delete m_engine;

	ComponentRegister::iterator it;

	for (it = m_register.begin(); it != m_register.end(); it++)
		m_register.erase(it, m_register.end());
}

