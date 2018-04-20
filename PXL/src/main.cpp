#include "core/engine.h"

int main(int argc, char* argv[]) 
{
	Engine* engine = new Engine(glm::vec2(1280.0f, 720.0f));
	engine->start();

	return 0;
}