#include "guiMaterial.h"

GuiMaterial::GuiMaterial(const std::string& name, Shader* shader) : Material(name, shader)
{
	this->getShader()->addUniform("mTransform");
	this->getShader()->addUniform("diffuseTexture");
	this->getShader()->addUniform("diffuseColor");
	this->getShader()->addUniform("alpha");
	this->getShader()->addUniform("hasDiffuseTexture");

	m_alpha = 1.0f;
	m_tiling = glm::vec2(1.0f, 1.0f);
	m_diffuseColor = glm::vec3(0.3f, 0.3f, 0.3f);

	this->bindAttributes();
}

void GuiMaterial::bindAttributes()
{
	this->getShader()->bindAttribute(0, "position");
}

void GuiMaterial::updateTransform(Transform* transform)
{
	this->getShader()->setUniformMat4fv("mTransform", transform->getTransformation());
}

void GuiMaterial::preUpdate(Scene* scene)
{
	this->getShader()->setUniform1i("hasDiffuseTexture", this->hasDiffuseTexture());
	this->getShader()->setUniform3fv("diffuseColor", this->getDiffuseColor());
	this->getShader()->setUniform1f("alpha", this->getAlpha());

	if (this->getDiffuseTexture() != nullptr)
	{
		this->getDiffuseTexture()->bind(0);
		this->getShader()->setUniform1i("diffuseTexture", 0);
	}
}

void GuiMaterial::postUpdate()
{
	if (this->getDiffuseTexture() != nullptr)
		this->getDiffuseTexture()->unbind();
}

GuiMaterial::~GuiMaterial()
{

}
