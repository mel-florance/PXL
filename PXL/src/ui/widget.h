#pragma once

#include <string>
#include <vector>


#include <glm\glm.hpp>
#include <SDL2\SDL.h>
#include "nanovg.h"

#include "rect.h"

class Widget
{
public:
	Widget(glm::vec2& position, glm::vec2& size);
	~Widget();

	inline void setRect(Rect* rect) { m_rect = rect; }
	inline Rect* getRect() { return m_rect; }

	virtual inline void setScreen(const glm::vec2& screen) { m_screen = screen; }
	virtual inline glm::vec2& getScreen() { return m_screen; }

	inline void setParent(Widget* parent) { m_parent = parent; }
	inline Widget* getParent() { return m_parent; }

	inline void setPosition(const glm::vec2 position) { m_rect->setPosition(position); }
	inline glm::vec2 getPosition() { return m_rect->getPosition(); }

	inline glm::vec2 getRelativePosition() 
	{
		glm::vec2 pos = this->getPosition();

		if (this->getParent() != nullptr)
			pos += this->getParent()->getPosition();

		return pos;
	}

	inline bool intersects(const glm::vec2& point)
	{
		glm::vec2 pos = this->getRelativePosition();

		return point.x > pos.x
			&& point.x < pos.x + this->getSize().x
			&& point.y > pos.y
			&& point.y < pos.y + this->getSize().y;
	}

	inline void setSize(const glm::vec2& size) { m_rect->setSize(size); }
	inline glm::vec2 getSize() { return m_rect->getSize(); }

	inline void addChild(Widget* child)
	{
		child->setParent(this);
		m_children.emplace_back(child);
	}

	inline std::vector<Widget*> getChildren() { return m_children; }

	virtual inline void draw(NVGcontext* ctx, double delta) {}
	virtual inline void update(double delta) {}

	virtual inline void onKeyDown(const SDL_Event& event) {}
	virtual inline void onTextInput(const SDL_Event& event) {}
	virtual inline void onKeyUp(const SDL_Event& event) {}

	virtual inline void onMouseMove(const glm::vec2& mouse, const glm::vec2& rel) {}
	virtual inline void onMouseDown(Uint8 button) {}
	virtual inline void onMouseUp(Uint8 button) {}

	inline void setDragged(bool state) { m_dragged = state; }
	inline bool getDragged() { return m_dragged; }

	inline void setDraggable(bool state) { m_draggable = state; }
	inline bool isDraggable() { return m_draggable; }

	inline void setHovered(bool state) { m_hovered = state; }
	inline bool isHovered() { return m_hovered; }
	
	inline void setFocused(bool state) { m_focused = state; }
	inline bool isFocused() { return m_focused; }

	bool m_dragged;
	bool m_hovered;
	bool m_focused;
	bool m_draggable;
	glm::vec2 m_mouse;
	glm::vec2 m_dragStart;
	glm::vec2 m_mouseDelta;

private:
	glm::vec2 m_screen;
	Widget* m_parent;
	std::vector<Widget*> m_children;
	Rect* m_rect;
};

