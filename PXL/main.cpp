#include <iostream>

#include "engine.h"
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "directionalLight.h"
#include "basicMaterial.h"
#include "textMaterial.h"
#include "text.h"

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

	DirectionalLight* light = new DirectionalLight();
	light->setPosition(glm::vec3(0.0f, 100.0f, 150.0f));

	Shader* shader = shaderManager->getShader("basic");
	Shader* textShader = shaderManager->getShader("text");

	BasicMaterial* checkerMat = new BasicMaterial("checkerMat", shader);

	TextMaterial* textMat = new TextMaterial("textMat", textShader);
	Texture* textFontAtlas = new Texture("./res/fonts/segoeui.bmp", false);
	textMat->setDiffuseTexture(textFontAtlas);


	char t[256] = "hello";
	Text* fpsText = new Text(t, 10, 500, 60);
	fpsText->setMaterial(textMat);
	scene->addText(fpsText);

	Mesh* testObject = assetManager->importMesh("./res/models/test.dae");

	if (testObject != nullptr) {
		testObject->getTransform()->setPosition(glm::vec3(2.0f, 2.0f, 0.0f));
		testObject->setMaterial(checkerMat);
		scene->addMesh(testObject);
	}

	Texture* checker_texture = new Texture("./res/textures/checker.png", true);
	checkerMat->setReflectivity(0.0f);
	checkerMat->setShininess(0.0f);
	checkerMat->setDiffuseTexture(checker_texture);

	Mesh* plane = assetManager->importMesh("./res/models/plane.obj");
	plane->getTransform()->setScale(glm::vec3(50.0f, 50.0f, 50.0f));
	plane->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	plane->setMaterial(checkerMat);

	Mesh* tree = assetManager->importMesh("./res/models/SM_Pine01.obj");
	tree->getTransform()->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
	BasicMaterial* treeMat = new BasicMaterial("treeMat", shader);
	treeMat->setReflectivity(0.0f);
	treeMat->setShininess(0.0f);
	tree->setMaterial(treeMat);
	Texture* tree_texture = new Texture("./res/textures/t_pine_fo_d.png", true);
	treeMat->setDiffuseTexture(tree_texture);

	scene->addMesh(plane);
	scene->addMesh(tree);

	scene->addCamera(camera);
	scene->addLight(light);

	float angle = 0.0f;
	while (!window->isClosed())
	{
		angle += 0.0003f;

		if(testObject != nullptr)
			testObject->getTransform()->setRotation(glm::vec3(0.0f, angle, 0.0f));

		engine->render();
	}
	
	return 0;
}