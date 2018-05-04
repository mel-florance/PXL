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


class Row;
class Layout;
class Icon;
class MenuItem;

class Widget : public Rect, public EventListener, public WidgetEvent, public WidgetState
{
public:
	Widget(const glm::vec2& position, const glm::vec2& size);
	~Widget();

	enum ExpandMode{ LAYOUT, PARENT, FIXED };

	inline ExpandMode getExpandModeX() { return m_expandModeX; }
	inline void setExpandModeX(ExpandMode mode) { m_expandModeX = mode; }

	inline ExpandMode getExpandModeY() { return m_expandModeY; }
	inline void setExpandModeY(ExpandMode mode) { m_expandModeY = mode; }

	inline ExpandMode getPositionModeX() { return m_positionModeX; }
	inline void setPositionModeX(ExpandMode mode) { m_positionModeX = mode; }

	inline ExpandMode getPositionModeY() { return m_positionModeY; }
	inline void setPositionModeY(ExpandMode mode) { m_positionModeY = mode; }

	const std::string& getName() { return m_name; }
	void setName(const std::string& name) { m_name = name; }

	inline void setWindow(Display* window) { m_window = window; }
	inline Display* getWindow() { return m_window; }

	virtual inline void setScreen(const glm::vec2& screen) { m_screen = screen; }
	virtual inline glm::vec2& getScreen() { return m_screen; }

	inline void setParent(Widget* parent) { m_parent = parent; }
	inline Widget* getParent() { return m_parent; }

	glm::vec2 getRelativePosition();
	glm::vec2 getRelativeSize();

	virtual void setCentered();

	bool intersects(const glm::vec2& point);

	inline void setLayout(Layout* layout) { m_layout = layout; }
	inline Layout* getLayout() { return m_layout;  }


	void addChild(Widget* child);
	inline std::vector<Widget*>& getChildren() { return m_children; }

	virtual inline void draw(NVGcontext* ctx, double delta) {}
	virtual inline void update(double delta) {}

	static void onClosed(CallbackData data);

	void setIcon(Icon* icon);
	Icon* getIcon();
	inline bool hasIcon() { return m_icon != nullptr; }

	virtual inline void* addRow() { return nullptr; }
	virtual inline void addItem(const std::string& item) {}
	virtual inline MenuItem* addMenuItem(std::string& item) { return (MenuItem*)NULL; }

	virtual inline const std::string getText() { return ""; }

	inline void setUnits(const std::string& units) { m_units = units; }
	const std::string& getUnits() { return m_units; }

	inline void setMinHeight(float value) { m_minHeight = value; }
	inline float getMinHeigh() { return m_minHeight; }

	inline void setMaxHeight(float value) { m_maxHeight = value; }
	inline float getMaxHeight() { return m_maxHeight; }

	inline void setMinWidth(float value) { m_minWidth = value; }
	inline float getMinWidth() { return m_minWidth; }

	inline void setMaxWidth(float value) { m_maxWidth = value; }
	inline float getMaxWidth() { return m_maxWidth; }

	void computePosition();
	void computeSize();

	inline void setComputedPosition(const glm::vec2& position) { m_computedPosition = position; }
	inline glm::vec2& getComputedPosition() { return m_computedPosition; }

	inline void setComputedSize(const glm::vec2& size) { m_computedSize = size; }
	inline glm::vec2& getComputedSize() { return m_computedSize; }

	glm::vec2 m_dragStart;
	glm::vec2 m_dragEnd;
	glm::vec2 m_dragDelta;

	glm::vec2 m_mouseDelta;
	glm::vec3 m_mouseStates;
	glm::vec2 m_mouse;
	glm::vec2 m_mouseRel;

private:
	ExpandMode m_positionModeX;
	ExpandMode m_positionModeY;
	ExpandMode m_expandModeX;
	ExpandMode m_expandModeY;

	glm::vec2 m_computedPosition;
	glm::vec2 m_computedSize;

	float m_minWidth;
	float m_minHeight;
	float m_maxWidth;
	float m_maxHeight;

	std::string m_name;
	Icon* m_icon;

	Display* m_window;
	Layout* m_layout;
	Widget* m_parent;

	std::string m_units;
	glm::vec2 m_screen;

	std::vector<class Widget*> m_children;
};
