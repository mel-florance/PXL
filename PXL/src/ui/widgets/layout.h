#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "../core/widget.h"

class GuiManager;
class AssetManager;
class Splitter;

typedef enum { HORIZONTAL, VERTICAL } StackDirection;

class Layout
{
public:
	Layout(const std::string& name, Display* window, const glm::vec2& position, const glm::vec2& size);

	enum ExpandMode { WINDOW, PARENT, FIXED };

	inline ExpandMode getExpandModeX() { return m_expandModeX; }
	inline void setExpandModeX(ExpandMode mode) { m_expandModeX = mode; }

	inline ExpandMode getExpandModeY() { return m_expandModeY; }
	inline void setExpandModeY(ExpandMode mode) { m_expandModeY = mode; }

	inline ExpandMode getPositionModeX() { return m_positionModeX; }
	inline void setPositionModeX(ExpandMode mode) { m_positionModeX = mode; }

	inline ExpandMode getPositionModeY() { return m_positionModeY; }
	inline void setPositionModeY(ExpandMode mode) { m_positionModeY = mode; }

	inline void setMinHeight(float value) { m_minHeight = value; }
	inline float getMinHeigh() { return m_minHeight; }

	inline void setMaxHeight(float value) { m_maxHeight = value; }
	inline float getMaxHeight() { return m_maxHeight; }

	inline void setMinWidth(float value) { m_minWidth = value; }
	inline float getMinWidth() { return m_minWidth; }

	inline void setMaxWidth(float value) { m_maxWidth = value; }
	inline float getMaxWidth() { return m_maxWidth; }

	inline std::vector<class Widget*> getWidgets() { return m_widgets; }
	virtual void addWidget(Widget* widget);
	void setWidgetWindow(Widget* widget);
	void setWidgetLayout(Widget* widget);
	virtual void removeWidget(Widget* widget);

	void setGuiManager(GuiManager* guiManager) { m_guiManager = guiManager; }
	inline GuiManager* getGuiManager() { return m_guiManager; }

	void setDirection(StackDirection direction) { m_direction = direction; }
	StackDirection getDirection() { return m_direction; }

	void update(double delta);
	void draw(NVGcontext* ctx, Layout* previous, unsigned int index, unsigned int depth, double delta);
	void drawSplitter(NVGcontext* ctx, unsigned int index, double delta);

	inline void setPosition(const glm::vec2& position) { m_position = position; }
	inline glm::vec2& getPosition() { return m_position; }

	inline void setBackground(const NVGcolor& color) { m_background = color; }
	inline NVGcolor& getBackground() { return m_background; }

	inline void setComputedPosition(const glm::vec2& position) { m_computedPosition = position; }
	inline glm::vec2& getComputedPosition() { return m_computedPosition; }

	inline void setSize(glm::vec2 size) { m_size = size; }
	inline glm::vec2 getSize() { return m_size; }

	inline void setComputedSize(const glm::vec2& size) { m_computedSize = size; }
	inline glm::vec2& getComputedSize() { return m_computedSize; }

	void computeStackDirection(Layout* previous, unsigned int index);
	void computePosition();
	void computeSize();

	glm::vec2 getRelativePosition();
	glm::vec2 getRelativeSize();

	inline void setName(const std::string& name) { m_name = name; }
	inline const std::string& getName() { return m_name; }

	inline Layout* getRoot()
	{
		if (this->getParent() != nullptr)
			return this->getParent()->getRoot();
		else
			return this;
	}

	inline void setParent(Layout* layout) { m_parent = layout; }
	inline Layout* Layout::getParent() { return m_parent; }

	void addChild(Layout* layout);

	inline std::vector<class Layout*>& getChildren() { return m_children; }

	void toggleAllWidgets();

	void onWindowResized(const SDL_Event& event);
	void onWindowSizeChanged(const SDL_Event& event);

	inline void setWindow(Display* window) { m_window = window; }
	inline Display* getWindow() { return m_window; }

	inline bool needRecomputeStackDirection() { return m_needRecomputeStackDirection; }
	inline void setNeedRecomputeStackDirection(bool state) { m_needRecomputeStackDirection = state; }

	inline Splitter* getSplitter() { return m_splitter; }
	inline void setSplitter(Splitter* splitter) { m_splitter = splitter; }

	~Layout();

private:
	glm::vec2 m_position;
	glm::vec2 m_size;
	NVGcolor m_background;

	float m_minWidth;
	float m_minHeight;
	float m_maxWidth;
	float m_maxHeight;

	bool m_needRecomputeStackDirection;

	Splitter* m_splitter;

	ExpandMode m_positionModeX;
	ExpandMode m_positionModeY;
	ExpandMode m_expandModeX;
	ExpandMode m_expandModeY;

	glm::vec2 m_computedPosition;
	glm::vec2 m_computedSize;
	GuiManager* m_guiManager;
	StackDirection m_direction;
	std::string m_name;
	Layout* m_parent;
	Display* m_window;
	std::vector<class Widget*> m_widgets;
	std::vector<class Layout*> m_children;
};
