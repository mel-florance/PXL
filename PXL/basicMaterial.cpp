#include "basicMaterial.h"

BasicMaterial::BasicMaterial(const std::string& name, Shader* shader) : Material(name, shader)
{
	this->getShader()->addUniform("mTransform");
	this->getShader()->addUniform("mView");
	this->getShader()->addUniform("mProj");

	this->getShader()->addUniform("lightPosition");
	this->getShader()->addUniform("lightColor");

	this->getShader()->addUniform("shininess");
	this->getShader()->addUniform("diffuseTexture");
	this->getShader()->addUniform("diffuseColor");
	this->getShader()->addUniform("ambientColor");
	this->getShader()->addUniform("specularColor");
	this->getShader()->addUniform("Ka");
	this->getShader()->addUniform("Kd");
	this->getShader()->addUniform("Ks");

	m_diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	m_ambient = glm::vec3(0.1f, 0.1f, 0.1f);
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

void BasicMaterial::preUpdate(Camera* camera, std::vector<Light*> lights)
{
	this->getShader()->setUniformMat4fv("mView", camera->getViewMatrix());
	this->getShader()->setUniformMat4fv("mProj", camera->getProjectionMatrix());

	this->getShader()->setUniform3fv("lightPosition", lights[0]->getPosition());
	this->getShader()->setUniform3fv("lightColor", lights[0]->getColor());

	this->getShader()->setUniform1f("shininess", this->getShininess());

	this->getShader()->setUniform3fv("diffuseColor", this->getDiffuse());
	this->getShader()->setUniform3fv("ambientColor", this->getAmbient());
	this->getShader()->setUniform3fv("specularColor", this->getSpecular());

	this->getShader()->setUniform1f("Ka", this->getKa());
	this->getShader()->setUniform1f("Kd", this->getKd());
	this->getShader()->setUniform1f("Ks", this->getKs());

	if (this->getDiffuseTexture() != nullptr) {
		this->getDiffuseTexture()->bind(0);

	/*	this->getShader()->setUniform1i("diffuseTexture", );*/
	}
}

void BasicMaterial::postUpdate()
{
	if (this->getDiffuseTexture() != nullptr) {
		this->getDiffuseTexture()->unbind();
	}
}

BasicMaterial::~BasicMaterial()
{

}
