#include "EditorComponent.h"
#include "../core/engine.h"

EditorComponent::EditorComponent(Engine* engine) : m_engine(engine)
{

}

void EditorComponent::setLayout(Layout* layout)
{
	m_layout = layout;
}

Layout* EditorComponent::getLayout()
{
	return m_layout;
}

void EditorComponent::setEngine(Engine* engine)
{
	m_engine = engine;
}

Engine* EditorComponent::getEngine()
{
	return m_engine;
}

EditorComponent::~EditorComponent()
{

}
