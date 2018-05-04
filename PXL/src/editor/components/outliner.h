#pragma once

#include "../../ui/widgets/layout.h"
#include "../../ui/widgets/window.h"
#include "../../ui/widgets/table.h"
#include "../editorComponent.h"


class Outliner : public EditorComponent
{
public:
	Outliner(Engine* engine);

	void init();

	inline Window* getWindow() { return m_window; }

	~Outliner();
private:
	Window* m_window;
	Table* m_table;
};

