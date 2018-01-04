#include <iostream>

#include "engine.h"
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "directionalLight.h"
#include "material.h"

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
	Material* checkerMat = new Material("checkerMat", shader);

	Mesh* testObject = assetManager->importMesh("./res/models/test.dae");

	if (testObject != nullptr) {
		testObject->getTransform()->setPosition(glm::vec3(2.0f, 2.0f, 0.0f));
		testObject->setMaterial(checkerMat);
		scene->addMesh(testObject);
	}

	Mesh* tree = assetManager->importMesh("./res/models/tree.obj");
	Mesh* plane = assetManager->importMesh("./res/models/plane.obj");

	plane->getTransform()->setScale(glm::vec3(50.0f, 50.0f, 50.0f));
	plane->getTransform()->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	plane->setMaterial(checkerMat);

	Material* atlasMat = new Material("houseMat", shader);
	tree->setMaterial(atlasMat);


	Texture* checker_texture = new Texture("./res/textures/checker.png", true);
	checkerMat->setDiffuseTexture(checker_texture);

	Texture* atlas_texture = new Texture("./res/textures/atlas.png", true);
	atlasMat->setDiffuseTexture(atlas_texture);


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