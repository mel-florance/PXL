#include "skyboxMaterial.h"

SkyboxMaterial::SkyboxMaterial(const std::string& name, Shader* shader) : Material(name, shader)
{
	this->getShader()->addUniform("mView");
	this->getShader()->addUniform("mProj");
	this->getShader()->addUniform("mTransform");

	this->getShader()->addUniform("limits");
	this->getShader()->addUniform("clearColor");
	this->getShader()->addUniform("cubemap");
	this->getShader()->addUniform("cubemap2");
	this->getShader()->addUniform("blendFactor");

	this->bindAttributes();

	m_limits = glm::vec2(-100.0f, 20.0f);
	m_transform = new Transform(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(400.0f, 400.0f, 400.0f));
	m_blendFactor = 0.0f;
	m_rotSpeed = 0.05f;
	m_rotation = 0.0f;
	m_time = 0.0f;
}

void SkyboxMaterial::bindAttributes()
{
	this->getShader()->bindAttribute(0, "position");
}

void SkyboxMaterial::updateUniforms(Camera* camera, glm::vec4& clearColor, double delta)
{
	m_rotation += m_rotSpeed * (float)delta;
	m_transform->setPosition(camera->getPosition());
	m_transform->setRotation(glm::vec3(0.0f, m_rotation, 0.0f));

	this->getShader()->setUniformMat4fv("mProj", camera->getProjectionMatrix());
	this->getShader()->setUniformMat4fv("mView", camera->getViewMatrix());
	this->getShader()->setUniformMat4fv("mTransform", m_transform->getTransformation());

	this->getShader()->setUniform4fv("clearColor", clearColor);
	this->getShader()->setUniform1f("blendFactor", this->getBlendFactor());
	this->getShader()->setUniform2fv("limits", this->getLimits());
}

void SkyboxMaterial::bindTextures(double delta)
{
	m_time += (float)delta * 1000.0f;
	//m_time = fmod(m_time, 24000.0f);

	Uint32 day = this->getCubemap();
	Uint32 night = this->getCubemap2();

	//if (m_time >= 0 && m_time < 5000.0f)
	//{
	//	t1 = night;
	//	t2 = night;
	//	m_blendFactor = m_time / 5000.0f;
	//}
	//else if (m_time >= 5000.0f && m_time < 8000.0f)
	//{
	//	t1 = night;
	//	t2 = day;
	//	m_blendFactor = (m_time - 5000.0f) / (8000.0f - 5000.0f);
	//}
	//else if (m_time >= 8000.0f && m_time < 21000.0f)
	//{
	//	t1 = day;
	//	t2 = day;
	//	m_blendFactor = (m_time - 8000.0f) / (21000.0f - 8000.0f);
	//}
	//else
	//{
	//	t1 = day;
	//	t2 = night;
	//	m_blendFactor = (m_time - 21000.0f) / (24000.0f - 21000.0f);
	//}

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, day);
	this->getShader()->setUniform1i("cubemap", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, night);
	this->getShader()->setUniform1i("cubemap2", 1);

	this->getShader()->setUniform1f("blendFactor", m_blendFactor);
}

SkyboxMaterial::~SkyboxMaterial()
{
	delete m_transform;
}
