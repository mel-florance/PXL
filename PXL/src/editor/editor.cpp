#include "editor.h"

#include "components/mainMenu.h"
#include "components/viewport.h"
#include "components/outliner.h"

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

	Light* light = new Light();
	light->setType(Light::POINT);
	light->setPosition(glm::vec3(2.0f, 5.0f, 5.0f));
	light->setColor(glm::vec3(3.0f, 3.0f, 3.0f));
	light->setAttenuation(glm::vec3(1.0f, 0.05f, 0.005f));
	scene->addLight(light);

	m_engine->getAssetManager()->importMesh("./res/models/plane.obj");
	Mesh* torus = m_engine->getAssetManager()->importMesh("./res/models/torus.obj");

	torus->getTransform()->setScale(glm::vec3(0.1f, 0.1f, 0.1f));

	m_register["1_viewport"] = &registerComponent<Viewport>;
	m_register["2_outliner"] = &registerComponent<Outliner>;
	m_register["3_main_menu"] = &registerComponent<MainMenu>;

	m_mainLayout = m_engine->getGuiManager()->createLayout("editor_window");


	Layout* layoutB = m_engine->getGuiManager()->createLayout("layoutB", glm::vec2(0.0f, 3.0f), glm::vec2(84.375f, 100.0f));
	Viewport* viewport = this->createComponent<Viewport>("viewport", "1_viewport");
	viewport->setLayout(layoutB);
	viewport->init();
	layoutB->addWidget(viewport->getWindow());
	m_mainLayout->addChild(layoutB);


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