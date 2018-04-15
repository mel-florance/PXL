#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <dirent.h>
#include "../core/widget.h"

#include "icon.h"

class TreeView : public Widget
{
public:
	TreeView(const glm::vec2& position, const glm::vec2& size, const std::string& font);

	struct Directory 
	{
		Directory(const std::string& name) : m_name(name), m_opened(false) {}
		std::string m_name;
		Icon* m_icon;
		bool m_opened;
		bool m_hovered;
		std::vector<struct Directory*> m_children;
	};

	inline void setPath(const std::string& path) { m_path = path; }
	inline const std::string& getPath() { return m_path; }

	inline void initDirectory() 
	{
		struct dirent* dir;
		DIR* stream = opendir(m_path.c_str());

		if (stream)
		{
			while ((dir = readdir(stream)) != NULL)
			{
				if (dir->d_type == DT_DIR && 
					strcmp(dir->d_name, ".") != 0 && 
					strcmp(dir->d_name, "..") != 0)
				{
					Directory* directory = new Directory(dir->d_name);
					directory->m_icon = new Icon("RIGHT_DIR", glm::vec2(0.0f), glm::vec2(0.0f));
					m_directories.emplace_back(directory);
				}
			}

			closedir(stream);
		}
	}

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);

	void onKeyDown(const SDL_Event& event);
	void onTextInput(const SDL_Event& event);
	void onKeyUp(const SDL_Event& event);
	void onMouseMove(const SDL_Event& event);
	void onMouseDown(const SDL_Event& event);
	void onMouseUp(const SDL_Event& event);
	void onWindowResized(const SDL_Event& event);
	void onWindowSizeChanged(const SDL_Event& event);

	~TreeView();

private:
	std::string m_path;
	std::vector<Directory*> m_directories;

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
