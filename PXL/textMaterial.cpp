#include "textMaterial.h"

TextMaterial::TextMaterial(const std::string& name, Shader* shader) : Material(name, shader)
{
	this->getShader()->addUniform("diffuseTexture");
}

void TextMaterial::bindAttributes()
{
	this->getShader()->bindAttribute(0, "position");
	this->getShader()->bindAttribute(1, "uvs");
}

void TextMaterial::preUpdate(Transform* transform, Camera* camera, std::vector<Light*> lights)
{

	this->getDiffuseTexture()->bind(0);
}

void TextMaterial::postUpdate()
{
	this->getShader()->unbind();
	this->getDiffuseTexture()->unbind();
}

TextMaterial::~TextMaterial()
{

}
