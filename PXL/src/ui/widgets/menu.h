#pragma once

#include <vector>
#include <algorithm>

#include <glm\glm.hpp>

#include "../core/widget.h"

#include "icon.h"

class Menu : public Widget
{
public:
	Menu(const glm::vec2& position, const glm::vec2& size, const std::string& font);

	struct MenuItem : public EventListener
	{
		MenuItem(const std::string& data, EventListenerFnPtr callback = NULL, const std::string& shortcut = "", const std::string& icon = "")
		{ 
			m_data = data; 
			m_shortcut = shortcut;
			m_opened = false;
			m_isSeparator = false;
			
			if(callback != NULL)
				this->addEventListener("mouseUp", callback);

			if (icon.size() > 0)
				m_icon = new Icon(icon, glm::vec2(), glm::vec2(20.0f, 20.0f));
			else
				m_icon = nullptr;
		}

		~MenuItem() {
			delete m_icon;
		}

		inline void addIcon() {

		}

		inline void setIconPosition(const glm::vec2& position) {
			if (this->hasIcon())
				m_icon->setPosition(position);
		}

		inline void setIconSize(const glm::vec2& size) {
			if (this->hasIcon())
				m_icon->setSize(size);
		}

		inline void setIconSymbol(const std::string& name) {
			if (this->hasIcon())
				m_icon->setSymbol(name);
		}

		inline MenuItem* addChild(const std::string& data, EventListenerFnPtr callback = NULL, const std::string& shortcut = "", const std::string& icon = "")
		{
			MenuItem* item = new MenuItem(data, callback, shortcut, icon);
			m_children.emplace_back(item);
			return item;
		}

		inline MenuItem* addSeparator() 
		{
			MenuItem* item = new MenuItem("");
			item->m_isSeparator = true;
			m_children.emplace_back(item);
			return item;
		};

		inline unsigned int getNbChildIcons()
		{
			unsigned int count = 0;
			for (auto& child : m_children)
				if (child->hasIcon())
					count++;

			return count;
		}

		inline unsigned int getNbSeparators()
		{
			unsigned int count = 0;
			for (auto& child : m_children)
				if (child->m_isSeparator)
					count++;

			return count;
		}

		inline bool hasIcon() { return m_icon != nullptr; }

		std::string m_data;
		std::string m_shortcut;
		Icon* m_icon;
		std::vector<MenuItem*> m_children;
		float m_width;
		bool m_hovered;
		bool m_opened;
		bool m_isSeparator;
	};

	void onMouseMove(const SDL_Event& event);
	void onMouseDown(const SDL_Event& event);
	void onMouseUp(const SDL_Event& event);
	void onKeyDown(const SDL_Event& event);

	inline void setDrawingShadow(bool state) { m_drawingShadow = state; }
	inline bool isDrawingShadow() { return m_drawingShadow; }

	void update(double delta);
	void draw(NVGcontext* ctx, double delta);

	inline MenuItem* addMenuItem(const std::string& data, EventListenerFnPtr callback = NULL, const std::string& shortcut = "")
	{
		MenuItem* item = new MenuItem(data, callback, shortcut);
		m_items.emplace_back(item);
		return item;
	}

	~Menu();

private:
	std::vector<MenuItem*> m_items;

	NVGpaint m_shadowPaint;
	bool m_drawingShadow;

	float m_borderRadius;
	float m_minHeight;
	float m_minFontSize;
	glm::vec4 m_margin;
	NVGalign m_align;
	std::string m_font;
	float m_fontSize;
	float m_blur;
	NVGcolor m_color;
	NVGcolor m_background;
};
