#include "material.h"



Material::Material(const std::string& name, const std::string& shaderId)
{
	m_name = name;
	m_shaderId = shaderId;
}


Material::~Material()
{
}
