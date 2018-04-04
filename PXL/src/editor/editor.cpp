#include "editor.h"

Editor::Editor()
{

}

void Editor::addLayout(EditorLayout* layout)
{
	m_layouts.emplace_back(layout);
}

void Editor::removeLayout(EditorLayout* layout)
{
	m_layouts.erase(std::remove(m_layouts.begin(), m_layouts.end(), layout), m_layouts.end());
}

Editor::~Editor()
{

}

