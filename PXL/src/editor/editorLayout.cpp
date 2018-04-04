#include "editorLayout.h"

EditorLayout::EditorLayout()
{

}

void EditorLayout::loadLayout()
{

}

void EditorLayout::addComponent(EditorComponent* component)
{
	m_components.push_back(component);
}

void EditorLayout::removeComponent(EditorComponent* component)
{
	m_components.erase(std::remove(m_components.begin(), m_components.end(), component), m_components.end());
}

EditorLayout::~EditorLayout()
{

}
