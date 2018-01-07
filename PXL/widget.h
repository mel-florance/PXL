#pragma once

#include "transform.h"
#include "texture.h"

class Widget
{
public:
	Widget();
	~Widget();

	inline Transform* getTransform() { return m_transform; }
	inline void setTransform(Transform* transform) { m_transform = transform; }

	inline Texture* getTexture() { return m_texture; }
	inline void setTexture(Texture* texture) { m_texture = texture; }

private:
	Transform* m_transform;
	Texture* m_texture;
};

