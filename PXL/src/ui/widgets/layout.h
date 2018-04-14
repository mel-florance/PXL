#pragma once

#include <vector>
#include <string>
#include <algorithm>

#include "../core/widget.h"

class GuiManager;
class AssetManager;

typedef enum { HORIZONTAL, VERTICAL } StackDirection;

class Layout
{
public:
	Layout(const std::string& name, Display* window, const glm::vec2& position, const glm::vec2& size);

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
	void draw(NVGcontext* ctx, double delta);

	inline void setPosition(const glm::vec2& position) { m_position = position; }
	inline glm::vec2& getPosition() { return m_position; }

	inline void setComputedPosition(const glm::vec2& position) { m_computedPosition = position; }
	inline glm::vec2& getComputedPosition() { return m_computedPosition; }

	inline void setSize(const glm::vec2& size) { m_size = size; }
	inline const glm::vec2& getSize() { return m_size; }

	inline void setComputedSize(const glm::vec2& size) { m_computedSize = size; }
	inline glm::vec2& getComputedSize() { return m_computedSize; }

	inline void setName(const std::string& name) { m_name = name; }
	inline const std::string& getName() { return m_name; }

	inline Layout* getRoot() {
		
		if (this->getParent() != nullptr)
			return this->getParent()->getRoot();
		else
			return this;
	}

	inline void setParent(Layout* layout) { m_parent = layout; }
	inline Layout* getParent() { return m_parent; }

	inline void addChild(Layout* layout) 
	{ 
		layout->setParent(this);
		m_children.emplace_back(layout); 
	}

	inline std::vector<class Layout*>& getChildren() { return m_children; }

	void toggleAllWidgets();

	void onWindowResized(const SDL_Event& event);
	void onWindowSizeChanged(const SDL_Event& event);

	~Layout();

private:
	glm::vec2 m_position;
	glm::vec2 m_size;
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

