#include "renderer.h"

Renderer::Renderer()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
}

void Renderer::render(Scene* scene)
{
	std::vector<Mesh*> meshes = scene->getMeshes();

	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->draw(scene->getActiveCamera(), scene->getLights());
	}
}

Renderer::~Renderer()
{

}
