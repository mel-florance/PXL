#include <iostream>
#include "GL/glew.h"

#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

#define WIDTH 1280.0f
#define HEIGHT 720.0f

int main(int argc, char* argv[]) 
{
	std::cout << "Engine started!" << std::endl;

	Display window(WIDTH, HEIGHT, "PXL Engine");
	Shader shader("./res/shaders/basicShader");
	Texture texture("./res/textures/rocks_COLOR.jpg");
	Transform transform(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f));
	Camera camera(glm::vec3(0, 0, -3), 70.f, window.getAspect(), 0.01f, 1000.0f);

	Vertex vertices[] = {
		Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
		Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec2(0.5f, 1.0f)),
		Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)),
	};

	unsigned indices[] = { 0, 1, 2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh monkey("./res/models/monkey.obj");

	float angle = 0.0f;

	while (!window.isClosed()) {
		window.clear(0.15f, 0.15f, 0.15f, 1.0f);

		float sinAngle = sinf(angle);
		float cosAngle = cosf(angle);

		transform.getPosition().x = sinAngle;
		transform.getPosition().z = cosAngle;

		transform.getRotation().x = angle;
		transform.getRotation().y = angle;
		transform.getRotation().z = angle;
		//transform.setScale(glm::vec3(cosAngle, cosAngle, cosAngle));

		shader.bind();
		shader.update(transform, camera);
		texture.bind(0);

		monkey.draw();

		window.swapBuffers();

		angle += 0.0001f;
	}

	return 0;
}