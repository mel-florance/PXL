#pragma once

#include <string>
#include <iomanip>
#include <sstream>

#include "../../ui/widgets/layout.h"
#include "../../ui/widgets/window.h"
#include "../../ui/widgets/text.h"
#include "../editorComponent.h"

class Viewport : public EditorComponent
{
public:
	Viewport(Engine* engine);

	void init();
	void update(double delta);

	inline Window* getWindow() { return m_window; }

	~Viewport();

private:
	Window* m_window;
	Text* m_fpsText;
	Text* m_frameText;
};
