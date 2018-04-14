#include "menu.h"
#include "../core/guiManager.h"

Menu::Menu(const glm::vec2& position, const glm::vec2& size, const std::string& font) : Widget(position, size)
{
	m_background = nvgRGB(28, 28, 28);
	m_borderRadius = 3.0f;
	m_minHeight = 30.0f;
	m_minFontSize = 18.0f;
	m_margin = glm::vec4(
		8.0f, // Top
		5.0f, // Right
		8.0f, // Bottom
		5.0f  // Left
	);

	m_font = font;
	m_fontSize = 18.0f;
	m_blur = 0.0f;
	m_align = NVG_ALIGN_MIDDLE;
	m_color = nvgRGB(150, 150, 150);

	this->setDrawingShadow(true);
}

void Menu::onKeyDown(const SDL_Event& event)
{
	if (event.key.keysym.sym == SDLK_c && this->getState("hovered")) {
		this->setState("visible", this->getState("visible") == false);
	}
}

void Menu::onMouseMove(const SDL_Event& event)
{
	m_mouse = glm::vec2(event.motion.x, event.motion.y);
	glm::vec2 position = this->getRelativePosition();


	float sizeY = this->getLayout()->getComputedSize().y;
	sizeY = sizeY < m_minHeight ? m_minHeight : sizeY;

	unsigned int i = 0;
	float stackedWidth = -7.5f;

	for (auto& item : m_items)
	{
		stackedWidth += item->m_width + 15.0f + 9.0f;
		float x = position.x + stackedWidth - item->m_width;
		i++;

		Rect rect(
			glm::vec2(x - 7.5f, position.y + 5.0f),
			glm::vec2(item->m_width + 15.0f, sizeY - 8.0f)
		);

		item->m_hovered = rect.intersects(m_mouse);

		if (item->m_opened == true)
		{
			unsigned int j = 0;
			for (auto& child : item->m_children)
			{
				float y = position.y + sizeY + (j * 25.0f);
				Rect childRect(
					glm::vec2(x - 15.0f, y),
					glm::vec2(230.0f, 25.0f)
				);

				child->m_hovered = childRect.intersects(m_mouse);
				child->m_opened = child->m_hovered;
				j++;

				if (child->m_isSeparator == true)
					j--;
			}
		}
	}
}

void Menu::onMouseDown(const SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		LayerManager* layerManager = this->getLayout()->getGuiManager()->getLayerManager();

		Rect rect(
			this->getRelativePosition(),
			this->getLayout()->getComputedSize()
		);

		if (rect.intersects(m_mouse)) {
			std::cout << "added" << std::endl;
			layerManager->addWidget(0, this);
		}
		else {
			std::cout << "removed" << std::endl;
			layerManager->removeWidget(0, this);
		}
	}
}

void Menu::onMouseUp(const SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouse = glm::vec2(event.motion.x, event.motion.y);
		glm::vec2 position = this->getRelativePosition();

		unsigned int i = 0;
		float stackedWidth = -7.5f;

		float sizeY = this->getLayout()->getComputedSize().y;
		sizeY = sizeY < m_minHeight ? m_minHeight : sizeY;


		for (auto& item : m_items)
		{
			stackedWidth += item->m_width + 15.0f + 9.0f;
			i++;
			float x = position.x + stackedWidth - item->m_width;


			Rect rect(
				glm::vec2(x - 7.5f, position.y + 5.0f),
				glm::vec2(item->m_width + 15.0f, sizeY - 8.0f)
			);

			unsigned int j = 0;
			for (auto& child : item->m_children)
			{
				float y = position.y + sizeY + (j * 25.0f);
				Rect childRect(
					glm::vec2(x - 15.0f, y),
					glm::vec2(230.0f, 25.0f)
				);

				child->m_hovered = childRect.intersects(m_mouse);
				child->m_opened = child->m_hovered;

				if (child->m_hovered == true && item->m_opened == true)
				{
					child->handleEventListener("mouseUp", { this });
				}

				j++;

				if (child->m_isSeparator == true)
					j--;
			}

			item->m_hovered = rect.intersects(m_mouse);
			item->m_opened = item->m_hovered;
		}
	}
}

void Menu::update(double delta)
{

}

void Menu::draw(NVGcontext* ctx, double delta)
{
	nvgSave(ctx);

	glm::vec2 position = this->getRelativePosition();
	float sizeY = this->getLayout()->getComputedSize().y;
	sizeY = sizeY < m_minHeight ? m_minHeight : sizeY;

	nvgBeginPath(ctx);
	nvgRect(ctx,
		position.x,
		position.y,
		this->getLayout()->getComputedSize().x,
		sizeY
	);

	nvgFillColor(ctx, m_background);
	nvgFill(ctx);

	float fontSize = 0.01f * this->getWindow()->getSize().x;
	fontSize = fontSize < m_minFontSize ? m_minFontSize : fontSize;

	nvgFontSize(ctx, fontSize);
	nvgFontFace(ctx, m_font.c_str());
	nvgTextAlign(ctx, m_align);
	nvgFontBlur(ctx, m_blur);


	// Draw menu items - First depth
	float stackedWidth = -7.5f;
	for (auto& item : m_items)
	{
		item->m_width = nvgTextBounds(ctx, 0, 0, item->m_data.c_str(), NULL, 0);
		stackedWidth += item->m_width + 15.0f + 6.0f;
		float x = position.x + stackedWidth - item->m_width;

		// Draw menu item background
		if (item->m_hovered || item->m_opened)
		{
			nvgBeginPath(ctx);
			nvgRoundedRect(ctx,
				x - 7.5f,
				position.y + 5.0f,
				item->m_width + 15.0f,
				sizeY - 8.0f,
				m_borderRadius
			);

			nvgFillColor(ctx, nvgRGB(40, 40, 40));
			nvgFill(ctx);
			m_color = nvgRGB(200, 200, 200);
		}
		else
			m_color = nvgRGB(150, 150, 150);
		
		nvgFillColor(ctx, m_color);

		// Draw menu item text
		nvgText(ctx,
			x,
			position.y + (sizeY * 0.5f),
			item->m_data.c_str(),
			NULL
		);

		if (item->m_opened && item->m_children.size() > 0)
		{
			float lh = 25.0f;
			float w = 230.0f;

			// Draw opened menu shadow
			if (this->isDrawingShadow())
			{
				float h = item->m_children.size() * lh - (item->getNbSeparators() * lh);

				m_shadowPaint = nvgBoxGradient(
					ctx,
					x - 7.5f,
					position.y + lh + 7.0f,
					w,
					h,
					m_borderRadius,
					8.0f,
					nvgRGBA(0, 0, 0, 64),
					nvgRGBA(0, 0, 0, 0)
				);

				nvgBeginPath(ctx);
				nvgRect(ctx,
					x - 10.0f,
					position.y + lh + 5.0f,
					w + lh,
					h + lh
				);

				nvgRoundedRect(ctx,
					x - 7.5f,
					position.y + lh + 7.0f,
					w,
					h - 3.0f,
					m_borderRadius
				);

				nvgPathWinding(ctx, NVG_HOLE);
				nvgFillPaint(ctx, m_shadowPaint);
				nvgFill(ctx);
			}
			
			// Draw childs
			unsigned int j = 0;
			float y = 0.0f;
			bool isSep = false;
			for (auto& child : item->m_children)
			{
				j++;
				y = position.y + (j * lh);

				if (child->m_isSeparator == true)
				{
					// Draw separator
					nvgBeginPath(ctx);
					nvgRect(ctx,
						x - 7.5f,
						y + 5.0f,
						w,
						1.0f
					);

					nvgFillColor(ctx, nvgRGB(40, 40, 40));
					nvgFill(ctx);

					j--;
				}
				else
				{
					// Draw child background
					nvgBeginPath(ctx);
					nvgRect(ctx,
						x - 7.5f,
						y + 5.0f + (isSep ? 1.0f : 0.0f),
						w,
						lh
					);

					if (child->m_hovered)
						nvgFillColor(ctx, nvgRGB(40, 40, 40));
					else
						nvgFillColor(ctx, nvgRGB(28, 28, 28));

					nvgFill(ctx);
				}

				isSep = child->m_isSeparator;
			}

			j = 0;
			for (auto& child : item->m_children)
			{
				j++;
				float y = position.y + (j * lh);

				// Draw child icon
				if (child->hasIcon()) 
				{
					nvgFontSize(ctx, fontSize);
					nvgFontFace(ctx, "entypo");

					if (child->m_hovered)
						nvgFillColor(ctx, nvgRGB(47, 124, 202));
					else
						nvgFillColor(ctx, nvgRGB(100, 100, 100));

					nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

					nvgText(ctx,
						x + 7.5f,
						y + 18.0f,
						child->m_icon->get(),
						NULL
					);
				}

				// Draw child text
				if (child->m_isSeparator == true)
				{
					j--;
				}
				else
				{
					if (child->m_hovered)
						nvgFillColor(ctx, nvgRGB(47, 124, 202));
					else
						nvgFillColor(ctx, nvgRGB(150, 150, 150));

					nvgFontSize(ctx, fontSize);
					nvgFontFace(ctx, m_font.c_str());
					nvgTextAlign(ctx, m_align);
					nvgFontBlur(ctx, m_blur);

					nvgText(ctx,
						x + (item->getNbChildIcons() > 0 ? 25.0f : 5.0f),
						y + 18.0f,
						child->m_data.c_str(),
						NULL
					);

					// Draw shortcut text
					if (child->m_shortcut.size() > 0)
					{
						float shortcutWidth = nvgTextBounds(ctx, 0, 0, child->m_shortcut.c_str(), NULL, 0);

						nvgFillColor(ctx, nvgRGB(100, 100, 100));

						nvgText(ctx,
							x + w - shortcutWidth - 15.0f,
							y + 18.0f,
							child->m_shortcut.c_str(),
							NULL
						);
					}
				}
			}
		}
	}

	nvgRestore(ctx);
}

Menu::~Menu()
{

}
