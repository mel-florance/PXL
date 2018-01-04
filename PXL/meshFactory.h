#pragma once

#include <vector>
#include <glm\glm.hpp>

class MeshFactory
{
public:

	static std::vector<glm::vec2> getQuad() {
		std::vector<glm::vec2> v = {
			glm::vec2(-1.0f, 1.0f),
			glm::vec2(-1.0f, -1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, -1.0f)
		};

		return v;
	};

private:
	MeshFactory() {}
};