#include "entityRenderer.h"
#include "scene.h"

EntityRenderer::EntityRenderer(ShaderManager* shaderManager)
{
	m_shaderManager = shaderManager;
	m_basicShader = m_shaderManager->getShader("basic");
}

void EntityRenderer::render(Scene* scene)
{
	m_basicShader->bind();

	for (unsigned int i = 0; i < scene->getMeshes().size(); ++i)
	{
		Mesh* mesh = scene->getMeshes()[i];
		Material* material = mesh->getMaterial();

		if (material->getBackFaceCulling() == true)
			glEnable(GL_CULL_FACE);

		glBindVertexArray(mesh->getVao());
		mesh->toggleAttributes(true);
		m_basicShader->setUniformMat4fv("mTransform", mesh->getTransform()->getTransformation());
		material->preUpdate(scene);
		mesh->draw();

		for (unsigned int j = 0; j < mesh->getInstances().size(); ++j)
		{
			m_basicShader->setUniformMat4fv("mTransform", mesh->getInstances()[j]->getTransform()->getTransformation());
			mesh->getInstances()[j]->draw();
		}

		if (material->getBackFaceCulling() == true)
			glDisable(GL_CULL_FACE);

		mesh->toggleAttributes(false);
		material->postUpdate();
		glBindVertexArray(0);
	}

	m_basicShader->unbind();

}

EntityRenderer::~EntityRenderer()
{

}
