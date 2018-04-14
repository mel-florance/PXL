#pragma once

#include "../ui/widgets/layout.h"

class Engine;

class EditorComponent
{
public:

	EditorComponent(Engine* engine);
	virtual ~EditorComponent();

	virtual void init() {}
	virtual void update(double delta) {}

	void setLayout(Layout* layout);
	Layout* getLayout();

	void setEngine(Engine* engine);
	Engine* getEngine();

private:
	Layout* m_layout;
	Engine* m_engine;
};
