#pragma once

#include <map>
#include <vector>
#include <string>

#include <glm\glm.hpp>
#include <SDL2\SDL.h>
#include "nanovg.h"

#include "../core/display.h"
#include "../events/eventListener.h"
#include "rect.h"

class Layout;

class Widget : public EventListener
{
public:
	Widget(const glm::vec2& position, const glm::vec2& size);
	~Widget();

	void handleEvent(const std::string& name, const SDL_Event& event);
	typedef void (Widget::*EventFnPtr)(const SDL_Event& event);

	inline void setWindow(Display* window) { m_window = window; }
	inline Display* getWindow() { return m_window; }

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
			pos += this->getParent()->getRelativePosition();
	
		return pos;
	}

	inline void setLayout(Layout* layout) { m_layout = layout; }
	inline Layout* getLayout() { return m_layout; }

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
		m_children.push_back(child);
	}

	inline std::vector<Widget*> getChildren() { return m_children; }

	virtual inline void draw(NVGcontext* ctx, double delta) {}
	virtual inline void update(double delta) {}


	virtual void onKeyDown(const SDL_Event& event);
	virtual void onTextInput(const SDL_Event& event);
	virtual void onKeyUp(const SDL_Event& event);
	virtual void onMouseMove(const SDL_Event& event){}
	virtual void onMouseDown(const SDL_Event& event);
	virtual void onMouseUp(const SDL_Event& event);
	virtual void onWindowResized(const SDL_Event& event);
	virtual void onWindowSizeChanged(const SDL_Event& event);

	inline void setDragged(bool state) { m_dragged = state; }
	inline bool getDragged() { return m_dragged; }

	inline void setDraggable(bool state) { m_draggable = state; }
	inline bool isDraggable() { return m_draggable; }

	inline void setHovered(bool state) { m_hovered = state; }
	inline bool isHovered() { return m_hovered; }
	
	inline void setFocused(bool state) { m_focused = state; }
	inline bool isFocused() { return m_focused; }

	inline void setActive(bool state) { m_active = state; }
	inline bool isActive() { return m_active; }

	bool m_dragged;
	bool m_hovered;
	bool m_focused;
	bool m_draggable;
	bool m_active;
	
	glm::vec2 m_dragStart;

	glm::vec2 m_mouseDelta;
	glm::vec3 m_mouseStates;
	glm::vec2 m_mouse;
	glm::vec2 m_mouseRel;

private:
	Display* m_window;
	glm::vec2 m_screen;
	std::map<std::string, EventFnPtr> m_events;

	Widget* m_parent;
	Layout* m_layout;
	std::vector<class Widget*> m_children;

	Rect* m_rect;
};

