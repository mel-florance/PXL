
#include "gridMaterial.h"
#include "shader.h"
#include "scene.h"
#include "transform.h"

 GridMaterial::GridMaterial(const std::string & name, Shader & shader) {

	this->getShader()->addUniform("mTransform");
	this->getShader()->addUniform("mView");
	this->getShader()->addUniform("mProj");

	this->bindAttributes();
}

void GridMaterial::preUpdate(Scene & scene) {

	this->getShader()->setUniformMat4fv("mView", scene->getActiveCamera()->getViewMatrix());
	this->getShader()->setUniformMat4fv("mProj", scene->getActiveCamera()->getProjectionMatrix());
}

void GridMaterial::updateTransform(Transform & transform) {

	this->getShader()->setUniformMat4fv("mTransform", transform->getTransformation());
}

void GridMaterial::bindAttributes() {

	this->getShader()->bindAttribute(0, "position");
	this->getShader()->bindAttribute(1, "uvs");
}

 GridMaterial::~GridMaterial() {


}

