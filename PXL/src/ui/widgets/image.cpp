
#include "image.h"

 Image::Image(NVGcontext & ctx, const std::string & name, glm::vec2 & position, glm::vec2 & size) {

	m_ctx = ctx;
	m_name = name;
	m_image = nvgCreateImage(ctx, name.c_str(), NVG_IMAGE_GENERATE_MIPMAPS);
}

 Image::~Image() {


}

void Image::draw(NVGcontext & ctx, double delta) {

	nvgSave(ctx);

	float x = this->getPosition().x;
	float y = this->getPosition().y;

	if (this->getParent() != nullptr)
	{
		x = this->getParent()->getPosition().x + x;
		y = this->getParent()->getPosition().y + y;
	}

	NVGpaint pattern = nvgImagePattern(
		ctx,
		x,
		y,
		this->getSize().x,
		this->getSize().y,
		0.0f / 180.0f * NVG_PI,
		m_image, 
		1.0f
	);

	nvgBeginPath(ctx);
	nvgRect(ctx, x, y, this->getSize().x, this->getSize().y);
	nvgFillPaint(ctx, pattern);
	nvgFill(ctx);

	nvgRestore(ctx);
}

