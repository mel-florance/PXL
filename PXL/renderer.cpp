#include "renderer.h"

Renderer::Renderer()
{

}

void Renderer::render(Scene* scene)
{
	std::vector<Mesh*> meshes = scene->getMeshes();

	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->getMaterial()->getShader()->bind();
		meshes[i]->getMaterial()->getShader()->update(*meshes[i]->getTransform(), *scene->getActiveCamera(), scene->getLights()[0]);
		meshes[i]->getMaterial()->getDiffuseTexture()->bind(0);

		glBindVertexArray(meshes[i]->getVao());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		glDrawElements(GL_TRIANGLES, meshes[i]->getVertexCount(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);

		meshes[i]->getMaterial()->getShader()->unbind();
		meshes[i]->getMaterial()->getDiffuseTexture()->unbind();

		glBindVertexArray(0);
	}
}

Renderer::~Renderer()
{

}
