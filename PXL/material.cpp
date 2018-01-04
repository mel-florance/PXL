#include "material.h"

Material::Material(const std::string& name, Shader* shader)
{
	m_name = name;
	m_shader = shader;
}

void Material::preUpdate(Transform* transform, Camera* camera, std::vector<Light*> lights)
{
	this->getShader()->bind();
	this->getShader()->update(*transform, *camera, lights);
	this->getDiffuseTexture()->bind(0);
}

void Material::postUpdate()
{
	this->getShader()->unbind();
	this->getDiffuseTexture()->unbind();
}

Material::~Material()
{

}
