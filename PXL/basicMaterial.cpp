#include "basicMaterial.h"

BasicMaterial::BasicMaterial(const std::string& name, Shader* shader) : Material(name, shader)
{
	this->getShader()->addUniform("mTransform");
	this->getShader()->addUniform("mView");
	this->getShader()->addUniform("mProj");

	this->getShader()->addUniform("fogColor");
	this->getShader()->addUniform("fogDensity");
	this->getShader()->addUniform("fogGradient");


	for (unsigned int i = 0; i < 8; i++)
	{
		std::ostringstream ss_lightPosition;
		ss_lightPosition << "lightPosition[" << i << "]";
		this->getShader()->addUniform(ss_lightPosition.str());

		std::ostringstream ss_lightColor;
		ss_lightColor << "lightColor[" << i << "]";
		this->getShader()->addUniform(ss_lightColor.str());

		std::ostringstream ss_lightAttenuation;
		ss_lightAttenuation << "lightAttenuation[" << i << "]";
		this->getShader()->addUniform(ss_lightAttenuation.str());

		//Fix light attenuation making all material blacks if at zero.
		this->getShader()->bind();
		this->getShader()->setUniform3fv(ss_lightAttenuation.str(), glm::vec3(1.0f, 0.0f, 0.0f));
	}


	this->getShader()->addUniform("shininess");
	this->getShader()->addUniform("exponent");
	this->getShader()->addUniform("hasDiffuseTexture");
	this->getShader()->addUniform("hasSpecularTexture");
	this->getShader()->addUniform("hasNormalTexture");
	this->getShader()->addUniform("diffuseTexture");
	this->getShader()->addUniform("specularTexture");
	this->getShader()->addUniform("normalTexture");
	this->getShader()->addUniform("Ka");
	this->getShader()->addUniform("Kd");
	this->getShader()->addUniform("Ks");

	m_shininess = 0.0f;
	m_exponent = 1.0f;
	m_alpha = 1.0f;
	m_Ka = glm::vec3(0.1f, 0.1f, 0.1f);
	m_Kd = glm::vec3(0.5f, 0.5f, 0.5f);
	m_tiling = glm::vec2(1.0f, 1.0f);
	m_backFaceCulling = true;

	this->bindAttributes();
}

void BasicMaterial::bindAttributes()
{
	this->getShader()->bindAttribute(0, "position");
	this->getShader()->bindAttribute(1, "uvs");
	this->getShader()->bindAttribute(2, "normal");
	this->getShader()->bindAttribute(3, "tangent");
}

void BasicMaterial::updateTransform(Transform* transform)
{
	this->getShader()->setUniformMat4fv("mTransform", transform->getTransformation());
}

void BasicMaterial::preUpdate(Scene* scene)
{
	this->getShader()->setUniformMat4fv("mView", scene->getActiveCamera()->getViewMatrix());
	this->getShader()->setUniformMat4fv("mProj", scene->getActiveCamera()->getProjectionMatrix());

	for (unsigned int i = 0; i < 8; i++)
	{
		std::ostringstream ss_lightPos;
		ss_lightPos << "lightPosition[" << i << "]";
		std::ostringstream ss_lightColor;
		ss_lightColor << "lightColor[" << i << "]";
		std::ostringstream ss_lightAttenuation;
		ss_lightAttenuation << "lightAttenuation[" << i << "]";

		if (i < scene->getLights().size())
		{
			this->getShader()->setUniform4fv(ss_lightPos.str(), scene->getLights()[i]->getPosition());
			this->getShader()->setUniform3fv(ss_lightColor.str(), scene->getLights()[i]->getColor());
			this->getShader()->setUniform3fv(ss_lightAttenuation.str(), scene->getLights()[i]->getAttenuation());
		}
	}

	this->getShader()->setUniform1f("shininess", this->getShininess());
	this->getShader()->setUniform1f("exponent", this->getExponent());

	this->getShader()->setUniform3fv("fogColor", scene->getFogColor());
	this->getShader()->setUniform1f("fogGradient", scene->getFogGradient());
	this->getShader()->setUniform1f("fogDensity", scene->getFogDensity());

	this->getShader()->setUniform3fv("Ka", this->getKa());
	this->getShader()->setUniform3fv("Kd", this->getKd());
	this->getShader()->setUniform3fv("Ks", this->getKs());

	this->getShader()->setUniform1i("hasDiffuseTexture", this->hasDiffuseTexture());
	this->getShader()->setUniform1i("hasSpecularTexture", this->hasSpecularTexture());
	this->getShader()->setUniform1i("hasNormalTexture", this->hasNormalTexture());

	if (this->getDiffuseTexture() != nullptr)
	{
		this->getDiffuseTexture()->bind(0);
		this->getShader()->setUniform1i("diffuseTexture", 0);
	}

	if (this->getSpecularTexture() != nullptr)
	{
		this->getSpecularTexture()->bind(1);
		this->getShader()->setUniform1i("specularTexture", 1);
	}

	if (this->getNormalTexture() != nullptr)
	{
		this->getNormalTexture()->bind(2);
		this->getShader()->setUniform1i("normalTexture", 2);
	}
}

void BasicMaterial::postUpdate()
{
	if (this->getDiffuseTexture() != nullptr)
		this->getDiffuseTexture()->unbind();

	if (this->getSpecularTexture() != nullptr)
		this->getSpecularTexture()->unbind();

	if (this->getNormalTexture() != nullptr)
		this->getNormalTexture()->unbind();
}

BasicMaterial::~BasicMaterial()
{

}
