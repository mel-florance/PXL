#pragma once

#include <string>
#include <iomanip>
#include <sstream>

#include "../../ui/widgets/button.h"
#include "../../ui/widgets/layout.h"
#include "../../ui/widgets/window.h"
#include "../../ui/widgets/text.h"
#include "../../ui/widgets/label.h"
#include "../../ui/widgets/checkbox.h"
#include "../../ui/widgets/input.h"
#include "../../ui/widgets/table.h"

#include "../editorComponent.h"

class Viewport : public EditorComponent
{
public:
	Viewport(Engine* engine);

	void init();
	void update(double delta);

	inline Window* getWindow() { return m_window; }

	static void addCube(CallbackData data);
	static void createCube(CallbackData data);
	static void onCreateCubeModalClosed(CallbackData data);

	~Viewport();

private:
	Window* m_window;
	Window* m_toolsPanel;
	Text* m_fpsText;
	Text* m_frameText;
};
