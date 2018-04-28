#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <dirent.h>
#include "../core/widget.h"
#include "../widgets/scrollbar.h"

#include "icon.h"
#include "layout.h"

class TreeView : public Widget
{
public:
	TreeView(const glm::vec2& position, const glm::vec2& size, const std::string& font);

	struct TreeItem 
	{
		TreeItem(const std::string& name, const std::string& path) : m_name(name), m_path(path), m_opened(false), m_hovered(false), m_selected(false) {}

		std::string m_name;
		std::string m_path;
		Icon* m_icon;
		bool m_opened;
		bool m_hovered;
		bool m_selected;
		std::vector<struct TreeItem*> m_children;

		inline void addChild(TreeItem* child) {
			auto exists = std::find(m_children.begin(), m_children.end(), child);
			if (exists == m_children.end())
				m_children.emplace_back(child); 
		}
	};

	float getTreeItemHeight(glm::vec2& position, TreeItem* item, unsigned int index);

	inline TreeItem* getRoot() { return m_root; }

	inline void deselectAllItems(TreeItem* root)
	{		
		root->m_selected = false;

		for (const auto& child : root->m_children)
			this->deselectAllItems(child);
	}

	inline void loadTreeItem(TreeItem* item, const std::string& path)
	{
		struct dirent* dir;
		DIR* stream = opendir(path.c_str());
		
		if (stream)
		{
			while ((dir = readdir(stream)) != NULL)
			{
				if (dir->d_type == DT_DIR &&
					strcmp(dir->d_name, ".") != 0 &&
					strcmp(dir->d_name, "..") != 0)
				{
					TreeItem* child = new TreeItem(dir->d_name, path + "/" + dir->d_name);
					child->m_icon = new Icon("RIGHT_DIR", glm::vec2(0.0f), glm::vec2(0.0f));
					item->addChild(child);
				}
			}

			closedir(stream);
		}
	}

	inline void unloadTreeItem(TreeItem* item)
	{
		item->m_children.clear();
	}

	static void onScrollbarDragged(CallbackData data);


	inline void init(const std::string& path) 
	{
		size_t index = path.rfind('/');
		std::string rootPath = path.substr(index);
		std::string rootName = rootPath.substr(1, rootPath.size());
		m_root = new TreeItem(rootName, path);
		m_root->m_icon = new Icon("RIGHT_DIR", glm::vec2(0.0f), glm::vec2(0.0f));
		m_root->m_opened = true;	

		this->loadTreeItem(m_root, path);
	}

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);

	void drawTreeItem(NVGcontext* ctx, glm::vec2& position, glm::vec2& size, TreeItem* item, unsigned int depth, unsigned int index);
	void onTreeItemMouseMove(const SDL_Event& event, glm::vec2& position, glm::vec2& size, TreeItem* item, unsigned int depth, unsigned int index);
	void onTreeItemMouseUp(const SDL_Event& event, glm::vec2& position, glm::vec2& size, TreeItem* item, unsigned int depth, unsigned int index);

	void onKeyDown(const SDL_Event& event);
	void onTextInput(const SDL_Event& event);
	void onKeyUp(const SDL_Event& event);
	void onMouseMove(const SDL_Event& event);
	void onMouseWheel(const SDL_Event& event);
	void onMouseDown(const SDL_Event& event);
	void onMouseUp(const SDL_Event& event);
	void onWindowResized(const SDL_Event& event);
	void onWindowSizeChanged(const SDL_Event& event);

	void setOffsetScroll(float value) { m_offsetScroll = value; }

	~TreeView();

private:
	TreeItem* m_root;
	Scrollbar* m_scrollbar;

	float m_offsetScroll;
	glm::vec4 m_margin;
	NVGalign m_align;
	std::string m_font;
	float m_fontSize;
	float m_blur;
	NVGcolor m_color;
	NVGcolor m_textHoverColor;
	NVGcolor m_background;
	NVGcolor m_backgroundHoverColor;
	float m_borderRadius;
	float m_opacity;
};
