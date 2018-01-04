#include "basicMaterial.h"

BasicMaterial::BasicMaterial()
{

}

void BasicMaterial::bindAttributes()
{
	this->getShader()->bindAttribute(0, "position");
	this->getShader()->bindAttribute(1, "uvs");
	this->getShader()->bindAttribute(2, "normal");
	this->getShader()->bindAttribute(3, "tangent");
}

BasicMaterial::~BasicMaterial()
{

}
