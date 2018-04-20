#include "treeView.h"
#include "layout.h"
#include "../core/guiManager.h"

TreeView::TreeView(const glm::vec2& position, const glm::vec2& size, const std::string& font = "segoeui") : Widget(position, size)
{
	m_margin = glm::vec4(
		8.0f, // Top
		5.0f, // Right
		8.0f, // Bottom
		5.0f  // Left
	);

	m_font = font;
	m_fontSize = 20.0f;
	m_blur = 0.0f;
	m_align = NVG_ALIGN_LEFT;
	m_color = nvgRGBA(255, 255, 255, 100);
	m_textHoverColor = nvgRGB(47, 124, 202);
	m_background = nvgRGB(40, 40, 40);
	m_backgroundHoverColor = nvgRGB(50, 50, 50);
	m_borderRadius = 0.0f;
	m_opacity = 1.0f;
	m_offsetScroll = 0.0f;

	m_scrollbar = new Scrollbar(position, size);
	m_scrollbar->setExpandModeX(Widget::ExpandMode::PARENT);
	m_scrollbar->addEventListener("onMouseMove", &TreeView::onScrollbarDragged);

	this->addChild(m_scrollbar);
}

void TreeView::onScrollbarDragged(CallbackData data)
{
	Scrollbar* sender = (Scrollbar*)data.sender;
	TreeView* parent = (TreeView*)data.sender->getParent();

	parent->setOffsetScroll(sender->getHandleDragOffset());
}

float TreeView::getTreeItemHeight(glm::vec2& position, TreeItem* item, unsigned int index)
{
	if (item == nullptr)
		return 0.0f;

	float lh = 30.0f;
	float max = position.y + (lh * index);

	if (item->m_opened && item->m_children.size() > 0)
	{
		index++;
		for (auto child : item->m_children) 
		{
			float height = this->getTreeItemHeight(position, child, index++);
			max = height > max ? height : max;
		}

		position.y += lh * item->m_children.size();
	}

	return max;
}

void TreeView::update(double delta)
{

}

void TreeView::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	glm::vec2 position = this->getRelativePosition();
	glm::vec2 size = this->getRelativeSize();

	nvgBeginPath(ctx);
	nvgRoundedRect(ctx,
		position.x,
		position.y + 30.0f,
		size.x,
		size.y - 30.0f,
		m_borderRadius
	);

	nvgFillColor(ctx, nvgRGBAf(m_background.r, m_background.g, m_background.b, m_opacity));
	nvgFill(ctx);

	nvgScissor(ctx, position.x, position.y + 30.0f, size.x, size.y - 30.0f);

	position.y -= m_offsetScroll;

	this->drawTreeItem(ctx, position, size, m_root, 0, 1);
	nvgResetScissor(ctx);

	nvgRestore(ctx);
}

void TreeView::drawTreeItem(NVGcontext* ctx, glm::vec2& position, glm::vec2& size, TreeItem* item, unsigned int depth, unsigned int index)
{
	if (item != nullptr)
	{
		float lh = 20.0f;
		float y = position.y + (lh * index);

		if (item->m_hovered || item->m_selected)
		{
			nvgBeginPath(ctx);
			nvgRect(ctx,
				position.x,
				y + lh,
				size.x,
				lh
			);

			nvgFillColor(ctx, m_backgroundHoverColor);
			nvgFill(ctx);
		}

		if (item->m_icon != nullptr)
		{
			nvgFontSize(ctx, 34.0f);
			nvgFontFace(ctx, "entypo");
			nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

			nvgFillColor(ctx, item->m_hovered || item->m_selected ? m_textHoverColor : m_color);

			nvgText(ctx,
				position.x + (depth * 15.0f) + 20.0f,
				y + 30.0f,
				item->m_icon->get(),
				NULL
			);
		}

		nvgFontSize(ctx, m_fontSize);
		nvgFontFace(ctx, m_font.c_str());
		nvgTextAlign(ctx, m_align);
		nvgFontBlur(ctx, m_blur);
		nvgFillColor(ctx, item->m_hovered || item->m_selected ? m_textHoverColor : m_color);

		nvgText(ctx,
			position.x + (depth * 15.0f) + 30.0f,
			y + 35.0f,
			item->m_name.c_str(),
			NULL
		);

		depth++;
		if (item->m_opened && item->m_children.size() > 0)
		{
			index++;

			for (auto child : item->m_children)
				this->drawTreeItem(ctx, position, size, child, depth, index++);

			position.y += lh * item->m_children.size();
		}
	}
}

void TreeView::onKeyDown(const SDL_Event & event)
{

}

void TreeView::onTextInput(const SDL_Event & event)
{

}

void TreeView::onKeyUp(const SDL_Event & event)
{

}

void TreeView::onTreeItemMouseMove(const SDL_Event& event, glm::vec2& position, glm::vec2& size, TreeItem* item, unsigned int depth, unsigned int index)
{
	if (item != nullptr)
	{
		float lh = 20.0f;
		float y = position.y + (lh * index);

		Rect rect(glm::vec2(position.x, y + lh), glm::vec2(size.x, lh));
		item->m_hovered = rect.intersects(m_mouse);

		depth++;
		if (item->m_opened && item->m_children.size() > 0)
		{
			index++;

			for (auto child : item->m_children)
				this->onTreeItemMouseMove(event, position, size, child, depth, index++);

			position.y += lh * item->m_children.size();
		}
	}
}

void TreeView::onMouseMove(const SDL_Event& event)
{
	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	this->setState("hovered", this->intersects(m_mouse));

	if (event.button.state != SDL_PRESSED)
	{
		glm::vec2 position = this->getRelativePosition();
		glm::vec2 size = this->getRelativeSize();

		position.y -= m_offsetScroll;

		this->onTreeItemMouseMove(event, position, size, m_root, 0, 1);
	}
}

void TreeView::onMouseDown(const SDL_Event& event)
{

}

void TreeView::onTreeItemMouseUp(const SDL_Event& event, glm::vec2& position, glm::vec2& size, TreeItem* item, unsigned int depth, unsigned int index)
{
	if (item != nullptr)
	{
		float lh = 20.0f;
		float y = position.y + (lh * index);

		Rect rect(glm::vec2(position.x, y + lh), glm::vec2(size.x, lh));
		item->m_hovered = rect.intersects(m_mouse);

		if (item->m_hovered)
		{
			this->deselectAllItems(m_root);
			item->m_selected = true;

			if (event.button.clicks == 2)
			{
				item->m_opened = !item->m_opened;

				if (item->m_opened)
					this->loadTreeItem(item, item->m_path);
				else
					this->unloadTreeItem(item);
			}

			item->m_icon->setSymbol(item->m_opened == true ? "DOWN_DIR" : "RIGHT_DIR");
		}

		depth++;
		if (item->m_opened && item->m_children.size() > 0)
		{
			index++;

			for (auto child : item->m_children)
				this->onTreeItemMouseUp(event, position, size, child, depth, index++);

			position.y += lh * item->m_children.size();
		}
	}
}

void TreeView::onMouseUp(const SDL_Event& event)
{
	m_mouse = glm::vec2((float)event.motion.x, (float)event.motion.y);
	this->setState("hovered", this->intersects(m_mouse));
	LayerManager* layerManager = this->getLayout()->getGuiManager()->getLayerManager();

	if (event.button.button == SDL_BUTTON_LEFT)
	{
		layerManager->addWidget(0, this);

		unsigned int i = 0;
		int lh = 20;
		glm::vec2 position = this->getRelativePosition();
		glm::vec2 size = this->getRelativeSize();
		position.y -= m_offsetScroll;

		this->onTreeItemMouseUp(event, position, size, m_root, 0, 1);

		float height = this->getTreeItemHeight(glm::vec2(0.0f), this->getRoot(), 1);
		float scrollMax = this->getRelativeSize().y - 30.0f;

		m_scrollbar->computeHandleHeight(height, scrollMax);
	}
	else
		layerManager->removeWidget(0, this);
}

void TreeView::onWindowResized(const SDL_Event& event)
{

}

void TreeView::onWindowSizeChanged(const SDL_Event& event)
{
	float height = this->getTreeItemHeight(glm::vec2(0.0f), this->getRoot(), 1);
	float scrollMax = this->getRelativeSize().y - 30.0f;

	std::cout << "SCROLLMAX: " << this->getRelativeSize().y << std::endl;

	m_scrollbar->computeHandleHeight(height, scrollMax);
}

TreeView::~TreeView()
{
	delete m_scrollbar;
}
