#pragma once

#include <vector>

#include <glm\glm.hpp>

#include "transform.h"
#include "textMaterial.h"

class Text
{
public:
	Text(const char* text, int x, int y, int size);
	~Text();

	inline int getX() { return m_x; }
	inline int getY() { return m_y; }
	inline int getSize() { return m_size; }

	inline void setX(int x) { m_x = x; }
	inline void setY(int y) { m_y = y; }
	inline void setSize(int size) { m_size = size; }

	inline TextMaterial* getMaterial() { return m_material; }
	inline void setMaterial(TextMaterial* material) { m_material = material; }

	void draw();

private:
	const char* m_text;
	int m_x;
	int m_y;
	int m_size;
	TextMaterial* m_material;

	unsigned int m_vbo_vertices;
	unsigned int m_vbo_uvs;
};

