#include "basicMaterial.h"

BasicMaterial::BasicMaterial(const std::string& name, Shader* shader) : Material(name, shader)
{
	this->getShader()->addUniform("mTransform");
	this->getShader()->addUniform("mView");
	this->getShader()->addUniform("mProj");

	this->getShader()->addUniform("fogColor");
	this->getShader()->addUniform("fogDensity");
	this->getShader()->addUniform("fogGradient");

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

	m_shininess = 50.0f;
	m_Ka = 1.0f;
	m_Kd = 1.0f;
	m_Ks = 1.0f;

	m_diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	m_ambient = glm::vec3(0.1f, 0.1f, 0.1f);
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

	//TODO: make multiple lights !
	this->getShader()->setUniform3fv("lightPosition", scene->getLights()[0]->getPosition());
	this->getShader()->setUniform3fv("lightColor", scene->getLights()[0]->getColor());

	this->getShader()->setUniform1f("shininess", this->getShininess());

	this->getShader()->setUniform3fv("fogColor", scene->getFogColor());
	this->getShader()->setUniform1f("fogGradient", scene->getFogGradient());
	this->getShader()->setUniform1f("fogDensity", scene->getFogDensity());

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
