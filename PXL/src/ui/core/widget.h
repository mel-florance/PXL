#pragma once

#include <map>
#include <vector>
#include <string>

#include <glm\glm.hpp>
#include <SDL2\SDL.h>
#include "../nanovg/nanovg.h"

#include "../../core/display.h"
#include "../../core/util.h"
#include "../../events/eventListener.h"

#include "widgetState.h"
#include "widgetEvent.h"

#include "../shapes/rect.h"

class Layout;
class Icon;

class Widget : public EventListener, public WidgetEvent, public WidgetState
{
public:
	Widget(const glm::vec2& position, const glm::vec2& size);
	~Widget();

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

	glm::vec2 getRelativePosition();

	virtual void setCentered();

	bool intersects(const glm::vec2& point);

	inline void setLayout(Layout* layout) { m_layout = layout; }
	inline Layout* getLayout() { return m_layout; }

	inline void setSize(const glm::vec2& size) { m_rect->setSize(size); }
	inline glm::vec2 getSize() { return m_rect->getSize(); }

	void addChild(Widget* child);
	inline std::vector<Widget*> getChildren() { return m_children; }

	virtual inline void draw(NVGcontext* ctx, double delta) {}
	virtual inline void update(double delta) {}

	void setIcon(Icon* icon);
	Icon* getIcon();
	inline bool hasIcon() { return m_icon != nullptr; }

	glm::vec2 m_dragStart;
	glm::vec2 m_dragEnd;

	glm::vec2 m_mouseDelta;
	glm::vec3 m_mouseStates;
	glm::vec2 m_mouse;
	glm::vec2 m_mouseRel;

private:
	Display* m_window;
	Layout* m_layout;
	Widget* m_parent;
	Rect* m_rect;
	Icon* m_icon;

	glm::vec2 m_screen;
	std::vector<class Widget*> m_children;
};

