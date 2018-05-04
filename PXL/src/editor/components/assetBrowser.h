#pragma once

#include "../../ui/widgets/treeView.h"
#include "../../ui/widgets/window.h"
#include "../EditorComponent.h"

class AssetBrowser : public EditorComponent
{
public:
	AssetBrowser(Engine* engine);

	void init();

	inline TreeView* getTreeView() { return m_treeView; }

	~AssetBrowser();

private:
	TreeView* m_treeView;
	Window* m_window;
};

