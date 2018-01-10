#pragma once

#include <string>

#include "transform.h"
#include "texture.h"
#include "guiMaterial.h"


class Widget
{
public:
	Widget(const std::string& name, Shader* shader);
	~Widget();

	inline Transform* getTransform() { return m_transform; }
	inline void setTransform(Transform* transform) { m_transform = transform; }

	inline GuiMaterial* getMaterial() { return m_material; }
	inline void setMaterial(GuiMaterial* material) { m_material = material; }

private:
	std::string m_name;
	Transform* m_transform;
	GuiMaterial* m_material;
};

