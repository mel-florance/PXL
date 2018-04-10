#include "skyboxRenderer.h"

SkyboxRenderer::SkyboxRenderer(Loader* loader, ShaderManager* shaderManager)
{
	m_loader = loader;
	m_shaderManager = shaderManager;
	m_skyboxShader = shaderManager->getShader("skybox");
	m_mesh = m_loader->loadToVAO("cube_skybox", MeshFactory::getCube(1.0f));
	m_material = new SkyboxMaterial("skybox_mat", m_skyboxShader);

	std::vector<std::string> sunny;
	sunny.push_back("./res/skyboxes/sunset/right.png");
	sunny.push_back("./res/skyboxes/sunset/left.png");
	sunny.push_back("./res/skyboxes/sunset/top.png");
	sunny.push_back("./res/skyboxes/sunset/bottom.png");
	sunny.push_back("./res/skyboxes/sunset/back.png");
	sunny.push_back("./res/skyboxes/sunset/front.png");

	std::vector<std::string> night;
	night.push_back("./res/skyboxes/night/right.png");
	night.push_back("./res/skyboxes/night/left.png");
	night.push_back("./res/skyboxes/night/top.png");
	night.push_back("./res/skyboxes/night/bottom.png");
	night.push_back("./res/skyboxes/night/back.png");
	night.push_back("./res/skyboxes/night/front.png");

	m_material->setCubemap(m_loader->loadCubeMap(sunny));
	m_material->setCubemap2(m_loader->loadCubeMap(night));
}

void SkyboxRenderer::render(Scene* scene, double delta)
{
	m_skyboxShader->bind();
	glBindVertexArray(m_mesh->getVao());
	glEnableVertexAttribArray(0);

	m_material->updateUniforms(scene->getActiveCamera(), scene->getClearColor(), delta);
	m_material->bindTextures(delta);

	glDrawArrays(GL_TRIANGLES, 0, m_mesh->getVertexCount());

	glDisableVertexAttribArray(0);
	m_skyboxShader->unbind();
}

SkyboxRenderer::~SkyboxRenderer()
{
	delete m_material;
}
