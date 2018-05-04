#pragma once

#include <string>

class ProjectManager
{
public:
	ProjectManager();
	~ProjectManager();

	void load(const std::string& name);
	void save(const std::string& name);

private:
};

