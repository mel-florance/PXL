#include "renderer.h"

Renderer::Renderer(ShaderManager* shaderManager)
{
	m_shaderManager = shaderManager;
	m_basicShader = m_shaderManager->getShader("basic");

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
}

void Renderer::render(Scene* scene)
{
	m_basicShader->bind();

	for (unsigned int i = 0; i < scene->getMeshes().size(); ++i)
	{
		Mesh* mesh = scene->getMeshes()[i];
		Material* material = mesh->getMaterial();
		std::vector<Mesh*> instances = mesh->getInstances();

		glBindVertexArray(mesh->getVao());
		material->bindAttributes();
		mesh->toggleAttributes(true);
		m_basicShader->setUniformMat4fv("mTransform", mesh->getTransform()->getTransformation());
		material->preUpdate(scene->getActiveCamera(), scene->getLights());
		mesh->draw();

		for (unsigned int j = 0; j < instances.size(); ++j) {
			m_basicShader->setUniformMat4fv("mTransform", instances[j]->getTransform()->getTransformation());
			instances[j]->draw();
		}

		mesh->toggleAttributes(false);
		material->postUpdate();
		glBindVertexArray(0);

	}

	m_basicShader->unbind();

	for (unsigned int i = 0; i < scene->getTexts().size(); i++)
	{
		scene->getTexts()[i]->draw();
	}
}

Renderer::~Renderer()
{

}
