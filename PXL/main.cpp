#include <iostream>

#include "engine.h"
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "pointLight.h"
#include "basicMaterial.h"
#include "text.h"

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

int main(int argc, char* argv[]) 
{
	Engine* engine = new Engine();
	Display* window = engine->getWindow();

	SceneManager* sceneManager = engine->getSceneManager();
	ShaderManager* shaderManager = engine->getShaderManager();
	AssetManager* assetManager = engine->getAssetManager();

	Scene* scene = sceneManager->addScene("test");

	Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, -3.0f), 70.0f, window->getAspect(), 0.01f, 1000.0f);
	window->setCamera(camera);

	PointLight* light = new PointLight();
	light->setPosition(glm::vec3(0.0f, 100.0f, 100.0f));
	light->setColor(glm::vec3(1.0f, 1.0f, 1.0f));

	assetManager->importMesh("./res/models/SM_Pine01.obj");
	assetManager->importMesh("./res/models/SM_Pine02.obj");
	assetManager->importMesh("./res/models/plane.obj");

	Mesh* treeTrunk = scene->getMeshByName("SM_Pine01");
	Mesh* treeLeaves = scene->getMeshByName("SM_Pine01.001_SM_Pine01.002");
	treeTrunk->getMaterial()->setBackFaceCulling(false);

	for (unsigned int i = 0; i < 50; i++) 
	{
		glm::vec3 rot = glm::vec3(0, RandomFloat(-10.0f, 10.0f), 0);
		glm::vec3 pos = glm::vec3(RandomFloat(-50.0f, 50.0f), 0, RandomFloat(-50.0f, 50.0f));
		Mesh* instance = treeTrunk->createInstance("tree_i_" + i);
		instance->getTransform()->setRotation(rot);
		instance->getTransform()->setPosition(pos);

		Mesh* instance2 = treeLeaves->createInstance("tree_i2_" + i);
		instance2->getTransform()->setRotation(rot);
		instance2->getTransform()->setPosition(pos);
	}

	Mesh* tree2Trunk = scene->getMeshByName("SM_Pine02.003");
	Mesh* tree2Leaves = scene->getMeshByName("SM_Pine02.002");
	tree2Trunk->getMaterial()->setBackFaceCulling(false);

	for (unsigned int i = 0; i < 50; i++) 
	{
		glm::vec3 rot = glm::vec3(0, RandomFloat(-10.0f, 10.0f), 0);
		glm::vec3 pos = glm::vec3(RandomFloat(-50.0f, 50.0f), 0, RandomFloat(-50.0f, 50.0f));
		Mesh* instance = tree2Trunk->createInstance("tree_i_" + i);
		instance->getTransform()->setRotation(rot);
		instance->getTransform()->setPosition(pos);

		Mesh* instance2 = tree2Leaves->createInstance("tree_i2_" + i);
		instance2->getTransform()->setRotation(rot);
		instance2->getTransform()->setPosition(pos);
	}

	Mesh* plane = scene->getMeshByName("Plane");
	plane->getTransform()->setScale(glm::vec3(50.0f, 50.0f, 50.0f));
	plane->getMaterial()->setTiling(glm::vec2(5.0f, 5.0f));

	CBitmapFont font = engine->getFontManager()->getFont("segoe_ui");
	Text* text = new Text("PXL Engine 1.0", glm::vec3(1.0f, 1.0f, 1.0f), 40, 960, font);
	Text* fpsText = new Text("0 fps", glm::vec3(1.0f, 1.0f, 1.0f), 40, 940, font);
	fpsText->setSize(glm::vec2(0.5f, 0.5f));
	scene->addText(text);
	scene->addText(fpsText);

	scene->addCamera(camera);
	scene->addLight(light);

	float angle = 0.0f;
	while (!window->isClosed())
	{
		angle += 0.0003f;
	
		char fps[128];
		sprintf(fps, "%d fps", (int)(1 / engine->getClock()->m_deltaTime));
		fpsText->setText(fps);

		engine->render();
	}
	
	return 0;
}