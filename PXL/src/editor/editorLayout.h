#pragma once

#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "EditorComponent.h"

class EditorLayout
{
public:
	EditorLayout();
	~EditorLayout();



	void loadLayout();
	
	void addComponent(const std::string& name);
	void removeComponent(const std::string& name);

private:

};
