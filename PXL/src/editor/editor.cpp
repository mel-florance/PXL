#include "editor.h"

#include "components/mainMenu.h"
#include "components/viewport.h"
#include "components/outliner.h"
#include "components/assetBrowser.h"

Editor::Editor()
{
	m_engine = new Engine();
	this->init();
	m_engine->setEditor(this);
	m_engine->start();
}

void Editor::update(double delta)
{
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

void Editor::init()
{
	Scene* scene = m_engine->getSceneManager()->addScene("Scene 1");

	Camera* camera = new FPSCamera(
		m_engine->getWindow(),
		glm::vec3(0.0f, 1.0f, -3.0f),
		70.0f, 
		(float)m_engine->getWindow()->getAspect(), 
		0.01f, 
		1000.0f
	);

	m_engine->getSceneManager()->getSceneByName("Scene 1")->addCamera(camera);

	Light* m_light = new Light();
	m_light->setType(Light::POINT);
	m_light->setPosition(glm::vec3(0.5f, 0.5f, 0.5f));
	m_light->setColor(glm::vec3(2.0f, 2.0f, 2.0f));
	m_light->setAttenuation(glm::vec3(1.0f, 0.001f, 0.0001f));
	scene->addLight(m_light);

	m_engine->getAssetManager()->importMesh("./res/models/plane.obj");
	Mesh* plane = scene->getMeshByName("Plane");
	plane->getTransform()->setScale(glm::vec3(5.0f, 5.0f, 5.0f));
	plane->getMaterial()->setTiling(glm::vec2(500.0f, 500.0f));
	plane->getMaterial()->setBackFaceCulling(false);

	m_cube = m_engine->getAssetManager()->importMesh("./res/models/cube.obj");
	BasicMaterial* mat = (BasicMaterial*)m_cube->getMaterial();
	mat->setKa(glm::vec3(0.12f));
	mat->setKs(glm::vec3(0.0f));
	mat->setKe(glm::vec3(0.0f));
	m_cube->getTransform()->setPosition(glm::vec3(0.0f, 0.1f, 0.0f));
	m_cube->getTransform()->setScale(glm::vec3(0.1f, 0.1f, 0.1f));

	Mesh* lightMesh = m_cube->createInstance("lightMesh");
	lightMesh->getTransform()->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
	lightMesh->getTransform()->setPosition(m_light->getPosition());

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

	m_mainLayout = m_engine->getGuiManager()->createLayout("editor_window");

	Layout* layoutB = m_engine->getGuiManager()->createLayout("layoutB", glm::vec2(0.0f, 3.0f), glm::vec2(84.375f, 73.0f));
	Viewport* viewport = this->createComponent<Viewport>("viewport", "1_viewport");
	viewport->setLayout(layoutB);
	viewport->init();
	camera->setViewport(viewport);
	layoutB->addWidget(viewport->getWindow());
	m_mainLayout->addChild(layoutB);

	Layout* layoutD = m_engine->getGuiManager()->createLayout("layoutD", glm::vec2(0.0f, 73.0f), glm::vec2(84.375f, 27.0f));
	AssetBrowser* assetBrowser = this->createComponent<AssetBrowser>("assetBrowser", "4_asset_browser");
	assetBrowser->setLayout(layoutD);
	assetBrowser->init();
	layoutD->addWidget(assetBrowser->getTreeView());
	m_mainLayout->addChild(layoutD);

	Layout* layoutC = m_engine->getGuiManager()->createLayout("layoutC", glm::vec2(84.375f, 3.0f), glm::vec2(15.625f, 100.0f));
	Outliner* outliner = this->createComponent<Outliner>("outliner", "2_outliner");
	outliner->setLayout(layoutC);
	outliner->init();
	layoutC->addWidget(outliner->getWindow());
	m_mainLayout->addChild(layoutC);

	Layout* layoutA = m_engine->getGuiManager()->createLayout("layoutA", glm::vec2(0.0f), glm::vec2(100.0f, 3.0f));
	MainMenu* mainMenu = this->createComponent<MainMenu>("mainMenu", "3_main_menu");
	mainMenu->setLayout(layoutA);
	mainMenu->init();
	layoutA->addWidget(mainMenu->getMenu());
	m_mainLayout->addChild(layoutA);
}

Editor::~Editor()
{
	delete m_engine;

	ComponentRegister::iterator it;

	for (it = m_register.begin(); it != m_register.end(); it++)
		m_register.erase(it, m_register.end());
}


// TODO: Serialize editor data for project export.

//json j2 = {
//	{ "pi", 3.141 },
//	{ "happy", true },
//	{ "name", "Niels" },
//	{ "nothing", nullptr },
//	{ 
//		"answer", {
//			{ "everything", 42 }
//		} 
//	},
//	{ "list", { 1, 0, 2 } },
//	{ 
//		"object", {
//			{ "currency", "USD" },
//			{ "value", 42.99 }
//		}
//	}
//};

//std::string s = j2.dump(); 
//std::cout << j2.dump(4) << std::endl;