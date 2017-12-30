#pragma once
#include <string>

class Material
{
public:
	Material(const std::string& name, const std::string& shaderId);
	~Material();

private:
	std::string m_name;
	std::string m_shaderId;
};

