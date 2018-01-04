#include "material.h"

Material::Material(const std::string& name, Shader* shader) : m_name(name), m_shader(shader)
{
	this->getShader()->addUniform("mTransform");
	this->getShader()->addUniform("mView");
	this->getShader()->addUniform("mProj");
	this->getShader()->addUniform("lightPosition");
	this->getShader()->addUniform("lightColor");
}

void Material::bindAttributes()
{
	this->getShader()->bindAttribute(0, "position");
	this->getShader()->bindAttribute(1, "uvs");
	this->getShader()->bindAttribute(2, "normal");
	this->getShader()->bindAttribute(3, "tangent");
}

void Material::preUpdate(Transform* transform, Camera* camera, std::vector<Light*> lights)
{
	this->getShader()->setUniformMat4fv("mTransform", transform->getModel());
	this->getShader()->setUniformMat4fv("mView", camera->getViewMatrix());
	this->getShader()->setUniformMat4fv("mProj", camera->getProjectionMatrix());
	this->getShader()->setUniform3fv("lightPosition", lights[0]->getPosition());
	this->getShader()->setUniform3fv("lightColor", lights[0]->getColor());
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
