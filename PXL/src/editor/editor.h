#pragma once

#include <vector>
#include <algorithm>

#include "editorLayout.h"

class Editor
{
public:
	Editor();
	~Editor();

	void addLayout(EditorLayout* layout);
	void removeLayout(EditorLayout* layout);

private:
	std::vector<class EditorLayout*> m_layouts;
};

