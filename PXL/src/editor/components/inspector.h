#pragma once

#include "../../ui/widgets/window.h"
#include "../../ui/widgets/tabs.h"
#include "../../ui/widgets/accordion.h"
#include "../EditorComponent.h"

class Inspector : public EditorComponent
{
public:
	Inspector(Engine* engine);

	void init();

	inline Window* getWindow() { return m_window; }

	~Inspector();

private:
	Tabs* m_tabs;
	Window* m_window;
};
