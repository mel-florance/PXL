#include "material.h"

Material::Material(const std::string& name, Shader* shader)
{
	m_name = name;
	m_shader = shader;
}

Material::~Material()
{

}
