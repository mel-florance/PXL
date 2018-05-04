
#include "editorComponent.h"
#include "engine.h"
#include "layout.h"

 EditorComponent::EditorComponent(Engine & engine) {


}

 EditorComponent::~EditorComponent() {


}

void EditorComponent::setLayout(Layout & layout) {

	m_layout = layout;
}

Layout EditorComponent::getLayout() {

	return m_layout;
}

void EditorComponent::setEngine(Engine & engine) {

	m_engine = engine;
}

Engine EditorComponent::getEngine() {

	return m_engine;
}

