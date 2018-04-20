#pragma once

#include "../../ui/widgets/window.h"
#include "../EditorComponent.h"

class Inspector : public EditorComponent
{
public:
	Inspector(Engine* engine);

	void init();

	inline Window* getWindow() { return m_window; }

	~Inspector();

private:
	Window* m_window;
};
