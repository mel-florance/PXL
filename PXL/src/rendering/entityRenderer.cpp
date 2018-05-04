
#include "entityRenderer.h"
#include "shadermanager.h"
#include "scene.h"
#include "shader.h"

 EntityRenderer::EntityRenderer(ShaderManager & shaderManager) {

	m_shaderManager = shaderManager;
	m_basicShader = m_shaderManager->getShader("basic");
}

 EntityRenderer::~EntityRenderer() {


}

void EntityRenderer::render(Scene & scene, double delta) {

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::vector<class Mesh*> meshes = scene->getMeshes();

	for (unsigned int i = 0; i < meshes.size(); ++i)
	{
		Mesh* mesh = meshes[i];
		Material* material = mesh->getMaterial();
		material->getShader()->bind();

		if (material->getBackFaceCulling() == true)
		{
			glCullFace(GL_BACK);
			glEnable(GL_CULL_FACE);
		}

		glBindVertexArray(mesh->getVao());
		mesh->toggleAttributes(true);
		material->getShader()->setUniformMat4fv("mTransform", mesh->getTransform()->getTransformation());
		material->preUpdate(scene);

		if (mesh->isVisible())
			mesh->draw();

		for (unsigned int j = 0; j < mesh->getInstances().size(); ++j)
		{
			if (mesh->getInstances()[j]->isVisible())
			{
				material->getShader()->setUniformMat4fv("mTransform", mesh->getInstances()[j]->getTransform()->getTransformation());
				mesh->getInstances()[j]->draw();
			}
		}

		if (material->getBackFaceCulling() == true)
			glDisable(GL_CULL_FACE);

		mesh->toggleAttributes(false);
		material->postUpdate();
		glBindVertexArray(0);
		material->getShader()->unbind();
	}
}

