#pragma once

#include <vector>
#include <algorithm>

#include "EditorComponent.h"

class EditorLayout
{
public:
	EditorLayout();
	~EditorLayout();

	void loadLayout();
	
	void addComponent(EditorComponent* component);
	void removeComponent(EditorComponent* component);

private:
	std::vector<class EditorComponent*> m_components;
};
