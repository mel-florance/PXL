#include "basicMaterial.h"

BasicMaterial::BasicMaterial(const std::string& name, Shader* shader) : Material(name, shader)
{
	this->getShader()->addUniform("mTransform");
	this->getShader()->addUniform("mView");
	this->getShader()->addUniform("mProj");
	this->getShader()->addUniform("lightPosition");
	this->getShader()->addUniform("lightColor");
	this->getShader()->addUniform("reflectivity");
	this->getShader()->addUniform("shininess");
	this->getShader()->addUniform("diffuseTexture");
}

void BasicMaterial::bindAttributes()
{
	this->getShader()->bindAttribute(0, "position");
	this->getShader()->bindAttribute(1, "uvs");
	this->getShader()->bindAttribute(2, "normal");
	this->getShader()->bindAttribute(3, "tangent");
}

void BasicMaterial::preUpdate(Transform* transform, Camera* camera, std::vector<Light*> lights)
{
	this->getShader()->setUniformMat4fv("mTransform", transform->getModel());
	this->getShader()->setUniformMat4fv("mView", camera->getViewMatrix());
	this->getShader()->setUniformMat4fv("mProj", camera->getProjectionMatrix());

	this->getShader()->setUniform3fv("lightPosition", lights[0]->getPosition());
	this->getShader()->setUniform3fv("lightColor", lights[0]->getColor());

	this->getShader()->setUniform1f("reflectivity", this->getReflectivity());
	this->getShader()->setUniform1f("shininess", this->getShininess());



	this->getDiffuseTexture()->bind(0);
	this->getShader()->setUniform1i("diffuseTexture", 0);
}

void BasicMaterial::postUpdate()
{
	this->getShader()->unbind();
	this->getDiffuseTexture()->unbind();
}

BasicMaterial::~BasicMaterial()
{

}
