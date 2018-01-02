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
	light->setPosition(glm::vec3(0.0f, 3.0f, 0.0f));

	Mesh* monkey = assetManager->importMesh("./res/models/monkey.obj");
	Mesh* plane = assetManager->importMesh("./res/models/plane.obj");

	Shader* shader = shaderManager->getShader("basic");
	Material* checkerMat = new Material("checkerMat", shader);
	monkey->setMaterial(checkerMat);
	plane->setMaterial(checkerMat);

	Texture* checker_texture = new Texture("./res/textures/checker.png", true);
	checkerMat->setDiffuseTexture(checker_texture);

	scene->addMesh(monkey);
	scene->addMesh(plane);
	scene->addCamera(camera);
	scene->addLight(light);

	while (!window->isClosed())
	{
		engine->render();
	}
	
	return 0;
}