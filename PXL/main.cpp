#include <iostream>

#include "engine.h"

float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

int main(int argc, char* argv[]) 
{
	Engine* engine = new Engine();
	engine->start();

	return 0;
}